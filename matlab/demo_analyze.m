
folderObs = '/data/sls/scratch/fgrondin/experiments/gccphat/obs/';
folderResult = '/data/sls/scratch/fgrondin/experiments/gccphat/results/';
folderSummary = '/data/sls/scratch/fgrondin/experiments/gccphat/summaries/';

setups = { 'betaHigh-snrHigh', ...
           'betaHigh-snrMid', ...
           'betaHigh-snrLow', ...
           'betaMid-snrHigh', ...
           'betaMid-snrMid', ...
           'betaMid-snrLow', ...
           'betaLow-snrHigh', ...
           'betaLow-snrMid', ...
           'betaLow-snrLow' };

methods = { 'm-1', 'f-1', 'f-2', 'f-4', 'f-8', 'f-16', 'f-32', 'q-1', 'q-2', 'q-4', 'q-8', 'q-16', 'q-32', 's-1' };

tags_keys = { 'm-1', 'f-1', 'f-2', 'f-4', 'f-8', 'f-16', 'f-32', 'q-1', 'q-2', 'q-4', 'q-8', 'q-16', 'q-32', 's-1' };
tags_values = { 'MM', 'FFT01', 'FFT02', 'FFT04', 'FFT08', 'FFT16', 'FFT32', 'FFT01-QI', 'FFT02-QI', 'FFT04-QI', 'FFT08-QI', 'FFT16-QI', 'FFT32-QI', 'SVD' };

tags = containers.Map(tags_keys, tags_values);

for iSetup = 1:1:length(setups)
     
    results = cell(length(methods),3);

    for iMethod = 1:1:length(methods)

        % File with theoretical DOAs
        fileDOAs = [ folderObs setups{iSetup} '/' 'doas.mat' ];

        % Generate list of input files
        dirResult = dir([folderResult setups{iSetup} '/' methods{iMethod} '/' '*.txt']);
        nResults = length(dirResult);
        filesResult = cell(nResults,1);
        for iResult = 1:1:nResults
            filesResult{iResult} = [ folderResult setups{iSetup} '/' methods{iMethod} '/' dirResult(iResult).name ];
        end

        % Analyze
        [rsme, rmse] = analyze(filesResult, fileDOAs);

        results{iMethod,1} = methods{iMethod};
        results{iMethod,2} = rsme;
        results{iMethod,3} = rmse;

    end
    
    rmse_string = sprintf('RMSE Method\n');
    rsme_string = sprintf('RSME Method\n');
    
    for iMethod = 1:1:length(methods)
        
        rmse_string = sprintf('%s%1.6f %s\n', rmse_string, results{iMethod,3}, tags(results{iMethod,1}));
        rsme_string = sprintf('%s%1.6f %s\n', rsme_string, results{iMethod,2}, tags(results{iMethod,1}));
        
    end

    fid = fopen([folderSummary 'rmse_' setups{iSetup} '.dat'],'w');
    fprintf(fid, rmse_string);
    fclose(fid);

    fid = fopen([folderSummary 'rsme_' setups{iSetup} '.dat'],'w');
    fprintf(fid, rsme_string);
    fclose(fid);    
    
end
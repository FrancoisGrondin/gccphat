
% Parameters  
simulation = [];
simulation.d = 0.05;
simulation.betas = [ 0.6 0.6 ];
simulation.snrs = [ 10 10 ];
simulation.roomSizes = [ 5 5 3 10 10 5 ; 10 10 3 20 20 5 ; 20 20 5 50 50 10 ]; 
simulation.marginSize = 0.5;
simulation.distanceMinimum = 0.5;
simulation.fS = 16000;
simulation.c = 343;
simulation.frameSize = 512;
simulation.hopSize = 160;

% Folders with inputs and outputs
folderSrc = '/data/sls/scratch/fgrondin/dataset/timit/clean/';
folderObs = '/data/sls/scratch/fgrondin/experiments/gccphat/obs/betaHigh-snrLow/';

% Generate list of input files
dirSrc = dir([folderSrc '*.wav']);
nSrcs = length(dirSrc);
filesSrc = cell(nSrcs,1);
for iSrc = 1:1:nSrcs
    filesSrc{iSrc} = [ folderSrc dirSrc(iSrc).name ];
end

% Generate list of output files
nObs = 1000;
filesObs = cell(nObs,1);
for iObs = 1:1:nObs
    filesObs{iObs} = [ folderObs sprintf('%08d.bin',iObs) ];
end

% File with theoretical DOAs
fileDOAs = [ folderObs 'doas.mat' ];

% Process
simulate(filesSrc, filesObs, fileDOAs, simulation);


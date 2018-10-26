function [rsme, rmse] = analyze(filesResult, fileDOAs)

    doas = load(fileDOAs,'doas');
    doas = doas.doas;
    
    nDoas = length(doas);
    nResults = length(filesResult);
    
    rsme = 0.0;
    rmse = 0.0;
    
    for iResult = 1:1:nResults
       
        [doas_results, energies_results] = import_results(filesResult{iResult});
        
        [~,name,~] = fileparts(filesResult{iResult});
        
        found = 0;
        for iDoa = 1:1:nDoas
            
            if (strcmp(doas{iDoa,1},name)==1)
               
                found = 1;
                break;
                
            end
            
        end
        
        if (found == 0)
           error(['Cannot find tag ' name]);
        end
        
        doa = doas{iDoa,2};
        
        mu = sum(doas_results .* energies_results) / sum(energies_results);
        sigma2 = sum(((doas_results - mu).^2) .* energies_results) / sum(energies_results);
        
        rsme_element = sqrt((mu-doa).^2);
        rmse_element = sqrt(sigma2);
        
        rsme = rsme + rsme_element;
        rmse = rmse + rmse_element;
        
    end
    
    rsme = rsme / nResults;
    rmse = rmse / nResults;

return
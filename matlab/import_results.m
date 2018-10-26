function [doas, energies] = import_results(fileResult)

    tmp = dlmread(fileResult);
    doas = tmp(:,1);
    energies = tmp(:,2);

return
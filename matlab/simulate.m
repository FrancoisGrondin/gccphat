function simulate(filesSrc, filesObs, fileDOAs, simulation)

    %
    % filesSrc:    List of speech wave files
    % filesObs:    List of generated observations
    % fileDoa:     File with all theoretical DOAs
    %
    % simulation:   Structure that contains all parameters:
    %
    %   simulation.d:               1x1 double
    %                               Spacing between microphones (in m)
    %
    %   simulation.betas:           1x2 double                
    %                               Minimum and maximum RT60 (in sec)
    %
    %   simulation.snrs:            1x2 double                
    %                               Minimum and maximum SNRs (in dB)
    %
    %   simulation.roomSizes:       (nb room types)x6 double
    %                               Room sizes [ Lx_min Ly_min Lz_min 
    %                               Lx_max Ly_max Lz_max ] (in m)
    %
    %   simulation.marginSize:      1x1 double
    %                               Minimum distance between mic and/or 
    %                               src with walls (in m)
    %
    %   simulation.distanceMinimum: 1x1 double
    %                               Minimum distance between mics and the
    %                               src (in m)
    %
    %   simulation.fS:              1x1 double
    %                               Sample rate (in samples/sec)
    %
    %   simulation.c:               1x1 double
    %                               Speed of sound (in m/sec)
    %
    %   simulation.frameSize:       1x1 double
    %                               Frame size (in samples)
    %
    %   simulation.hopSize:         1x1 double
    %                               Shift between frames (in samples)    
    %

    nSrcs = length(filesSrc);
    nObs = length(filesObs);
    
    doas = cell(nObs,2);

    for iObs = 1:1:nObs
       
        % Choose one of the room randomly
        room_id = ceil(rand(1) * size(simulation.roomSizes,1));
        
        % Generate room dimensions
        room = generate_room( simulation.roomSizes(room_id, 1:1:3), ...
                              simulation.roomSizes(room_id, 4:1:6), ...
                              simulation.marginSize, ...
                              simulation.distanceMinimum, ...
                              simulation.d );

        % Choose reflection coefficients randomly
        beta = ones(1,6) * rand(1) * (simulation.betas(2) - simulation.betas(1)) + simulation.betas(1);
                          
        % Generate room impulse response
        rir = generate_rir( room, ...
                            simulation.fS, ...
                            simulation.c, ...
                            beta );

        % Generate SNR randomly
        snr = rand(1) * (simulation.snrs(2) - simulation.snrs(1)) + simulation.snrs(1);
                        
        % Get random wave file
        iSrc = ceil(nSrcs * rand(1));
        s = audioread(filesSrc{iSrc});
        
        % Perform filtering and add noise
        x = [ filter(rir(1,:), 1, s') ; filter(rir(2,:), 1, s') ];
        g = sqrt((10^(snr/10)) ./ (mean(x.^2,2)));
        y = (g * ones(1, size(x,2))) .* x + randn(size(x));
        
        % Generate spectrogram
        Xv = generate_stft( y, ...
                            simulation.hopSize, ...
                            simulation.frameSize );

        % Get theoretical DOA
        doa = generate_doa(room);
        [~,name,~] = fileparts(filesObs{iObs});
        doas{iObs,1} = name;
        doas{iObs,2} = doa;

        % Write observations to file
        fid = fopen(filesObs{iObs},'wb');
        fwrite(fid, single(Xv), 'float');
        fclose(fid);

    end

    % Write DOAs to file
    save(fileDOAs, 'doas');
    
return

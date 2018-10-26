function room = generate_room(roomSizeMin, roomSizeMax, marginSize, distanceMinimum, micSpacing)

    roomSize = roomSizeMin + (roomSizeMax - roomSizeMin) .* rand(1,3);
    
    while(true)
        
        mics = roomSize .* rand(1,3);
        direction = randn(1,3);
        direction = direction ./ (norm(direction) + eps);
        mic1 = mics + micSpacing * direction/2.0;
        mic2 = mics - micSpacing * direction/2.0;
        
        src = roomSize .* rand(1,3);
        
        dist1 = min(abs(mic1 - zeros(1,3)));
        dist2 = min(abs(mic2 - zeros(1,3)));
        dist3 = min(abs(src - zeros(1,3)));
        dist4 = min(abs(mic1 - roomSize));
        dist5 = min(abs(mic2 - roomSize));
        dist6 = min(abs(src - roomSize));
        dist7 = norm(mic1 - src);
        dist8 = norm(mic2 - src);
        
        if ((dist1 >= marginSize) && ...
            (dist2 >= marginSize) && ...
            (dist3 >= marginSize) && ...
            (dist4 >= marginSize) && ...
            (dist5 >= marginSize) && ...
            (dist6 >= marginSize) && ...
            (dist7 >= distanceMinimum) && ...
            (dist8 >= distanceMinimum))
        
            break;
        
        end
        
    end
    
    room = [];
    room.size = roomSize;
    room.mic1 = mic1;
    room.mic2 = mic2;
    room.src = src;

return
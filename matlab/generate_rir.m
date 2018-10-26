function h = generate_rir(room, fS, c, beta)

    r = [ room.mic1 ; room.mic2 ];
    s = room.src;
    L = room.size;
    n = 4096;

    h = rir_generator(c, fS, r, s, L, beta, n);

return
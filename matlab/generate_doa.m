function doa = generate_doa(room)

    mic = room.mic2 - room.mic1;
    src = room.src - (room.mic1 + room.mic2) / 2;

    doa = asin(dot(mic,src) / (norm(mic)*norm(src)));

return
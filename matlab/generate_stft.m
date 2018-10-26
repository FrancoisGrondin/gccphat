function Xv = generate_stft(x, hopSize, frameSize)

    X1 = time2freq(x(1,:), hopSize, frameSize);
    X2 = time2freq(x(2,:), hopSize, frameSize);
    
    X = X1.*conj(X2)./(abs(X1).*abs(X2)+eps);

    Xv_real = reshape(real(X)',1,numel(X));
    Xv_imag = reshape(imag(X)',1,numel(X));
    Xv_reim = [Xv_real; Xv_imag];
    Xv = reshape(Xv_reim,1,numel(Xv_reim));    
    
return
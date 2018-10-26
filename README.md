# GCC-PHAT

## Building the library

You need to have cmake installed:

```
sudo apt-get install cmake
```

And the FFTW library installed:

```
sudo apt-get install libfftw3-dev
```

Change to the `gccphat` root directory. Create a new directory `build`

```
mkdir build
```

Move to the directory `build`

```
cd build
```

Launch cmake

```
cmake ../
```

Make the library

```
make
```

## Using GCC-PHAT

### Toy example

To test the sample file `xcorrspectra.dat` that contains the cross-correlated normalized spectrum with the FFT method with interpolation rate of 1:

```
cat ../example/xcorrspectra.dat | ../bin/gccphat -c 343 -d 0.05 -i 1 -m f -N 512 -o -Q 181 -r 16000
```

This should return the following result in the terminal:

```
0.226893 0.822148
0.226893 0.809518
0.226893 0.794880
0.226893 0.791429
0.226893 0.755286
0.226893 0.787747
...
0.226893 0.822148
0.226893 0.809518
0.226893 0.794880
0.226893 0.791429
0.226893 0.755286
0.226893 0.787747
```

The first column corresponds to the angle in radian, and the second column holds the energy. Each line corresponds to a frame.

To compute the execution time, replace the `-o` option by `-l`, as in the following call (the execution time does not include the initialization time to prepare the system before processing the frames):

```
cat ../example/xcorrspectra.dat | ../bin/gccphat -c 343 -d 0.05 -i 1 -m f -N 512 -l -Q 181 -r 16000
```

This returns a value that correspond to the time (in sec) for all frames:

```
0.000648
```

### Configurations in the paper

Here are the different configurations tested in the paper:

- MM: ` ../bin/gccphat -c 343 -d 0.05 -i 1 -m m -N 512 -o -Q 181 -r 16000`
- FFT01: ` ../bin/gccphat -c 343 -d 0.05 -i 1 -m f -N 512 -o -Q 181 -r 16000`
- FFT02: ` ../bin/gccphat -c 343 -d 0.05 -i 2 -m f -N 512 -o -Q 181 -r 16000`
- FFT04: ` ../bin/gccphat -c 343 -d 0.05 -i 4 -m f -N 512 -o -Q 181 -r 16000`
- FFT08: ` ../bin/gccphat -c 343 -d 0.05 -i 8 -m f -N 512 -o -Q 181 -r 16000`
- FFT16: ` ../bin/gccphat -c 343 -d 0.05 -i 16 -m f -N 512 -o -Q 181 -r 16000`
- FFT32: ` ../bin/gccphat -c 343 -d 0.05 -i 32 -m f -N 512 -o -Q 181 -r 16000`
- FFT01-QI: ` ../bin/gccphat -c 343 -d 0.05 -i 1 -m q -N 512 -o -Q 181 -r 16000`
- FFT02-QI: ` ../bin/gccphat -c 343 -d 0.05 -i 2 -m q -N 512 -o -Q 181 -r 16000`
- FFT04-QI: ` ../bin/gccphat -c 343 -d 0.05 -i 4 -m q -N 512 -o -Q 181 -r 16000`
- FFT08-QI: ` ../bin/gccphat -c 343 -d 0.05 -i 8 -m q -N 512 -o -Q 181 -r 16000`
- FFT16-QI: ` ../bin/gccphat -c 343 -d 0.05 -i 16 -m q -N 512 -o -Q 181 -r 16000`
- FFT32-QI: ` ../bin/gccphat -c 343 -d 0.05 -i 32 -m q -N 512 -o -Q 181 -r 16000`
- SVD: ` ../bin/gccphat -c 343 -d 0.05 -i 1 -m s -N 512 -o -Q 181 -r 16000`



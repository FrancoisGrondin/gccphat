#ifndef __GCCPHATFFT_UTILS_GPFFT
#define __GCCPHATFFT_UTILS_GPFFT

    #include <math.h>
    #include <stdlib.h>
    #include <string.h>
    #include <fftw3.h>

    typedef struct gpfft_obj {

        unsigned int N;
        unsigned int Ni;
        unsigned int fS;
        float c;
        float d;
        unsigned int i;
        
        unsigned int K;
        unsigned int Ki;
        unsigned int Q;
                
        float * thetas;
        float * tdoas;
        unsigned int * mapper;

        fftwf_plan C2R;
        fftwf_complex * complexArray;
        float * realArray;

    } gpfft_obj;

    gpfft_obj * gpfft_construct(const unsigned int N, const unsigned int fS, const float c, const float d, const unsigned int Q, const unsigned int i);

    void gpfft_destroy(gpfft_obj * obj);

    int gpfft_process(gpfft_obj * obj, const float * X, float * x);

#endif
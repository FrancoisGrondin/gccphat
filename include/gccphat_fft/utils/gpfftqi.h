#ifndef __GCCPHATFFT_UTILS_GPFFTQI
#define __GCCPHATFFT_UTILS_GPFFTQI

    #include <math.h>
    #include <stdlib.h>
    #include <string.h>
    #include <fftw3.h>

    typedef struct gpfftqi_obj {

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
        float * deltas;
        unsigned int * mapperPrev;
        unsigned int * mapper;
        unsigned int * mapperNext;

        fftwf_plan C2R;
        fftwf_complex * complexArray;
        float * realArray;

    } gpfftqi_obj;

    gpfftqi_obj * gpfftqi_construct(const unsigned int N, const unsigned int fS, const float c, const float d, const unsigned int Q, const unsigned int i);

    void gpfftqi_destroy(gpfftqi_obj * obj);

    int gpfftqi_process(gpfftqi_obj * obj, const float * X, float * x);

#endif
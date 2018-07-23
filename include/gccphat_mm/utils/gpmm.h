#ifndef __GCCPHATMM_UTILS_GPMM
#define __GCCPHATMM_UTILS_GPMM

    #include <math.h>
    #include <stdlib.h>
    #include <string.h>

    typedef struct gpmm_obj {

        unsigned int N;
        unsigned int fS;
        float c;
        float d;
        
        unsigned int K;
        unsigned int Q;
                
        float * thetas;
        float * tdoas;

        float * W_real;
        float * W_imag;

    } gpmm_obj;

    gpmm_obj * gpmm_construct(const unsigned int N, const unsigned int fS, const float c, const float d, const unsigned int Q);

    void gpmm_destroy(gpmm_obj * obj);

    int gpmm_process(gpmm_obj * obj, const float * X, float * x);

    int gpmm_getMatrices(gpmm_obj * obj, float * W_real, float * W_imag);

#endif
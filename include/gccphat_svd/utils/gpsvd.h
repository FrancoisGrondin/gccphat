#ifndef __GCCPHATSVD_UTILS_GPSVD
#define __GCCPHATSVD_UTILS_GPSVD

    #include <stdlib.h>
    #include "matrix.h"
    #include "svd.h"

    typedef struct gpsvd_obj {

        unsigned int N;
        unsigned int fS;
        float c;
        float d;
        
        unsigned int K;
        unsigned int Q;
                
        float * thetas;
        float * tdoas;

        unsigned int R_real;
        unsigned int R_imag;

        float * U_real;
        float * T_real;

        float * U_imag;
        float * T_imag;

        float * TX_real;
        float * TX_imag;

    } gpsvd_obj;

    gpsvd_obj * gpsvd_construct(const unsigned int N, const unsigned int fS, const float c, const float d, const unsigned int Q);

    void gpsvd_destroy(gpsvd_obj * obj);

    int gpsvd_process(gpsvd_obj * obj, const float * X, float * x);

#endif
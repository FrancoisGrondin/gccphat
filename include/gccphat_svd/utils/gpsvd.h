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
        unsigned int R;
        
        matrix_obj * thetas;
        matrix_obj * tdoas;

        matrix_obj * Ureal;
        matrix_obj * SVTreal;

        matrix_obj * Uimag;
        matrix_obj * SVTimag;

    } gpsvd_obj;

    gpsvd_obj * gpsvd_construct(const unsigned int N, const unsigned int fS, const float c, const float d, const unsigned int Q);

    void gpsvd_destroy(gpsvd_obj * obj);

    int gpsvd_process(gpsvd_obj * obj, const float * X, float * x);

#endif
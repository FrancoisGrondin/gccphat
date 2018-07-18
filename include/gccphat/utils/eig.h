#ifndef __GCCPHAT_UTILS_EIG
#define __GCCPHAT_UTILS_EIG

    #include <stdlib.h>
    #include <gccphat/utils/matrix.h>
    #include <gccphat/utils/qr.h>

    typedef struct eig_obj {

        unsigned int M;
        
        matrix_obj * Q;
        matrix_obj * R;

        matrix_obj * QT;
        matrix_obj * A;
        matrix_obj * QTA;
        matrix_obj * QTV;

        matrix_obj * I;
        matrix_obj * D;

        qr_obj * qr;

    } eig_obj;

    eig_obj * eig_construct(const unsigned int M);

    void eig_destroy(eig_obj * obj);

    int eig_process(eig_obj * obj, const matrix_obj * A, matrix_obj * V, matrix_obj * D);

#endif
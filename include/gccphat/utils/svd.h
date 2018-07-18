#ifndef __GCCPHAT_UTILS_SVD
#define __GCCPHAT_UTILS_SVD

    #include <stdlib.h>
	#include <gccphat/utils/eig.h>
    #include <gccphat/utils/matrix.h>	

	typedef struct svd_obj {

		unsigned int M;
		unsigned int N;

		matrix_obj * A;
		matrix_obj * AT;

		matrix_obj * ATA;
		matrix_obj * AAT;

		matrix_obj * D1;
		matrix_obj * V1;
		matrix_obj * D2;
		matrix_obj * V2;

		matrix_obj * U;
		matrix_obj * S;
		matrix_obj * V;

		eig_obj * eigM;
		eig_obj * eigN;

	} svd_obj;

	svd_obj * svd_construct(const unsigned int M, const unsigned int N);

	void svd_destroy(svd_obj * obj);

	int svd_process(svd_obj * obj, const matrix_obj * A, matrix_obj * U, matrix_obj * S, matrix_obj * V);

#endif
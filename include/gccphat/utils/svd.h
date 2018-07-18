#ifndef __GCCPHAT_UTILS_SVD
#define __GCCPHAT_UTILS_SVD

    #include <stdlib.h>
	#include <gccphat/utils/matrix.h>

	typedef struct svd_obj {


	} svd_obj;

	svd_obj * svd_construct(const unsigned int M, const unsigned int N);

	void svd_destroy(svd_obj * obj);

	int svd_process(svd_obj * obj, const matrix_obj * A, matrix_obj * U, matrix_obj * S, matrix_obj * V);

#endif
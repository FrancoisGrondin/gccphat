#ifndef __GCCPHATSVD_UTILS_SVD
#define __GCCPHATSVD_UTILS_SVD

    #include <stdlib.h>
	#include "matrix.h"

	typedef struct svd_obj {

	} svd_obj;

	svd_obj * svd_construct(void);

	void svd_destroy(svd_obj * obj);

	int svd_process(svd_obj * obj, const matrix_obj * A, matrix_obj * U, matrix_obj * S, matrix_obj * V);

#endif

	#include <gccphat.h>

	int main(int argc, char * argv[]) {

		matrix_obj * A;
		matrix_obj * U;
		matrix_obj * S;
		matrix_obj * V;
		
		svd_obj * svd;

		A = matrix_construct(4,3);
		U = matrix_construct(4,3);
		S = matrix_construct(3,3);
		V = matrix_construct(3,3);

		matrix_setR(A, 0, 0, 1.0);
		matrix_setI(A, 0, 0, 1.0);
		matrix_setR(A, 0, 1, 2.0);
		matrix_setI(A, 0, 1, 2.0);
		matrix_setR(A, 0, 2, 3.0);
		matrix_setI(A, 0, 2, 3.0);

		matrix_setR(A, 1, 0, 4.0);
		matrix_setI(A, 1, 0, 4.0);
		matrix_setR(A, 1, 1, 5.0);
		matrix_setI(A, 1, 1, 5.0);
		matrix_setR(A, 1, 2, 6.0);
		matrix_setI(A, 1, 2, 6.0);

		matrix_setR(A, 2, 0, 7.0);
		matrix_setI(A, 2, 0, 7.0);
		matrix_setR(A, 2, 1, 8.0);
		matrix_setI(A, 2, 1, 8.0);
		matrix_setR(A, 2, 2, 9.0);
		matrix_setI(A, 2, 2, 9.0);

		matrix_setR(A, 3, 0, -1.0);
		matrix_setI(A, 3, 0, 2.0);
		matrix_setR(A, 3, 1, -3.0);
		matrix_setI(A, 3, 1, 1.0);
		matrix_setR(A, 3, 2, 4.0);
		matrix_setI(A, 3, 2, -3.0);

		svd = svd_construct();

		svd_process(svd, A, U, S, V);

		matrix_printf(A);

		return 0;

	}
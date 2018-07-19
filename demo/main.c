
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

		matrix_set(A, 0, 0, 1.0);
		matrix_set(A, 0, 1, 2.0);
		matrix_set(A, 0, 2, 3.0);
		
		matrix_set(A, 1, 0, 4.0);
		matrix_set(A, 1, 1, 5.0);
		matrix_set(A, 1, 2, 6.0);

		matrix_set(A, 2, 0, 7.0);
		matrix_set(A, 2, 1, 8.0);
		matrix_set(A, 2, 2, 9.0);

		matrix_set(A, 3, 0, -1.0);
		matrix_set(A, 3, 1, -3.0);
		matrix_set(A, 3, 2, 4.0);

		svd = svd_construct();

		svd_process(svd, A, U, S, V);

		printf("A = \n");
		matrix_printf(A);
		printf("\n");

		printf("U = \n");
		matrix_printf(U);
		printf("\n");

		printf("S = \n");
		matrix_printf(S);
		printf("\n");

		printf("V = \n");
		matrix_printf(V);
		printf("\n");


		return 0;

	}
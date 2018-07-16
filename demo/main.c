
	#include <gccphat.h>

	int main(int argc, char * argv[]) {

		matrix_obj * A;
		matrix_obj * Q;
		matrix_obj * QA;
		scalar_struct a;
		householder_obj * ho;

		A = matrix_construct(3,3);
		Q = matrix_construct(3,3);
		QA = matrix_construct(3,3);

		a.real = 12; a.imag = 0; matrix_setElement(A, 0, 0, &a);
		a.real = -51; a.imag = 0; matrix_setElement(A, 0, 1, &a);
		a.real = 4; a.imag = 0; matrix_setElement(A, 0, 2, &a);
		a.real = 6; a.imag = 0; matrix_setElement(A, 1, 0, &a);
		a.real = 167; a.imag = 0; matrix_setElement(A, 1, 1, &a);
		a.real = -68; a.imag = 0; matrix_setElement(A, 1, 2, &a);
		a.real = -4; a.imag = 0; matrix_setElement(A, 2, 0, &a);
		a.real = 24; a.imag = 0; matrix_setElement(A, 2, 1, &a);
		a.real = -41; a.imag = 0; matrix_setElement(A, 2, 2, &a);

		matrix_printf(A);

		ho = householder_construct(3,3);

		householder_process(ho, A, Q);

		printf("\n");
		matrix_printf(Q);

		matrix_mul(QA, Q, A);
		
		printf("\n");
		matrix_printf(QA);

		householder_destroy(ho);

		matrix_destroy(A);

		return 0;

	}
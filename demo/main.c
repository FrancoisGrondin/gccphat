
	#include <gccphat.h>

	int main(int argc, char * argv[]) {

		matrix_obj * A;
		matrix_obj * V;
		matrix_obj * D;
		scalar_struct a;
		eig_obj * eig;

		A = matrix_construct(3,3);
		V = matrix_construct(3,3);
		D = matrix_construct(3,3);

		a.real = +1;   a.imag = 0;   matrix_setElement(A, 0, 0, &a);
		a.real = +2;   a.imag = 0;  matrix_setElement(A, 0, 1, &a);
		a.real = -2;   a.imag = 0;   matrix_setElement(A, 0, 2, &a);
		a.real = +2;   a.imag = 0;  matrix_setElement(A, 1, 0, &a);
		a.real = +3;   a.imag = 0;   matrix_setElement(A, 1, 1, &a);
		a.real = +4;   a.imag = 0;   matrix_setElement(A, 1, 2, &a);
		a.real = -2;   a.imag = 0;  matrix_setElement(A, 2, 0, &a);
		a.real = +4;   a.imag = 0;   matrix_setElement(A, 2, 1, &a);
		a.real = +5;   a.imag = 0;   matrix_setElement(A, 2, 2, &a);

		eig = eig_construct(3);

		printf("\nA = \n");
		matrix_printf(A);

		eig_process(eig, A, V, D);

		eig_destroy(eig);

		matrix_destroy(A);

		return 0;

	}
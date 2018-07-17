
	#include <gccphat.h>

	int main(int argc, char * argv[]) {

		matrix_obj * A;
		matrix_obj * AT;
		matrix_obj * Q;
		matrix_obj * R;
		scalar_struct a;
		qr_obj * qr;

		A = matrix_construct(4,3);
		AT = matrix_construct(3,4);
		Q = matrix_construct(3,3);
		R = matrix_construct(3,4);

		qr = qr_construct(3,4);

		a.real = 5;   a.imag = 0; matrix_setElement(A, 0, 0, &a);
		a.real = 10;  a.imag = 0; matrix_setElement(A, 0, 1, &a);
		a.real = 2;   a.imag = 0; matrix_setElement(A, 0, 2, &a);
		a.real = 5;   a.imag = 0; matrix_setElement(A, 1, 0, &a);
		a.real = 7;   a.imag = 0; matrix_setElement(A, 1, 1, &a);
		a.real = 2;   a.imag = 0; matrix_setElement(A, 1, 2, &a);
		a.real = 5;   a.imag = 0; matrix_setElement(A, 2, 0, &a);
		a.real = 1;   a.imag = 0; matrix_setElement(A, 2, 1, &a);
		a.real = 6;   a.imag = 0; matrix_setElement(A, 2, 2, &a);
		a.real = 3;   a.imag = 0; matrix_setElement(A, 3, 0, &a);
		a.real = 2;   a.imag = 0; matrix_setElement(A, 3, 1, &a);
		a.real = 9;   a.imag = 0; matrix_setElement(A, 3, 2, &a);

		matrix_conj(AT,A);

		printf("\nA = \n");
		matrix_printf(A);
		printf("\nAT = \n");
		matrix_printf(AT);

		qr_process(qr, AT, Q, R);

		printf("\nQ = \n");
		matrix_printf(Q);
		printf("\nR =\n");
		matrix_printf(R);

		matrix_destroy(A);
		matrix_destroy(AT);
		matrix_destroy(Q);
		matrix_destroy(R);

		qr_destroy(qr);

		return 0;

	}
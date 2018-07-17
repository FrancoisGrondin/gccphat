
	#include <gccphat.h>

	int main(int argc, char * argv[]) {

		matrix_obj * A;
		matrix_obj * Q;
		matrix_obj * R;
		scalar_struct a;
		qr_obj * qr;

		A = matrix_construct(3,3);
		Q = matrix_construct(3,3);
		R = matrix_construct(3,3);

		qr = qr_construct(3,3);

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

		qr_process(qr, A, Q, R);

		printf("\n");
		matrix_printf(Q);
		printf("\n");
		matrix_printf(R);

		matrix_destroy(A);
		matrix_destroy(Q);
		matrix_destroy(R);

		qr_destroy(qr);

		return 0;

	}
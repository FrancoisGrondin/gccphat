
	#include <gccphat.h>

	int main(int argc, char * argv[]) {

		matrix_obj * A;
		matrix_obj * V;
		matrix_obj * D;
		scalar_struct a;
		eig_obj * eig;
		matrix_obj * Q;
		matrix_obj * R;

		//qr_obj * qr;

		A = matrix_construct(3,3);
		V = matrix_construct(3,3);
		D = matrix_construct(3,3);

		Q = matrix_construct(3,3);
		R = matrix_construct(3,3);

		//qr = qr_construct(3,3);

		
		a.real = +1;   a.imag = 0;   matrix_setElement(A, 0, 0, &a);
		a.real = +2;   a.imag = 0;  matrix_setElement(A, 0, 1, &a);
		a.real = -2;   a.imag = 0;   matrix_setElement(A, 0, 2, &a);
		a.real = +2;   a.imag = 0;  matrix_setElement(A, 1, 0, &a);
		a.real = +3;   a.imag = 0;   matrix_setElement(A, 1, 1, &a);
		a.real = +4;   a.imag = 0;   matrix_setElement(A, 1, 2, &a);
		a.real = -2;   a.imag = 0;  matrix_setElement(A, 2, 0, &a);
		a.real = +4;   a.imag = 0;   matrix_setElement(A, 2, 1, &a);
		a.real = +5;   a.imag = 0;   matrix_setElement(A, 2, 2, &a);

		/*
		a.imag = 0.0f;
		a.real = +1.889E+00; matrix_setElement(A, 0, 0, &a);
		a.real = +1.238E-01; matrix_setElement(A, 0, 1, &a);
		a.real = -2.682E+00; matrix_setElement(A, 0, 2, &a);
		a.real = +1.238E-01; matrix_setElement(A, 1, 0, &a);
		a.real = +6.862E+00; matrix_setElement(A, 1, 1, &a);
		a.real = +2.989E+00; matrix_setElement(A, 1, 2, &a);
		a.real = -2.682E+00; matrix_setElement(A, 2, 0, &a);
		a.real = +2.989E+00; matrix_setElement(A, 2, 1, &a);
		a.real = +2.490E-01; matrix_setElement(A, 2, 2, &a);
		
		qr_process(qr, A, Q, R);
		qr_process(qr, A, Q, R);*/

		eig = eig_construct(3);

		eig_process(eig, A, V, D);

		printf("A = \n");
		matrix_printf(A);
		printf("V = \n");
		matrix_printf(V);
		printf("D = \n");
		matrix_printf(D);

		eig_destroy(eig);

		matrix_destroy(A);
		matrix_destroy(V);
		matrix_destroy(D);
		//matrix_destroy(Q);
		//matrix_destroy(R);
		//qr_destroy(qr);

		return 0;

	}
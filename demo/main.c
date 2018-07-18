
	#include <gccphat.h>

	int main(int argc, char * argv[]) {

		matrix_obj * A;
		matrix_obj * U;
		matrix_obj * S;
		matrix_obj * V;

		matrix_obj * US;
		matrix_obj * VT;
		matrix_obj * USVT;

		scalar_struct a;

		svd_obj * svd;

		A = matrix_construct(3,2);
		U = matrix_construct(3,3);
		S = matrix_construct(3,2);
		V = matrix_construct(2,2);

		US = matrix_construct(3,2);
		VT = matrix_construct(2,2);
		USVT = matrix_construct(3,2);
		
		a.real = +1;   a.imag = 0;   matrix_setElement(A, 0, 0, &a);
		a.real = +2;   a.imag = 0;  matrix_setElement(A, 0, 1, &a);
		a.real = +3;   a.imag = 0;  matrix_setElement(A, 1, 0, &a);
		a.real = +4;   a.imag = 0;   matrix_setElement(A, 1, 1, &a);
		a.real = +5;   a.imag = 0;   matrix_setElement(A, 2, 0, &a);
		a.real = +6;   a.imag = 0;   matrix_setElement(A, 2, 1, &a);

		svd = svd_construct(3, 2);

		svd_process(svd, A, U, S, V);

		printf("A: \n");
		matrix_printf(A);
		printf("\n");

		printf("U: \n");
		matrix_printf(U);
		printf("\n");

		printf("S: \n");
		matrix_printf(S);
		printf("\n");

		printf("V: \n");
		matrix_printf(V);
		printf("\n");

		matrix_mul(US, U, S);
		matrix_conj(VT, V);
		matrix_mul(USVT, US, VT);

		printf("US: \n");
		matrix_printf(US);
		printf("\n");

		printf("VT: \n");
		matrix_printf(VT);
		printf("\n");


		printf("USVT: \n");
		matrix_printf(USVT);
		printf("\n");

		matrix_destroy(A);
		matrix_destroy(U);
		matrix_destroy(S);
		matrix_destroy(V);

		matrix_destroy(US);
		matrix_destroy(VT);
		matrix_destroy(USVT);

		svd_destroy(svd);

		return 0;

	}
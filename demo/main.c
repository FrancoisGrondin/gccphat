
	#include <gccphat.h>

	int main(int argc, char * argv[]) {

		matrix_obj * A;
		matrix_obj * B;
		matrix_obj * C;
		unsigned int index;

		A = matrix_construct(4,3);
		B = matrix_construct(3,4);
		C = matrix_construct(4,4);

		for (index = 0; index < 12; index++) {

			A->real[index] = (float) index;
			A->imag[index] = (float) (index+100);

			B->real[index] = (float) (index*2);
			B->imag[index] = (float) (index+50);

		}

		matrix_printf(A);
		printf("\n");
		matrix_printf(B);
		printf("\n");

		matrix_mul(C, A, B);

		matrix_printf(C);
		printf("\n");

		matrix_destroy(A);
		matrix_destroy(B);

		return 0;

	}
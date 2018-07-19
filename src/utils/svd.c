
    #include <gccphat/utils/svd.h>

	svd_obj * svd_construct(void) {

		svd_obj * obj;

		obj = (svd_obj *) malloc(sizeof(svd_obj));

		return obj;

	}

	void svd_destroy(svd_obj * obj) {

		free((void *) obj);

	}

	int svd_process(svd_obj * obj, const matrix_obj * A, matrix_obj * U, matrix_obj * S, matrix_obj * V) {

		unsigned int M, N;
		unsigned int i, j, k;
		float alpha, beta, gamma_real, gamma_imag;
		float u_ki_real, u_ki_imag;
		float u_kj_real, u_kj_imag;

		M = A->M;
		N = A->N;

		if (A->M != M) { return -1; }
		if (A->N != N) { return -1; }
		if (U->M != M) { return -1; }
		if (U->N != N) { return -1; }
		if (S->M != N) { return -1; }
		if (S->N != N) { return -1; }
		if (V->M != N) { return -1; }
		if (V->N != N) { return -1; }

		matrix_copy(U, A);

		for (i = 0; i < N; i++) {

			for (j = (i+1); j < N; j++) {

				alpha = 0.0f;
				beta = 0.0f;
				gamma_real = 0.0f;
				gamma_imag = 0.0f;

				for (k = 0; k < M; k++) {

					u_ki_real = matrix_getR(U, k, i);
					u_ki_imag = matrix_getI(U, k, i);

					u_kj_real = matrix_getR(U, k, j);
					u_kj_imag = matrix_getI(U, k, j);

					alpha += u_ki_real * u_ki_real + u_ki_imag * u_ki_imag;
					beta += u_kj_real * u_kj_real + u_kj_imag * u_kj_imag;
					gamma_real += u_ki_real * u_kj_real - u_ki_imag * u_kj_imag;
					gamma_imag += u_ki_real * u_kj_imag + u_ki_imag * u_kj_real;

				}

			}

		}

		return 0;

	}
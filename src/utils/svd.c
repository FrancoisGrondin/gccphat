
    #include <gccphat/utils/svd.h>

	svd_obj * svd_construct(const unsigned int M, const unsigned int N) {

		svd_obj * obj;

		obj = (svd_obj *) malloc(sizeof(svd_obj));

		obj->M = M;
		obj->N = N;

		obj->A = matrix_construct(M, N);
		obj->AT = matrix_construct(N, M);
		obj->ATA = matrix_construct(N, N);
		obj->AAT = matrix_construct(M, M);
		obj->D1 = matrix_construct(M, M);
		obj->V1 = matrix_construct(M, M);
		obj->D2 = matrix_construct(N, N);
		obj->V2 = matrix_construct(N, N);
		obj->U = matrix_construct(M, M);
		obj->S = matrix_construct(M, N);
		obj->V = matrix_construct(N, N);

		obj->eigM = eig_construct(M);
		obj->eigN = eig_construct(N);

		return obj;

	}

	void svd_destroy(svd_obj * obj) {

		matrix_destroy(obj->A);
		matrix_destroy(obj->AT);
		matrix_destroy(obj->ATA);
		matrix_destroy(obj->AAT);
		matrix_destroy(obj->D1);
		matrix_destroy(obj->V1);
		matrix_destroy(obj->D2);
		matrix_destroy(obj->V2);
		matrix_destroy(obj->U);
		matrix_destroy(obj->S);
		matrix_destroy(obj->V);

		eig_destroy(obj->eigM);
		eig_destroy(obj->eigN);

		free((void *) obj);

	}

	int svd_process(svd_obj * obj, const matrix_obj * A, matrix_obj * U, matrix_obj * S, matrix_obj * V) {

		unsigned int T;
		unsigned int t;
		scalar_struct lambda1;
		scalar_struct lambda2;
		scalar_struct lambda12;
		float lambda;

		if (obj->M != A->nRows) { return -1; }
		if (obj->N != A->nCols) { return -1; }
		if (obj->M != U->nRows) { return -1; }
		if (obj->M != U->nCols) { return -1; }
		if (obj->M != S->nRows) { return -1; }
		if (obj->N != S->nCols) { return -1; }
		if (obj->N != V->nRows) { return -1; }
		if (obj->N != V->nCols) { return -1; }

		if (obj->M < obj->N) { T = obj->M; }
		else { T = obj->N; }

		matrix_copy(obj->A, A);
		matrix_conj(obj->AT, A);

		matrix_mul(obj->ATA, obj->AT, obj->A);
		matrix_mul(obj->AAT, obj->A, obj->AT);

		eig_process(obj->eigM, obj->AAT, obj->V1, obj->D1);
		eig_process(obj->eigN, obj->ATA, obj->V2, obj->D2);

		for (t = 0; t < T; t++) {

			matrix_getElement(obj->D1, t, t, &lambda1);
			matrix_getElement(obj->D2, t, t, &lambda2);

			lambda = sqrtf((lambda1.real + lambda2.real) / 2.0f);

			lambda12.real = lambda;
			lambda12.imag = 0.0f;

			matrix_setElement(obj->S, t, t, &lambda12);

		}

		matrix_copy(obj->U, obj->V1);
		matrix_copy(obj->V, obj->V2);

		matrix_copy(U, obj->U);
		matrix_copy(S, obj->S);
		matrix_copy(V, obj->V);

		return 0;

	}
    
    #include <gccphat/utils/eig.h>

    eig_obj * eig_construct(const unsigned int M) {

    	eig_obj * obj;

    	obj = (eig_obj *) malloc(sizeof(eig_obj));

    	obj->M = M;

        obj->Q = matrix_construct(M, M);
        obj->R = matrix_construct(M, M);

        obj->QT = matrix_construct(M, M);
        obj->A = matrix_construct(M, M);
        obj->QTA = matrix_construct(M, M);
        obj->QTV = matrix_construct(M, M);

        obj->I = matrix_construct(M, M);
        obj->D = matrix_construct(M, M);
        obj->V = matrix_construct(M, M);

        obj->v = vector_construct(M);

        obj->qr = qr_construct(M, M);

        obj->lambdas = (float *) malloc(sizeof(float) * M);
        obj->indexes = (unsigned int *) malloc(sizeof(unsigned int) * M);

    	return obj;

    }

    void eig_destroy(eig_obj * obj) {

    	matrix_destroy(obj->Q);
    	matrix_destroy(obj->R);

    	matrix_destroy(obj->QT);
    	matrix_destroy(obj->A);
    	matrix_destroy(obj->QTA);
        matrix_destroy(obj->QTV);

        matrix_destroy(obj->I);
        matrix_destroy(obj->D);
        matrix_destroy(obj->V);

        vector_destroy(obj->v);

    	qr_destroy(obj->qr);

        free((void *) obj->lambdas);
        free((void *) obj->indexes);

    	free((void *) obj);

    }

    int eig_process(eig_obj * obj, const matrix_obj * A, matrix_obj * V, matrix_obj * D) {

    	char symm;
    	char tril;

    	unsigned int k;
        const unsigned int K = 1000;

        unsigned int d;
        scalar_struct lambda;

        unsigned int d1, d2;
        float l;
        unsigned int i;

    	matrix_symm(A, &symm); if (symm == 0) { return -1; }
    	if (A->nRows != obj->M) { return -1; }
    	if (A->nCols != obj->M) { return -1; }
    	if (V->nRows != obj->M) { return -1; }
    	if (V->nCols != obj->M) { return -1; }
    	if (D->nRows != obj->M) { return -1; }
    	if (D->nCols != obj->M) { return -1; }

        matrix_identity(obj->I);
    	matrix_copy(obj->A, A);
        matrix_identity(obj->V);

    	for (k = 0; k < K; k++) {

    		matrix_tril(obj->A, &tril);

    		if (tril == 1) { break; }

    		qr_process(obj->qr, obj->A, obj->Q, obj->R);
    		    		
    		matrix_conj(obj->QT, obj->Q);
    		matrix_mul(obj->QTA, obj->QT, obj->A);
    		matrix_mul(obj->A, obj->QTA, obj->Q);

            matrix_mul(obj->QTV, obj->QT, obj->V);
            matrix_copy(obj->V, obj->QTV);
    		
    	}

        matrix_had(D, obj->A, obj->I);
        matrix_real(obj->D, D);

        matrix_copy(obj->QTV, obj->V);
        matrix_conj(obj->V, obj->QTV);

        for (d = 0; d < obj->M; d++) {

            matrix_getElement(obj->D, d, d, &lambda);
            obj->lambdas[d] = lambda.real;
            obj->indexes[d] = d;

        }

        for (d1 = 0; d1 < obj->M; d1++) {

            for (d2 = d1; d2 < obj->M; d2++) {

                if (obj->lambdas[d1] < obj->lambdas[d2]) {

                    l = obj->lambdas[d1];
                    obj->lambdas[d1] = obj->lambdas[d2];
                    obj->lambdas[d2] = l;

                    i = obj->indexes[d1];
                    obj->indexes[d1] = obj->indexes[d2];
                    obj->indexes[d2] = i;

                }

            }

        }

        for (d = 0; d < obj->M; d++) {

            lambda.real = obj->lambdas[d];
            lambda.imag = 0.0f;
            matrix_setElement(D, d, d, &lambda);

            matrix_getCol(obj->V, obj->indexes[d], obj->v);
            matrix_setCol(V, d, obj->v);

        }

    	return 0;

    }
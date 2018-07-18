    
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

        obj->qr = qr_construct(M, M);

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

    	qr_destroy(obj->qr);

    	free((void *) obj);

    }

    int eig_process(eig_obj * obj, const matrix_obj * A, matrix_obj * V, matrix_obj * D) {

    	char symm;
    	char tril;

    	unsigned int k = 0;
        const unsigned int K = 1000;

    	matrix_symm(A, &symm); if (symm == 0) { return -1; }
    	if (A->nRows != obj->M) { return -1; }
    	if (A->nCols != obj->M) { return -1; }
    	if (V->nRows != obj->M) { return -1; }
    	if (V->nCols != obj->M) { return -1; }
    	if (D->nRows != obj->M) { return -1; }
    	if (D->nCols != obj->M) { return -1; }

        matrix_identity(obj->I);
    	matrix_copy(obj->A, A);
        matrix_identity(V);

    	for (k = 0; k < K; k++) {

    		matrix_tril(obj->A, &tril);

    		if (tril == 1) { break; }

    		qr_process(obj->qr, obj->A, obj->Q, obj->R);
    		    		
    		matrix_conj(obj->QT, obj->Q);
    		matrix_mul(obj->QTA, obj->QT, obj->A);
    		matrix_mul(obj->A, obj->QTA, obj->Q);

            matrix_mul(obj->QTV, obj->QT, V);
            matrix_copy(V, obj->QTV);
    		
    	}

        matrix_had(obj->D, obj->A, obj->I);
        matrix_real(D, obj->D);

        matrix_copy(obj->QTV, V);
        matrix_conj(V, obj->QTV);

    	return 0;

    }
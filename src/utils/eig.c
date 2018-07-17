    
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

        obj->qr = qr_construct(M, M);

    	return obj;

    }

    void eig_destroy(eig_obj * obj) {

    	matrix_destroy(obj->Q);
    	matrix_destroy(obj->R);

    	matrix_destroy(obj->QT);
    	matrix_destroy(obj->A);
    	matrix_destroy(obj->QTA);

    	qr_destroy(obj->qr);

    	free((void *) obj);

    }

    int eig_process(eig_obj * obj, const matrix_obj * A, matrix_obj * V, matrix_obj * D) {

    	char symm;
    	char tril;

    	unsigned int k = 0;

    	matrix_symm(A, &symm); if (symm == 0) { return -1; }
    	if (A->nRows != obj->M) { return -1; }
    	if (A->nCols != obj->M) { return -1; }
    	if (V->nRows != obj->M) { return -1; }
    	if (V->nCols != obj->M) { return -1; }
    	if (D->nRows != obj->M) { return -1; }
    	if (D->nCols != obj->M) { return -1; }

    	matrix_copy(obj->A, A);

    	for (k = 0; k < 2; k++) {

    		//matrix_tril(obj->A, &tril);

    		//if (tril == 1) { break; }

    		qr_process(obj->qr, obj->A, obj->Q, obj->R);
    		
    		printf("A_%u = \n", k);
    		matrix_printf(obj->A);
    		printf("Q_%u = \n", k);
    		matrix_printf(obj->Q);
    		printf("R_%u = \n", k);
    		matrix_printf(obj->R);
    		printf("\n");
    		
    		matrix_conj(obj->QT, obj->Q);
    		matrix_mul(obj->QTA, obj->QT, obj->A);
    		matrix_mul(obj->A, obj->QTA, obj->Q);
    		
    	}

    	return 0;

    }

    #include <gccphat/utils/qr.h>

    qr_obj * qr_construct(const unsigned int M, const unsigned int N) {

        qr_obj * obj;
        unsigned int t;
        unsigned int T;

        obj = (qr_obj *) malloc(sizeof(qr_obj));

        if (M > N) { T = M; } else { T = N; }

        obj->M = M;
        obj->N = N;
        obj->T = T;

        obj->Qs = (matrix_obj **) malloc(sizeof(matrix_obj *) * T);
        obj->Qps = (matrix_obj **) malloc(sizeof(matrix_obj *) * T);
        obj->As = (matrix_obj **) malloc(sizeof(matrix_obj *) * T);
        obj->Aps = (matrix_obj **) malloc(sizeof(matrix_obj *) * T);
        obj->householders = (householder_obj **) malloc(sizeof(householder_obj *) * T);

        obj->QT = matrix_construct(M, M);
        obj->Qp = matrix_construct(M, M);
        obj->Rp = matrix_construct(M, N);

        for (t = 0; t < T; t++) {

            obj->Qs[t] = matrix_construct(M-t,M-t);
            obj->Qps[t] = matrix_construct(M, M);
            obj->As[t] = matrix_construct(M-t,N-t);
            obj->Aps[t] = matrix_construct(M-t,N-t);
            obj->householders[t] = householder_construct(M-t,N-t);

        }

        return obj;

    }

    void qr_destroy(qr_obj * obj) {

        unsigned int t;
        unsigned int T;

        T = obj->T;

        for (t = 0; t < T; t++) {

            matrix_destroy(obj->Qs[t]);
            matrix_destroy(obj->Qps[t]);
            matrix_destroy(obj->As[t]);
            matrix_destroy(obj->Aps[t]);
            householder_destroy(obj->householders[t]);

        }

        free((void *) obj->Qs);
        free((void *) obj->Qps);
        free((void *) obj->As);
        free((void *) obj->Aps);
        free((void *) obj->householders);

        matrix_destroy(obj->QT);
        matrix_destroy(obj->Qp);
        matrix_destroy(obj->Rp);

        free((void *) obj);

    }

    int qr_process(qr_obj * obj, const matrix_obj * A, matrix_obj * Q, matrix_obj * R) {

        unsigned int M;
        unsigned int N;
        unsigned int T;

        unsigned int t;

        if (A->nRows != obj->M) { return -1; }
        if (A->nCols != obj->N) { return -1; }
        if (Q->nRows != obj->M) { return -1; }
        if (Q->nCols != obj->M) { return -1; }
        if (R->nRows != obj->M) { return -1; }
        if (R->nCols != obj->N) { return -1; }

        M = obj->M;
        N = obj->N;
        T = obj->T;

        for (t = 0; t < T; t++) {

            matrix_identity(obj->Qps[t]);

        }

        matrix_copy(obj->As[0], A);

        printf("A0 = \n");
        matrix_printf(obj->As[0]);

        for (t = 0; t < T; t++) {

            householder_process(obj->householders[t], obj->As[t], obj->Qs[t]);

            printf("Qs[%u] = \n", t);
            matrix_printf(obj->Qs[t]);

            matrix_setSubMatrix(obj->Qps[t], t, t, obj->Qs[t]);

            matrix_mul(obj->Aps[t], obj->Qs[t], obj->As[t]);
            printf("As[%u] = \n", t);
            matrix_printf(obj->Aps[t]);

            if ((t+1) < T) {

                matrix_getSubMatrix(obj->Aps[t], 1, 1, obj->As[t+1]);

            printf("As_sub = \n");
            matrix_printf(obj->As[t+1]);


            }


        }

        matrix_identity(Q);
        matrix_copy(R, A);

            printf("Q = \n");
            matrix_printf(Q);


        for (t = 0; t < T; t++) {

            printf("Qps[%u] = \n",t);
            matrix_printf(obj->Qps[t]);

            matrix_conj(obj->QT, obj->Qps[t]);
            printf("QT = \n");
            matrix_printf(obj->QT);
            matrix_mul(obj->Qp, Q, obj->QT);
            matrix_copy(Q, obj->Qp);
            printf("Q = \n");
            matrix_printf(Q);

            matrix_mul(obj->Rp, obj->Qps[t], R);
            matrix_copy(R, obj->Rp);

        }



        return 0;

    }




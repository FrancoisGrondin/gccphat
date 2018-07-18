
    #include <gccphat/utils/householder.h>

    householder_obj * householder_construct(const unsigned int M, const unsigned int N) {

        householder_obj * obj;
        scalar_struct one;

        obj = (householder_obj *) malloc(sizeof(householder_obj));

        obj->M = M;
        obj->N = N;

        obj->e1 = vector_construct(M);
        obj->alpha_e1 = vector_construct(M);
        obj->x = vector_construct(M);
        obj->u = vector_construct(M);
        obj->v = vector_construct(M);

        obj->V = matrix_construct(M,1);
        obj->VH = matrix_construct(1,M);
        obj->VVH = matrix_construct(M,M);
        obj->twoVVH = matrix_construct(M,M);
        obj->I = matrix_construct(M,M);

        one.real = 1.0f;
        one.imag = 0.0f;
        vector_set(obj->e1, 0, &one);
        matrix_identity(obj->I);

        return obj;

    }

    void householder_destroy(householder_obj * obj) {

        vector_destroy(obj->e1);
        vector_destroy(obj->alpha_e1);
        vector_destroy(obj->x);
        vector_destroy(obj->u);
        vector_destroy(obj->v);

        matrix_destroy(obj->V);
        matrix_destroy(obj->VH);
        matrix_destroy(obj->VVH);
        matrix_destroy(obj->twoVVH);
        matrix_destroy(obj->I);

    }

    int householder_process(householder_obj * obj, const matrix_obj * A, matrix_obj * Q) {

        scalar_struct x1;
        float Xnorm;
        scalar_struct alpha;
        scalar_struct two;
        scalar_struct q;

        if (A->nRows != obj->M) { return -1; }
        if (A->nCols != obj->N) { return -1; }
        if (Q->nRows != obj->M) { return -1; }
        if (Q->nCols != obj->M) { return -1; }

        if (obj->M > 1) {

            matrix_getCol(A, 0, obj->x);
            vector_norm(&Xnorm, obj->x);

            vector_get(obj->x, 0, &x1);
            alpha = scalar_setPhasor(Xnorm, scalar_getPhase(x1));

            vector_scale(obj->alpha_e1, obj->e1, &alpha);

            vector_sub(obj->u, obj->x, obj->alpha_e1);

            vector_normalize(obj->v, obj->u);

            two.real = 2.0f;
            two.imag = 0.0f;
            
            matrix_setCol(obj->V, 0, obj->v);
            matrix_conj(obj->VH, obj->V);
            matrix_mul(obj->VVH, obj->V, obj->VH);
            matrix_scale(obj->twoVVH, obj->VVH, &two);

            matrix_sub(Q, obj->I, obj->twoVVH);

        }
        else {

            q.real = 1.0f;
            q.imag = 0.0f;

            matrix_setElement(Q, 0, 0, &q);

        }

        return 0;

    }
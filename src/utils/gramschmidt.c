    
    #include <gccphat/utils/gramschmidt.h>

    gramschmidt_obj * gramschmidt_construct(const unsigned int N) {

        gramschmidt_obj * obj;
        unsigned int n;

        obj = (gramschmidt_obj *) malloc(sizeof(gramschmidt_obj));

        obj->N = N;

        obj->as = (vector_obj **) malloc(sizeof(vector_obj *) * N);
        obj->us = (vector_obj **) malloc(sizeof(vector_obj *) * N);
        obj->es = (vector_obj **) malloc(sizeof(vector_obj *) * N);

        for (n = 0; n < N; n++) {

            obj->as[n] = vector_construct(N);
            obj->us[n] = vector_construct(N);
            obj->es[n] = vector_construct(N);

        }

        obj->u1 = vector_construct(N);
        obj->u2 = vector_construct(N);

        return obj;

    }

    void gramschmidt_destroy(gramschmidt_obj * obj) {

        unsigned int n;

        for (n = 0; n < obj->N; n++) {

            vector_destroy(obj->as[n]);
            vector_destroy(obj->us[n]);
            vector_destroy(obj->es[n]);

        }

        vector_destroy(obj->u1);
        vector_destroy(obj->u2);

        free((void *) obj);

    }

    int gramschmidt_process(gramschmidt_obj * obj, const matrix_obj * A, matrix_obj * E) {

        unsigned int n;
        unsigned int k;
        float dot_a_u_real;
        float dot_a_u_imag;
        float norm_u;

        if (A->nRows != obj->N) { return -1; }
        if (A->nCols != obj->N) { return -1; }
        if (E->nRows != obj->N) { return -1; }
        if (E->nCols != obj->N) { return -1; }        

        matrix_zero(E);

        for (n = 0; n < obj->N; n++) {

            matrix_getCol(A, n, obj->as[n]);

        }

        for (n = 0; n < obj->N; n++) {

            vector_copy(obj->us[n], obj->as[n]);

            for (k = 0; k < obj->N; k++) {

                vector_dot(obj->as[n], obj->us[k], &dot_a_u_real, &dot_a_u_imag);
                vector_norm(obj->us[k], &norm_u);

                vector_scale(obj->u1, obj->us[k], dot_a_u_real / norm_u, dot_a_u_imag / norm_u);
                vector_sub(obj->u2, obj->us[n], obj->u1);
                vector_copy(obj->us[n], obj->u2);

            }

            vector_norm(obj->us[n], &norm_u);
            vector_scale(obj->es[n], obj->us[n], 1.0/norm_u, 0.0f);

        }

        return 0;

    }

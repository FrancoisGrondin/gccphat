    
    #include <gccphat/utils/gramschmidt.h>

    gramschmidt_obj * gramschmidt_construct(const unsigned int N, const unsigned int M) {

        gramschmidt_obj * obj;
        unsigned int m;

        obj = (gramschmidt_obj *) malloc(sizeof(gramschmidt_obj));

        obj->N = N;
        obj->M = M;

        obj->as = (vector_obj **) malloc(sizeof(vector_obj *) * M);
        obj->us = (vector_obj **) malloc(sizeof(vector_obj *) * M);
        obj->es = (vector_obj **) malloc(sizeof(vector_obj *) * M);

        for (m = 0; m < M; m++) {

            obj->as[m] = vector_construct(N);
            obj->us[m] = vector_construct(N);
            obj->es[m] = vector_construct(N);

        }

        obj->u1 = vector_construct(N);
        obj->u2 = vector_construct(N);

        return obj;

    }

    void gramschmidt_destroy(gramschmidt_obj * obj) {

        unsigned int m;

        for (m = 0; m < obj->M; m++) {

            vector_destroy(obj->as[m]);
            vector_destroy(obj->us[m]);
            vector_destroy(obj->es[m]);

        }

        vector_destroy(obj->u1);
        vector_destroy(obj->u2);

        free((void *) obj);

    }

    int gramschmidt_process(gramschmidt_obj * obj, const matrix_obj * A, matrix_obj * E) {

        unsigned int m;
        unsigned int k;
        scalar_struct dot_a_u;
        scalar_struct dot_a_u_conj;
        scalar_struct dot_u_u;
        scalar_struct dot_a_u_conj_D_dot_u_u;
        scalar_struct norm_u;
        scalar_struct norm_u_inv;

        if (A->nRows != obj->N) { return -1; }
        if (A->nCols != obj->M) { return -1; }
        if (E->nRows != obj->N) { return -1; }
        if (E->nCols != obj->M) { return -1; }        

        matrix_zero(E);

        for (m = 0; m < obj->M; m++) {

            matrix_getCol(A, m, obj->as[m]);

            printf("a%u = ",(m+1));
            vector_printf(obj->as[m]);
            printf("\n");

        }

        for (m = 0; m < obj->M; m++) {

            vector_copy(obj->us[m], obj->as[m]);

            for (k = 0; k < m; k++) {

                vector_dot(&dot_a_u, obj->us[k], obj->as[m]);
                dot_a_u_conj = scalar_conj(dot_a_u);
                vector_dot(&dot_u_u, obj->us[k], obj->us[k]);
                dot_a_u_conj_D_dot_u_u = scalar_div(dot_a_u_conj, dot_u_u);             
                vector_scale(obj->u1, obj->us[k], &dot_a_u_conj_D_dot_u_u);

                vector_sub(obj->u2, obj->us[m], obj->u1);
                vector_copy(obj->us[m], obj->u2);

            }

            vector_norm(&norm_u, obj->us[m]);
            norm_u_inv = scalar_inv(norm_u);

            vector_scale(obj->es[m], obj->us[m], &norm_u_inv);

        }

        
        for (m = 0; m < obj->M; m++) {

            matrix_setCol(E, m, obj->es[m]);

        }

        return 0;

    }

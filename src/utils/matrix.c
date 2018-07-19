
    #include <gccphat/utils/matrix.h>

    matrix_obj * matrix_construct(const unsigned int M, const unsigned int N) {

        matrix_obj * obj;

        obj = (matrix_obj *) malloc(sizeof(matrix_obj));

        obj->M = M;
        obj->N = N;
        obj->array = (float *) malloc(sizeof(float) * M * N * 2);
        memset(obj->array, 0x00, sizeof(float) * M * N * 2);

        return obj;

    }

    void matrix_destroy(matrix_obj * obj) {

        free((void *) (obj->array));
        free((void *) obj);

    }

    float matrix_getR(const matrix_obj * obj, const unsigned int m, const unsigned int n) {

        return obj->array[(m * obj->N + n) * 2 + 0];

    }

    float matrix_getI(const matrix_obj * obj, const unsigned int m, const unsigned int n) {

        return obj->array[(m * obj->N + n) * 2 + 1];

    }

    void matrix_setR(const matrix_obj * obj, const unsigned int m, const unsigned int n, const float real) {

        obj->array[(m * obj->N + n) * 2 + 0] = real;

    }

    void matrix_setI(const matrix_obj * obj, const unsigned int m, const unsigned int n, const float imag) {

        obj->array[(m * obj->N + n) * 2 + 1] = imag;

    }

    void matrix_copy(matrix_obj * dest, const matrix_obj * src) {

        if (dest->M != src->M) { return; }
        if (dest->N != src->N) { return; }

        memcpy(dest->array, src->array, sizeof(float) * src->M * src->N * 2);

    }

    void matrix_printf(const matrix_obj * obj) {

        unsigned int m, n;

        printf("\n");

        for (m = 0; m < obj->M; m++) {

            for (n = 0; n < obj->N; n++) {

                printf("( %+1.3f, %+1.3fj ) ", obj->array[(m * obj->N + n) * 2 + 0], obj->array[(m * obj->N + n) * 2 + 1]);

            }

            printf("\n");

        }

    }
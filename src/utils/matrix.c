
    #include <gccphat/utils/matrix.h>

    matrix_obj * matrix_construct(const unsigned int M, const unsigned int N) {

        matrix_obj * obj;

        obj = (matrix_obj *) malloc(sizeof(matrix_obj));

        obj->M = M;
        obj->N = N;
        obj->array = (float *) malloc(sizeof(float) * M * N);
        memset(obj->array, 0x00, sizeof(float) * M * N);

        return obj;

    }

    void matrix_destroy(matrix_obj * obj) {

        free((void *) (obj->array));
        free((void *) obj);

    }

    float matrix_get(const matrix_obj * obj, const unsigned int m, const unsigned int n) {

        return obj->array[m * obj->N + n];

    }

    void matrix_set(const matrix_obj * obj, const unsigned int m, const unsigned int n, const float value) {

        obj->array[m * obj->N + n] = value;

    }

    void matrix_copy(matrix_obj * dest, const matrix_obj * src) {

        if (dest->M != src->M) { return; }
        if (dest->N != src->N) { return; }

        memcpy(dest->array, src->array, sizeof(float) * src->M * src->N);

    }

    void matrix_eye(matrix_obj * obj) {

        unsigned int T;
        unsigned int t;

        if (obj->M > obj->N) { T = obj->N; } else { T = obj->M; }

        memset(obj->array, 0x00, sizeof(float) * obj->M * obj->N);

        for (t = 0; t < T; t++) {

            obj->array[t * obj->M + t] = 1.0f;

        }

    }

    void matrix_zero(matrix_obj * obj) {

        memset(obj->array, 0x00, sizeof(float) * obj->M * obj->N);

    }

    void matrix_printf(const matrix_obj * obj) {

        unsigned int m, n;

        printf("\n");

        for (m = 0; m < obj->M; m++) {

            for (n = 0; n < obj->N; n++) {

                printf("%+1.3f ", obj->array[m * obj->N + n]);

            }

            printf("\n");

        }

    }
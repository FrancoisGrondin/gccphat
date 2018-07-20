
    #include <gccphat_svd/utils/matrix.h>

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

    void matrix_transpose(matrix_obj * dest, const matrix_obj * src) {

        unsigned int m, n;

        if (dest->M != src->N) { return; }
        if (dest->N != src->M) { return; }

        for (m = 0; m < dest->M; m++) {

            for (n = 0; n < dest->N; n++) {

                dest->array[m * dest->N + n] = src->array[n * src->N + m];

            }

        }

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

    void matrix_add(matrix_obj * dest, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int m, n;
        unsigned int M, N;

        if (dest->M != src1->M) { return; }
        if (dest->N != src1->N) { return; }
        if (dest->M != src2->M) { return; }
        if (dest->N != src2->N) { return; }

        M = dest->M;
        N = dest->N;

        for (m = 0; m < M; m++) {

            for (n = 0; n < N; n++) {

                dest->array[m * N + n] = src1->array[m * N + n] + src2->array[m * N + n];

            }

        }

    }

    void matrix_sub(matrix_obj * dest, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int m, n;
        unsigned int M, N;

        if (dest->M != src1->M) { return; }
        if (dest->N != src1->N) { return; }
        if (dest->M != src2->M) { return; }
        if (dest->N != src2->N) { return; }

        M = dest->M;
        N = dest->N;

        for (m = 0; m < M; m++) {

            for (n = 0; n < N; n++) {

                dest->array[m * N + n] = src1->array[m * N + n] - src2->array[m * N + n];

            }

        }

    }

    void matrix_mul(matrix_obj * dest, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int m, n, k;
        unsigned int M, N, K;
        float total;

        if (dest->M != src1->M) { return; }
        if (dest->N != src2->N) { return; }
        if (src1->N != src2->M) { return; }

        M = dest->M;
        N = dest->N;
        K = src1->N;

        for (m = 0; m < M; m++) {

            for (n = 0; n < N; n++) {

                total = 0.0f;

                for (k = 0; k < K; k++) {

                    total += src1->array[m * K + k] * src2->array[k * N + n];

                }

                dest->array[m * N + n] = total;

            }

        }

    }

    void matrix_had(matrix_obj * dest, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int m, n;
        unsigned int M, N;

        if (dest->M != src1->M) { return; }
        if (dest->N != src1->N) { return; }
        if (dest->M != src2->M) { return; }
        if (dest->N != src2->N) { return; }

        M = dest->M;
        N = dest->N;

        for (m = 0; m < M; m++) {

            for (n = 0; n < N; n++) {

                dest->array[m * N + n] = src1->array[m * N + n] * src2->array[m * N + n];

            }

        }

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
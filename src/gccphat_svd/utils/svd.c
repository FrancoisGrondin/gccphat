
    #include <gccphat_svd/utils/svd.h>

    svd_obj * svd_construct(void) {

        svd_obj * obj;

        obj = (svd_obj *) malloc(sizeof(svd_obj));

        return obj;

    }

    void svd_destroy(svd_obj * obj) {

        free((void *) obj);

    }

    int svd_process(svd_obj * obj, const matrix_obj * A, matrix_obj * U, matrix_obj * S, matrix_obj * V) {

        unsigned int M, N;
        unsigned int m, n;
        unsigned int i, j, k;
        float alpha, beta, gamma;
        float u_ki, u_kj;
        float zeta, zeta_sign;
        float t, c, s;
        float v_ki, v_kj;
        float cost, costMax;
        float u_nm;
        float singular;
        float s_ii;
        float s_jj;

        const float epsilon = 1E-5;

        M = A->M;
        N = A->N;

        if (A->M != M) { return -1; }
        if (A->N != N) { return -1; }
        if (U->M != M) { return -1; }
        if (U->N != N) { return -1; }
        if (S->M != N) { return -1; }
        if (S->N != N) { return -1; }
        if (V->M != N) { return -1; }
        if (V->N != N) { return -1; }
        if (M < N) { return -1; }

        matrix_copy(U, A);
        matrix_eye(V);
        matrix_zero(S);
        
        // SVD via 2x2 Jacobian Rotation, until convergence

        do {

            costMax = 0.0f;

            for (i = 0; i < N; i++) {

                for (j = (i+1); j < N; j++) {

                    alpha = 0.0f;
                    beta = 0.0f;
                    gamma = 0.0f;

                    for (k = 0; k < M; k++) {

                        u_ki = matrix_get(U, k, i);
                        u_kj = matrix_get(U, k, j);

                        alpha += u_ki * u_ki;
                        beta += u_kj * u_kj;
                        gamma += u_ki * u_kj;

                    }

                    zeta = (beta-alpha) / (2.0f * gamma);

                    if (zeta > 0.0f) { zeta_sign = 1.0f; }
                    if (zeta == 0.0f) { zeta_sign = 0.0f; }
                    if (zeta < 0.0f) { zeta_sign = -1.0f; }

                    t = zeta_sign / (fabsf(zeta) + sqrtf(1 + zeta*zeta));

                    c = 1.0 / sqrtf(1.0 + t * t);
                    s = c * t;

                    for (k = 0; k < M; k++) {

                        u_ki = matrix_get(U, k, i);
                        u_kj = matrix_get(U, k, j);

                        t = u_ki;

                        u_ki = c * t - s * u_kj;
                        u_kj = s * t + c * u_kj;

                        matrix_set(U, k, i, u_ki);
                        matrix_set(U, k, j, u_kj);

                    }

                    for (k = 0; k < N; k++) {

                        v_ki = matrix_get(V, k, i);
                        v_kj = matrix_get(V, k, j);

                        t = v_ki;

                        v_ki = c * t - s * v_kj;
                        v_kj = s * t + c * v_kj;

                        matrix_set(V, k, i, v_ki);
                        matrix_set(V, k, j, v_kj);

                    }

                    cost = fabsf(gamma) / sqrtf(alpha * beta); 

                    if (cost > costMax) {
                        costMax = cost;
                    }

                }

            } 

        } while (costMax > epsilon);

        // Get singular values for S, and normalize U

        for (n = 0; n < N; n++) {

            singular = 0.0f;

            for (m = 0; m < M; m++) {

                u_nm = matrix_get(U, m, n);
                singular += u_nm * u_nm;

            }

            singular = sqrtf(singular);
            matrix_set(S, n, n, singular);

            for (m = 0; m < M; m++) {

                u_nm = matrix_get(U, m, n);
                u_nm /= singular;
                matrix_set(U, m, n, u_nm);

            }

        }

        // Order from highest singular value to lowest

        for (i = 0; i < N; i++) {

            for (j = i; j < N; j++) {

                s_ii = matrix_get(S, i, i);
                s_jj = matrix_get(S, j, j);

                if (s_ii < s_jj) {

                    matrix_set(S, i, i, s_jj);
                    matrix_set(S, j, j, s_ii);

                    for (k = 0; k < M; k++) {

                        u_ki = matrix_get(U, k, i);
                        u_kj = matrix_get(U, k, j);

                        matrix_set(U, k, i, u_kj);
                        matrix_set(U, k, j, u_ki);                        

                    }

                    for (k = 0; k < N; k++) {

                        v_ki = matrix_get(V, k, i);
                        v_kj = matrix_get(V, k, j);

                        matrix_set(V, k, i, v_kj);
                        matrix_set(V, k, j, v_ki);

                    }

                }

            }

        }

        return 0;

    }
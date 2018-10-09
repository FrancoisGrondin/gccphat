    
    #include <gccphat_svd/utils/gpsvd.h>

    gpsvd_obj * gpsvd_construct(const unsigned int N, const unsigned int fS, const float c, const float d, const unsigned int Q) {

        gpsvd_obj * obj;
        
        float theta, tdoa;
        float w_real, w_imag;
        float g;

        unsigned int K;
        unsigned int k;
        unsigned int q;
        unsigned int m;

        matrix_obj * W_real;
        matrix_obj * W_imag;

        matrix_obj * A_real;
        matrix_obj * A_imag;

        matrix_obj * U_real;
        matrix_obj * S_real;
        matrix_obj * V_real;
        matrix_obj * U_imag;
        matrix_obj * S_imag;
        matrix_obj * V_imag;

        float lambda_real_cumul;
        float lambda_real_total;
        float lambda_imag_cumul;
        float lambda_imag_total;

        unsigned int R_real;
        unsigned int R_imag;
        unsigned int r;

        svd_obj * svd;

        const float epsilon = 1E-5;

        obj = (gpsvd_obj *) malloc(sizeof(gpsvd_obj));

        obj->N = N;
        obj->fS = fS;
        obj->c = c;
        obj->d = d;
        
        K = N/2 + 1;

        obj->K = K;
        obj->Q = Q;
                
        obj->thetas = (float *) malloc(sizeof(float) * Q);
        obj->tdoas = (float *) malloc(sizeof(float) * Q);

        // Sample arc from -pi/2 to pi/2 over Q points
        // Compute corresponding TDOAs on the arc
        
        for (q = 0; q < Q; q++) {

            theta = -1.0f * M_PI_2 + (((float) q) / ((float) (Q-1))) * M_PI;
            obj->thetas[q] = theta;

            tdoa = d * (fS/c) * sin(theta);
            obj->tdoas[q] = tdoa;

        }

        // Generate W matrix, real and imag parts, and decompose in singular values

        W_real = matrix_construct(Q, K);
        W_imag = matrix_construct(Q, K);

        for (q = 0; q < Q; q++) {

            tdoa = obj->tdoas[q];

            for (k = 0; k < K; k++) {

                if ((k == 0) || (k == N/2)) { g = 1; } else { g = 2; }

                w_real = sqrtf(g/((float) N)) * cosf(2.0f * M_PI * ((float) k) * tdoa / ((float) N));
                w_imag = sqrtf(g/((float) N)) * sinf(2.0f * M_PI * ((float) k) * tdoa / ((float) N));

                matrix_set(W_real, q, k, w_real);
                matrix_set(W_imag, q, k, w_imag);

            }

        }

        svd = svd_construct();

        if (Q >= K) {

            A_real = matrix_construct(Q, K);
            A_imag = matrix_construct(Q, K);

            matrix_copy(A_real, W_real);
            matrix_copy(A_imag, W_imag);

            U_real = matrix_construct(Q, K);
            U_imag = matrix_construct(Q, K);
            S_real = matrix_construct(K, K);
            S_imag = matrix_construct(K, K);
            V_real = matrix_construct(K, K);
            V_imag = matrix_construct(K, K);

            svd_process(svd, A_real, U_real, S_real, V_real);
            svd_process(svd, A_imag, U_imag, S_imag, V_imag);

        }
        else {

            A_real = matrix_construct(K, Q);
            A_imag = matrix_construct(K, Q);

            matrix_transpose(A_real, W_real);
            matrix_transpose(A_imag, W_imag);

            U_real = matrix_construct(K, Q);
            U_imag = matrix_construct(K, Q);
            S_real = matrix_construct(Q, Q);
            S_imag = matrix_construct(Q, Q);
            V_real = matrix_construct(Q, Q);
            V_imag = matrix_construct(Q, Q);

            svd_process(svd, A_real, U_real, S_real, V_real);
            svd_process(svd, A_imag, U_imag, S_imag, V_imag);

        }

        matrix_destroy(W_real);
        matrix_destroy(W_imag);
        matrix_destroy(A_real);
        matrix_destroy(A_imag);
      
        svd_destroy(svd);

        // Rank reduction

        R_real = S_real->M;
        
        lambda_real_total = 0.0f;
        for (m = 0; m < S_real->M; m++) {
            lambda_real_total += matrix_get(S_real, m, m) * matrix_get(S_real, m, m);
        }       

        lambda_real_cumul = 0.0f;
        for (m = 0; m < S_real->M; m++) {
            lambda_real_cumul += matrix_get(S_real, m, m) * matrix_get(S_real, m, m);
            if (lambda_real_cumul >= (1.0f - epsilon) * lambda_real_total) {
                R_real = (m+1);
                break;
            }
        }

        R_imag = S_imag->M;

        lambda_imag_total = 0.0f;
        for (m = 0; m < S_imag->M; m++) {
            lambda_imag_total += matrix_get(S_imag, m, m) * matrix_get(S_imag, m, m);
        }       

        lambda_imag_cumul = 0.0f;
        for (m = 0; m < S_imag->M; m++) {
            lambda_imag_cumul += matrix_get(S_imag, m, m) * matrix_get(S_imag, m, m);
            if (lambda_imag_cumul >= (1.0f - epsilon) * lambda_imag_total) {
                R_imag = (m+1);
                break;
            }
        }

        obj->R_real = R_real;
        obj->R_imag = R_imag;

        obj->U_real = (float *) malloc(sizeof(float) * Q * R_real);
        obj->T_real = (float *) malloc(sizeof(float) * R_real * K);

        obj->U_imag = (float *) malloc(sizeof(float) * Q * R_imag);
        obj->T_imag = (float *) malloc(sizeof(float) * R_imag * K);

        if (Q >= K) {

            for (r = 0; r < R_real; r++) {
                for (q = 0; q < Q; q++) {
                    obj->U_real[q * R_real + r] = matrix_get(U_real, q, r);
                }
            }

            for (r = 0; r < R_imag; r++) {
                for (q = 0; q < Q; q++) {
                    obj->U_imag[q * R_imag + r] = matrix_get(U_imag, q, r);
                }
            }

            for (r = 0; r < R_real; r++) {
                for (k = 0; k < K; k++) {
                    obj->T_real[r * K + k] = matrix_get(S_real, r, r) * matrix_get(V_real, k, r);
                }
            }

            for (r = 0; r < R_imag; r++) {
                for (k = 0; k < K; k++) {
                    obj->T_imag[r * K + k] = matrix_get(S_imag, r, r) * matrix_get(V_imag, k, r);
                }
            }

        }
        else {

            for (r = 0; r < R_real; r++) {
                for (q = 0; q < Q; q++) {
                    obj->U_real[q * R_real + r] = matrix_get(V_real, q, r);
                }
            }

            for (r = 0; r < R_imag; r++) {
                for (q = 0; q < Q; q++) {
                    obj->U_imag[q * R_imag + r] = matrix_get(V_imag, q, r);
                }
            }

            for (r = 0; r < R_real; r++) {
                for (k = 0; k < K; k++) {
                    obj->T_real[r * K + k] = matrix_get(S_real, r, r) * matrix_get(U_real, k, r);
                    
                }
            }            

            for (r = 0; r < R_imag; r++) {
                for (k = 0; k < K; k++) {
                    obj->T_imag[r * K + k] = matrix_get(S_imag, r, r) * matrix_get(U_imag, k, r);
                }
            }

        }

        matrix_destroy(U_real);
        matrix_destroy(S_real);
        matrix_destroy(V_real);
        matrix_destroy(U_imag);
        matrix_destroy(S_imag);
        matrix_destroy(V_imag);

        obj->TX_real = (float *) malloc(sizeof(float) * R_real);
        obj->TX_imag = (float *) malloc(sizeof(float) * R_imag);

        return obj;

    }

    void gpsvd_destroy(gpsvd_obj * obj) {

        free((void *) (obj->thetas));
        free((void *) (obj->tdoas));

        free((void *) (obj->U_real));
        free((void *) (obj->T_real));
        free((void *) (obj->U_imag));
        free((void *) (obj->T_imag));

        free((void *) (obj->TX_real));
        free((void *) (obj->TX_imag));

        free((void *) obj);

    }

    int gpsvd_process(gpsvd_obj * obj, const float * X, float * x) {

        unsigned int R_real;
        unsigned int r_real;
        unsigned int R_imag;
        unsigned int r_imag;        
        unsigned int K;
        unsigned int k;
        unsigned int Q;
        unsigned int q;

        float total_real;
        float total_imag;

        K = obj->K;
        Q = obj->Q;
        R_real = obj->R_real;
        R_imag = obj->R_imag;

        for (r_real = 0; r_real < R_real; r_real++) {

            total_real = 0.0f;

            for (k = 0; k < K; k++) {
                total_real += obj->T_real[r_real * K + k] * X[k*2+0];
            }

            obj->TX_real[r_real] = total_real;

        }

        for (r_imag = 0; r_imag < R_imag; r_imag++) {

            total_imag = 0.0f;

            for (k = 0; k < K; k++) {
                total_imag += obj->T_imag[r_imag * K + k] * X[k*2+1];
            }

            obj->TX_imag[r_imag] = total_imag;

        }

        for (q = 0; q < Q; q++) {

            total_real = 0.0f;

            for (r_real = 0; r_real < R_real; r_real++) {
                total_real += obj->U_real[q * R_real + r_real] * obj->TX_real[r_real];
            }

            total_imag = 0.0f;

            for (r_imag = 0; r_imag < R_imag; r_imag++) {
                total_imag += obj->U_imag[q * R_imag + r_imag] * obj->TX_imag[r_imag];
            }

            x[q] = total_real - total_imag;

        }

        return 0;

    }

    int gpsvd_getMatrices(gpsvd_obj * obj, float * W_real, float * W_imag) {

        unsigned int Q;
        unsigned int K;
        unsigned int R_real;
        unsigned int R_imag;

        unsigned int q;
        unsigned int k;
        unsigned int r_real;
        unsigned int r_imag;

        float total_real;
        float total_imag;

        K = obj->K;
        Q = obj->Q;
        R_real = obj->R_real;
        R_imag = obj->R_imag;

        for (q = 0; q < Q; q++) {

            for (k = 0; k < K; k++) {

                total_real = 0.0f;

                for (r_real = 0; r_real < R_real; r_real++) {

                    total_real += obj->U_real[q * R_real + r_real] * obj->T_real[r_real * K + k];

                }

                total_imag = 0.0f;

                for (r_imag = 0; r_imag < R_imag; r_imag++) {

                    total_imag += obj->U_imag[q * R_imag + r_imag] * obj->T_imag[r_imag * K + k];

                }

                W_real[q * K + k] = total_real;
                W_imag[q * K + k] = total_imag;

            }

        }

        return 0;

    }
    
    #include <gccphat_svd/utils/gpsvd.h>

    gpsvd_obj * gpsvd_construct(const unsigned int N, const unsigned int fS, const float c, const float d, const unsigned int Q) {

        gpsvd_obj * obj;
        
        float theta, tdoa;
        float w_real, w_imag;
        float g;

        unsigned int K, R;
        unsigned int k, q;

        matrix_obj * W_real;
        matrix_obj * W_imag;

        matrix_obj * A1;
        matrix_obj * A2;

        matrix_obj * U1;
        matrix_obj * S1;
        matrix_obj * V1;
        matrix_obj * U2;
        matrix_obj * S2;
        matrix_obj * V2;

        svd_obj * svd;

        obj = (gpsvd_obj *) malloc(sizeof(gpsvd_obj));

        obj->N = N;
        obj->fS = fS;
        obj->c = c;
        obj->d = d;
        
        K = N/2 + 1;

        obj->K = K;
        obj->Q = Q;
                
        obj->thetas = matrix_construct(Q, 1);
        obj->tdoas = matrix_construct(Q, 1);

        // Sample arc from -pi/2 to pi/2 over Q points
        
        for (q = 0; q < Q; q++) {

            theta = -1.0f * M_PI_2 + (((float) q) / ((float) (Q-1))) * M_PI;
            matrix_set(obj->thetas, q, 0, theta);

        }

        // Compute corresponding TDOAs on the arc
        
        for (q = 0; q < Q; q++) {

            theta = matrix_get(obj->thetas, q, 0);
            tdoa = d * (fS/c) * sin(theta);
            matrix_set(obj->tdoas, q, 0, tdoa);

        }

        // Generate W matrix, and copy to A1 and A2 matrices

        W_real = matrix_construct(Q, K);
        W_imag = matrix_construct(Q, K);

        for (q = 0; q < Q; q++) {

            tdoa = matrix_get(obj->tdoas, q, 0);

            for (k = 0; k < K; k++) {

                if ((k == 0) || (k == N/2)) { g = 1; } else { g = 2; }

                w_real = sqrtf(g/((float) N)) * cosf(M_2_PI * ((float) k) * tdoa / ((float) N));
                w_imag = sqrtf(g/((float) N)) * sinf(M_2_PI * ((float) k) * tdoa / ((float) N));

                matrix_set(W_real, q, k, w_real);
                matrix_set(W_imag, q, k, w_imag);

            }

        }

        if (Q >= K) {

            A1 = matrix_construct(Q, K);
            A2 = matrix_construct(Q, K);

            matrix_copy(A1, W_real);
            matrix_copy(A2, W_imag);

        }
        else {

            A1 = matrix_construct(K, Q);
            A2 = matrix_construct(K, Q);

            matrix_transpose(A1, W_real);
            matrix_transpose(A2, W_imag);

        }

        matrix_destroy(W_real);
        matrix_destroy(W_imag);

        // Decompose

        svd = svd_construct();

        svd_destroy(svd);

        return obj;

    }

    void gpsvd_destroy(gpsvd_obj * obj) {

    }

    int gpsvd_process(gpsvd_obj * obj, const float * X, float * x) {

    }
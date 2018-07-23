    
    #include <gccphat_mm/utils/gpmm.h>
#include <stdio.h>
    
    gpmm_obj * gpmm_construct(const unsigned int N, const unsigned int fS, const float c, const float d, const unsigned int Q) {

        gpmm_obj * obj;
        unsigned int k, q;
        float theta, tdoa;
        float w_real, w_imag;
        unsigned int K;
        float g;

        obj = (gpmm_obj *) malloc(sizeof(gpmm_obj));

        obj->N = N;
        obj->fS = fS;
        obj->c = c;
        obj->d = d;
        
        K = N/2+1;

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

        obj->W_real = (float *) malloc(sizeof(float) * Q * K);
        obj->W_imag = (float *) malloc(sizeof(float) * Q * K);

        for (q = 0; q < Q; q++) {

            tdoa = obj->tdoas[q];

            for (k = 0; k < K; k++) {

                if ((k == 0) || (k == N/2)) { g = 1; } else { g = 2; }

                w_real = sqrtf(g/((float) N)) * cosf(2.0f * M_PI * ((float) k) * tdoa / ((float) N));
                w_imag = sqrtf(g/((float) N)) * sinf(2.0f * M_PI * ((float) k) * tdoa / ((float) N));

                obj->W_real[q * K + k] = w_real;
                obj->W_imag[q * K + k] = w_imag;

            }

        }

        return obj;

    }

    void gpmm_destroy(gpmm_obj * obj) {

        free((void *) obj->thetas);
        free((void *) obj->tdoas);
        free((void *) obj->W_real);
        free((void *) obj->W_imag);

    }

    int gpmm_process(gpmm_obj * obj, const float * X, float * x) {

        unsigned int Q;
        unsigned int K;

        unsigned int q;
        unsigned int k;

        float total_real;

        float Xk_real;
        float Xk_imag;
        float Wqk_real;
        float Wqk_imag;

        Q = obj->Q;
        K = obj->K;

        for (q = 0; q < Q; q++) {

            total_real = 0.0f;

            for (k = 0; k < K; k++) {

                Xk_real = X[k*2+0];
                Xk_imag = X[k*2+1];
                Wqk_real = obj->W_real[q * K + k];
                Wqk_imag = obj->W_imag[q * K + k];

                total_real += Xk_real * Wqk_real - Xk_imag * Wqk_imag;

            }

            x[q] = total_real;

        }

        return 0;

    }

    int gpmm_getMatrices(gpmm_obj * obj, float * W_real, float * W_imag) {

        memcpy(W_real, obj->W_real, sizeof(float) * obj->Q * obj->K);
        memcpy(W_imag, obj->W_imag, sizeof(float) * obj->Q * obj->K);

        return 0;

    }

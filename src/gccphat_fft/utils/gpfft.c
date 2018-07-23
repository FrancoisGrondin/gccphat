    
    #include <gccphat_fft/utils/gpfft.h>

    gpfft_obj * gpfft_construct(const unsigned int N, const unsigned int fS, const float c, const float d, const unsigned int Q, const unsigned int i) {

        gpfft_obj * obj;

        unsigned int n, q;
        float theta, tdoa;

        obj = (gpfft_obj *) malloc(sizeof(gpfft_obj));

        obj->N = N;
        obj->Ni = N * i;
        obj->fS = fS;
        obj->c = c;
        obj->d = d;
        obj->i = i;

        obj->K = N/2 + 1;
        obj->Ki = i*N/2 + 1;
        obj->Q = Q;

        obj->thetas = (float *) malloc(sizeof(float) * Q);
        obj->tdoas = (float *) malloc(sizeof(float) * Q);
        obj->mapper = (unsigned int *) malloc(sizeof(unsigned int) * Q);

        // Sample arc from -pi/2 to pi/2 over Q points
        // Compute corresponding TDOAs on the arc
        
        for (q = 0; q < Q; q++) {

            theta = -1.0f * M_PI_2 + (((float) q) / ((float) (Q-1))) * M_PI;
            obj->thetas[q] = theta;

            tdoa = roundf(i * d * (fS/c) * sin(theta)) / i;
            obj->tdoas[q] = tdoa;

            if (tdoa < 0.0f) {
                n = (unsigned int) (i * tdoa + (float) (i * N));
            }
            else {
                n = (unsigned int) (i * tdoa);
            }
            obj->mapper[q] = n;

        }

        obj->realArray = (float *) fftwf_malloc(sizeof(float) * N * i);
        obj->complexArray = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * obj->Ki);

        obj->C2R = fftwf_plan_dft_c2r_1d(N*i, obj->complexArray, obj->realArray, FFTW_ESTIMATE);

        return obj;

    }

    void gpfft_destroy(gpfft_obj * obj) {

        free((void *) obj->thetas);
        free((void *) obj->tdoas);
        free((void *) obj->mapper);

        fftwf_destroy_plan(obj->C2R);
        fftwf_free(obj->realArray);
        fftwf_free(obj->complexArray);

        fftwf_cleanup();

        free((void *) obj);

    }

    int gpfft_process(gpfft_obj * obj, const float * X, float * x) {
        
        unsigned int k, q;

        for (k = 0; k < obj->Ki; k++) {
            obj->complexArray[k][0] = 0.0f;
            obj->complexArray[k][1] = 0.0f;
        }

        for (k = 0; k < obj->K; k++) {

            obj->complexArray[k][0] = X[2*k+0];
            obj->complexArray[k][1] = X[2*k+1];

        }

        fftwf_execute(obj->C2R);

        for (q = 0; q < obj->Q; q++) {

            x[q] = obj->realArray[obj->mapper[q]] / ((float) obj->N);

        }

    }

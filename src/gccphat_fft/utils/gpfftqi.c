    
    #include <gccphat_fft/utils/gpfftqi.h>

    gpfftqi_obj * gpfftqi_construct(const unsigned int N, const unsigned int fS, const float c, const float d, const unsigned int Q, const unsigned int i) {

        gpfftqi_obj * obj;

        unsigned int n, q;
        float theta, tdoa, delta;

        unsigned int nPrev, nNext;
        float tdoaPrev, tdoaNext;

        obj = (gpfftqi_obj *) malloc(sizeof(gpfftqi_obj));

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
        obj->deltas = (float *) malloc(sizeof(float) * Q);
        obj->mapperPrev = (unsigned int *) malloc(sizeof(unsigned int) * Q);
        obj->mapper = (unsigned int *) malloc(sizeof(unsigned int) * Q);
        obj->mapperNext = (unsigned int *) malloc(sizeof(unsigned int) * Q);

        // Sample arc from -pi/2 to pi/2 over Q points
        // Compute corresponding TDOAs on the arc
        
        for (q = 0; q < Q; q++) {

            theta = -1.0f * M_PI_2 + (((float) q) / ((float) (Q-1))) * M_PI;
            obj->thetas[q] = theta;

            tdoa = roundf(i * d * (fS/c) * sin(theta)) / i;
            obj->tdoas[q] = tdoa;

            delta = i * d * (fS/c) * sin(theta) - tdoa * i;
            obj->deltas[q] = delta;

            tdoaPrev = (i * tdoa - 1.0f) / i;
            tdoaNext = (i * tdoa + 1.0f) / i;

            if (tdoa < 0.0f) {
                n = (unsigned int) (i * tdoa + (float) (i * N));
            }
            else {
                n = (unsigned int) (i * tdoa);
            }
            obj->mapper[q] = n;

            if (tdoaPrev < 0.0f) {
                nPrev = (unsigned int) (i * tdoaPrev + (float) (i * N));
            }
            else {
                nPrev = (unsigned int) (i * tdoaPrev);
            }
            obj->mapperPrev[q] = nPrev;

            if (tdoaNext < 0.0f) {
                nNext = (unsigned int) (i * tdoaNext + (float) (i * N));
            }
            else {
                nNext = (unsigned int) (i * tdoaNext);
            }
            obj->mapperNext[q] = nNext;

        }

        obj->realArray = (float *) fftwf_malloc(sizeof(float) * N * i);
        obj->complexArray = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * obj->Ki);

        obj->C2R = fftwf_plan_dft_c2r_1d(N*i, obj->complexArray, obj->realArray, FFTW_ESTIMATE);

        return obj;

    }

    void gpfftqi_destroy(gpfftqi_obj * obj) {

        free((void *) obj->thetas);
        free((void *) obj->tdoas);
        free((void *) obj->deltas);
        free((void *) obj->mapperPrev);
        free((void *) obj->mapper);
        free((void *) obj->mapperNext);

        fftwf_destroy_plan(obj->C2R);
        fftwf_free(obj->realArray);
        fftwf_free(obj->complexArray);

        fftwf_cleanup();

        free((void *) obj);

    }

    int gpfftqi_process(gpfftqi_obj * obj, const float * X, float * x) {
        
        unsigned int k, q;
        float yPrev, y, yNext;
        float delta;
        float a, b, c;

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

            yPrev = obj->realArray[obj->mapperPrev[q]] / ((float) obj->N);
            y = obj->realArray[obj->mapper[q]] / ((float) obj->N);
            yNext = obj->realArray[obj->mapperNext[q]] / ((float) obj->N);

            delta = obj->deltas[q];

            a = 0.5f * yPrev - y + 0.5f * yNext;
            b = -0.5f * yPrev + 0.5f * yNext;
            c = y;

            x[q] = a * delta * delta + b * delta + c;

        }

    }

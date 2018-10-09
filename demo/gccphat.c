
    #include <gccphat_svd.h>
    #include <gccphat_mm.h>
    #include <gccphat_fft.h>

    #include <getopt.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <math.h>
    #include <time.h>

    void help(void) {

        printf("c    Speed of sound (m/sec)\n");
        printf("d    Distance between microphones (m)\n");
        printf("h    Display help\n");
        printf("i    Interpolation rate\n");
        printf("m    Method to compute GCC-PHAT ('f', for fft, m' for multiplication, 's' for svd)\n");
        printf("N    Frame size (sample)\n");
        printf("Q    Number of discrete angle on the arc from -pi/2 to +pi/2\n");
        printf("r    Sample rate (sample/sec)­\n");

    }

    int findMax(const float * x, const unsigned int Q) {

        unsigned int q;
        float maxValue;
        unsigned int qMax;

        maxValue = -INFINITY;
        qMax = 0;

        for (q = 0; q < Q; q++) {

            if (x[q] > maxValue) { 
                maxValue = x[q]; 
                qMax = q;
            }

        }

        return qMax;

    }

    int main(int argc, char * argv[]) {

        int option;

        unsigned int N, r, Q;
        float c, d;
        char m;
        unsigned int i;

        unsigned int K;
        unsigned int q, k;
        unsigned int qMax;
        float theta;

        gpsvd_obj * gpsvd;
        gpmm_obj * gpmm;
        gpfft_obj * gpfft;

        float * X;
        float * x;

        float * Wreal;
        float * Wimag;

        char l, o;

        clock_t t;
        double time_taken;

        c = NAN;
        d = NAN;
        i = 1;
        l = 0;
        m = 0x00;
        N = 0;
        o = 0;
        Q = 0;
        r = 0;

        while ((option = getopt(argc, argv, "c:d:hi:lm:N:oQ:r:")) != -1) {

            switch (option) {

                case 'c': c = atof(optarg); break;
                case 'd': d = atof(optarg); break;
                case 'h': help(); exit(EXIT_SUCCESS); break;
                case 'i': i = atoi(optarg); break;
                case 'l': l = 1; break;
                case 'm': m = optarg[0]; break;
                case 'N': N = atoi(optarg); break;
                case 'o': o = 1; break;
                case 'Q': Q = atoi(optarg); break;
                case 'r': r = atoi(optarg); break;

            }

        }

        if (isnan(c) != 0) { printf("Missing speed of sound\n"); exit(EXIT_FAILURE); }
        if (isnan(d) != 0) { printf("Missing distance between microphones\n"); exit(EXIT_FAILURE); }
        if (m == 0x00) { printf("Missing method\n"); exit(EXIT_FAILURE); }
        if (N == 0) { printf("Missing frame size\n"); exit(EXIT_FAILURE); }
        if (Q == 0) { printf("Missing number of discretized angles\n"); exit(EXIT_FAILURE); }
        if (r == 0) { printf("Missing sample rate\n"); exit(EXIT_FAILURE); }        

        K = N/2 + 1;

        switch (m) {

            case 'f':

                X = (float *) malloc(sizeof(float) * K * 2);
                x = (float *) malloc(sizeof(float) * Q);

                gpfft = gpfft_construct(N, r, c, d, Q, i);

                time_taken = 0.0f;

                while (fread(X, sizeof(float), 2*K, stdin) == (2*K)) {

                    t = clock();

                    gpfft_process(gpfft, X, x);

                    qMax = findMax(x, Q);
                    theta = gpfft->thetas[qMax];

                    if (o == 1)
                        fprintf(stdout, "%1.6f\n", theta);

                    t = clock() - t;
                    time_taken += ((double)t)/CLOCKS_PER_SEC;

                }

                if (l == 1)
                    fprintf(stdout, "%1.6f\n", time_taken);                

                gpfft_destroy(gpfft);
                
                free((void *) X);
                free((void *) x);                

            break;

            case 'm':

                X = (float *) malloc(sizeof(float) * K * 2);
                x = (float *) malloc(sizeof(float) * Q);

                gpmm = gpmm_construct(N, r, c, d, Q);
                
                time_taken = 0.0f;

                while (fread(X, sizeof(float), 2*K, stdin) == (2*K)) {

                    t = clock();

                    gpmm_process(gpmm, X, x);
                    qMax = findMax(x, Q);
                    theta = gpmm->thetas[qMax];

                    if (o == 1)
                        fprintf(stdout, "%1.6f\n", theta);

                    t = clock() - t;
                    time_taken += ((double)t)/CLOCKS_PER_SEC;

                }

                if (l == 1)
                    fprintf(stdout, "%1.6f\n", time_taken);

                gpmm_destroy(gpmm);

                free((void *) X);
                free((void *) x);

            break;

            case 's':

                X = (float *) malloc(sizeof(float) * K * 2);
                x = (float *) malloc(sizeof(float) * Q);

                gpsvd = gpsvd_construct(N, r, c, d, Q);

                time_taken = 0.0f;

                while (fread(X, sizeof(float), 2*K, stdin) == (2*K)) {

                    t = clock();

                    gpsvd_process(gpsvd, X, x);
                    qMax = findMax(x, Q);
                    theta = gpsvd->thetas[qMax];

                    if (o == 1)
                        fprintf(stdout, "%1.6f\n", theta);

                    t = clock() - t;
                    time_taken += ((double)t)/CLOCKS_PER_SEC;

                }

                if (l == 1)
                    fprintf(stdout, "%1.6f\n", time_taken);

                gpsvd_destroy(gpsvd);

                free((void *) X);
                free((void *) x);

            break;

            default:

                printf("Invalid method\n");
                exit(EXIT_FAILURE);

            break;

        }

        return 0;

    }
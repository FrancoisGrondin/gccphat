
    #include <getopt.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <math.h>

    void help(void) {

        printf("c    Speed of sound (m/sec)\n");
        printf("d    Distance between microphones (m)\n");
        printf("h    Display help\n");
        printf("N    Frame size (sample)\n");
        printf("r    Sample rate (sample/sec)­\n");

    }

    int main(int argc, char * argv[]) {

        int option;

        float a;
        float c;
        float d;
        unsigned int N;
        unsigned int r;

        unsigned int k;
        unsigned int K;
        float tdoa;
        float angle;
        float w_real;
        float w_imag;
        float * W;

        char str[64];

        c = NAN;
        d = NAN;
        N = 0;
        r = 0;
        
        while ((option = getopt(argc, argv, "c:d:F:hN:r:")) != -1) {

            switch (option) {

                case 'c': c = atof(optarg); break;
                case 'd': d = atof(optarg); break;
                case 'h': help(); exit(EXIT_SUCCESS); break;
                case 'N': N = atoi(optarg); break;
                case 'r': r = atoi(optarg); break;

            }

        }

        if (isnan(c) != 0) { printf("Missing speed of sound\n"); exit(EXIT_FAILURE); }
        if (isnan(d) != 0) { printf("Missing distance between microphones\n"); exit(EXIT_FAILURE); }
        if (N == 0) { printf("Missing frame size\n"); exit(EXIT_FAILURE); }
        if (r == 0) { printf("Missing sample rate\n"); exit(EXIT_FAILURE); }

        K = N/2 + 1;

        while(scanf("%f", &a) > 0) {

            tdoa = (((float) r)/c) * d * sin(a);
            W = (float *) malloc(sizeof(float) * K * 2);

            for (k = 0; k < K; k++) {

                angle = 2*M_PI*((float) k)*-1.0*tdoa/((float) N);

                w_real = cosf(angle);
                w_imag = sinf(angle);

                W[k*2+0] = w_real;
                W[k*2+1] = w_imag;

            }

            fwrite(W, sizeof(float), 2*K, stdout);

        }

        return 0;

    }
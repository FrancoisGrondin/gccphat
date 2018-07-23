
	#include <gccphat_svd.h>
	#include <gccphat_mm.h>

	int main(int argc, char * argv[]) {

		gpsvd_obj * gpsvd;
		gpmm_obj * gpmm;

		unsigned int N, fS, Q;
		float c, d;

		float * Wreal_mm;
		float * Wimag_mm;
		float * Wreal_svd;
		float * Wimag_svd;
		unsigned int K;

		unsigned int q, k;

		N = 32;
		fS = 16000;
		Q = 11;
		
		c = 343.0f;
		d = 0.05;

		K = N/2 + 1;

		gpsvd = gpsvd_construct(N, fS, c, d, Q);
		gpmm = gpmm_construct(N, fS, c, d, Q);
		
		Wreal_mm = (float *) malloc(sizeof(float) * Q * K);
		Wimag_mm = (float *) malloc(sizeof(float) * Q * K);
		Wreal_svd = (float *) malloc(sizeof(float) * Q * K);
		Wimag_svd = (float *) malloc(sizeof(float) * Q * K);


		free((void *) Wreal_mm);
		free((void *) Wimag_mm);
		free((void *) Wreal_svd);
		free((void *) Wimag_svd);

		gpmm_destroy(gpmm);
		gpsvd_destroy(gpsvd);

		return 0;

	}
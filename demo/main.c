
	#include <gccphat_svd.h>

	int main(int argc, char * argv[]) {

		gpsvd_obj * gpsvd;
		unsigned int N, fS, Q;
		float c, d;

		N = 128;
		fS = 16000;
		Q = 11;
		c = 343.0f;
		d = 0.05;

		gpsvd = gpsvd_construct(N, fS, c, d, Q);

		gpsvd_destroy(gpsvd);

		return 0;

	}
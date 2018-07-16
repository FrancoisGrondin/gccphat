
    #include <gccphat/utils/scalar.h>

	scalar_struct scalar_add(scalar_struct a, scalar_struct b) {

		scalar_struct c;

		c.real = a.real + b.real;
		c.imag = a.imag + b.imag;

		return c;

	}

    scalar_struct scalar_sub(scalar_struct a, scalar_struct b) {

    	scalar_struct c;

    	c.real = a.real - b.real;
    	c.imag = a.imag - b.imag;

    	return c;

    }

    scalar_struct scalar_mul(scalar_struct a, scalar_struct b) {

    	scalar_struct c;

    	c.real = a.real * b.real - a.imag * b.imag;
    	c.imag = a.real * b.imag + a.imag * b.real;

    	return c;

    }

    scalar_struct scalar_div(scalar_struct a, scalar_struct b) {

    	scalar_struct c;

    	c.real = (a.real * b.real + a.imag * b.imag) / (b.real * b.real + b.imag * b.imag);
    	c.imag = (a.imag * b.real - a.real * b.imag) / (b.real * b.real + b.imag * b.imag);

    	return c;

    }

    scalar_struct scalar_inv(scalar_struct a) {

    	scalar_struct b;

    	b.real = a.real / (a.real * a.real + a.imag * a.imag);
    	b.imag = -1.0f * a.imag / (a.real * a.real + a.imag * a.imag);

    	return b;

    }

    scalar_struct scalar_conj(scalar_struct a) {

    	scalar_struct b;

    	b.real = a.real;
    	b.imag = -1.0f * a.imag;

    	return b;

    }

    float scalar_getAmplitude(scalar_struct a) {

        return (sqrtf(a.real*a.real + a.imag*a.imag));

    }

    float scalar_getPhase(scalar_struct a) {

        return (atan2f(a.imag, a.real));

    }

    scalar_struct scalar_setPhasor(const float amplitude, const float phase) {

        scalar_struct a;

        a.real = amplitude * cosf(phase);
        a.imag = amplitude * sinf(phase);

        return a;

    }
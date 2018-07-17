    
    #include <gccphat/utils/vector.h>

    vector_obj * vector_construct(const unsigned int nElements) {

        vector_obj * obj;

        obj = (vector_obj *) malloc(sizeof(vector_obj));

        obj->nElements = nElements;

        obj->real = (float *) malloc(sizeof(float) * nElements);
        obj->imag = (float *) malloc(sizeof(float) * nElements);

        memset(obj->real, 0x00, sizeof(float) * nElements);
        memset(obj->imag, 0x00, sizeof(float) * nElements);

        return obj;

    }

    void vector_destroy(vector_obj * obj) {

        free((void *) obj->real);
        free((void *) obj->imag);

        free((void *) obj);

    }

    int vector_copy(vector_obj * dest, const vector_obj * src) {

        unsigned int nElements;

        if (dest->nElements != src->nElements) { return -1; }

        nElements = dest->nElements;

        memcpy(dest->real, src->real, sizeof(float) * nElements);
        memcpy(dest->imag, src->imag, sizeof(float) * nElements);

        return 0;

    }    

    int vector_get(vector_obj * obj, const unsigned int iElement, scalar_struct * scalar) {

        if (iElement >= obj->nElements) { return -1; }

        scalar->real = obj->real[iElement];
        scalar->imag = obj->imag[iElement];

        return 0;

    }

    int vector_set(vector_obj * obj, const unsigned int iElement, const scalar_struct * scalar) {

        if (iElement >= obj->nElements) { return -1; }

        obj->real[iElement] = scalar->real;
        obj->imag[iElement] = scalar->imag;

        return 0;       

    }

    int vector_zero(vector_obj * obj) {

        memset(obj->real, 0x00, sizeof(float) * obj->nElements);
        memset(obj->imag, 0x00, sizeof(float) * obj->nElements);

        return 0;

    }

    int vector_dot(scalar_struct * dest, const vector_obj * src1, const vector_obj * src2) {

        unsigned int iElement;
        unsigned int nElements;

        if (src1->nElements != src2->nElements) { return -1; }

        nElements = src1->nElements;

        dest->real = 0.0f;
        dest->imag = 0.0f;

        for (iElement = 0; iElement < nElements; iElement++) {

            dest->real += src1->real[iElement] * src2->real[iElement] - (src1->imag[iElement]) * -1.0f * src2->imag[iElement];
            dest->imag += src1->real[iElement] * -1.0f * src2->imag[iElement] + (src1->imag[iElement]) * src2->real[iElement];

        }

        return 0;

    }

    int vector_norm(float * dest, const vector_obj * obj) {

        unsigned int iElement;
        unsigned int nElements;

        nElements = obj->nElements;

        *dest = 0.0f;

        for (iElement = 0; iElement < nElements; iElement++) {

            *dest += obj->real[iElement] * obj->real[iElement] + obj->imag[iElement] * obj->imag[iElement];

        }

        *dest = sqrtf(*dest);

        return 0;

    }

    int vector_add(vector_obj * dest, const vector_obj * src1, const vector_obj * src2) {

        unsigned int iElement;
        unsigned int nElements;

        if (dest->nElements != src1->nElements) { return -1; }
        if (dest->nElements != src2->nElements) { return -1; }

        nElements = dest->nElements;

        for (iElement = 0; iElement < nElements; iElement++) {

            dest->real[iElement] = src1->real[iElement] + src2->real[iElement];
            dest->imag[iElement] = src1->imag[iElement] + src2->imag[iElement];

        }

        return 0;

    }

    int vector_sub(vector_obj * dest, const vector_obj * src1, const vector_obj * src2) {

        unsigned int iElement;
        unsigned int nElements;

        if (dest->nElements != src1->nElements) { return -1; }
        if (dest->nElements != src2->nElements) { return -1; }

        nElements = dest->nElements;

        for (iElement = 0; iElement < nElements; iElement++) {

            dest->real[iElement] = src1->real[iElement] - src2->real[iElement];
            dest->imag[iElement] = src1->imag[iElement] - src2->imag[iElement];

        }

        return 0;

    }

    int vector_scale(vector_obj * dest, const vector_obj * src, const scalar_struct * scale) {

        unsigned int iElement;
        unsigned int nElements;

        if (dest->nElements != src->nElements) { return -1; }

        nElements = dest->nElements;

        for (iElement = 0; iElement < nElements; iElement++) {

            dest->real[iElement] = src->real[iElement] * scale->real - src->imag[iElement] * scale->imag;
            dest->imag[iElement] = src->real[iElement] * scale->imag + src->imag[iElement] * scale->real;

        }

        return 0;

    }

    int vector_normalize(vector_obj * dest, const vector_obj * src) {

        unsigned int iElement;
        unsigned int nElements;
        float norm;

        if (dest->nElements != src->nElements) { return -1; }

        nElements = dest->nElements;

        norm = 0.0f;

        for (iElement = 0; iElement < nElements; iElement++) {

            norm += src->real[iElement] * src->real[iElement] + src->imag[iElement] * src->imag[iElement];

        }

        norm = sqrtf(norm);

        for (iElement = 0; iElement < nElements; iElement++) {

            dest->real[iElement] = src->real[iElement] / norm;
            dest->imag[iElement] = src->imag[iElement] / norm;

        }

        return 0;

    }

    void vector_printf(vector_obj * obj) {

        unsigned int iElement;
        float objR, objI;

        for (iElement = 0; iElement < obj->nElements; iElement++) {

            objR = obj->real[iElement];
            objI = obj->imag[iElement];

            printf("(%+.3E %+.3Ej)  ", objR, objI);

        }        

    }
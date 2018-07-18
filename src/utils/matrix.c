
    #include <gccphat/utils/matrix.h>

    matrix_obj * matrix_construct(const unsigned int nRows, const unsigned int nCols) {

        matrix_obj * obj;

        obj = (matrix_obj *) malloc(sizeof(matrix_obj));

        obj->nRows = nRows;
        obj->nCols = nCols;

        obj->real = (float *) malloc(sizeof(float) * nRows * nCols);
        obj->imag = (float *) malloc(sizeof(float) * nRows * nCols);

        memset(obj->real, 0x00, sizeof(float) * nRows * nCols);
        memset(obj->imag, 0x00, sizeof(float) * nRows * nCols);

        return obj;

    }

    void matrix_destroy(matrix_obj * obj) {

        free((void *) (obj->real));
        free((void *) (obj->imag));

        free((void *) obj);

    }

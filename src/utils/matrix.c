    
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

    int matrix_get(matrix_obj * obj, const unsigned int iRow, const unsigned int iCol, float * real, float * imag) {

        if (iRow >= obj->nRows) { return -1; }
        if (iCol >= obj->nCols) { return -1; }

        *real = obj->real[iRow * obj->nCols + iCol];
        *imag = obj->imag[iRow * obj->nCols + iCol];

        return 0;

    }

    int matrix_set(matrix_obj * obj, const unsigned int iRow, const unsigned int iCol, const float real, const float imag) {

        if (iRow >= obj->nRows) { return -1; }
        if (iCol >= obj->nCols) { return -1; }

        obj->real[iRow * obj->nCols + iCol] = real;
        obj->imag[iRow * obj->nCols + iCol] = imag;

        return 0;

    }

    int matrix_add(matrix_obj * dest, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int iRow, iCol;

        float destR, destI;
        float src1R, src1I;
        float src2R, src2I;

        if (dest->nRows != src1->nRows) { return -1; }
        if (dest->nCols != src1->nCols) { return -1; }
        if (dest->nRows != src2->nRows) { return -1; }
        if (dest->nCols != src2->nCols) { return -1; }

        for (iRow = 0; iRow < dest->nRows; iRow++) {

            for (iCol = 0; iCol < dest->nCols; iCol++) {

                src1R = src1->real[iRow * src1->nCols + iCol];
                src1I = src1->imag[iRow * src1->nCols + iCol];
                src2R = src2->real[iRow * src2->nCols + iCol];
                src2I = src2->imag[iRow * src2->nCols + iCol];

                destR = src1R + src2R;
                destI = src1I + src2I;

                dest->real[iRow * dest->nCols + iCol] = destR;
                dest->imag[iRow * dest->nCols + iCol] = destI;

            }

        }

        return 0;

    }

    int matrix_sub(matrix_obj * dest, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int iRow, iCol;

        float destR, destI;
        float src1R, src1I;
        float src2R, src2I;

        if (dest->nRows != src1->nRows) { return -1; }
        if (dest->nCols != src1->nCols) { return -1; }
        if (dest->nRows != src2->nRows) { return -1; }
        if (dest->nCols != src2->nCols) { return -1; }

        for (iRow = 0; iRow < dest->nRows; iRow++) {

            for (iCol = 0; iCol < dest->nCols; iCol++) {

                src1R = src1->real[iRow * src1->nCols + iCol];
                src1I = src1->imag[iRow * src1->nCols + iCol];
                src2R = src2->real[iRow * src2->nCols + iCol];
                src2I = src2->imag[iRow * src2->nCols + iCol];

                destR = src1R - src2R;
                destI = src1I - src2I;

                dest->real[iRow * dest->nCols + iCol] = destR;
                dest->imag[iRow * dest->nCols + iCol] = destI;

            }

        }

        return 0;

    }

    int matrix_mul(matrix_obj * dest, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int iRow, iCol, iElement;
        
        float destR, destI;
        float src1R, src1I;
        float src2R, src2I;  

        if (dest->nRows != src1->nRows) { return -1; }
        if (dest->nCols != src2->nCols) { return -1; }
        if (src1->nCols != src2->nRows) { return -1; }

        for (iRow = 0; iRow < dest->nRows; iRow++) {

            for (iCol = 0; iCol < dest->nCols; iCol++) {

                destR = 0.0f;
                destI = 0.0f;

                for (iElement = 0; iElement < src1->nCols; iElement++) {

                    src1R = src1->real[iRow * src1->nCols + iElement];
                    src1I = src1->imag[iRow * src1->nCols + iElement];
                    src2R = src2->real[iElement * src2->nCols + iCol];
                    src2I = src2->imag[iElement * src2->nCols + iCol];

                    destR += src1R * src2R - src1I * src2I;
                    destI += src1R * src2I + src1I * src2R;

                }

                dest->real[iRow * dest->nCols + iCol] = destR;
                dest->imag[iRow * dest->nCols + iCol] = destI;

            }

        }

        return 0;

    }

    int matrix_conj(matrix_obj * dest, const matrix_obj * src) {

        unsigned int iRow, iCol;

        float destR, destI;
        float srcR, srcI;

        if (dest->nRows != src->nCols) { return -1; }
        if (dest->nCols != src->nRows) { return -1; }

        for (iRow = 0; iRow < dest->nRows; iRow++) {

            for (iCol = 0; iCol < dest->nCols; iCol++) {

                srcR = src->real[iRow * src->nCols + iCol];
                srcI = src->imag[iRow * src->nCols + iCol];

                destR = srcR;
                destI = -1.0f * srcI;

                dest->real[iCol * dest->nRows + iRow] = destR;
                dest->imag[iCol * dest->nRows + iRow] = destI;

            }

        }

        return 0;

    }

    void matrix_printf(matrix_obj * obj) {

        unsigned int iRow, iCol;
        float objR, objI;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                objR = obj->real[iRow * obj->nCols + iCol];
                objI = obj->imag[iRow * obj->nCols + iCol];

                printf("(%+.3E %+.3Ej)  ", objR, objI);

            }

            printf("\n");

        }

    }

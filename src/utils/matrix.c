    
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

    int matrix_copy(matrix_obj * dest, const matrix_obj * src) {

        if (dest->nRows != src->nRows) { return -1; }
        if (dest->nCols != src->nCols) { return -1; }

        memcpy(dest->real, src->real, sizeof(float) * dest->nRows * dest->nCols);
        memcpy(dest->imag, src->imag, sizeof(float) * dest->nRows * dest->nCols);

        return 0;

    }

    int matrix_getElement(const matrix_obj * obj, const unsigned int iRow, const unsigned int iCol, scalar_struct * scalar) {

        if (iRow >= obj->nRows) { return -1; }
        if (iCol >= obj->nCols) { return -1; }

        scalar->real = obj->real[iRow * obj->nCols + iCol];
        scalar->imag = obj->imag[iRow * obj->nCols + iCol];

        return 0;

    }

    int matrix_setElement(matrix_obj * obj, const unsigned int iRow, const unsigned int iCol, const scalar_struct * scalar) {

        if (iRow >= obj->nRows) { return -1; }
        if (iCol >= obj->nCols) { return -1; }

        obj->real[iRow * obj->nCols + iCol] = scalar->real;
        obj->imag[iRow * obj->nCols + iCol] = scalar->imag;

        return 0;

    }

    int matrix_getRow(const matrix_obj * obj, const unsigned int iRow, vector_obj * vtr) {

        unsigned int iElement;
        unsigned int nElements;

        if (iRow >= obj->nRows) { return -1; }
        if (vtr->nElements != obj->nCols) { return -1; }

        nElements = vtr->nElements;

        for (iElement = 0; iElement < nElements; iElement++) {

            vtr->real[iElement] = obj->real[iRow * obj->nCols + iElement];
            vtr->imag[iElement] = obj->imag[iRow * obj->nCols + iElement];

        }

        return 0;

    }

    int matrix_setRow(matrix_obj * obj, const unsigned int iRow, const vector_obj * vtr) {

        unsigned int iElement;
        unsigned int nElements;

        if (iRow >= obj->nRows) { return -1; }
        if (vtr->nElements != obj->nCols) { return -1; }

        nElements = vtr->nElements;

        for (iElement = 0; iElement < nElements; iElement++) {

            obj->real[iRow * obj->nCols + iElement] = vtr->real[iElement];
            obj->imag[iRow * obj->nCols + iElement] = vtr->imag[iElement];

        }

        return 0;
    }

    int matrix_getCol(const matrix_obj * obj, const unsigned int iCol, vector_obj * vtr) {

        unsigned int iElement;
        unsigned int nElements;

        if (iCol >= obj->nCols) { return -1; }
        if (vtr->nElements != obj->nRows) { return -1; }

        nElements = vtr->nElements;

        for (iElement = 0; iElement < nElements; iElement++) {

            vtr->real[iElement] = obj->real[iElement * obj->nCols + iCol];
            vtr->imag[iElement] = obj->imag[iElement * obj->nCols + iCol];

        }

        return 0;

    }

    int matrix_setCol(matrix_obj * obj, const unsigned int iCol, const vector_obj * vtr) {

        unsigned int iElement;
        unsigned int nElements;

        if (iCol >= obj->nCols) { return -1; }
        if (vtr->nElements != obj->nRows) { return -1; }

        nElements = vtr->nElements;

        for (iElement = 0; iElement < nElements; iElement++) {

            obj->real[iElement * obj->nCols + iCol] = vtr->real[iElement];
            obj->imag[iElement * obj->nCols + iCol] = vtr->imag[iElement];

        }

        return 0;

    }

    int matrix_getSubMatrix(const matrix_obj * obj, const unsigned int iRow, const unsigned int iCol, matrix_obj * sub) {

        unsigned int iRowMain;
        unsigned int iColMain;
        unsigned int iRowSub;
        unsigned int iColSub;

        if ((iRow + sub->nRows) > obj->nRows) { return -1; }
        if ((iCol + sub->nCols) > obj->nCols) { return -1; }

        for (iRowSub = 0; iRowSub < sub->nRows; iRowSub++) {

            iRowMain = iRow + iRowSub;

            for (iColSub = 0; iColSub < sub->nCols; iColSub++) {

                iColMain = iCol + iColSub;

                sub->real[iRowSub * sub->nCols + iColSub] = obj->real[iRowMain * obj->nCols + iColMain];
                sub->imag[iRowSub * sub->nCols + iColSub] = obj->imag[iRowMain * obj->nCols + iColMain];

            }

        }

        return 0;

    }

    int matrix_setSubMatrix(matrix_obj * obj, const unsigned int iRow, const unsigned int iCol, const matrix_obj * sub) {

        unsigned int iRowMain;
        unsigned int iColMain;
        unsigned int iRowSub;
        unsigned int iColSub;

        if ((iRow + sub->nRows) > obj->nRows) { return -1; }
        if ((iCol + sub->nCols) > obj->nCols) { return -1; }

        for (iRowSub = 0; iRowSub < sub->nRows; iRowSub++) {

            iRowMain = iRow + iRowSub;

            for (iColSub = 0; iColSub < sub->nCols; iColSub++) {

                iColMain = iCol + iColSub;

                obj->real[iRowMain * obj->nCols + iColMain] = sub->real[iRowSub * sub->nCols + iColSub];
                obj->imag[iRowMain * obj->nCols + iColMain] = sub->imag[iRowSub * sub->nCols + iColSub];
                
            }

        }

        return 0;

    }

    int matrix_getDiag(const matrix_obj * obj, vector_obj * vtr) {

        unsigned int nRows;
        unsigned int nCols;
        unsigned int nElements;
        unsigned int iRow;
        unsigned int iCol;
        unsigned int iElement;

        if (obj->nRows != obj->nCols) { return -1; }
        if (obj->nRows != vtr->nElements) { return -1; }

        nElements = vtr->nElements;
        nRows = obj->nRows;
        nCols = obj->nCols;

        for (iRow = 0; iRow < nRows; iRow++) {

            iCol = iRow;
            iElement = iRow;

            vtr->real[iElement] = obj->real[iRow * nCols + iCol];
            vtr->imag[iElement] = obj->imag[iRow * nCols + iCol];

        }

        return 0;

    }

    int matrix_setDiag(matrix_obj * obj, const vector_obj * vtr) {

        unsigned int nRows;
        unsigned int nCols;
        unsigned int nElements;
        unsigned int iRow;
        unsigned int iCol;
        unsigned int iElement;

        if (obj->nRows != obj->nCols) { return -1; }
        if (obj->nRows != vtr->nElements) { return -1; }

        nElements = vtr->nElements;
        nRows = obj->nRows;
        nCols = obj->nCols;

        for (iRow = 0; iRow < nRows; iRow++) {

            iCol = iRow;
            iElement = iRow;

            obj->real[iRow * nCols + iCol] = vtr->real[iElement];
            obj->imag[iRow * nCols + iCol] = vtr->imag[iElement];

        }

        return 0;

    }

    int matrix_zero(matrix_obj * obj) {

        memset(obj->real, 0x00, sizeof(float) * obj->nRows * obj->nCols);
        memset(obj->imag, 0x00, sizeof(float) * obj->nRows * obj->nCols);

        return 0;

    }

    int matrix_identity(matrix_obj * obj) {

        unsigned int iElement;
        unsigned int nElements;
        
        if (obj->nRows >= obj->nCols) { nElements = obj->nCols; }
        else { nElements = obj->nRows; }

        memset(obj->real, 0x00, sizeof(float) * obj->nRows * obj->nCols);
        memset(obj->imag, 0x00, sizeof(float) * obj->nRows * obj->nCols);

        for (iElement = 0; iElement < nElements; iElement++) {

            obj->real[iElement * obj->nCols + iElement] = 1.0f;

        }

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

    int matrix_had(matrix_obj * dest, const matrix_obj * src1, const matrix_obj * src2) {

        unsigned int iRow;
        unsigned int iCol;
        unsigned int nRows;
        unsigned int nCols;

        float src1R, src1I;
        float src2R, src2I;
        float destR, destI; 

        if (dest->nRows != src1->nRows) { return -1; }
        if (dest->nRows != src2->nRows) { return -1; }
        if (dest->nCols != src1->nCols) { return -1; }
        if (dest->nCols != src2->nCols) { return -1; }

        nRows = dest->nRows;
        nCols = dest->nCols;

        for (iRow = 0; iRow < nRows; iRow++) {

            for (iCol = 0; iCol < nCols; iCol++) {

                src1R = src1->real[iRow * nCols + iCol];
                src1I = src1->imag[iRow * nCols + iCol];
                src2R = src2->real[iRow * nCols + iCol];
                src2I = src2->imag[iRow * nCols + iCol];

                destR = src1R * src2R - src1I * src2I;
                destI = src1R * src2I + src1I * src2R;

                dest->real[iRow * nCols + iCol] = destR;
                dest->imag[iRow * nCols + iCol] = destI;

            }

        }

        return 0;

    }

    int matrix_conj(matrix_obj * dest, const matrix_obj * src) {

        unsigned int iRowSrc, iColSrc;
        unsigned int iRowDest, iColDest;

        float destR, destI;
        float srcR, srcI;

        if (dest->nRows != src->nCols) { return -1; }
        if (dest->nCols != src->nRows) { return -1; }

        for (iRowSrc = 0; iRowSrc < src->nRows; iRowSrc++) {

            for (iColSrc = 0; iColSrc < src->nCols; iColSrc++) {

                iColDest = iRowSrc;
                iRowDest = iColSrc;

                srcR = src->real[iRowSrc * src->nCols + iColSrc];
                srcI = src->imag[iRowSrc * src->nCols + iColSrc];

                destR = srcR;
                destI = -1.0f * srcI;

                dest->real[iRowDest * dest->nCols + iColDest] = destR;
                dest->imag[iRowDest * dest->nCols + iColDest] = destI;

            }

        }

        return 0;

    }

    int matrix_scale(matrix_obj * dest, const matrix_obj * src, const scalar_struct * scalar) {

        unsigned int iRow, iCol;

        float destR, destI;
        float srcR, srcI;

        if (dest->nRows != src->nRows) { return -1; }
        if (dest->nCols != src->nCols) { return -1; }

        for (iRow = 0; iRow < dest->nRows; iRow++) {

            for (iCol = 0; iCol < dest->nCols; iCol++) {

                srcR = src->real[iRow * src->nCols + iCol];
                srcI = src->imag[iRow * src->nCols + iCol];

                destR = srcR * scalar->real - srcI * scalar->imag;
                destI = srcI * scalar->real + srcR * scalar->imag;

                dest->real[iRow * src->nCols + iCol] = destR;
                dest->imag[iRow * src->nCols + iCol] = destI;

            }

        }

        return 0;

    }

    int matrix_real(matrix_obj * dest, const matrix_obj * src) {

        if (dest->nRows != src->nRows) { return -1; }
        if (dest->nCols != src->nCols) { return -1; }

        memcpy(dest->real, src->real, sizeof(float) * src->nRows * src->nCols);
        memset(dest->imag, 0x00, sizeof(float) * src->nRows * src->nCols);

        return 0;

    }

    int matrix_imag(matrix_obj * dest, const matrix_obj * src) {

        if (dest->nRows != src->nRows) { return -1; }
        if (dest->nCols != src->nCols) { return -1; }

        memset(dest->real, 0x00, sizeof(float) * src->nRows * src->nCols);
        memcpy(dest->imag, src->imag, sizeof(float) * src->nRows * src->nCols);

        return 0;

    }

    int matrix_norm(const matrix_obj * obj, const unsigned int p, float * norm) {

        unsigned int iRow, iCol;
        float real, imag;
        float total;

        if (p == 0) { return -1; }

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                real = obj->real[iRow * obj->nCols + iCol];
                imag = obj->imag[iRow * obj->nCols + iCol];

                total = powf(sqrtf(real * real + imag * imag), (float) p);

            }

        }

        total = powf(total, 1.0/((float) p));

        return 0;

    }

    int matrix_symm(const matrix_obj * obj, char * symm) {

        unsigned int iRow, iCol;
        unsigned int iRow1, iCol1;
        unsigned int iRow2, iCol2;
        float real1, imag1;
        float real2, imag2;
        float realD, imagD;
        float total;
        const float epsilon = 1E-20;

        total = 0.0f;

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = (iRow+1); iCol < obj->nCols; iCol++) {

                iRow1 = iRow;
                iCol1 = iCol;
                iRow2 = iCol;
                iCol2 = iRow;

                real1 = obj->real[iRow1 * obj->nCols + iCol1];
                imag1 = obj->imag[iRow1 * obj->nCols + iCol1];
                real2 = obj->real[iRow2 * obj->nCols + iCol2];
                imag2 = obj->imag[iRow2 * obj->nCols + iCol2];

                realD = real1-real2;
                imagD = imag1+imag2;

                total += realD*realD + imagD*imagD;

            }

        }

        total /= ((float) (obj->nRows * obj->nCols));

        if (total < epsilon) {
            *symm = 1;
        }
        else {
            *symm = 0;
        }

        return 0;

    }

    int matrix_tril(const matrix_obj * obj, char * tril) {

        unsigned int iRow, iCol;
        float real, imag;
        float total;
        const float epsilon = 1E-20;

        for (iRow = 1; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < iRow; iCol++) {

                real = obj->real[iRow * obj->nCols + iCol];
                imag = obj->imag[iRow * obj->nCols + iCol];

                total += real*real + imag*imag;

            }

        }

        total /= ((float) (obj->nRows * obj->nCols));

        if (total < epsilon) {
            *tril = 1;
        }
        else {
            *tril = 0;
        }

        return 0;

    }

    void matrix_printf(const matrix_obj * obj) {

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

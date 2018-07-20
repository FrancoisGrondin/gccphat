#ifndef __GCCPHATSVD_UTILS_MATRIX
#define __GCCPHATSVD_UTILS_MATRIX

   /**
    * \file         matrix.h
    * \author       Francois Grondin (fgrondin@mit.edu)
    * \version      1.0
    * \date         2018-07-13
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */

    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
        
    typedef struct matrix_obj {

        float * array;
        unsigned int M;
        unsigned int N;

    } matrix_obj;

    matrix_obj * matrix_construct(const unsigned int M, const unsigned int N);

    void matrix_destroy(matrix_obj * obj);   


    float matrix_get(const matrix_obj * obj, const unsigned int m, const unsigned int n);

    void matrix_set(const matrix_obj * obj, const unsigned int m, const unsigned int n, const float value);


    void matrix_copy(matrix_obj * dest, const matrix_obj * src);

    void matrix_transpose(matrix_obj * dest, const matrix_obj * src);

    void matrix_eye(matrix_obj * obj);

    void matrix_zero(matrix_obj * obj);


    void matrix_add(matrix_obj * dest, const matrix_obj * src1, const matrix_obj * src2);

    void matrix_sub(matrix_obj * dest, const matrix_obj * src1, const matrix_obj * src2);

    void matrix_mul(matrix_obj * dest, const matrix_obj * src1, const matrix_obj * src2);

    void matrix_had(matrix_obj * dest, const matrix_obj * src1, const matrix_obj * src2);


    void matrix_printf(const matrix_obj * obj);

#endif
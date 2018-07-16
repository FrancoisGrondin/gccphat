#ifndef __GCCPHAT_UTILS_HOUSEHOLDER
#define __GCCPHAT_UTILS_HOUSEHOLDER

   /**
    * \file         householder.h
    * \author       Francois Grondin (fgrondin@mit.edu)
    * \version      1.0
    * \date         2018-07-14
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

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <gccphat/utils/matrix.h>
    #include <gccphat/utils/scalar.h>
    #include <gccphat/utils/vector.h>

    typedef struct householder_obj {

        unsigned int M;
        unsigned int N;

        vector_obj * e1;
        vector_obj * alpha_e1;
        vector_obj * x;
        vector_obj * u;
        vector_obj * v;

        matrix_obj * V;
        matrix_obj * VH;
        matrix_obj * VVH;
        matrix_obj * twoVVH;
        matrix_obj * I;

    } householder_obj;


    householder_obj * householder_construct(const unsigned int M, const unsigned int N);

    void householder_destroy(householder_obj * obj);   


    int householder_process(householder_obj * obj, const matrix_obj * A, matrix_obj * Q);
    

#endif
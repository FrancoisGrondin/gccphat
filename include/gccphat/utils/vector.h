#ifndef __GCCPHAT_UTILS_VECTOR
#define __GCCPHAT_UTILS_VECTOR

   /**
    * \file         vector.h
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
    #include <gccphat/utils/scalar.h>
    
    typedef struct vector_obj {

        float * real;
        float * imag;
        unsigned int nElements;

    } vector_obj;


    vector_obj * vector_construct(const unsigned int nElements);

    void vector_destroy(vector_obj * obj);   


    int vector_copy(vector_obj * dest, const vector_obj * src);


    int vector_get(vector_obj * obj, const unsigned int iElement, scalar_struct * scalar);

    int vector_set(vector_obj * obj, const unsigned int iElement, const scalar_struct * scalar);


    int vector_zero(vector_obj * obj);


    int vector_dot(scalar_struct * dest, const vector_obj * src1, const vector_obj * src2);
    
    int vector_inner(scalar_struct * dest, const vector_obj * src1, const vector_obj * src2);

    int vector_norm(float * dest, const vector_obj * src);


    int vector_add(vector_obj * dest, const vector_obj * src1, const vector_obj * src2);

    int vector_sub(vector_obj * dest, const vector_obj * src1, const vector_obj * src2);

    int vector_scale(vector_obj * dest, const vector_obj * src, const scalar_struct * scale);

    int vector_normalize(vector_obj * dest, const vector_obj * src);


    void vector_printf(vector_obj * obj);

#endif
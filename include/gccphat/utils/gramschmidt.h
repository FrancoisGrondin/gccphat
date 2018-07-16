#ifndef __GCCPHAT_UTILS_GRAMSCHMIDT
#define __GCCPHAT_UTILS_GRAMSCHMIDT

   /**
    * \file         gramschmidt.h
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
    #include <gccphat/utils/vector.h>

    typedef struct gramschmidt_obj {

        unsigned int N;
        vector_obj ** as;
        vector_obj ** us;
        vector_obj ** es;
        vector_obj * u1;
        vector_obj * u2;

    } gramschmidt_obj;


    gramschmidt_obj * gramschmidt_construct(const unsigned int N);

    void gramschmidt_destroy(gramschmidt_obj * obj);   


    int gramschmidt_process(gramschmidt_obj * obj, const matrix_obj * A, matrix_obj * E);
    

#endif
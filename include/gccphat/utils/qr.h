#ifndef __GCCPHAT_UTILS_QR
#define __GCCPHAT_UTILS_QR

   /**
    * \file         qr.h
    * \author       Francois Grondin (fgrondin@mit.edu)
    * \version      1.0
    * \date         2018-07-16
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
    #include <gccphat/utils/householder.h>
    #include <gccphat/utils/matrix.h>
    #include <gccphat/utils/scalar.h>
    #include <gccphat/utils/vector.h>

    typedef struct qr_obj {

        unsigned int M;
        unsigned int N;
        unsigned int T;

        matrix_obj ** Qs;
        matrix_obj ** Qps;
        matrix_obj ** As;
        matrix_obj ** Aps;
        
        matrix_obj * QT;
        matrix_obj * Qp;
        matrix_obj * Rp;

        householder_obj ** householders;

    } qr_obj;

    qr_obj * qr_construct(const unsigned int M, const unsigned int N);

    void qr_destroy(qr_obj * obj);

    int qr_process(qr_obj * obj, const matrix_obj * A, matrix_obj * Q, matrix_obj * R);

#endif
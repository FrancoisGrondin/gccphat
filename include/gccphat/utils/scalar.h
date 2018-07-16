#ifndef __GCCPHAT_UTILS_SCALAR
#define __GCCPHAT_UTILS_SCALAR

   /**
    * \file         scalar.h
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

    typedef struct scalar_struct {

        float real;
        float imag;

    } scalar_struct;

    scalar_struct scalar_add(scalar_struct a, scalar_struct b);

    scalar_struct scalar_sub(scalar_struct a, scalar_struct b);

    scalar_struct scalar_mul(scalar_struct a, scalar_struct b);

    scalar_struct scalar_div(scalar_struct a, scalar_struct b);

    scalar_struct scalar_inv(scalar_struct a);

    scalar_struct scalar_conj(scalar_struct a);

    float scalar_getAmplitude(scalar_struct a);

    float scalar_getPhase(scalar_struct a);

    scalar_struct scalar_setPhasor(const float amplitude, const float phase);

#endif
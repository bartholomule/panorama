/*
*  Copyright (C) 1998, 2000 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  and Kevin Harris 
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful, but
*  WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef _ROOT_SOLVER__
#define _ROOT_SOLVER__

// NOTE: (Kevin Harris 13Aug2000) -- For more solvers (entierly generic in
// type although slower than the solvers provided for the low order solvers
// here), see the file 'solvers.h'. 

int SolveQuadric (double c[3], double s[2]);
int SolveCubic (double c[4], double s[3]);
int SolveQuartic (double c[5], double s[4]);

// Safe versions of the above functions to solve a polynomial equation of low
// order.  Unlike the above, they will check the high order terms to see if
// they are zero.  If so, they will call the safe version of the next lower
// order solver, otherwise they will call the correct solver (from above).
// (KH 11Aug2000)
int SafeSolveLinear  (double c[2], double s[1]);
int SafeSolveQuadric (double c[3], double s[2]);
int SafeSolveCubic   (double c[4], double s[3]);
int SafeSolveQuartic (double c[5], double s[4]);
			  

#include <vector>

// Solve a polynomial equation of any size.  Note that it is not guaranteed
// (although this would be nice) to find *all* zeros of the polynomial. Under
// many circumstances, this will find all of the zeros to the polynomial.  For
// polynomials with order <= 4, it will call one of the above defined solvers.
int SolveEquation (const vector<double>& coefs, vector<double>& solutions);

#endif  /* _RT_ROOT_SOLVER__ */

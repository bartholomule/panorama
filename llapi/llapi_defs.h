/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _LLAPI_DEFS__
#define _LLAPI_DEFS__

#include <cfloat>
#include "llapi/vector2d.h"
#include "llapi/vector3d.h"
#include "llapi/frame.h"
#include "llapi/matrix.h"
#include "llapi/interval.h"
#include "llapi/quaternion.h"

//
// Minimum distance between scalar values
//
#define FX_EPSILON (1e-5)

//
// Huge scalar value
//
#define FX_HUGE (1e8)

//
// Base type used in coordinates and limit values of this type
//
typedef double   TScalar;

#define SCALAR_MAX            DBL_MAX
#define SCALAR_MIN            DBL_MIN

//
// Template instances & specific types used in this program
//
typedef TVector3D<TScalar>          TVector;
typedef TVector2D<TScalar>          TVector2;
typedef TBaseMatrix<TScalar>        TMatrix;
typedef TBaseInterval<TScalar>      TInterval;
typedef quaternion<TScalar>         TQuaternion;
typedef TFrame<float>               TZBuffer;
typedef TFrame<TVector>             TNBuffer;

//
// Default index of refraction for medium
//
#define FX_MEDIUM_IOR          (1)

//
// Buffer flags
//
#define FX_ZBUFFER       (1)
#define FX_NBUFFER       (2)

#endif  /* _LLAPI_DEFS__ */

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

#ifndef LLAPI_DEFS_H_INCLUDED
#define LLAPI_DEFS_H_INCLUDED

#include <limits>
#include <cfloat>

#include "llapi/vector2.hpp"
#include "llapi/vector3.hpp"
#include "llapi/point2.hpp"
#include "llapi/point3.hpp"
#include "llapi/mat_4x4.hpp"
#include "llapi/quaternion.hpp"
#include "llapi/frame.h"
#include "llapi/interval.h"

namespace panorama
{
  //
  // Base type used in coordinates and limit values of this type
  //
  typedef double TScalar;

  //
  // Minimum distance between scalar values
  //
  const TScalar FX_EPSILON = std::numeric_limits<TScalar>::epsilon();

  //
  // Huge scalar value
  //
  const TScalar FX_HUGE = std::numeric_limits<TScalar>::max() / 4;

  const TScalar SCALAR_MAX = std::numeric_limits<TScalar>::max();
  const TScalar SCALAR_MIN = std::numeric_limits<TScalar>::min();

  //
  // Template instances & specific types used in this program
  //
  typedef vector3<TScalar> TVector;
  typedef vector2<TScalar> TVector2;
  typedef point3<TScalar> TPoint;
  typedef point2<TScalar> TPoint2;
  typedef matrix_4x4<TScalar> TMatrix;
  typedef quaternion<TScalar> TQuaternion;
  typedef TBaseInterval<TScalar> TInterval;
  typedef TFrame<float> TZBuffer;
  typedef TFrame<TVector> TNBuffer;

  //
  // Default index of refraction for medium
  //
  const TScalar FX_MEDIUM_IOR = 1;

  //
  // Buffer flags
  //
  enum EBufferType
  {
    FX_ZBUFFER = 1,
    FX_NBUFFER = 2
  };

} // end namespace panorama

#endif  /* LLAPI_DEFS_H_INCLUDED */

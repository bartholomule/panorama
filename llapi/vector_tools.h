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

#ifndef _VECTOR__
#define _VECTOR__

#include "llapi/llapi_defs.h"

inline TVector vrand (void)
{

  return TVector (srand(), srand(), srand());
  
}  /* vrand() */


inline TVector RandomVectorInSphere (void)
{

  float     fAlpha   = frand() * 2 * PI;
  float     fBeta    = frand() * PI;
  float     fSinBeta = sin (fBeta);
  TVector   tSol (cos (fAlpha) * fSinBeta, cos (fBeta), sin (fAlpha) * fSinBeta);
  
  return tSol;
  
}  /* RandomVectorInSphere() */


inline Byte Crossings (const TVector2& rktPOINT1, const TVector2& rktPOINT2)
{

  TScalar   tCoordX;
  
  if ( ( ( rktPOINT1.y() >= 0 ) && ( rktPOINT2.y() >= 0 ) ) ||
       ( ( rktPOINT1.y() < 0 ) && ( rktPOINT2.y() < 0 ) ) )
  {
    return 0;
  }

  if ( rktPOINT1.x() == rktPOINT2.x() )
  {
    return ( rktPOINT1.x() > 0 ) ? 1 : 0;
  }

  tCoordX = rktPOINT1.x() + (-rktPOINT1.y() * (rktPOINT2.x() - rktPOINT1.x())) /
                            (rktPOINT2.y() - rktPOINT1.y());

  return ( tCoordX > 0 ) ? 1 : 0;

}  /* Crossings() */


inline Byte Dominant (const TVector& rktVECTOR)
{

  Byte      bDom;
  TScalar   v1 = fabs (rktVECTOR.x());
  TScalar   v2 = fabs (rktVECTOR.y());
  TScalar   v3 = fabs (rktVECTOR.z());
  
  if ( v1 > v2 )
  {
    bDom = ( v1 > v3 ) ? 0 : 2;
  }
  else
  {
    bDom = ( v2 > v3 ) ? 1 : 2;
  }

  return bDom;
  
}  /* Dominant() */


template <class TItem>
inline TVector2D<TItem> Convert3DTo2D (const TVector3D<TItem>& rktVECTOR, Byte bPOS)
{

  TVector2D<TItem>   tVector;

  tVector [0] = ( bPOS == 0 ) ? rktVECTOR.y() : rktVECTOR.x();
  tVector [1] = ( ( bPOS == 1 ) || ( bPOS == 0 ) ) ? rktVECTOR.z() : rktVECTOR.y();

  return tVector;

}  /* Convert3DTo2D() */


template <class TItem>
inline TVector3D<TItem> Convert2DTo3D (const TVector2D<TItem>& rktVECTOR, Byte bPOS)
{

  TVector3D<TItem>   tVector;

  tVector [0] = ( bPOS == 0 ) ? 0 : rktVECTOR.x();
  tVector [1] = ( bPOS == 1 ) ? 0 : (( bPOS == 0 ) ? rktVECTOR.y() : rktVECTOR.x());
  tVector [2] = ( bPOS == 2 ) ? 0 : rktVECTOR.y();

  return tVector;

}  /* Convert2DTo3D */

#endif  /* _VECTOR__ */

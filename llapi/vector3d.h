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

#ifndef _VECTOR_3D__
#define _VECTOR_3D__

#include <cassert>
#include <cmath>
#include <iostream>
#include "llapi/base_class.h"
#include "llapi/machine.h"
#include "llapi/math_tools.h"

template <class TItem>
class TBaseMatrix;

template <class TItem>
class TVector3D : public TBaseClass
{

  protected:

    TItem   vx, vy, vz;

  public:

    TVector3D (TItem X = 0, TItem Y = 0, TItem Z = 0) :
      vx (X), vy (Y), vz (Z) {}

    TVector3D (const TVector3D& rktVECTOR) :
      vx (rktVECTOR.x()), vy (rktVECTOR.y()), vz (rktVECTOR.z()) {}

    TVector3D& operator = (const TVector3D& rktVECTOR)
    {
      vx = rktVECTOR.x();
      vy = rktVECTOR.y();
      vz = rktVECTOR.z();
      
      return *this;
    }

    TItem& operator [] (Byte bVAL)
    {
      assert ( bVAL < 3 );
      
      return ( bVAL == 0 ) ? vx : (( bVAL == 1 ) ? vy : vz);
    }

    TItem operator [] (Byte bVAL) const
    {
      assert ( bVAL < 3 );

      return ( bVAL == 0 ) ? vx : (( bVAL == 1 ) ? vy : vz);
    }

    TItem x (void) const { return vx; }
    TItem y (void) const { return vy; }
    TItem z (void) const { return vz; }

    void set (TItem X = 0, TItem Y = 0, TItem Z = 0)
    {
      vx = X;
      vy = Y;
      vz = Z;
    }

    void setX (TItem X = 0)
    {
      vx = X;
    }

    void setY (TItem Y = 0)
    {
      vy = Y;
    }

    void setZ (TItem Z = 0)
    {
      vz = Z;
    }

    TVector3D<TItem>& operator += (const TVector3D<TItem>& rktVECTOR);
    TVector3D<TItem>& operator -= (const TVector3D<TItem>& rktVECTOR);
    TVector3D<TItem>& operator *= (const TVector3D<TItem>& rktVECTOR);
    TVector3D<TItem>& operator /= (const TVector3D<TItem>& rktVECTOR);
    
    TVector3D<TItem>& operator += (TItem tITEM);
    TVector3D<TItem>& operator -= (TItem tITEM);
    TVector3D<TItem>& operator *= (TItem tITEM);
    TVector3D<TItem>& operator /= (TItem tITEM);
    
    TItem norm (void) const;

    void normalize (void);

    void applyTransform (const TBaseMatrix<TItem>* pktMATRIX);

    void printDebug (void) const;

    EClass classType (void) const { return FX_VECTOR_CLASS; }
    string className (void) const { return "Vector"; }
    
};  /* class TVector3D */


template <class TItem>
inline TItem TVector3D<TItem>::norm (void) const
{

  return sqrt (vx * vx + vy * vy + vz * vz);

}  /* norm() */


template <class TItem>
inline void TVector3D<TItem>::normalize (void)
{

  TItem   tNorm = norm();

  assert ( tNorm > 0.0 );
  
  vx /= tNorm;
  vy /= tNorm;
  vz /= tNorm;

}  /* normalize() */


template <class TItem>
inline void TVector3D<TItem>::applyTransform (const TBaseMatrix<TItem>* pktMATRIX)
{

  if ( pktMATRIX )
  {
    TItem   tx, ty, tz;
  
    tx = pktMATRIX->atElement[0][0] * vx +
         pktMATRIX->atElement[1][0] * vy +
         pktMATRIX->atElement[2][0] * vz;

    ty = pktMATRIX->atElement[0][1] * vx +
         pktMATRIX->atElement[1][1] * vy +
         pktMATRIX->atElement[2][1] * vz;

    tz = pktMATRIX->atElement[0][2] * vx +
         pktMATRIX->atElement[1][2] * vy +
         pktMATRIX->atElement[2][2] * vz;

    vx = tx;
    vy = ty;
    vz = tz;
  }

}  /* applyTransform() */

                                
template <class TItem>
inline void TVector3D<TItem>::printDebug (void) const
{

  cerr << "TVector3D <" << vx << ", " << vy << ", " << vz << ">" << endl;

}  /* printDebug() */


template <class TItem>
inline TVector3D<TItem>& TVector3D<TItem>::operator += (const TVector3D<TItem>& rktVECTOR)
{

  vx += rktVECTOR.x();
  vy += rktVECTOR.y();
  vz += rktVECTOR.z();

  return *this;

}  /* operator += () */


template <class TItem>
inline TVector3D<TItem>& TVector3D<TItem>::operator -= (const TVector3D<TItem>& rktVECTOR)
{

  vx -= rktVECTOR.x();
  vy -= rktVECTOR.y();
  vz -= rktVECTOR.z();

  return *this;

}  /* operator -= () */


template <class TItem>
inline TVector3D<TItem>& TVector3D<TItem>::operator *= (const TVector3D<TItem>& rktVECTOR)
{

  vx *= rktVECTOR.x();
  vy *= rktVECTOR.y();
  vz *= rktVECTOR.z();

  return *this;

}  /* operator *= () */


template <class TItem>
inline TVector3D<TItem>& TVector3D<TItem>::operator /= (const TVector3D<TItem>& rktVECTOR)
{

  vx /= rktVECTOR.x();
  vy /= rktVECTOR.y();
  vz /= rktVECTOR.z();

  return *this;

}  /* operator /= () */


template <class TItem>
inline TVector3D<TItem>& TVector3D<TItem>::operator += (TItem tITEM)
{

  vx += tITEM;
  vy += tITEM;
  vz += tITEM;

  return *this;

}  /* operator += () */


template <class TItem>
inline TVector3D<TItem>& TVector3D<TItem>::operator -= (TItem tITEM)
{

  vx -= tITEM;
  vy -= tITEM;
  vz -= tITEM;

  return *this;

}  /* operator -= () */


template <class TItem>
inline TVector3D<TItem>& TVector3D<TItem>::operator *= (TItem tITEM)
{

  vx *= tITEM;
  vy *= tITEM;
  vz *= tITEM;

  return *this;

}  /* operator *= () */


template <class TItem>
inline TVector3D<TItem>& TVector3D<TItem>::operator /= (TItem tITEM)
{

  vx /= tITEM;
  vy /= tITEM;
  vz /= tITEM;

  return *this;

}  /* operator /= () */


template <class TItem>
inline TVector3D<TItem> operator - (const TVector3D<TItem>& rktVECTOR)
{

  return TVector3D<TItem> (-rktVECTOR.x(), -rktVECTOR.y(), -rktVECTOR.z());

}  /* operator - () */


template <class TItem>
inline TVector3D<TItem> operator - (const TVector3D<TItem>& rktVECTOR1, const TVector3D<TItem>& rktVECTOR2)
{

  return TVector3D<TItem> (rktVECTOR1.x() - rktVECTOR2.x(),
                           rktVECTOR1.y() - rktVECTOR2.y(),
                           rktVECTOR1.z() - rktVECTOR2.z());

}  /* operator - () */


template <class TItem>
inline TVector3D<TItem> operator + (const TVector3D<TItem>& rktVECTOR1, const TVector3D<TItem>& rktVECTOR2)
{

  return TVector3D<TItem> (rktVECTOR1.x() + rktVECTOR2.x(),
                           rktVECTOR1.y() + rktVECTOR2.y(),
                           rktVECTOR1.z() + rktVECTOR2.z());

}  /* operator + () */


template <class TItem>
inline TVector3D<TItem> operator * (const TVector3D<TItem>& rktVECTOR1, const TVector3D<TItem>& rktVECTOR2)
{

  return TVector3D<TItem> (rktVECTOR1.x() * rktVECTOR2.x(),
                           rktVECTOR1.y() * rktVECTOR2.y(),
                           rktVECTOR1.z() * rktVECTOR2.z());

}  /* operator * () */


template <class TItem>
inline TVector3D<TItem> operator / (const TVector3D<TItem>& rktVECTOR1, const TVector3D<TItem>& rktVECTOR2)
{

  return TVector3D<TItem> (rktVECTOR1.x() / rktVECTOR2.x(),
                           rktVECTOR1.y() / rktVECTOR2.y(),
                           rktVECTOR1.z() / rktVECTOR2.z());

}  /* operator / () */


template <class TItem>
inline TVector3D<TItem> operator / (const TVector3D<TItem>& rktVECTOR, TItem tITEM)
{

  return TVector3D<TItem> (rktVECTOR.x() / tITEM,
                           rktVECTOR.y() / tITEM,
                           rktVECTOR.z() / tITEM);

}  /* operator / () */


template <class TItem>
inline TVector3D<TItem> operator * (const TVector3D<TItem>& rktVECTOR, TItem tITEM)
{

  return TVector3D<TItem> (rktVECTOR.x() * tITEM,
                           rktVECTOR.y() * tITEM,
                           rktVECTOR.z() * tITEM);

}  /* operator * () */


template <class TItem>
inline TVector3D<TItem> operator * (TItem tITEM, const TVector3D<TItem>& rktVECTOR)
{

  return rktVECTOR * tITEM;

}  /* operator * () */


template <class TItem>
inline TItem Distance (const TVector3D<TItem>& rktVECTOR1, const TVector3D<TItem>& rktVECTOR2)
{

  return (TVector3D<TItem> (rktVECTOR2 - rktVECTOR1)).norm();

}  /* Distance() */


template <class TItem>
inline TItem dotProduct (const TVector3D<TItem>& rktVECTOR1, const TVector3D<TItem>& rktVECTOR2)
{

  return ( rktVECTOR1.x() * rktVECTOR2.x() +
           rktVECTOR1.y() * rktVECTOR2.y() +
           rktVECTOR1.z() * rktVECTOR2.z() );

}  /* dotProduct() */


template <class TItem>
inline bool operator == (const TVector3D<TItem>& rktVECTOR1, const TVector3D<TItem>& rktVECTOR2)
{

  return ( (rktVECTOR1.x() == rktVECTOR2.x()) &&
           (rktVECTOR1.y() == rktVECTOR2.y()) &&
           (rktVECTOR1.z() == rktVECTOR2.z()) );

}  /* operator == () */


template <class TItem>
inline bool operator != (const TVector3D<TItem>& rktVECTOR1, const TVector3D<TItem>& rktVECTOR2)
{

  return ( (rktVECTOR1.x() != rktVECTOR2.x()) ||
           (rktVECTOR1.y() != rktVECTOR2.y()) ||
           (rktVECTOR1.z() != rktVECTOR2.z()) );

}  /* operator |= () */


template <class TItem>
inline TVector3D<TItem> crossProduct (const TVector3D<TItem>& rktVECTOR1, const TVector3D<TItem>& rktVECTOR2)
{

  return TVector3D<TItem> (rktVECTOR1.y() * rktVECTOR2.z() - rktVECTOR1.z() * rktVECTOR2.y(),
                           rktVECTOR1.z() * rktVECTOR2.x() - rktVECTOR1.x() * rktVECTOR2.z(),
                           rktVECTOR1.x() * rktVECTOR2.y() - rktVECTOR1.y() * rktVECTOR2.x());

}  /* crossProduct() */

#endif  /* _VECTOR_3D__ */

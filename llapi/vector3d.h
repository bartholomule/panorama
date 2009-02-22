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

#ifndef VECTOR3D_H_INCLUDED
#define VECTOR3D_H_INCLUDED

#if defined(FX_NO_BOUNDS_CHECKING)
#include <cassert>
#endif

#include <cmath>
#include <iostream>
#include "llapi/base_class.h"
#include "llapi/machine.h"
#include "llapi/math_tools.h"
#include "generic/magic_pointer.h"

namespace panorama
{
  template <class TItem>
  class TBaseMatrix;

  template <class TItem>
  class TVector3D : public TBaseClass
  {

  protected:
    /* class that has 3 Ts stored directly */
    struct vector3_direct { TItem x; TItem y; TItem z; };
    /* class that has 3 Ts stored in an array */
    struct vector3_array { TItem coords[3]; };
    /* union to allow accesses to both indirectly through an array, and
       directly athrough a name, without adding any extra processing time or
       space requirements */
    union  vector3_union
    {
      vector3_union() {}
      vector3_union(TItem x, TItem y, TItem z)
      {
        direct.x = x;
        direct.y = y;
        direct.z = z;
      }
      inline TItem& operator[](Byte index)      { return(array.coords[index]); }
      inline TItem  operator[](Byte index)const { return(array.coords[index]); }
      vector3_direct direct;
      vector3_array  array;
    };

    vector3_union vec;

    //  TItem   vx, vy, vz;

  public:

    TVector3D (TItem X = 0, TItem Y = 0, TItem Z = 0) :
      vec(X, Y, Z) { }

    TVector3D (const TVector3D& rktVECTOR) :
      vec (rktVECTOR.x(), rktVECTOR.y(), rktVECTOR.z()) {}

    TVector3D& operator = (const TVector3D& rktVECTOR)
    {
      vec.direct.x = rktVECTOR.x();
      vec.direct.y = rktVECTOR.y();
      vec.direct.z = rktVECTOR.z();

      return *this;
    }

    TItem& operator [] (Byte bVAL)
    {
#if !defined(FX_NO_BOUNDS_CHECKING)
      assert ( bVAL < 3 );
#endif

      return vec[bVAL];
    }

    TItem operator [] (Byte bVAL) const
    {
#if !defined(FX_NO_BOUNDS_CHECKING)
      assert ( bVAL < 3 );
#endif

      return vec[bVAL];
    }

    inline TItem x (void) const { return vec.direct.x; }
    inline TItem y (void) const { return vec.direct.y; }
    inline TItem z (void) const { return vec.direct.z; }
    inline TItem& x (void) { return vec.direct.x; }
    inline TItem& y (void) { return vec.direct.y; }
    inline TItem& z (void) { return vec.direct.z; }

    void set (TItem X = 0, TItem Y = 0, TItem Z = 0)
    {
      vec.direct.x = X;
      vec.direct.y = Y;
      vec.direct.z = Z;
    }

    void setX (TItem X = 0)
    {
      vec.direct.x = X;
    }

    void setY (TItem Y = 0)
    {
      vec.direct.y = Y;
    }

    void setZ (TItem Z = 0)
    {
      vec.direct.z = Z;
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

    void applyTransform (const magic_pointer<TBaseMatrix<TItem> > pktMATRIX);
    void applyTransform (const TBaseMatrix<TItem>& rktMATRIX);

    EClass classType (void) const { return FX_VECTOR_CLASS; }
    std::string className (void) const { return "Vector"; }

  };  /* class TVector3D */


  template <class TItem>
  inline TItem TVector3D<TItem>::norm (void) const
  {

    return sqrt (x() * x() + y() * y() + z() * z());

  }  /* norm() */


  template <class TItem>
  inline void TVector3D<TItem>::normalize (void)
  {

    TItem   tNorm = norm();

    assert ( tNorm > 0.0 );

    vec.direct.x /= tNorm;
    vec.direct.y /= tNorm;
    vec.direct.z /= tNorm;

  }  /* normalize() */


  template <class TItem>
  inline void TVector3D<TItem>::applyTransform (const magic_pointer<TBaseMatrix<TItem> > pktMATRIX)
  {

    if ( pktMATRIX )
    {
      TItem   tx, ty, tz;

      tx = pktMATRIX->atElement[0][0] * x() +
        pktMATRIX->atElement[1][0] * y() +
        pktMATRIX->atElement[2][0] * z();

      ty = pktMATRIX->atElement[0][1] * x() +
        pktMATRIX->atElement[1][1] * y() +
        pktMATRIX->atElement[2][1] * z();

      tz = pktMATRIX->atElement[0][2] * x() +
        pktMATRIX->atElement[1][2] * y() +
        pktMATRIX->atElement[2][2] * z();

      vec.direct.x = tx;
      vec.direct.y = ty;
      vec.direct.z = tz;
    }

  }  /* applyTransform() */

  template <class TItem>
  inline void TVector3D<TItem>::applyTransform (const TBaseMatrix<TItem>& rktMATRIX)
  {

    TItem   tx, ty, tz;

    tx = rktMATRIX.atElement[0][0] * x() +
      rktMATRIX.atElement[1][0] * y() +
      rktMATRIX.atElement[2][0] * z();

    ty = rktMATRIX.atElement[0][1] * x() +
      rktMATRIX.atElement[1][1] * y() +
      rktMATRIX.atElement[2][1] * z();

    tz = rktMATRIX.atElement[0][2] * x() +
      rktMATRIX.atElement[1][2] * y() +
      rktMATRIX.atElement[2][2] * z();

    vec.direct.x = tx;
    vec.direct.y = ty;
    vec.direct.z = tz;

  }  /* applyTransform() */

  template <class TItem>
  inline TVector3D<TItem>& TVector3D<TItem>::operator += (const TVector3D<TItem>& rktVECTOR)
  {

    vec.direct.x += rktVECTOR.x();
    vec.direct.y += rktVECTOR.y();
    vec.direct.z += rktVECTOR.z();

    return *this;

  }  /* operator += () */


  template <class TItem>
  inline TVector3D<TItem>& TVector3D<TItem>::operator -= (const TVector3D<TItem>& rktVECTOR)
  {

    vec.direct.x -= rktVECTOR.x();
    vec.direct.y -= rktVECTOR.y();
    vec.direct.z -= rktVECTOR.z();

    return *this;

  }  /* operator -= () */


  template <class TItem>
  inline TVector3D<TItem>& TVector3D<TItem>::operator *= (const TVector3D<TItem>& rktVECTOR)
  {

    vec.direct.x *= rktVECTOR.x();
    vec.direct.y *= rktVECTOR.y();
    vec.direct.z *= rktVECTOR.z();

    return *this;

  }  /* operator *= () */


  template <class TItem>
  inline TVector3D<TItem>& TVector3D<TItem>::operator /= (const TVector3D<TItem>& rktVECTOR)
  {

    vec.direct.x /= rktVECTOR.x();
    vec.direct.y /= rktVECTOR.y();
    vec.direct.z /= rktVECTOR.z();

    return *this;

  }  /* operator /= () */


  template <class TItem>
  inline TVector3D<TItem>& TVector3D<TItem>::operator += (TItem tITEM)
  {

    vec.direct.x += tITEM;
    vec.direct.y += tITEM;
    vec.direct.z += tITEM;

    return *this;

  }  /* operator += () */


  template <class TItem>
  inline TVector3D<TItem>& TVector3D<TItem>::operator -= (TItem tITEM)
  {

    vec.direct.x -= tITEM;
    vec.direct.y -= tITEM;
    vec.direct.z -= tITEM;

    return *this;

  }  /* operator -= () */


  template <class TItem>
  inline TVector3D<TItem>& TVector3D<TItem>::operator *= (TItem tITEM)
  {

    vec.direct.x *= tITEM;
    vec.direct.y *= tITEM;
    vec.direct.z *= tITEM;

    return *this;

  }  /* operator *= () */


  template <class TItem>
  inline TVector3D<TItem>& TVector3D<TItem>::operator /= (TItem tITEM)
  {

    vec.direct.x /= tITEM;
    vec.direct.y /= tITEM;
    vec.direct.z /= tITEM;

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

  template <class TItem>
  inline ostream& operator<<(ostream& o, const TVector3D<TItem>& vec)
  {
    o << "<" << vec.x() << "," << vec.y() << "," << vec.z() << ">";
    return o;
  } /* operator << */
}

#endif  /* VECTOR3D_H_INCLUDED */

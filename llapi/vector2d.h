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

#ifndef _VECTOR_2D__
#define _VECTOR_2D__

#include <cassert>
#include <iostream>
#include "llapi/machine.h"

template <class TItem>
class TVector2D
{

  protected:

    TItem   vx, vy;

  public:

    TVector2D (TItem X = 0, TItem Y = 0) :
      vx (X), vy (Y) {}

    TVector2D (const TVector2D& rktVECTOR) :
      vx (rktVECTOR.x()), vy (rktVECTOR.y()) {}

    TVector2D& operator = (const TVector2D& rktVECTOR)
    {
      vx = rktVECTOR.x();
      vy = rktVECTOR.y();

      return *this;
    }

    TItem& operator [] (Byte bVAL)
    {
      assert ( bVAL < 2 );
      
      return ( bVAL == 0 ) ? vx : vy;
    }

    TItem operator [] (Byte bVAL) const
    {
      assert ( bVAL < 2 );
      
      return ( bVAL == 0 ) ? vx : vy;
    }

    TItem x (void) const { return vx; }
    TItem y (void) const { return vy; }

    void set (TItem X = 0, TItem Y = 0)
    {
      vx = X;
      vy = Y;
    }

    TVector2D<TItem>& operator += (const TVector2D<TItem>& rktVECTOR);
    TVector2D<TItem>& operator -= (const TVector2D<TItem>& rktVECTOR);
    TVector2D<TItem>& operator *= (const TVector2D<TItem>& rktVECTOR);
    TVector2D<TItem>& operator /= (const TVector2D<TItem>& rktVECTOR);
    
    TVector2D<TItem>& operator += (TItem tITEM);
    TVector2D<TItem>& operator -= (TItem tITEM);
    TVector2D<TItem>& operator *= (TItem tITEM);
    TVector2D<TItem>& operator /= (TItem tITEM);
    
    TItem norm (void) const;

    void normalize (void);

    void printDebug (void) const;

};  /* class TVector2D */


template <class TItem>
inline TItem TVector2D<TItem>::norm (void) const
{

  return sqrt (sqr (vx) + sqr (vy));

}  /* norm() */


template <class TItem>
inline void TVector2D<TItem>::normalize (void)
{

  TItem   tNorm = norm();

  vx /= tNorm;
  vy /= tNorm;

}  /* normalize() */


template <class TItem>
inline void TVector2D<TItem>::printDebug (void) const
{

  cerr << "TVector2D <" << vx << ", " << vy << ">" << endl;

}  /* printDebug() */


template <class TItem>
inline TVector2D<TItem>& TVector2D<TItem>::operator += (const TVector2D<TItem>& rktVECTOR)
{

  vx += rktVECTOR.x();
  vy += rktVECTOR.y();

  return *this;

}  /* operator += () */


template <class TItem>
inline TVector2D<TItem>& TVector2D<TItem>::operator -= (const TVector2D<TItem>& rktVECTOR)
{

  vx -= rktVECTOR.x();
  vy -= rktVECTOR.y();

  return *this;

}  /* operator -= () */


template <class TItem>
inline TVector2D<TItem>& TVector2D<TItem>::operator *= (const TVector2D<TItem>& rktVECTOR)
{

  vx *= rktVECTOR.x();
  vy *= rktVECTOR.y();

  return *this;

}  /* operator *= () */


template <class TItem>
inline TVector2D<TItem>& TVector2D<TItem>::operator /= (const TVector2D<TItem>& rktVECTOR)
{

  vx /= rktVECTOR.x();
  vy /= rktVECTOR.y();

  return *this;

}  /* operator /= () */


template <class TItem>
inline TVector2D<TItem>& TVector2D<TItem>::operator += (TItem tITEM)
{

  vx += tITEM;
  vy += tITEM;

  return *this;

}  /* operator += () */


template <class TItem>
inline TVector2D<TItem>& TVector2D<TItem>::operator -= (TItem tITEM)
{

  vx -= tITEM;
  vy -= tITEM;

  return *this;

}  /* operator -= () */


template <class TItem>
inline TVector2D<TItem>& TVector2D<TItem>::operator *= (TItem tITEM)
{

  vx *= tITEM;
  vy *= tITEM;

  return *this;

}  /* operator *= () */


template <class TItem>
inline TVector2D<TItem>& TVector2D<TItem>::operator /= (TItem tITEM)
{

  vx /= tITEM;
  vy /= tITEM;

  return *this;

}  /* operator /= () */


template <class TItem>
inline TVector2D<TItem> operator - (const TVector2D<TItem>& rktVECTOR)
{

  return TVector2D<TItem> (-rktVECTOR.x(), -rktVECTOR.y());

}  /* operator - () */


template <class TItem>
inline TVector2D<TItem> operator - (const TVector2D<TItem>& rktVECTOR1, const TVector2D<TItem>& rktVECTOR2)
{

  return TVector2D<TItem> (rktVECTOR1.x() - rktVECTOR2.x(), rktVECTOR1.y() - rktVECTOR2.y());

}  /* operator - () */


template <class TItem>
inline TVector2D<TItem> operator + (const TVector2D<TItem>& rktVECTOR1, const TVector2D<TItem>& rktVECTOR2)
{

  return TVector2D<TItem> (rktVECTOR1.x() + rktVECTOR2.x(), rktVECTOR1.y() + rktVECTOR2.y());

}  /* operator + () */


template <class TItem>
inline TVector2D<TItem> operator * (const TVector2D<TItem>& rktVECTOR1, const TVector2D<TItem>& rktVECTOR2)
{

  return TVector2D<TItem> (rktVECTOR1.x() * rktVECTOR2.x(), rktVECTOR1.y() * rktVECTOR2.y());

}  /* operator * () */


template <class TItem>
inline TVector2D<TItem> operator / (const TVector2D<TItem>& rktVECTOR, TItem tITEM)
{

  return TVector2D<TItem> (rktVECTOR.x() / tITEM, rktVECTOR.y() / tITEM);

}  /* operator / () */


template <class TItem>
inline TVector2D<TItem> operator * (const TVector2D<TItem>& rktVECTOR, TItem tITEM)
{

  return TVector2D<TItem> (rktVECTOR.x() * tITEM, rktVECTOR.y() * tITEM);

}  /* operator * () */


template <class TItem>
inline TVector2D<TItem> operator * (TItem tITEM, const TVector2D<TItem>& rktVECTOR)
{

  return rktVECTOR * tITEM;

}  /* operator * () */


template <class TItem>
inline TItem Distance (const TVector2D<TItem>& rktVECTOR1, const TVector2D<TItem>& rktVECTOR2)
{

  return (TVector2D<TItem> (rktVECTOR2 - rktVECTOR1)).norm();

}  /* Distance() */


template <class TItem>
inline TItem dotProduct (const TVector2D<TItem>& rktVEC1, const TVector2D<TItem>& rktVEC2)
{

  return (rktVEC1.vx * rktVEC2.vx +
          rktVEC1.vy * rktVEC2.vy);

}  /* dotProduct() */


template <class TItem>
inline bool operator == (const TVector2D<TItem>& rktVECTOR1, const TVector2D<TItem>& rktVECTOR2)
{

  return ( (rktVECTOR1.x() == rktVECTOR2.x()) &&
           (rktVECTOR1.y() == rktVECTOR2.y()) );

}  /* operator == () */


template <class TItem>
inline TVector2D<TItem> crossProduct (const TVector2D<TItem>& rktVECTOR1, const TVector2D<TItem>& rktVECTOR2)
{

  return TVector2D<TItem> (rktVECTOR1.x() * rktVECTOR2.y() - rktVECTOR1.y() * rktVECTOR2.x());

}  /* crossProduct() */

#endif  /* _VECTOR_2D__ */

/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _MATRIX__
#define _MATRIX__

#include <iostream>
#include "llapi/vector3d.h"
#include "llapi/math_tools.h"

template <class TItem>
class TBaseMatrix
{

  friend class TVector3D<TItem>;
  
  friend TBaseMatrix<TItem> operator *<TItem> (const TBaseMatrix<TItem>& rktMAT1, const TBaseMatrix<TItem>& rktMAT2);
  friend TVector3D<TItem> operator *<TItem> (const TBaseMatrix<TItem>& rktMAT, const TVector3D<TItem>& rktVECTOR);

  protected:
  
    TItem   atElement[4][4];
    
  public:

    void clear (void);
    void setIdentity (void);
    void setTranslation (const TVector3D<TItem>& rktVECT);
    void setRotationX (TItem tANGLE);
    void setRotationX (TItem tSIN, TItem tCOS);
    void setRotationY (TItem tANGLE);
    void setRotationY (TItem tSIN, TItem tCOS);
    void setRotationZ (TItem tANGLE);
    void setRotation (const TVector3D<TItem>& rktAXISPOINT1, const TVector3D<TItem>& rktAXISPOINT2, TItem tANGLE);
    void setScaling (const TVector3D<TItem>& rktSCALING_XYZ, const TVector3D<TItem>& rktPOINT);

    void setElement (Byte bROW, Byte bCOL, TItem tITEM);

    TItem getElement (Byte bROW, Byte bCOL) const;
    
    void printDebug (void) const;
            
};  /* class TBaseMatrix */

template <class TItem>
TBaseMatrix<TItem> operator + (const TBaseMatrix<TItem>& rktMAT1, const TBaseMatrix<TItem>& rktMAT2);


template <class TItem>
void TBaseMatrix<TItem>::clear (void)
{

  for (Byte I = 0; ( I < 4 ) ;I++)
  {
    for (Byte J = 0; ( J < 4 ) ;J++)
    {
      atElement[I][J] = TItem (0);
    }
  }

}  /* TBaseMatrix() */


template <class TItem>
void TBaseMatrix<TItem>::setIdentity (void)
{

  for (Byte I = 0; ( I < 4 ) ; I++)
  {
    for (Byte J = 0; ( J < 4 ) ; J++)
    {
      if ( I == J )
      {
        atElement[I][J] = TItem (1);
      }
      else
      {
        atElement[I][J] = TItem (0);
      }
    }
  }
    
}  /* setIdentity() */


template <class TItem>
void TBaseMatrix<TItem>::setTranslation (const TVector3D<TItem>& rktVECT)
{

  for (Byte I = 0; ( I < 3 ) ;I++)
  {
    for (Byte J = 0; ( J < 3 ) ;J++)
    {
      if ( I == J )
      {
        atElement[I][J] = TItem (1);
      }
      else
      {
        atElement[I][J] = TItem (0);
      }
    }
    atElement[I][3] = rktVECT [I];
  }

  for (Byte J = 0; ( J < 3 ) ; J++)
  {
    atElement[3][J] = TItem (0);
  }
  atElement[3][3] = TItem (1);

}  /* setTranslation() */


template <class TItem>
void TBaseMatrix<TItem>::setRotationZ (TItem tANGLE)
{

  TItem   tAngle = degreeToRadian (tANGLE);
  
  atElement[0][0] = TItem (cos (tAngle));
  atElement[0][1] = TItem (-sin (tAngle));
  atElement[0][2] = TItem (0);
  atElement[0][3] = TItem (0);
  atElement[1][0] = TItem (sin (tAngle));
  atElement[1][1] = TItem (cos (tAngle));
  atElement[1][2] = TItem (0);
  atElement[1][3] = TItem (0);

  for (Byte I = 2; ( I < 4 ) ; I++)
  {
    for (Byte J = 0; ( J < 4 ) ; J++)
    {
      if ( I == J )
      {
        atElement[I][J] = TItem (1);
      }
      else
      {
        atElement[I][J] = TItem (0);
      }
    }
  }

}  /* setRotationZ() */


template <class TItem>
void TBaseMatrix<TItem>::setRotationX (TItem tANGLE)
{

  TItem   tAngle = degreeToRadian (tANGLE);
  
  atElement[0][0] = TItem (1);
  atElement[0][1] = TItem (0);
  atElement[0][2] = TItem (0);
  atElement[0][3] = TItem (0);

  atElement[1][0] = TItem (0);
  atElement[1][1] = TItem (cos (tAngle));
  atElement[1][2] = TItem (-sin (tAngle));
  atElement[1][3] = TItem (0);

  atElement[2][0] = TItem (0);
  atElement[2][1] = TItem (sin (tAngle));
  atElement[2][2] = TItem (cos (tAngle));
  atElement[2][3] = TItem (0);

  atElement[3][0] = TItem (0);
  atElement[3][1] = TItem (0);
  atElement[3][2] = TItem (0);
  atElement[3][3] = TItem (1);  

}  /* setRotationX() */


template <class TItem>
void TBaseMatrix<TItem>::setRotationX (TItem tSIN, TItem tCOS)
{

  atElement[0][0] = TItem (1);
  atElement[0][1] = TItem (0);
  atElement[0][2] = TItem (0);
  atElement[0][3] = TItem (0);

  atElement[1][0] = TItem (0);
  atElement[1][1] = tCOS;
  atElement[1][2] = -tSIN;
  atElement[1][3] = TItem (0);

  atElement[2][0] = TItem (0);
  atElement[2][1] = tSIN;
  atElement[2][2] = tCOS;
  atElement[2][3] = TItem (0);

  atElement[3][0] = TItem (0);
  atElement[3][1] = TItem (0);
  atElement[3][2] = TItem (0);
  atElement[3][3] = TItem (1);  

}  /* setRotationX() */


template <class TItem>
void TBaseMatrix<TItem>::setRotationY (TItem tANGLE)
{

  TItem   tAngle = degreeToRadian (tANGLE);

  atElement[0][0] = TItem (cos (tAngle));
  atElement[0][1] = TItem (0);
  atElement[0][2] = TItem (sin (tAngle));
  atElement[0][3] = TItem (0);

  atElement[1][0] = TItem (0);
  atElement[1][1] = TItem (1);
  atElement[1][2] = TItem (0);
  atElement[1][3] = TItem (0);

  atElement[2][0] = TItem (-sin (tAngle));
  atElement[2][1] = TItem (0);
  atElement[2][2] = TItem (cos (tAngle));
  atElement[2][3] = TItem (0);

  atElement[3][0] = TItem (0);
  atElement[3][1] = TItem (0);
  atElement[3][2] = TItem (0);
  atElement[3][3] = TItem (1);  

}  /* setRotationY() */


template <class TItem>
void TBaseMatrix<TItem>::setRotationY (TItem tSIN, TItem tCOS)
{

  atElement[0][0] = tCOS;
  atElement[0][1] = TItem (0);
  atElement[0][2] = tSIN;
  atElement[0][3] = TItem (0);

  atElement[1][0] = TItem (0);
  atElement[1][1] = TItem (1);
  atElement[1][2] = TItem (0);
  atElement[1][3] = TItem (0);

  atElement[2][0] = -tSIN;
  atElement[2][1] = TItem (0);
  atElement[2][2] = tCOS;
  atElement[2][3] = TItem (0);

  atElement[3][0] = TItem (0);
  atElement[3][1] = TItem (0);
  atElement[3][2] = TItem (0);
  atElement[3][3] = TItem (1);  

}  /* setRotationY() */


template <class TItem>
void TBaseMatrix<TItem>::setRotation (const TVector3D<TItem>& rktAXISPOINT1, const TVector3D<TItem>& rktAXISPOINT2, TItem tANGLE)
{

  TItem                a, b, c, d;
  TVector3D<TItem>     v;
  TBaseMatrix<TItem>   tTotal;
  TBaseMatrix<TItem>   tTranslation;
  TBaseMatrix<TItem>   tRotationX;
  TBaseMatrix<TItem>   tRotationY;
  TBaseMatrix<TItem>   tRotationZ;
  bool                 bDoRotationX = false;
  
  v = (rktAXISPOINT2 - rktAXISPOINT1);
  v.normalize();
  
  a = v.x();
  b = v.y();
  c = v.z();
  if ( ( b != TItem (0) ) || ( c != TItem (0) ) )
  {
    d            = sqrt (b * b + c * c);
    bDoRotationX = true;
  }
  else
  {
    d = c;
  }
    
  tTranslation.setTranslation (-rktAXISPOINT1);
  if ( bDoRotationX )
  {
    tRotationX.setRotationX (b / d, c / d);
  }
  tRotationY.setRotationY (-a, d);
  tRotationZ.setRotationZ (tANGLE);

  if ( bDoRotationX )
  {
    tTotal = tRotationZ * tRotationY * tRotationX * tTranslation;
  }
  else
  {
    tTotal = tRotationZ * tRotationY * tTranslation;
  }
  tTranslation.setTranslation (rktAXISPOINT1);
  if ( bDoRotationX )
  {
    tRotationX.setRotationX (-(b / d), c / d);
  }
  tRotationY.setRotationY (a, d);
  
  if ( bDoRotationX )
  {
    tTotal = tTranslation * tRotationX * tRotationY * tTotal;
  }
  else
  {
    tTotal = tTranslation * tRotationY * tTotal;
  }
  *this = tTotal;

}  /* setRotation() */


template <class TItem>
void TBaseMatrix<TItem>::setScaling (const TVector3D<TItem>& rktSCALING_XYZ, const TVector3D<TItem>& rktPOINT)
{

  atElement[0][0] = rktSCALING_XYZ.x();
  atElement[0][1] = TItem (0);
  atElement[0][2] = TItem (0);
  atElement[0][3] = (1 - rktSCALING_XYZ.x()) * rktPOINT.x();

  atElement[1][0] = TItem (0);
  atElement[1][1] = rktSCALING_XYZ.y();
  atElement[1][2] = TItem (0);
  atElement[1][3] = (1 - rktSCALING_XYZ.y()) * rktPOINT.y();

  atElement[2][0] = TItem (0);
  atElement[2][1] = TItem (0);
  atElement[2][2] = rktSCALING_XYZ.z();
  atElement[2][3] = (1 - rktSCALING_XYZ.z()) * rktPOINT.z();

  atElement[3][0] = TItem (0);
  atElement[3][1] = TItem (0);
  atElement[3][2] = TItem (0);
  atElement[3][3] = TItem (1);  

}  /* setScaling() */


template <class TItem>
inline void TBaseMatrix<TItem>::setElement (Byte bROW, Byte bCOL, TItem tITEM)
{

  assert ( bROW < 4 );
  assert ( bCOL < 4 );

  atElement[bROW][bCOL] = tITEM;
  
}  /* setElement() */


template <class TItem>
inline TItem TBaseMatrix<TItem>::getElement (Byte bROW, Byte bCOL) const
{

  assert ( bROW < 4 );
  assert ( bCOL < 4 );

  return atElement [bROW] [bCOL];
  
}  /* getElement() */

    
template <class TItem>
void TBaseMatrix<TItem>::printDebug (void) const
{

  for (Byte I = 0; ( I < 4 ) ;I++)
  {
    for (Byte J = 0; ( J < 4 ) ;J++)
    {
      cerr << atElement[I][J]; cerr << " | ";
    }
    cerr << endl;
  }
                
}  /* printDebug() */


template <class TItem>
TBaseMatrix<TItem> operator * (const TBaseMatrix<TItem>& rktMAT1, const TBaseMatrix<TItem>& rktMAT2)
{

  TBaseMatrix<TItem>   tMatrix;

  for (Byte I = 0; ( I < 4 ) ;I++)
  {
    for (Byte J = 0; ( J < 4 ) ;J++)
    {
      tMatrix.atElement[I][J] = TItem (0);
      for (size_t K = 0; ( K < 4 ) ;K++)
      {
        tMatrix.atElement[I][J] += rktMAT1.atElement[I][K] * rktMAT2.atElement[K][J];
      }
    }
  }

  return tMatrix;

}  /* operator * () */


template <class TItem>
TVector3D<TItem> operator * (const TBaseMatrix<TItem>& rktMAT, const TVector3D<TItem>& rktVECTOR)
{

  TVector3D<TItem>   tVector (rktMAT.atElement[0][0] * rktVECTOR.x() +
                              rktMAT.atElement[0][1] * rktVECTOR.y() +
                              rktMAT.atElement[0][2] * rktVECTOR.z() +
                              rktMAT.atElement[0][3],
                              rktMAT.atElement[1][0] * rktVECTOR.x() +
                              rktMAT.atElement[1][1] * rktVECTOR.y() +
                              rktMAT.atElement[1][2] * rktVECTOR.z() +
                              rktMAT.atElement[1][3],
                              rktMAT.atElement[2][0] * rktVECTOR.x() +
                              rktMAT.atElement[2][1] * rktVECTOR.y() +
                              rktMAT.atElement[2][2] * rktVECTOR.z() +
                              rktMAT.atElement[2][3]);

  return tVector;

}  /* operator * () */


template <class TItem>
TBaseMatrix<TItem> operator + (const TBaseMatrix<TItem>& rktMAT1, const TBaseMatrix<TItem>& rktMAT2)
{

  TBaseMatrix<TItem>   tMatrix;

  for (Byte I = 0; ( I < 4 ) ;I++)
  {
    for (Byte J = 0; ( J < 4 ) ;J++)
    {
      tMatrix.atElement[I][J] = rktMAT1.atElement[I][J] + rktMAT2.atElement[I][J];
    }
  }

  return tMatrix;

}  /* operator + () */

#endif  /* _MATRIX__ */

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

#ifndef _CHECKERBOARD__
#define _CHECKERBOARD__

#include "llapi/llapi_defs.h"

class TCheckerBoard
{

  protected:

    TScalar   tSize;
    TScalar   tBorder;

  public:

    TCheckerBoard (TScalar tSIZE = 10, TScalar tBORDER = 0) :
      tSize (tSIZE),
      tBorder (tBORDER) {}

    void setSize (TScalar tSIZE = 10) { tSize = tSIZE; }
    void setBorder (TScalar tBORDER = 0) { tBorder = tBORDER; }

    TScalar size (void) const { return tSize; }
    TScalar border (void) const { return tBorder; }
    
    TScalar evaluate (const TVector& rktPOS) const;

};  /* class TCheckerBoard */


inline TScalar TCheckerBoard::evaluate (const TVector& rktPOS) const
{

  size_t    v, v1, v2, v3;
  TScalar   tValue;

  if ( tBorder == 0 )
  {
    v = size_t ((rktPOS.x() + 999999) / tSize) +
        size_t ((rktPOS.y() + 999999) / tSize) +
        size_t ((rktPOS.z() + 999999) / tSize) ;
    tValue = TScalar (v & 1);
  }
  else
  {
    v1 = (size_t (rktPOS.x() + 999999) % size_t (tSize));
    v2 = (size_t (rktPOS.y() + 999999) % size_t (tSize));
    v3 = (size_t (rktPOS.z() + 999999) % size_t (tSize));
    tValue = ( ( v1 < tBorder ) ||
               ( v2 < tBorder ) ||
               ( v3 < tBorder ) );
  }

  return tValue;

}  /* evaluate() */

#endif  /* _CHECKERBOARD__ */

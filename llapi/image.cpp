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

#include <iostream.h>
#include "llapi/image.h"

void TImage::setPixel (size_t X, size_t Y, const TColor& rktCOLOR, bool gSUM)
{

  float    fIntensity;
  size_t   zPos;

  if ( ( X < zWidth ) && ( Y < zHeight ) )
  {
    zPos = Y * zWidth + X;
    
    if ( gSUM )
    {
      ptBuffer [zPos] += rktCOLOR;
    }
    else
    {
      ptBuffer [zPos] = rktCOLOR;
    }

    fIntensity = ptBuffer [zPos].intensity();
    
    if ( fIntensity > fMaxIntensity )
    {
      fMaxIntensity = fIntensity;
    }
    else if ( fIntensity < fMinIntensity )
    {
      fMinIntensity = fIntensity;
    }
  }
  
}  /* setPixel() */


void TImage::setAAPixel (TScalar X, TScalar Y, const TColor& rktCOLOR, bool gSUM)
{

  size_t    BI = size_t (floor (X));
  size_t    BJ = size_t (floor (Y));
  TScalar   L1, L2, L3, L4;

  L1 = ceil (X) - X;
  L2 = ceil (Y) - Y;
  L3 = X + 1 - ceil (X);
  L4 = Y + 1 - ceil (Y);
  
  setPixel (BI    , BJ    , rktCOLOR * (L1 * L2), gSUM);
  setPixel (BI + 1, BJ    , rktCOLOR * (L3 * L2), gSUM);
  setPixel (BI    , BJ + 1, rktCOLOR * (L1 * L4), gSUM);
  setPixel (BI + 1, BJ + 1, rktCOLOR * (L3 * L4), gSUM);

}  /* setAAPixel() */

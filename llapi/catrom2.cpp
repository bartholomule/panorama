/*
*  Copyright (C) 1999 Peter Barnett
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

#include "llapi/catrom2.h"


TCatRom2::TCatRom2()
{
  int      i;
  TScalar  tX;
  
  for (i = 0; i < NENTRIES ; i++)
  {
    tX = i / (TScalar) SAMPRATE;
    tX = sqrtf (tX);
    
    if ( tX < 1)
    {
      atTable [i] = 0.5 * (2 + tX * tX * (-5 + tX * 3));
    }
    else
    {
      atTable [i] = 0.5 * (4 + tX * (-8 + tX * (5 - tX)));
    }
    //cout << tX << "\t" << atTable [i] << endl;
  }
}

TScalar TCatRom2::filter (const TScalar ktVALUE) const
{
  TScalar  tD;
  int      i = 0;
  
  if ( ktVALUE >= 4 )
  {
    return 0.0;
  }
  
  tD = ktVALUE * SAMPRATE + 0.5;

  i = (int) tfloor (tD);
  
  if ( i >= NENTRIES )
  {
    return 0.0;
  }
  
  return atTable [i];
}  /* filter */


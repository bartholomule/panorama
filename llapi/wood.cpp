/*
*  Copyright (C) 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#include "llapi/wood.h"
#include "llapi/mat_utils.h"

/* ported from Larry Gritz's wood2.sl shader for BMRT; used by permission. */


TScalar TWood::wood (const TScalar ktX,
                     const TScalar ktY,
                     const TScalar ktZ,
                     const TScalar ktRINGSCALE,
                     const TScalar ktGRAINFACTOR) const
{
  TVector  tQ;
  TScalar  tT;
  TScalar  tR;
  TScalar  tS;

  tT =  ktZ / ktRINGSCALE;
  tQ =  TVector (ktX * 8.0, ktY * 8.0, ktZ);
  tT += tNoise.noise (tQ) / 16.0;

  tQ =  TVector (ktX, tT, ktY + 12.93);
  tR =  ktRINGSCALE * tNoise.noise (tQ);
  tR -= tfloor (tR);
  tR =  0.2 + 0.8 * smoothstep (0.2, 0.55, tR) * (1.0 - smoothstep (0.75, 0.8, tR));
  
  tQ =  TVector (ktX * 128.0 + 5.0, ktZ * 8.0 - 3.0, ktY * 128.0 + 1);
  tS =  ktGRAINFACTOR * (1.3 - tNoise.noise (tQ)) + (1.0 - ktGRAINFACTOR);
  
  return tR * tS * tS;

}  /* wood */


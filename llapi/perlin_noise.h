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

#ifndef _PERLIN_NOISE__
#define _PERLIN_NOISE__

#include "llapi/llapi_defs.h"

#define FX_NOISE_SIZE         256

struct TNoiseData
{
  
  TScalar   tValue;
  TVector   tTangent;
  
};  /* struct TNoiseData */


class TPerlinNoise
{

  protected:

    TNoiseData   atData [FX_NOISE_SIZE];
    int          aiPermutation [FX_NOISE_SIZE];
    
    mutable TVector   tBasePoint;
    mutable TVector   tFractional;

    TNoiseData hash (const TVector& rktPOINT) const;
    TNoiseData interpolate (Byte bLEVEL, Byte bPOS) const;

  public:

    TPerlinNoise (void);

    TScalar noise (const TVector& rktPOINT, TVector* ptGRADIENT = NULL) const;
    TScalar snoise (const TVector& rktPOINT, TVector* ptGRADIENT = NULL) const
    {
      TScalar   t = noise (rktPOINT, ptGRADIENT);
      
      return t + (t - 1);
    }
    TScalar fractalSum (const TVector& rktPOINT, TScalar tMIN_FREQ, TScalar tMAX_FREQ, TVector* ptGRADIENT = NULL) const;
    TScalar turbulence (const TVector& rktPOINT, TScalar tMIN_FREQ, TScalar tMAX_FREQ) const;
    
};  /* class TPerlinNoise */

#endif  /* _PERLIN_NOISE__ */

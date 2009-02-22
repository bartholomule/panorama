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

#include "llapi/math_tools.h"
#include "llapi/perlin_noise.h"
#include "llapi/vector_tools.h"

inline static TScalar Hermite (TScalar X0, TScalar X1, TScalar T0, TScalar T1, TScalar X)
{

  TScalar   X2 = X * X;
  
  return ( X0 * ((X * 2 - 3) * X2 + 1) +
           X1 * (-2 * X + 3) * X2      +
           T0 * ((X - 2) * X + 1) * X  +
           T1 * (X - 1) * X2           );
  
}  /* Hermite() */

                                 
inline static TVector Point (const TVector& rktPOINT, Byte bPOS)
{

  return TVector (rktPOINT.x() + (bPOS & 1),
                  rktPOINT.y() + ((bPOS >> 1) & 1),
                  rktPOINT.z() + ((bPOS >> 2) & 1));
  
}  /* Point() */

                                 
inline TNoiseData TPerlinNoise::hash (const TVector& rktPOINT) const
{

  return atData [mod (aiPermutation [mod (aiPermutation [mod (rktPOINT.x(), FX_NOISE_SIZE)] + rktPOINT.y(), FX_NOISE_SIZE)] + rktPOINT.z(), FX_NOISE_SIZE)];
  
}  /* hash() */

                                 
TNoiseData TPerlinNoise::interpolate (Byte bLEVEL, Byte bPOS) const
{

  TNoiseData   tData;
  TNoiseData   tData1, tData2;
  
  if ( bLEVEL == 0 )
  {
    return hash (Point (tBasePoint, bPOS));
  }

  bLEVEL--;

  tData1 = interpolate (bLEVEL, bPOS);
  tData2 = interpolate (bLEVEL, bPOS | (1 << bLEVEL));

  tData.tTangent = lerp (tData1.tTangent, tData2.tTangent, tFractional [bLEVEL]);
  tData.tValue   = Hermite (tData1.tValue,
                            tData2.tValue,
                            tData1.tTangent [bLEVEL],
                            tData2.tTangent [bLEVEL],
                            tFractional [bLEVEL]);
//  tData.tValue = lerp (tData1.tValue, tData2.tValue, tFractional [bLEVEL]);
  
  return tData;
                            
}  /* interpolate() */


TPerlinNoise::TPerlinNoise (void)
{

  int      iTemp, iPos;
  size_t   J;
  
  //
  // Fill data array with pseudo-random numbers between 0 and 1 and normalized std::vectors.
  //
  for (J = 0; ( J < FX_NOISE_SIZE ) ;J++)
  {
    atData[J].tValue   = frand();
    atData[J].tTangent = RandomVectorInSphere();
  }

  //
  // Fill permutation array with [0..(n-1)] and then shuffle it
  //
  for (J = 0; ( J < FX_NOISE_SIZE ) ;J++)
  {
    aiPermutation [J] = J;
  }
  for (J = 0; ( J < FX_NOISE_SIZE ) ;J++)
  {
    iPos                 = int (frand() * FX_NOISE_SIZE);
    iTemp                = aiPermutation [J];
    aiPermutation [J]    = aiPermutation [iPos];
    aiPermutation [iPos] = iTemp;
  }
  
}  /* TPerlinNoise() */


TScalar TPerlinNoise::noise (const TVector& rktPOINT, TVector* ptGRADIENT) const
{

  TNoiseData   tData;

  tBasePoint.set (floor (rktPOINT.x()), floor (rktPOINT.y()), floor (rktPOINT.z()));
  tFractional.set (rktPOINT.x() - tBasePoint.x(), rktPOINT.y() - tBasePoint.y(), rktPOINT.z() - tBasePoint.z());

  tData = interpolate (3, 0);

  if ( tData.tValue < 0)
  {
    tData.tValue = 0;
  }
  else if ( tData.tValue > 1 )
  {
    tData.tValue = 1;
  }

  if ( ptGRADIENT )
  {
    *ptGRADIENT = tData.tTangent;
  }
  
  return tData.tValue;
  
}  /* noise() */


TScalar TPerlinNoise::fractalSum (const TVector& rktPOINT, TScalar tMIN_FREQ, TScalar tMAX_FREQ, TVector* ptGRADIENT) const
{

  TScalar   tNoise;
  TVector   tGradient;
  TScalar   tValue = 0;

  for (TScalar f = tMIN_FREQ; ( f < tMAX_FREQ ) ;f *= 2.17)
  {
    tNoise  = noise (rktPOINT * f, &tGradient);
    tValue += tNoise / f;
    if ( ptGRADIENT )
    {
      *ptGRADIENT = *ptGRADIENT + tGradient * f;
    }
  }

  if ( ptGRADIENT )
  {
    ptGRADIENT->normalize();
  }

  return tValue;
  
}  /* fractalSum() */


TScalar TPerlinNoise::turbulence (const TVector& rktPOINT, TScalar tMIN_FREQ, TScalar tMAX_FREQ) const
{

  TScalar   tValue = 0;

  for (TScalar f = tMIN_FREQ; ( f < tMAX_FREQ ) ;f *= 2.17)
  {
    tValue += fabs (snoise (rktPOINT * f)) / f;
  }

  return tValue;
  
}  /* turbulence() */

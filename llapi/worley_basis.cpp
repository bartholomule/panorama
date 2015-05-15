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

#include "llapi/worley_basis.h"

inline TScalar TWorleyBasis::hash (const TVector& rktPOINT) const
{

  return atData [mod (aiPermutation [mod (aiPermutation [mod (rktPOINT.x(), FX_RANDOM_TABLE_SIZE)] + rktPOINT.y(), FX_RANDOM_TABLE_SIZE)] + rktPOINT.z(), FX_RANDOM_TABLE_SIZE)];
  
}  /* hash() */


Byte TWorleyBasis::getPoints (TScalar tVALUE) const
{

  // [_OPT_] Change this for a hardcoded binary search
  
  Byte   J = 0;
  
  do
  {
    J++;
  } while ( ( tVALUE < atProbabilities [J] ) && ( J < 8 ) );

  return J;
  
}  /* getPoints() */

                                 
TScalar TWorleyBasis::distance (const TVector& rktPOINT1, const TVector& rktPOINT2) const
{

  return Distance (rktPOINT1, rktPOINT2);

//  return max3 (fabs (rktPOINT1.x() - rktPOINT2.x()),
//               fabs (rktPOINT1.y() - rktPOINT2.y()),
//               fabs (rktPOINT1.z() - rktPOINT2.z()));
                     
}  /* distance() */


void TWorleyBasis::checkVoxel (const TVector& rktBASE_POINT,
                               const TVector& rktPOINT,
                               TPriorityQueue<TWorleyBasis::TPointData>* ptPQUEUE) const
{

  TVector      tPoint;
  TPointData   tPointData;
  TScalar      tRandomValue = hash (rktBASE_POINT);
  size_t       zRandomInt   = (size_t) floor (tRandomValue * FX_RANDOM_TABLE_SIZE);
  Byte         bPoints      = getPoints (tRandomValue);

  for (Byte J = 0; ( J < bPoints ) ;J++)
  {
    tPoint.set (
      rktBASE_POINT.x() + atData [aiPermutation [mod (zRandomInt + 0, FX_RANDOM_TABLE_SIZE)]],
      rktBASE_POINT.y() + atData [aiPermutation [mod (zRandomInt + 1, FX_RANDOM_TABLE_SIZE)]],
      rktBASE_POINT.z() + atData [aiPermutation [mod (zRandomInt + 2, FX_RANDOM_TABLE_SIZE)]]);
    tPointData.tPoint    = tPoint;
    tPointData.tVector   = tPoint - rktPOINT;
    tPointData.tDistance = distance (tPoint, rktPOINT);
    tPointData.tVector.normalize();
    ptPQUEUE->insert (tPointData, tPointData.tDistance);
  }

}  /* checkVoxel() */

                                 
void TWorleyBasis::checkVoxels (const TVector& rktBASE_POINT,
                                const TVector& rktPOINT,
                                Byte bMASK,
                                TPriorityQueue<TWorleyBasis::TPointData>* ptPQUEUE) const
{

  TScalar   tMinDistance;
  
  if ( ptPQUEUE->size() < bNearestPoints )
  {
    tMinDistance = SCALAR_MAX;
  }
  else
  {
    tMinDistance = (*ptPQUEUE)[0].tData.tDistance;
  }

  if ( bMASK & 1 )
  {
    // Z axis
    if ( fabs (rktBASE_POINT[2] - rktPOINT[2]) < tMinDistance )
    {
      checkVoxels (rktBASE_POINT + TVector (0, 0, -1), rktPOINT, bMASK & 6, ptPQUEUE);
    }
    checkVoxels (rktBASE_POINT, rktPOINT, bMASK & 6, ptPQUEUE);
    if ( fabs (rktBASE_POINT[2] + 1 - rktPOINT[2]) < tMinDistance )
    {
      checkVoxels (rktBASE_POINT + TVector (0, 0, 1), rktPOINT, bMASK & 6, ptPQUEUE);
    }
  }
  else if ( bMASK & 2 )
  {
    // Y axis
    if ( fabs (rktBASE_POINT[1] - rktPOINT[1]) < tMinDistance )
    {
      checkVoxels (rktBASE_POINT + TVector (0, -1, 0), rktPOINT, bMASK & 5, ptPQUEUE);
    }
    checkVoxels (rktBASE_POINT, rktPOINT, bMASK & 5, ptPQUEUE);
    if ( fabs (rktBASE_POINT[1] + 1 - rktPOINT[1]) < tMinDistance )
    {
      checkVoxels (rktBASE_POINT + TVector (0, 1, 0), rktPOINT, bMASK & 5, ptPQUEUE);
    }
  }
  else if ( bMASK & 4 )
  {
    // X axis
    if ( fabs (rktBASE_POINT[0] - rktPOINT[0]) < tMinDistance )
    {
      checkVoxels (rktBASE_POINT + TVector (-1, 0, 0), rktPOINT, bMASK & 3, ptPQUEUE);
    }
    checkVoxels (rktBASE_POINT, rktPOINT, bMASK & 3, ptPQUEUE);
    if ( fabs (rktBASE_POINT[0] + 1 - rktPOINT[0]) < tMinDistance )
    {
      checkVoxels (rktBASE_POINT + TVector (1, 0, 0), rktPOINT, bMASK & 3, ptPQUEUE);
    }
  }
  else
  {
    if ( rktBASE_POINT != tBasePoint )
    {
      checkVoxel (rktBASE_POINT, rktPOINT, ptPQUEUE);
    }
  }

}  /* checkVoxels() */

                                 
TWorleyBasis::TWorleyBasis (Byte bNEAREST_POINTS, TScalar tLAMBDA) :
  bNearestPoints (bNEAREST_POINTS)
{

  int       iTemp, iPos;
  size_t    J;
  TScalar   tSum = 0;

  assert ( bNEAREST_POINTS < 10 );
  
  //
  // Calculate probabilities array
  //
  for (int I = 0; ( I < 8 ) ;I++)
  {
    tSum              += 1 / (pow (tLAMBDA, -(I + 1)) * exp (tLAMBDA) * factorial (I + 1));
    atProbabilities[I] = tSum;
  }
  
  //
  // Fill data array with pseudo-random numbers between 0 and 1.
  //
  for (J = 0; ( J < FX_RANDOM_TABLE_SIZE ) ;J++)
  {
    atData[J] = frand();
  }

  //
  // Fill permutation array with [0..(n-1)] and then shuffle it
  //
  for (J = 0; ( J < FX_RANDOM_TABLE_SIZE ) ;J++)
  {
    aiPermutation [J] = J;
  }
  for (J = 0; ( J < FX_RANDOM_TABLE_SIZE ) ;J++)
  {
    iPos                 = int (frand() * FX_RANDOM_TABLE_SIZE);
    iTemp                = aiPermutation [J];
    aiPermutation [J]    = aiPermutation [iPos];
    aiPermutation [iPos] = iTemp;
  }
  
}  /* TWorleyBasis() */


TPriorityQueue<TWorleyBasis::TPointData>* TWorleyBasis::evaluate (const TVector& rktPOINT) const
{

  TPriorityQueue<TPointData>*   ptPQueue;

  ptPQueue = new TPriorityQueue<TPointData> (bNearestPoints);
                                 
  tBasePoint.set (floor (rktPOINT.x()), floor (rktPOINT.y()), floor (rktPOINT.z()));

  checkVoxel (tBasePoint, rktPOINT, ptPQueue);
  
  checkVoxels (tBasePoint, rktPOINT, 7, ptPQueue);
  
  return ptPQueue;
  
}  /* evaluate() */

/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez, Carlos Jimenez Moreno and Peter Barnett
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
*
*  Algorithm based on public domain code by Jim McElhiney,
*  CompuServe 71201,1326, aka mcelhiney@acm.org
*/

#include <stdlib.h>
#include <stream.h>
#include <time.h>
#include "mat_crackle.h"

DEFINE_PLUGIN ("MaterialCrackle", FX_MATERIAL_CLASS, TMaterialCrackle);

TVoronoi::TVoronoi()
{
  lRandomSeed = 12345L;
  lLastHashValue = 0x80000000;

  // build hash table for use by Hash3d

  for (int i = 0; i <= HASHMASK; i++)
  {
    aiHashTable[i] = i;
  }

  // shuffle the values

  for (int i = 0; i <= HASHMASK; i++)
  {
    int iTemp, iIndex = Random() & HASHMASK;
    iTemp = aiHashTable[iIndex];
    aiHashTable[iIndex] = aiHashTable[i];
    aiHashTable[i] = iTemp;
  }
}  /* TVoronoi */ 

/*
inline long TVoronoi::Random()
{
  long lHigh, lLow;

  lHigh = lRandomSeed / 127773L;
  lLow  = lRandomSeed % 127773L;
  lRandomSeed = 16807L * lLow - 2836 * lHigh;
  if (lRandomSeed <= 0L)
  {
    lRandomSeed += 0x7fffffff;
  }
  
  return lRandomSeed;
}

inline long TVoronoi::Random1()
{
  return rand();
}
*/

long TVoronoi::Random() const
{
  #ifdef USE_NEWRAND
  lRandomSeed = lRandomSeed * 17231723L + 2001L;
  return((lRandomSeed >> 16) & 0x7fff);
  #else
  return rand();
  #endif
}

double TVoronoi::Drandom() const
{
  #ifdef USE_NEWRAND
  return (double)Random() / 0x7fff;
  #else
  return (double)Random() / RAND_MAX;
  #endif
}

inline void TVoronoi::SeedRandom(long lSeed) const
{
  #ifdef USE_NEWRAND
  lRandomSeed = lSeed;
  #else
  srand(lSeed);
  #endif
}

inline int TVoronoi::Hash3d(int iX, int iY, int iZ) const
{
  return aiHashTable[aiHashTable[aiHashTable[iX & HASHMASK] ^ (iY & HASHMASK)] ^ (iZ & HASHMASK)];
}

// create a point at random coordinates within the same unit cube
// as the input point

long TVoronoi::GeneratePointInCube( const TVector& rktPoint, TVector& tNewPoint) const
{
  long    lSeed;
  TScalar tFloorX = floor (rktPoint.x() - 1.0E-6);
  TScalar tFloorY = floor (rktPoint.y() - 1.0E-6);
  TScalar tFloorZ = floor (rktPoint.z() - 1.0E-6);

  lSeed = Hash3d ((int) tFloorX, (int) tFloorY, (int) tFloorZ);

  SeedRandom (lSeed);

  tNewPoint.set (tFloorX + Drandom(), tFloorY + Drandom(), tFloorZ + Drandom());
  
  return lSeed;
}

// build a cache of displaced points in all unit cubes within a
// 3D knight's move from the specified point

void TVoronoi::BuildPointCache(const TVector& rktPOINT) const
{
  TVector tOffset, tNewPoint;
  TScalar tX, tY, tZ;
  int iCount = 0;
  static int i = 0;
  long l;
  for (tX = -2.0; tX < 2.5; tX += 1.0)
  {
    for (tY = -2.0; tY < 2.5; tY += 1.0)
    {
      for (tZ = -2.0; tZ < 2.5; tZ += 1.0)
      {
        if ((fabs (tX) > 1.5) + (fabs (tY) > 1.5) + (fabs (tZ) > 1.5) <= 1 )
        {
           tOffset.set (tX, tY, tZ);
           l = GeneratePointInCube (tOffset + rktPOINT, tNewPoint);
           atPointCache[iCount++] = tNewPoint;
        }
      }
    }
  }
  i = 1;
  iPointsInCache = iCount;
}

TScalar TVoronoi::GetValueAtPoint (const TVector& rktPOINT, TVector* ptGRADIENT) const
{
  int     iCount;
  long    lHashValue;
  TVector tDummy,tDifference, tNearest1, tNearest2;
  TScalar tTemp, tDistSquared, tMinDistSquared1, tMinDistSquared2;

  lHashValue = GeneratePointInCube (rktPOINT, tDummy);

  // rebuild point cache if point is not in the same unit cube
  // as the previous point evaluated

  if (lHashValue != lLastHashValue)
  {
    BuildPointCache (rktPOINT);
    lLastHashValue = lHashValue;
  }

  // get initial values for the two shortest distances
 
  tDifference = atPointCache[0] - rktPOINT;
  tMinDistSquared1 = dotProduct (tDifference, tDifference);
  tNearest1 = atPointCache[0];
  
  tDifference = atPointCache[1] - rktPOINT;
  tMinDistSquared2 = dotProduct (tDifference, tDifference);
  tNearest2 = atPointCache[2];
  
  // make sure tMinDistSquared1 < tMinDistSquared2

  if (tMinDistSquared1 > tMinDistSquared2)
  {
    tTemp = tMinDistSquared1;
    tMinDistSquared1 = tMinDistSquared2;
    tMinDistSquared2 = tTemp;
    tNearest1 = atPointCache[1];
    tNearest2 = atPointCache[0];
  }
  // iterate through point cache to find the two nearest points
  
  for (iCount = 2; iCount < iPointsInCache; iCount++)
  {
    tDifference = atPointCache[iCount] - rktPOINT;
    tDistSquared = dotProduct (tDifference, tDifference);

    if (tDistSquared < tMinDistSquared1)
    {
      tMinDistSquared2 = tMinDistSquared1;
      tMinDistSquared1 = tDistSquared;
      tNearest2 = tNearest1;
      tNearest1 = atPointCache[iCount];
    }
    else
    {
      if (tDistSquared < tMinDistSquared2)
      {
        tMinDistSquared2 = tDistSquared;
        tNearest2 = atPointCache[iCount];
      }
    }
  }

  if ( ptGRADIENT != NULL )
  {
    *ptGRADIENT = tNearest2 - tNearest1;
  }
  
  return sqrt (tMinDistSquared2) - sqrt (tMinDistSquared1);
}

inline TScalar TMaterialCrackle::evaluate (const TVector& rktPOINT, TVector* ptGRADIENT) const
{
  return tVoronoi.GetValueAtPoint (rktPOINT, ptGRADIENT);
}  /* evaluate() */


inline TVector TMaterialCrackle::perturbNormal (const TSurfaceData& rktDATA) const
{

  TVector   tNewNormal = rktDATA.normal();

  if ( fabs(tBumpFactor) > FX_EPSILON )
  {
    TVector   tGradient;
    TVector   tPoint = rktDATA.localPoint() * tZoom;

    evaluate (tPoint, &tGradient);

    tNewNormal = rktDATA.normal() + tGradient * tBumpFactor;
    tNewNormal.normalize();
  }
  
  return tNewNormal;
  
}  /* perturbNormal() */

int TMaterialCrackle::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "base_color" )
  {
    if ( eTYPE == FX_COLOR )
    {
      setBaseColor (*((TColor*) nVALUE.pvValue));
    }
    else if ( eTYPE == FX_STRING )
    {
      bGradientLoaded = tGradient.loadGradient((char *) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "zoom" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      tZoom = *((TVector*) nVALUE.pvValue);
      tZoom.set (1.0 / tZoom.x(), 1.0 / tZoom.y(), 1.0 / tZoom.z());
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "bump" )
  {
    if ( eTYPE == FX_REAL )
    {
      tBumpFactor = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TMaterial::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TMaterialCrackle::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "base_color" )
  {
    rnVALUE.pvValue = &tBaseColor;
  }
  else if ( rktNAME == "zoom" )
  {
    // [_ERROR_] It should return the inverse of this vector.
    rnVALUE.pvValue = &tZoom;
  }
  else if ( rktNAME == "bump" )
  {
    rnVALUE.dValue = tBumpFactor;
  }
  else
  {
    return TMaterial::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TMaterialCrackle::getAttributeList (TAttributeList& rtLIST) const
{

  TMaterial::getAttributeList (rtLIST);

  rtLIST ["base_color"] = FX_COLOR;
  rtLIST ["zoom"]       = FX_VECTOR;
  rtLIST ["bump"]       = FX_REAL;

}  /* getAttributeList() */


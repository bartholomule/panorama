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

#include "llapi/warning_eliminator.h"
#include "uniform_grid.h"

bool TUniformGrid::boundingBoxIntersection (const TRay& rktRAY, TVector& rtVECT) const
{

  TScalar   tIntX1, tIntX2;
  TScalar   tIntY1, tIntY2;
  TScalar   tIntZ1, tIntZ2;
  TScalar   tMin, tMax;
  TScalar   tLimitX1  = tBoundingBoxPoint1.x();
  TScalar   tLimitX2  = tBoundingBoxPoint2.x();
  TScalar   tLimitY1  = tBoundingBoxPoint1.y();
  TScalar   tLimitY2  = tBoundingBoxPoint2.y();
  TScalar   tLimitZ1  = tBoundingBoxPoint1.z();
  TScalar   tLimitZ2  = tBoundingBoxPoint2.z();
  TInterval tRayRange = rktRAY.range();
  TScalar   tTmp      = 0;

  if ( fabs (rktRAY.direction().x()) < FX_EPSILON )
  {
    // Ray is parallel to YZ plane
    if ( ( rktRAY.location().x() < tLimitX1 ) || ( rktRAY.location().x() > tLimitX2 ) )
    {
      return false;
    }
    tIntX1 = 0;
    tIntX2 = SCALAR_MAX;
  }
  else
  {
    tIntX1 = (tLimitX1 - rktRAY.location().x()) / rktRAY.direction().x();
    tIntX2 = (tLimitX2 - rktRAY.location().x()) / rktRAY.direction().x();
    if ( tIntX2 < tIntX1 )
    {
      tTmp   = tIntX1;
      tIntX1 = tIntX2;
      tIntX2 = tTmp;
    }
  }

  if ( fabs (rktRAY.direction().y()) < FX_EPSILON )
  {
    // Ray is parallel to ZX plane
    if ( ( rktRAY.location().y() < tLimitY1 ) || ( rktRAY.location().y() > tLimitY2 ) )
    {
      return false;
    }
    tIntY1 = 0;
    tIntY2 = SCALAR_MAX;
  }
  else
  {
    tIntY1 = (tLimitY1 - rktRAY.location().y()) / rktRAY.direction().y();
    tIntY2 = (tLimitY2 - rktRAY.location().y()) / rktRAY.direction().y();
    if ( tIntY2 < tIntY1 )
    {
      tTmp   = tIntY1;
      tIntY1 = tIntY2;
      tIntY2 = tTmp;
    }
  }

  if ( fabs (rktRAY.direction().z()) < FX_EPSILON )
  {
    // Ray is parallel to XY plane
    if ( ( rktRAY.location().z() < tLimitZ1 ) || ( rktRAY.location().z() > tLimitZ2 ) )
    {
      return false;
    }
    tIntZ1 = 0;
    tIntZ2 = SCALAR_MAX;
  }
  else
  {
    tIntZ1 = (tLimitZ1 - rktRAY.location().z()) / rktRAY.direction().z();
    tIntZ2 = (tLimitZ2 - rktRAY.location().z()) / rktRAY.direction().z();
    if ( tIntZ2 < tIntZ1 )
    {
      tTmp   = tIntZ1;
      tIntZ1 = tIntZ2;
      tIntZ2 = tTmp;
    }
  }

  tMax = ( tIntX1 > tIntY1 ) ? (( tIntX1 > tIntZ1 ) ? tIntX1 : tIntZ1) :
                               (( tIntY1 > tIntZ1 ) ? tIntY1 : tIntZ1);

  tMin = ( tIntX2 < tIntY2 ) ? (( tIntX2 < tIntZ2 ) ? tIntX2 : tIntZ2) :
                               (( tIntY2 < tIntZ2 ) ? tIntY2 : tIntZ2);
  
  if ( ( tMax > tMin ) || ( (tMin - tMax) < FX_EPSILON ) )
  {
    //
    // If there is no intersection or the intersection is in a single point.
    //
    return false;
  }

  //  if ( ( tMax > 0 ) && ( tMax < tRayRange ) )
  if( tRayRange.inside(tMax) )
  {
    rtVECT = rktRAY.location() + (rktRAY.direction() * tMax);
    return true;
  }
  
  return false;

}  /* boundingBoxIntersection() */


bool TUniformGrid::findIntersectionInsideVoxel (TUGLatticeCoord tVOXEL_X, TUGLatticeCoord tVOXEL_Y, TUGLatticeCoord tVOXEL_Z,
                                                const TVector& rktPOINT_LC1, const TVector& rktPOINT_LC2,
                                                const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  list<TUGVoxel>*   ptBucket;
  TUGBucketType     tIndex;
  TVector           tPoint2GC;
  TScalar           tNorm;
  TRay              tRayTmp       = rktRAY;
  bool              gIntersection = false;

  tIndex   = hash (tVOXEL_X, tVOXEL_Y, tVOXEL_Z);
  ptBucket = aptVoxelHashTable [tIndex];

  if ( ptBucket )
  {
    for (list<TUGVoxel>::iterator tIter = ptBucket->begin(); ( tIter != ptBucket->end() ) ;tIter++)
    {
      if ( ( tIter->i == tVOXEL_X ) && ( tIter->j == tVOXEL_Y ) && ( tIter->k == tVOXEL_Z ) )
      {
        for (list<magic_pointer<const TObject> >::const_iterator tIter1 = tIter->tObjectList.begin(); ( tIter1 != tIter->tObjectList.end() ) ;tIter1++)
        {
          if ( (*tIter1)->findFirstIntersection (tRayTmp, rtDATA) )
          {
            tRayTmp.setRange (tRayTmp.range().min(), rtDATA.distance());
            gIntersection = true;
          }
        }

        if ( gIntersection )
        {
          tPoint2GC = rktPOINT_LC2 * tVoxelSize;   // Global coords
          tNorm     = (tPoint2GC - rktRAY.location()).norm();
          if ( rtDATA.distance() < tNorm )
          {
            return true;
          }
        }

        return false;
      }
    }
    
    return false;
  }

  return false;

}  /* findIntersectionInsideVoxel() */


void TUniformGrid::boundingPointRayDestination1 (const TRay& rktRAY, TUGLatticeCoord& rtBX, TUGLatticeCoord& rtBY, TUGLatticeCoord& rtBZ,
                                                 TUGLatticeCoord tLATTICE_INC_X, TUGLatticeCoord tLATTICE_INC_Y, TUGLatticeCoord tLATTICE_INC_Z,
                                                 TVector& rtRAY_DESTINATION_LC) const
{

  TVector           tLastRayPoint;
  TScalar           tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ;
  TUGLatticeCoord   tVoxelLastX, tVoxelLastY, tVoxelLastZ;
  TUGLatticeCoord   tVoxelLastNewX, tVoxelLastNewY, tVoxelLastNewZ;
  TScalar           tRayLimit = rktRAY.maxLimit();

  if ( tRayLimit < SCALAR_MAX )
  {
    tLastRayPoint = rktRAY.location() + rktRAY.direction() * tRayLimit;
    if ( ( tLastRayPoint.x() > tBoundingBoxPoint1.x() ) && ( tLastRayPoint.x() < tBoundingBoxPoint2.x() ) &&
         ( tLastRayPoint.y() > tBoundingBoxPoint1.y() ) && ( tLastRayPoint.y() < tBoundingBoxPoint2.y() ) &&
         ( tLastRayPoint.z() > tBoundingBoxPoint1.z() ) && ( tLastRayPoint.z() < tBoundingBoxPoint2.z() ) )
    {
      tLastRayPointLCX = tLastRayPoint.x() * tInvVoxelSize;
      tLastRayPointLCY = tLastRayPoint.y() * tInvVoxelSize;
      tLastRayPointLCZ = tLastRayPoint.z() * tInvVoxelSize;
      rtRAY_DESTINATION_LC.set (tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ);
    
      // Calculate New Voxel key
      tVoxelLastX = (TUGLatticeCoord) floor (tLastRayPointLCX);
      if ( (tLastRayPointLCX - (TScalar) tVoxelLastX) < FX_EPSILON )
      {
        tVoxelLastNewX = ( tLATTICE_INC_X > 0 ) ? tVoxelLastX - 1 : tVoxelLastX;
      }
      else if ( ((TScalar) (tVoxelLastX + 1) - tLastRayPointLCX) < FX_EPSILON )
      {
        tVoxelLastNewX = ( tLATTICE_INC_X > 0 ) ? tVoxelLastX : tVoxelLastX + 1;
      }
      else
      {
        tVoxelLastNewX = tVoxelLastX;
      }
    
      tVoxelLastY = (TUGLatticeCoord) floor (tLastRayPointLCY);
      if ( (tLastRayPointLCY - (TScalar) tVoxelLastY) < FX_EPSILON )
      {
        tVoxelLastNewY = ( tLATTICE_INC_Y > 0 ) ? tVoxelLastY - 1 : tVoxelLastY;
      }
      else if ( ((TScalar) (tVoxelLastY + 1) - tLastRayPointLCY) < FX_EPSILON )
      {
        tVoxelLastNewY = ( tLATTICE_INC_Y > 0 ) ? tVoxelLastY : tVoxelLastY + 1;
      }
      else
      {
        tVoxelLastNewY = tVoxelLastY;
      }
      
      tVoxelLastZ = (TUGLatticeCoord) floor (tLastRayPointLCZ);
      if ( (tLastRayPointLCZ - (TScalar) tVoxelLastZ) < FX_EPSILON )
      {
        tVoxelLastNewZ = ( tLATTICE_INC_Z > 0 ) ? tVoxelLastZ - 1 : tVoxelLastZ;
      }
      else if ( ((TScalar) (tVoxelLastZ + 1) - tLastRayPointLCZ) < FX_EPSILON )
      {
        tVoxelLastNewZ = ( tLATTICE_INC_Z > 0 ) ? tVoxelLastZ : tVoxelLastZ + 1;
      }
      else
      {
        tVoxelLastNewZ = tVoxelLastZ;
      }
    
      // Calculate New Bounding Point
      rtBX = ( tLATTICE_INC_X > 0 ) ? tVoxelLastNewX : tVoxelLastNewX + 1;
      rtBY = ( tLATTICE_INC_Y > 0 ) ? tVoxelLastNewY : tVoxelLastNewY + 1;
      rtBZ = ( tLATTICE_INC_Z > 0 ) ? tVoxelLastNewZ : tVoxelLastNewZ + 1;
    }
    else
    {
      rtBX = ( tLATTICE_INC_X > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
      rtBY = ( tLATTICE_INC_Y > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
      rtBZ = ( tLATTICE_INC_Z > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
    }
  }
  else
  {
    rtBX = ( tLATTICE_INC_X > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
    rtBY = ( tLATTICE_INC_Y > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
    rtBZ = ( tLATTICE_INC_Z > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
  }
  
}  /* boundingPointRayDestination1() */


void TUniformGrid::boundingPointRayDestination2 (const TRay& rktRAY, TUGLatticeCoord& rtBX, TUGLatticeCoord& rtBZ,
                                                 TUGLatticeCoord tLATTICE_INC_X, TUGLatticeCoord tLATTICE_INC_Z,
                                                 TVector& rtRAY_DESTINATION_LC) const
{

  TVector           tLastRayPoint;
  TScalar           tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ;
  TUGLatticeCoord   tVoxelLastX, tVoxelLastZ;
  TUGLatticeCoord   tVoxelLastNewX, tVoxelLastNewZ;
  TScalar           tRayLimit = rktRAY.maxLimit();

  if ( tRayLimit < SCALAR_MAX )
  {
    tLastRayPoint = rktRAY.location() + rktRAY.direction() * tRayLimit;
    if ( ( tLastRayPoint.x() > tBoundingBoxPoint1.x() ) && ( tLastRayPoint.x() < tBoundingBoxPoint2.x() ) &&
         ( tLastRayPoint.y() > tBoundingBoxPoint1.y() ) && ( tLastRayPoint.y() < tBoundingBoxPoint2.y() ) &&
         ( tLastRayPoint.z() > tBoundingBoxPoint1.z() ) && ( tLastRayPoint.z() < tBoundingBoxPoint2.z() ) )
    {
      tLastRayPointLCX = tLastRayPoint.x() * tInvVoxelSize;
      tLastRayPointLCY = tLastRayPoint.y() * tInvVoxelSize;
      tLastRayPointLCZ = tLastRayPoint.z() * tInvVoxelSize;
      rtRAY_DESTINATION_LC.set (tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ);
    
      // Calculate New Voxel key
      tVoxelLastX = (TUGLatticeCoord) floor (tLastRayPointLCX);
      if ( (tLastRayPointLCX - (TScalar) tVoxelLastX) < FX_EPSILON )
      {
        tVoxelLastNewX = ( tLATTICE_INC_X > 0 ) ? tVoxelLastX - 1 : tVoxelLastX;
      }
      else if ( ((TScalar) (tVoxelLastX + 1) - tLastRayPointLCX) < FX_EPSILON )
      {
        tVoxelLastNewX = ( tLATTICE_INC_X > 0 ) ? tVoxelLastX : tVoxelLastX + 1;
      }
      else
      {
        tVoxelLastNewX = tVoxelLastX;
      }
    
      tVoxelLastZ = (TUGLatticeCoord) floor (tLastRayPointLCZ);
      if ( (tLastRayPointLCZ - (TScalar) tVoxelLastZ) < FX_EPSILON )
      {
        tVoxelLastNewZ = ( tLATTICE_INC_Z > 0 ) ? tVoxelLastZ - 1 : tVoxelLastZ;
      }
      else if ( ((TScalar) (tVoxelLastZ + 1) - tLastRayPointLCZ) < FX_EPSILON )
      {
        tVoxelLastNewZ = ( tLATTICE_INC_Z > 0 ) ? tVoxelLastZ : tVoxelLastZ + 1;
      }
      else
      {
        tVoxelLastNewZ = tVoxelLastZ;
      }
    
      // Calculate New Bounding Point
      rtBX = ( tLATTICE_INC_X > 0 ) ? tVoxelLastNewX : tVoxelLastNewX + 1;
      rtBZ = ( tLATTICE_INC_Z > 0 ) ? tVoxelLastNewZ : tVoxelLastNewZ + 1;
    }
    else
    {
      rtBX = ( tLATTICE_INC_X > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
      rtBZ = ( tLATTICE_INC_Z > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
    }
  }
  else
  {
    rtBX = ( tLATTICE_INC_X > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
    rtBZ = ( tLATTICE_INC_Z > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
  }
  
}  /* boundingPointRayDestination2() */


void TUniformGrid::boundingPointRayDestination3 (const TRay& rktRAY, TUGLatticeCoord& rtBY, TUGLatticeCoord& rtBZ,
                                                 TUGLatticeCoord tLATTICE_INC_Y, TUGLatticeCoord tLATTICE_INC_Z,
                                                 TVector& rtRAY_DESTINATION_LC) const
{

  TVector           tLastRayPoint;
  TScalar           tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ;
  TUGLatticeCoord   tVoxelLastY, tVoxelLastZ;
  TUGLatticeCoord   tVoxelLastNewY, tVoxelLastNewZ;
  TScalar           tRayLimit = rktRAY.maxLimit();

  if ( tRayLimit < SCALAR_MAX )
  {
    tLastRayPoint = rktRAY.location() + rktRAY.direction() * tRayLimit;
    if ( ( tLastRayPoint.x() > tBoundingBoxPoint1.x() ) && ( tLastRayPoint.x() < tBoundingBoxPoint2.x() ) &&
         ( tLastRayPoint.y() > tBoundingBoxPoint1.y() ) && ( tLastRayPoint.y() < tBoundingBoxPoint2.y() ) &&
         ( tLastRayPoint.z() > tBoundingBoxPoint1.z() ) && ( tLastRayPoint.z() < tBoundingBoxPoint2.z() ) )
    {
      tLastRayPointLCX = tLastRayPoint.x() * tInvVoxelSize;
      tLastRayPointLCY = tLastRayPoint.y() * tInvVoxelSize;
      tLastRayPointLCZ = tLastRayPoint.z() * tInvVoxelSize;
      rtRAY_DESTINATION_LC.set (tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ);
    
      // Calculate New Voxel key
      tVoxelLastY = (TUGLatticeCoord) floor (tLastRayPointLCY);
      if ( (tLastRayPointLCY - (TScalar) tVoxelLastY) < FX_EPSILON )
      {
        tVoxelLastNewY = ( tLATTICE_INC_Y > 0 ) ? tVoxelLastY - 1 : tVoxelLastY;
      }
      else if ( ((TScalar) (tVoxelLastY + 1) - tLastRayPointLCY) < FX_EPSILON )
      {
        tVoxelLastNewY = ( tLATTICE_INC_Y > 0 ) ? tVoxelLastY : tVoxelLastY + 1;
      }
      else
      {
        tVoxelLastNewY = tVoxelLastY;
      }
      
      tVoxelLastZ = (TUGLatticeCoord) floor (tLastRayPointLCZ);
      if ( (tLastRayPointLCZ - (TScalar) tVoxelLastZ) < FX_EPSILON )
      {
        tVoxelLastNewZ = ( tLATTICE_INC_Z > 0 ) ? tVoxelLastZ - 1 : tVoxelLastZ;
      }
      else if ( ((TScalar) (tVoxelLastZ + 1) - tLastRayPointLCZ) < FX_EPSILON )
      {
        tVoxelLastNewZ = ( tLATTICE_INC_Z > 0 ) ? tVoxelLastZ : tVoxelLastZ + 1;
      }
      else
      {
        tVoxelLastNewZ = tVoxelLastZ;
      }
    
      // Calculate New Bounding Point
      rtBY = ( tLATTICE_INC_Y > 0 ) ? tVoxelLastNewY : tVoxelLastNewY + 1;
      rtBZ = ( tLATTICE_INC_Z > 0 ) ? tVoxelLastNewZ : tVoxelLastNewZ + 1;
    }
    else
    {
      rtBY = ( tLATTICE_INC_Y > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
      rtBZ = ( tLATTICE_INC_Z > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
    }
  }
  else
  {
    rtBY = ( tLATTICE_INC_Y > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
    rtBZ = ( tLATTICE_INC_Z > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
  }
  
}  /* boundingPointRayDestination3() */


void TUniformGrid::boundingPointRayDestination4 (const TRay& rktRAY, TUGLatticeCoord& rtBX, TUGLatticeCoord& rtBY,
                                                 TUGLatticeCoord tLATTICE_INC_X, TUGLatticeCoord tLATTICE_INC_Y,
                                                 TVector& rtRAY_DESTINATION_LC) const
{

  TVector           tLastRayPoint;
  TScalar           tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ;
  TUGLatticeCoord   tVoxelLastX, tVoxelLastY;
  TUGLatticeCoord   tVoxelLastNewX, tVoxelLastNewY;
  TScalar           tRayLimit = rktRAY.maxLimit();

  if ( tRayLimit < SCALAR_MAX )
  {
    tLastRayPoint = rktRAY.location() + rktRAY.direction() * tRayLimit;
    if ( ( tLastRayPoint.x() > tBoundingBoxPoint1.x() ) && ( tLastRayPoint.x() < tBoundingBoxPoint2.x() ) &&
         ( tLastRayPoint.y() > tBoundingBoxPoint1.y() ) && ( tLastRayPoint.y() < tBoundingBoxPoint2.y() ) &&
         ( tLastRayPoint.z() > tBoundingBoxPoint1.z() ) && ( tLastRayPoint.z() < tBoundingBoxPoint2.z() ) )
    {
      tLastRayPointLCX = tLastRayPoint.x() * tInvVoxelSize;
      tLastRayPointLCY = tLastRayPoint.y() * tInvVoxelSize;
      tLastRayPointLCZ = tLastRayPoint.z() * tInvVoxelSize;
      rtRAY_DESTINATION_LC.set (tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ);
    
      // Calculate New Voxel key
      tVoxelLastX = (TUGLatticeCoord) floor (tLastRayPointLCX);
      if ( (tLastRayPointLCX - (TScalar) tVoxelLastX) < FX_EPSILON )
      {
        tVoxelLastNewX = ( tLATTICE_INC_X > 0 ) ? tVoxelLastX - 1 : tVoxelLastX;
      }
      else if ( ((TScalar) (tVoxelLastX + 1) - tLastRayPointLCX) < FX_EPSILON )
      {
        tVoxelLastNewX = ( tLATTICE_INC_X > 0 ) ? tVoxelLastX : tVoxelLastX + 1;
      }
      else
      {
        tVoxelLastNewX = tVoxelLastX;
      }
    
      tVoxelLastY = (TUGLatticeCoord) floor (tLastRayPointLCY);
      if ( (tLastRayPointLCY - (TScalar) tVoxelLastY) < FX_EPSILON )
      {
        tVoxelLastNewY = ( tLATTICE_INC_Y > 0 ) ? tVoxelLastY - 1 : tVoxelLastY;
      }
      else if ( ((TScalar) (tVoxelLastY + 1) - tLastRayPointLCY) < FX_EPSILON )
      {
        tVoxelLastNewY = ( tLATTICE_INC_Y > 0 ) ? tVoxelLastY : tVoxelLastY + 1;
      }
      else
      {
        tVoxelLastNewY = tVoxelLastY;
      }
      
      // Calculate New Bounding Point
      rtBX = ( tLATTICE_INC_X > 0 ) ? tVoxelLastNewX : tVoxelLastNewX + 1;
      rtBY = ( tLATTICE_INC_Y > 0 ) ? tVoxelLastNewY : tVoxelLastNewY + 1;
    }
    else
    {
      rtBX = ( tLATTICE_INC_X > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
      rtBY = ( tLATTICE_INC_Y > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
    }
  }
  else
  {
    rtBX = ( tLATTICE_INC_X > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
    rtBY = ( tLATTICE_INC_Y > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
  }
  
}  /* boundingPointRayDestination4() */


void TUniformGrid::boundingPointRayDestination5 (const TRay& rktRAY, TUGLatticeCoord& rtBY,
                                                 TUGLatticeCoord tLATTICE_INC_Y,
                                                 TVector& rtRAY_DESTINATION_LC) const
{

  TVector           tLastRayPoint;
  TScalar           tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ;
  TUGLatticeCoord   tVoxelLastY;
  TUGLatticeCoord   tVoxelLastNewY;
  TScalar           tRayLimit = rktRAY.maxLimit();

  if ( tRayLimit < SCALAR_MAX )
  {
    tLastRayPoint = rktRAY.location() + rktRAY.direction() * tRayLimit;
    if ( ( tLastRayPoint.x() > tBoundingBoxPoint1.x() ) && ( tLastRayPoint.x() < tBoundingBoxPoint2.x() ) &&
         ( tLastRayPoint.y() > tBoundingBoxPoint1.y() ) && ( tLastRayPoint.y() < tBoundingBoxPoint2.y() ) &&
         ( tLastRayPoint.z() > tBoundingBoxPoint1.z() ) && ( tLastRayPoint.z() < tBoundingBoxPoint2.z() ) )
    {
      tLastRayPointLCX = tLastRayPoint.x() * tInvVoxelSize;
      tLastRayPointLCY = tLastRayPoint.y() * tInvVoxelSize;
      tLastRayPointLCZ = tLastRayPoint.z() * tInvVoxelSize;
      rtRAY_DESTINATION_LC.set (tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ);
    
      // Calculate New Voxel key
      tVoxelLastY = (TUGLatticeCoord) floor (tLastRayPointLCY);
      if ( (tLastRayPointLCY - (TScalar) tVoxelLastY) < FX_EPSILON )
      {
        tVoxelLastNewY = ( tLATTICE_INC_Y > 0 ) ? tVoxelLastY - 1 : tVoxelLastY;
      }
      else if ( ((TScalar) (tVoxelLastY + 1) - tLastRayPointLCY) < FX_EPSILON )
      {
        tVoxelLastNewY = ( tLATTICE_INC_Y > 0 ) ? tVoxelLastY : tVoxelLastY + 1;
      }
      else
      {
        tVoxelLastNewY = tVoxelLastY;
      }
      
      // Calculate New Bounding Point
      rtBY = ( tLATTICE_INC_Y > 0 ) ? tVoxelLastNewY : tVoxelLastNewY + 1;
    }
    else
    {
      rtBY = ( tLATTICE_INC_Y > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
    }
  }
  else
  {
    rtBY = ( tLATTICE_INC_Y > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
  }
  
}  /* boundingPointRayDestination5() */


void TUniformGrid::boundingPointRayDestination6 (const TRay& rktRAY, TUGLatticeCoord& rtBX,
                                                 TUGLatticeCoord tLATTICE_INC_X,
                                                 TVector& rtRAY_DESTINATION_LC) const
{

  TVector           tLastRayPoint;
  TScalar           tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ;
  TUGLatticeCoord   tVoxelLastX;
  TUGLatticeCoord   tVoxelLastNewX;
  TScalar           tRayLimit = rktRAY.maxLimit();

  if ( tRayLimit < SCALAR_MAX )
  {
    tLastRayPoint = rktRAY.location() + rktRAY.direction() * tRayLimit;
    if ( ( tLastRayPoint.x() > tBoundingBoxPoint1.x() ) && ( tLastRayPoint.x() < tBoundingBoxPoint2.x() ) &&
         ( tLastRayPoint.y() > tBoundingBoxPoint1.y() ) && ( tLastRayPoint.y() < tBoundingBoxPoint2.y() ) &&
         ( tLastRayPoint.z() > tBoundingBoxPoint1.z() ) && ( tLastRayPoint.z() < tBoundingBoxPoint2.z() ) )
    {
      tLastRayPointLCX = tLastRayPoint.x() * tInvVoxelSize;
      tLastRayPointLCY = tLastRayPoint.y() * tInvVoxelSize;
      tLastRayPointLCZ = tLastRayPoint.z() * tInvVoxelSize;
      rtRAY_DESTINATION_LC.set (tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ);
    
      // Calculate New Voxel key
      tVoxelLastX = (TUGLatticeCoord) floor (tLastRayPointLCX);
      if ( (tLastRayPointLCX - (TScalar) tVoxelLastX) < FX_EPSILON )
      {
        tVoxelLastNewX = ( tLATTICE_INC_X > 0 ) ? tVoxelLastX - 1 : tVoxelLastX;
      }
      else if ( ((TScalar) (tVoxelLastX + 1) - tLastRayPointLCX) < FX_EPSILON )
      {
        tVoxelLastNewX = ( tLATTICE_INC_X > 0 ) ? tVoxelLastX : tVoxelLastX + 1;
      }
      else
      {
        tVoxelLastNewX = tVoxelLastX;
      }
    
      // Calculate New Bounding Point
      rtBX = ( tLATTICE_INC_X > 0 ) ? tVoxelLastNewX : tVoxelLastNewX + 1;
    }
    else
    {
      rtBX = ( tLATTICE_INC_X > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
    }
  }
  else
  {
    rtBX = ( tLATTICE_INC_X > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
  }
  
}  /* boundingPointRayDestination6() */


void TUniformGrid::boundingPointRayDestination7 (const TRay& rktRAY, TUGLatticeCoord& rtBZ,
                                                 TUGLatticeCoord tLATTICE_INC_Z,
                                                 TVector& rtRAY_DESTINATION_LC) const
{

  TVector           tLastRayPoint;
  TScalar           tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ;
  TUGLatticeCoord   tVoxelLastZ;
  TUGLatticeCoord   tVoxelLastNewZ;
  TScalar           tRayLimit = rktRAY.maxLimit();

  if ( tRayLimit < SCALAR_MAX )
  {
    tLastRayPoint = rktRAY.location() + rktRAY.direction() * tRayLimit;
    if ( ( tLastRayPoint.x() > tBoundingBoxPoint1.x() ) && ( tLastRayPoint.x() < tBoundingBoxPoint2.x() ) &&
         ( tLastRayPoint.y() > tBoundingBoxPoint1.y() ) && ( tLastRayPoint.y() < tBoundingBoxPoint2.y() ) &&
         ( tLastRayPoint.z() > tBoundingBoxPoint1.z() ) && ( tLastRayPoint.z() < tBoundingBoxPoint2.z() ) )
    {
      tLastRayPointLCX = tLastRayPoint.x() * tInvVoxelSize;
      tLastRayPointLCY = tLastRayPoint.y() * tInvVoxelSize;
      tLastRayPointLCZ = tLastRayPoint.z() * tInvVoxelSize;
      rtRAY_DESTINATION_LC.set (tLastRayPointLCX, tLastRayPointLCY, tLastRayPointLCZ);
    
      tVoxelLastZ = (TUGLatticeCoord) floor (tLastRayPointLCZ);
      if ( (tLastRayPointLCZ - (TScalar) tVoxelLastZ) < FX_EPSILON )
      {
        tVoxelLastNewZ = ( tLATTICE_INC_Z > 0 ) ? tVoxelLastZ - 1 : tVoxelLastZ;
      }
      else if ( ((TScalar) (tVoxelLastZ + 1) - tLastRayPointLCZ) < FX_EPSILON )
      {
        tVoxelLastNewZ = ( tLATTICE_INC_Z > 0 ) ? tVoxelLastZ : tVoxelLastZ + 1;
      }
      else
      {
        tVoxelLastNewZ = tVoxelLastZ;
      }
    
      // Calculate New Bounding Point
      rtBZ = ( tLATTICE_INC_Z > 0 ) ? tVoxelLastNewZ : tVoxelLastNewZ + 1;
    }
    else
    {
      rtBZ = ( tLATTICE_INC_Z > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
    }
  }
  else
  {
    rtBZ = ( tLATTICE_INC_Z > 0 ) ? ktLatticeCoordMax : ktLatticeCoordMin;
  }
  
}  /* boundingPointRayDestination7() */


bool TUniformGrid::findFirstIntersection1 (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TScalar           tRayDirX, tRayDirY, tRayDirZ;
  TScalar           tRayLocX, tRayLocY, tRayLocZ;
  TVector           tFirstRayPoint;                                            // First ray point on lattice (global coords)
  TScalar           tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ;   // First ray point on lattice (lattice coords)
  TScalar           tPyx, tPzx;
  TScalar           tPxy, tPzy;
  TScalar           tPxz, tPyz;
  TUGLatticeCoord   tLatticeIncrementX, tLatticeIncrementY, tLatticeIncrementZ;
  TUGLatticeCoord   tVoxelX, tVoxelY, tVoxelZ;            // Voxel key
  TUGLatticeCoord   tVoxelNewX, tVoxelNewY, tVoxelNewZ;   // Voxel key
  TUGLatticeCoord   tBx, tBy, tBz;                        // Bounding Advance Point
  TUGLatticeCoord   tBNewx, tBNewy, tBNewz;               // Bounding Advance Point
  TScalar           tDeltaX, tDeltaY, tDeltaZ;
  TUGLatticeCoord   tPointAdvanceXx;                      // X Advance Point (TUGLatticeCoord, TScalar, TScalar)
  TScalar           tPointAdvanceXy, tPointAdvanceXz;
  TUGLatticeCoord   tPointAdvanceYy;                      // Y Advance Point (TScalar, TUGLatticeCoord, TScalar)
  TScalar           tPointAdvanceYx, tPointAdvanceYz;
  TUGLatticeCoord   tPointAdvanceZz;                      // Z Advance Point (TScalar, TScalar, TUGLatticeCoord)
  TScalar           tPointAdvanceZx, tPointAdvanceZy;
  TVector           tPointIn;
  TVector           tPointOut;
  bool              gX  = false;
  bool              gY  = false;
  bool              gZ  = false;
  bool              g1b = false;
  
  tRayLocX = rktRAY.location().x();
  tRayLocY = rktRAY.location().y();
  tRayLocZ = rktRAY.location().z();

  if ( ( tRayLocX >= tBoundingBoxPoint1.x() ) && ( tRayLocX <= tBoundingBoxPoint2.x() ) &&
       ( tRayLocY >= tBoundingBoxPoint1.y() ) && ( tRayLocY <= tBoundingBoxPoint2.y() ) &&
       ( tRayLocZ >= tBoundingBoxPoint1.z() ) && ( tRayLocZ <= tBoundingBoxPoint2.z() ) )
  {
    tFirstRayPoint.set (tRayLocX, tRayLocY, tRayLocZ);
  }
  else
  {
    if ( !boundingBoxIntersection (rktRAY, tFirstRayPoint) )
    {
      return false;
    }
    g1b = true;
  }

  tRayDirX = rktRAY.direction().x();
  tRayDirY = rktRAY.direction().y();
  tRayDirZ = rktRAY.direction().z();

  tPyx = tRayDirY / tRayDirX;
  tPzx = tRayDirZ / tRayDirX;
  tPxy = tRayDirX / tRayDirY;
  tPzy = tRayDirZ / tRayDirY;
  tPxz = tRayDirX / tRayDirZ;
  tPyz = tRayDirY / tRayDirZ;
  
  // Lattice Increments in the three axis
  tLatticeIncrementX = ( tRayDirX > 0 ) ?  1 : -1;
  tLatticeIncrementY = ( tRayDirY > 0 ) ?  1 : -1;
  tLatticeIncrementZ = ( tRayDirZ > 0 ) ?  1 : -1;
  
  tFirstRayPointLCX = tFirstRayPoint.x() * tInvVoxelSize;
  tFirstRayPointLCY = tFirstRayPoint.y() * tInvVoxelSize;
  tFirstRayPointLCZ = tFirstRayPoint.z() * tInvVoxelSize;

  tVoxelX = (TUGLatticeCoord) floor (tFirstRayPointLCX);
  if ( (tFirstRayPointLCX - (TScalar) tVoxelX) < FX_EPSILON )
  {
    tVoxelNewX = ( tLatticeIncrementX > 0 ) ? tVoxelX : tVoxelX - 1;
    gX         = true;
  }
  else if ( ((TScalar) (tVoxelX + 1) - tFirstRayPointLCX) < FX_EPSILON )
  {
    tVoxelNewX = ( tLatticeIncrementX > 0 ) ? tVoxelX + 1 : tVoxelX;
    gX         = true;
  }
  else
  {
    tVoxelNewX = tVoxelX;
  }

  tVoxelY = (TUGLatticeCoord) floor (tFirstRayPointLCY);
  if ( (tFirstRayPointLCY - (TScalar) tVoxelY) < FX_EPSILON )
  {
    tVoxelNewY = ( tLatticeIncrementY > 0 ) ? tVoxelY : tVoxelY - 1;
    gY         = true;
  }
  else if ( ((TScalar) (tVoxelY + 1) - tFirstRayPointLCY) < FX_EPSILON )
  {
    tVoxelNewY = ( tLatticeIncrementY > 0 ) ? tVoxelY + 1 : tVoxelY;
    gY         = true;
  }
  else
  {
    tVoxelNewY = tVoxelY;
  }
  
  tVoxelZ = (TUGLatticeCoord) floor (tFirstRayPointLCZ);
  if ( (tFirstRayPointLCZ - (TScalar) tVoxelZ) < FX_EPSILON )
  {
    tVoxelNewZ = ( tLatticeIncrementZ > 0 ) ? tVoxelZ : tVoxelZ - 1;
    gZ         = true;
  }
  else if ( ((TScalar) (tVoxelZ + 1) - tFirstRayPointLCZ) < FX_EPSILON )
  {
    tVoxelNewZ = ( tLatticeIncrementZ > 0 ) ? tVoxelZ + 1 : tVoxelZ;
    gZ         = true;
  }
  else
  {
    tVoxelNewZ = tVoxelZ;
  }

  // Calculate New Bounding Point
  tBNewx = ( tLatticeIncrementX > 0 ) ? tVoxelNewX : tVoxelNewX + 1;
  tBNewy = ( tLatticeIncrementY > 0 ) ? tVoxelNewY : tVoxelNewY + 1;
  tBNewz = ( tLatticeIncrementZ > 0 ) ? tVoxelNewZ : tVoxelNewZ + 1;

  // Calculate tPointAdvanceX, tPointAdvanceY, tPointAdvanceZ
  if ( gX )
  {
    tPointAdvanceXx = tBNewx;
    tPointAdvanceXy = tFirstRayPointLCY;
    tPointAdvanceXz = tFirstRayPointLCZ;
  }
  else
  {
    tPointAdvanceXx = tBNewx + tLatticeIncrementX;
    tDeltaX         = (TScalar) tPointAdvanceXx - tFirstRayPointLCX;
    tPointAdvanceXy = tFirstRayPointLCY + tPyx * tDeltaX;
    tPointAdvanceXz = tFirstRayPointLCZ + tPzx * tDeltaX;
  }
  
  if ( gY )
  {
    tPointAdvanceYx = tFirstRayPointLCX;
    tPointAdvanceYy = tBNewy;
    tPointAdvanceYz = tFirstRayPointLCZ;
  }
  else
  {
    tPointAdvanceYy = tBNewy + tLatticeIncrementY;
    tDeltaY         = (TScalar) tPointAdvanceYy - tFirstRayPointLCY;
    tPointAdvanceYx = tFirstRayPointLCX + tPxy * tDeltaY;
    tPointAdvanceYz = tFirstRayPointLCZ + tPzy * tDeltaY;
  }
  
  if ( gZ )
  {
    tPointAdvanceZx = tFirstRayPointLCX;
    tPointAdvanceZy = tFirstRayPointLCY;
    tPointAdvanceZz = tBNewz;
  }
  else
  {
    tPointAdvanceZz = tBNewz + tLatticeIncrementZ;
    tDeltaZ         = (TScalar) tPointAdvanceZz - tFirstRayPointLCZ;
    tPointAdvanceZx = tFirstRayPointLCX + tPxz * tDeltaZ;
    tPointAdvanceZy = tFirstRayPointLCY + tPyz * tDeltaZ;
  }

  if ( !(gX || gY || gZ) )
  {
    tPointIn.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);

    tBx = tBNewx;
    tBy = tBNewy;
    tBz = tBNewz;
    
    if ( ( ( tLatticeIncrementY > 0 ) ? ( tPointAdvanceXy < ((TScalar) (tBy + 1) + FX_EPSILON) ) : ( tPointAdvanceXy > ((TScalar) (tBy - 1) - FX_EPSILON) ) ) &&
         ( ( tLatticeIncrementZ > 0 ) ? ( tPointAdvanceXz < ((TScalar) (tBz + 1) + FX_EPSILON) ) : ( tPointAdvanceXz > ((TScalar) (tBz - 1) - FX_EPSILON) ) ) )
    {
      tBNewx     += tLatticeIncrementX;
      tVoxelNewX += tLatticeIncrementX;
      tPointOut.set ((TScalar) tPointAdvanceXx, tPointAdvanceXy, tPointAdvanceXz);
    }
    if ( ( ( tLatticeIncrementX > 0 ) ? ( tPointAdvanceYx < ((TScalar) (tBx + 1) + FX_EPSILON) ) : ( tPointAdvanceYx > ((TScalar) (tBx - 1) - FX_EPSILON) ) ) &&
         ( ( tLatticeIncrementZ > 0 ) ? ( tPointAdvanceYz < ((TScalar) (tBz + 1) + FX_EPSILON) ) : ( tPointAdvanceYz > ((TScalar) (tBz - 1) - FX_EPSILON) ) ) )
    {
      tBNewy     += tLatticeIncrementY;
      tVoxelNewY += tLatticeIncrementY;
      tPointOut.set (tPointAdvanceYx, (TScalar) tPointAdvanceYy, tPointAdvanceYz);
    }
    if ( ( ( tLatticeIncrementX > 0 ) ? ( tPointAdvanceZx < ((TScalar) (tBx + 1) + FX_EPSILON) ) : ( tPointAdvanceZx > ((TScalar) (tBx - 1) - FX_EPSILON) ) ) &&
         ( ( tLatticeIncrementY > 0 ) ? ( tPointAdvanceZy < ((TScalar) (tBy + 1) + FX_EPSILON) ) : ( tPointAdvanceZy > ((TScalar) (tBy - 1) - FX_EPSILON) ) ) )
    {
      tBNewz     += tLatticeIncrementZ;
      tVoxelNewZ += tLatticeIncrementZ;
      tPointOut.set (tPointAdvanceZx, tPointAdvanceZy, (TScalar) tPointAdvanceZz);
    }
    
    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }
  else
  {
    tPointOut.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);
  }

  tPyx *= (TScalar) tLatticeIncrementX;
  tPzx *= (TScalar) tLatticeIncrementX;
  tPxy *= (TScalar) tLatticeIncrementY;
  tPzy *= (TScalar) tLatticeIncrementY;
  tPxz *= (TScalar) tLatticeIncrementZ;
  tPyz *= (TScalar) tLatticeIncrementZ;

  TUGLatticeCoord   tDestinationBx, tDestinationBy, tDestinationBz;
  TUGLatticeCoord   tBLatticeLimitX, tBLatticeLimitY, tBLatticeLimitZ;
  TVector           tRayDestinationLC;
  
  boundingPointRayDestination1 (rktRAY, tDestinationBx, tDestinationBy, tDestinationBz,
                                tLatticeIncrementX, tLatticeIncrementY, tLatticeIncrementZ,
                                tRayDestinationLC);

  tBLatticeLimitX = ( tLatticeIncrementX > 0 ) ? tMaxX : tMinX;
  tBLatticeLimitY = ( tLatticeIncrementY > 0 ) ? tMaxY : tMinY;
  tBLatticeLimitZ = ( tLatticeIncrementZ > 0 ) ? tMaxZ : tMinZ;

  tBLatticeLimitX *= tLatticeIncrementX;
  tBLatticeLimitY *= tLatticeIncrementY;
  tBLatticeLimitZ *= tLatticeIncrementZ;

  while ( ( (tBNewx * tLatticeIncrementX) < tBLatticeLimitX ) &&
          ( (tBNewy * tLatticeIncrementY) < tBLatticeLimitY ) &&
          ( (tBNewz * tLatticeIncrementZ) < tBLatticeLimitZ ) &&
          ( ( tBNewx != tDestinationBx ) || ( tBNewy != tDestinationBy ) ||
            ( tBNewz != tDestinationBz ) ) )
  {
    tPointIn = tPointOut;
    tVoxelX  = tVoxelNewX;
    tVoxelY  = tVoxelNewY;
    tVoxelZ  = tVoxelNewZ;
    tBx      = tBNewx;
    tBy      = tBNewy;
    tBz      = tBNewz;

    // Calculate tPointAdvanceX, tPointAdvanceY, tPointAdvanceZ
    if ( tBx == tPointAdvanceXx )
    {
      tPointAdvanceXx  = tBx + tLatticeIncrementX;
      tPointAdvanceXy += tPyx;
      tPointAdvanceXz += tPzx;
    }
    if ( tBy == tPointAdvanceYy )
    {
      tPointAdvanceYy  = tBy + tLatticeIncrementY;
      tPointAdvanceYx += tPxy;
      tPointAdvanceYz += tPzy;
    }
    if ( tBz == tPointAdvanceZz )
    {
      tPointAdvanceZz  = tBz + tLatticeIncrementZ;
      tPointAdvanceZx += tPxz;
      tPointAdvanceZy += tPyz;
    }

    if ( ( ( tLatticeIncrementY > 0 ) ? ( tPointAdvanceXy < ((TScalar) (tBy + 1) + FX_EPSILON) ) : ( tPointAdvanceXy > ((TScalar) (tBy - 1) - FX_EPSILON) ) ) &&
         ( ( tLatticeIncrementZ > 0 ) ? ( tPointAdvanceXz < ((TScalar) (tBz + 1) + FX_EPSILON) ) : ( tPointAdvanceXz > ((TScalar) (tBz - 1) - FX_EPSILON) ) ) )
    {
      tBNewx     += tLatticeIncrementX;
      tVoxelNewX += tLatticeIncrementX;
      tPointOut.set ((TScalar) tPointAdvanceXx, tPointAdvanceXy, tPointAdvanceXz);
    }
    if ( ( ( tLatticeIncrementX > 0 ) ? ( tPointAdvanceYx < ((TScalar) (tBx + 1) + FX_EPSILON) ) : ( tPointAdvanceYx > ((TScalar) (tBx - 1) - FX_EPSILON) ) ) &&
         ( ( tLatticeIncrementZ > 0 ) ? ( tPointAdvanceYz < ((TScalar) (tBz + 1) + FX_EPSILON) ) : ( tPointAdvanceYz > ((TScalar) (tBz - 1) - FX_EPSILON) ) ) )
    {
      tBNewy     += tLatticeIncrementY;
      tVoxelNewY += tLatticeIncrementY;
      tPointOut.set (tPointAdvanceYx, (TScalar) tPointAdvanceYy, tPointAdvanceYz);
    }
    if ( ( ( tLatticeIncrementX > 0 ) ? ( tPointAdvanceZx < ((TScalar) (tBx + 1) + FX_EPSILON) ) : ( tPointAdvanceZx > ((TScalar) (tBx - 1) - FX_EPSILON) ) ) &&
         ( ( tLatticeIncrementY > 0 ) ? ( tPointAdvanceZy < ((TScalar) (tBy + 1) + FX_EPSILON) ) : ( tPointAdvanceZy > ((TScalar) (tBy - 1) - FX_EPSILON) ) ) )
    {
      tBNewz     += tLatticeIncrementZ;
      tVoxelNewZ += tLatticeIncrementZ;
      tPointOut.set (tPointAdvanceZx, tPointAdvanceZy, (TScalar) tPointAdvanceZz);
    }

    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  if ( ( tBNewx == tDestinationBx ) && ( tBNewy == tDestinationBy ) &&
       ( tBNewz == tDestinationBz ) )
  {
    if ( findIntersectionInsideVoxel (tVoxelNewX, tVoxelNewY, tVoxelNewZ, tPointOut, tRayDestinationLC, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  return false;
  
}  /* findFirstIntersection1() */


bool TUniformGrid::findFirstIntersection2 (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TScalar           tRayDirX, tRayDirZ;
  TScalar           tRayLocX, tRayLocY, tRayLocZ;
  TVector           tFirstRayPoint;                                            // First ray point on lattice (global coords)
  TScalar           tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ;   // First ray point on lattice (lattice coords)
  TScalar           tPzx;
  TScalar           tPxz;
  TUGLatticeCoord   tLatticeIncrementX, tLatticeIncrementZ;
  TUGLatticeCoord   tVoxelX, tVoxelY, tVoxelZ;            // Voxel key
  TUGLatticeCoord   tVoxelNewX, tVoxelNewZ;               // Voxel key
  TUGLatticeCoord   tBx, tBz;                             // Bounding Advance Point
  TUGLatticeCoord   tBNewx, tBNewz;                       // Bounding Advance Point
  TScalar           tDeltaX, tDeltaZ;
  TUGLatticeCoord   tPointAdvanceXx;                      // X Advance Point (TUGLatticeCoord, TScalar, TScalar)
  TScalar           tPointAdvanceXz;
  TUGLatticeCoord   tPointAdvanceZz;                      // Z Advance Point (TScalar, TScalar, TUGLatticeCoord)
  TScalar           tPointAdvanceZx;
  TVector           tPointIn;
  TVector           tPointOut;
  bool              gX  = false;
  bool              gZ  = false;
  bool              g1b = false;
  
  tRayLocX = rktRAY.location().x();
  tRayLocY = rktRAY.location().y();
  tRayLocZ = rktRAY.location().z();

  if ( ( tRayLocX >= tBoundingBoxPoint1.x() ) && ( tRayLocX <= tBoundingBoxPoint2.x() ) &&
       ( tRayLocZ >= tBoundingBoxPoint1.z() ) && ( tRayLocZ <= tBoundingBoxPoint2.z() ) )
  {
    tFirstRayPoint.set (tRayLocX, tRayLocY, tRayLocZ);
  }
  else
  {
    if ( !boundingBoxIntersection (rktRAY, tFirstRayPoint) )
    {
      return false;
    }
    g1b = true;
  }

  tRayDirX = rktRAY.direction().x();
  tRayDirZ = rktRAY.direction().z();

  tPzx = tRayDirZ / tRayDirX;
  tPxz = tRayDirX / tRayDirZ;
  
  // Lattice Increments in the three axis
  tLatticeIncrementX = ( tRayDirX > 0 ) ?  1 : -1;
  tLatticeIncrementZ = ( tRayDirZ > 0 ) ?  1 : -1;
  
  tFirstRayPointLCX = tFirstRayPoint.x() * tInvVoxelSize;
  tFirstRayPointLCY = tFirstRayPoint.y() * tInvVoxelSize;
  tFirstRayPointLCZ = tFirstRayPoint.z() * tInvVoxelSize;

  tVoxelX = (TUGLatticeCoord) floor (tFirstRayPointLCX);
  if ( (tFirstRayPointLCX - (TScalar) tVoxelX) < FX_EPSILON )
  {
    tVoxelNewX = ( tLatticeIncrementX > 0 ) ? tVoxelX : tVoxelX - 1;
    gX         = true;
  }
  else if ( ((TScalar) (tVoxelX + 1) - tFirstRayPointLCX) < FX_EPSILON )
  {
    tVoxelNewX = ( tLatticeIncrementX > 0 ) ? tVoxelX + 1 : tVoxelX;
    gX         = true;
  }
  else
  {
    tVoxelNewX = tVoxelX;
  }

  tVoxelY = (TUGLatticeCoord) floor (tFirstRayPointLCY);
  tVoxelZ = (TUGLatticeCoord) floor (tFirstRayPointLCZ);
  if ( (tFirstRayPointLCZ - (TScalar) tVoxelZ) < FX_EPSILON )
  {
    tVoxelNewZ = ( tLatticeIncrementZ > 0 ) ? tVoxelZ : tVoxelZ - 1;
    gZ         = true;
  }
  else if ( ((TScalar) (tVoxelZ + 1) - tFirstRayPointLCZ) < FX_EPSILON )
  {
    tVoxelNewZ = ( tLatticeIncrementZ > 0 ) ? tVoxelZ + 1 : tVoxelZ;
    gZ         = true;
  }
  else
  {
    tVoxelNewZ = tVoxelZ;
  }

  // Calculate New Bounding Point
  tBNewx = ( tLatticeIncrementX > 0 ) ? tVoxelNewX : tVoxelNewX + 1;
  tBNewz = ( tLatticeIncrementZ > 0 ) ? tVoxelNewZ : tVoxelNewZ + 1;

  // Calculate tPointAdvanceX, tPointAdvanceZ
  if ( gX )
  {
    tPointAdvanceXx = tBNewx;
    tPointAdvanceXz = tFirstRayPointLCZ;
  }
  else
  {
    tPointAdvanceXx = tBNewx + tLatticeIncrementX;
    tDeltaX         = (TScalar) tPointAdvanceXx - tFirstRayPointLCX;
    tPointAdvanceXz = tFirstRayPointLCZ + tPzx * tDeltaX;
  }
  
  if ( gZ )
  {
    tPointAdvanceZx = tFirstRayPointLCX;
    tPointAdvanceZz = tBNewz;
  }
  else
  {
    tPointAdvanceZz = tBNewz + tLatticeIncrementZ;
    tDeltaZ         = (TScalar) tPointAdvanceZz - tFirstRayPointLCZ;
    tPointAdvanceZx = tFirstRayPointLCX + tPxz * tDeltaZ;
  }

  if ( !(gX || gZ) )
  {
    tPointIn.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);

    tBx = tBNewx;
    tBz = tBNewz;
    
    if ( ( ( tLatticeIncrementZ > 0 ) ? ( tPointAdvanceXz < ((TScalar) (tBz + 1) + FX_EPSILON) ) : ( tPointAdvanceXz > ((TScalar) (tBz - 1) - FX_EPSILON) ) ) )
    {
      tBNewx     += tLatticeIncrementX;
      tVoxelNewX += tLatticeIncrementX;
      tPointOut.set ((TScalar) tPointAdvanceXx, tFirstRayPointLCY, tPointAdvanceXz);
    }
    if ( ( ( tLatticeIncrementX > 0 ) ? ( tPointAdvanceZx < ((TScalar) (tBx + 1) + FX_EPSILON) ) : ( tPointAdvanceZx > ((TScalar) (tBx - 1) - FX_EPSILON) ) ) )
    {
      tBNewz     += tLatticeIncrementZ;
      tVoxelNewZ += tLatticeIncrementZ;
      tPointOut.set (tPointAdvanceZx, tFirstRayPointLCY, (TScalar) tPointAdvanceZz);
    }
    
    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }
  else
  {
    tPointOut.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);
  }

  tPzx *= (TScalar) tLatticeIncrementX;
  tPxz *= (TScalar) tLatticeIncrementZ;

  TUGLatticeCoord   tDestinationBx, tDestinationBz;
  TUGLatticeCoord   tBLatticeLimitX, tBLatticeLimitZ;
  TVector           tRayDestinationLC;
  
  boundingPointRayDestination2 (rktRAY, tDestinationBx, tDestinationBz,
                                tLatticeIncrementX, tLatticeIncrementZ,
                                tRayDestinationLC);

  tBLatticeLimitX  = ( tLatticeIncrementX > 0 ) ? tMaxX : tMinX;
  tBLatticeLimitZ  = ( tLatticeIncrementZ > 0 ) ? tMaxZ : tMinZ;
  tBLatticeLimitX *= tLatticeIncrementX;
  tBLatticeLimitZ *= tLatticeIncrementZ;

  while ( ( (tBNewx * tLatticeIncrementX) < tBLatticeLimitX ) &&
          ( (tBNewz * tLatticeIncrementZ) < tBLatticeLimitZ ) &&
          ( ( tBNewx != tDestinationBx ) || ( tBNewz != tDestinationBz ) ) )
  {
    tPointIn = tPointOut;
    tVoxelX  = tVoxelNewX;
    tVoxelZ  = tVoxelNewZ;
    tBx      = tBNewx;
    tBz      = tBNewz;

    // Calculate tPointAdvanceX, tPointAdvanceZ
    if ( tBx == tPointAdvanceXx )
    {
      tPointAdvanceXx  = tBx + tLatticeIncrementX;
      tPointAdvanceXz += tPzx;
    }
    if ( tBz == tPointAdvanceZz )
    {
      tPointAdvanceZz  = tBz + tLatticeIncrementZ;
      tPointAdvanceZx += tPxz;
    }

    if ( ( ( tLatticeIncrementZ > 0 ) ? ( tPointAdvanceXz < ((TScalar) (tBz + 1) + FX_EPSILON) ) : ( tPointAdvanceXz > ((TScalar) (tBz - 1) - FX_EPSILON) ) ) )
    {
      tBNewx     += tLatticeIncrementX;
      tVoxelNewX += tLatticeIncrementX;
      tPointOut.set ((TScalar) tPointAdvanceXx, tFirstRayPointLCY, tPointAdvanceXz);
    }
    if ( ( ( tLatticeIncrementX > 0 ) ? ( tPointAdvanceZx < ((TScalar) (tBx + 1) + FX_EPSILON) ) : ( tPointAdvanceZx > ((TScalar) (tBx - 1) - FX_EPSILON) ) ) )
    {
      tBNewz     += tLatticeIncrementZ;
      tVoxelNewZ += tLatticeIncrementZ;
      tPointOut.set (tPointAdvanceZx, tFirstRayPointLCY, (TScalar) tPointAdvanceZz);
    }

    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  if ( ( tBNewx == tDestinationBx ) && ( tBNewz == tDestinationBz ) )
  {
    if ( findIntersectionInsideVoxel (tVoxelNewX, tVoxelY, tVoxelNewZ, tPointOut, tRayDestinationLC, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  return false;
  
}  /* findFirstIntersection2() */


bool TUniformGrid::findFirstIntersection3 (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TScalar           tRayDirY, tRayDirZ;
  TScalar           tRayLocX, tRayLocY, tRayLocZ;
  TVector           tFirstRayPoint;                                            // First ray point on lattice (global coords)
  TScalar           tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ;   // First ray point on lattice (lattice coords)
  TScalar           tPzy;
  TScalar           tPyz;
  TUGLatticeCoord   tLatticeIncrementY, tLatticeIncrementZ;
  TUGLatticeCoord   tVoxelX, tVoxelY, tVoxelZ;            // Voxel key
  TUGLatticeCoord   tVoxelNewY, tVoxelNewZ;               // Voxel key
  TUGLatticeCoord   tBy, tBz;                             // Bounding Advance Point
  TUGLatticeCoord   tBNewy, tBNewz;                       // Bounding Advance Point
  TScalar           tDeltaY, tDeltaZ;
  TUGLatticeCoord   tPointAdvanceYy;                      // Y Advance Point (TScalar, TUGLatticeCoord, TScalar)
  TScalar           tPointAdvanceYz;
  TUGLatticeCoord   tPointAdvanceZz;                      // Z Advance Point (TScalar, TScalar, TUGLatticeCoord)
  TScalar           tPointAdvanceZy;
  TVector           tPointIn;
  TVector           tPointOut;
  bool              gY  = false;
  bool              gZ  = false;
  bool              g1b = false;
  
  tRayLocX = rktRAY.location().x();
  tRayLocY = rktRAY.location().y();
  tRayLocZ = rktRAY.location().z();

  if ( ( tRayLocX >= tBoundingBoxPoint1.x() ) && ( tRayLocX <= tBoundingBoxPoint2.x() ) &&
       ( tRayLocY >= tBoundingBoxPoint1.y() ) && ( tRayLocY <= tBoundingBoxPoint2.y() ) &&
       ( tRayLocZ >= tBoundingBoxPoint1.z() ) && ( tRayLocZ <= tBoundingBoxPoint2.z() ) )
  {
    tFirstRayPoint.set (tRayLocX, tRayLocY, tRayLocZ);
  }
  else
  {
    if ( !boundingBoxIntersection (rktRAY, tFirstRayPoint) )
    {
      return false;
    }
    g1b = true;
  }

  tRayDirY = rktRAY.direction().y();
  tRayDirZ = rktRAY.direction().z();

  tPzy = tRayDirZ / tRayDirY;
  tPyz = tRayDirY / tRayDirZ;
  
  // Lattice Increments in the three axis
  tLatticeIncrementY = ( tRayDirY > 0 ) ?  1 : -1;
  tLatticeIncrementZ = ( tRayDirZ > 0 ) ?  1 : -1;
  
  tFirstRayPointLCX = tFirstRayPoint.x() * tInvVoxelSize;
  tFirstRayPointLCY = tFirstRayPoint.y() * tInvVoxelSize;
  tFirstRayPointLCZ = tFirstRayPoint.z() * tInvVoxelSize;

  tVoxelX = (TUGLatticeCoord) floor (tFirstRayPointLCX);
  tVoxelY = (TUGLatticeCoord) floor (tFirstRayPointLCY);
  if ( (tFirstRayPointLCY - (TScalar) tVoxelY) < FX_EPSILON )
  {
    tVoxelNewY = ( tLatticeIncrementY > 0 ) ? tVoxelY : tVoxelY - 1;
    gY         = true;
  }
  else if ( ((TScalar) (tVoxelY + 1) - tFirstRayPointLCY) < FX_EPSILON )
  {
    tVoxelNewY = ( tLatticeIncrementY > 0 ) ? tVoxelY + 1 : tVoxelY;
    gY         = true;
  }
  else
  {
    tVoxelNewY = tVoxelY;
  }
  
  tVoxelZ = (TUGLatticeCoord) floor (tFirstRayPointLCZ);
  if ( (tFirstRayPointLCZ - (TScalar) tVoxelZ) < FX_EPSILON )
  {
    tVoxelNewZ = ( tLatticeIncrementZ > 0 ) ? tVoxelZ : tVoxelZ - 1;
    gZ         = true;
  }
  else if ( ((TScalar) (tVoxelZ + 1) - tFirstRayPointLCZ) < FX_EPSILON )
  {
    tVoxelNewZ = ( tLatticeIncrementZ > 0 ) ? tVoxelZ + 1 : tVoxelZ;
    gZ         = true;
  }
  else
  {
    tVoxelNewZ = tVoxelZ;
  }

  // Calculate New Bounding Point
  tBNewy = ( tLatticeIncrementY > 0 ) ? tVoxelNewY : tVoxelNewY + 1;
  tBNewz = ( tLatticeIncrementZ > 0 ) ? tVoxelNewZ : tVoxelNewZ + 1;

  // Calculate tPointAdvanceY, tPointAdvanceZ
  if ( gY )
  {
    tPointAdvanceYy = tBNewy;
    tPointAdvanceYz = tFirstRayPointLCZ;
  }
  else
  {
    tPointAdvanceYy = tBNewy + tLatticeIncrementY;
    tDeltaY         = (TScalar) tPointAdvanceYy - tFirstRayPointLCY;
    tPointAdvanceYz = tFirstRayPointLCZ + tPzy * tDeltaY;
  }
  
  if ( gZ )
  {
    tPointAdvanceZy = tFirstRayPointLCY;
    tPointAdvanceZz = tBNewz;
  }
  else
  {
    tPointAdvanceZz = tBNewz + tLatticeIncrementZ;
    tDeltaZ         = (TScalar) tPointAdvanceZz - tFirstRayPointLCZ;
    tPointAdvanceZy = tFirstRayPointLCY + tPyz * tDeltaZ;
  }

  if ( !(gY || gZ) )
  {
    tPointIn.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);

    tBy = tBNewy;
    tBz = tBNewz;
    
    if ( ( ( tLatticeIncrementZ > 0 ) ? ( tPointAdvanceYz < ((TScalar) (tBz + 1) + FX_EPSILON) ) : ( tPointAdvanceYz > ((TScalar) (tBz - 1) - FX_EPSILON) ) ) )
    {
      tBNewy     += tLatticeIncrementY;
      tVoxelNewY += tLatticeIncrementY;
      tPointOut.set (tFirstRayPointLCX, (TScalar) tPointAdvanceYy, tPointAdvanceYz);
    }
    if ( ( ( tLatticeIncrementY > 0 ) ? ( tPointAdvanceZy < ((TScalar) (tBy + 1) + FX_EPSILON) ) : ( tPointAdvanceZy > ((TScalar) (tBy - 1) - FX_EPSILON) ) ) )
    {
      tBNewz     += tLatticeIncrementZ;
      tVoxelNewZ += tLatticeIncrementZ;
      tPointOut.set (tFirstRayPointLCX, tPointAdvanceZy, (TScalar) tPointAdvanceZz);
    }
    
    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }
  else
  {
    tPointOut.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);
  }

  tPzy *= (TScalar) tLatticeIncrementY;
  tPyz *= (TScalar) tLatticeIncrementZ;

  TUGLatticeCoord   tDestinationBy, tDestinationBz;
  TUGLatticeCoord   tBLatticeLimitY, tBLatticeLimitZ;
  TVector           tRayDestinationLC;
  
  boundingPointRayDestination3 (rktRAY, tDestinationBy, tDestinationBz,
                                tLatticeIncrementY, tLatticeIncrementZ,
                                tRayDestinationLC);

  tBLatticeLimitY  = ( tLatticeIncrementY > 0 ) ? tMaxY : tMinY;
  tBLatticeLimitZ  = ( tLatticeIncrementZ > 0 ) ? tMaxZ : tMinZ;
  tBLatticeLimitY *= tLatticeIncrementY;
  tBLatticeLimitZ *= tLatticeIncrementZ;

  while ( ( (tBNewy * tLatticeIncrementY) < tBLatticeLimitY ) &&
          ( (tBNewz * tLatticeIncrementZ) < tBLatticeLimitZ ) &&
          ( ( tBNewy != tDestinationBy ) || ( tBNewz != tDestinationBz ) ) )
  {
    tPointIn = tPointOut;
    tVoxelY  = tVoxelNewY;
    tVoxelZ  = tVoxelNewZ;
    tBy      = tBNewy;
    tBz      = tBNewz;

    // Calculate tPointAdvanceY, tPointAdvanceZ
    if ( tBy == tPointAdvanceYy )
    {
      tPointAdvanceYy  = tBy + tLatticeIncrementY;
      tPointAdvanceYz += tPzy;
    }
    if ( tBz == tPointAdvanceZz )
    {
      tPointAdvanceZz  = tBz + tLatticeIncrementZ;
      tPointAdvanceZy += tPyz;
    }

    if ( ( ( tLatticeIncrementZ > 0 ) ? ( tPointAdvanceYz < ((TScalar) (tBz + 1) + FX_EPSILON) ) : ( tPointAdvanceYz > ((TScalar) (tBz - 1) - FX_EPSILON) ) ) )
    {
      tBNewy     += tLatticeIncrementY;
      tVoxelNewY += tLatticeIncrementY;
      tPointOut.set (tFirstRayPointLCX, (TScalar) tPointAdvanceYy, tPointAdvanceYz);
    }
    if ( ( ( tLatticeIncrementY > 0 ) ? ( tPointAdvanceZy < ((TScalar) (tBy + 1) + FX_EPSILON) ) : ( tPointAdvanceZy > ((TScalar) (tBy - 1) - FX_EPSILON) ) ) )
    {
      tBNewz     += tLatticeIncrementZ;
      tVoxelNewZ += tLatticeIncrementZ;
      tPointOut.set (tFirstRayPointLCX, tPointAdvanceZy, (TScalar) tPointAdvanceZz);
    }

    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  if ( ( tBNewy == tDestinationBy ) && ( tBNewz == tDestinationBz ) )
  {
    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelNewY, tVoxelNewZ, tPointOut, tRayDestinationLC, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  return false;

}  /* findFirstIntersection3() */


bool TUniformGrid::findFirstIntersection4 (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TScalar           tRayDirX, tRayDirY;
  TScalar           tRayLocX, tRayLocY, tRayLocZ;
  TVector           tFirstRayPoint;                                            // First ray point on lattice (global coords)
  TScalar           tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ;   // First ray point on lattice (lattice coords)
  TScalar           tPyx;
  TScalar           tPxy;
  TUGLatticeCoord   tLatticeIncrementX, tLatticeIncrementY;
  TUGLatticeCoord   tVoxelX, tVoxelY, tVoxelZ;            // Voxel key
  TUGLatticeCoord   tVoxelNewX, tVoxelNewY;               // Voxel key
  TUGLatticeCoord   tBx, tBy;                             // Bounding Advance Point
  TUGLatticeCoord   tBNewx, tBNewy;                       // Bounding Advance Point
  TScalar           tDeltaX, tDeltaY;
  TUGLatticeCoord   tPointAdvanceXx;                      // X Advance Point (TUGLatticeCoord, TScalar, TScalar)
  TScalar           tPointAdvanceXy;
  TUGLatticeCoord   tPointAdvanceYy;                      // Y Advance Point (TScalar, TUGLatticeCoord, TScalar)
  TScalar           tPointAdvanceYx;
  TVector           tPointIn;
  TVector           tPointOut;
  bool              gX  = false;
  bool              gY  = false;
  bool              g1b = false;
  
  tRayLocX = rktRAY.location().x();
  tRayLocY = rktRAY.location().y();
  tRayLocZ = rktRAY.location().z();

  if ( ( tRayLocX >= tBoundingBoxPoint1.x() ) && ( tRayLocX <= tBoundingBoxPoint2.x() ) &&
       ( tRayLocY >= tBoundingBoxPoint1.y() ) && ( tRayLocY <= tBoundingBoxPoint2.y() ) &&
       ( tRayLocZ >= tBoundingBoxPoint1.z() ) && ( tRayLocZ <= tBoundingBoxPoint2.z() ) )
  {
    tFirstRayPoint.set (tRayLocX, tRayLocY, tRayLocZ);
  }
  else
  {
    if ( !boundingBoxIntersection (rktRAY, tFirstRayPoint) )
    {
      return false;
    }
    g1b = true;
  }

  tRayDirX = rktRAY.direction().x();
  tRayDirY = rktRAY.direction().y();

  tPyx = tRayDirY / tRayDirX;
  tPxy = tRayDirX / tRayDirY;
  
  // Lattice Increments in the three axis
  tLatticeIncrementX = ( tRayDirX > 0 ) ?  1 : -1;
  tLatticeIncrementY = ( tRayDirY > 0 ) ?  1 : -1;
  
  tFirstRayPointLCX = tFirstRayPoint.x() * tInvVoxelSize;
  tFirstRayPointLCY = tFirstRayPoint.y() * tInvVoxelSize;
  tFirstRayPointLCZ = tFirstRayPoint.z() * tInvVoxelSize;

  tVoxelX = (TUGLatticeCoord) floor (tFirstRayPointLCX);
  if ( (tFirstRayPointLCX - (TScalar) tVoxelX) < FX_EPSILON )
  {
    tVoxelNewX = ( tLatticeIncrementX > 0 ) ? tVoxelX : tVoxelX - 1;
    gX         = true;
  }
  else if ( ((TScalar) (tVoxelX + 1) - tFirstRayPointLCX) < FX_EPSILON )
  {
    tVoxelNewX = ( tLatticeIncrementX > 0 ) ? tVoxelX + 1 : tVoxelX;
    gX         = true;
  }
  else
  {
    tVoxelNewX = tVoxelX;
  }

  tVoxelY = (TUGLatticeCoord) floor (tFirstRayPointLCY);
  if ( (tFirstRayPointLCY - (TScalar) tVoxelY) < FX_EPSILON )
  {
    tVoxelNewY = ( tLatticeIncrementY > 0 ) ? tVoxelY : tVoxelY - 1;
    gY         = true;
  }
  else if ( ((TScalar) (tVoxelY + 1) - tFirstRayPointLCY) < FX_EPSILON )
  {
    tVoxelNewY = ( tLatticeIncrementY > 0 ) ? tVoxelY + 1 : tVoxelY;
    gY         = true;
  }
  else
  {
    tVoxelNewY = tVoxelY;
  }
  
  tVoxelZ = (TUGLatticeCoord) floor (tFirstRayPointLCZ);

  // Calculate New Bounding Point
  tBNewx = ( tLatticeIncrementX > 0 ) ? tVoxelNewX : tVoxelNewX + 1;
  tBNewy = ( tLatticeIncrementY > 0 ) ? tVoxelNewY : tVoxelNewY + 1;

  // Calculate tPointAdvanceX, tPointAdvanceY, tPointAdvanceZ
  if ( gX )
  {
    tPointAdvanceXx = tBNewx;
    tPointAdvanceXy = tFirstRayPointLCY;
  }
  else
  {
    tPointAdvanceXx = tBNewx + tLatticeIncrementX;
    tDeltaX         = (TScalar) tPointAdvanceXx - tFirstRayPointLCX;
    tPointAdvanceXy = tFirstRayPointLCY + tPyx * tDeltaX;
  }
  
  if ( gY )
  {
    tPointAdvanceYx = tFirstRayPointLCX;
    tPointAdvanceYy = tBNewy;
  }
  else
  {
    tPointAdvanceYy = tBNewy + tLatticeIncrementY;
    tDeltaY         = (TScalar) tPointAdvanceYy - tFirstRayPointLCY;
    tPointAdvanceYx = tFirstRayPointLCX + tPxy * tDeltaY;
  }
  
  if ( !(gX || gY) )
  {

    tPointIn.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);

    tBx = tBNewx;
    tBy = tBNewy;
    
    if ( ( ( tLatticeIncrementY > 0 ) ? ( tPointAdvanceXy < ((TScalar) (tBy + 1) + FX_EPSILON) ) : ( tPointAdvanceXy > ((TScalar) (tBy - 1) - FX_EPSILON) ) ) )
    {
      tBNewx     += tLatticeIncrementX;
      tVoxelNewX += tLatticeIncrementX;
      tPointOut.set ((TScalar) tPointAdvanceXx, tPointAdvanceXy, tFirstRayPointLCZ);
    }
    if ( ( ( tLatticeIncrementX > 0 ) ? ( tPointAdvanceYx < ((TScalar) (tBx + 1) + FX_EPSILON) ) : ( tPointAdvanceYx > ((TScalar) (tBx - 1) - FX_EPSILON) ) ) )
    {
      tBNewy     += tLatticeIncrementY;
      tVoxelNewY += tLatticeIncrementY;
      tPointOut.set (tPointAdvanceYx, (TScalar) tPointAdvanceYy, tFirstRayPointLCZ);
    }
    
    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }
  else
  {
    tPointOut.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);
  }

  tPyx *= (TScalar) tLatticeIncrementX;
  tPxy *= (TScalar) tLatticeIncrementY;

  TUGLatticeCoord   tDestinationBx, tDestinationBy;
  TUGLatticeCoord   tBLatticeLimitX, tBLatticeLimitY;
  TVector           tRayDestinationLC;
  
  boundingPointRayDestination4 (rktRAY, tDestinationBx, tDestinationBy,
                                tLatticeIncrementX, tLatticeIncrementY,
                                tRayDestinationLC);

  tBLatticeLimitX  = ( tLatticeIncrementX > 0 ) ? tMaxX : tMinX;
  tBLatticeLimitY  = ( tLatticeIncrementY > 0 ) ? tMaxY : tMinY;
  tBLatticeLimitX *= tLatticeIncrementX;
  tBLatticeLimitY *= tLatticeIncrementY;

  while ( ( (tBNewx * tLatticeIncrementX) < tBLatticeLimitX ) &&
          ( (tBNewy * tLatticeIncrementY) < tBLatticeLimitY ) &&
          ( ( tBNewx != tDestinationBx ) || ( tBNewy != tDestinationBy ) ) )
  {
    tPointIn = tPointOut;
    tVoxelX  = tVoxelNewX;
    tVoxelY  = tVoxelNewY;
    tBx      = tBNewx;
    tBy      = tBNewy;

    // Calculate tPointAdvanceX, tPointAdvanceY
    if ( tBx == tPointAdvanceXx )
    {
      tPointAdvanceXx  = tBx + tLatticeIncrementX;
      tPointAdvanceXy += tPyx;
    }
    if ( tBy == tPointAdvanceYy )
    {
      tPointAdvanceYy  = tBy + tLatticeIncrementY;
      tPointAdvanceYx += tPxy;
    }

    if ( ( ( tLatticeIncrementY > 0 ) ? ( tPointAdvanceXy < ((TScalar) (tBy + 1) + FX_EPSILON) ) : ( tPointAdvanceXy > ((TScalar) (tBy - 1) - FX_EPSILON) ) ) )
    {
      tBNewx     += tLatticeIncrementX;
      tVoxelNewX += tLatticeIncrementX;
      tPointOut.set ((TScalar) tPointAdvanceXx, tPointAdvanceXy, tFirstRayPointLCZ);
    }
    if ( ( ( tLatticeIncrementX > 0 ) ? ( tPointAdvanceYx < ((TScalar) (tBx + 1) + FX_EPSILON) ) : ( tPointAdvanceYx > ((TScalar) (tBx - 1) - FX_EPSILON) ) ) )
    {
      tBNewy     += tLatticeIncrementY;
      tVoxelNewY += tLatticeIncrementY;
      tPointOut.set (tPointAdvanceYx, (TScalar) tPointAdvanceYy, tFirstRayPointLCZ);
    }

    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  if ( ( tBNewx == tDestinationBx ) && ( tBNewy == tDestinationBy ) )
  {
    if ( findIntersectionInsideVoxel (tVoxelNewX, tVoxelNewY, tVoxelZ, tPointOut, tRayDestinationLC, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  return false;
  
}  /* findFirstIntersection4() */


bool TUniformGrid::findFirstIntersection5 (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TScalar           tRayDirY;
  TScalar           tRayLocX, tRayLocY, tRayLocZ;
  TVector           tFirstRayPoint;                                            // First ray point on lattice (global coords)
  TScalar           tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ;   // First ray point on lattice (lattice coords)
  TUGLatticeCoord   tLatticeIncrementY;
  TUGLatticeCoord   tVoxelX, tVoxelY, tVoxelZ;            // Voxel key
  TUGLatticeCoord   tVoxelNewY;                           // Voxel key
  TUGLatticeCoord   tBy;                                  // Bounding Advance Point
  TUGLatticeCoord   tBNewy;                               // Bounding Advance Point
  TUGLatticeCoord   tPointAdvanceYy;                      // Y Advance Point (TScalar, TUGLatticeCoord, TScalar)
  TVector           tPointIn;
  TVector           tPointOut;
  bool              gY  = false;
  bool              g1b = false;
  
  tRayLocX = rktRAY.location().x();
  tRayLocY = rktRAY.location().y();
  tRayLocZ = rktRAY.location().z();

  if ( ( tRayLocX >= tBoundingBoxPoint1.x() ) && ( tRayLocX <= tBoundingBoxPoint2.x() ) &&
       ( tRayLocY >= tBoundingBoxPoint1.y() ) && ( tRayLocY <= tBoundingBoxPoint2.y() ) &&
       ( tRayLocZ >= tBoundingBoxPoint1.z() ) && ( tRayLocZ <= tBoundingBoxPoint2.z() ) )
  {
    tFirstRayPoint.set (tRayLocX, tRayLocY, tRayLocZ);
  }
  else
  {
    if ( !boundingBoxIntersection (rktRAY, tFirstRayPoint) )
    {
      return false;
    }
    g1b = true;
  }

  tRayDirY = rktRAY.direction().y();

  // Lattice Increments in the three axis
  tLatticeIncrementY = ( tRayDirY > 0 ) ?  1 : -1;
  
  tFirstRayPointLCX = tFirstRayPoint.x() * tInvVoxelSize;
  tFirstRayPointLCY = tFirstRayPoint.y() * tInvVoxelSize;
  tFirstRayPointLCZ = tFirstRayPoint.z() * tInvVoxelSize;

  tVoxelX = (TUGLatticeCoord) floor (tFirstRayPointLCX);
  tVoxelY = (TUGLatticeCoord) floor (tFirstRayPointLCY);
  if ( (tFirstRayPointLCY - (TScalar) tVoxelY) < FX_EPSILON )
  {
    tVoxelNewY = ( tLatticeIncrementY > 0 ) ? tVoxelY : tVoxelY - 1;
    gY         = true;
  }
  else if ( ((TScalar) (tVoxelY + 1) - tFirstRayPointLCY) < FX_EPSILON )
  {
    tVoxelNewY = ( tLatticeIncrementY > 0 ) ? tVoxelY + 1 : tVoxelY;
    gY         = true;
  }
  else
  {
    tVoxelNewY = tVoxelY;
  }
  
  tVoxelZ = (TUGLatticeCoord) floor (tFirstRayPointLCZ);

  // Calculate New Bounding Point
  tBNewy = ( tLatticeIncrementY > 0 ) ? tVoxelNewY : tVoxelNewY + 1;

  // Calculate tPointAdvanceY
  if ( gY )
  {
    tPointAdvanceYy = tBNewy;
  }
  else
  {
    tPointAdvanceYy = tBNewy + tLatticeIncrementY;
  }
  
  if ( !(gY) )
  {
    tPointIn.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);

    tBy = tBNewy;
    
    tBNewy     += tLatticeIncrementY;
    tVoxelNewY += tLatticeIncrementY;
    tPointOut.set (tFirstRayPointLCX, (TScalar) tPointAdvanceYy, tFirstRayPointLCZ);
    
    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }
  else
  {
    tPointOut.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);
  }

  TUGLatticeCoord   tDestinationBy;
  TUGLatticeCoord   tBLatticeLimitY;
  TVector           tRayDestinationLC;
  
  boundingPointRayDestination5 (rktRAY, tDestinationBy,
                                tLatticeIncrementY,
                                tRayDestinationLC);

  tBLatticeLimitY  = ( tLatticeIncrementY > 0 ) ? tMaxY : tMinY;
  tBLatticeLimitY *= tLatticeIncrementY;

  while ( ( (tBNewy * tLatticeIncrementY) < tBLatticeLimitY ) &&
          ( ( tBNewy != tDestinationBy ) ) )
  {
    tPointIn = tPointOut;
    tVoxelY  = tVoxelNewY;
    tBy      = tBNewy;

    // Calculate tPointAdvanceY
    if ( tBy == tPointAdvanceYy )
    {
      tPointAdvanceYy  = tBy + tLatticeIncrementY;
    }

    tBNewy     += tLatticeIncrementY;
    tVoxelNewY += tLatticeIncrementY;
    tPointOut.set (tFirstRayPointLCX, (TScalar) tPointAdvanceYy, tFirstRayPointLCZ);

    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  if ( ( tBNewy == tDestinationBy ) )
  {
    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelNewY, tVoxelZ, tPointOut, tRayDestinationLC, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  return false;
  
}  /* findFirstIntersection5() */


bool TUniformGrid::findFirstIntersection6 (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TScalar           tRayDirX;
  TScalar           tRayLocX, tRayLocY, tRayLocZ;
  TVector           tFirstRayPoint;                                            // First ray point on lattice (global coords)
  TScalar           tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ;   // First ray point on lattice (lattice coords)
  TUGLatticeCoord   tLatticeIncrementX;
  TUGLatticeCoord   tVoxelX, tVoxelY, tVoxelZ;            // Voxel key
  TUGLatticeCoord   tVoxelNewX;                           // Voxel key
  TUGLatticeCoord   tBx;                                  // Bounding Advance Point
  TUGLatticeCoord   tBNewx;                               // Bounding Advance Point
  TUGLatticeCoord   tPointAdvanceXx;                      // X Advance Point (TUGLatticeCoord, TScalar, TScalar)
  TVector           tPointIn;
  TVector           tPointOut;
  bool              gX  = false;
  bool              g1b = false;
  
  tRayLocX = rktRAY.location().x();
  tRayLocY = rktRAY.location().y();
  tRayLocZ = rktRAY.location().z();

  if ( ( tRayLocX >= tBoundingBoxPoint1.x() ) && ( tRayLocX <= tBoundingBoxPoint2.x() ) &&
       ( tRayLocY >= tBoundingBoxPoint1.y() ) && ( tRayLocY <= tBoundingBoxPoint2.y() ) &&
       ( tRayLocZ >= tBoundingBoxPoint1.z() ) && ( tRayLocZ <= tBoundingBoxPoint2.z() ) )
  {
    tFirstRayPoint.set (tRayLocX, tRayLocY, tRayLocZ);
  }
  else
  {
    if ( !boundingBoxIntersection (rktRAY, tFirstRayPoint) )
    {
      return false;
    }
    g1b = true;
  }

  tRayDirX = rktRAY.direction().x();

  // Lattice Increments in the three axis
  tLatticeIncrementX = ( tRayDirX > 0 ) ?  1 : -1;
  
  tFirstRayPointLCX = tFirstRayPoint.x() * tInvVoxelSize;
  tFirstRayPointLCY = tFirstRayPoint.y() * tInvVoxelSize;
  tFirstRayPointLCZ = tFirstRayPoint.z() * tInvVoxelSize;

  tVoxelX = (TUGLatticeCoord) floor (tFirstRayPointLCX);
  if ( (tFirstRayPointLCX - (TScalar) tVoxelX) < FX_EPSILON )
  {
    tVoxelNewX = ( tLatticeIncrementX > 0 ) ? tVoxelX : tVoxelX - 1;
    gX         = true;
  }
  else if ( ((TScalar) (tVoxelX + 1) - tFirstRayPointLCX) < FX_EPSILON )
  {
    tVoxelNewX = ( tLatticeIncrementX > 0 ) ? tVoxelX + 1 : tVoxelX;
    gX         = true;
  }
  else
  {
    tVoxelNewX = tVoxelX;
  }

  tVoxelY = (TUGLatticeCoord) floor (tFirstRayPointLCY);
  tVoxelZ = (TUGLatticeCoord) floor (tFirstRayPointLCZ);

  // Calculate New Bounding Point
  tBNewx = ( tLatticeIncrementX > 0 ) ? tVoxelNewX : tVoxelNewX + 1;

  // Calculate tPointAdvanceX, tPointAdvanceY, tPointAdvanceZ
  if ( gX )
  {
    tPointAdvanceXx = tBNewx;
  }
  else
  {
    tPointAdvanceXx = tBNewx + tLatticeIncrementX;
  }
  
  if ( !(gX) )
  {
    tPointIn.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);

    tBx = tBNewx;
    
    tBNewx     += tLatticeIncrementX;
    tVoxelNewX += tLatticeIncrementX;
    tPointOut.set ((TScalar) tPointAdvanceXx, tFirstRayPointLCY, tFirstRayPointLCZ);
    
    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }
  else
  {
    tPointOut.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);
  }

  TUGLatticeCoord   tDestinationBx;
  TUGLatticeCoord   tBLatticeLimitX;
  TVector           tRayDestinationLC;
  
  boundingPointRayDestination6 (rktRAY, tDestinationBx,
                                tLatticeIncrementX,
                                tRayDestinationLC);

  tBLatticeLimitX  = ( tLatticeIncrementX > 0 ) ? tMaxX : tMinX;
  tBLatticeLimitX *= tLatticeIncrementX;

  while ( ( (tBNewx * tLatticeIncrementX) < tBLatticeLimitX ) &&
          ( ( tBNewx != tDestinationBx ) ) )
  {
    tPointIn = tPointOut;
    tVoxelX  = tVoxelNewX;
    tBx      = tBNewx;

    // Calculate tPointAdvanceX, tPointAdvanceY, tPointAdvanceZ
    if ( tBx == tPointAdvanceXx )
    {
      tPointAdvanceXx  = tBx + tLatticeIncrementX;
    }

    tBNewx     += tLatticeIncrementX;
    tVoxelNewX += tLatticeIncrementX;
    tPointOut.set ((TScalar) tPointAdvanceXx, tFirstRayPointLCY, tFirstRayPointLCZ);

    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  if ( ( tBNewx == tDestinationBx ) )
  {
    if ( findIntersectionInsideVoxel (tVoxelNewX, tVoxelY, tVoxelZ, tPointOut, tRayDestinationLC, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  return false;
  
}  /* findFirstIntersection6() */


bool TUniformGrid::findFirstIntersection7 (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TScalar           tRayDirZ;
  TScalar           tRayLocX, tRayLocY, tRayLocZ;
  TVector           tFirstRayPoint;                                            // First ray point on lattice (global coords)
  TScalar           tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ;   // First ray point on lattice (lattice coords)
  TUGLatticeCoord   tLatticeIncrementZ;
  TUGLatticeCoord   tVoxelX, tVoxelY, tVoxelZ;            // Voxel key
  TUGLatticeCoord   tVoxelNewZ;                           // Voxel key
  TUGLatticeCoord   tBz;                                  // Bounding Advance Point
  TUGLatticeCoord   tBNewz;                               // Bounding Advance Point
  TUGLatticeCoord   tPointAdvanceZz;                      // Z Advance Point (TScalar, TScalar, TUGLatticeCoord)
  TVector           tPointIn;
  TVector           tPointOut;
  bool              gZ  = false;
  bool              g1b = false;
  
  tRayLocX = rktRAY.location().x();
  tRayLocY = rktRAY.location().y();
  tRayLocZ = rktRAY.location().z();

  if ( ( tRayLocX >= tBoundingBoxPoint1.x() ) && ( tRayLocX <= tBoundingBoxPoint2.x() ) &&
       ( tRayLocY >= tBoundingBoxPoint1.y() ) && ( tRayLocY <= tBoundingBoxPoint2.y() ) &&
       ( tRayLocZ >= tBoundingBoxPoint1.z() ) && ( tRayLocZ <= tBoundingBoxPoint2.z() ) )
  {
    tFirstRayPoint.set (tRayLocX, tRayLocY, tRayLocZ);
  }
  else
  {
    if ( !boundingBoxIntersection (rktRAY, tFirstRayPoint) )
    {
      return false;
    }
    g1b = true;
  }

  tRayDirZ = rktRAY.direction().z();

  // Lattice Increments in the three axis
  tLatticeIncrementZ = ( tRayDirZ > 0 ) ?  1 : -1;
  
  tFirstRayPointLCX = tFirstRayPoint.x() * tInvVoxelSize;
  tFirstRayPointLCY = tFirstRayPoint.y() * tInvVoxelSize;
  tFirstRayPointLCZ = tFirstRayPoint.z() * tInvVoxelSize;

  tVoxelX = (TUGLatticeCoord) floor (tFirstRayPointLCX);
  tVoxelY = (TUGLatticeCoord) floor (tFirstRayPointLCY);
  tVoxelZ = (TUGLatticeCoord) floor (tFirstRayPointLCZ);
  if ( (tFirstRayPointLCZ - (TScalar) tVoxelZ) < FX_EPSILON )
  {
    tVoxelNewZ = ( tLatticeIncrementZ > 0 ) ? tVoxelZ : tVoxelZ - 1;
    gZ         = true;
  }
  else if ( ((TScalar) (tVoxelZ + 1) - tFirstRayPointLCZ) < FX_EPSILON )
  {
    tVoxelNewZ = ( tLatticeIncrementZ > 0 ) ? tVoxelZ + 1 : tVoxelZ;
    gZ         = true;
  }
  else
  {
    tVoxelNewZ = tVoxelZ;
  }

  // Calculate New Bounding Point
  tBNewz = ( tLatticeIncrementZ > 0 ) ? tVoxelNewZ : tVoxelNewZ + 1;

  // Calculate tPointAdvanceZ
  if ( gZ )
  {
    tPointAdvanceZz = tBNewz;
  }
  else
  {
    tPointAdvanceZz = tBNewz + tLatticeIncrementZ;
  }

  if ( !(gZ) )
  {
    tPointIn.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);

    tBz = tBNewz;
    
    tBNewz     += tLatticeIncrementZ;
    tVoxelNewZ += tLatticeIncrementZ;
    tPointOut.set (tFirstRayPointLCX, tFirstRayPointLCY, (TScalar) tPointAdvanceZz);
    
    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }
  else
  {
    tPointOut.set (tFirstRayPointLCX, tFirstRayPointLCY, tFirstRayPointLCZ);
  }

  TUGLatticeCoord   tDestinationBz;
  TUGLatticeCoord   tBLatticeLimitZ;
  TVector           tRayDestinationLC;
  
  boundingPointRayDestination7 (rktRAY, tDestinationBz,
                                tLatticeIncrementZ,
                                tRayDestinationLC);

  tBLatticeLimitZ  = ( tLatticeIncrementZ > 0 ) ? tMaxZ : tMinZ;
  tBLatticeLimitZ *= tLatticeIncrementZ;

  while ( ( (tBNewz * tLatticeIncrementZ) < tBLatticeLimitZ ) &&
          ( ( tBNewz != tDestinationBz ) ) )
  {
    tPointIn = tPointOut;
    tVoxelZ  = tVoxelNewZ;
    tBz      = tBNewz;

    // Calculate tPointAdvanceZ
    if ( tBz == tPointAdvanceZz )
    {
      tPointAdvanceZz  = tBz + tLatticeIncrementZ;
    }

    tBNewz     += tLatticeIncrementZ;
    tVoxelNewZ += tLatticeIncrementZ;
    tPointOut.set (tFirstRayPointLCX, tFirstRayPointLCY, (TScalar) tPointAdvanceZz);

    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelZ, tPointIn, tPointOut, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  if ( ( tBNewz == tDestinationBz ) )
  {
    if ( findIntersectionInsideVoxel (tVoxelX, tVoxelY, tVoxelNewZ, tPointOut, tRayDestinationLC, rktRAY, rtDATA) )
    {
      return true;
    }
  }

  return false;
  
}  /* findFirstIntersection7() */


void TUniformGrid::add (TUGLatticeCoord tI, TUGLatticeCoord tJ, TUGLatticeCoord tK, magic_pointer<const TObject> pktOBJECT)
{

  list<TUGVoxel>*   ptBucket;
  TUGVoxel          tVoxel;
  TUGBucketType     tIndex;

  tIndex   = hash (tI, tJ, tK);
  ptBucket = aptVoxelHashTable [tIndex];

  if ( ptBucket )
  {
    for (list<TUGVoxel>::iterator tIter = ptBucket->begin(); ( tIter != ptBucket->end() ) ;tIter++)
    {
      if ( ( tIter->i == tI ) && ( tIter->j == tJ ) && ( tIter->k == tK ) )
      {
        tIter->tObjectList.push_back (pktOBJECT);
        return;
      }
    }

    tVoxel.i = tI;
    tVoxel.j = tJ;
    tVoxel.k = tK;
    tVoxel.tObjectList.push_back (pktOBJECT);
    ptBucket->push_back (tVoxel);
    return;
  }
  
  // We must create a new bucket
  tVoxel.i = tI;
  tVoxel.j = tJ;
  tVoxel.k = tK;
  tVoxel.tObjectList.push_back (pktOBJECT);
  ptBucket = new list<TUGVoxel>;
  ptBucket->push_back (tVoxel);
  aptVoxelHashTable [tIndex] = ptBucket;
  
  return;
  
}  /* add() */


bool TUniformGrid::initialize (void)
{
  bool val = true;
  
  list<TUGVoxel>*   ptBucket;

  tMinX = ktLatticeCoordMax;
  tMinY = ktLatticeCoordMax;
  tMinZ = ktLatticeCoordMax;
  tMaxX = ktLatticeCoordMin;
  tMaxY = ktLatticeCoordMin;
  tMaxZ = ktLatticeCoordMin;

  for (size_t m = 0; ( m < ktHashSize ) ;m++)
  {
    ptBucket = aptVoxelHashTable [m];
    if ( ptBucket )
    {
      for (list<TUGVoxel>::iterator tIter = ptBucket->begin(); ( tIter != ptBucket->end() ) ;tIter++)
      {
        tMinX = ( tIter->i < tMinX ) ? tIter->i : tMinX;
        tMinY = ( tIter->j < tMinY ) ? tIter->j : tMinY;
        tMinZ = ( tIter->k < tMinZ ) ? tIter->k : tMinZ;

        tMaxX = ( tIter->i + 1 > tMaxX ) ? tIter->i + 1 : tMaxX;
        tMaxY = ( tIter->j + 1 > tMaxY ) ? tIter->j + 1 : tMaxY;
        tMaxZ = ( tIter->k + 1 > tMaxZ ) ? tIter->k + 1 : tMaxZ;
      }
    }
  }

  tBoundingBoxPoint1.set (((TScalar) tMinX) * tVoxelSize, ((TScalar) tMinY) * tVoxelSize, ((TScalar) tMinZ) * tVoxelSize);
  tBoundingBoxPoint2.set (((TScalar) tMaxX) * tVoxelSize, ((TScalar) tMaxY) * tVoxelSize, ((TScalar) tMaxZ) * tVoxelSize);

  return val;
  
}  /* initialize() */


void TUniformGrid::calculateVoxelSize (const vector<magic_pointer<TObject> >& rktOBJECT_LIST)
{

  TScalar   tTmp;
  TScalar   tVoxelSizeTmp;
  size_t    zObjetListSize = rktOBJECT_LIST.size();

  tVoxelSizeTmp = 0;
  for (vector<magic_pointer<TObject> >::const_iterator tIter = rktOBJECT_LIST.begin(); ( tIter != rktOBJECT_LIST.end() ) ;tIter++)
  {
    // We calculate bounding box side mean value
    tTmp  = 0;
    tTmp  = (*tIter)->boundingBox().xlimits().max() - (*tIter)->boundingBox().xlimits().min();
    tTmp += (*tIter)->boundingBox().ylimits().max() - (*tIter)->boundingBox().ylimits().min();
    tTmp += (*tIter)->boundingBox().zlimits().max() - (*tIter)->boundingBox().zlimits().min();
    tTmp /= 3.0;

    tVoxelSizeTmp += tTmp;
  }

  tVoxelSizeTmp /= (TScalar) zObjetListSize;
  setVoxelSize (tVoxelSizeTmp);
  
}  /* calculateVoxelSize() */


void TUniformGrid::addObject (const magic_pointer<TObject> pktOBJECT)
{
  
  TUGLatticeCoord   I1, J1, K1;
  TUGLatticeCoord   I2, J2, K2;

  // Transformation from global coords to lattice coords
  I1 = (TUGLatticeCoord) floor (((TScalar) pktOBJECT->boundingBox().xlimits().min()) * tInvVoxelSize);
  J1 = (TUGLatticeCoord) floor (((TScalar) pktOBJECT->boundingBox().ylimits().min()) * tInvVoxelSize);
  K1 = (TUGLatticeCoord) floor (((TScalar) pktOBJECT->boundingBox().zlimits().min()) * tInvVoxelSize);

  I2 = (TUGLatticeCoord) floor (((TScalar) pktOBJECT->boundingBox().xlimits().max()) * tInvVoxelSize);
  J2 = (TUGLatticeCoord) floor (((TScalar) pktOBJECT->boundingBox().ylimits().max()) * tInvVoxelSize);
  K2 = (TUGLatticeCoord) floor (((TScalar) pktOBJECT->boundingBox().zlimits().max()) * tInvVoxelSize);

  for (TUGLatticeCoord I = I1; ( I <= I2 ) ;I++)
  {
    for (TUGLatticeCoord J = J1; ( J <= J2 ) ;J++)
    {
      for (TUGLatticeCoord K = K1; ( K <= K2 ) ;K++)
      {
        add (I, J, K, rcp_static_cast<const TObject>(pktOBJECT));
      }
    }
  }
  
}  /* addObject() */


bool TUniformGrid::findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TScalar   tRayDirX;
  TScalar   tRayDirY;
  TScalar   tRayDirZ;
  TScalar   tRayLocX;
  TScalar   tRayLocY;
  TScalar   tRayLocZ;
  TVector   tRayDir = rktRAY.direction();
  TVector   tRayLoc = rktRAY.location();
  
  tRayDirX = tRayDir.x();
  tRayDirY = tRayDir.y();
  tRayDirZ = tRayDir.z();

  tRayLocX = tRayLoc.x();
  tRayLocY = tRayLoc.y();
  tRayLocZ = tRayLoc.z();

  if ( fabs (tRayDirX) > FX_EPSILON )
  {
    if ( fabs (tRayDirY) > FX_EPSILON )
    {
      if ( fabs (tRayDirZ) > FX_EPSILON )
      {
        return findFirstIntersection1 (rktRAY, rtDATA);
      }
      else
      {
        if ( ( tRayLocZ < tBoundingBoxPoint1.z() ) || ( tRayLocZ > tBoundingBoxPoint2.z() ) )
        {
          return false;
        }
        return findFirstIntersection4 (rktRAY, rtDATA);
      }
    }
    else
    {
      if ( ( tRayLocY < tBoundingBoxPoint1.y() ) || ( tRayLocY > tBoundingBoxPoint2.y() ) )
      {
        return false;
      }

      if ( fabs (tRayDirZ) > FX_EPSILON )
      {
        return findFirstIntersection2 (rktRAY, rtDATA);
      }
      else
      {
        if ( ( tRayLocZ < tBoundingBoxPoint1.z() ) || ( tRayLocZ > tBoundingBoxPoint2.z() ) )
        {
          return false;
        }
        return findFirstIntersection6 (rktRAY, rtDATA);
      }
    }
  }
  else
  {
    if ( ( tRayLocX < tBoundingBoxPoint1.x() ) || ( tRayLocX > tBoundingBoxPoint2.x() ) )
    {
      return false;
    }
    
    if ( fabs (tRayDirY) > FX_EPSILON )
    {
      if ( fabs (tRayDirZ) > FX_EPSILON )
      {
        return findFirstIntersection3 (rktRAY, rtDATA);
      }
      else
      {
        if ( ( tRayLocZ < tBoundingBoxPoint1.z() ) || ( tRayLocZ > tBoundingBoxPoint2.z() ) )
        {
          return false;
        }
        return findFirstIntersection5 (rktRAY, rtDATA);
      }
    }
    else
    {
      if ( ( tRayLocY < tBoundingBoxPoint1.y() ) || ( tRayLocY > tBoundingBoxPoint2.y() ) )
      {
        return false;
      }
      
      if ( fabs (tRayDirZ) > FX_EPSILON )
      {
        return findFirstIntersection7 (rktRAY, rtDATA);
      }
      else
      {
        // rktRAY.direction() can not be == TVector (0, 0, 0)
        assert ( false );
        return false;
      }
    }
  }

  assert ( false );
  return false;

}  /* findFirstIntersection() */


void TUniformGrid::printGrid (void) const
{

  size_t   zCont0          = 0;
  size_t   zCont1          = 0;
  size_t   zCont2          = 0;
  size_t   zCont3          = 0;
  size_t   zCont4          = 0;
  size_t   zCont5          = 0;
  size_t   zContDefault    = 0;
  size_t   zElements       = 0;
  size_t   zVoxelsNonEmpty = 0;
  
  GOM.debug() << "TUniformGrid::printGrid tVoxelSize " << tVoxelSize << endl;
  
  for (size_t m = 0; ( m < ktHashSize ) ;m++)
  {
    if ( aptVoxelHashTable [m] )
    {
      switch ( (aptVoxelHashTable [m])->size() )
      {
        case 1:
        {
          zCont1++;
        }
        break;

        case 2:
        {
          zCont2++;
        }
        break;

        case 3:
        {
          zCont3++;
        }
        break;

        case 4:
        {
          zCont4++;
        }
        break;

        case 5:
        {
          zCont5++;
        }
        break;

        default:
        {
          zContDefault++;
        }
        break;
      }
      for (list<TUGVoxel>::const_iterator tIter = (aptVoxelHashTable [m])->begin(); ( tIter != (aptVoxelHashTable [m])->end() ) ;tIter++)
      {
        if ( tIter->tObjectList.size() > 0 )
        {
          zVoxelsNonEmpty   += 1;
          zElements         += tIter->tObjectList.size();
        }
      }
    }
    else
    {
      zCont0++;
    }
  }

  GOM.debug() << "TUniformGrid::printGrid empty buckets = " << zCont0 << endl;
  GOM.debug() << "TUniformGrid::printGrid buckets with 1 element    = " << zCont1 << endl;
  GOM.debug() << "TUniformGrid::printGrid buckets with 2 elements   = " << zCont2 << endl;
  GOM.debug() << "TUniformGrid::printGrid buckets with 3 elements   = " << zCont3 << endl;
  GOM.debug() << "TUniformGrid::printGrid buckets with 4 elements   = " << zCont4 << endl;
  GOM.debug() << "TUniformGrid::printGrid buckets with 5 elements   = " << zCont5 << endl;
  GOM.debug() << "TUniformGrid::printGrid buckets with more elements = " << zContDefault << endl;
  GOM.debug() << "TUniformGrid::printGrid non empty voxels = " << zVoxelsNonEmpty << endl;

}  /* printGrid() */

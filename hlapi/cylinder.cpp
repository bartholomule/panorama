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

#include "hlapi/cylinder.h"

TVector TCylinder::localNormal (const TVector& rktPOINT) const
{

  if ( fabs (rktPOINT.y() - 1) < FX_EPSILON )
  {
    return TVector (0, 1, 0);
  }
  else if ( fabs (rktPOINT.y()) < FX_EPSILON )
  {
    return TVector (0, -1, 0);
  }

  return TVector (rktPOINT.x(), 0, rktPOINT.z());

}  /* localNormal() */


void TCylinder::initialize (void)
{

  tBoundingBox.set (TVector (-1, 0, -1), TVector (1, 1, 1));
  tBoundingBox.applyTransform (*ptMatrix);

}  /* initialize() */


bool TCylinder::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
{

  TSurfaceData   tSurfaceData;
  TScalar        a, b, c, d;
  TScalar        s1, s2;
  TVector        tPoint;
  TScalar        tFactor;
  TRay           tRayIT            = rktRAY;
  bool           gIntersection     = false;
  Byte           bCapIntersections = 0;

  if ( !tBoundingBox.intersects (rktRAY) )
  {
    return false;
  }

  tFactor = tRayIT.applyTransform (ptInverseMatrix);

  if ( rktRAY.limit() < SCALAR_MAX )
  {
    tRayIT.setLimit (rktRAY.limit() / tFactor);
  }

  tSurfaceData.setup (this, rktRAY);
  
  if ( !( fabs (tRayIT.direction().y()) < FX_EPSILON ) )
  {
    //
    // Intersection with bottom circle
    //
    s1     = -tRayIT.location().y() / tRayIT.direction().y();
    tPoint = tRayIT.location() + (tRayIT.direction() * s1);
    if ( ( (tPoint.x() * tPoint.x() + tPoint.z() * tPoint.z()) <= 1 ) &&
         ( s1 >= FX_EPSILON )                                         &&
         ( s1 <= tRayIT.limit() )                                      )
    {
      if ( tSurfaceData.setPoint (tFactor * s1) )
      {
        rtLIST.add (tSurfaceData);
        bCapIntersections++;
        gIntersection = true;
      }
    }

    //
    // Intersection with top circle
    //
    s1     = (1 - tRayIT.location().y()) / tRayIT.direction().y();
    tPoint = tRayIT.location() + (tRayIT.direction() * s1);
    if ( ( (tPoint.x() * tPoint.x() + tPoint.z() * tPoint.z()) <= 1 ) &&
         ( s1 >= FX_EPSILON )                                         &&
         ( s1 <= tRayIT.limit() )                                      )
    {
      if ( tSurfaceData.setPoint (tFactor * s1) )
      {
        rtLIST.add (tSurfaceData);
        bCapIntersections++;
        gIntersection = true;
      }
    }
  }

  if ( bCapIntersections == 2 )
  {
    //
    // Ray intersects both caps, so there are no more intersections
    //
    return gIntersection;
  }

  a = tRayIT.direction().x() * tRayIT.direction().x() + tRayIT.direction().z() * tRayIT.direction().z();
  b = (tRayIT.location().x() * tRayIT.direction().x() + tRayIT.location().z() * tRayIT.direction().z()) * 2.0;
  c = tRayIT.location().x() * tRayIT.location().x() + tRayIT.location().z() * tRayIT.location().z() - 1;
  d = (b * b) - (4 * a * c);

  if ( d <= FX_EPSILON )
  {
    //
    // If there is no intersection or the intersection is in a single point.
    //
    return gIntersection;
  }
  else
  {
    d  = sqrt (d);
    s1 = (-b + d) / (2.0 * a);
    s2 = (-b - d) / (2.0 * a);

    if ( ( s1 >= FX_EPSILON ) && ( s1 <= tRayIT.limit() ) )
    {
      tPoint = tRayIT.location() + (tRayIT.direction() * s1);
      if ( ( tPoint.y() > 0 ) && ( tPoint.y() < 1 ) )
      {
        if ( tSurfaceData.setPoint (tFactor * s1) )
        {
          rtLIST.add (tSurfaceData);
          gIntersection = true;
        }
      }
    }

    if ( ( s2 >= FX_EPSILON ) && ( s2 <= tRayIT.limit() ) )
    {
      tPoint = tRayIT.location() + (tRayIT.direction() * s2);
      if ( ( tPoint.y() > 0 ) && ( tPoint.y() < 1 ) )
      {
        if ( tSurfaceData.setPoint (tFactor * s2) )
        {
          rtLIST.add (tSurfaceData);
          gIntersection = true;
        }
      }
    }
  }

  return gIntersection;

}  /* findAllIntersections() */

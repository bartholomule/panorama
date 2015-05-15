/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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
#include "hlapi/cylinder.h"

TVector TCylinder::localNormal (const TVector& rktPOINT) const
{

  if ( fabs (rktPOINT.y() - 1) < FX_EPSILON )
  {
    return TVector (0, 1, 0);
  }
  else if ( fabs (rktPOINT.y() + 1) < FX_EPSILON )
  {
    return TVector (0, -1, 0);
  }

  return TVector (rktPOINT.x(), 0, rktPOINT.z());

}  /* localNormal() */


bool TCylinder::initialize (void)
{
  bool val = true;
  TVector tAxis;
  TVector tCentre;

  tCentre      = (tTopPoint + tBottomPoint) / 2.0;
  
  tAxis     = tCentre - tTopPoint;
  tHeight   = tAxis.norm();
  
  // Canonical cylinder has endpoints at < 0, 1, 0 > and < 0,-1, 0 >   
  // First, scale the canonical cylinder to the correct dimensions
  
  scale (TVector (tRadius, tHeight, tRadius), TVector (0, 0, 0) );
  
  // Secondly, we translate the cylinder so that the base is the
  // correct distance from the origin.    
  // Finally, we rotate the cylinder to the correct coordinates
    
  if ( ( fabs (tAxis.x()) < FX_EPSILON ) && ( fabs (tAxis.z()) < FX_EPSILON ) )
  {
    // cylinder is on the y-axis.
    if ( dotProduct (tAxis, TVector (0, 1, 0)) < 0 )
    {
      // cylinder is on the -ve y-axis, and needs to be rotated
      rotate (TVector (180, 0, 0));
    }
  }
  else
  {
    TVector   tTmpX;
    TVector   tTmpZ;
    TScalar   tAxisYProyection;
    TScalar   tAxistTmpZProyection;
      
    tTmpX = crossProduct (TVector (0, 1, 0), tAxis);
    tTmpX.normalize();
    tTmpZ = crossProduct (tTmpX, TVector (0, 1, 0));
    tTmpZ.normalize();
    tAxisYProyection     = dotProduct (tAxis, TVector (0, 1, 0));
    tAxistTmpZProyection = dotProduct (tAxis, tTmpZ);

    rotate (tTmpX * 1.0, tTmpX * 2.0, atan2 (tAxistTmpZProyection, tAxisYProyection) * 180 / PI);
  }

  translate (tCentre); 

  tBoundingBox.set (TVector (-1, -1, -1), TVector (1, 1, 1));
  tBoundingBox.applyTransform (*ptMatrix);

  return val && TObject::initialize();
  
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
    //return false;
  }

  tFactor = tRayIT.applyTransform (ptInverseMatrix);

  if ( rktRAY.limit() < SCALAR_MAX )
  {
    tRayIT.setLimit (rktRAY.limit() / tFactor);
  }

  tSurfaceData.setup (this, rktRAY);
  
  if ( !( fabs (tRayIT.direction().y()) < FX_EPSILON ) && !gOpen )
  {
    //
    // Intersection with bottom circle
    //
    s1     = -(1 + tRayIT.location().y()) / tRayIT.direction().y();
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
      if ( ( tPoint.y() > -1 ) && ( tPoint.y() < 1 ) )
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
      if ( ( tPoint.y() > -1 ) && ( tPoint.y() < 1 ) )
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


int TCylinder::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  if ( rktNAME == "point1" )
  {
    if ( eTYPE == FX_VECTOR )
    {
     tTopPoint = *((TVector*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "point2" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      tBottomPoint = *((TVector*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "open" )
  {
    if ( eTYPE == FX_BOOL )
    {
      gOpen = nVALUE.gValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "radius" )
  {
    if ( eTYPE == FX_REAL )
    {
      tRadius  = nVALUE.dValue;
      tRadius2 = tRadius * tRadius;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TObject::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TCylinder::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "point1" )
  {
    rnVALUE.pvValue = &tTopPoint;
  }
  else if ( rktNAME == "point2" )
  {
    rnVALUE.pvValue = &tBottomPoint;
  }
  else if ( rktNAME == "open" )
  {
    rnVALUE.gValue = gOpen;
  }
  else if ( rktNAME == "radius" )
  {
    rnVALUE.dValue = tRadius;
  }
  else
  {
    return TObject::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TCylinder::getAttributeList (TAttributeList& rtLIST) const
{

  TObject::getAttributeList (rtLIST);

  rtLIST ["point1"] = FX_VECTOR;
  rtLIST ["point2"] = FX_VECTOR;
  rtLIST ["open"]   = FX_BOOL;
  rtLIST ["radius"] = FX_REAL;

}  /* getAttributeList() */

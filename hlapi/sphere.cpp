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

#include <cmath>
#include "llapi/math_tools.h"
#include "hlapi/sphere.h"

void TSphere::initialize (void)
{

  tBoundingBox.set (TVector (tLocation.x() - tRadius, tLocation.y() - tRadius, tLocation.z() - tRadius),
                    TVector (tLocation.x() + tRadius, tLocation.y() + tRadius, tLocation.z() + tRadius));

}  /* initialize() */


int TSphere::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "radius" )
  {
    if ( eTYPE == FX_REAL )
    {
      setRadius (nVALUE.dValue);
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


int TSphere::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "radius" )
  {
    rnVALUE.dValue = tRadius;
  }
  else
  {
    return TObject::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TSphere::getAttributeList (TAttributeList& rtLIST) const
{

  TObject::getAttributeList (rtLIST);

  rtLIST ["radius"] = FX_REAL;

}  /* getAttributeList() */


void TSphere::setRadius (TScalar tRADIUS)
{

  tRadius  = tRADIUS;
  tRadius2 = (tRadius * tRadius);

}  /* setRadius() */


bool TSphere::findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TScalar   tClosestApp2;
  TScalar   tIntersection2;
  TScalar   s1;
  TScalar   s2;
  TVector   tCenter       = (tLocation - rktRAY.location());
  TScalar   tDistance2    = dotProduct (tCenter, tCenter);
  TScalar   tProjection   = dotProduct (tCenter, rktRAY.direction());

  if ( tDistance2 < tRadius2 )
  {
    // Ray origin is inside the sphere
    tClosestApp2   = tDistance2 - (tProjection * tProjection);
    tIntersection2 = tRadius2 - tClosestApp2;

    s1 = tProjection + sqrt (tIntersection2);

    if ( ( s1 >= FX_EPSILON ) && ( s1 <= rktRAY.limit() ) )
    {
      rtDATA.setup (this, rktRAY);
      rtDATA.setPoint (s1);

      return true;
    }
  }
  else
  {
    // Ray origin is outside the sphere

    // Ray pointing outwards?
    if ( tProjection < 0 )
    {
      return false;
    }

    tClosestApp2   = tDistance2 - (tProjection * tProjection);
    tIntersection2 = tRadius2 - tClosestApp2;

    // Ray does not intersect sphere?
    if ( tIntersection2 < 0 )
    {
      return false;
    }

    s1 = tProjection - sqrt (tIntersection2);
    s2 = tProjection + sqrt (tIntersection2);

    if ( ( s1 >= FX_EPSILON ) && ( s1 <= rktRAY.limit() ) )
    {
      rtDATA.setup (this, rktRAY);
      rtDATA.setPoint (s1);

      return true;
    }

    if ( ( s2 >= FX_EPSILON ) && ( s2 <= rktRAY.limit() ) )
    {
      rtDATA.setup (this, rktRAY);
      rtDATA.setPoint (s2);

      return true;
    }
  }
  
  return false;

}  /* findFirstIntersection() */


bool TSphere::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
{

  TSurfaceData   tSurfaceData;
  TScalar        tClosestApp2;
  TScalar        tIntersection2;
  TScalar        s1            = 0;
  TScalar        s2            = 0;
  bool           gIntersection = false;
  TVector        tCenter       = (tLocation - rktRAY.location());
  TScalar        tDistance2    = dotProduct (tCenter, tCenter);
  TScalar        tProjection   = dotProduct (tCenter, rktRAY.direction());

  if ( tDistance2 < tRadius2 )
  {
    // Ray origin is inside the sphere
    tClosestApp2   = tDistance2 - (tProjection * tProjection);
    tIntersection2 = tRadius2 - tClosestApp2;

    s1 = tProjection + sqrt (tIntersection2);
  }
  else
  {
    // Ray origin is outside the sphere

    // Ray pointing outwards?
    if ( tProjection < 0 )
    {
      return false;
    }

    tClosestApp2   = tDistance2 - (tProjection * tProjection);
    tIntersection2 = tRadius2 - tClosestApp2;

    // Ray does not intersect sphere?
    if ( tIntersection2 < 0 )
    {
      return false;
    }

    s1 = tProjection - sqrt (tIntersection2);
    s2 = tProjection + sqrt (tIntersection2);
  }

  tSurfaceData.setup (this, rktRAY);

  if ( ( s1 >= FX_EPSILON ) && ( s1 <= rktRAY.limit() ) )
  {
    if ( tSurfaceData.setPoint (s1) )
    {
      rtLIST.add (tSurfaceData);
      gIntersection = true;
    }
  }

  if ( ( s2 >= FX_EPSILON ) && ( s2 <= rktRAY.limit() ) )
  {
    if ( tSurfaceData.setPoint (s2) )
    {
      rtLIST.add (tSurfaceData);
      gIntersection = true;
    }
  }

  return gIntersection;

}  /* findAllIntersections() */


void TSphere::printDebug (void) const
{

  TObject::printDebug();

  TDebug::_push();
  
  cerr << TDebug::_indent() << "Radius : " << tRadius << endl;

  TDebug::_pop();

}  /* printDebug() */

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
#include "hlapi/plane.h"

void TPlane::update (void)
{

  tNormal.normalize();

  D = -dotProduct (tNormal, tLocation);

}  /* update() */


bool TPlane::findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TScalar   tSol;
  TVector   tPoint;
  TScalar   tDen = dotProduct (tNormal, rktRAY.direction());

  //
  // Return false if ray and plane are parallels.
  //
  if ( fabs (tDen) < FX_EPSILON )
  {
    return false;
  }

  if ( gOneSided && ( tDen > 0 ) )
  {
    return false;
  }
  
  tSol = -(dotProduct (tNormal, rktRAY.location()) + D) / tDen;

  if ( ( tSol >= FX_EPSILON ) && ( tSol <= rktRAY.limit() ) )
  {
    tPoint = rktRAY.location() + (rktRAY.direction() * tSol);

    //
    // This test is for descendants. It has no sense in this class (returns always true).
    //
    if ( !inside (tPoint) )
    {
      return false;
    }

    rtDATA.setup (this, rktRAY);
    rtDATA.setPoint (tSol);

    return true;
  }

  return false;

}  /* findFirstIntersection() */


bool TPlane::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
{

  TSurfaceData   tSurfaceData;
  TScalar        tSol;
  TVector        tPoint;
  TScalar        tDen = dotProduct (tNormal, rktRAY.direction());

  //
  // Return false if ray and plane are parallels.
  //
  if ( fabs (tDen) < FX_EPSILON )
  {
    return false;
  }

  if ( gOneSided && ( tDen > 0 ) )
  {
    return false;
  }
  
  tSol = -(dotProduct (tNormal, rktRAY.location()) + D) / tDen;

  if ( ( tSol >= FX_EPSILON ) && ( tSol <= rktRAY.limit() ) )
  {
    tPoint = rktRAY.location() + (rktRAY.direction() * tSol);

    //
    // This test is for descendants. It has no sense in this class (returns always true).
    //
    if ( !inside (tPoint) )
    {
      return false;
    }

    tSurfaceData.setup (this, rktRAY);
    tSurfaceData.setPoint (tSol);

    if ( gOneSided )
    {
      tSurfaceData.setNormal (tNormal);
    }
    else
    {
      tSurfaceData.setNormal (( tDen < 0 ) ? tNormal : -tNormal);
    }

    rtLIST.add (tSurfaceData);

    return true;
  }

  return false;

}  /* findAllIntersections() */


int TPlane::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "normal" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      setNormal (*((TVector*) nVALUE.pvValue));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "one_sided" )
  {
    if ( eTYPE == FX_BOOL )
    {
      setOneSided (nVALUE.gValue);
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


int TPlane::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "normal" )
  {
    rnVALUE.pvValue = &tNormal;
  }
  else if ( rktNAME == "one_sided" )
  {
    rnVALUE.gValue = gOneSided;
  }
  else
  {
    return TObject::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPlane::getAttributeList (TAttributeList& rtLIST) const
{

  TObject::getAttributeList (rtLIST);

  rtLIST ["normal"]    = FX_VECTOR;
  rtLIST ["one_sided"] = FX_BOOL;

}  /* getAttributeList() */


void TPlane::printDebug (void) const
{

  TObject::printDebug();

  TDebug::_push();

  cerr << TDebug::_indent() << "Normal   : "; tNormal.printDebug(); cerr << endl;
  cerr << TDebug::_indent() << "OneSided : " << gOneSided << endl;

  TDebug::_pop();
  
}  /* printDebug() */

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

#include <iostream>
#include "llapi/surface_data.h"
#include "llapi/object.h"
#include "llapi/material.h"

void TSurfaceData::setup (const TObject* pktOBJ, const TRay& rktRAY)
{

  pktObject = pktOBJ;
  tRay      = rktRAY;

  zObjectCode = ( pktOBJ ) ? pktOBJ->objectCode() : 0;

}  /* setup() */


bool TSurfaceData::setPoint (TScalar tDISTANCE, const TVector& rktNORMAL)
{

  tDistance = tDISTANCE;
  if ( pktObject )
  {
    gNormalAssigned = true;
    tPoint          = tRay.location() + (tRay.direction() * tDISTANCE);
    tNormal         = rktNORMAL;
    tNormal         = pktObject->material()->perturbNormal (*this);
    
    return true;
  }

  return false;

}  /* setPoint() */


TVector TSurfaceData::localPoint (void) const
{
  
  TMatrix*   ptMatrix = pktObject->inverseTransformMatrix();

  if ( ptMatrix )
  {
    return (*ptMatrix * tPoint);
  }

  return tPoint;
  
}  /* localPoint() */


TVector TSurfaceData::normal(void) const
{

  if ( !gNormalAssigned )
  {
    gNormalAssigned = true;
    tNormal         = pktObject->normal (*this);
    tNormal         = pktObject->material()->perturbNormal (*this);
  }

  return tNormal;

}  /* normal() */


void TSurfaceData::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_IntData_]" << endl;

  TDebug::_push();
  
  if ( !pktObject )
  {
    cerr << TDebug::_indent() << "NULL" << endl;
  }
  else
  {
    cerr << TDebug::_indent() << "tRay.location         : "; tRay.location().printDebug(); cerr << endl;
    cerr << TDebug::_indent() << "tRay.direction        : "; tRay.direction().printDebug(); cerr << endl;
    cerr << TDebug::_indent() << "Distance              : " << tDistance << endl;
    cerr << TDebug::_indent() << "Point                 : "; tPoint.printDebug(); cerr << endl;
    if ( gNormalAssigned )
    {
      cerr << TDebug::_indent() << "tNormal               : "; tNormal.printDebug(); cerr << endl;
    }
  }

  TDebug::_pop();
  
}  /* printDebug() */

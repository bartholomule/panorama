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
    gNormalAssigned    = true;
    tPoint             = tRay.location() + (tRay.direction() * tDISTANCE);
    tUnperturbedNormal = rktNORMAL;
    tNormal            = tUnperturbedNormal;
    tNormal            = pktObject->material()->perturbNormal (*this);
    
    return true;
  }

  return false;

}  /* setPoint() */


TVector TSurfaceData::localPoint (void) const
{
  
  if ( pktObject )
  {
    TMatrix*   ptMatrix = pktObject->inverseTransformMatrix();

    if ( ptMatrix )
    {
      return (*ptMatrix * tPoint);
    }
  }

  return tPoint;

}  /* localPoint() */


TVector TSurfaceData::unperturbedNormal (void) const
{

  return tUnperturbedNormal;

}  /* unperturbedNormal() */


void TSurfaceData::setUnperturbedNormal (const TVector& rktNORMAL)
{

  tUnperturbedNormal = rktNORMAL;
  tNormal            = tUnperturbedNormal;

  gNormalAssigned = true;

}  /* setUnperturbedNormal() */


void TSurfaceData::setNormal (const TVector& rktNORMAL)
{

  tUnperturbedNormal = rktNORMAL;
  tNormal            = tUnperturbedNormal;

  if ( pktObject )
  {
    tNormal = pktObject->material()->perturbNormal (*this);
  }

  gNormalAssigned = true;

}  /* setNormal() */


TVector TSurfaceData::normal (void) const
{

  if ( !gNormalAssigned )
  {
    gNormalAssigned = true;
    if ( !pktObject )
    {
      tNormal.set (0, 0, 0);
      tUnperturbedNormal = tNormal;
    }
    else
    {
      tUnperturbedNormal = pktObject->normal (*this);

      tNormal = tUnperturbedNormal;
      tNormal = pktObject->material()->perturbNormal (*this);

      if ( gFlipNormal )
      {
        tUnperturbedNormal = -tUnperturbedNormal;
        tNormal            = -tNormal;
        gFlipNormal = false;
      }
    }
  }

  return tNormal;

}  /* normal() */


void TSurfaceData::printDebug (const string& indent) const
{

  cerr << indent << "[_IntData_]" << endl;

  string new_indent = TDebug::Indent(indent);
  
  if ( !pktObject )
  {
    cerr << new_indent << "NULL" << endl;
  }
  else
  {
    cerr << new_indent << "tRay.location         : "; tRay.location().printDebug(new_indent); cerr << endl;
    cerr << new_indent << "tRay.direction        : "; tRay.direction().printDebug(new_indent); cerr << endl;
    cerr << new_indent << "Distance              : " << tDistance << endl;
    cerr << new_indent << "Point                 : "; tPoint.printDebug(new_indent); cerr << endl;
    if ( gNormalAssigned )
    {
      cerr << new_indent << "tUnperturbedNormal    : "; tUnperturbedNormal.printDebug(new_indent); cerr << endl;
      cerr << new_indent << "tNormal               : "; tNormal.printDebug(new_indent); cerr << endl;
    }
  }
  
}  /* printDebug() */

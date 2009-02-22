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

namespace panorama
{

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
      magic_pointer<TMatrix> ptMatrix = pktObject->inverseTransformMatrix();

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

  std::string TSurfaceData::internalMembers(const Indentation& indent, PrefixType prefix ) const
  {
    std::string tag = indent.level();
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag = indent.level() + TSurfaceData::name() + "::";
    }

    Indentation nextIndent = indent.nextLevel();

    std::string retval;

    retval += indent + "ray=" + tRay.toString(nextIndent, prefix) + "\n";
    if( pktObject )
    {
      retval += indent + "object=" + pktObject->toString(nextIndent) + "\n";

      retval += indent + "hit point=" + tPoint.toString(nextIndent, prefix) + "\n";
      if( gNormalAssigned )
      {
        retval += indent + "normal=" + tNormal.toString(nextIndent, prefix) + "\n";
        retval += indent + "normal (unperturbed)=" + tUnpertorbedNormal.toString(nextIndent, prefix) + "\n";
      }
      retval += indent + string_format("reflection=%1\n", zReflection);
      retval += indent + string_format("transmission=%1\n", zTransmission);
      retval += indent + "lightRadiance=" + tLightRadiance.toString(nextIndent, prefix);
    }
    else
    {
      retval += indent + "object=NULL\n";
    }
    return retval;
  }

  std::string TSurfaceData::name() const
  {
    return "SurfaceData";
  }

} // end namespace panorama

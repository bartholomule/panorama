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

#include "llapi/warning_eliminator.h"
#include "llapi/math_tools.h"
#include "llapi/light.h"

int TLight::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "color" )
  {
    if ( eTYPE == FX_COLOR )
    {
      setColor (*((TColor*) nVALUE.pvValue));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "intensity" )
  {
    if ( eTYPE == FX_REAL )
    {
      setIntensity (nVALUE.dValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "shadow" )
  {
    if ( eTYPE == FX_BOOL )
    {
      tProperties.gShadow = nVALUE.gValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "volumetric" )
  {
    if ( eTYPE == FX_BOOL )
    {
      tProperties.gVolumetric = nVALUE.gValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "raytraced" )
  {
    if ( eTYPE == FX_BOOL )
    {
      tProperties.gRaytraced = nVALUE.gValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "lightonly" )
  {
    // This can not be modified by a user.  It is a property inherent in lights.
    return FX_ATTRIB_USER_ERROR;
  }
  else
  {
    return TEntity::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TLight::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "color" )
  {
    rnVALUE.pvValue = &tColor;
  }
  else if ( rktNAME == "intensity" )
  {
    rnVALUE.dValue = tIntensity;
  }
  else if ( rktNAME == "shadow" )
  {
    rnVALUE.gValue = tProperties.gShadow;
  }
  else if ( rktNAME == "volumetric" )
  {
    rnVALUE.gValue = tProperties.gVolumetric;
  }
  else if ( rktNAME == "raytraced" )
  {
    rnVALUE.gValue = tProperties.gRaytraced;
  }
  else if ( rktNAME == "lightonly" )
  {
    rnVALUE.gValue = true;
  }  
  else
  {
    return TEntity::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TLight::getAttributeList (TAttributeList& rtLIST) const
{

  TEntity::getAttributeList (rtLIST);

  rtLIST ["color"]      = FX_COLOR;
  rtLIST ["intensity"]  = FX_REAL;
  rtLIST ["shadow"]     = FX_BOOL;
  rtLIST ["volumetric"] = FX_BOOL;
  rtLIST ["raytraced"]  = FX_BOOL;
  rtLIST ["lightonly"]  = FX_BOOL;
}  /* getAttributeList() */



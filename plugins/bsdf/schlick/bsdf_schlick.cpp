/*
*  Copyright (C) 1999 Jon Frydensbjerg
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
#include "llapi/object.h"
#include "llapi/material.h"
#include "bsdf_schlick.h"

DEFINE_PLUGIN ("BsdfSchlick", FX_BSDF_CLASS, TBsdfSchlick);

TBsdfSchlick::TBsdfSchlick (void) :
  tRoughness (0.3f),
  tIsotropy (1.0f),
  tReflectance (TColor::_white())  
{

  setupBsdf();

}  /* TBsdfSchlick() */


int TBsdfSchlick::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "roughness" )
  {
    if ( eTYPE == FX_REAL )
    {
      tRoughness = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "reflection_color" )
  {
    if ( eTYPE == FX_COLOR )
    {
      tReflectance = *((TColor *) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "isotropy" )
  {
    if ( eTYPE == FX_REAL )
    {
      tIsotropy = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TBsdf::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  setupBsdf();

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TBsdfSchlick::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "roughness" )
  {
    rnVALUE.dValue = tRoughness;
  }
  else if ( rktNAME == "reflection_color" )
  {
    rnVALUE.pvValue = &tReflectance;
  }
  else if ( rktNAME == "isotropy" )
  {
    rnVALUE.dValue = tIsotropy;
  }
  else
  {
    return TBsdf::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TBsdfSchlick::getAttributeList (TAttributeList& rtLIST) const
{

  TBsdf::getAttributeList (rtLIST);

  rtLIST ["roughness"]        = FX_REAL;
  rtLIST ["reflection_color"] = FX_COLOR;
  rtLIST ["isotropy"]         = FX_REAL;

}  /* getAttributeList() */





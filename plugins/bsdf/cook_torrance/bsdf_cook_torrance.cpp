/*
*  Copyright (C) 1999-2000 Jon Frydensbjerg
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
#include <iostream>
#include "llapi/object.h"
#include "llapi/material.h"
#include "bsdf_cook_torrance.h"

DEFINE_PLUGIN ("BsdfCookTorrance", FX_BSDF_CLASS, TBsdfCookTorrance);


TBsdfCookTorrance::TBsdfCookTorrance (void)
{

  setSpecularReflectionCoefficients (new TPattern (TColor::_white()));
  setStandardDeviation (new TPattern (1.0));

}  /* TBsdfCookTorrance() */


int TBsdfCookTorrance::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "roughness" )
  {
    if ( eTYPE == FX_PATTERN )
    {
      setStandardDeviation ((TPattern*) nVALUE.pvValue);
    }
    else if ( eTYPE == FX_REAL )
    {
      setStandardDeviation (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setStandardDeviation (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "reflection_color" )
  {
    if ( eTYPE == FX_PATTERN )
    {
      setSpecularReflectionCoefficients ((TPattern*) nVALUE.pvValue);
    }
    else if ( eTYPE == FX_REAL )
    {
      setSpecularReflectionCoefficients (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setSpecularReflectionCoefficients (new TPattern (*((TColor*) nVALUE.pvValue)));
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

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TBsdfCookTorrance::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "roughness" )
  {
    rnVALUE.pvValue = ptStandardDeviation;
  }
  else if ( rktNAME == "reflection_color" )
  {
    rnVALUE.pvValue = ptSpecularReflectionCoefficients;
  }
  else
  {
    return TBsdf::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TBsdfCookTorrance::getAttributeList (TAttributeList& rtLIST) const
{

  TBsdf::getAttributeList (rtLIST);

  rtLIST ["reflection_color"] = FX_PATTERN;
  rtLIST ["roughness"]        = FX_PATTERN;

}  /* getAttributeList() */





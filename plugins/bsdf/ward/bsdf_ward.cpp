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
#include "bsdf_ward.h"

DEFINE_PLUGIN ("BsdfWard", FX_BSDF_CLASS, TBsdfWard);

TBsdfWard::TBsdfWard (void) :
  tStandardDeviation_x (0.3f),
  tStandardDeviation_y (0.3f) 
{

}  /* TBsdfWard() */


int TBsdfWard::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "roughness_x" )
  {
    if ( eTYPE == FX_REAL )
    {
      tStandardDeviation_x = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "roughness_y" )
  {
    if ( eTYPE == FX_REAL )
    {
      tStandardDeviation_y = nVALUE.dValue;
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


int TBsdfWard::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "roughness_x" )
  {
    rnVALUE.dValue = tStandardDeviation_x;
  }
  else if ( rktNAME == "roughness_y" )
  {
    rnVALUE.dValue = tStandardDeviation_y;
  }
  else
  {
    return TBsdf::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TBsdfWard::getAttributeList (TAttributeList& rtLIST) const
{

  TBsdf::getAttributeList (rtLIST);

  rtLIST ["roughness_x"] = FX_REAL;
  rtLIST ["roughness_y"] = FX_REAL;

}  /* getAttributeList() */





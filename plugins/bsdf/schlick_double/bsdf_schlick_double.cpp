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

#include <iostream>
#include "llapi/object.h"
#include "llapi/material.h"
#include "bsdf_schlick_double.h"

DEFINE_PLUGIN ("BsdfSchlickDouble", FX_BSDF_CLASS, TBsdfSchlickDouble);

TBsdfSchlickDouble::TBsdfSchlickDouble (void)
{

  ptLayerOne = new TBsdfSchlick();
  ptLayerTwo = new TBsdfSchlick();

}  /* TBsdfSchlickDouble() */


TBsdfSchlickDouble::~TBsdfSchlickDouble (void)
{

  delete ptLayerOne;
  delete ptLayerTwo;

}  /* ~TBsdfSchlickDouble() */


int TBsdfSchlickDouble::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "l2_roughness" )
  {
    ptLayerTwo->setAttribute ("roughness", nVALUE, eTYPE);
  }
  else if ( rktNAME == "l2_reflection_color" )
  {
    ptLayerTwo->setAttribute ("reflection_color", nVALUE, eTYPE);
  }
  else if ( rktNAME == "l2_isotropy" )
  {
    ptLayerTwo->setAttribute ("isotropy", nVALUE, eTYPE);
  }
  else
  {
    return ptLayerOne->setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TBsdfSchlickDouble::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "l2_roughness" )
  {
    ptLayerTwo->getAttribute ("roughness", rnVALUE);
  }
  else if ( rktNAME == "l2_reflection_color" )
  {
    ptLayerTwo->getAttribute ("reflection_color", rnVALUE);
  }
  else if ( rktNAME == "l2_isotropy" )
  {
    ptLayerTwo->getAttribute ("isotropy", rnVALUE);
  }
  else
  {    
    return ptLayerOne->getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TBsdfSchlickDouble::getAttributeList (TAttributeList& rtLIST) const
{

  TBsdf::getAttributeList (rtLIST);
  ptLayerOne->getAttributeList (rtLIST);

  rtLIST ["l2_roughness"]        = FX_PATTERN;
  rtLIST ["l2_reflection_color"] = FX_PATTERN;
  rtLIST ["l2_isotropy"]         = FX_PATTERN;

}  /* getAttributeList() */





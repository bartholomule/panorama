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
#include "bsdf_ward.h"
#include "llapi/attribute.h"
#include "llapi/extended_attribute.h"

DEFINE_PLUGIN ("BsdfWard", FX_BSDF_CLASS, TBsdfWard);


TBsdfWard::TBsdfWard (void)
{

  ptStandardDeviation_x = (magic_pointer<TPattern>)new TPattern (0.3);
  ptStandardDeviation_y = (magic_pointer<TPattern>)new TPattern (0.3);

  setSpecularColor ((magic_pointer<TPattern>)new TPattern (TColor::_white()));

}  /* TBsdfWard() */


int TBsdfWard::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "roughness_x" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_PATTERN )
    {
      ptStandardDeviation_x = (TPattern*) nVALUE.pvValue;
    }
    else if ( eTYPE == FX_REAL )
    {
      ptStandardDeviation_x = new TPattern (nVALUE.dValue);
    }
    else if ( eTYPE == FX_COLOR )
    {
      ptStandardDeviation_x = new TPattern (*((TColor*) nVALUE.pvValue));
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      ptStandardDeviation_x = pat->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "roughness_y" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_PATTERN )
    {
      ptStandardDeviation_y = (TPattern*) nVALUE.pvValue;
    }
    else if ( eTYPE == FX_REAL )
    {
      ptStandardDeviation_y = new TPattern (nVALUE.dValue);
    }
    else if ( eTYPE == FX_COLOR )
    {
      ptStandardDeviation_y = new TPattern (*((TColor*) nVALUE.pvValue));
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      ptStandardDeviation_y = pat->tValue;
    }
#endif    
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "specular_color" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_PATTERN )
    {
      setSpecularColor (((TPattern*) nVALUE.pvValue)->clone_new());
    }
    else if ( eTYPE == FX_REAL )
    {
      setSpecularColor (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setSpecularColor (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      setSpecularColor (pat->tValue);
    }
#endif    
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


int TBsdfWard::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)  
  if ( rktNAME == "roughness_x" )
  {
    rnVALUE.pvValue = ptStandardDeviation_x.get_pointer();
  }
  else if ( rktNAME == "roughness_y" )
  {
    rnVALUE.pvValue = ptStandardDeviation_y.get_pointer();
  }
  else if ( rktNAME == "specular_color" )
  {
    rnVALUE.pvValue = ptSpecularColor.get_pointer();
  }
#else
  if ( rktNAME == "roughness_x" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (ptStandardDeviation_x);
  }
  else if ( rktNAME == "roughness_y" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (ptStandardDeviation_y);
  }
  else if ( rktNAME == "specular_color" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (ptSpecularColor);
  }
#endif
  else
  {
    return TBsdf::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TBsdfWard::getAttributeList (TAttributeList& rtLIST) const
{

  TBsdf::getAttributeList (rtLIST);

  rtLIST ["roughness_x"]    = FX_PATTERN;
  rtLIST ["roughness_y"]    = FX_PATTERN;
  rtLIST ["specular_color"] = FX_PATTERN;

}  /* getAttributeList() */





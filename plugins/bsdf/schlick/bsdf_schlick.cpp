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
#include "bsdf_schlick.h"
#include "llapi/attribute.h"
#include "llapi/extended_attribute.h"

DEFINE_PLUGIN ("BsdfSchlick", FX_BSDF_CLASS, TBsdfSchlick);


TBsdfSchlick::TBsdfSchlick (void)
{

  ptRoughness   = (magic_pointer<TPattern>)new TPattern (0.3);
  ptIsotropy    = (magic_pointer<TPattern>)new TPattern (1.0);
  ptReflectance = (magic_pointer<TPattern>)new TPattern (TColor::_white()); 

}  /* TBsdfSchlick() */


int TBsdfSchlick::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "roughness" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_PATTERN )
    {
      ptRoughness = ((TPattern*) nVALUE.pvValue)->clone_new();
    }
    else if ( eTYPE == FX_REAL )
    {
      ptRoughness = new TPattern (nVALUE.dValue);
    }
    else if ( eTYPE == FX_COLOR )
    {
      ptRoughness = new TPattern (*((TColor*) nVALUE.pvValue));
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      ptRoughness = pat->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "reflection_color" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_PATTERN )
    {
      ptReflectance = ((TPattern*) nVALUE.pvValue)->clone_new();
    }
    else if ( eTYPE == FX_REAL )
    {
      ptReflectance = new TPattern (nVALUE.dValue);
    }
    else if ( eTYPE == FX_COLOR )
    {
      ptReflectance = new TPattern (*((TColor*) nVALUE.pvValue));
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      ptReflectance = pat->tValue;
    }
#endif    
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "isotropy" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_PATTERN )
    {
      ptIsotropy = ((TPattern*) nVALUE.pvValue)->clone_new();
    }
    else if ( eTYPE == FX_REAL )
    {
      ptIsotropy = new TPattern (nVALUE.dValue);
    }
    else if ( eTYPE == FX_COLOR )
    {
      ptIsotropy = new TPattern (*((TColor*) nVALUE.pvValue));
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      ptIsotropy = pat->tValue;
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

  setupBsdf();

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TBsdfSchlick::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)
  if ( rktNAME == "roughness" )
  {
    rnVALUE.pvValue = ptRoughness.get_pointer();
  }
  else if ( rktNAME == "reflection_color" )
  {
    rnVALUE.pvValue = ptReflectance.get_pointer();
  }
  else if ( rktNAME == "isotropy" )
  {
    rnVALUE.pvValue = ptIsotropy.get_pointer();
  }
#else
  if ( rktNAME == "roughness" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (ptRoughness);
  }
  else if ( rktNAME == "reflection_color" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (ptReflectance);
  }
  else if ( rktNAME == "isotropy" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (ptIsotropy);
  }
#endif  
  else
  {
    return TBsdf::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TBsdfSchlick::getAttributeList (TAttributeList& rtLIST) const
{

  TBsdf::getAttributeList (rtLIST);

  rtLIST ["roughness"]        = FX_PATTERN;
  rtLIST ["reflection_color"] = FX_PATTERN;
  rtLIST ["isotropy"]         = FX_PATTERN;

}  /* getAttributeList() */





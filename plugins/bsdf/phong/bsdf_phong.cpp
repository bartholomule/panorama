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
#include <iostream>
#include "llapi/object.h"
#include "llapi/material.h"
#include "bsdf_phong.h"
#include "llapi/attribute.h"
#include "llapi/extended_attribute.h"

DEFINE_PLUGIN ("BsdfPhong", FX_BSDF_CLASS, TBsdfPhong);


TBsdfPhong::TBsdfPhong (void)
{

  setPhongExp (new TPattern (0.0));
  setSpecularColor (new TPattern (TColor::_white()));

}  /* TBsdfPhong() */


int TBsdfPhong::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "exponent" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_PATTERN )
    {
      setPhongExp (((TPattern*) nVALUE.pvValue)->clone_new());
    }
    else if ( eTYPE == FX_REAL )
    {
      setPhongExp (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setPhongExp (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      setPhongExp (pat->tValue);
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


int TBsdfPhong::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{
#if !defined(NEW_ATTRIBUTES)
  if ( rktNAME == "exponent" )
  {
    rnVALUE.pvValue = ptPhongExp.get_pointer();
  }
  else if ( rktNAME == "specular_color" )
  {
    rnVALUE.pvValue = ptSpecularColor.get_pointer();
  }
#else
  if ( rktNAME == "exponent" )
  {
    rnVALUE = new TAttribPattern (ptPhongExp);
  }
  else if ( rktNAME == "specular_color" )
  {
    rnVALUE = new TAttribPattern (ptSpecularColor);    
  }  
#endif
  else
  {
    return TBsdf::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TBsdfPhong::getAttributeList (TAttributeList& rtLIST) const
{

  TBsdf::getAttributeList (rtLIST);

  rtLIST ["exponent"]       = FX_PATTERN;
  rtLIST ["specular_color"] = FX_PATTERN;

}  /* getAttributeList() */

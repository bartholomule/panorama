/*
*  Copyright (C) 1999 Angel Jimenez Jimenez, Carlos Jimenez Moreno and Peter Barnett
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
#include "pat_wood.h"
#include "llapi/attribute.h"
#include "llapi/extended_attribute.h"

DEFINE_PLUGIN ("PatternWood", FX_PATTERN_CLASS, TPatternWood);

TColor TPatternWood::evaluate (const TVector& rktPOINT) const
{

  TScalar  tX = rktPOINT.x();
  TScalar  tY = rktPOINT.y();
  TScalar  tZ = rktPOINT.z();
  TScalar  tValue;
  TColor   tRet;
  
  tValue = tWood.wood (tX, tY, tZ, tRingScale, tGrainFactor);
  
  tValue = clamp (tValue, 0, 1);

  if ( bGradientLoaded == true )
  {
    tRet = tGradient.getColorAt (tValue);
  }
  else
  {
    tRet = lerp (tColor, tBaseColor, tValue);
  }
  
  return tRet;

}  /* evaluate() */


int TPatternWood::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "color" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_COLOR )
    {
      setColor (*((TColor*) nVALUE.pvValue));
    }
#else
    magic_pointer<TAttribColor> col = get_color(nVALUE);
    if( !!col )
    {
      setColor (col->tValue);
    }
#endif
    else 
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "base_color" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_COLOR )
    {
      setBaseColor (*((TColor*) nVALUE.pvValue));
    }
    else if ( eTYPE == FX_STRING )
    {
      bGradientLoaded = tGradient.loadGradient((char *) nVALUE.pvValue);
    }
#else
    magic_pointer<TAttribColor>  col = get_color(nVALUE);
    magic_pointer<TAttribString> str = get_string(nVALUE);    
    if( !!col )
    {
      setBaseColor (col->tValue);
    }
    else if( !!str )
    {
      bGradientLoaded = tGradient.loadGradient (str->tValue);
    }
#endif    
    else 
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "ringscale" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_REAL )
    {
      tRingScale = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tRingScale = r->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "grain" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      tGrainFactor = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tGrainFactor = r->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "zoom" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_VECTOR )
    {
      tZoom = *((TVector*) nVALUE.pvValue);
      tZoom.set (1.0 / tZoom.x(), 1.0 / tZoom.y(), 1.0 / tZoom.z());
    }
#else
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      tZoom = vec->tValue;
      tZoom.set (1.0 / tZoom.x(), 1.0 / tZoom.y(), 1.0 / tZoom.z());      
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TPattern::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TPatternWood::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)
  if ( rktNAME == "color" )
  {
    rnVALUE.pvValue = &tColor;
  }
  else if ( rktNAME == "base_color" )
  {
    rnVALUE.pvValue = &tBaseColor;
  }
  else if ( rktNAME == "ringscale" )
  {
    rnVALUE.dValue = tRingScale;
  }
  else if ( rktNAME == "grain" )
  {
    rnVALUE.dValue = tGrainFactor;
  }
  else if ( rktNAME == "zoom" )
  {
    // [_ERROR_] It should return the inverse of this vector.
    rnVALUE.pvValue = &tZoom;
  }
#else
  if ( rktNAME == "color" )
  {
    rnVALUE = (user_arg_type)new TAttribColor (tColor);
  }
  else if ( rktNAME == "base_color" )
  {
    rnVALUE = (user_arg_type)new TAttribColor (tBaseColor);
  }
  else if ( rktNAME == "ringscale" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tRingScale);
  }
  else if ( rktNAME == "grain" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tGrainFactor);
  }
  else if ( rktNAME == "zoom" )
  {
    TVector inv(1.0 / tZoom.x(), 1.0 / tZoom.y(), 1.0 / tZoom.z());
    rnVALUE = (user_arg_type)new TAttribVector (inv);
  }  
#endif
  else
  {
    return TPattern::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPatternWood::getAttributeList (TAttributeList& rtLIST) const
{

  TPattern::getAttributeList (rtLIST);

  rtLIST ["color"]      = FX_COLOR;
  rtLIST ["base_color"] = FX_COLOR;
  rtLIST ["ringscale"]  = FX_REAL;
  rtLIST ["grain"]      = FX_REAL;
  rtLIST ["zoom"]       = FX_VECTOR;

}  /* getAttributeList() */

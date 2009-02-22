/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez, Carlos Jimenez Moreno and Peter Barnett
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
#include <cmath>
#include "pat_marble.h"
#include "llapi/attribute.h"
#include "llapi/extended_attribute.h"

DEFINE_PLUGIN ("PatternMarble", FX_PATTERN_CLASS, TPatternMarble);


int TPatternMarble::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
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
    magic_pointer<TAttribColor> col = get_color(nVALUE);
    magic_pointer<TAttribString> str = get_string(nVALUE);    
    if( !!col )
    {
      setColor (col->tValue);
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
      tZoom.set (1.0 / vec->tValue.x(), 1.0 / vec->tValue.y(), 1.0 / vec->tValue.z());
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "lacunarity" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      if ( nVALUE.dValue > 0.0 )
      {
        tLacunarity = nVALUE.dValue;
      }
      else
      {
        return FX_ATTRIB_WRONG_VALUE;
      }
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      if( r->tValue <= 0.0 )
      {
        return FX_ATTRIB_WRONG_VALUE;	
      }
      tLacunarity = r->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "octaves" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      if ( nVALUE.dValue >= 1.0 )
      {
        tNumOctaves = nVALUE.dValue;
      }
      else
      {
        return FX_ATTRIB_WRONG_VALUE;
      }
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      if( r->tValue < 1.0 )
      {
        return FX_ATTRIB_WRONG_VALUE;	
      }
      tNumOctaves = r->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }    
  }
  else if ( rktNAME == "offset" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      tOffset = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tOffset = r->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }    
  }
  else if ( rktNAME == "multiplier" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      if ( fabs (nVALUE.dValue) > FX_EPSILON )
      {
        tMultiplier = nVALUE.dValue;
      }
      else
      {
        return FX_ATTRIB_WRONG_VALUE;
      }
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      if( fabs(r->tValue) <= FX_EPSILON )
      {
        return FX_ATTRIB_WRONG_VALUE;	
      }
      tMultiplier = r->tValue;
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


int TPatternMarble::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
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
  else if ( rktNAME == "zoom" )
  {
    // [_ERROR_] It should return the inverse of this std::vector.
    rnVALUE.pvValue = &tZoom;
  }
  else if ( rktNAME == "offset" )
  {
    rnVALUE.dValue = tOffset;
  }
  else if ( rktNAME == "multiplier" )
  {
    rnVALUE.dValue = tMultiplier;
  }
  else if ( rktNAME == "lacunarity" )
  {
    rnVALUE.dValue = tLacunarity;
  }
  else if ( rktNAME == "octaves" )
  {
    rnVALUE.dValue = tNumOctaves;
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
  else if ( rktNAME == "zoom" )
  {
    TVector inv(1.0 / tZoom.x(), 1.0 / tZoom.y(), 1.0 / tZoom.z());
    rnVALUE = (user_arg_type)new TAttribVector (inv);
  }
  else if ( rktNAME == "offset" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tOffset);
  }
  else if ( rktNAME == "multiplier" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tMultiplier);
  }
  else if ( rktNAME == "lacunarity" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tLacunarity);
  }
  else if ( rktNAME == "octaves" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tNumOctaves);
  }
#endif
  else
  {
    return TPattern::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPatternMarble::getAttributeList (TAttributeList& rtLIST) const
{

  TPattern::getAttributeList (rtLIST);

  rtLIST ["color"]      = FX_COLOR;
  rtLIST ["base_color"] = FX_COLOR;
  rtLIST ["zoom"]       = FX_VECTOR;
  rtLIST ["offset"]     = FX_REAL;
  rtLIST ["multiplier"] = FX_REAL;
  rtLIST ["lacunarity"] = FX_REAL;
  rtLIST ["octaves"]    = FX_REAL;

}  /* getAttributeList() */

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
#include "llapi/pattern.h"
#include "llapi/light.h"
#include "llapi/attribute.h"

bool TLight::findAllIntersections(const class TRay &, class TSpanList &) const
{
  //      cerr << "Pure light with intersection test!!" << endl;
  return false;
}

int TLight::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "color" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_COLOR )
    {
      setColor (*((TColor*) nVALUE.pvValue));
    }
#else
    magic_pointer<TAttribColor> c = get_color(nVALUE);
    if( !!c )
    {
      setColor (c->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "intensity" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_REAL )
    {
      setIntensity (nVALUE.dValue);
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      setIntensity (r->tValue);
    }    
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "shadow" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_BOOL )
    {
      tProperties.gShadow = nVALUE.gValue;
    }
#else
    magic_pointer<TAttribBool> b = get_bool(nVALUE);
    if( !!b )
    {
      tProperties.gShadow = b->tValue;
    }    
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "volumetric" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_BOOL )
    {
      tProperties.gVolumetric = nVALUE.gValue;
    }
#else
    magic_pointer<TAttribBool> b = get_bool(nVALUE);
    if( !!b )
    {
      tProperties.gVolumetric = b->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "raytraced" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_BOOL )
    {
      tProperties.gRaytraced = nVALUE.gValue;
    }
#else
    magic_pointer<TAttribBool> b = get_bool(nVALUE);
    if( !!b )
    {
      tProperties.gRaytraced = b->tValue;
    }    
#endif
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
  
#if !defined(NEW_ATTRIBUTES)
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
#else
  if ( rktNAME == "color" )
  {
    rnVALUE = (user_arg_type)new TAttribColor (tColor);
  }
  else if ( rktNAME == "intensity" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tIntensity);
  }
  else if ( rktNAME == "shadow" )
  {
    rnVALUE = (user_arg_type)new TAttribBool (tProperties.gShadow);
  }
  else if ( rktNAME == "volumetric" )
  {
    rnVALUE = (user_arg_type)new TAttribBool (tProperties.gVolumetric);
  }
  else if ( rktNAME == "raytraced" )
  {
    rnVALUE = (user_arg_type)new TAttribBool (tProperties.gRaytraced);
  }
  else if ( rktNAME == "lightonly" )
  {
    rnVALUE = (user_arg_type)new TAttribBool (true);
  }  
#endif
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



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
#include "llapi/scene.h"
#include "if_fog.h"
#include "llapi/attribute.h"

#define FX_MAX_Z                 (SCALAR_MAX / 2)

DEFINE_PLUGIN ("IF_Fog", FX_IMAGE_FILTER_CLASS, TIF_Fog);

TIF_Fog::TIF_Fog (void) :
  TImageFilter(),
  tFogDistance (1000),
  tFogColor (TColor::_white())
{

  wNeededBuffers = FX_ZBUFFER;
  
}  /* TIF_Fog() */


void TIF_Fog::filter (SBuffers& rsBUFFERS)
{

  float        Z;
  float        fFactor;
  TColor       tPixel;
  TImage*      ptImage   = rsBUFFERS.ptImage;
  TZBuffer*    ptZBuffer = rsBUFFERS.ptZBuffer;
  
  if( pfUserUpdate )
  {
    pfUserUpdate(1.0, pvUserData);
  }
  
  for (size_t J = 0; ( J < ptImage->height() ) ;J++)
  {
    for (size_t I = 0; ( I < ptImage->width() ) ;I++)
    {
      Z = ptZBuffer->getPixel (I, J);
      if ( Z > FX_MAX_Z )
      {
        fFactor = 1;
      }
      else
      {
//        fFactor = min (1.0, Z / tFogDistance);
        fFactor = 1 - exp (-Z / tFogDistance);
      }
      tPixel  = ptImage->getPixel (I, J);
      ptImage->setPixel (I, J, lerp (tPixel, tFogColor, fFactor));
    }
    if( pfUserUpdate )
    {
      if(!pfUserUpdate(J / double(ptImage->height()), pvUserData))
      {
	break;
      }
    }    
  }
  if( pfUserUpdate )
  {
    pfUserUpdate(1.0, pvUserData);
  }  

}  /* filter() */


int TIF_Fog::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "color" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_COLOR )
    {
      tFogColor = *((TColor*) nVALUE.pvValue);
    }
#else
    magic_pointer<TAttribColor> col = get_color(nVALUE);
    if( !!col )
    {
      tFogColor = col->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "distance" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      tFogDistance = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tFogDistance = r->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TImageFilter::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TIF_Fog::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)  
  if ( rktNAME == "color" )
  {
    rnVALUE.pvValue = &tFogColor;
  }
  else if ( rktNAME == "distance" )
  {
    rnVALUE.dValue = tFogDistance;
  }
#else
  if ( rktNAME == "color" )
  {
    rnVALUE = (user_arg_type)new TAttribColor (tFogColor);
  }
  else if ( rktNAME == "distance" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tFogDistance);
  }
#endif
  else
  {
    return TImageFilter::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TIF_Fog::getAttributeList (TAttributeList& rtLIST) const
{

  TImageFilter::getAttributeList (rtLIST);

  rtLIST ["color"]    = FX_COLOR;
  rtLIST ["distance"] = FX_REAL;

}  /* getAttributeList() */

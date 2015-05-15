/*
*  Copyright (C) 1999 Ken Geis
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

#include <cmath>
#include <string.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "llapi/file.h"
#include "llapi/scene.h"
#include "if_text.h"

extern multimap<string, string>   tConfigData;

#if defined(FREETYPE_MAJOR) && (FREETYPE_MAJOR >= 2)
#include "ft2.cpp"
#elif defined(TT_FREETYPE_MAJOR) && (TT_FREETYPE_MAJOR <= 1)
#include "ft1.cpp"
#else
#error "Unknown freetype library!"
#endif


DEFINE_PLUGIN ("IF_Text", FX_IMAGE_FILTER_CLASS, TIF_Text);

TIF_Text::TIF_Text (void) :
  TImageFilter(),
  tColor (TColor::_black()),
  tTranslate (0, 0)
{

  wSize = (Word) (10.0 * 64.0);  // 10.0 in 26.6 fixed point format

}  /* TIF_Text() */

int TIF_Text::setAttribute (const string& rktNAME, NAttribute nVALUE,
                            EAttribType eTYPE)
{

  if ( rktNAME == "color" )
  {
    if ( eTYPE == FX_COLOR )
    {
      tColor = *((TColor*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "fontfile" )
  {
    if ( eTYPE == FX_STRING )
    {
      tFontFile = (char *) nVALUE.pvValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "size" )
  {
    if ( eTYPE == FX_REAL )
    {
      if( nVALUE.dValue <= 0 )
      {
	return FX_ATTRIB_WRONG_VALUE;
      }
      wSize = (Word) (nVALUE.dValue * 64.0);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "text" )
  {
    if ( eTYPE == FX_STRING )
    {
      tText = (char *) nVALUE.pvValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "xlate" )
  {
    if ( eTYPE == FX_VECTOR2 )
    {
      tTranslate = *((TVector2 *) nVALUE.pvValue);
    }
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


int TIF_Text::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "color" )
  {
    rnVALUE.pvValue = &tColor;
  }
  else if ( rktNAME == "fontfile" )
  {
    rnVALUE.pvValue = &tFontFile;
  }
  else if ( rktNAME == "size" )
  {
    rnVALUE.dValue = wSize / 64.0;
  }
  else if ( rktNAME == "text" )
  {
    rnVALUE.pvValue = &tText;
  }
  else if ( rktNAME == "xlate" )
  {
    rnVALUE.pvValue = &tTranslate;
  }
  else
  {
    return TImageFilter::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TIF_Text::getAttributeList (TAttributeList& rtLIST) const
{

  TImageFilter::getAttributeList (rtLIST);

  rtLIST ["color"]     = FX_COLOR;
  rtLIST ["fontfile"]  = FX_STRING;
  rtLIST ["size"]      = FX_REAL;
  rtLIST ["text"]      = FX_STRING;
  rtLIST ["xlate"]     = FX_VECTOR2;
  
}  /* getAttributeList() */

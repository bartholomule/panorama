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
#include <freetype.h>
#include "llapi/scene.h"
#include "if_text.h"

DEFINE_PLUGIN ("IF_Text", FX_IMAGE_FILTER_CLASS, TIF_Text);

TIF_Text::TIF_Text (void) :
  TImageFilter(),
  tColor (TColor::_black()),
  tTranslate (0, 0)
{

  wSize = (Word) (10.0 * 64.0);  // 10.0 in 26.6 fixed point format

}  /* TIF_Text() */


void TIF_Text::filter (SBuffers& rsBUFFERS)
{

  TColor               tPixelColor, tFontColor;
  TImage*              ptImage = rsBUFFERS.ptImage;
  TT_Engine            tEngine;
  TT_Face              tFace;
  TT_Face_Properties   tFaceProps;
  TT_Instance          tInstance;
  TT_CharMap           tCharMap;
  TT_Glyph             tGlyph;
  TT_Glyph_Metrics     tMetrics;
  TT_Pos               tXPos, tYPos;
  TT_Outline           tOutline;
  TT_Raster_Map        tPixmap;
  int                  iError;
  Byte                 abPalette[] = {0, 63, 127, 191, 255};
    
  iError = TT_Init_FreeType (&tEngine);
  if ( iError )
  {
    cerr << "Could not create FreeType engine." << endl;
    return;
  }
  
  iError = TT_Open_Face (tEngine, tFontFile.c_str(), &tFace);
  if ( iError )
  {
    cerr << "Could not open file '" << tFontFile << "'." << endl;
    return;
  }

  iError = TT_Set_Raster_Gray_Palette (tEngine, abPalette);
  if ( iError )
  {
    cerr << "Could not set raster palette." << endl;
    return;
  }
    
  iError = TT_Get_Face_Properties (tFace, &tFaceProps);
  if ( iError )
  {
    cerr << "Could not get face properties." << endl;
    return;
  }

  iError = TT_New_Instance (tFace, &tInstance);
  if ( iError )
  {
    cerr << "Could not create instance." << endl;
    return;
  }

  iError = TT_Set_Instance_Resolutions (tInstance, 72, 72);
  if ( iError )
  {
    cerr << "Could not set resolution." << endl;
    return;
  }

  iError = TT_Set_Instance_CharSize (tInstance, wSize);
  if ( iError )
  {
    cerr << "Could not set character size." << endl;
    return;
  }

  iError = TT_Get_CharMap (tFace, 0, &tCharMap);
  if ( iError )
  {
    cerr << "Could not get charmap." << endl;
    return;
  }

  iError = TT_New_Glyph (tFace, &tGlyph);
  if ( iError )
  {
    cerr << "Could not create glyph." << endl;
    return;
  }

  //  Set up the raster map
  tPixmap.rows = ptImage->height();
  tPixmap.width = ptImage->width();
  tPixmap.cols = (tPixmap.width + 3) & -4;
  tPixmap.flow = TT_Flow_Down;
  tPixmap.size = tPixmap.rows * tPixmap.cols;
  tPixmap.bitmap = new Byte[tPixmap.size];
  memset (tPixmap.bitmap, 0, tPixmap.size);
  
  tXPos = (unsigned int) tTranslate.x();
  tYPos = ptImage->height() - ((unsigned int) tTranslate.y());
  
  for (size_t tI = 0; tI < tText.length(); tI++)
  {
    TT_UShort uIndex;

    uIndex = TT_Char_Index (tCharMap, tText[tI]);
    if ( ! uIndex )
    {
      cerr << "Could not find char index for '" << tText[tI] << "'." << endl;
      continue;
    }
    
    iError = TT_Load_Glyph (tInstance, tGlyph, uIndex, TTLOAD_DEFAULT);
    if ( iError )
    {
      cerr << "Could not load glyph for '" << tText[tI] << "'." << endl;
      cerr << "Error code: " << iError << endl;
      continue;
    }

    TT_Get_Glyph_Metrics (tGlyph, &tMetrics);
    TT_Get_Glyph_Outline (tGlyph, &tOutline);
    TT_Translate_Outline (&tOutline, tXPos * 64, tYPos * 64);
    
    //  blit bitmap to surface
    TT_Get_Outline_Pixmap (tEngine, &tOutline, &tPixmap);
    
    tXPos += (tMetrics.advance + 32) / 64;
  }
  
  for (size_t J = 0; ( J < ptImage->height() ) ; J++)
  {
    for (size_t I = 0; ( I < ptImage->width() ) ; I++)
    {
      Byte bFontAlpha = ((char *) tPixmap.bitmap)[J * tPixmap.cols + I];
      if ( bFontAlpha != 0 )
      {
        tPixelColor = ptImage->getPixel (I, J);
        tPixelColor *= (255 - bFontAlpha) / 255.0;

        tFontColor = tColor;
        tFontColor *= bFontAlpha / 255.0;
        
        tPixelColor += tFontColor;
        ptImage->setPixel (I, J, tPixelColor);
      }
    }
  }

  //  Clean up
  delete tPixmap.bitmap;
  
}  /* filter() */


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

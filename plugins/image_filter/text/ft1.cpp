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

/*
  This function was moved here by Kevin Harris, in an attempt to support both
  the new and the old freetype libraries.  If this does not work, either fix
  it, or upgrade your freetype library.  The code for using the newer library
  is in ft2.cpp.
 */

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
  Byte                 abPalette[]   = {0, 63, 127, 191, 255};
  bool                 gAbsolutePath = ( tFontFile[0] == '/' );

  iError = TT_Init_FreeType (&tEngine);
  if ( iError )
  {
    GOM.error() << "Could not create FreeType engine." << endl;
    return;
  }
  
  iError = 1;
  if ( gAbsolutePath )
  {
    iError = TT_Open_Face (tEngine, tFontFile.c_str(), &tFace);
  }
  else
  {
    multimap<string, string>::const_iterator   iter;

    iter = tConfigData.find ("FontPath");
    while ( ( iter != tConfigData.end() ) && ( (*iter).first == "FontPath" ) )
    {
      string   tAux ((*iter).second + "/" + tFontFile);
      
      if ( FileExists (tAux) )
      {
        iError = TT_Open_Face (tEngine, tAux.c_str(), &tFace);
        break;
      }
      iter++;
    }
  }

  if ( iError )
  {
    GOM.error() << "Could not open file '" << tFontFile << "'." << endl;
    return;
  }

  iError = TT_Set_Raster_Gray_Palette (tEngine, abPalette);
  if ( iError )
  {
    GOM.error() << "Could not set raster palette." << endl;
    return;
  }
    
  iError = TT_Get_Face_Properties (tFace, &tFaceProps);
  if ( iError )
  {
    GOM.error() << "Could not get face properties." << endl;
    return;
  }

  iError = TT_New_Instance (tFace, &tInstance);
  if ( iError )
  {
    GOM.error() << "Could not create instance." << endl;
    return;
  }

  iError = TT_Set_Instance_Resolutions (tInstance, 72, 72);
  if ( iError )
  {
    GOM.error() << "Could not set resolution." << endl;
    return;
  }

  iError = TT_Set_Instance_CharSize (tInstance, wSize);
  if ( iError )
  {
    GOM.error() << "Could not set character size." << endl;
    return;
  }

  iError = TT_Get_CharMap (tFace, 0, &tCharMap);
  if ( iError )
  {
    GOM.error() << "Could not get charmap." << endl;
    return;
  }

  iError = TT_New_Glyph (tFace, &tGlyph);
  if ( iError )
  {
    GOM.error() << "Could not create glyph." << endl;
    return;
  }

  //  Set up the raster map
  tPixmap.rows = ptImage->height();
  tPixmap.width = ptImage->width();
  tPixmap.cols = (tPixmap.width + 3) & -4;
  tPixmap.flow = TT_Flow_Down;
  tPixmap.size = tPixmap.rows * tPixmap.cols;
  tPixmap.bitmap = calloc (1, tPixmap.size);
  
  tXPos = (unsigned int) tTranslate.x();
  tYPos = ptImage->height() - ((unsigned int) tTranslate.y());

  if( pfUserUpdate )
  {
    pfUserUpdate(0.0, pvUserData);
  }
  
  for (size_t tI = 0; tI < tText.length(); tI++)
  {
    TT_UShort uIndex;

    uIndex = TT_Char_Index (tCharMap, tText[tI]);
    if ( ! uIndex )
    {
      GOM.error() << "Could not find char index for '" << tText[tI] << "'." << endl;
      continue;
    }
    
    iError = TT_Load_Glyph (tInstance, tGlyph, uIndex, TTLOAD_DEFAULT);
    if ( iError )
    {
      GOM.error() << "Could not load glyph for '" << tText[tI] << "'." << endl;
      GOM.error() << "Error code: " << iError << endl;
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
  
  //  Clean up
  free (tPixmap.bitmap);
  
}  /* filter() */


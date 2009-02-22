/*
*  Copyright (C) 2001 Kevin Harris
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
  Copy a bitmap of a 'glyph' onto the given panorama image.
 */
static void glyph_to_image(TImage* ptImage,
			   unsigned x, unsigned y,
			   const TColor& color,
			   const FT_Bitmap& glyph)
{
  unsigned min_x = 0;
  unsigned min_y = 0;
  unsigned max_x = ptImage->width() - x;
  unsigned max_y = ptImage->height() - y;

  if(max_x > unsigned(glyph.width))
  {
    max_x = glyph.width;
  }
  if(max_y > unsigned(glyph.rows))
  {
    max_y = glyph.rows;
  }
  
  TColor tPixelColor, tFontColor;  
  for(unsigned j = min_y; j < max_y; ++j)
  {
    for(unsigned i = min_x; i < max_x; ++i)
    {
      Byte bFontAlpha = glyph.buffer[ j * glyph.width + i];
      // If it is not transparent...
      if ( bFontAlpha != 0 )
      {
	tPixelColor = ptImage->getPixel (i + x, j + y);
	tPixelColor *= (255 - bFontAlpha) / 255.0;

	tFontColor = color;
	tFontColor *= bFontAlpha / 255.0;

	tPixelColor += tFontColor;
	ptImage->setPixel (i + x, j + y, tPixelColor);
      }
    }
  }
} /* glyph_to_image() */
			    

void TIF_Text::filter (SBuffers& rsBUFFERS)
{
  // FIXME!!! Allow the user a choice of the face number.
  wFaceNumber = 0;
  
  TColor               tPixelColor, tFontColor;
  TImage*              ptImage = rsBUFFERS.ptImage;
  FT_Library           tEngine;
  FT_Face              tFace;
  FT_CharMap           tCharMap;
  FT_Pos               tXPos, tYPos;
  int                  iError;
  bool                 gAbsolutePath = ( tFontFile[0] == '/' );

  iError = FT_Init_FreeType (&tEngine);
  if ( iError )
  {
    GOM.error() << "Could not create FreeType engine." << std::endl;
    return;
  }
  
  iError = 1;
  if ( gAbsolutePath )
  {
    iError = FT_New_Face (tEngine, tFontFile.c_str(), wFaceNumber, &tFace);
  }
  else
  {
    std::multimap<std::string, std::string>::const_iterator   iter;

    iter = tConfigData.find ("FontPath");
    while ( ( iter != tConfigData.end() ) && ( (*iter).first == "FontPath" ) )
    {
      std::string   tAux ((*iter).second + "/" + tFontFile);
      
      if ( FileExists (tAux) )
      {
	// Load the first font face from the file.
        iError = FT_New_Face (tEngine, tAux.c_str(), wFaceNumber, &tFace);
        break;
      }
      iter++;
    }
  }

  if ( iError )
  {
    GOM.error() << "Could not open file '" << tFontFile << "'." << std::endl;
    return;
  }

  iError = FT_Set_Char_Size(tFace, wSize, wSize, 72, 72);
  if ( iError )
  {
    GOM.error() << "Could not set the face size and resolution" << std::endl;
    return;
    
  }

  tCharMap = tFace->charmap;
  if ( tCharMap == NULL )
  {
    if(tFace->num_charmaps > 0)
    {
      tCharMap = tFace->charmaps[0];
      FT_Set_Charmap(tFace, tCharMap);
    }
    else
    {
      GOM.error() << "Could not get charmap." << std::endl;
      return;
    }
  }

  //  Set up the raster map
  tXPos = (unsigned int) tTranslate.x();
  tYPos = ptImage->height() - ((unsigned int) tTranslate.y());

  if( pfUserUpdate )
  {
    pfUserUpdate(0.0, pvUserData);
  }
  
  for (size_t tI = 0; tI < tText.length(); tI++)
  {
    FT_UShort uIndex;

    uIndex = FT_Get_Char_Index (tFace, tText[tI]);
    if ( ! uIndex )
    {
      GOM.error() << "Could not find char index for '" << tText[tI] << "'." << std::endl;
      continue;
    }
    
    iError = FT_Load_Glyph (tFace, uIndex, FT_LOAD_DEFAULT);
    if ( iError )
    {
      GOM.error() << "Could not load glyph for '" << tText[tI] << "'." << std::endl;
      GOM.error() << "Error code: " << iError << std::endl;
      continue;
    }

    //  Render the glyph to its buffer...
    iError = FT_Render_Glyph( tFace->glyph, ft_render_mode_normal );
    
    // Copy it to the output image
    glyph_to_image(ptImage,
		   tXPos + tFace->glyph->metrics.horiBearingX / 64,
		   tYPos - tFace->glyph->metrics.horiBearingY / 64,
		   tColor, tFace->glyph->bitmap);
    
    tXPos += tFace->glyph->metrics.horiAdvance / 64;

    if( pfUserUpdate )
    {
      if(!pfUserUpdate(tI / double(tText.length()), pvUserData))
      {
	break;
      }
    }    
  }
  if( pfUserUpdate )
  {
    pfUserUpdate(1.0, pvUserData);
  }  
  // Clean up...
  FT_Done_FreeType(tEngine);
}  /* filter() */



/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  Copyright (C) 1999 Jose Antonio Robles Ordoñez 
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

#include <stdio.h> // for FILE access
#include "hlapi/image_manager.h"

extern "C" {
#include <jpeglib.h> //jpeg library
}
#include "jpeg_io.h"

DEFINE_IMAGE_IO_PLUGIN_WITH_ALIAS ("jpeg", "jpg", TImageJpeg);

int TImageJpeg::save (const TImage* pktIMAGE)
{

  FILE*                          tOutFile;
  static struct jpeg_error_mgr   _sWriteJerr;
  struct jpeg_compress_struct    sComp;
  Byte*                          pbScanline;
  TColor                         tPixel;
  TColor                         tColor;
  
  tOutFile = fopen (tFileName.c_str(),"w");
  
  if ( !tOutFile )
  {
    return -1;
  }

  pbScanline = new Byte[pktIMAGE->width() * 3];

  if ( !pbScanline )
  {
    return -1;
  }

  /* Set the standard error routine and some other parameters */
  
  sComp.err = jpeg_std_error (&_sWriteJerr);
  jpeg_create_compress (&sComp);

  /* Set output file */
  jpeg_stdio_dest (&sComp, tOutFile);
  
  /* Set some parameters. */
  sComp.image_width  = pktIMAGE->width();
  sComp.image_height = pktIMAGE->height();
  sComp.input_components = 3; /* Number of channels -> RGB */
  sComp.in_color_space = JCS_RGB;

  jpeg_set_defaults (&sComp); /* Other defaults values */

  /* Set plugin parameters */
  jpeg_set_quality (&sComp,(int) fQuality,TRUE);
  sComp.smoothing_factor = (int) fSmoothing;

  /* Start compression */
  jpeg_start_compress (&sComp, TRUE);

  for (size_t J = 0; ( J < pktIMAGE->height() ) ;J++)
  {
    /* Each scanline */
    for (size_t I = 0;  ( I < pktIMAGE->width() * 3 ) ;I+=3)
    {
      tPixel = pktIMAGE->getPixel (I/3, J);
      tPixel.clamp();
      tColor = tPixel.convertTo24Bits();

      pbScanline [I ]    = (Byte) tColor.red();
      pbScanline [I + 1] = (Byte) tColor.green();
      pbScanline [I + 2] = (Byte) tColor.blue();
    }
    /* Write the scanline to the output file */
    jpeg_write_scanlines (&sComp, &pbScanline, 1);
  }  

  /* Finish compression and free allocated memory */
  jpeg_finish_compress  (&sComp);
  jpeg_destroy_compress (&sComp);

  fclose (tOutFile);

  delete[] pbScanline;
  
  return 0;
  
}  /* save() */


TImage* TImageJpeg::load (void)
{

  FILE*                          tInputFile;
  static struct jpeg_error_mgr   _sReadJerr;
  struct jpeg_decompress_struct  sDecomp;
  size_t                         zWidth, zHeight;
  TColor                         tColor;
  TImage*                        ptImage;
  Byte*                          pbScanline;

  tInputFile = fopen (tFileName.c_str(),"r");

  if ( !tInputFile )
  {
    return NULL;
  }

  sDecomp.err = jpeg_std_error (&_sReadJerr);

  jpeg_create_decompress (&sDecomp);
  jpeg_stdio_src (&sDecomp, tInputFile);
  jpeg_read_header (&sDecomp, TRUE);

  zWidth  = sDecomp.image_width;
  zHeight = sDecomp.image_height;
  //What happen if num_chans  != 3  more or less color components ?
  
  ptImage = new TImage (zWidth, zHeight);

  if ( !ptImage )
  {
    return NULL;
  }
  
  pbScanline = new Byte[zWidth*3];

  if ( !pbScanline )
  {
    delete ptImage;
    return NULL;
  }

  jpeg_start_decompress (&sDecomp);

  for (size_t J = 0; ( J < zHeight ) ;J++)
  {
    jpeg_read_scanlines (&sDecomp, &pbScanline, 1);

    //Process the scanline
    for (size_t I = 0; ( I < zWidth * 3 ) ;I+=3)
    {
      tColor = TColor (pbScanline[I], pbScanline[I + 1], pbScanline[I + 2]);
      tColor = tColor.convertFrom24Bits();
      ptImage->setPixel (I / 3, J, tColor);
    }    
  }

  jpeg_finish_decompress  (&sDecomp);
  jpeg_destroy_decompress (&sDecomp);

  fclose (tInputFile);  
  
  delete[] pbScanline;

  return ptImage;
  
}  /* load() */


int TImageJpeg::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "quality" )
  {
    if ( eTYPE == FX_REAL )
    {
      fQuality = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "smoothing" )
  {
    if ( eTYPE == FX_REAL )
    {
      fSmoothing = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TImageIO::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TImageJpeg::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "quality" )
  {
    rnVALUE.dValue = fQuality;
  }
  else if ( rktNAME == "smoothing" )
  {
    rnVALUE.dValue = fSmoothing;
  }
  else
  {
    return TImageIO::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TImageJpeg::getAttributeList (TAttributeList& rtLIST) const
{

  TImageIO::getAttributeList (rtLIST);

  rtLIST ["quality"]   = FX_REAL;
  rtLIST ["smoothing"] = FX_REAL;

}  /* getAttributeList() */

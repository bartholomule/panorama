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

#include <fstream.h>
#include "hlapi/image_manager.h"
#include "png_io.h"

DEFINE_IMAGE_IO_PLUGIN ("png", TImagePng);

extern "C" {
#include <png.h>
  
  void error_callback(png_structp png_ptr, const char *msg) {
    cerr << msg << endl;
  }
  void user_write_data(png_structp png_ptr, png_bytep data,
		       png_size_t length) {
    ofstream *ptOutput = (ofstream *) png_get_io_ptr(png_ptr);
    ptOutput->write(data, length);
  }
  void user_flush_data(png_structp png_ptr) {
    ofstream *ptOutput = (ofstream *) png_get_io_ptr(png_ptr);
    ptOutput->flush();
  }
}


int TImagePng::save (const TImage* pktIMAGE) {
  TColor     tColor;
  TColor     tPixel;
  size_t     zWidth, zHeight;
  ofstream   tOutput;

  tOutput.open(tFileName.c_str());

  if ( ! tOutput.good() )
    return -1;

  png_structp png_ptr =
    png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL,
			    error_callback, error_callback);

  if( ! png_ptr )
    return -1;

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if( ! info_ptr ) {
    png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
    return -1;
  }

  if(setjmp(png_ptr->jmpbuf)) {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    //    fclose(fp);
    return -1;
  }

  png_set_write_fn(png_ptr, &tOutput, user_write_data, user_flush_data);
  png_set_compression_level(png_ptr, TImagePng::iCompression);

  zWidth  = pktIMAGE->width();
  zHeight = pktIMAGE->height();
  
  png_set_IHDR(png_ptr, info_ptr, zWidth, zHeight, 8, PNG_COLOR_TYPE_RGB,
	       PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
	       PNG_FILTER_TYPE_DEFAULT);

  png_write_info(png_ptr, info_ptr);

  png_byte *row = new png_byte[zWidth * 3];

  for (size_t j = 0; j < zHeight; j++) {
    int row_index = 0;
    for (size_t i = 0; i < zWidth; i++) {
      tPixel = pktIMAGE->getPixel (i, j);
      tPixel.clamp();
      tColor = tPixel.convertTo24Bits();
      row[row_index++] = (Byte) tColor.red();
      row[row_index++] = (Byte) tColor.green();
      row[row_index++] = (Byte) tColor.blue();
    }
    png_write_row(png_ptr, row);
  }

  png_write_end(png_ptr, info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);

  delete row;

  tOutput.close();

  return 0;
  
}  /* TImagePng::save() */


TImage* TImagePng::load ()
{

  Byte        bRed, bGreen, bBlue;
  TColor      tColor;
  TImage*     ptImage;
  size_t      zWidth, zHeight;
  ifstream    tInput;

  cerr << "TImagePng::load() unimplemented." << endl;
  
  tInput.open(tFileName.c_str());

  if ( ! tInput.good() )
    return NULL;
  
  return NULL;
  
}  /* TImagePng::load() */


int TImagePng::setAttribute (const string& rktNAME, NAttribute nVALUE,
			     EAttribType eTYPE)
{
  
  if ( rktNAME == "compression" ) {
    if ( eTYPE == FX_REAL ) {
      if(floor(nVALUE.dValue) != nVALUE.dValue ||
	 nVALUE.dValue < -1 || nVALUE.dValue > 9) {
	return FX_ATTRIB_WRONG_VALUE;
      }
      setCompression (nVALUE.dValue);
    } else {
      return FX_ATTRIB_WRONG_TYPE;
    }
  } else {
    return TImageIO::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* TImagePng::setAttribute() */


int TImagePng::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "compression" ) {
    rnVALUE.dValue = TImagePng::iCompression;
  } else {
    return TImageIO::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* TImagePng::getAttribute() */


void TImagePng::getAttributeList (TAttributeList& rtLIST) const
{

  TImageIO::getAttributeList (rtLIST);

  rtLIST ["compression"] = FX_REAL;

}  /* TImagePng::getAttributeList() */

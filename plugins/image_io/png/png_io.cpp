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

#if PNG_LIBPNG_VER < 90
/* Compatibility defines for older library versions */
#define png_get_valid(png, infop, var) (infop->valid & var)
#define png_get_rowbytes(png, infop) infop->rowbytes
#endif

DEFINE_IMAGE_IO_PLUGIN ("png", TImagePng);

extern "C" {
#include <png.h>
  
  void error_callback (png_structp ptPng, png_const_charp kcpMsg)
  {

    cerr << kcpMsg << endl;

  }  /* error_callback() */


#if PNG_LIBPNG_VER > 89
  void user_read_data (png_structp ptPng, png_bytep bpData,
                       png_size_t zLength)
#else
  void user_read_data (png_structp ptPng, png_bytep bpData,
                       png_uint_32 zLength)
#endif
  {

    ifstream* ptInput = (ifstream *) png_get_io_ptr (ptPng);
    ptInput->read ((char*)bpData, zLength);

  }  /* user_read_data() */

#if PNG_LIBPNG_VER > 89
  void user_write_data (png_structp ptPng, png_bytep bpData,
                        png_size_t zLength)
#else
  void user_write_data (png_structp ptPng, png_bytep bpData,
                        png_uint_32 zLength)
#endif
  {

    ofstream* ptOutput = (ofstream *) png_get_io_ptr (ptPng);
    ptOutput->write ((char*)bpData, zLength);

  }  /* user_write_data() */

  void user_flush_data(png_structp ptPng)
  {

    ofstream *ptOutput = (ofstream *) png_get_io_ptr (ptPng);
    ptOutput->flush();

  }  /* user_flush_data() */

}


int TImagePng::save (const TImage* pktIMAGE) {
  TColor        tColor;
  TColor        tPixel;
  size_t        zWidth, zHeight;
  ofstream      tOutput;
  png_structp   ptPng;
  png_infop     ptInfo;
  png_bytep     pbRow;
  
  tOutput.open (tFileName.c_str());

  if ( ! tOutput.good() )
  {
    return -1;
  }
  
  ptPng = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL,
                                   error_callback, error_callback);

  if( ! ptPng )
  {
    tOutput.close();
    return -1;
  }
  
  ptInfo = png_create_info_struct (ptPng);
  if( ! ptInfo )
  {
    png_destroy_write_struct (&ptPng, (png_infopp) NULL);
    tOutput.close();
    return -1;
  }

  if ( setjmp (ptPng->jmpbuf) )
  {
    png_destroy_write_struct (&ptPng, &ptInfo);
    tOutput.close();
    return -1;
  }

  png_set_write_fn (ptPng, &tOutput, user_write_data, user_flush_data);
  png_set_compression_level (ptPng, TImagePng::iCompression);

  zWidth  = pktIMAGE->width();
  zHeight = pktIMAGE->height();
  
#if PNG_LIBPNG_VER > 89
  png_set_IHDR (ptPng, ptInfo, zWidth, zHeight, 8, PNG_COLOR_TYPE_RGB,
                PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
                PNG_FILTER_TYPE_DEFAULT);
#else
  ptInfo->width       = zWidth;
  ptInfo->height      = zHeight;
  ptInfo->bit_depth   = 8;
  ptInfo->color_type  = PNG_COLOR_TYPE_RGB;
  ptInfo->compression_type = 0;
  ptInfo->filter_type = 0;
  ptInfo->interlace_type = 0;
  ptInfo->channels = 3;
  ptInfo->pixel_depth = (png_byte)(ptInfo->channels * ptInfo->bit_depth);
#endif

  png_write_info (ptPng, ptInfo);

  pbRow = new png_byte[zWidth * 3];

  for (size_t j = 0; j < zHeight; j++) {
    int row_index = 0;
    for (size_t i = 0; i < zWidth; i++) {
      tPixel = pktIMAGE->getPixel (i, j);
      tPixel.clamp();
      tColor = tPixel.convertTo24Bits();
      pbRow[row_index++] = (Byte) tColor.red();
      pbRow[row_index++] = (Byte) tColor.green();
      pbRow[row_index++] = (Byte) tColor.blue();
    }
    png_write_row (ptPng, pbRow);
  }

  png_write_end (ptPng, ptInfo);
  png_destroy_write_struct (&ptPng, &ptInfo);

  delete pbRow;

  tOutput.close();

  return 0;
  
}  /* TImagePng::save() */


TImage* TImagePng::load (void)
{

  TColor        tColor;
  TImage*       ptImage;
  DWord         dwWidth, dwHeight;
  ifstream      tInput;
  Byte          abHeader[8];
  int           iIsPng;
  Word          wInterlacePasses;
  int           iBitDepth, iColorType, iInterlaceType;
  int           iCompressionType, iFilterType;
  png_structp   ptPng;
  png_infop     ptInfo, ptEndInfo;
  png_bytep     pbRow;
  
  tInput.open(tFileName.c_str());

  if ( ! tInput.good() )
  {
    cerr << "TImagePng::load : Error loading " << tFileName << endl;
    return NULL;
  }
  
  tInput.read ((char*)abHeader, 8);
  //  png_set_sig_bytes_read (8);
  iIsPng = png_check_sig (abHeader, 8);

  if ( ! iIsPng )
  {
    cerr << "TImagePng::load : " << tFileName << " is not a PNG file." << endl;
    tInput.close();
    return NULL;
  }

  ptPng = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL,
                                  error_callback, error_callback);
  if ( ! ptPng )
  {
    cerr << "TImagePng::load : Error loading " << tFileName << endl;
    tInput.close();
    return NULL;
  }

  ptInfo = png_create_info_struct (ptPng);
  if ( ! ptInfo )
  {
    cerr << "TImagePng::load : Error loading " << tFileName << endl;
    png_destroy_read_struct (&ptPng, (png_infopp) NULL, (png_infopp) NULL);
    tInput.close();
    return NULL;
  }

  ptEndInfo = png_create_info_struct (ptPng);
  if ( ! ptEndInfo )
  {
    cerr << "TImagePng::load : Error loading " << tFileName << endl;
    png_destroy_read_struct (&ptPng, &ptInfo, (png_infopp) NULL);
    tInput.close();
    return NULL;
  }

  if ( setjmp (ptPng->jmpbuf) )
  {
    png_destroy_write_struct (&ptPng, &ptInfo);
    tInput.close();
    return NULL;
  }

#if PNG_LIBPNG_VER > 89
  png_set_read_fn (ptPng, &tInput, user_read_data);

  png_set_sig_bytes (ptPng, 8);
#else
  // We need to close the file and reopen so that the library is 
  // at the beginning of the file.
  tInput.close();
  tInput.open(tFileName.c_str());
  if ( ! tInput.good() )
  {
    cerr << "TImagePng::load : Error loading " << tFileName << endl;
    return NULL;
  }
      
  png_set_read_fn (ptPng, &tInput, user_read_data);
#endif  
  png_read_info (ptPng, ptInfo);
  
#if PNG_LIBPNG_VER > 89
  png_get_IHDR (ptPng, ptInfo, &dwWidth, &dwHeight, &iBitDepth, &iColorType,
                &iInterlaceType, &iCompressionType, &iFilterType);
#else
  dwWidth    = ptInfo->width;
  dwHeight   = ptInfo->height;
  iBitDepth  = ptInfo->bit_depth;
  iColorType = ptInfo->color_type;
  iInterlaceType = ptInfo->interlace_type;
  iCompressionType = ptInfo->compression_type;
  iFilterType = ptInfo->filter_type;
#endif

  ptImage = new TImage(dwWidth, dwHeight);
  
  if ( iColorType == PNG_COLOR_TYPE_PALETTE && iBitDepth <= 8 )
  {
    png_set_expand (ptPng);
  }
  
  if ( iColorType == PNG_COLOR_TYPE_GRAY && iBitDepth < 8 )
  {
    png_set_expand (ptPng);
  }
  
  if ( png_get_valid(ptPng, ptInfo, PNG_INFO_tRNS) )
  {
    png_set_expand (ptPng);
  }

  if ( iBitDepth == 16 )
  {
    png_set_strip_16 (ptPng);
  }

  if (iColorType & PNG_COLOR_MASK_ALPHA)
  {
#if PNG_LIBPNG_VER > 89
    png_set_strip_alpha (ptPng);
#else
    cerr << "TImagePng::load : Error loading " << tFileName << 
      " alpha channel not supported" << endl;
    png_destroy_read_struct (&ptPng, &ptInfo, (png_infopp) NULL);
    tInput.close();
    return NULL;
#endif
  }
  
  png_set_packing (ptPng);

  wInterlacePasses = png_set_interlace_handling (ptPng);
  
  png_read_update_info (ptPng, ptInfo);
  
  pbRow = new png_byte[png_get_rowbytes (ptPng, ptInfo)];

  for (Word wPass = 0; wPass < wInterlacePasses; wPass++)
  {
    for (DWord dwRow = 0; dwRow < dwHeight; dwRow++)
    {
      png_read_row (ptPng, pbRow, NULL);
      for (Word wRowIndex = 0; wRowIndex < dwWidth; wRowIndex++)
      {
        tColor.setRed (pbRow[3 * wRowIndex]);
        tColor.setGreen (pbRow[3 * wRowIndex + 1]);
        tColor.setBlue (pbRow[3 * wRowIndex + 2]);
        tColor = tColor.convertFrom24Bits();
        ptImage->setPixel (wRowIndex, dwRow, tColor);
      }
    }
  }
  
  delete pbRow;
  
  png_read_end (ptPng, ptInfo);

  png_destroy_read_struct (&ptPng, &ptInfo, (png_infopp) NULL);
  
  tInput.close();

  return ptImage;
  
}  /* TImagePng::load() */


int TImagePng::setAttribute (const string& rktNAME, NAttribute nVALUE,
			     EAttribType eTYPE)
{
  
  if ( rktNAME == "compression" )
  {
    if ( eTYPE == FX_REAL )
    {
      if( floor(nVALUE.dValue) != nVALUE.dValue ||
          nVALUE.dValue < -1 || nVALUE.dValue > 9 )
      {
	return FX_ATTRIB_WRONG_VALUE;
      }
      setCompression (int(nVALUE.dValue));
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

}  /* TImagePng::setAttribute() */


int TImagePng::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "compression" )
  {
    rnVALUE.dValue = TImagePng::iCompression;
  }
  else
  {
    return TImageIO::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* TImagePng::getAttribute() */


void TImagePng::getAttributeList (TAttributeList& rtLIST) const
{

  TImageIO::getAttributeList (rtLIST);

  rtLIST ["compression"] = FX_REAL;

}  /* TImagePng::getAttributeList() */

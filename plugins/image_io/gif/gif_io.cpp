/*
 *  Copyright (C) 1999, 2000 Jon Frydensbjerg
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
#include <cstdio>
#include "hlapi/image_manager.h"
#include "gif_io.h"

DEFINE_IMAGE_IO_PLUGIN ("gif", TImageGif);

extern "C" {
/* NB: Configure libungif without X Windows support! */
#include <gif_lib.h> 
}

/* Start line for deinterlacing */
static Byte _abInterlaceStart[4] = {0, 4, 2, 1};
/* Rate at which we accelerate vertically when deinterlacing */
static Byte _abInterlaceRate [4] = {8, 8, 4, 2};


int TImageGif::save (const TImage* pktIMAGE) {

  TColor           tColor;
  TColor           tPixel;
  size_t           zWidth, zHeight;
  GifFileType*     ptOutput;
  GifByteType*     ptRed;
  GifByteType*     ptTempRed;
  GifByteType*     ptGreen;
  GifByteType*     ptTempGreen;
  GifByteType*     ptBlue;
  GifByteType*     ptTempBlue;
  GifByteType*     ptOutputImage;
  GifColorType     atOutputColorMap[256];
  ColorMapObject*  ptOutputMapObject;
  int              iMapSize;
  Byte             iBPP;
  int              iErrorCode;
  
  ptOutput = EGifOpenFileName((char *) tFileName.c_str(), FALSE);

  if ( !ptOutput )
  {
    return -1;
  }
  
  zWidth  = pktIMAGE->width();
  zHeight = pktIMAGE->height();

  ptRed         = (GifByteType *) malloc (zWidth * zHeight);
  ptGreen       = (GifByteType *) malloc (zWidth * zHeight);
  ptBlue        = (GifByteType *) malloc (zWidth * zHeight);
  ptOutputImage = (GifByteType *) malloc (zWidth * zHeight);

  ptTempRed     = ptRed;
  ptTempGreen   = ptGreen;
  ptTempBlue    = ptBlue;
  
  for (size_t J = 0; (J < zHeight) ;J++) {
    for (size_t I = 0; (I < zWidth) ;I++) {
      tPixel = pktIMAGE->getPixel (I, J);
      tPixel.clamp();
      tColor = tPixel.convertTo24Bits();

      *(ptTempRed++)   = (GifByteType) tColor.red();
      *(ptTempGreen++) = (GifByteType) tColor.green();
      *(ptTempBlue++)  = (GifByteType) tColor.blue();
    }
  }

  iMapSize = 256;

  QuantizeBuffer (zWidth, zHeight, &iMapSize, ptRed, ptGreen, ptBlue, ptOutputImage, atOutputColorMap);

  /* Calculate no. bits necessary to code image */
  if ( iMapSize == 1 )
  {
    iBPP = 1;
  }
  else
  {
    iBPP = (Byte) ceil (log (iMapSize) / log (2));
  }

  ptOutputMapObject = MakeMapObject (1 << iBPP, atOutputColorMap);  

  iErrorCode = EGifPutScreenDesc (ptOutput, zWidth, zHeight, ptOutputMapObject->BitsPerPixel, ptOutput->SBackGroundColor, ptOutputMapObject);
  if ( iErrorCode == GIF_ERROR )
  { 
    cerr << "TImageGif::save : Error saving " << tFileName << endl;
    return -1;
  }

  iErrorCode = EGifPutImageDesc (ptOutput, 0, 0, zWidth, zHeight, FALSE, ptOutputMapObject);
  if ( iErrorCode == GIF_ERROR )
  { 
    cerr << "TImageGif::save : Error saving " << tFileName << endl;
    return -1;
  }
 
  iErrorCode = EGifPutLine (ptOutput, ptOutputImage, (zWidth * zHeight));
  if ( iErrorCode == GIF_ERROR )
  { 
    cerr << "TImageGif::save : Error saving " << tFileName << endl;
    return -1;
  }

  EGifCloseFile (ptOutput);

  FreeMapObject (ptOutputMapObject);

  free (ptRed);
  free (ptGreen);
  free (ptBlue);
  free (ptOutputImage);

  cout << "Warning: No image compression performed - LZW algorithm is patented by UniSys." << endl;

  return 0;
  
}  /* TImageGif::save() */


TImage* TImageGif::load (void)
{

  TColor         tColor;
  TImage*        ptImage;
  size_t         zWidth, zHeight;
  GifFileType*   ptInput;
  GifPixelType*  ptDecodedImage;
  GifColorType   tRGBValue;
  GifColorType*  ptColors;  
  int            iInterlace;
  Word*          awDeinterlaceTable;
  Word           wCurrentLine;  

  ptInput = DGifOpenFileName (tFileName.c_str());
  
  if ( !ptInput )
  {
    cerr << "TImageGif::load : Error loading " << tFileName << endl;
    return NULL;
  }
  
  if ( DGifSlurp (ptInput) == GIF_ERROR )
  { 
    cerr << "TImageGif::load : Error loading " << tFileName << endl;
    return NULL;
  }

  ptColors = ptInput->SColorMap->Colors;

  ptDecodedImage = (GifPixelType *) ptInput->SavedImages->RasterBits;

  iInterlace = ptInput->SavedImages->ImageDesc.Interlace;

  zWidth  = ptInput->SWidth;
  zHeight = ptInput->SHeight;
  
  awDeinterlaceTable = (Word *) malloc (zHeight * sizeof(Word));

  if ( iInterlace ) 
  {

    for (Word I = 0, N = 0; (I < 4) ;I++)
    {
      for (Word J = _abInterlaceStart[I]; (J < zHeight) ;(J += _abInterlaceRate[I]))
      {
        awDeinterlaceTable[N++] = J;
      }
    }
  }
  else
  {
    for (Word I = 0; (I < zHeight) ;I++)
    {
      awDeinterlaceTable[I] = I;
    }
  }

  ptImage = new TImage (zWidth, zHeight);

  for (Word I = 0; (I < zHeight) ;I++)
  {
    wCurrentLine = awDeinterlaceTable[I];

    for (Word J = 0; (J < zWidth) ;J++)
    { 
      tRGBValue = ptColors[ *(ptDecodedImage++) ];

      tColor.setRed   (tRGBValue.Red);
      tColor.setGreen (tRGBValue.Green);
      tColor.setBlue  (tRGBValue.Blue);
      tColor = tColor.convertFrom24Bits();
      ptImage->setPixel (J, wCurrentLine, tColor);
    }
  }
  
  DGifCloseFile (ptInput);

  free (awDeinterlaceTable);

  return ptImage;
  
}  /* TImageGif::load() */






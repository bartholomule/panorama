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

#include <fstream.h>
#include "tga_io.h"
#include "hlapi/image_manager.h"

DEFINE_IMAGE_IO_PLUGIN ("tga", TImageTga);

int TImageTga::save (const TImage* pktIMAGE)
{

  TColor     tColor;
  TColor     tPixel;
  ofstream   sFile;
  size_t     zWidth  = pktIMAGE->width();
  size_t     zHeight = pktIMAGE->height();
  Byte*      pbRow   = new Byte [zWidth * 3];

  sFile.open (tFileName.c_str(), ios::bin | ios::out);

  sFile << (Byte) 0;                         // Lenght of identifier string
  sFile << (Byte) 0;                         // Color map type (0 = no color map)
  sFile << (Byte) 2;                         // Image type (2 = RGB)
  sFile << (Byte) 0;                         // First color map entry (LSB)
  sFile << (Byte) 0;                         //   "     "    "    "   (MSB)
  sFile << (Byte) 0;                         // Entries in color map (LSB)
  sFile << (Byte) 0;                         //    "     "   "    "  (MSB)
  sFile << (Byte) 0;                         // Size of color map entry
  sFile << (Byte) 0;                         // X origin of image (LSB)
  sFile << (Byte) 0;                         // "    "    "   "   (MSB)
  sFile << (Byte) 0;                         // Y origin of image (LSB)
  sFile << (Byte) 0;                         // "    "    "   "   (MSB)
  sFile << (Byte) (zWidth % 256);
  sFile << (Byte) (zWidth / 256);
  sFile << (Byte) (zHeight % 256);
  sFile << (Byte) (zHeight / 256);
  sFile << (Byte) 24;                        // Pixel size (24 bits)
  sFile << (Byte) 32;                        // Attributes (32 = origin in upper left)

  for (size_t J = 0; ( J < zHeight ) ;J++)
  {
    for (size_t I = 0; ( I < zWidth ) ;I++)
    {
      tPixel = pktIMAGE->getPixel (I, J);
      tPixel.clamp();
      tColor = tPixel.convertTo24Bits();

      pbRow [I * 3]     = (Byte) tColor.blue();
      pbRow [I * 3 + 1] = (Byte) tColor.green();
      pbRow [I * 3 + 2] = (Byte) tColor.red();
    }
    sFile.write (pbRow, zWidth * 3);
  }

  sFile.close();

  delete[] pbRow;
  
  return 0;
  
}  /* save() */


TImage* TImageTga::load (void)
{

  ifstream   sFile;
  Byte       bRed, bGreen, bBlue;
  Byte       bAux;
  TColor     tColor;
  TImage*    ptImage;
  size_t     zWidth, zHeight;

  sFile.open (tFileName.c_str(), ios::in | ios::nocreate | ios::bin);

  if ( ! sFile )
  {
    return NULL;
  }
  
  bAux = sFile.get();                             // Lenght of identifier string
  bAux = sFile.get();                             // Color map type (0 = no color map)
  bAux = sFile.get();                             // Image type (2 = RGB)
  bAux = sFile.get();                             // First color map entry
  bAux = sFile.get();
  bAux = sFile.get();                             // Entries in color map
  bAux = sFile.get();
  bAux = sFile.get();                             // Size of color map entry
  bAux = sFile.get();                             // X origin of image
  bAux = sFile.get();
  bAux = sFile.get();                             // Y origin of image
  bAux = sFile.get();

  bAux = sFile.get();
  zWidth = bAux;
  bAux = sFile.get();
  zWidth += (Word (bAux) * 256);

  bAux = sFile.get();
  zHeight = bAux;
  bAux = sFile.get();
  zHeight += (Word (bAux) * 256);

  bAux = sFile.get();                             // Pixel size (24 bits)
  bAux = sFile.get();                             // Attributes (32 = origin in upper left)

  ptImage = new TImage (zWidth, zHeight);

  for (size_t J = 0; ( J < zHeight ) ;J++)
  {
    for (size_t I = 0; ( I < zWidth ) ;I++)
    {
      bBlue  = sFile.get();
      bGreen = sFile.get();
      bRed   = sFile.get();
      tColor = TColor (bRed, bGreen, bBlue);
      tColor = tColor.convertFrom24Bits();
      ptImage->setPixel (I, J, tColor);
    }
  }

  sFile.close();

  return ptImage;
  
}  /* load() */

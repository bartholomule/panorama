/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  Copyright (C) 1999 Jon Frydensbjerg
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

#include <fstream>
#include "hlapi/image_manager.h"
#include "tga_io.h"

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

  sFile << (Byte) 0;                         // Length of identifier string
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
  sFile << (Byte) 0;                         // Attributes (0 = origin in lower left)

  for (int J = (zHeight - 1) ; ( J >= 0 ) ;J--)
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
  size_t     zWidth, zHeight, zCountColors, zTotalNoPixels;
  Byte       bIndentifierLength;
  Byte       bColorMapType;
  Byte       bSizeofMapEntry;
  Byte       bImageType;
  Byte       bAttributes;
  Byte       bPixelSize;
  int        iStart, iStop, iAdd;

  sFile.open (tFileName.c_str(), ios::in | ios::nocreate | ios::bin);

  if ( ! sFile )
  {
    return NULL;
  }
  
  bAux = sFile.get();                             // Length of identifier string
  bIndentifierLength = bAux;

  bAux = sFile.get();                             // Color map type (0 = no color map)
  bColorMapType = bAux;

  bAux = sFile.get();                             // Image type
  bImageType = bAux;

  if ( ( bImageType != 2 ) && ( bImageType != 10 ) )
  {
    cerr << "TImageTga::load : Unsupported image type. Error loading " << tFileName << endl;
    return NULL;    
  }

  bAux = sFile.get();                             // First color map entry
  bAux = sFile.get();

  bAux = sFile.get();                             // Entries in color map
  zCountColors = bAux;
  bAux = sFile.get();
  zCountColors += (Word (bAux) * 256);

  bAux = sFile.get();                             // Size of color map entry
  bSizeofMapEntry = bAux;

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

  bAux = sFile.get();                             // Pixel size 
  bPixelSize = bAux;

  if ( ( bPixelSize != 16 ) && ( bPixelSize != 24 ) && ( bPixelSize != 32 ) )
  {
    cerr << "TImageTga::load : Unsupported pixel size. Error loading " << tFileName << endl;
    return NULL;    
  }

  bAux = sFile.get();                             // Attributes 
  bAttributes = bAux;

  sFile.seekg(sFile.tellg() + bIndentifierLength);
  
  if ( bColorMapType )                            // Ignore color map
  {
    sFile.seekg (sFile.tellg() + (bSizeofMapEntry / 8) * zCountColors);
  }

  if ( ( bAttributes & 0x20 ) )                   // Check origin (upper or lower left)
  {
    iStart = 0;
    iStop  = zHeight;
    iAdd   = 1;
  }
  else 
  {
    iStart = (zHeight - 1); 
    iStop  = -1; 
    iAdd   = -1;
  } 

  ptImage = new TImage (zWidth, zHeight);

  bRed   = 0;
  bGreen = 0;
  bBlue  = 0;

  if ( bImageType == 2 )                          // Uncompressed      
  {
    for (int J = iStart; ( J != iStop ) ; (J += iAdd) )
    {
      for (size_t I = 0; ( I < zWidth ) ;I++)
      {
        grabRGB (bPixelSize, sFile, bRed, bGreen, bBlue); 

        tColor = TColor (bRed, bGreen, bBlue);
        tColor = tColor.convertFrom24Bits();
        ptImage->setPixel (I, J, tColor);
      }
    }
  }
  else                                            // Runlength encoded
  {
    zTotalNoPixels = ( zWidth * zHeight );
 
    int    J = iStart;
    size_t I = 0;
    
    Byte   N = 0;

    while ( zTotalNoPixels )
    {
      bAux = sFile.get();

      N = ( (bAux & 0x7f) + 1 );

      if ( bAux & 0x80 )
      {
        grabRGB (bPixelSize, sFile, bRed, bGreen, bBlue); 

        tColor = TColor (bRed, bGreen, bBlue);
        tColor = tColor.convertFrom24Bits();

        for (Byte M = 0; ( M < N ) ;M++)
        {
          ptImage->setPixel (I, J, tColor);

          I++;
          zTotalNoPixels--;

          if ( I == zWidth ) 
          {
            I  = 0;
            J += iAdd;
          }
        }                
      }
      else
      {
        for (Byte M = 0; ( M < N ) ;M++)
        {
          grabRGB (bPixelSize, sFile, bRed, bGreen, bBlue); 

          tColor = TColor (bRed, bGreen, bBlue);
          tColor = tColor.convertFrom24Bits();
          ptImage->setPixel (I, J, tColor);

          I++;
          zTotalNoPixels--;

          if ( I == zWidth ) 
          {
            I  = 0;
            J += iAdd;
          }
        }                
      }
    }
  }
  
  sFile.close();

  return ptImage;
  
}  /* load() */


void TImageTga::grabRGB (Byte bPixelSize, ifstream &sTGAStream, Byte& bRed, Byte& bGreen, Byte& bBlue) 
{
  Byte bAux;
 
  switch ( bPixelSize ) {
    case ( 16 ) : 
      bAux    = sTGAStream.get();
      bBlue   = bAux & 0x1f;
      bGreen  = bAux >> 5;

      bAux    = sTGAStream.get();
      bGreen |= ( bAux & 0x3  ) << 3;
      bRed    = ( bAux & 0x7c ) >> 2;
 
      bBlue   = (bBlue  * 255) / 31;
      bGreen  = (bGreen * 255) / 31;
      bRed    = (bRed   * 255) / 31;
      break;

    case ( 32 ) :  
      bBlue   = sTGAStream.get();
      bGreen  = sTGAStream.get();
      bRed    = sTGAStream.get();
      sTGAStream.get(); 
      break;

    default:                                      // default: 24 bit
      bBlue   = sTGAStream.get();
      bGreen  = sTGAStream.get();
      bRed    = sTGAStream.get();
  }
}  /* grabRGB() */




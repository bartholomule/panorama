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

#include <fstream>
#include "hlapi/image_manager.h"
#include "tiff_io.h"
#include <tiffio.h>
#include <tiffconf.h>
#include <time.h>

DEFINE_IMAGE_IO_PLUGIN ("tiff", TImageTiff);


/*
  Write a TIFF image from the given raster data.
  The libtiff library does not have a nice, clean interface for doing this, so
  I am stuck writing all of the nasty fields manually.
 */
int TImageTiff::save (const TImage* pktIMAGE) {
  TColor        tColor;
  TColor        tPixel;
  size_t        zWidth, zHeight;
  zWidth  = pktIMAGE->width();
  zHeight = pktIMAGE->height();

  // Attempt to open the file for writing...
  TIFF* tif = TIFFOpen(tFileName.c_str(),"w");

  // Make sure it opened, and the library is OK.
  if(!tif)
  {
    return (-1);
  }

  // Set Width & Height
  TIFFSetField(tif, TIFFTAG_IMAGEWIDTH,  (uint32)zWidth);
  TIFFSetField(tif, TIFFTAG_IMAGELENGTH, (uint32)zHeight);
  TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
  
  // Set BPS,SPP (24 bit image)
  TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 3);
  TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE,   8);

  // Set other required fields: standard planar order (RGBRGBRGB..., not
  // RRRR...GGGG...BBBB...)
  TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
  TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

  // If compression was requested, use the best compression supported by the
  // system (and by what I could figure out without library documentation).
  if(compression)
  {
#if defined(LZW_SUPPORT)
		 // #warning "Using LZW compresion when compression is requested"
    cerr << "TiffIO:Warning:LZW comressed TIFF images may not be useable with"
	 << endl
	 << "  some installations of panorama." << endl;
    
    TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_LZW);
    
#elif defined(PACKBITS_SUPPORT)
    TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_PACKBITS);
#else
    
    cerr << "TiffIO:Warning:Compression was requested, but not supported by your tifflib." << endl;
    TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
#endif /* compression type support */
  }
  else /* no compression for write */
  {
    TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE);    
  }
  
  unsigned rowsperstrip = 8192 / (3 * zWidth);
  TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, rowsperstrip);

  // Stick a time flag in the file...
  time_t cur_time = time(NULL);
  char time_buffer[22];
  // It must be in the format YYYY:MM:DD HH:MM:SS
  strftime(time_buffer,21,"%Y:%m:%d %H:%M:%S",localtime(&cur_time));
  TIFFSetField(tif, TIFFTAG_DATETIME, (void*)time_buffer);

  // Stick a software tag in the file.
  TIFFSetField(tif, TIFFTAG_SOFTWARE, (void*)string(string("Panorama TIFF output plugin (c)2001 Kevin Harris\r\n") + string(TIFFGetVersion())).c_str());  

  // Get the strip size, and make sure it is what it should be (if the above
  // tags were entered correctly).
  unsigned strip_size = TIFFStripSize(tif);
  if(strip_size != (3 * rowsperstrip * zWidth))
  {
    cerr << "Tiff reports strip as " << strip_size
	 << " bytes instead of expected " << 3 * zWidth * rowsperstrip
	 << " bytes." << endl;
    TIFFClose(tif);        
    return(-1);
  }
  // Preallocation/calculation for conversion...
  unsigned char* strip_data = new unsigned char[strip_size];
  unsigned num_strips = zHeight / rowsperstrip;
  unsigned extra_rows = zHeight - (num_strips * rowsperstrip);

  // Variable to save some calculation...
  unsigned y = 0;

  // Write all of the entire strips...
  for(unsigned strip = 0; strip < num_strips; ++strip)
  {
    // Copy the data from all of the rows within a strip into the strip buffer.
    int strip_data_index = 0;
    for(unsigned strip_row = 0; strip_row < rowsperstrip; ++strip_row)
    {
      for (size_t x = 0; x < zWidth; x++)
      {
	tPixel = pktIMAGE->getPixel (x, y);
	tPixel.clamp();
	tColor = tPixel.convertTo24Bits();
	strip_data[strip_data_index++] = (Byte) tColor.red();
	strip_data[strip_data_index++] = (Byte) tColor.green();
	strip_data[strip_data_index++] = (Byte) tColor.blue();
      }
      ++y;
    }
    // Encode/Write the strip.  This was found from reading the headers, not
    // the documentation.  The documentation suggests using TiffWriteScanline,
    // which is, apparently, not supported by the library when using
    // compression. 
    if(TIFFWriteEncodedStrip(tif, strip, (void*)strip_data, strip_size) < 0)    
    {
      cerr << "TiffIO:Error writing strip " << strip << endl;
      delete[] strip_data;
      TIFFClose(tif);          
      return (-1);
    }
  }
  // Write the partial strips...
  if(extra_rows > 0)
  {
    unsigned strip = num_strips;
    int strip_data_index = 0;
    
    // This loop is the same as the above, with the upper bound changed (less
    // data to copy).
    for(unsigned strip_row = 0; strip_row < extra_rows; ++strip_row)
    {
      for (size_t x = 0; x < zWidth; x++)
      {
	tPixel = pktIMAGE->getPixel (x, y);
	tPixel.clamp();
	tColor = tPixel.convertTo24Bits();
	strip_data[strip_data_index++] = (Byte) tColor.red();
	strip_data[strip_data_index++] = (Byte) tColor.green();
	strip_data[strip_data_index++] = (Byte) tColor.blue();
      }
      ++y;
    }
    if(TIFFWriteEncodedStrip(tif, strip, (void*)strip_data,
			     extra_rows * zWidth * 3) < 0)
    {
      cerr << "TiffIO:Error writing partial strip " << strip << endl;
      delete[] strip_data;
      TIFFClose(tif);          
      return (-1);      
    }    
  }
  if(y != zHeight)
  {
    cerr << "TiffIO:Math error... y (" << y
	 << ") != zHeight (" << zHeight << ")" << endl;
    delete[] strip_data;
    TIFFClose(tif);    
    return (-1);    
  }

  delete[] strip_data;

  TIFFClose(tif);

  return 0;
  
}  /* TImageTiff::save() */


/*
  Load a TIFF image.  This one is MUCH simpler than the corresponding save,
  because libtiff has an abstraction layer for loading rgb images (the work has
  to be done for saving them).  The basic outline for thie was taken from the
  libtiff documentation.
*/
TImage* TImageTiff::load (void)
{

  TColor        tColor;
  TImage*       ptImage = NULL;

  TIFF* tif = TIFFOpen(tFileName.c_str(),"r");
  
  if ( !tif )
  {
    cerr << "TImageTiff::load : Error loading " << tFileName << endl;
    return NULL;
  }

  TIFFRGBAImage img;
  char emsg[1024];
  if (TIFFRGBAImageBegin(&img, tif, 0, emsg))
  {
    size_t npixels;
    uint32* raster;
    npixels = img.width * img.height;
    raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));
    if (raster != NULL)
    {
      if (TIFFRGBAImageGet(&img, raster, img.width, img.height))
      {
	//...process raster data...
	ptImage = new TImage(img.width, img.height);
	
	for(unsigned y = 0; y < img.height; ++y)
	{
	  unsigned y_off = y * img.width;
	  for(unsigned x = 0; x < img.width; ++x)
	  {
	    unsigned x_off = x * 3;
	    tColor.setRed  (raster[y_off + x_off + 0]);
	    tColor.setGreen(raster[y_off + x_off + 1]);
	    tColor.setBlue (raster[y_off + x_off + 2]);
	    ptImage->setPixel(x,y, tColor.convertFrom24Bits());
	  }
	}	
      }
      else
      {
	cerr << "TImageTiff::load : Error loading " << tFileName
	     << " (RGBAImageGet failed)"
	     << endl;  
      }      
      _TIFFfree(raster);
    }
    else
    {
      cerr << "TImageTiff::load : Error loading " << tFileName
	   << " (out of memory?)"
	   << endl;    
    }    
    TIFFRGBAImageEnd(&img);
  }
  else
  {
    cerr << "TImageTiff::load : Error loading " << tFileName
	 << " (" << emsg << ")"
	 << endl;
  }
  TIFFClose(tif);
  
  return ptImage;
  
}  /* TImageTiff::load() */


int TImageTiff::setAttribute (const string& rktNAME, NAttribute nVALUE,
			     EAttribType eTYPE)
{
  
  if ( rktNAME == "compression" )
  {
    if ( eTYPE == FX_BOOL )
    {
      setCompression (nVALUE.gValue);
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

}  /* TImageTiff::setAttribute() */


int TImageTiff::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "compression" )
  {
    rnVALUE.gValue = compression;
  }
  else
  {
    return TImageIO::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* TImageTiff::getAttribute() */


void TImageTiff::getAttributeList (TAttributeList& rtLIST) const
{

  TImageIO::getAttributeList (rtLIST);

  rtLIST ["compression"] = FX_BOOL;

}  /* TImageTiff::getAttributeList() */

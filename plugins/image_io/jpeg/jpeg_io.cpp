/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  Copyright (C) 1999 Jose Antonio Robles Ordoñez
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



#include <cstdio> // for FILE access
#include "hlapi/image_manager.h"
#include "llapi/attribute.h"
#include <setjmp.h>

extern "C" {
#include <jpeglib.h> //jpeg library
}
#include "jpeg_io.h"

DEFINE_IMAGE_IO_PLUGIN_WITH_ALIAS ("jpeg", "jpg", TImageJpeg);

/*
  NOTES:
  This file has bee modified (07Aug2001 -- KH) to have the load/store functions
  actually return to their callers on the event of failure.  The method used
  was taken from The Gimp's jpeg plugin (I borrowed a few lines of code,
  including one complete function [my_error_exit]).

  I have never used setjmp, as I always feared horrible interactions with C++
  destructors.  This is very possible, but SHOULD NOT happen in this file, as
  the control returns back into the same function, with NO variables declared
  after the call to setjmp (If you modify it, place all variable declarations
  BEFORE the call to setjmp, failure to do so could cause memory leaks and/or
  worse problems).  Depending on the C++ implementation, they could potentially
  cause problems with exception handling (a theory, but maybe someone can
  [dis]prove it).  Threads may also cause problems.

  Personally, I consider a call to setjmp/longjmp to be almost as evil as a
  goto (slightly better), but there is no other method that I am aware of for
  returning control to a function when a function it calls will not return to
  it (only to an error routine).

  I guess that I have put enough verbage about the evils of setjmp in here, so
  I'll just put one more statement: BE CAREFUL!
 */

/*
  This struct was taken from Gimp's jpeg plugin.
 */
struct my_error_mgr
{
  struct jpeg_error_mgr pub;            /* "public" fields */

  jmp_buf               setjmp_buffer;  /* for return to caller */
};


/*
  This function was taken from Gimp's jpeg plugin.
 */
static void my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_mgr* myerr = (my_error_mgr*) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp (myerr->setjmp_buffer, 1);
}

// This function is here to avoid any output from the jpeg library (warnings
// and/or errors).  It is being used (below) instead of the standard.
static void silent_output (j_common_ptr cinfo)
{
  /* NOTHING: BE QUIET! */
}


int TImageJpeg::save (const TImage* pktIMAGE)
{

  FILE*                          tOutFile;
  struct jpeg_compress_struct    sComp;
  my_error_mgr                   jerr;    
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
    fclose (tOutFile);
    
    return -1;
  }

  /* Set the standard error routine and some other parameters */
  
  sComp.err = jpeg_std_error (&jerr.pub);
  jerr.pub.error_exit = &my_error_exit;
  
  if( bSilent )
  {
    jerr.pub.output_message = &silent_output;
  }


  /* Establish the setjmp return context for my_error_exit to use. */
  if (setjmp (jerr.setjmp_buffer))
  {
    /*
      If we get here, the JPEG code has signaled an error.  We need to clean up
      anything that was allocated or opened before returning an error.
      Note that the data which has not been allocated yet (ie. the compress
      buffer) still needs to be freed.
     */
    jpeg_destroy_compress (&sComp);
    fclose (tOutFile);
    delete[] pbScanline;

    if( !bSilent )
    {
      cerr << "TImageJpeg::save : error saving file " << tFileName << endl;
    }
    return -1;
  }  

  
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
  struct jpeg_decompress_struct  sDecomp;
  my_error_mgr                   jerr;  
  size_t                         zWidth, zHeight;
  TColor                         tColor;
  TImage*                        ptImage = NULL;
  Byte*                          pbScanline = NULL;
   
  tInputFile = fopen (tFileName.c_str(),"r");

  if ( !tInputFile )
  {
    return NULL;
  }

  sDecomp.err = jpeg_std_error (&jerr.pub);  
  jerr.pub.error_exit = &my_error_exit;
  if( bSilent )
  {
    jerr.pub.output_message = &silent_output;
  }

  /* Establish the setjmp return context for my_error_exit to use. */
  if (setjmp (jerr.setjmp_buffer))
  {
    /* If we get here, the JPEG code has signaled an error.
     * We need to clean up the JPEG object, close the input file, and return.
     * As well as delete any memory which was dynamically allocated before the
     * error was flagged (thus transfering control here).
     */
    jpeg_destroy_decompress (&sDecomp);
    
    fclose (tInputFile);
    
    if ( ptImage )
    {
      delete ptImage;
    }
    if ( pbScanline )
    {
      delete[] pbScanline;
    }    

    if( !bSilent )
    {
      cerr << "TImageJpeg::load : " << tFileName << " is not a jpeg file." << endl;
    }
    
    return NULL;
  }
  
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
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      fQuality = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      fQuality = r->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "smoothing" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      fSmoothing = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      fSmoothing = r->tValue;
    }
#endif
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

#if !defined(NEW_ATTRIBUTES)
  if ( rktNAME == "quality" )
  {
    rnVALUE.dValue = fQuality;
  }
  else if ( rktNAME == "smoothing" )
  {
    rnVALUE.dValue = fSmoothing;
  }
#else
  if ( rktNAME == "quality" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (fQuality);
  }
  else if ( rktNAME == "smoothing" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (fSmoothing);
  }  
#endif
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

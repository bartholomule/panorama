/*
*  Copyright (C) 2000 Jon Frydensbjerg
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

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "llapi/file.h"
#include "hlapi/image_manager.h"
#include "pat_texture.h"

DEFINE_PLUGIN ("PatternTexture", FX_PATTERN_CLASS, TPatternTexture);


int TPatternTexture::correctTexel (int iVALUE, const size_t& rkzMAX) const
{

  return ( iVALUE < 0 ) ? -iVALUE : (rkzMAX - iVALUE);

}  /* correctTexel() */


TColor TPatternTexture::lerpTexel (TScalar ut, TScalar vt) const
{
 
  TColor   tColor;
  int      iu, iv;
  float    uv, iuv, uiv, iuiv;
  float    tmu, tmv;
  double   iiu, iiv;
  double   fu, fv;
  
  // width/2 and height/2
  tmu = ut * (double) zTextureWidth;
  tmv = vt * (double) zTextureHeight;

  fu = modf (tmu, &iiu);
  fv = modf (tmv, &iiv);

  uv   = fu * fv;
  iuv  = (1.0 - fu) * fv;
  uiv  = fu * (1.0 - fv);
  iuiv = (1.0 - fu) * (1.0 - fv);

  // values in u and v
  iu = (int) iiu;
  iv = (int) iiv;

  tColor  = ptImage->getPixel (correctTexel (iu    , zTextureWidth), 
			       correctTexel (iv    , zTextureHeight)) * iuiv;
  tColor += ptImage->getPixel (correctTexel (iu + 1, zTextureWidth), 
			       correctTexel (iv    , zTextureHeight)) * uiv;
  tColor += ptImage->getPixel (correctTexel (iu    , zTextureWidth),
			       correctTexel (iv + 1, zTextureHeight)) * iuv;
  tColor += ptImage->getPixel (correctTexel (iu + 1, zTextureWidth), 
			       correctTexel (iv + 1, zTextureHeight)) * uv;

  return tColor;

}  /* lerpTexel() */


void TPatternTexture::sphericalMap (const TVector& rktPOINT, TScalar& rtTHETA, TScalar& rtPHI) const
{
  
  TVector   tVector;
  TScalar   x, y, z;
  TScalar   len;

  tVector = rktPOINT;
  tVector.normalize();

  x = tVector.x();
  y = tVector.y();
  z = tVector.z();
  
  rtPHI = 0.5 + asin (y) / PI;

  len = sqrt (x * x + z * z);

  if ( len < FX_EPSILON )
  {
    rtTHETA = 0.0;
  }
  else
  {
    if ( fabs (z) < FX_EPSILON )
    {
      if ( x > 0 )
      {
	rtTHETA = 0.0;
      }
      else
      {
	rtTHETA = PI;
      }
    }
    else
    {
      rtTHETA = acos (x / len);

      if ( z < 0.0 )
      {
	rtTHETA = (PI * 2) - rtTHETA;
      }
    }

    rtTHETA /= (PI * 2);
  }
  
}  /* sphericalMap() */


TColor TPatternTexture::pattern (const TSurfaceData& rktDATA) const
{

  TColor   tColor;
  TVector  tPoint;
  TScalar  u, v;
  
  if ( !ptImage )
  {
    cerr << "Error: texture must be set" << endl;
    exit (1);
  }

  tPoint = rktDATA.localPoint();

  sphericalMap (tPoint, u, v);

  tColor = lerpTexel (u, v);
    
  return tColor;

}  /* pattern() */


int TPatternTexture::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "texture" )
  {
    if ( eTYPE == FX_STRING )
    {
      char*   pcName = (char*) nVALUE.pvValue;
        
      ptImage = tImageManager.newImage (pcName, FileExtension (pcName));

      if ( !ptImage )
      {
        TProcedural::_tUserErrorMessage = string ("could not open texture file ") + (char*) nVALUE.pvValue;
        return FX_ATTRIB_USER_ERROR;
      }

      zTextureWidth  = ptImage->width();
      zTextureHeight = ptImage->height();
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TPattern::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TPatternTexture::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "texture" )
  {
    rnVALUE.pvValue = ptImage;
  }
  else
  {
    return TPattern::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPatternTexture::getAttributeList (TAttributeList& rtLIST) const
{

  TPattern::getAttributeList (rtLIST);

  rtLIST ["texture"] = FX_IMAGE;

}  /* getAttributeList() */


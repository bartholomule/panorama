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

TPatternTexture::TPatternTexture (void) :
      TPattern(),
      tTiling (1, 1),
      tScaling (1.0, 1.0, 1.0),
      gMirror (false),
      gTile (true),
      eMapping (FX_SPHERICAL)
{

  recalculateMatrix();

}  /* TPatternTexture() */


int TPatternTexture::correctTexel (int iVALUE, const size_t& rkzMAX) const
{

  return ( iVALUE <= 0 ) ? -iVALUE : (rkzMAX - iVALUE);

}  /* correctTexel() */


TColor TPatternTexture::lerpTexel (const TVector2& rktUVCOORD) const
{
 
  TColor   tLerpColor;
  TScalar  u, v;  
  int      iu, iv;
  float    uv, iuv, uiv, iuiv;
  float    tmu, tmv;
  double   iiu, iiv;
  double   fu, fv;

  u = rktUVCOORD.x();
  v = rktUVCOORD.y();  

  tmu = fmod (u, 1.0) * (double) zTextureWidth;
  tmv = fmod (v, 1.0) * (double) zTextureHeight;

  fu = modf (tmu, &iiu);
  fv = modf (tmv, &iiv);

  // values in u and v
  iu = (int) iiu;
  iv = (int) iiv;

  if ( gMirror )
  {
    if ( ((int) u) & 1 )
    {
      iu = -iu;
      fu = 1.0 - fu;
    }

    if ( ((int) v) & 1 )
    {
      iv = -iv;
      fv = 1.0 - fv;
    }
  }

  uv   = fu * fv;
  iuv  = (1.0 - fu) * fv;
  uiv  = fu * (1.0 - fv);
  iuiv = (1.0 - fu) * (1.0 - fv);

  tLerpColor  = ptImage->getPixel (correctTexel (iu    , zTextureWidth), 
                                   correctTexel (iv    , zTextureHeight)) * iuiv;
  tLerpColor += ptImage->getPixel (correctTexel (iu + 1, zTextureWidth), 
                                   correctTexel (iv    , zTextureHeight)) * uiv;
  tLerpColor += ptImage->getPixel (correctTexel (iu    , zTextureWidth),
                                   correctTexel (iv + 1, zTextureHeight)) * iuv;
  tLerpColor += ptImage->getPixel (correctTexel (iu + 1, zTextureWidth), 
                                   correctTexel (iv + 1, zTextureHeight)) * uv;

  return tLerpColor;

}  /* lerpTexel() */


void TPatternTexture::sphericalMap (const TVector& rktPOINT, TVector2& rtUVCOORD) const
{
  
  TVector   tVector;
  TScalar   x, y, z;
  TScalar   len;
  TScalar   rtPhi;
  TScalar   rtTheta;

  tVector = rktPOINT;
  tVector.normalize();

  x = tVector.x();
  y = tVector.y();
  z = tVector.z();
  
  rtPhi = asin (y) / PI;

  len = sqrt (x * x + z * z);

  if ( len < FX_EPSILON )
  {
    rtTheta = 0.0;
  }
  else
  {
    if ( fabs (z) < FX_EPSILON )
    {
      if ( x > 0 )
      {
	rtTheta = 0.0;
      }
      else
      {
	rtTheta = PI;
      }
    }
    else
    {
      rtTheta = acos (x / len);

      if ( z < 0.0 )
      {
	rtTheta = (PI * 2) - rtTheta;
      }
    }

    rtTheta /= (PI * 2);
  }

  rtUVCOORD.set (rtTheta - 0.5, rtPhi);
  
}  /* sphericalMap() */


void TPatternTexture::cylindricalMap (const TVector& rktPOINT, TVector2& rtUVCOORD) const
{
  
  TVector   tVector;
  TScalar   x, y, z;
  TScalar   len;
  TScalar   rtTheta;

  tVector = rktPOINT;
  //tVector.normalize();

  x = tVector.x();
  y = tVector.y();
  z = tVector.z();
  
  len = sqrt (x * x + z * z);

  if ( len < FX_EPSILON )
  {
    rtTheta = 0.0;
  }
  else
  {
    if ( fabs (z) < FX_EPSILON )
    {
      if ( x > 0 )
      {
	rtTheta = 0.0;
      }
      else
      {
	rtTheta = PI;
      }
    }
    else
    {
      rtTheta = acos (x / len);

      if ( z < 0.0 )
      {
	rtTheta = (PI * 2) - rtTheta;
      }
    }

    rtTheta /= (PI * 2);
  }

  rtUVCOORD.set (rtTheta - 0.5, y * 0.5);
  
}  /* cylindricalMap() */


void TPatternTexture::planarMap (const TVector& rktPOINT, TVector2& rtUVCOORD) const
{
  
  TVector   tVector;
  TScalar   x, y;

  tVector = rktPOINT;
  //tVector.normalize();

  x = tVector.x();
  y = tVector.y();

  rtUVCOORD.set (x * 0.5, y * 0.5);
  
}  /* planarMap() */


void TPatternTexture::recalculateMatrix (void)
{

  TMatrix   tTempMatrix;

  tMatrix.setIdentity();
  
  tTempMatrix.setTranslation (tTranslation);
  tMatrix = tTempMatrix * tMatrix;

  tTempMatrix.setRotationX (tRotation.x());
  tMatrix = tTempMatrix * tMatrix;
  
  tTempMatrix.setRotationY (tRotation.y());
  tMatrix = tTempMatrix * tMatrix;
  
  tTempMatrix.setRotationZ (tRotation.z());
  tMatrix = tTempMatrix * tMatrix;

  tTempMatrix.setScaling (tScaling, TVector(0, 0, 0));
  tMatrix = tTempMatrix * tMatrix;

}  /* recalculateMatrix() */


TColor TPatternTexture::pattern (const TSurfaceData& rktDATA) const
{

  TVector   tPoint;
  TVector2  tUVcoord;
  
  if ( !ptImage )
  {
    cerr << "Error: texture must be set" << endl;
    exit (1);
  }

  tPoint = tMatrix * rktDATA.localPoint();

  switch (eMapping) 
  {
    case (FX_PLANAR) :
      planarMap (tPoint, tUVcoord);
      break; 

    case (FX_CYLINDRICAL) :
      cylindricalMap (tPoint, tUVcoord);
      break;
 
    default:
      sphericalMap (tPoint, tUVcoord);
  }

  tUVcoord *= tTiling;

  if ( !gTile )
  {
    TScalar  u = tUVcoord.x();
    TScalar  v = tUVcoord.y();

    if ( ( u < -0.5 ) || ( u > 0.5 ) || ( v < -0.5 ) || ( v > 0.5 ) )
    {
      return tColor;
    }
  }
    
  tUVcoord += tOffset;
  tUVcoord += 0.5;

  return lerpTexel (tUVcoord);

}  /* pattern() */


int TPatternTexture::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "color" )
  {
    if ( eTYPE == FX_COLOR )
    {
      tColor = *((TColor*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "texture" )
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
  else if ( rktNAME == "tiling" )
  {
    if ( eTYPE == FX_VECTOR2 )
    {
      tTiling = *((TVector2*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "offset" )
  {
    if ( eTYPE == FX_VECTOR2 )
    {
      tOffset = *((TVector2*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "rotation" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      tRotation = *((TVector*) nVALUE.pvValue);      

      recalculateMatrix();
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "scaling" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      tScaling = *((TVector*) nVALUE.pvValue);

      recalculateMatrix();
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "translation" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      tTranslation = *((TVector*) nVALUE.pvValue);

      recalculateMatrix();
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "mirror" )
  {
    if ( eTYPE == FX_BOOL )
    {
      gMirror = nVALUE.gValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "tile" )
  {
    if ( eTYPE == FX_BOOL )
    {
      gTile = nVALUE.gValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "mapping" )
  {
    if ( eTYPE == FX_STRING )
    {
      string tMapping ((char *) nVALUE.pvValue);

      if ( tMapping == "spherical" )
      {
        eMapping = FX_SPHERICAL;
      }
      else if ( tMapping == "cylindrical" )
      {
        eMapping = FX_CYLINDRICAL;
      }
      else if ( tMapping == "planar" )
      {
        eMapping = FX_PLANAR;
      }
      else
      {
        return FX_ATTRIB_WRONG_VALUE;
      } 
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

  if ( rktNAME == "color" )
  {
    rnVALUE.pvValue = &tColor;
  }
  else if ( rktNAME == "texture" )
  {
    rnVALUE.pvValue = ptImage;
  }
  else if ( rktNAME == "tiling" )
  {
    rnVALUE.pvValue = &tTiling;
  }
  else if ( rktNAME == "offset" )
  {
    rnVALUE.pvValue = &tOffset;
  }
  else if ( rktNAME == "rotation" )
  {
    rnVALUE.pvValue = &tRotation;
  }
  else if ( rktNAME == "scaling" )
  {
    rnVALUE.pvValue = &tScaling;
  }
  else if ( rktNAME == "translation" )
  {
    rnVALUE.pvValue = &tTranslation;
  }
  else if ( rktNAME == "mirror" )
  {
    rnVALUE.gValue = gMirror;
  }
  else if ( rktNAME == "tile" )
  {
    rnVALUE.gValue = gTile;
  }
  else if ( rktNAME == "mapping" )
  {
    switch (eMapping) 
    {
      case (FX_PLANAR) :
        rnVALUE.pvValue = (void *) "planar";
        break; 

      case (FX_CYLINDRICAL) :
        rnVALUE.pvValue = (void *) "cylindrical";
        break;
 
      default:
        rnVALUE.pvValue = (void *) "spherical";
    }
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

  rtLIST ["color"]       = FX_COLOR;
  rtLIST ["texture"]     = FX_IMAGE;
  rtLIST ["tiling"]      = FX_VECTOR2;
  rtLIST ["offset"]      = FX_VECTOR2;
  rtLIST ["rotation"]    = FX_VECTOR;
  rtLIST ["scaling"]     = FX_VECTOR;
  rtLIST ["translation"] = FX_VECTOR;
  rtLIST ["mirror"]      = FX_BOOL;
  rtLIST ["tile"]        = FX_BOOL;
  rtLIST ["mapping"]     = FX_STRING;

}  /* getAttributeList() */


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

#include "llapi/warning_eliminator.h"
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
      gMirror (false),
      gTile (true),
      eMapping (FX_SPHERICAL)
{

  recalculateMatrix();

}  /* TPatternTexture() */


TColor TPatternTexture::lerpTexel (const TVector2& rktUVCOORD) const
{
 
  TColor   tLerpColor;
  TScalar  u, v;  
  int      iu, iv, iu2, iv2;
  float    uv, iuv, uiv, iuiv;
  double   iiu, iiv;
  double   fu, fv;
  bool     gUWrapped;
  bool     gU2Wrapped;
  bool     gVWrapped;
  bool     gV2Wrapped;

  u = rktUVCOORD.x() * dTextureWidth;
  v = rktUVCOORD.y() * dTextureHeight;  
 
  // fractional part in fu and fv
  fu = modf (u, &iiu);
  fv = modf (v, &iiv);

  // integral part in iu and iv
  iu = (int) iiu;
  iv = (int) iiv;

  iu2 = correctTexel (iu + 1, gU2Wrapped, zTextureWidth );
  iv2 = correctTexel (iv + 1, gV2Wrapped, zTextureHeight);
  iu  = correctTexel (iu    , gUWrapped , zTextureWidth );
  iv  = correctTexel (iv    , gVWrapped , zTextureHeight);

  if ( fu < 0.0 ) 
  {
    fu += 1.0;
  }
  if ( fv < 0.0 ) 
  {
    fv += 1.0;
  }

  uv   = fu * fv;
  iuv  = (1.0 - fu) * fv;
  uiv  = fu * (1.0 - fv);
  iuiv = (1.0 - fu) * (1.0 - fv);

  tLerpColor  = getColor ((gUWrapped  | gVWrapped ), iu , iv ) * iuiv;
  tLerpColor += getColor ((gU2Wrapped | gVWrapped ), iu2, iv ) * uiv;
  tLerpColor += getColor ((gUWrapped  | gV2Wrapped), iu , iv2) * iuv;
  tLerpColor += getColor ((gU2Wrapped | gV2Wrapped), iu2, iv2) * uv;

  return tLerpColor;

}  /* lerpTexel() */


void TPatternTexture::sphericalMap (const TVector& rktPOINT, TVector2& rtUVCOORD) const
{
  
  TVector   tVector;
  TScalar   x, y, z;
  TScalar   tLength;
  TScalar   tPhi;
  TScalar   tTheta;

  tVector = rktPOINT;
  tVector.normalize();

  x = tVector.x();
  y = tVector.y();
  z = tVector.z();
  
  tPhi = asin (y) / PI;

  tLength = sqrt (x * x + z * z);

  if ( tLength < FX_EPSILON )
  {
    tTheta = 0.0;
  }
  else
  {
    if ( fabs (z) < FX_EPSILON )
    {
      if ( x > 0 )
      {
	tTheta = 0.0;
      }
      else
      {
	tTheta = PI;
      }
    }
    else
    {
      tTheta = acos (x / tLength);

      if ( z < 0.0 )
      {
	tTheta = (PI * 2) - tTheta;
      }
    }

    tTheta *= (1.0 / (PI * 2));
  }

  rtUVCOORD.set (tTheta - 0.5, tPhi);
  
}  /* sphericalMap() */


void TPatternTexture::cylindricalMap (const TVector& rktPOINT, TVector2& rtUVCOORD) const
{
  
  TVector   tVector;
  TScalar   x, y, z;
  TScalar   tLength;
  TScalar   tTheta;

  tVector = rktPOINT;

  x = tVector.x();
  y = tVector.y();
  z = tVector.z();
  
  tLength = sqrt (x * x + z * z);

  if ( tLength < FX_EPSILON )
  {
    tTheta = 0.0;
  }
  else
  {
    if ( fabs (z) < FX_EPSILON )
    {
      if ( x > 0 )
      {
	tTheta = 0.0;
      }
      else
      {
	tTheta = PI;
      }
    }
    else
    {
      tTheta = acos (x / tLength);

      if ( z < 0.0 )
      {
	tTheta = (PI * 2) - tTheta;
      }
    }

    tTheta *= (1.0 / (PI * 2));
  }

  rtUVCOORD.set (tTheta - 0.5, y * 0.5);
  
}  /* cylindricalMap() */


void TPatternTexture::torusMap (const TVector& rktPOINT, TVector2& rtUVCOORD) const
{
  
  TVector   tVector;
  TScalar   x, y, z;
  TScalar   tLength;
  TScalar   tPhi;
  TScalar   tTheta;

  tVector = rktPOINT;

  x = tVector.x();
  y = tVector.y();
  z = tVector.z();
  
  tLength = sqrt (x * x + z * z);

  if ( tLength < FX_EPSILON )
  {
    tTheta = 0.0;
  }
  else
  {
    if ( fabs (z) < FX_EPSILON )
    {
      if ( x > 0 )
      {
	tTheta = 0.0;
      }
      else
      {
	tTheta = PI;
      }
    }
    else
    {
      tTheta = acos (x / tLength);

      if ( z < 0.0 )
      {
	tTheta = tTheta - (PI * 2);
      }
    }
  }
  
  x = tLength - tTubeCenter;

  tPhi = acos (-x / sqrt (x * x + y * y));

  if (y > 0.0)
  {
    tPhi = (PI * 2) - tPhi;
  }

  tTheta *= (1.0 / (PI * 2));
  tPhi   *= (1.0 / (PI * 2));

  rtUVCOORD.set (0.5 - tTheta, tPhi);
  
}  /* torusMap() */


void TPatternTexture::planarMap (const TVector& rktPOINT, TVector2& rtUVCOORD) const
{
  
  TVector   tVector;
  TScalar   x, y;

  tVector = rktPOINT;

  x = tVector.x();
  y = tVector.y();

  rtUVCOORD.set (x * 0.5, y * 0.5);
  
}  /* planarMap() */


TColor TPatternTexture::pattern (const TSurfaceData& rktDATA) const
{

  TVector   tPoint;
  TVector2  tUVcoord;
  
  if ( !ptImage )
  {
    cerr << "Error: texture must be set" << endl;
    exit (1);
  }

  tPoint = rktDATA.localPoint();

  switch (eMapping) 
  {
    case (FX_CYLINDRICAL) :
      cylindricalMap (tPoint, tUVcoord);
      break;

    case (FX_TORUS) :
      torusMap (tPoint, tUVcoord);
      break;

    case (FX_PLANAR) :
      planarMap (tPoint, tUVcoord);
      break; 
 
    default:
      sphericalMap (tPoint, tUVcoord);
  }

  tUVcoord *= tTiling;

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

      zTextureWidth  = (size_t) ptImage->width();
      zTextureHeight = (size_t) ptImage->height();

      dTextureWidth  = ptImage->width();
      dTextureHeight = ptImage->height();
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
      else if ( tMapping == "torus" )
      {
        eMapping = FX_TORUS;
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
  else if ( rktNAME == "tube_center" )
  {
    if ( eTYPE == FX_REAL )
    {
      tTubeCenter = nVALUE.dValue;
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
      case (FX_CYLINDRICAL) :
        rnVALUE.pvValue = (void *) "cylindrical";
        break;
 
      case (FX_TORUS) :
        rnVALUE.pvValue = (void *) "torus";
        break;

      case (FX_PLANAR) :
        rnVALUE.pvValue = (void *) "planar";
        break; 
 
      default:
        rnVALUE.pvValue = (void *) "spherical";
    }
  }
  else if ( rktNAME == "tube_center" )
  {
    rnVALUE.dValue = tTubeCenter;
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
  rtLIST ["mirror"]      = FX_BOOL;
  rtLIST ["tile"]        = FX_BOOL;
  rtLIST ["mapping"]     = FX_STRING;
  rtLIST ["tube_center"] = FX_REAL;

}  /* getAttributeList() */


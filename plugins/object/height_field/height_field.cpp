/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#include <math.h>
#include <iostream.h>
#include "llapi/file.h"
#include "hlapi/image_manager.h"
#include "height_field.h"

DEFINE_PLUGIN ("HeightField", FX_OBJECT_CLASS, THeightField);

inline TScalar THeightField::getHeight (size_t I, size_t J) const
{

  return ptImage->getPixel (I, J).red() + ptImage->getPixel (I, J).green() + ptImage->getPixel (I, J).blue();
  
}  /* getHeight() */


bool THeightField::checkIntersection (int iCELLX, int iCELLZ, const TRay& rktRAY, const TInterval& rktINTY, TSurfaceData& rtDATA) const
{

  TVector   tNormal;
  TScalar   D, tDen, tSol;
  TScalar   Y1         = getHeight (iCELLX,     iCELLZ);
  TScalar   Y2         = getHeight (iCELLX + 1, iCELLZ);
  TScalar   Y3         = getHeight (iCELLX,     iCELLZ + 1);
  TScalar   Y4         = getHeight (iCELLX + 1, iCELLZ + 1);
  TScalar   tLocalMinY = min (min (Y1, Y2), min (Y3, Y4));
  TScalar   tLocalMaxY = max (max (Y1, Y2), max (Y3, Y4));
  TScalar   tPosX      = TScalar (iCELLX) - tHalfWidth;
  TScalar   tPosZ      = TScalar (iCELLZ) - tHalfHeight;

  if ( ( rktINTY.min() > tLocalMaxY ) || ( rktINTY.max() < tLocalMinY ) )
  {
    return false;
  }

  // Check intersection with first triangle.

  tNormal.set (Y2 - Y1, -1, Y3 - Y1);
  tNormal.normalize();

  tDen = dotProduct (tNormal, rktRAY.direction());

  // Check that ray and plane are not parallel and ray is pointing in the right direction
  if ( fabs (tDen) > FX_EPSILON )
  {
    D = -(tNormal.x() * tPosX +
          tNormal.y() * Y1 +
          tNormal.z() * tPosZ);

    tSol = -(dotProduct (tNormal, rktRAY.location()) + D) / tDen;

    if ( ( tSol >= FX_EPSILON ) && ( tSol <= rktRAY.limit()) )
    {
      TVector   tPoint = rktRAY.location() + rktRAY.direction() * tSol;

      if ( ( tPoint.x() >= tPosX ) &&
           ( tPoint.z() >= tPosZ ) &&
           ( (tPoint.x() + tPoint.z()) <= (tPosX + tPosZ + 2) ) )
      {
        rtDATA.setup (this, rktRAY);
        rtDATA.setPoint (tSol, tNormal);

        return true;
      }
    }
  }

  // Check intersection with second triangle.

  tNormal.set (Y4 - Y3, -1, Y4 - Y2);
  tNormal.normalize();

  tDen = dotProduct (tNormal, rktRAY.direction());

  // Check if ray and plane are not parallel
  if ( fabs (tDen) > FX_EPSILON )
  {
    D = -(tNormal.x() * (tPosX + 1) +
          tNormal.y() * Y4 +
          tNormal.z() * (tPosZ + 1));

    tSol = -(dotProduct (tNormal, rktRAY.location()) + D) / tDen;

    if ( ( tSol >= FX_EPSILON ) && ( tSol <= rktRAY.limit()) )
    {
      TVector   tPoint = rktRAY.location() + rktRAY.direction() * tSol;

      if ( ( tPoint.x() <= (tPosX + 1) ) &&
           ( tPoint.z() <= (tPosZ + 1) ) &&
           ( (tPoint.x() + tPoint.z()) >= (tPosX + tPosZ + 2) ) )
      {
        rtDATA.setup (this, rktRAY);
        rtDATA.setPoint (tSol, tNormal);

        return true;
      }
    }
  }
  
  return false;
      
}  /* checkIntersection() */


bool THeightField::traverseGrid (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TScalar   tError;
  TScalar   tDelta, tDeltaY;
  TScalar   tNearY, tFarY;
  int       iCellX = (int) floor (rktRAY.location().x() + tHalfWidth);
  int       iCellZ = (int) floor (rktRAY.location().z() + tHalfHeight);
  int       iSignX = sign (rktRAY.direction().x());
  int       iSignZ = sign (rktRAY.direction().z());
  TScalar   X0     = rktRAY.location().x() - floor (rktRAY.location().x());
  TScalar   Z0     = rktRAY.location().z() - floor (rktRAY.location().z());

  tNearY = rktRAY.location().y();

  if ( fabs (rktRAY.direction().x()) >= fabs (rktRAY.direction().z()) )
  {
    // Driving axis is X axis

    tDelta  = fabs (rktRAY.direction().z() / rktRAY.direction().x());
    tDeltaY = rktRAY.direction().y() / fabs (rktRAY.direction().x());

    if ( rktRAY.direction().x() >= 0 )
    {
      tFarY = rktRAY.location().y() + (1 - X0) * tDeltaY;
      
      if ( rktRAY.direction().z() >= 0 )
      {
        // First octant
        tError = Z0 + (1 - X0) * tDelta - 1;
      }
      else
      {
        // Eighth octant
        tError = -Z0 + (1 - X0) * tDelta;
      }
    }
    else
    {
      tFarY = rktRAY.location().y() + X0 * tDeltaY;
      
      if ( rktRAY.direction().z() >= 0 )
      {
        // Fourth octant
        tError = Z0 + X0 * tDelta - 1;
      }
      else
      {
        // Fifth octant
        tError = -Z0 + X0 * tDelta;
      }
    }

    do
    {
      if ( checkIntersection (iCellX, iCellZ, rktRAY, TInterval (tNearY, tFarY), rtDATA) )
      {
        return true;
      }

      if ( tError > FX_EPSILON )
      {
        iCellZ += iSignZ;
        if ( ( iCellZ < 0 ) || ( iCellZ == ptImage->height() ) )
        {
          break;
        }
        else if ( checkIntersection (iCellX, iCellZ, rktRAY, TInterval (tNearY, tFarY), rtDATA) )
        {
          return true;
        }

        tError--;
      }
      else if ( tError > -FX_EPSILON )
      {
        // Ray crosses at exactly the corner of the cell.

        iCellZ += iSignZ;
        tError--;
      }

      iCellX += iSignX;
      tError += tDelta;
      tNearY  = tFarY;
      tFarY  += tDeltaY;

    } while ( ( tNearY >= tMinY ) && ( tNearY <= tMaxY )       &&
              ( iCellX >= 0 ) && ( iCellX < ptImage->width() ) &&
              ( iCellZ >= 0 ) && ( iCellZ < ptImage->height() ) );
  }
  else
  {
    // Driving axis is Z axis

    tDelta  = fabs (rktRAY.direction().x() / rktRAY.direction().z());
    tDeltaY = rktRAY.direction().y() / fabs (rktRAY.direction().z());

    if ( rktRAY.direction().z() >= 0 )
    {
      tFarY = rktRAY.location().y() + (1 - Z0) * tDeltaY;
      
      if ( rktRAY.direction().x() >= 0 )
      {
        // Second octant
        tError = X0 + (1 - Z0) * tDelta - 1;
      }
      else
      {
        // Third octant
        tError = -X0 + (1 - Z0) * tDelta;
      }
    }
    else
    {
      tFarY = rktRAY.location().y() + Z0 * tDeltaY;
      
      if ( rktRAY.direction().z() >= 0 )
      {
        // Fourth octant
        tError = X0 + Z0 * tDelta - 1;
      }
      else
      {
        // Fifth octant
        tError = -X0 + Z0 * tDelta;
      }
    }

    do
    {
      if ( checkIntersection (iCellX, iCellZ, rktRAY, TInterval (tNearY, tFarY), rtDATA) )
      {
        return true;
      }

      if ( tError > FX_EPSILON )
      {
        iCellX += iSignX;
        if ( ( iCellX < 0 ) || ( iCellX == ptImage->width() ) )
        {
          break;
        }
        else if ( checkIntersection (iCellX, iCellZ, rktRAY, TInterval (tNearY, tFarY), rtDATA) )
        {
          return true;
        }

        tError--;
      }
      else if ( tError > -FX_EPSILON )
      {
        // Ray crosses at exactly the corner of the cell.

        iCellX += iSignX;
        tError--;
      }

      iCellZ += iSignZ;
      tError += tDelta;
      tNearY  = tFarY;
      tFarY  += tDeltaY;

    } while ( ( tNearY >= tMinY ) && ( tNearY <= tMaxY )       &&
              ( iCellX >= 0 ) && ( iCellX < ptImage->width() ) &&
              ( iCellZ >= 0 ) && ( iCellZ < ptImage->height() ) );
    
  }

  return false;
  
}  /* traverseGrid() */

                                 
void THeightField::initialize (void)
{

  TScalar   Y;

  assert ( ptImage );

  tMaxY = -SCALAR_MAX;
  tMinY = SCALAR_MAX;

  tHalfWidth  = ptImage->width() * 0.5;
  tHalfHeight = ptImage->height() * 0.5;

  for (size_t J = 0; ( J < ptImage->height() ) ;J++)
  {
    for (size_t I = 0; ( I < ptImage->width() ) ;I++)
    {
      Y = getHeight (I, J);
                     
      if ( Y > tMaxY )
      {
        tMaxY = Y;
      }
      if ( Y < tMinY )
      {
        tMinY = Y;
      }
    }
  }

  tBoundingBox.set (TVector (-tHalfWidth, tMinY, -tHalfHeight), TVector (tHalfWidth, tMaxY, tHalfHeight));
  tBoundingBox.applyTransform (*ptMatrix);

}  /* initialize() */


int THeightField::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "image" )
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
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TObject::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int THeightField::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "image" )
  {
    rnVALUE.pvValue = ptImage;
  }
  else
  {
    return TObject::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void THeightField::getAttributeList (TAttributeList& rtLIST) const
{

  TObject::getAttributeList (rtLIST);

  rtLIST ["image"]  = FX_IMAGE;

}  /* getAttributeList() */


bool THeightField::findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TInterval   tInt;
  TScalar     tFactor;
  TRay        tRayIT = rktRAY;

  tInt = tBoundingBox.clipRay (rktRAY);

  if ( tInt.empty() )
  {
    return false;
  }
  
  tFactor = tRayIT.applyTransform (ptInverseMatrix);

  tInt.set (tInt.min() / tFactor, tInt.max() / tFactor);
  
  tRayIT.setLocation (tRayIT.location() + tRayIT.direction() * tInt.min());
  tRayIT.setLimit (tInt.max());

  if ( traverseGrid (tRayIT, rtDATA) )
  {
    TVector   tNormal = rtDATA.normal();
    
    tNormal.applyTransform (ptMatrix);
        
    rtDATA.setup (this, rktRAY);
    rtDATA.setPoint (rtDATA.distance() * tFactor, tNormal);

    return true;
  }
  
  return false;

}  /* findFirstIntersection() */


bool THeightField::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
{

  TSurfaceData   tSurfaceData;
  TInterval      tIntX, tIntY, tIntZ, tIntTmp;
  TScalar        tFactor;
  TRay           tRayIT        = rktRAY;
  bool           gIntersection = false;

  if ( !tBoundingBox.intersects (rktRAY) )
  {
    return false;
  }
  
  tFactor = tRayIT.applyTransform (ptInverseMatrix);

  if ( rktRAY.limit() < SCALAR_MAX )
  {
    tRayIT.setLimit (rktRAY.limit() / tFactor);
  }

  if ( fabs (tRayIT.direction().x()) < FX_EPSILON )
  {
    // Ray is parallel to YZ plane
    if ( !( ( tRayIT.location().x() >= -0.5 ) && ( tRayIT.location().x() <= 0.5 ) ) )
    {
      return false;
    }
    tIntX.set (0, SCALAR_MAX);
  }
  else
  {
    tIntX.set ((-0.5 - tRayIT.location().x()) / tRayIT.direction().x(), (0.5 - tRayIT.location().x()) / tRayIT.direction().x());
  }

  if ( fabs (tRayIT.direction().y()) < FX_EPSILON )
  {
    // Ray is parallel to ZX plane
    if ( !( ( tRayIT.location().y() >= -0.5 ) && ( tRayIT.location().y() <= 0.5 ) ) )
    {
      return false;
    }
    tIntY.set (0, SCALAR_MAX);
  }
  else
  {
    tIntY.set ((-0.5 - tRayIT.location().y()) / tRayIT.direction().y(), (0.5 - tRayIT.location().y()) / tRayIT.direction().y());
  }

  if ( fabs (tRayIT.direction().z()) < FX_EPSILON )
  {
    // Ray is parallel to XY plane
    if ( !( ( tRayIT.location().z() >= -0.5 ) && ( tRayIT.location().z() <= 0.5 ) ) )
    {
      return false;
    }
    tIntZ.set (0, SCALAR_MAX);
  }
  else
  {
    tIntZ.set ((-0.5 - tRayIT.location().z()) / tRayIT.direction().z(), (0.5 - tRayIT.location().z()) / tRayIT.direction().z());
  }

  tIntTmp = Intersection (tIntX, tIntY);
  tIntTmp = Intersection (tIntTmp, tIntZ);

  if ( tIntTmp.empty() || ( tIntTmp.size() <= FX_EPSILON ) )
  {
    //
    // If there is no intersection or the intersection is in a single point.
    //
    return false;
  }

  tSurfaceData.setup (this, rktRAY);
  
  if ( ( tIntTmp.min() >= FX_EPSILON ) && ( tIntTmp.min() <= rktRAY.limit() ) )
  {
    if ( tSurfaceData.setPoint (tIntTmp.min() * tFactor) )
    {
      rtLIST.add (tSurfaceData);
      gIntersection = true;
    }
  }
  if ( ( tIntTmp.max() >= FX_EPSILON ) && ( tIntTmp.max() <= rktRAY.limit() ) )
  {
    if ( tSurfaceData.setPoint (tIntTmp.max() * tFactor) )
    {
      rtLIST.add (tSurfaceData);
      gIntersection = true;
    }
  }

  return gIntersection;

}  /* findAllIntersections() */

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

#include "llapi/warning_eliminator.h"
#include "llapi/file.h"
#include "hlapi/image_manager.h"
#include "projector.h"

DEFINE_PLUGIN ("Projector", FX_LIGHT_CLASS, TProjector);

TProjector::TProjector (void) :
  TPointLight(),
  tAngle (degreeToRadian (45)),
  tUp (0, 1, 0),
  ptImage (NULL) {}


int TProjector::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "point_at" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      tPointAt = *((TVector*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "up" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      tUp = *((TVector*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "angle" )
  {
    if ( eTYPE == FX_REAL )
    {
      tAngle = degreeToRadian (nVALUE.dValue);
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
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TPointLight::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TProjector::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "point_at" )
  {
    rnVALUE.pvValue = &tPointAt;
  }
  else if ( rktNAME == "up" )
  {
    rnVALUE.pvValue = &tUp;
  }
  else if ( rktNAME == "angle" )
  {
    // [_ERROR_] It should convert it to degree before returning.
    rnVALUE.dValue = tAngle;
  }
  else if ( rktNAME == "texture" )
  {
    rnVALUE.pvValue = ptImage;
  }
  else
  {
    return TPointLight::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TProjector::getAttributeList (TAttributeList& rtLIST) const
{

  TPointLight::getAttributeList (rtLIST);

  rtLIST ["point_at"] = FX_VECTOR;
  rtLIST ["up"]       = FX_VECTOR;
  rtLIST ["angle"]    = FX_REAL;
  rtLIST ["texture"]  = FX_IMAGE;

}  /* getAttributeList() */


bool TProjector::initialize (void)
{

  bool val = TPointLight::initialize();
  
  if ( ptImage )
  {
    tDirection = (tPointAt - tLocation);
    tDirection.normalize();

    I = crossProduct (tDirection, tUp);
    J = crossProduct (I, tDirection);
    I.normalize();
    J.normalize();

    tPixelSize =  ptImage->width() / tan (tAngle);
  }

  return val;
  
}  /* initialize() */


TColor TProjector::color (const TVector& rktPOS) const
{

  TScalar   u, v;
  TScalar   hx, hy;
  TScalar   pt, pu, pv;
  TVector   tPoint;

  if ( !visible (rktPOS) || !ptImage )
  {
    return TColor::_black();
  }

  tPoint = (rktPOS - tLocation);
  
  pt = dotProduct (tDirection, tPoint);
  pu = dotProduct (I, tPoint);
  pv = dotProduct (J, tPoint);

  hx = ptImage->width() / 2;
  hy = ptImage->height() / 2;

  u = hx + ((pu / pt) * tPixelSize);
  if ( ( u < 0 ) || ( u > ptImage->width() ) )
  {
    return TColor::_black();
  }
  v = hy - ((pv / pt) * tPixelSize);
  if ( ( v < 0 ) || ( v > ptImage->height() ) )
  {
    return TColor::_black();
  }

  return tColor * tIntensity * ptImage->getPixel (size_t (u), size_t (v)) * attenuation (rktPOS);

}  /* color() */


void TProjector::printDebug (void) const
{

  TPointLight::printDebug();

  TDebug::_push();

  cerr << TDebug::_indent() << "Angle     : " << tAngle << endl;
  cerr << TDebug::_indent() << "Up vector : "; tUp.printDebug();
  cerr << TDebug::_indent() << "Point at  : "; tPointAt.printDebug();
    
  TDebug::_pop();

}  /* printDebug() */

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
#include "llapi/attribute.h"
#include "llapi/extended_attribute.h"

DEFINE_PLUGIN ("Projector", FX_LIGHT_CLASS, TProjector);

TProjector::TProjector (void) :
  TPointLight(),
  tAngle (degreeToRadian (45)),
  tUp (0, 1, 0),
  ptImage (NULL) {}


int TProjector::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "point_at" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_VECTOR )
    {
      tPointAt = *((TVector*) nVALUE.pvValue);
    }
#else
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      tPointAt = vec->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "up" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_VECTOR )
    {
      tUp = *((TVector*) nVALUE.pvValue);
    }
#else
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      tUp = vec->tValue;
    }
#endif    
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "angle" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      tAngle = degreeToRadian (nVALUE.dValue);
    }
#else
    magic_pointer<TAttribReal> r = get_real (nVALUE);
    if( !!r )
    {
      tAngle = degreeToRadian (r->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "texture" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_STRING )
    {
      char*   pcName = (char*) nVALUE.pvValue;
        
      ptImage = tImageManager.newImage (pcName, FileExtension (pcName));
      if ( !ptImage )
      {
        TProcedural::_tUserErrorMessage = std::string ("could not open texture file ") + (char*) nVALUE.pvValue;
        return FX_ATTRIB_USER_ERROR;
      }
    }
    else if ( eTYPE == FX_IMAGE )
    {
      TImage* im2 = (TImage*)nVALUE.pvValue;

      if( im2 != NULL )
      {
	ptImage = new TImage(*im2);
      }
      else
      {
	TProcedural::_tUserErrorMessage = "null image given";
	
	return FX_ATTRIB_USER_ERROR;
      }      
    }
#else
    magic_pointer<TAttribString> str = get_string(nVALUE);
    if( !!str )
    {
      std::string pcName = str->tValue;
      ptImage = (magic_pointer<TImage>)tImageManager.newImage (pcName, FileExtension (pcName));
      if ( !ptImage )
      {
        TProcedural::_tUserErrorMessage = "could not open texture file " + pcName;
        return FX_ATTRIB_USER_ERROR;
      }      
    }
    else if( eTYPE == FX_IMAGE )
    {
      magic_pointer<TAttribImage> img = get_image(nVALUE);
      
      if( !!img )
      {
	ptImage = img->tValue;
      }
      else
      {
	TProcedural::_tUserErrorMessage = "null image given";
	
	return FX_ATTRIB_USER_ERROR;
      }
    }
#endif
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



int TProjector::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)
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
    // (KH) Fixed.
    rnVALUE.dValue = (tAngle * 180.0) / PI;
  }
  else if ( rktNAME == "texture" )
  {
    rnVALUE.pvValue = ptImage.get_pointer();
  }
#else
  if ( rktNAME == "point_at" )
  {
    rnVALUE = (user_arg_type)new TAttribVector (tPointAt);
  }
  else if ( rktNAME == "up" )
  {
    rnVALUE = (user_arg_type)new TAttribVector (tUp);    
  }
  else if ( rktNAME == "angle" )
  {
    rnVALUE = (user_arg_type)new TAttribReal ((tAngle * 180.0) / PI);
  }
  else if ( rktNAME == "texture" )
  {
    rnVALUE = (user_arg_type)new TAttribImage (ptImage);
  }  
#endif
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
  
  if ( !!ptImage )
  {
    tDirection = (tPointAt - location());
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

  tPoint = (rktPOS - location() );
  
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


void TProjector::printDebug (const std::string& indent) const
{

  TPointLight::printDebug(indent);

  std::string new_indent = TDebug::Indent(indent);

  GOM.debug() << new_indent << "Angle     : " << tAngle << std::endl;
  GOM.debug() << new_indent << "Up std::vector : "; tUp.printDebug(new_indent);
  GOM.debug() << new_indent << "Point at  : "; tPointAt.printDebug(new_indent);
  GOM.debug() << indent << "." << std::endl;

}  /* printDebug() */

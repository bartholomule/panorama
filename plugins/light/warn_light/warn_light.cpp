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

#include "warn_light.h"

DEFINE_PLUGIN ("WarnLight", FX_LIGHT_CLASS, TWarnLight);

TScalar TWarnLight::attenuation (const TVector& rktPOINT) const
{

  TScalar   tCos;
  TScalar   tAtten = 0;
  TVector   tPoint = (rktPOINT - tLocation);

  tPoint.normalize();
  tCos = dotProduct (tLightAxis, tPoint);
  if ( tCos > 0 )
  {
    tAtten = pow (tCos, tExponent);
  }

  return (tAtten * TPointLight::attenuation (rktPOINT));
  
}  /* attenuation() */


int TWarnLight::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "point_at" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      pointAt (*((TVector*) nVALUE.pvValue));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "exponent" )
  {
    if ( eTYPE == FX_REAL )
    {
      setExponent (nVALUE.dValue);
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


int TWarnLight::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "point_at" )
  {
    rnVALUE.pvValue = &tLightAxis;
  }
  else if ( rktNAME == "exponent" )
  {
    rnVALUE.dValue = tExponent;
  }
  else
  {
    return TPointLight::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TWarnLight::getAttributeList (TAttributeList& rtLIST) const
{

  TPointLight::getAttributeList (rtLIST);

  rtLIST ["point_at"] = FX_VECTOR;
  rtLIST ["exponent"] = FX_REAL;

}  /* getAttributeList() */


void TWarnLight::initialize (void)
{

  TPointLight::initialize();
  
  //
  // [_ERROR_] This will not work if called more than once.
  //
  tLightAxis = (tLightAxis - tLocation);
  tLightAxis.normalize();
  
}  /* initialize() */


void TWarnLight::printDebug (void) const
{

  TPointLight::printDebug();
  
  TDebug::_push();

  cerr << TDebug::_indent() << "Light axis : "; tLightAxis.printDebug();
  cerr << TDebug::_indent() << "Exponent   : " << tExponent << endl;
  
  TDebug::_pop();
  
}  /* printDebug() */

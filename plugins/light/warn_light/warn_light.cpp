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

#include "llapi/warning_eliminator.h"
#include "warn_light.h"
#include "llapi/attribute.h"

DEFINE_PLUGIN ("WarnLight", FX_LIGHT_CLASS, TWarnLight);

TScalar TWarnLight::attenuation (const TVector& rktPOINT) const
{

  TScalar   tCos;
  TScalar   tAtten = 0;
  TVector   tPoint = (rktPOINT - location());

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
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_VECTOR )
    {
      pointAt (*((TVector*) nVALUE.pvValue));
    }
#else
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      pointAt (vec->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "exponent" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      setExponent (nVALUE.dValue);
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      setExponent (r->tValue);
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


int TWarnLight::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)
  if ( rktNAME == "point_at" )
  {
    rnVALUE.pvValue = &tLightPoint;
  }
  else if ( rktNAME == "exponent" )
  {
    rnVALUE.dValue = tExponent;
  }
#else
  if ( rktNAME == "point_at" )
  {
    rnVALUE = (user_arg_type)new TAttribVector (tLightPoint);
  }
  else if ( rktNAME == "exponent" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tExponent);
  }  
#endif
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


bool TWarnLight::initialize (void)
{

  bool val = TPointLight::initialize();
  
  //
  // [_ERROR_] This will not work if called more than once.
  // (KH) I think this is no longer a problem.
  //
  tLightAxis = (tLightPoint - location());
  tLightAxis.normalize();

  return val;
}  /* initialize() */


void TWarnLight::printDebug (const string& indent) const
{

  TPointLight::printDebug(indent);
  
  string new_indent = TDebug::Indent(indent);

  cerr << new_indent << "Light axis : "; tLightAxis.printDebug(new_indent);
  cerr << new_indent << "Exponent   : " << tExponent << endl;
  cerr << indent << "." << endl;
  
}  /* printDebug() */

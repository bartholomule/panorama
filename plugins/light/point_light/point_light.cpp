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
#include "point_light.h"
#include "llapi/attribute.h"

DEFINE_PLUGIN ("PointLight", FX_LIGHT_CLASS, TPointLight);

bool TPointLight::visible (const TVector& rktPOINT) const
{

  TScalar   tDist;
  TVector   tPoint;
  TVector   tLocation = location();

  if ( tDistanceThreshold > 0 )
  {
    //
    // Check if light - point distance is less than threshold.
    //
    tDist = Distance (rktPOINT, tLocation);

    if ( tDist > tDistanceThreshold )
    {
      return false;
    }
  }

  if ( tCosThreshold > 0 )
  {
    //
    // Check if point is inside cone defined by light axis and angle threshold.
    //
    tPoint = (rktPOINT - tLocation);
    tPoint.normalize();
    if ( dotProduct (tConeAxis, tPoint) < tCosThreshold )
    {
      return false;
    }
  }

  return true;

}  /* visible() */


TColor TPointLight::scatteredLight (const TSurfaceData& rktDATA) const
{

  TScalar   t0, d0;

  if ( tHaloSize != 0 )
  {
    TVector tLocation = location();
    
    // Calculate t0 for the point in ray closest to light.
    t0 = dotProduct ((tLocation - rktDATA.ray().location()), rktDATA.ray().direction());

    // Calculate minimum distance from ray to light.
    d0 = (tLocation - (rktDATA.ray().location() + (rktDATA.ray().direction() * t0))).norm();

    // [_TODO_] Take into account light attenuation function.
    return tColor * (atan ((rktDATA.distance() - t0) / d0) - atan (-t0 / d0)) / ((1.0 / tHaloSize) * d0);
  }

  return TColor::_null();
  
}  /* scatteredLight() */


int TPointLight::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "falloff" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_VECTOR )
    {
      setFalloff (*((TVector*) nVALUE.pvValue));
    }
#else
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      setFalloff (vec->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "axis" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_VECTOR )
    {
      setAxis (*((TVector*) nVALUE.pvValue));
    }
#else
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      setAxis (vec->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "angle_th" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      setAngleThreshold (nVALUE.dValue);
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      setAngleThreshold (r->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "distance_th" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      setDistanceThreshold (nVALUE.dValue);
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      setDistanceThreshold (r->tValue);
    }    
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "halo" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      tHaloSize = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tHaloSize = r->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TLight::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TPointLight::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)
  if ( rktNAME == "falloff" )
  {
    rnVALUE.pvValue = &tFalloff;
  }
  else if ( rktNAME == "axis" )
  {
    rnVALUE.pvValue = &tConeAxis;
  }
  else if ( rktNAME == "angle_th" )
  {
    rnVALUE.dValue = tCosThreshold;
  }
  else if ( rktNAME == "distance_th" )
  {
    rnVALUE.dValue = tDistanceThreshold;
  }
  else if ( rktNAME == "halo" )
  {
    rnVALUE.dValue = tHaloSize;
  }
#else
  if ( rktNAME == "falloff" )
  {
    rnVALUE = new TAttribVector (tFalloff);
  }
  else if ( rktNAME == "axis" )
  {
    rnVALUE = new TAttribVector (tConeAxis);
  }
  else if ( rktNAME == "angle_th" )
  {
    rnVALUE = new TAttribReal (tCosThreshold);
  }
  else if ( rktNAME == "distance_th" )
  {
    rnVALUE = new TAttribReal (tDistanceThreshold);
  }
  else if ( rktNAME == "halo" )
  {
    rnVALUE = new TAttribReal (tHaloSize);
  }
#endif
  else
  {
    return TLight::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPointLight::getAttributeList (TAttributeList& rtLIST) const
{

  TLight::getAttributeList (rtLIST);

  rtLIST ["falloff"]     = FX_VECTOR;
  rtLIST ["axis"]        = FX_VECTOR;
  rtLIST ["angle_th"]    = FX_REAL;
  rtLIST ["distance_th"] = FX_REAL;
  rtLIST ["halo"]        = FX_REAL;

}  /* getAttributeList() */


bool TPointLight::initialize (void)
{

  bool val = TLight::initialize();
  
  //
  // [_ERROR_] This will not work if initialized more than once.
  // (KH) I think that this MAY no longer be a problem.
  // FIXME! Check this again.
  //
  tConeAxis = (tConeAxis2 - location());

  if ( tConeAxis != TVector (0, 0, 0) )
  {
    tConeAxis.normalize();
  }

  return val;
}  /* initialize() */


void TPointLight::printDebug (const string& indent) const
{

  cerr << indent << "[_" << className() << "_]" << endl;

  string new_indent = TDebug::Indent(indent);

  cerr << new_indent << "a (falloff)        : " << tFalloff [0] << endl;
  cerr << new_indent << "b (falloff)        : " << tFalloff [1] << endl;
  cerr << new_indent << "c (falloff)        : " << tFalloff [2] << endl;
  cerr << new_indent << "Distance threshold : " << tDistanceThreshold << endl;
  cerr << new_indent << "Cosine threshold   : " << tCosThreshold << endl;
  cerr << new_indent << "Cone axis          : "; tConeAxis.printDebug(new_indent);
  cerr << indent << "." << endl;

}  /* printDebug() */

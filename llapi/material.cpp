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

#include <cassert>
#include "llapi/math_tools.h"
#include "llapi/material.h"
#include "llapi/object.h"
#include "llapi/span_list.h"

TMaterial::TMaterial (void) :
  gTransparent (false),
  tOpacity (1),
  tAmbientReflection (0),
  tDiffuseReflection (0),
  tSpecularReflection (0),
  tIor (1),
  tCaustics (0),
  tSelfEmission (0),
  ptBsdf (NULL) {}


TMaterial::TMaterial (const TMaterial& rktMATERIAL) :
  gTransparent (rktMATERIAL.gTransparent),
  tColor (rktMATERIAL.tColor),
  tOpacity (rktMATERIAL.tOpacity),
  tAmbientReflection (rktMATERIAL.tAmbientReflection),
  tDiffuseReflection (rktMATERIAL.tDiffuseReflection),
  tSpecularReflection (rktMATERIAL.tSpecularReflection),
  tIor (rktMATERIAL.tIor),
  tCaustics (rktMATERIAL.tCaustics),
  tSelfEmission (rktMATERIAL.tSelfEmission),
  ptBsdf (rktMATERIAL.ptBsdf) {}


TMaterial& TMaterial::operator = (const TMaterial& rktMATERIAL)
{

  gTransparent        = rktMATERIAL.gTransparent;
  tColor              = rktMATERIAL.tColor;
  tOpacity            = rktMATERIAL.tOpacity;
  tAmbientReflection  = rktMATERIAL.tAmbientReflection;
  tDiffuseReflection  = rktMATERIAL.tDiffuseReflection;
  tSpecularReflection = rktMATERIAL.tSpecularReflection;
  tIor                = rktMATERIAL.tIor;
  tCaustics           = rktMATERIAL.tCaustics;
  tSelfEmission       = rktMATERIAL.tSelfEmission;
  ptBsdf              = rktMATERIAL.ptBsdf;

  return *this;
  
}  /* operator =() */


TScalar TMaterial::transparency (const TSpanList& rktLIST) const
{

  TScalar        tDistance;
  TScalar        tCos;
  TVector        tDir;
  TSurfaceData   tData1, tData2;
  TScalar        tTransparency = 0;

  if ( rktLIST.empty() ) return 0;

  //
  //  By default, it takes first and last points, and consider the material continuous
  //  and homogeneous between them.
  //
  tData1 = rktLIST.first();
  tData2 = rktLIST.last();

  if ( transparent (tData1) && transparent (tData2) )
  {
    tDistance     = tData2.distance() - tData1.distance();
    tTransparency = exp (-tOpacity * tDistance);
    
    // Check if light is inside object
    if ( tDistance > 0 )
    {
      // Fake caustic idea taken from POV.
      if ( causticExponent (tData1) != 0 )
      {
        tDir = tData1.point() - tData2.point();
        tDir.normalize();

        tCos           = dotProduct (tData1.object()->normal (tData1), tDir);
        tTransparency += pow (fabs (tCos), causticExponent (tData1));
      }
    }
  }

  return tTransparency;

}  /* transparency() */


inline TScalar TMaterial::transparency (TScalar tDIST) const
{

  return exp (-tOpacity * tDIST);

}  /* transparency() */


int TMaterial::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "color" )
  {
    if ( eTYPE == FX_COLOR )
    {
      setColor (*((TColor*) nVALUE.pvValue));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "opacity" )
  {
    if ( eTYPE == FX_REAL )
    {
      setOpacity (nVALUE.dValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "ambient" )
  {
    if ( eTYPE == FX_REAL )
    {
      setAmbientReflection (nVALUE.dValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "diffuse" )
  {
    if ( eTYPE == FX_REAL )
    {
      setDiffuseReflection (nVALUE.dValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "specular" )
  {
    if ( eTYPE == FX_REAL )
    {
      setSpecularReflection (nVALUE.dValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "ior" )
  {
    if ( eTYPE == FX_REAL )
    {
      setIor (nVALUE.dValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "caustics" )
  {
    if ( eTYPE == FX_REAL )
    {
      setCaustics (nVALUE.dValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "emission" )
  {
    if ( eTYPE == FX_REAL )
    {
      setSelfEmission (nVALUE.dValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "bsdf" )
  {
    if ( eTYPE == FX_BSDF )
    {
      setBsdf ((TBsdf*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TProcedural::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TMaterial::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "color" )
  {
    rnVALUE.pvValue = &tColor;
  }
  else if ( rktNAME == "opacity" )
  {
    rnVALUE.dValue = tOpacity;
  }
  else if ( rktNAME == "ambient" )
  {
    rnVALUE.dValue = tAmbientReflection;
  }
  else if ( rktNAME == "diffuse" )
  {
    rnVALUE.dValue = tDiffuseReflection;
  }
  else if ( rktNAME == "specular" )
  {
    rnVALUE.dValue = tSpecularReflection;
  }
  else if ( rktNAME == "ior" )
  {
    rnVALUE.dValue = tIor;
  }
  else if ( rktNAME == "caustics" )
  {
    rnVALUE.dValue = tCaustics;
  }
  else if ( rktNAME == "emission" )
  {
    rnVALUE.dValue = tSelfEmission;
  }
  else if ( rktNAME == "bsdf" )
  {
    rnVALUE.pvValue = ptBsdf;
  }
  else
  {
    return TProcedural::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TMaterial::getAttributeList (TAttributeList& rtLIST) const
{

  TProcedural::getAttributeList (rtLIST);

  rtLIST ["color"]    = FX_COLOR;
  rtLIST ["opacity"]  = FX_REAL;
  rtLIST ["ambient"]  = FX_REAL;
  rtLIST ["diffuse"]  = FX_REAL;
  rtLIST ["specular"] = FX_REAL;
  rtLIST ["ior"]      = FX_REAL;
  rtLIST ["caustics"] = FX_REAL;
  rtLIST ["emission"] = FX_REAL;
  rtLIST ["bsdf"]     = FX_BSDF;

}  /* getAttributeList() */


void TMaterial::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_Material_]" << endl;

  TDebug::_push();

  cerr << TDebug::_indent() <<"Color    : "; tColor.printDebug(); cerr << endl;
  cerr << TDebug::_indent() <<"Ambient  : " << tAmbientReflection << endl;
  cerr << TDebug::_indent() <<"Diffuse  : " << tDiffuseReflection << endl;
  cerr << TDebug::_indent() <<"Specular : " << tSpecularReflection << endl;
  cerr << TDebug::_indent() <<"IOR      : " << tIor << endl;
  cerr << TDebug::_indent() <<"Emission : " << tSelfEmission << endl;

  TDebug::_pop();
  
}  /* printDebug() */

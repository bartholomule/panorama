/*
*  Copyright (C) 1998-2000 Angel Jimenez Jimenez, Carlos Jimenez Moreno and
*                          Jon Frydensbjerg
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
  ptEmission(NULL),
  ptBsdf (NULL) 
{

  ptColor              = new TPattern (0.0);
  ptOpacity            = new TPattern (1.0);
  ptAmbientReflection  = new TPattern (0.0);
  ptDiffuseReflection  = new TPattern (0.0);
  ptSpecularReflection = new TPattern (0.0);
  ptIor                = new TPattern (1.0);
  ptCaustics           = new TPattern (0.0);
  ptPerturbation       = new TPerturbation();
 
}  /* TMaterial() */


TMaterial::TMaterial (TMaterial* ptMATERIAL) :
  TProcedural(*ptMATERIAL),
  ptColor (ptMATERIAL->ptColor),
  ptEmission (ptMATERIAL->ptEmission),  
  ptOpacity (ptMATERIAL->ptOpacity),
  ptAmbientReflection (ptMATERIAL->ptAmbientReflection),
  ptDiffuseReflection (ptMATERIAL->ptDiffuseReflection),
  ptSpecularReflection (ptMATERIAL->ptSpecularReflection),
  ptIor (ptMATERIAL->ptIor),
  ptCaustics (ptMATERIAL->ptCaustics),
  ptPerturbation (ptMATERIAL->ptPerturbation),
  ptBsdf (ptMATERIAL->ptBsdf) {}


TMaterial& TMaterial::operator = (TMaterial* ptMATERIAL)
{

  if( ptMATERIAL != this )
  {
    ptColor              = ptMATERIAL->ptColor;
    ptEmission           = ptMATERIAL->ptEmission;    
    ptOpacity            = ptMATERIAL->ptOpacity;
    ptAmbientReflection  = ptMATERIAL->ptAmbientReflection;
    ptDiffuseReflection  = ptMATERIAL->ptDiffuseReflection;
    ptSpecularReflection = ptMATERIAL->ptSpecularReflection;
    ptIor                = ptMATERIAL->ptIor;
    ptCaustics           = ptMATERIAL->ptCaustics;
    ptPerturbation       = ptMATERIAL->ptPerturbation;
    ptBsdf               = ptMATERIAL->ptBsdf;
    
    TProcedural::operator= (*ptMATERIAL);
  }
  
  return *this;
  
}  /* operator =() */

TColor TMaterial::color (const TSurfaceData& rktDATA) const
{
  return ptColor->color (rktDATA);
}

TColor TMaterial::emission (const TSurfaceData& rktDATA) const
{
  if( ptEmission != NULL )
  {
    return ptEmission->color (rktDATA); 
  }
  return TColor::_black();
}

TScalar TMaterial::transparency (const TSpanList& rktLIST) const
{

  TScalar        tDistance;
  TScalar        tCos;
  TVector        tDir;
  TSurfaceData   tData1, tData2;
  TScalar        tTransparency = 0;

  if ( rktLIST.empty() )
  {
    return 0;
  }

  //
  //  By default, it takes first and last points, and consider the material continuous
  //  and homogeneous between them.
  //
  tData1 = rktLIST.first();
  tData2 = rktLIST.last();

  if ( transparent (tData1) && transparent (tData2) )
  {
    tDistance     = tData2.distance() - tData1.distance();

    //
    // Take opacity value from the first span, but the last span could
    // also have been used as long the homogenity assertion holds.
    // However, this assertion is NOT always true anymore!
    //
    tTransparency = exp (-ptOpacity->scalar (tData1) * tDistance);
    
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


bool TMaterial::initialize (void)
{
  bool val = true;
  assert ( ptBsdf );

  val = val && ptBsdf->initialize();

#define INIT_MAT_PTR_STUFF(x) \
  if ( val && ( (x) != NULL ) ) \
  {                             \
    val = val && (x)->initialize();   \
  }
 
  INIT_MAT_PTR_STUFF(ptColor);
  INIT_MAT_PTR_STUFF(ptEmission);
  INIT_MAT_PTR_STUFF(ptOpacity);
  INIT_MAT_PTR_STUFF(ptAmbientReflection);
  INIT_MAT_PTR_STUFF(ptDiffuseReflection);
  INIT_MAT_PTR_STUFF(ptSpecularReflection);
  INIT_MAT_PTR_STUFF(ptIor);
  INIT_MAT_PTR_STUFF(ptCaustics);
  INIT_MAT_PTR_STUFF(ptPerturbation);
#undef INIT_MAT_PTR_STUFF
  return val && TProcedural::initialize();
}

int TMaterial::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "color" )
  {
    if ( eTYPE == FX_PATTERN )
    {
      setColor ((TPattern*) nVALUE.pvValue);
    }
    else if ( eTYPE == FX_REAL )
    {
      setColor (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setColor (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "emission" )
  {
    if ( eTYPE == FX_PATTERN )
    {
      setEmission ((TPattern*) nVALUE.pvValue);
    }
    else if ( eTYPE == FX_REAL )
    {
      setEmission (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setEmission (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }  
  else if ( rktNAME == "opacity" )
  {
    if ( eTYPE == FX_PATTERN )
    {
      setOpacity ((TPattern*) nVALUE.pvValue);
    } 
    else if ( eTYPE == FX_REAL )
    {
      setOpacity (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setOpacity (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "ambient" )
  {
    if ( eTYPE == FX_PATTERN )
    {
      setAmbientReflection ((TPattern*) nVALUE.pvValue);
    }
    else if ( eTYPE == FX_REAL )
    {
      setAmbientReflection (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setAmbientReflection (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "diffuse" )
  {
    if ( eTYPE == FX_PATTERN )
    {
      setDiffuseReflection ((TPattern*) nVALUE.pvValue);
    }
    else if ( eTYPE == FX_REAL )
    {
      setDiffuseReflection (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setDiffuseReflection (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "specular" )
  {
    if ( eTYPE == FX_PATTERN )
    {
      setSpecularReflection ((TPattern*) nVALUE.pvValue);
    }
    else if ( eTYPE == FX_REAL )
    {
      setSpecularReflection (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setSpecularReflection (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "ior" )
  {
    if ( eTYPE == FX_PATTERN )
    {
      setIor ((TPattern*) nVALUE.pvValue);
    }
    else if ( eTYPE == FX_REAL )
    {
      setIor (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setIor (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "caustics" )
  {
    if ( eTYPE == FX_PATTERN )
    {
      setCaustics ((TPattern*) nVALUE.pvValue);
    }
    else if ( eTYPE == FX_REAL )
    {
      setCaustics (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setCaustics (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "perturb_func" )
  {
    if ( eTYPE == FX_PERTURBATION )
    {
      setPerturbation ((TPerturbation*) nVALUE.pvValue);
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
    rnVALUE.pvValue = ptColor;
  }
  if ( rktNAME == "emission" )
  {
    rnVALUE.pvValue = ptEmission;
  }  
  else if ( rktNAME == "opacity" )
  {
    rnVALUE.pvValue = ptOpacity;
  }
  else if ( rktNAME == "ambient" )
  {
    rnVALUE.pvValue = ptAmbientReflection;
  }
  else if ( rktNAME == "diffuse" )
  {
    rnVALUE.pvValue = ptDiffuseReflection;
  }
  else if ( rktNAME == "specular" )
  {
    rnVALUE.pvValue = ptSpecularReflection;
  }
  else if ( rktNAME == "ior" )
  {
    rnVALUE.pvValue = ptIor;
  }
  else if ( rktNAME == "caustics" )
  {
    rnVALUE.pvValue = ptCaustics;
  } 
  else if ( rktNAME == "perturb_func" )
  {
    rnVALUE.pvValue = ptPerturbation;
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

  rtLIST ["color"]        = FX_PATTERN;
  rtLIST ["emission"]     = FX_PATTERN;
  rtLIST ["opacity"]      = FX_PATTERN;
  rtLIST ["ambient"]      = FX_PATTERN;
  rtLIST ["diffuse"]      = FX_PATTERN;
  rtLIST ["specular"]     = FX_PATTERN;
  rtLIST ["ior"]          = FX_PATTERN;
  rtLIST ["caustics"]     = FX_PATTERN;
  rtLIST ["perturb_func"] = FX_PERTURBATION;
  rtLIST ["bsdf"]         = FX_BSDF;

}  /* getAttributeList() */


void TMaterial::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_Material_]" << endl;

  TDebug::_push();

  cerr << TDebug::_indent() << "Color    : "; ptColor->lastColor().printDebug(); cerr << endl;
  cerr << TDebug::_indent() << "Opacity  : " << ptOpacity->lastScalar() << endl;
  cerr << TDebug::_indent() << "Ambient  : " << ptAmbientReflection->lastScalar() << endl;
  cerr << TDebug::_indent() << "Diffuse  : " << ptDiffuseReflection->lastScalar() << endl;
  cerr << TDebug::_indent() << "Specular : " << ptSpecularReflection->lastScalar() << endl;
  cerr << TDebug::_indent() << "IOR      : " << ptIor->lastScalar() << endl;
  cerr << TDebug::_indent() << "Caustics : " << ptCaustics->lastScalar() << endl;
  cerr << TDebug::_indent() << "Emission : ";
  if( ptEmission != NULL )
  {
    ptEmission->lastColor().printDebug();
  }
  else
  {
    cerr << "NULL";
  }
  cerr << endl;

  TDebug::_pop();
  
}  /* printDebug() */

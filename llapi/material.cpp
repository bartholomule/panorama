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

#include "llapi/warning_eliminator.h"
#include <cassert>
#include "llapi/math_tools.h"
#include "llapi/material.h"
#include "llapi/object.h"
#include "llapi/span_list.h"
#include "llapi/attribute.h"
#include "llapi/object_required.h"

TMaterial::TMaterial (void) :
  ptEmission(NULL),
  ptBsdf (NULL) 
{

  ptColor              = (magic_pointer<TPattern>)new TPattern (0.0);
  ptOpacity            = (magic_pointer<TPattern>)new TPattern (1.0);
  ptAmbientReflection  = (magic_pointer<TPattern>)new TPattern (0.0);
  ptDiffuseReflection  = (magic_pointer<TPattern>)new TPattern (0.0);
  ptSpecularReflection = (magic_pointer<TPattern>)new TPattern (0.0);
  ptIor                = (magic_pointer<TPattern>)new TPattern (1.0);
  ptCaustics           = (magic_pointer<TPattern>)new TPattern (0.0);
  ptPerturbation       = (magic_pointer<TPerturbation>)new TPerturbation();
 
}  /* TMaterial() */


TMaterial::TMaterial (TMaterial& rtMATERIAL) :
  TProcedural(rtMATERIAL),
  ptColor (rtMATERIAL.ptColor),
  ptEmission (rtMATERIAL.ptEmission),  
  ptOpacity (rtMATERIAL.ptOpacity),
  ptAmbientReflection (rtMATERIAL.ptAmbientReflection),
  ptDiffuseReflection (rtMATERIAL.ptDiffuseReflection),
  ptSpecularReflection (rtMATERIAL.ptSpecularReflection),
  ptIor (rtMATERIAL.ptIor),
  ptCaustics (rtMATERIAL.ptCaustics),
  ptPerturbation (rtMATERIAL.ptPerturbation),
  ptBsdf (rtMATERIAL.ptBsdf) {}


TMaterial& TMaterial::operator = (TMaterial& rtMATERIAL)
{

  if( &rtMATERIAL != this )
  {
    ptColor              = rtMATERIAL.ptColor;
    ptEmission           = rtMATERIAL.ptEmission;    
    ptOpacity            = rtMATERIAL.ptOpacity;
    ptAmbientReflection  = rtMATERIAL.ptAmbientReflection;
    ptDiffuseReflection  = rtMATERIAL.ptDiffuseReflection;
    ptSpecularReflection = rtMATERIAL.ptSpecularReflection;
    ptIor                = rtMATERIAL.ptIor;
    ptCaustics           = rtMATERIAL.ptCaustics;
    ptPerturbation       = rtMATERIAL.ptPerturbation;
    ptBsdf               = rtMATERIAL.ptBsdf;
    
    TProcedural::operator=(rtMATERIAL);
  }
  
  return *this;
  
}  /* operator =() */

TColor TMaterial::color (const TSurfaceData& rktDATA) const
{
  return ptColor->color (rktDATA);
}

TColor TMaterial::emission (const TSurfaceData& rktDATA) const
{
  if( ptEmission )
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
  assert ( !!ptBsdf );

  val = val && ptBsdf->initialize();

#define INIT_MAT_PTR_STUFF(x) \
  if ( val && ( !!(x) ) ) \
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
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_PATTERN )
    {
      setColor (((TPattern*) nVALUE.pvValue)->clone_new());
    }
    else if ( eTYPE == FX_REAL )
    {
      setColor (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setColor (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      setColor (pat->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "emission" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_PATTERN )
    {
      setEmission (((TPattern*) nVALUE.pvValue)->clone_new());
    }
    else if ( eTYPE == FX_REAL )
    {
      setEmission (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setEmission (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      setEmission (pat->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }  
  else if ( rktNAME == "opacity" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_PATTERN )
    {
      setOpacity (((TPattern*) nVALUE.pvValue)->clone_new());
    } 
    else if ( eTYPE == FX_REAL )
    {
      setOpacity (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setOpacity (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      setOpacity (pat->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "ambient" )
  {
#if !defined(NEW_ATTRIBUTES)    
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
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      setAmbientReflection (pat->tValue);
    }    
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "diffuse" )
  {
#if !defined(NEW_ATTRIBUTES)    
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
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      setDiffuseReflection (pat->tValue);
    }    
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "specular" )
  {
#if !defined(NEW_ATTRIBUTES)    
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
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      setSpecularReflection (pat->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "ior" )
  {
#if !defined(NEW_ATTRIBUTES)
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
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      setIor (pat->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "caustics" )
  {
#if !defined(NEW_ATTRIBUTES)    
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
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      setCaustics (pat->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "perturb_func" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_PERTURBATION )
    {
      setPerturbation ((TPerturbation*) nVALUE.pvValue);
    }
#else
    magic_pointer<TAttribPerturbation> pert = get_perturbation(nVALUE);
    if( !!pert )
    {
      setPerturbation (pert->tValue);
    }    
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "bsdf" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_BSDF )
    {
      setBsdf ((TBsdf*) nVALUE.pvValue);
    }
#else
    magic_pointer<TAttribBsdf> bsdf = get_bsdf(nVALUE);
    if( !!bsdf )
    {
      setBsdf (bsdf->tValue);
    }    
#endif
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
  
#if !defined(NEW_ATTRIBUTES)
  if ( rktNAME == "color" )
  {
    rnVALUE.pvValue = ptColor.get_pointer();
  }
  if ( rktNAME == "emission" )
  {
    rnVALUE.pvValue = ptEmission.get_pointer();
  }  
  else if ( rktNAME == "opacity" )
  {
    rnVALUE.pvValue = ptOpacity.get_pointer();
  }
  else if ( rktNAME == "ambient" )
  {
    rnVALUE.pvValue = ptAmbientReflection.get_pointer();
  }
  else if ( rktNAME == "diffuse" )
  {
    rnVALUE.pvValue = ptDiffuseReflection.get_pointer();
  }
  else if ( rktNAME == "specular" )
  {
    rnVALUE.pvValue = ptSpecularReflection.get_pointer();
  }
  else if ( rktNAME == "ior" )
  {
    rnVALUE.pvValue = ptIor.get_pointer();
  }
  else if ( rktNAME == "caustics" )
  {
    rnVALUE.pvValue = ptCaustics.get_pointer();
  } 
  else if ( rktNAME == "perturb_func" )
  {
    rnVALUE.pvValue = ptPerturbation.get_pointer();
  }
  else if ( rktNAME == "bsdf" )
  {
    rnVALUE.pvValue = ptBsdf.get_pointer();
  }
#else
  if ( rktNAME == "color" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern(ptColor);
  }
  if ( rktNAME == "emission" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (ptEmission);
  }  
  else if ( rktNAME == "opacity" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (ptOpacity);
  }
  else if ( rktNAME == "ambient" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (ptAmbientReflection);
  }
  else if ( rktNAME == "diffuse" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (ptDiffuseReflection);
  }
  else if ( rktNAME == "specular" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (ptSpecularReflection);
  }
  else if ( rktNAME == "ior" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (ptIor);
  }
  else if ( rktNAME == "caustics" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (ptCaustics);
  } 
  else if ( rktNAME == "perturb_func" )
  {
    rnVALUE = (user_arg_type)new TAttribPerturbation (ptPerturbation);
  }
  else if ( rktNAME == "bsdf" )
  {
    rnVALUE = (user_arg_type)new TAttribBsdf (ptBsdf);
  }  
#endif
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


void TMaterial::printDebug (const string& indent) const
{

  GOM.debug() << indent << "[_Material_]" << endl;
  GOM.debug() << indent << "FIX THIS!  It does not print out patterns correctly (fix pattern too)" << endl;

  string new_indent = TDebug::Indent(indent);
  
  GOM.debug() << new_indent << "Color    : "; ptColor->lastColor().printDebug(new_indent); GOM.debug() << endl;
  GOM.debug() << new_indent << "Opacity  : " << ptOpacity->lastScalar() << endl;
  GOM.debug() << new_indent << "Ambient  : " << ptAmbientReflection->lastScalar() << endl;
  GOM.debug() << new_indent << "Diffuse  : " << ptDiffuseReflection->lastScalar() << endl;
  GOM.debug() << new_indent << "Specular : " << ptSpecularReflection->lastScalar() << endl;
  GOM.debug() << new_indent << "IOR      : " << ptIor->lastScalar() << endl;
  GOM.debug() << new_indent << "Caustics : " << ptCaustics->lastScalar() << endl;
  GOM.debug() << new_indent << "Emission : ";
  if( ptEmission  )
  {
    ptEmission->lastColor().printDebug(new_indent);
  }
  else
  {
    GOM.debug() << "NULL";
  }
  GOM.debug() << endl << indent << "." << endl;

}  /* printDebug() */


TUserFunctionMap TMaterial::getUserFunctions()
{
  TUserFunctionMap ufm = TProcedural::getUserFunctions();


  ufm["getBsdf"]               = create_user_function(this,&TMaterial::bsdf);
  ufm["getPerturbation"]       = create_user_function(this,&TMaterial::perturbation);

  // A variable to allow the correct function (most of these are overloaded).
  pattern_pointer (TMaterial::*fptr)(void) const;
  fptr = &TMaterial::color;
  ufm["getColor"]              = create_user_function(this,fptr);
  fptr = &TMaterial::emission;  
  ufm["getEmission"]           = create_user_function(this,fptr);
  fptr = &TMaterial::opacity;
  ufm["getOpacity"]            = create_user_function(this,fptr);
  fptr = &TMaterial::ambientReflection;  
  ufm["getAmbientReflection"]  = create_user_function(this,fptr);
  fptr = &TMaterial::diffuseReflection;  
  ufm["getDiffuseReflection"]  = create_user_function(this,fptr);
  fptr = &TMaterial::specularReflection;  
  ufm["getSpecularReflection"] = create_user_function(this,fptr);
  fptr = &TMaterial::ior;  
  ufm["getIOR"]                = create_user_function(this,fptr);
  fptr = &TMaterial::caustics;  
  ufm["getCaustics"]           = create_user_function(this,fptr);


  ufm["setBsdf"]               = create_user_function(this,&TMaterial::setBsdf);
  ufm["setPerturbation"]       = create_user_function(this,&TMaterial::setPerturbation);  
  
  ufm["setColor"]              = create_user_function(this,&TMaterial::setColor);
  ufm["setEmission"]           = create_user_function(this,&TMaterial::setEmission);
  ufm["setOpacity"]            = create_user_function(this,&TMaterial::setOpacity);
  ufm["setAmbientReflection"]  = create_user_function(this,&TMaterial::setAmbientReflection);
  ufm["setDiffuseReflection"]  = create_user_function(this,&TMaterial::setDiffuseReflection);
  ufm["setSpecularReflection"] = create_user_function(this,&TMaterial::setSpecularReflection);
  ufm["setIOR"]                = create_user_function(this,&TMaterial::setIor);
  ufm["setCaustics"]           = create_user_function(this,&TMaterial::setCaustics);

  ufm["className"]             = create_user_function(this,&TMaterial::className);

  return ufm;
}

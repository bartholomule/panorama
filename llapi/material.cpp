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
#include "llapi/warning_eliminator.h"
#include "llapi/math_tools.h"
#include "llapi/material.h"
#include "llapi/object.h"
#include "llapi/span_list.h"
#include "llapi/attribute.h"
#include "llapi/object_required.h"

namespace panorama
{

  TMaterial::TMaterial (void) :
    ptEmission(NULL),
    ptBsdf (NULL)
  {

    ptColor              = (rc_pointer<TPattern>)new TPattern (0.0);
    ptOpacity            = (rc_pointer<TPattern>)new TPattern (1.0);
    ptAmbientReflection  = (rc_pointer<TPattern>)new TPattern (0.0);
    ptDiffuseReflection  = (rc_pointer<TPattern>)new TPattern (0.0);
    ptSpecularReflection = (rc_pointer<TPattern>)new TPattern (0.0);
    ptIor                = (rc_pointer<TPattern>)new TPattern (1.0);
    ptCaustics           = (rc_pointer<TPattern>)new TPattern (0.0);
    ptPerturbation       = (rc_pointer<TPerturbation>)new TPerturbation();

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

#define INIT_MAT_PTR_STUFF(x)                   \
    if ( val && ( !!(x) ) )                     \
    {                                           \
      val = val && (x)->initialize();           \
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

  int TMaterial::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
  {

    if ( rktNAME == "color" )
    {
      rc_pointer<TAttribPattern> pat = get_pattern(nVALUE);
      if( !!pat )
      {
        setColor (pat->tValue);
      }
      else
      {
        return FX_ATTRIB_WRONG_TYPE;
      }
    }
    else if ( rktNAME == "emission" )
    {
      rc_pointer<TAttribPattern> pat = get_pattern(nVALUE);
      if( !!pat )
      {
        setEmission (pat->tValue);
      }
      else
      {
        return FX_ATTRIB_WRONG_TYPE;
      }
    }
    else if ( rktNAME == "opacity" )
    {
      rc_pointer<TAttribPattern> pat = get_pattern(nVALUE);
      if( !!pat )
      {
        setOpacity (pat->tValue);
      }
      else
      {
        return FX_ATTRIB_WRONG_TYPE;
      }
    }
    else if ( rktNAME == "ambient" )
    {
      rc_pointer<TAttribPattern> pat = get_pattern(nVALUE);
      if( !!pat )
      {
        setAmbientReflection (pat->tValue);
      }
      else
      {
        return FX_ATTRIB_WRONG_TYPE;
      }
    }
    else if ( rktNAME == "diffuse" )
    {
      rc_pointer<TAttribPattern> pat = get_pattern(nVALUE);
      if( !!pat )
      {
        setDiffuseReflection (pat->tValue);
      }
      else
      {
        return FX_ATTRIB_WRONG_TYPE;
      }
    }
    else if ( rktNAME == "specular" )
    {
      rc_pointer<TAttribPattern> pat = get_pattern(nVALUE);
      if( !!pat )
      {
        setSpecularReflection (pat->tValue);
      }
      else
      {
        return FX_ATTRIB_WRONG_TYPE;
      }
    }
    else if ( rktNAME == "ior" )
    {
      rc_pointer<TAttribPattern> pat = get_pattern(nVALUE);
      if( !!pat )
      {
        setIor (pat->tValue);
      }
      else
      {
        return FX_ATTRIB_WRONG_TYPE;
      }
    }
    else if ( rktNAME == "caustics" )
    {
      rc_pointer<TAttribPattern> pat = get_pattern(nVALUE);
      if( !!pat )
      {
        setCaustics (pat->tValue);
      }
      else
      {
        return FX_ATTRIB_WRONG_TYPE;
      }
    }
    else if ( rktNAME == "perturb_func" )
    {
      rc_pointer<TAttribPerturbation> pert = get_perturbation(nVALUE);
      if( !!pert )
      {
        setPerturbation (pert->tValue);
      }
      else
      {
        return FX_ATTRIB_WRONG_TYPE;
      }
    }
    else if ( rktNAME == "bsdf" )
    {
      rc_pointer<TAttribBsdf> bsdf = get_bsdf(nVALUE);
      if( !!bsdf )
      {
        setBsdf (bsdf->tValue);
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


  int TMaterial::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
  {
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


  std::string TMaterial::internalMembers(const Indentation& indent, StringDumpable::PrefixType prefix) const;
  {
    std::string tag = indent.level();
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag = indent.level() + TMaterial::name() + "::";
    }

    Indentation nextIndent = indent.nextLevel();
    std::string retval;

    retval += tag + "color=" + toString(ptColor, nextIndent, prefix) + "\n";
    retval += tag + "emission=" + toString(ptEmission, nextIndent, prefix) + "\n";
    retval += tag + "opacity=" + toString(ptOpacity, nextIndent, prefix) + "\n";
    retval += tag + "ambientReflection=" + toString(ptAmbientReflection, nextIndent, prefix) + "\n";
    retval += tag + "diffuseReflection=" + toString(ptDiffuseReflection, nextIndent, prefix) + "\n";
    retval += tag + "specularReflection=" + toString(ptSpecularReflection, nextIndent, prefix) + "\n";
    retval += tag + "ior=" + toString(ptIor, nextIndent, prefix) + "\n";
    retval += tag + "caustics=" + toString(ptCaustics, nextIndent, prefix) + "\n";
    retval += tag + "perturbation=" + toString(ptPerturbation, nextIndent, prefix) + "\n";
    retval += tag + "bsdf=" + toString(ptBsdf, nextIndent, prefix) + "\n";

    return retval;
  }

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

} // end namespace panorama

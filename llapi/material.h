/*
*  Copyright (C) 1998-2001 Angel Jimenez Jimenez, Carlos Jimenez Moreno,
*                          Jon Frydensbjerg and Kevin Harris
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

#ifndef PANORAMA_MATERIAL_H_INCLUDED
#define PANORAMA_MATERIAL_H_INCLUDED

#include "llapi/span_list.h"
#include "llapi/bsdf.h"
#include "llapi/procedural.h"
#include "llapi/pattern.h"
#include "llapi/perturbation.h"
#include "generic/rc_pointer.hpp"

namespace panorama
{
  class TMaterial : public TProcedural
  {

  public:
    typedef rc_pointer<TPattern> pattern_pointer;

  protected:

    pattern_pointer ptColor;
    pattern_pointer ptEmission;
    pattern_pointer ptOpacity;
    pattern_pointer ptAmbientReflection;
    pattern_pointer ptDiffuseReflection;
    pattern_pointer ptSpecularReflection;
    pattern_pointer ptIor;
    pattern_pointer ptCaustics;
    rc_pointer<TPerturbation> ptPerturbation;
    rc_pointer<TBsdf> ptBsdf;

  public:

    TMaterial (void);
    TMaterial (TMaterial& ptMATERIAL);

    TMaterial& operator = (TMaterial& ptMATERIAL);

    bool transparent (const TSurfaceData& rktDATA) const { return ( opacity (rktDATA) < 1 ); }
    TScalar transparency (const TSpanList& rktLIST) const;
    TColor color (const TSurfaceData& rktDATA) const;
    TColor emission (const TSurfaceData& rktDATA) const;
    TScalar opacity (const TSurfaceData& rktDATA) const { return ptOpacity->scalar (rktDATA); }
    TScalar ambientReflection (const TSurfaceData& rktDATA) const { return ptAmbientReflection->scalar (rktDATA); }
    TScalar diffuseReflection (const TSurfaceData& rktDATA) const { return ptDiffuseReflection->scalar (rktDATA); }
    TScalar specularReflection (const TSurfaceData& rktDATA) const { return ptSpecularReflection->scalar (rktDATA); }
    TScalar ior (const TSurfaceData& rktDATA) const { return ptIor->scalar (rktDATA); }
    TScalar causticExponent (const TSurfaceData& rktDATA) const { return ptCaustics->scalar (rktDATA); }

    const rc_pointer<TBsdf> bsdf (void) const { return ptBsdf; }

    virtual bool initialize (void);

    AttributeErrorCode setAttribute (const std::string& rktNAME, Attribute nVALUE);
    AttributeErrorCode getAttribute (const std::string& rktNAME, Attribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    pattern_pointer color (void) const { return ptColor; }
    pattern_pointer emission (void) const { return ptEmission; }
    pattern_pointer opacity (void) const { return ptOpacity; }
    pattern_pointer ambientReflection (void) const { return ptAmbientReflection; }
    pattern_pointer diffuseReflection (void) const { return ptDiffuseReflection; }
    pattern_pointer specularReflection (void) const { return ptSpecularReflection; }
    pattern_pointer ior (void) const { return ptIor; }
    pattern_pointer caustics (void) const { return ptCaustics; }
    const rc_pointer<TPerturbation> perturbation (void) const { return ptPerturbation; }

    void setColor (pattern_pointer ptPATTERN) { ptColor = ptPATTERN; }
    void setEmission (pattern_pointer ptPATTERN) { ptEmission = ptPATTERN; }
    void setOpacity (pattern_pointer ptPATTERN) { ptOpacity = ptPATTERN; }
    void setAmbientReflection (pattern_pointer ptPATTERN) { ptAmbientReflection = ptPATTERN; }
    void setDiffuseReflection (pattern_pointer ptPATTERN) { ptDiffuseReflection = ptPATTERN; }
    void setSpecularReflection (pattern_pointer ptPATTERN) { ptSpecularReflection = ptPATTERN; }
    void setIor (pattern_pointer ptPATTERN) { ptIor = ptPATTERN; }
    void setCaustics (pattern_pointer ptPATTERN) { ptCaustics = ptPATTERN; }
    void setPerturbation (rc_pointer<TPerturbation> ptPERTURBATION) { ptPerturbation = ptPERTURBATION; }
    void setBsdf (rc_pointer<TBsdf> ptBSDF) { ptBsdf = ptBSDF; }

    TVector perturbNormal (const TSurfaceData& rktDATA) const { return ptPerturbation->perturbNormal (rktDATA); }

    EClass classType (void) const { return FX_MATERIAL_CLASS; }
    virtual std::string name (void) const { return "Material"; }
    virtual std::string internalMembers(const Indentation& indent, StringDumpable::PrefixType prefix) const;

    virtual TUserFunctionMap getUserFunctions();

  };  /* class TMaterial */
} // end namespace panorama

#endif  /* PANORAMA_MATERIAL_H_INCLUDED */





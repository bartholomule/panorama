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

#ifndef _MATERIAL__
#define _MATERIAL__

#include "llapi/span_list.h"
#include "llapi/bsdf.h"
#include "llapi/procedural.h"
#include "llapi/pattern.h"
#include "llapi/perturbation.h"

class TMaterial : public TProcedural
{

  protected:

    TPattern*       ptColor;
    TPattern*       ptEmission;  
    TPattern*       ptOpacity;
    TPattern*       ptAmbientReflection;
    TPattern*       ptDiffuseReflection;
    TPattern*       ptSpecularReflection;
    TPattern*       ptIor;
    TPattern*       ptCaustics;
    TPerturbation*  ptPerturbation;
    TBsdf*          ptBsdf;

  public:

    TMaterial (void);
    TMaterial (TMaterial* ptMATERIAL);

    TMaterial& operator = (TMaterial* ptMATERIAL);

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

    TBsdf* bsdf (void) const { return ptBsdf; }

  virtual bool initialize (void);
    
    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    TPattern* color (void) const { return ptColor; }
    TPattern* emission (void) const { return ptEmission; }  
    TPattern* opacity (void) const { return ptOpacity; }
    TPattern* ambientReflection (void) const { return ptAmbientReflection; }
    TPattern* diffuseReflection (void) const { return ptDiffuseReflection; }
    TPattern* specularReflection (void) const { return ptSpecularReflection; }
    TPattern* ior (void) const { return ptIor; }
    TPattern* caustics (void) const { return ptCaustics; }
    TPerturbation* perturbation (void) const { return ptPerturbation; }

    void setColor (TPattern* ptPATTERN) { ptColor = ptPATTERN; }
    void setEmission (TPattern* ptPATTERN) { ptEmission = ptPATTERN; }  
    void setOpacity (TPattern* ptPATTERN) { ptOpacity = ptPATTERN; }
    void setAmbientReflection (TPattern* ptPATTERN) { ptAmbientReflection = ptPATTERN; }
    void setDiffuseReflection (TPattern* ptPATTERN) { ptDiffuseReflection = ptPATTERN; }
    void setSpecularReflection (TPattern* ptPATTERN) { ptSpecularReflection = ptPATTERN; }
    void setIor (TPattern* ptPATTERN) { ptIor = ptPATTERN; }
    void setCaustics (TPattern* ptPATTERN) { ptCaustics = ptPATTERN; }
    void setPerturbation (TPerturbation* ptPERTURBATION) { ptPerturbation = ptPERTURBATION; }
    void setBsdf (TBsdf* ptBSDF) { ptBsdf = ptBSDF; }

    TVector perturbNormal (const TSurfaceData& rktDATA) const { return ptPerturbation->perturbNormal (rktDATA); }
                                
    void printDebug (void) const;

    EClass classType (void) const { return FX_MATERIAL_CLASS; }
    string className (void) const { return "Material"; }

};  /* class TMaterial */

#endif  /* _MATERIAL__ */





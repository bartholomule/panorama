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

#ifndef _MATERIAL__
#define _MATERIAL__

#include "llapi/span_list.h"
#include "llapi/bsdf.h"
#include "llapi/procedural.h"

class TMaterial : public TProcedural
{

  protected:

    bool      gTransparent;
    TColor    tColor;
    TScalar   tOpacity;
    TScalar   tAmbientReflection;
    TScalar   tDiffuseReflection;
    TScalar   tSpecularReflection;
    TScalar   tIor;
    TScalar   tCaustics;
    TScalar   tSelfEmission;
    TBsdf*    ptBsdf;

  public:

    TMaterial (void);
    TMaterial (const TMaterial& rktMATERIAL);

    TMaterial& operator = (const TMaterial& rktMATERIAL);

    virtual bool transparent (const TSurfaceData& rktDATA) const { return gTransparent; }
    virtual TScalar transparency (const TSpanList& rktLIST) const;
    virtual TScalar transparency (TScalar tDIST) const;
    virtual TColor color (const TSurfaceData& rktDATA) const { return tColor; }
    virtual TScalar ambientReflection (const TSurfaceData& rktDATA) const { return tAmbientReflection; }
    virtual TScalar diffuseReflection (const TSurfaceData& rktDATA) const { return tDiffuseReflection; }
    virtual TScalar specularReflection (const TSurfaceData& rktDATA) const { return tSpecularReflection; }
    virtual TScalar ior (const TSurfaceData& rktDATA) const { return tIor; }
    virtual TScalar causticExponent (const TSurfaceData& rktDATA) const { return tCaustics; }
    virtual TScalar selfEmission (void) { return tSelfEmission; }

    TBsdf* bsdf (void) const { return ptBsdf; }

    virtual void initialize (void)
    {
      assert ( ptBsdf );

      ptBsdf->initialize();
    }
    
    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    virtual void setColor (const TColor& rktCOLOR)
    {
      tColor = rktCOLOR;
    }
    virtual void setOpacity (TScalar tVALUE)
    {
      tOpacity     = tVALUE;
      gTransparent = ( tOpacity < 1 );
    }
    virtual void setAmbientReflection (TScalar tVALUE) { tAmbientReflection = tVALUE; }
    virtual void setDiffuseReflection (TScalar tVALUE) { tDiffuseReflection = tVALUE; }
    virtual void setSpecularReflection (TScalar tVALUE) { tSpecularReflection = tVALUE; }
    virtual void setIor (TScalar tVALUE) { tIor = tVALUE; }
    virtual void setBsdf (TBsdf* ptBSDF) { ptBsdf = ptBSDF; }
    virtual void setCaustics (TScalar tCAUSTICS) { tCaustics = tCAUSTICS; }
    virtual void setSelfEmission (TScalar tSELF_EMISSION) { tSelfEmission = tSELF_EMISSION; }

    virtual TVector perturbNormal (const TSurfaceData& rktDATA) const { return rktDATA.normal(); }
                                
    void printDebug (void) const;

    EClass classType (void) const { return FX_MATERIAL_CLASS; }
    string className (void) const { return "Material"; }

};  /* class TMaterial */

#endif  /* _MATERIAL__ */

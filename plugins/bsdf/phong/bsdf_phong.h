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

#ifndef _BSDF_PHONG__
#define _BSDF_PHONG__

#include "llapi/bsdf.h"
#include "llapi/material.h"
#include "llapi/vector_tools.h"
#include "hlapi/plugin_manager.h"

class TBsdfPhong : public TBsdf
{

  protected:

    TScalar   tPhongExp;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TColor evaluateReflection (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TScalar tCOSNL, TColor tRAD) const;

    // [_TODO_] This implementation is for Lambertian reflection. It should be replaced.
    void getRayDirection (const TSurfaceData& rktDATA, const TVector& rktREFLECTED, TVector& rtDIR) const
    {
      TVector   v = RandomVectorInSphere();

      rtDIR = ( dotProduct (v, rktDATA.normal()) > 0 ) ? v : -v;
    }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;
    
    void setPhongExp (TScalar tEXP) { tPhongExp = tEXP; }

    string className (void) const { return "BsdfPhong"; }

};  /* class TBsdfPhong */

extern TBsdfPhong   tDefaultBsdf;

inline TColor TBsdfPhong::evaluateReflection (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TScalar tCOSNL, TColor tRAD) const
{
  
  TScalar      tCosNH;
  TVector      tHalfway = rktLIGHT - rktDATA.ray().direction();
  TMaterial*   ptMat    = rktDATA.object()->material();
  TColor       tColor   = ptMat->color (rktDATA);
  TScalar      kd       = ptMat->diffuseReflection (rktDATA);
  TScalar      ks       = ptMat->specularReflection (rktDATA);

  tHalfway.normalize();

  tCosNH = dotProduct (rktDATA.normal(), tHalfway);

  return (tColor * kd * tCOSNL) + (TColor::_white() * ks * pow (tCosNH, tPhongExp));

}  /* evaluateReflection() */

#endif  /* _BSDF_PHONG__ */

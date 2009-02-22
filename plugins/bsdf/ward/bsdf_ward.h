/*
*  Copyright (C) 1999-2000 Jon Frydensbjerg
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

#ifndef _BSDF_WARD__
#define _BSDF_WARD__

#include "llapi/bsdf.h"
#include "llapi/material.h"
#include "llapi/math_tools.h"
#include "llapi/vector_tools.h"
#include "hlapi/plugin_manager.h"

class TBsdfWard : public TBsdf
{

  public:
    typedef magic_pointer<TPattern> PTPattern;
  protected:

    PTPattern   ptStandardDeviation_x;
    PTPattern   ptStandardDeviation_y;
    PTPattern   ptSpecularColor;

  protected:

    inline TScalar sqr (TScalar X) const { return (X * X); }

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);
 
    TBsdfWard (void);

    TColor evaluateReflection (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TScalar tCOSNL, TColor tRAD) const;

    void getRayDirection (const TSurfaceData& rktDATA, const TVector& rktREFLECTED, TVector& rtDIR) const
    {
      TVector   v = RandomVectorInSphere();

      rtDIR = ( dotProduct (v, rktDATA.normal()) > 0 ) ? v : -v;
    }

    int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setSpecularColor (PTPattern ptCOLOR) { ptSpecularColor = ptCOLOR; }

    std::string className (void) const { return "BsdfWard"; }

    TBsdfWard* clone_new() const { return new TBsdfWard(*this); }
  
};  /* class TBsdfWard */


inline TColor TBsdfWard::evaluateReflection (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TScalar tCOSNL, TColor tRAD) const
{
  
  TScalar      tCosNH;
  TScalar      tCosVH;
  TScalar      tCosNV;
  TVector      tHalfway = rktLIGHT - rktDATA.ray().direction();
  TVector      tTangent_x;
  TVector      tTangent_y;
  TVector      tTangent_z;
  magic_pointer<TMaterial> ptMat = rktDATA.object()->material();
  TColor       tColor   = ptMat->color (rktDATA);
  TScalar      kd       = ptMat->diffuseReflection (rktDATA);
  TScalar      ks       = ptMat->specularReflection (rktDATA);
  TScalar      dx, dy;
  TScalar      tGlare;
  TScalar      tExp;
  TScalar      tStandardDeviation_x = ptStandardDeviation_x->scalar (rktDATA);
  TScalar      tStandardDeviation_y = ptStandardDeviation_y->scalar (rktDATA);
  TColor       tSpecColor = ptSpecularColor->color (rktDATA);

  tHalfway.normalize();

  tCosNV = dotProduct (rktDATA.normal(), -rktDATA.ray().direction());
  tCosNH = dotProduct (rktDATA.normal(), tHalfway);
  tCosVH = dotProduct (-rktDATA.ray().direction(), tHalfway);

  //
  // Obtain tangent vectors (z = normal - x/y = tangents)
  // 

  tTangent_z = rktDATA.normal();

  tTangent_x = crossProduct (tTangent_z, TVector (0.0, 1.0, 0.0));
  
  if ( tTangent_x.norm() < FX_EPSILON )
  {
    tTangent_x.set (0.0, 1.0, 0.0);

    if ( fabs (tTangent_z.y() - 1.0) < FX_EPSILON )
    {
      tTangent_z.set (0.0, 1.0, 0.0);
    }
    else
    {
      tTangent_z.set (0.0, -1.0, 0.0);
    }
  }

  tTangent_x.normalize();

  tTangent_y = crossProduct (tTangent_x, tTangent_z);

  //
  // Evaluate Ward's BRDF
  // 

  dx = dotProduct (tHalfway, tTangent_x) / tStandardDeviation_x;
  dy = dotProduct (tHalfway, tTangent_y) / tStandardDeviation_y;

  tGlare = 1.0 / (sqrt (tCosNV * tCOSNL) * 2.0 * tStandardDeviation_x * tStandardDeviation_y);

  tExp   = exp (-2.0 * (sqr (dx) + sqr (dy)) / (1.0 + tCosNH));

  return (tColor * kd) + (tSpecColor * ks * tGlare * tExp);

}  /* evaluateReflection() */

#endif  /* _BSDF_WARD__ */





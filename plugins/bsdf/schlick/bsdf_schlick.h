/*
*  Copyright (C) 1999 Jon Frydensbjerg
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

#ifndef _BSDF_SCHLICK__
#define _BSDF_SCHLICK__

#include "llapi/bsdf.h"
#include "llapi/material.h"
#include "llapi/math_tools.h"
#include "llapi/mat_utils.h"
#include "llapi/vector.h"
#include "hlapi/plugin_manager.h"

class TBsdfSchlick : public TBsdf
{

  protected:

    TScalar   tRoughness;
    TScalar   tIsotropy;
    TColor    tReflectance;

    TScalar   A;
    TScalar   B;
    TScalar   tInvRoughness;
    TScalar   tRoughnessInv;
    TScalar   tIsotropy_2;
    TScalar   tInvIsotropy_2;
    TScalar   tRed,   tInvRed;
    TScalar   tGreen, tInvGreen;
    TScalar   tBlue,  tInvBlue;

  protected:

    inline TScalar sqr (TScalar X) const { return (X * X); }

    void setupBsdf (void);

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);
 
    TBsdfSchlick (void);

    TScalar computeFresnel (TScalar& rtCOSVH, const TScalar& rktFRESNEL, const TScalar& rktINVFRESNEL) const;
    TScalar computeZenith (TScalar& rtCOSNH) const;
    TScalar computeAzimuth (TScalar& rtCOSTI) const;
    TScalar computeSmith (TScalar& rtCOS) const;

    TColor computeFresnelColor (TScalar& rtCOSVH) const;

    TColor evaluateReflection (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TScalar tCOSNL, TColor tRAD) const;

    void getRayDirection (const TSurfaceData& rktDATA, const TVector& rktREFLECTED, TVector& rtDIR) const
    {
      TVector   v = RandomVectorInSphere();

      rtDIR = ( dotProduct (v, rktDATA.normal()) > 0 ) ? v : -v;
    }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    inline TScalar getA (void) const { return A; }
    inline TScalar getB (void) const { return B; }

    string className (void) const { return "BsdfSchlick"; }

};  /* class TBsdfSchlick */


inline void TBsdfSchlick::setupBsdf (void)
{

  tRoughnessInv  =  tRoughness - 1.0;
  tInvRoughness  = -tRoughness + 1.0;

  tIsotropy_2    =  sqr (tIsotropy);
  tInvIsotropy_2 = -tIsotropy_2 + 1.0;

  tRed   = tReflectance.red();
  tGreen = tReflectance.green();
  tBlue  = tReflectance.blue();

  tInvRed   = 1.0 - tRed;
  tInvGreen = 1.0 - tGreen;
  tInvBlue  = 1.0 - tBlue;

  B = 4.0 * tRoughness * (1.0 - tRoughness);

  if ( tRoughness < 0.5 ) 
  {
    A = 0.0;
  }
  else 
  {
    A = 1.0 - B;
  }

}  /* setupBsdf() */


inline TScalar TBsdfSchlick::computeFresnel (TScalar& rtCOSVH, const TScalar& rktFRESNEL, const TScalar& rktINVFRESNEL) const
{

  TScalar tInvCosVH;

  tInvCosVH = 1.0 - rtCOSVH;

  return rktFRESNEL + rktINVFRESNEL * sqr (sqr (tInvCosVH)) * tInvCosVH;

}  /* computeFresnel() */


inline TColor TBsdfSchlick::computeFresnelColor (TScalar& rtCOSVH) const
{

  TScalar   tSred;
  TScalar   tSgreen;
  TScalar   tSblue;

  tSred   = computeFresnel (rtCOSVH, tRed,   tInvRed);
  tSgreen = computeFresnel (rtCOSVH, tGreen, tInvGreen);
  tSblue  = computeFresnel (rtCOSVH, tBlue,  tInvBlue);

  return TColor (tSred, tSgreen, tSblue);

}  /* computeFresnelColor() */


inline TScalar TBsdfSchlick::computeZenith (TScalar& rtCOSNH) const
{

  return tRoughness / sqr (1.0 + tRoughnessInv * sqr (rtCOSNH));

}  /* computeZenith() */


inline TScalar TBsdfSchlick::computeAzimuth (TScalar& rtCOSTI) const
{

  TScalar tCosTI_2;

  tCosTI_2 = sqr (rtCOSTI);

  return sqrt (tIsotropy / (tIsotropy_2 + tInvIsotropy_2 * tCosTI_2));

}  /* computeAzimuth() */


inline TScalar TBsdfSchlick::computeSmith (TScalar& rtCOS) const
{

  return rtCOS / (tRoughness + tInvRoughness * rtCOS); 

}  /* computeSmith() */


inline TColor TBsdfSchlick::evaluateReflection (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TScalar tCOSNL, TColor tRAD) const
{
  
  TScalar      tCosNV;
  TScalar      tCosNH;
  TScalar      tCosVH;
  TScalar      tCosTI;
  TVector      tHalfway = rktLIGHT - rktDATA.ray().direction();
  TVector      tTangent;
  TVector      tHalfwayProj;
  TMaterial*   ptMat    = rktDATA.object()->material();
  TScalar      k        = ptMat->diffuseReflection (rktDATA) + ptMat->specularReflection (rktDATA);
  TScalar      tGeometrical;
  TScalar      tDirectional;
  TColor       tFresnelColor;

  tHalfway.normalize();

  tCosNV = dotProduct (rktDATA.normal(), -rktDATA.ray().direction());
  tCosNH = dotProduct (rktDATA.normal(), tHalfway);
  tCosVH = dotProduct (-rktDATA.ray().direction(), tHalfway);

  //
  // Obtain tangent vector
  // 

  tTangent = crossProduct (rktDATA.normal(), TVector(0.0, 1.0, 0.0));
  
  if ( tTangent.norm() < FX_EPSILON )
  {
    tTangent.set (1.0, 0.0, 0.0);
  }

  tTangent.normalize();

  //
  // Find halfway vector projected perpendicular onto the normal
  // 

  tHalfwayProj = tHalfway - (rktDATA.normal() * dotProduct (rktDATA.normal(), tHalfway));
  tHalfwayProj.normalize();

  tCosTI = dotProduct (tTangent, tHalfwayProj);

  //
  // Evaluate Schlick's BRDF for SINGLE material
  // 
 
  tFresnelColor = computeFresnelColor (tCosVH);

  tGeometrical = computeSmith (tCosNV) * computeSmith (tCOSNL);
  
  tDirectional  = tGeometrical * computeZenith (tCosNH) * computeAzimuth (tCosTI);
  tDirectional += (tGeometrical - 1.0);
  tDirectional /= (2.0 * tCosNV * tCOSNL);

  if ( tDirectional < 0.0 )
  {
    tDirectional = 0.0;
  }

  return (tFresnelColor * k * (A + B * tDirectional));

}  /* evaluateReflection() */

#endif  /* _BSDF_SCHLICK__ */


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

#ifndef _BSDF_COOK_TORRANCE__
#define _BSDF_COOK_TORRANCE__

#include "llapi/bsdf.h"
#include "llapi/material.h"
#include "llapi/math_tools.h"
#include "llapi/vector.h"
#include "hlapi/plugin_manager.h"

class TBsdfCookTorrance : public TBsdf
{

  protected:

    TScalar   tStandardDeviation;
    TColor    tSpecularReflectionCoefficients;

    TScalar   tStandardDeviationSqr;
    TScalar   tNred;
    TScalar   tNgreen;
    TScalar   tNblue;

  protected:

    inline TScalar sqr (TScalar X) const { return (X * X); }
    
    void setStandardDeviation (TScalar tSTDDEV);
    void setSpecularReflectionCoefficients (TColor tFRESNELZERO);

    TScalar calculateFresnel (const TScalar& N, TScalar& rtCosVH) const;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);
 
    TBsdfCookTorrance (void);

    TColor evaluateReflection (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TScalar tCOSNL, TColor tRAD) const;

    void getRayDirection (const TSurfaceData& rktDATA, const TVector& rktREFLECTED, TVector& rtDIR) const
    {
      TVector   v = RandomVectorInSphere();

      rtDIR = ( dotProduct (v, rktDATA.normal()) > 0 ) ? v : -v;
    }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    string className (void) const { return "BsdfCookTorrance"; }

};  /* class TBsdfCookTorrance */


inline void TBsdfCookTorrance::setStandardDeviation (TScalar tSTDDEV)
{

  tStandardDeviation = tSTDDEV; 
  tStandardDeviationSqr = sqr (tSTDDEV); 

}  /* setStandardDeviation() */


inline void TBsdfCookTorrance::setSpecularReflectionCoefficients (TColor tREFLECTION)
{

  tSpecularReflectionCoefficients = tREFLECTION;

  tNred   = (1.0 + sqrt (tREFLECTION.red()))   / (1.0 - sqrt (tREFLECTION.red()));
  tNgreen = (1.0 + sqrt (tREFLECTION.green())) / (1.0 - sqrt (tREFLECTION.green()));
  tNblue  = (1.0 + sqrt (tREFLECTION.blue()))  / (1.0 - sqrt (tREFLECTION.blue()));

  if ( tNred == HUGE_VAL )
  {
    tNred = 1e6;
  }
  if ( tNgreen == HUGE_VAL )
  {
    tNgreen = 1e6;
  }
  if ( tNblue == HUGE_VAL )
  {
    tNblue = 1e6;
  }

}  /* setSpecularReflectionCoefficients() */


inline TScalar TBsdfCookTorrance::calculateFresnel (const TScalar& N, TScalar& rtCosVH) const
{

  TScalar C = rtCosVH;
  TScalar G = sqrt (sqr (N) + sqr (C) - 1.0); 

  return 0.5 * sqr ((G - C) / (G + C)) * (1.0 + sqr ((C * (G + C) - 1.0) / (C * (G - C) + 1.0)));						      

}  /* calculateFresnel() */


inline TColor TBsdfCookTorrance::evaluateReflection (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TScalar tCOSNL, TColor tRAD) const
{
  
  TScalar      tCosNH;
  TScalar      tCosVH;
  TScalar      tCosNV;
  TScalar      tAngleNH;
  TVector      tHalfway = rktLIGHT - rktDATA.ray().direction();
  TMaterial*   ptMat    = rktDATA.object()->material();
  TColor       tColor   = ptMat->color (rktDATA);
  TScalar      kd       = ptMat->diffuseReflection (rktDATA);
  TScalar      ks       = ptMat->specularReflection (rktDATA);
  TScalar      D;
  TScalar      G, Gs, Gm, tGcommon;
  TScalar      Fr, Fg, Fb;
  TScalar      tGlare;

  tHalfway.normalize();

  tCosNV   = dotProduct (rktDATA.normal(), -rktDATA.ray().direction());
  tCosNH   = dotProduct (rktDATA.normal(), tHalfway);
  tCosVH   = dotProduct (-rktDATA.ray().direction(), tHalfway);

  tAngleNH = acos (tCosNH);

  //
  // Micro-geometry term (Beckman distribution)
  //

  D = exp (- sqr (tan (tAngleNH)) / tStandardDeviationSqr) / (4.0 * tStandardDeviationSqr * sqr (sqr (tCosNH)));
  
  //
  // Shadowing / masking term
  //

  tGcommon = 2.0 * tCosNH / tCosVH;

  Gm = tGcommon * tCosNV;
  Gs = tGcommon * tCOSNL;

  G  = min3 (1.0, Gm, Gs);

  //
  // Glare effect
  //

  tGlare = 1.0 / tCosNV;

  //  
  // Fresnel term
  //  

  Fr = calculateFresnel (tNred,   tCosVH);
  Fg = calculateFresnel (tNgreen, tCosVH);
  Fb = calculateFresnel (tNblue,  tCosVH);  

  return (tColor * kd * tCOSNL) + (TColor (Fr, Fg, Fb) * ks * (D * G * tGlare));

}  /* evaluateReflection() */

#endif  /* _BSDF_COOK_TORRANCE__ */

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

#ifndef _BSDF_SCHLICK_DOUBLE__
#define _BSDF_SCHLICK_DOUBLE__

#include "llapi/bsdf.h"
#include "llapi/material.h"
#include "llapi/math_tools.h"
#include "llapi/vector_tools.h"
#include "hlapi/plugin_manager.h"
#include "../schlick/bsdf_schlick.h"

class TBsdfSchlickDouble : public TBsdf
{

  protected:

    TBsdfSchlick*  ptLayerOne; 
    TBsdfSchlick*  ptLayerTwo;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);
 
    TBsdfSchlickDouble (void);
    ~TBsdfSchlickDouble (void);

    TColor evaluateReflection (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TScalar tCOSNL, TColor tRAD) const;

    void getRayDirection (const TSurfaceData& rktDATA, const TVector& rktREFLECTED, TVector& rtDIR) const
    {
      TVector   v = RandomVectorInSphere();

      rtDIR = ( dotProduct (v, rktDATA.normal()) > 0 ) ? v : -v;
    }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    string className (void) const { return "BsdfSchlickDouble"; }

};  /* class TBsdfSchlickDouble */


inline TColor TBsdfSchlickDouble::evaluateReflection (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TScalar tCOSNL, TColor tRAD) const
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
  TScalar      tGeometrical, tL2_Geometrical;
  TScalar      tDirectional, tL2_Directional;
  TColor       tFresnelColor, tL2_FresnelColor;
  TColor       tL1_Color, tL2_Color;

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
  // Evaluate Schlick's BRDF for DOUBLE material
  //
  // ... First evaluate the opaque layer
  // 

  tFresnelColor = ptLayerOne->computeFresnelColor (tCosVH);
 
  tGeometrical = ptLayerOne->computeSmith (tCosNV) * ptLayerOne->computeSmith (tCOSNL);
  
  tDirectional  = tGeometrical * ptLayerOne->computeZenith (tCosNH) * ptLayerOne->computeAzimuth (tCosTI);
  tDirectional += tGeometrical - 1.0;
  tDirectional /= 2.0 * tCosNV * tCOSNL;

  if ( tDirectional < 0.0 )
  {
    tDirectional = 0.0;
  }

  tL1_Color = tFresnelColor * (ptLayerOne->getA() + ptLayerOne->getB() * tDirectional);

  //
  // ... Then evaluate the translucide layer
  //

  tL2_FresnelColor = ptLayerTwo->computeFresnelColor (tCosVH);

  tL2_Geometrical = ptLayerTwo->computeSmith (tCosNV) * ptLayerTwo->computeSmith (tCOSNL);

  tL2_Directional  = tL2_Geometrical * ptLayerTwo->computeZenith (tCosNH) * ptLayerTwo->computeAzimuth (tCosTI);
  tL2_Directional += tL2_Geometrical - 1.0;
  tL2_Directional /= 2.0 * tCosNV * tCOSNL;

  if ( tL2_Directional < 0.0 )
  {
    tL2_Directional = 0.0;
  }

  tL2_Color = tL2_FresnelColor * (ptLayerTwo->getA() + ptLayerTwo->getB() * tL2_Directional);

  return ((tL1_Color + (TColor::_white() - tFresnelColor) * tL2_Color) * k);

}  /* evaluateReflection() */

#endif  /* _BSDF_SCHLICK_DOUBLE__ */

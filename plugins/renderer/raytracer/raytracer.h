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

#ifndef _RAYTRACER__
#define _RAYTRACER__

#include "llapi/renderer.h"
#include "llapi/ray.h"
#include "llapi/span_list.h"
#include "llapi/light.h"
#include "hlapi/plugin_manager.h"

enum ESamplingMethod
{

  FX_SINGLE,
  FX_UNIFORM,
  FX_STOCHASTIC,
  FX_ADAPTIVE,
  FX_FALSE_COLOR

};  /* enum ESamplingMethod */


class TRaytracer : public TRenderer
{

  protected:

    Word              wMaxDepth;
    TScalar           tMaxColorDiff;
    TColor            tAmbientLight;
    TScene*           ptScene;
    ESamplingMethod   eSamplingMethod;
    Byte              bMaxAADepth;
    Word              wNeededBuffers;

    virtual TColor getRadiance (TSurfaceData& rtDATA, Word wDEPTH) const;
    void traceRay (TRay& rtRAY, TSurfaceData& rtDATA) const;
    bool traceShadowRay (const TRay& rktRAY, const TLight& rktLIGHT, TColor& rtRAD) const;
    TColor shadePrimaryRay (TScalar I, TScalar J, TSurfaceData& rtDATA);
    void singleSample (TScalar I, TScalar J, SBuffers& rsBUFFERS);
    void superSampleUniform (TScalar I, TScalar J, SBuffers& rsBUFFERS);
    void superSampleStochastic (TScalar I, TScalar J, SBuffers& rsBUFFERS);
    void superSampleAdaptive (TScalar I, TScalar J, SBuffers& rsBUFFERS);
    TColor recursiveSampleAdaptive (TScalar I, TScalar J, TScalar tSIZE, TColor* atRADIANCE, Byte bDEPTH);
    void sampleFalseColor (TScalar I, TScalar J, SBuffers& rsBUFFERS);

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TRaytracer (void) :
      TRenderer(),
      wMaxDepth (10),
      tMaxColorDiff (0.1),
      tAmbientLight (TColor::_white()),
      eSamplingMethod (FX_SINGLE),
      bMaxAADepth (2) {}

    void render (SBuffers& rsBUFFERS);

    void initialize (TScene& rtSCENE)
    {
      ptScene = &rtSCENE;
    }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setAmbientLight (const TColor& rktCOLOR);

    TColor mediaRadiance (const TSurfaceData& rktDATA, const TColor& rktRAD) const;
    TColor directLight (const TSurfaceData& rktDATA) const;
    TColor directLight (const TSurfaceData& rktDATA, const TLight* pktLIGHT) const;
    TColor ambientLight (const TSurfaceData& rktDATA, Word wDEPTH) const;
    TColor specularReflectedLight (const TSurfaceData& rktDATA, Word wDEPTH, size_t* pzOBJ_CODE = NULL) const;
    TColor specularTransmittedLight (const TSurfaceData& rktDATA, Word wDEPTH, size_t* pzOBJ_CODE = NULL) const;

    string className (void) const { return "Raytracer"; }

    void printDebug (void) const;
    
};  /* class TRaytracer */

#endif  /* _RAYTRACER__ */

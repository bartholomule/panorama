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

#include <cassert>
#include <cstdlib>
#include <iostream>
#include "llapi/object.h"
#include "llapi/material.h"
#include "llapi/scene.h"
#include "llapi/bsdf.h"
#include "raytracer.h"

DEFINE_PLUGIN ("Raytracer", FX_RENDERER_CLASS, TRaytracer);

/*
*  traceRay()
*
*/
inline void TRaytracer::traceRay (TRay& rtRAY, TSurfaceData& rtDATA) const
{

  //
  // Search for the first intersection.
  //
  if ( !ptScene->world()->findFirstIntersection (rtRAY, rtDATA) )
  {
    //
    // There was no intersection, so we can only store ray and a null pointer
    //
    rtDATA.setup (NULL, rtRAY);
    rtDATA.setPoint (SCALAR_MAX);
  }

}  /* traceRay() */


/*
*  getRadiance()
*
*/
inline TColor TRaytracer::getRadiance (TSurfaceData& rtDATA, Word wDEPTH) const
{

  TColor   tRadiance;

  if ( rtDATA.object() )
  {
    //
    // There was an intersection
    //
    tRadiance = ambientLight (rtDATA, wDEPTH);

    rtDATA.tLightRadiance = directLight (rtDATA);

    tRadiance += rtDATA.tLightRadiance;

    rtDATA.zReflection = 0;
    if ( rtDATA.object()->material()->specularReflection (rtDATA) > 0 )
    {
      tRadiance += specularReflectedLight (rtDATA, wDEPTH, &rtDATA.zReflection);
    }

    rtDATA.zTransmission = 0;
    if ( rtDATA.object()->material()->transparent (rtDATA) )
    {
      tRadiance += specularTransmittedLight (rtDATA, wDEPTH, &rtDATA.zTransmission);
    }

    tRadiance = mediaRadiance (rtDATA, tRadiance);

    for (list<const TObjectFilter*>::const_iterator tIter = rtDATA.object()->filterList().begin(); ( tIter != rtDATA.object()->filterList().end() ) ;tIter++)
    {
      tRadiance = (*tIter)->filterRadiance (rtDATA, tRadiance);
    }
  }
  else
  {
    //
    // There was no intersection
    //
    tRadiance = mediaRadiance (rtDATA, ptScene->backgroundColor());
  }

  return tRadiance;
  
}  /* getRadiance() */


/*
*  traceShadowRay()
*
*/
inline bool TRaytracer::traceShadowRay (const TRay& rktRAY, const TLight& rktLIGHT, TColor& rtRADIANCE) const
{

  TColor           tLightColor;
  TMaterial*       ptMaterial;
  TScalar          tTransparency;
  TSurfaceData     tSurfaceData;
  TSpanList        tList;
  TRay             tRay = rktRAY;

  //
  // We start with the light that would reach the point of intersection ignoring
  // any obstacle.
  //
  tLightColor = rktLIGHT.color (tRay.location());
  if ( tLightColor == TColor::_null() )
  {
    return false;
  }
  
  //
  // If this is a shadowless light, we have finished.
  //
  if ( !rktLIGHT.shadow() )
  {
    rtRADIANCE = tLightColor;
    return true;
  }
  
  //
  // Set light location as a limit for intersection tests.
  //
  tRay.setLimit (Distance (tRay.location(), rktLIGHT.location()));

  while ( ptScene->world()->findFirstIntersection (tRay, tSurfaceData) )
  {
    //
    // Atmospheric attenuation (without scattering).
    //
    if ( ptScene->participatingMedia() )
    {
      tLightColor *= ptScene->atmosphere()->transparency (tRay.location(), tSurfaceData.point());
    }
      
    ptMaterial = tSurfaceData.object()->material();

    if ( !ptMaterial->transparent (tSurfaceData) )
    {
      //
      // Light is blocked by this object.
      //
      return false;
    }
    else
    {
      // [_TODO_] We could apply refraction to ray here.
      tSurfaceData.object()->findAllIntersections (tRay, tList);

      assert ( !tList.empty() );

      tTransparency  = ptMaterial->transparency (tList);
      tLightColor   *= ptMaterial->color (tSurfaceData) * tTransparency;

      //
      // Set new ray location to the last intersection point.
      //
      tSurfaceData = tList.last();
      tRay.setLocation (tSurfaceData.point());
      tRay.setLimit (tRay.limit() - tSurfaceData.distance());
    }
  }

  rtRADIANCE = tLightColor;

  return true;

}  /* traceShadowRay() */


inline TColor TRaytracer::shadePrimaryRay (TScalar I, TScalar J, TSurfaceData& rtDATA)
{

  TRay   tRay;

  ptScene->camera()->getRay (I, J, tRay);

  traceRay (tRay, rtDATA);

  return getRadiance (rtDATA, wMaxDepth);
  
}  /* shadePrimaryRay() */

                                           
inline void TRaytracer::superSampleUniform (TScalar I, TScalar J, SBuffers& rsBUFFERS)
{

  TColor         tRadiance;
  TSurfaceData   tSurfaceData;
  TScalar        tStep  = 1.0 / bMaxAADepth;
  TScalar        BI     = I - 0.5;
  TScalar        BJ     = J - 0.5;

  J = BJ;
  for (Byte SJ = 0; ( SJ < bMaxAADepth ) ;SJ++)
  {
    I = BI;
    for (Byte SI = 0; ( SI < bMaxAADepth ) ;SI++)
    {
      tRadiance += shadePrimaryRay (I, J, tSurfaceData);

      I += tStep;
    }

    J += tStep;
  }

  if ( wNeededBuffers & FX_ZBUFFER )
  {
    rsBUFFERS.ptZBuffer->setPixel (I, J, tSurfaceData.distance());
  }

  if ( wNeededBuffers & FX_NBUFFER )
  {
    rsBUFFERS.ptNBuffer->setPixel (I, J, tSurfaceData.normal());
  }
  
  tRadiance /= (bMaxAADepth * bMaxAADepth);
  
  rsBUFFERS.ptImage->setPixel (I, J, tRadiance);

}  /* superSampleUniform() */


inline void TRaytracer::singleSample (TScalar I, TScalar J, SBuffers& rsBUFFERS)
{

  TColor         tRadiance;
  TSurfaceData   tSurfaceData;

  tRadiance = shadePrimaryRay (I, J, tSurfaceData);

  if ( wNeededBuffers & FX_ZBUFFER )
  {
    rsBUFFERS.ptZBuffer->setPixel (I, J, tSurfaceData.distance());
  }

  if ( wNeededBuffers & FX_NBUFFER )
  {
    rsBUFFERS.ptNBuffer->setPixel (I, J, tSurfaceData.normal());
  }

  rsBUFFERS.ptImage->setPixel (I, J, tRadiance);

}  /* singleSample() */


inline void TRaytracer::superSampleStochastic (TScalar I, TScalar J, SBuffers& rsBUFFERS)
{

  TColor         tRadiance;
  TSurfaceData   tSurfaceData;

  for (Byte S = 0; ( S < bMaxAADepth ) ;S++)
  {
    tRadiance += shadePrimaryRay (I + srand() * 0.5, J + srand() * 0.5, tSurfaceData);
  }

  tRadiance /= bMaxAADepth;
  
  if ( wNeededBuffers & FX_ZBUFFER )
  {
    rsBUFFERS.ptZBuffer->setPixel (I, J, tSurfaceData.distance());
  }

  if ( wNeededBuffers & FX_NBUFFER )
  {
    rsBUFFERS.ptNBuffer->setPixel (I, J, tSurfaceData.normal());
  }
  
  rsBUFFERS.ptImage->setPixel (I, J, tRadiance);

}  /* superSampleStochastic() */


TColor TRaytracer::recursiveSampleAdaptive (TScalar I, TScalar J, TScalar tSIZE, TColor* atRADIANCE, Byte bDEPTH)
{

  TSurfaceData   tSurfaceData;
  TColor         tRadiance;
  TColor         tTotalRadiance;
  TColor         atRadiance [4];
  TScalar        tHalfSize = tSIZE * 0.5;

  tRadiance = shadePrimaryRay (I, J, tSurfaceData);

  //
  // Upper-left square
  //
  if ( ( ( fabs (tRadiance.red() - atRADIANCE[0].red()) > tMaxColorDiff )     ||
         ( fabs (tRadiance.green() - atRADIANCE[0].green()) > tMaxColorDiff ) ||
         ( fabs (tRadiance.blue() - atRADIANCE[0].blue()) > tMaxColorDiff ) ) &&
       ( bDEPTH < bMaxAADepth ) )
  {
    atRadiance[0] = atRADIANCE[0];
    atRadiance[1] = shadePrimaryRay (I, J - tSIZE, tSurfaceData);
    atRadiance[1] = shadePrimaryRay (I - tSIZE, J, tSurfaceData);
    atRadiance[3] = tRadiance;

    tTotalRadiance += recursiveSampleAdaptive (I - tHalfSize, J - tHalfSize, tHalfSize, atRadiance, bDEPTH + 1);
  }
  else
  {
    tTotalRadiance += (tRadiance + atRADIANCE[0]) * 0.5;
  }

  //
  // Upper-right square
  //
  if ( ( ( fabs (tRadiance.red() - atRADIANCE[1].red()) > tMaxColorDiff )     ||
         ( fabs (tRadiance.green() - atRADIANCE[1].green()) > tMaxColorDiff ) ||
         ( fabs (tRadiance.blue() - atRADIANCE[1].blue()) > tMaxColorDiff ) ) &&
       ( bDEPTH < bMaxAADepth ) )
  {
    atRadiance[0] = shadePrimaryRay (I, J - tSIZE, tSurfaceData);
    atRadiance[1] = atRADIANCE[1];
    atRadiance[2] = tRadiance;
    atRadiance[3] = shadePrimaryRay (I + tSIZE, J, tSurfaceData);
    
    tTotalRadiance += recursiveSampleAdaptive (I + tHalfSize, J - tHalfSize, tHalfSize, atRadiance, bDEPTH + 1);
  }
  else
  {
    tTotalRadiance += (tRadiance + atRADIANCE[1]) * 0.5;
  }

  //
  // Lower-left square
  //
  if ( ( ( fabs (tRadiance.red() - atRADIANCE[2].red()) > tMaxColorDiff )     ||
         ( fabs (tRadiance.green() - atRADIANCE[2].green()) > tMaxColorDiff ) ||
         ( fabs (tRadiance.blue() - atRADIANCE[2].blue()) > tMaxColorDiff ) ) &&
       ( bDEPTH < bMaxAADepth ) )
  {
    atRadiance[0] = shadePrimaryRay (I - tSIZE, J, tSurfaceData);
    atRadiance[1] = tRadiance;
    atRadiance[2] = atRADIANCE[2];
    atRadiance[3] = shadePrimaryRay (I, J + tSIZE, tSurfaceData);
    
    tTotalRadiance += recursiveSampleAdaptive (I - tHalfSize, J + tHalfSize, tHalfSize, atRadiance, bDEPTH + 1);
  }
  else
  {
    tTotalRadiance += (tRadiance + atRADIANCE[2]) * 0.5;
  }

  //
  // Lower-right square
  //
  if ( ( ( fabs (tRadiance.red() - atRADIANCE[3].red()) > tMaxColorDiff )     ||
         ( fabs (tRadiance.green() - atRADIANCE[3].green()) > tMaxColorDiff ) ||
         ( fabs (tRadiance.blue() - atRADIANCE[3].blue()) > tMaxColorDiff ) ) &&
       ( bDEPTH < bMaxAADepth ) )
  {
    atRadiance[0] = tRadiance;
    atRadiance[1] = shadePrimaryRay (I + tSIZE, J, tSurfaceData);
    atRadiance[2] = shadePrimaryRay (I, J + tSIZE, tSurfaceData);
    atRadiance[3] = atRADIANCE[3];
    
    tTotalRadiance += recursiveSampleAdaptive (I + tHalfSize, J + tHalfSize, tHalfSize, atRadiance, bDEPTH + 1);
  }
  else
  {
    tTotalRadiance += (tRadiance + atRADIANCE[3]) * 0.5;
  }

  return tTotalRadiance * 0.25;
  
}  /* recursiveSampleAdaptive() */


inline void TRaytracer::superSampleAdaptive (TScalar I, TScalar J, SBuffers& rsBUFFERS)
{

  TColor         tRadiance;
  TColor         atRadiance [4];
  TSurfaceData   tSurfaceData;

  atRadiance[0] = shadePrimaryRay (I - 0.5, J - 0.5, tSurfaceData);
  atRadiance[1] = shadePrimaryRay (I + 0.5, J - 0.5, tSurfaceData);
  atRadiance[2] = shadePrimaryRay (I - 0.5, J + 0.5, tSurfaceData);
  atRadiance[3] = shadePrimaryRay (I + 0.5, J + 0.5, tSurfaceData);

  tRadiance = recursiveSampleAdaptive (I, J, 0.5, atRadiance, 0);
                                       
  if ( wNeededBuffers & FX_ZBUFFER )
  {
    rsBUFFERS.ptZBuffer->setPixel (I, J, tSurfaceData.distance());
  }

  if ( wNeededBuffers & FX_NBUFFER )
  {
    rsBUFFERS.ptNBuffer->setPixel (I, J, tSurfaceData.normal());
  }
  
  rsBUFFERS.ptImage->setPixel (I, J, tRadiance);

}  /* superSampleAdaptive() */


inline void TRaytracer::sampleFalseColor (TScalar I, TScalar J, SBuffers& rsBUFFERS)
{

  TColor         tRadiance;
  TColor         atRadiance [5];
  TSurfaceData   atSurfaceData [5];

  atRadiance[4] = shadePrimaryRay (I, J, atSurfaceData[4]);

  if ( wNeededBuffers & FX_ZBUFFER )
  {
    rsBUFFERS.ptZBuffer->setPixel (I, J, atSurfaceData[4].distance());
  }

  if ( wNeededBuffers & FX_NBUFFER )
  {
    rsBUFFERS.ptNBuffer->setPixel (I, J, atSurfaceData[4].normal());
  }
  
  atRadiance[0] = shadePrimaryRay (I - 0.5, J - 0.5, atSurfaceData[0]);
  atRadiance[1] = shadePrimaryRay (I + 0.5, J - 0.5, atSurfaceData[1]);
  atRadiance[2] = shadePrimaryRay (I - 0.5, J + 0.5, atSurfaceData[2]);
  atRadiance[3] = shadePrimaryRay (I + 0.5, J + 0.5, atSurfaceData[3]);

  if ( ( atSurfaceData[4].objectCode() != atSurfaceData[0].objectCode() ) ||
       ( atSurfaceData[4].objectCode() != atSurfaceData[1].objectCode() ) ||
       ( atSurfaceData[4].objectCode() != atSurfaceData[2].objectCode() ) ||
       ( atSurfaceData[4].objectCode() != atSurfaceData[3].objectCode() )  )
  {
    tRadiance += TColor (1, 0, 0);
  }

  if ( ( atSurfaceData[4].zReflection != atSurfaceData[0].zReflection ) ||
       ( atSurfaceData[4].zReflection != atSurfaceData[1].zReflection ) ||
       ( atSurfaceData[4].zReflection != atSurfaceData[2].zReflection ) ||
       ( atSurfaceData[4].zReflection != atSurfaceData[3].zReflection )  )
  {
    tRadiance += TColor (0, 1, 0);
  }

  /*
  if ( ( atSurfaceData[4].zTransmission != atSurfaceData[0].zTransmission ) ||
       ( atSurfaceData[4].zTransmission != atSurfaceData[1].zTransmission ) ||
       ( atSurfaceData[4].zTransmission != atSurfaceData[2].zTransmission ) ||
       ( atSurfaceData[4].zTransmission != atSurfaceData[3].zTransmission )  )
  {
    tRadiance += TColor (0, 0, 1);
  }
  */
  
  if ( ( MaxColorDiff (atSurfaceData[4].tLightRadiance, atSurfaceData[0].tLightRadiance) > tMaxColorDiff ) ||
       ( MaxColorDiff (atSurfaceData[4].tLightRadiance, atSurfaceData[1].tLightRadiance) > tMaxColorDiff ) ||
       ( MaxColorDiff (atSurfaceData[4].tLightRadiance, atSurfaceData[2].tLightRadiance) > tMaxColorDiff ) ||
       ( MaxColorDiff (atSurfaceData[4].tLightRadiance, atSurfaceData[3].tLightRadiance) > tMaxColorDiff )  )
  {
    tRadiance += TColor (0, 0, 1);
  }

  rsBUFFERS.ptImage->setPixel (I, J, tRadiance);

}  /* sampleFalseColor() */


int TRaytracer::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "ambient" )
  {
    if ( eTYPE == FX_COLOR )
    {
      setAmbientLight (*((TColor*) nVALUE.pvValue));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "depth" )
  {
    if ( eTYPE == FX_REAL )
    {
      wMaxDepth = Word (nVALUE.dValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "max_diff" )
  {
    if ( eTYPE == FX_REAL )
    {
      tMaxColorDiff = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "aa_depth" )
  {
    if ( eTYPE == FX_REAL )
    {
      bMaxAADepth = Byte (nVALUE.dValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "sampling" )
  {
    if ( eTYPE == FX_STRING )
    {
      string   tName = (char*) nVALUE.pvValue;
      if ( tName == "single" )
      {
        eSamplingMethod = FX_SINGLE;
      }
      else if ( tName == "uniform" )
      {
        eSamplingMethod = FX_UNIFORM;
      }
      else if ( tName == "stochastic" )
      {
        eSamplingMethod = FX_STOCHASTIC;
      }
      else if ( tName == "adaptive" )
      {
        eSamplingMethod = FX_ADAPTIVE;
      }
      else if ( tName == "false_color" )
      {
        eSamplingMethod = FX_FALSE_COLOR;
      }
      else
      {
        TProcedural::_tUserErrorMessage = "unknown sampling method : " + tName;

        return FX_ATTRIB_USER_ERROR;
      }
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TRenderer::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TRaytracer::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "ambient" )
  {
    rnVALUE.pvValue = &tAmbientLight;
  }
  else if ( rktNAME == "depth" )
  {
    rnVALUE.dValue = wMaxDepth;
  }
  else if ( rktNAME == "max_diff" )
  {
    rnVALUE.dValue = tMaxColorDiff;
  }
  else if ( rktNAME == "aa_depth" )
  {
    rnVALUE.dValue = bMaxAADepth;
  }
  else
  {
    return TRenderer::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TRaytracer::getAttributeList (TAttributeList& rtLIST) const
{

  TRenderer::getAttributeList (rtLIST);

  rtLIST ["ambient"]  = FX_COLOR;
  rtLIST ["depth"]    = FX_REAL;
  rtLIST ["max_diff"] = FX_REAL;
  rtLIST ["aa_depth"] = FX_REAL;

}  /* getAttributeList() */


void TRaytracer::setAmbientLight (const TColor& rktCOLOR)
{

  tAmbientLight = rktCOLOR;

}  /* setAmbientLight() */


void TRaytracer::render (SBuffers& rsBUFFERS)
{

  wNeededBuffers = ptScene->neededBuffers();
  
  for (size_t J = 0; ( J < rsBUFFERS.ptImage->height() ) ;J++)
  {
    for (size_t I = 0; ( I < rsBUFFERS.ptImage->width() ) ;I++)
    {
      switch ( eSamplingMethod )
      {
        case FX_SINGLE      : singleSample (I, J, rsBUFFERS); break;
        
        case FX_UNIFORM     : superSampleUniform (I, J, rsBUFFERS); break;

        case FX_STOCHASTIC  : superSampleStochastic (I, J, rsBUFFERS); break;
        
        case FX_ADAPTIVE    : superSampleAdaptive (I, J, rsBUFFERS); break;
        
        case FX_FALSE_COLOR : sampleFalseColor (I, J, rsBUFFERS); break;
      }
    }
    
    if ( pfUserFunction )
    {
      //
      // Calls user function once for each line.
      //
      (*pfUserFunction) (J, pvUserData);
    }
  }

}  /* render() */


inline TColor TRaytracer::mediaRadiance (const TSurfaceData& rktDATA, const TColor& rktRAD) const
{

  TColor   tRad = rktRAD;

  for (vector<TLight*>::const_iterator tIter = ptScene->lightList().begin(); ( tIter != ptScene->lightList().end() ) ;tIter++)
  {
    tRad += (*tIter)->scatteredLight (rktDATA);
  }

  if ( ptScene->participatingMedia() )
  {
    tRad = ptScene->atmosphere()->filterRadiance (rktDATA, rktRAD);
  }

  return tRad;
  
}  /* mediaRadiance() */


inline TColor TRaytracer::ambientLight (const TSurfaceData& rktDATA, Word wDEPTH) const
{

  TMaterial*   ptMat = rktDATA.object()->material();
  TColor       tRad  = tAmbientLight * ptMat->color (rktDATA) * ptMat->ambientReflection (rktDATA);

  return tRad;

}  /* ambientLight() */


inline TColor TRaytracer::directLight (const TSurfaceData& rktDATA) const
{

  TLight*   ptLight;
  TColor    tTotalRadiance;
    
  for (vector<TLight*>::const_iterator tIter = ptScene->lightList().begin(); ( tIter != ptScene->lightList().end() ) ;tIter++)
  {
    ptLight         = *tIter;
    tTotalRadiance += directLight (rktDATA, ptLight);
  }

  return tTotalRadiance;

}  /* directLight() */


inline TColor TRaytracer::directLight (const TSurfaceData& rktDATA, const TLight* pktLIGHT) const
{

  TScalar   tCosNL;
  TColor    rho;
  TColor    tTotalRadiance;
  TColor    tRadiance;
  TRay      tRay (rktDATA.point(), pktLIGHT->location() - rktDATA.point());

  tRay.normalize();

  if ( rktDATA.object() )
  {
    tCosNL = dotProduct (rktDATA.normal(), tRay.direction());
    
    if ( tCosNL > 0 )
    {
      if ( traceShadowRay (tRay, *pktLIGHT, tRadiance) )
      {
        rho            = rktDATA.object()->material()->bsdf()->evaluateReflection (rktDATA, tRay.direction(), tCosNL, tRadiance);
        tTotalRadiance = tRadiance * rho;
      }
    }
  }
  else
  {
    if ( traceShadowRay (tRay, *pktLIGHT, tRadiance) )
    {
      tTotalRadiance = tRadiance;
    }
  }

  return tTotalRadiance;

}  /* directLight() */


TColor TRaytracer::specularReflectedLight (const TSurfaceData& rktDATA, Word wDEPTH, size_t* pzOBJ_CODE) const
{

  TRay           tRay;
  TColor         tRadiance;
  TSurfaceData   tSurfaceData;
  TVector        tNormal    = rktDATA.normal();
  TMaterial*     ptMaterial = rktDATA.object()->material();

  if ( wDEPTH-- )
  {
    tRay = rktDATA.ray();
    tRay.setLimit (SCALAR_MAX);
    tRay.setLocation (rktDATA.point());

    if ( ptMaterial->transparent (rktDATA) && dotProduct (rktDATA.ray().direction(), tNormal) > 0 )
    {
      tNormal = -tNormal;
    }
    
    tRay.reflect (tNormal);

    traceRay (tRay, tSurfaceData);

    if ( pzOBJ_CODE )
    {
      *pzOBJ_CODE = tSurfaceData.objectCode();
    }
    
    tRadiance = getRadiance (tSurfaceData, wDEPTH) * ptMaterial->specularReflection (rktDATA);
  }

  return tRadiance;

}  /* specularReflectedLight() */


TColor TRaytracer::specularTransmittedLight (const TSurfaceData& rktDATA, Word wDEPTH, size_t* pzOBJ_CODE) const
{

  TColor         tRadiance;
  TColor         rho;
  bool           gEntering;
  TSurfaceData   tSurfaceData;
  bool           gTIR       = false;
  TRay           tRay       = rktDATA.ray();
  TVector        tNormal    = rktDATA.normal();
  TMaterial*     ptMaterial = rktDATA.object()->material();

  tRay.setLimit (SCALAR_MAX);

  if ( wDEPTH-- )
  {
    gEntering = tRay.refract (tNormal, ptMaterial->ior (rktDATA), gTIR);

    tRay.setLocation (rktDATA.point());

    traceRay (tRay, tSurfaceData);

    if ( pzOBJ_CODE )
    {
      *pzOBJ_CODE = tSurfaceData.objectCode();
    }
    
    tRadiance = getRadiance (tSurfaceData, wDEPTH);

    if ( gTIR )
    {
      tRadiance = TColor::_null();
    }
    else
    {
      rho        = ptMaterial->bsdf()->evaluateTransmission (rktDATA, tRay.direction(), tRadiance);
      tRadiance *= rho;
    }
  }

  return tRadiance;
  
}  /* specularTransmittedLight() */


void TRaytracer::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_Raytracer_]" << endl;

  TDebug::_push();

  cerr << TDebug::_indent() << "Max. depth    : " << wMaxDepth << endl;
  cerr << TDebug::_indent() << "Ambient light : "; tAmbientLight.printDebug(); cerr << endl;

  TDebug::_pop();
  
}  /* printDebug() */

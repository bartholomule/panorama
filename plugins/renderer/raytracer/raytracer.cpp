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

#include "llapi/warning_eliminator.h"
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
void TRaytracer::traceRay (TRay& rtRAY, TSurfaceData& rtDATA) const
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
TColor TRaytracer::getRadiance (TSurfaceData& rtDATA, Word wDEPTH) const
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

    //
    // Addition to allow objects to be emissive.  Note that this is done even
    // if an object is illuminated by a light source.  This hack is NOT
    // correct, as it will increase the apparent brightness of lights to
    // *potentially* twice their standard intensity.
    // [_FIXME_]
    //
    tRadiance = tRadiance + rtDATA.object()->material()->emission(rtDATA);
    
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
    TVector  tDirection;
    TVector  tNormal;
   
    tDirection = rtDATA.ray().direction();

    rtDATA.setPoint (tDirection);

    tNormal = -tDirection;
    tNormal.normalize();

    rtDATA.setNormal (tNormal);

    tRadiance = mediaRadiance (rtDATA, ptScene->backgroundColor (rtDATA));
  }

  return tRadiance;
  
}  /* getRadiance() */


/*
*  traceShadowRay()
*
*/
bool TRaytracer::traceShadowRay (const TRay& rktRAY, const TLight& rktLIGHT, TColor& rtRADIANCE) const
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


bool TRaytracer::traceShadowRay ( const TRay& rktRAY, const TObject& rktALight, TVector& light_location, TColor& rtRAD) const
{
  TColor           tLightColor;
  TColor           tLightFilter(1,1,1);
  TMaterial*       ptMaterial;
  TScalar          tTransparency;
  TSurfaceData     tSurfaceData;
  TSpanList        tList;
  TRay             tRay = rktRAY;
  
  //
  // Set light location as a limit for intersection tests.
  //
  tRay.setLimit (Distance (tRay.location(), light_location));

  while ( ptScene->world()->findFirstIntersection (tRay, tSurfaceData) )
  {
    //
    // Atmospheric attenuation (without scattering).
    //
    if ( ptScene->participatingMedia() )
    {
      tLightFilter *= ptScene->atmosphere()->transparency (tRay.location(), tSurfaceData.point());
    }
      
    ptMaterial = tSurfaceData.object()->material();

    // Check to see if the ray hit the light (it has shape).
    if( tSurfaceData.checkObject( &rktALight ) )
    {
      // The ray hit the light somewhere other than the point that would have
      // been the location of the light photons.  We will just pick this point
      // as the point of light emision.
      light_location = tSurfaceData.point ();
      // The ray could be limited again, but we've already hit the light.
      // So... We can just terminate this loop and use the filtered light color
      // given by the previous iterations.
      break;
    }
    else if ( !ptMaterial->transparent (tSurfaceData) )
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
      tLightFilter   *= ptMaterial->color (tSurfaceData) * tTransparency;

      //
      // Set new ray location to the last intersection point.
      //
      tSurfaceData = tList.last();
      tRay.setLocation (tSurfaceData.point());
      tRay.setLimit (tRay.limit() - tSurfaceData.distance());
    }
  }

  // Set up the surface data so that the color of emission can be calculated
  // from the material.  In doing so, assume a perfect ray still exists in tRay.
  tSurfaceData.setup (&rktALight, tRay);
  tSurfaceData.setPoint (light_location);
  ptMaterial = rktALight.material();
  
  tLightColor = ptMaterial->emission (tSurfaceData);
  rtRAD = tLightColor * tLightFilter;

  return true;
} /* traceShadowRay() */


TColor TRaytracer::shadePrimaryRay (TScalar I, TScalar J, TSurfaceData& rtDATA)
{

  TRay   tRay;

  ptScene->camera()->getRay (I, J, tRay);

  traceRay (tRay, rtDATA);

  TColor primary_radiance =  getRadiance (rtDATA, wMaxDepth);

  /*

    // If it hit an object, and that object was emissive... Send another ray to
    // it to allow it to be visible with a primary ray.
    if( (rtDATA.object()) && (rtDATA.object()->material()->emission()) )
    {
    TColor primary_emission(0,0,0);
    TSurfaceData tsd;
    tsd.setPoint(tRay.location());
    tsd.setNormal(tRay.direction());
    tsd.setup (rtDATA.object(),tRay);
    TVector point = rtDATA.point();

    if( traceShadowRay (tRay, *rtDATA.object(), point, primary_emission) )
    {
    return primary_radiance + primary_emission;  
    }
    }
  */
  return primary_radiance;
}  /* shadePrimaryRay() */

                                           
void TRaytracer::superSampleUniform (TScalar I, TScalar J, SBuffers& rsBUFFERS)
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
    rsBUFFERS.ptZBuffer->setPixel (unsigned(I), unsigned(J),
				   tSurfaceData.distance());
  }

  if ( wNeededBuffers & FX_NBUFFER )
  {
    rsBUFFERS.ptNBuffer->setPixel (unsigned(I), unsigned(J),
				   tSurfaceData.normal());
  }
  
  tRadiance /= (bMaxAADepth * bMaxAADepth);
  
  rsBUFFERS.ptImage->setPixel (unsigned(I), unsigned(J), tRadiance);

}  /* superSampleUniform() */


void TRaytracer::singleSample (TScalar I, TScalar J, SBuffers& rsBUFFERS)
{

  TColor         tRadiance;
  TSurfaceData   tSurfaceData;

  tRadiance = shadePrimaryRay (I, J, tSurfaceData);

  if ( wNeededBuffers & FX_ZBUFFER )
  {
    rsBUFFERS.ptZBuffer->setPixel (unsigned(I), unsigned(J),
				   tSurfaceData.distance());
  }

  if ( wNeededBuffers & FX_NBUFFER )
  {
    rsBUFFERS.ptNBuffer->setPixel (unsigned(I), unsigned(J),
				   tSurfaceData.normal());
  }

  rsBUFFERS.ptImage->setPixel (unsigned(I), unsigned(J), tRadiance);

}  /* singleSample() */


void TRaytracer::superSampleStochastic (TScalar I, TScalar J, SBuffers& rsBUFFERS)
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
    rsBUFFERS.ptZBuffer->setPixel (unsigned(I), unsigned(J),
				   tSurfaceData.distance());
  }

  if ( wNeededBuffers & FX_NBUFFER )
  {
    rsBUFFERS.ptNBuffer->setPixel (unsigned(I), unsigned(J),
				   tSurfaceData.normal());
  }
  
  rsBUFFERS.ptImage->setPixel (unsigned(I), unsigned(J), tRadiance);

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
    atRadiance[2] = shadePrimaryRay (I - tSIZE, J, tSurfaceData);
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


void TRaytracer::superSampleAdaptive (TScalar I, TScalar J, SBuffers& rsBUFFERS)
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
    rsBUFFERS.ptZBuffer->setPixel (unsigned(I), unsigned(J),
				   tSurfaceData.distance());
  }

  if ( wNeededBuffers & FX_NBUFFER )
  {
    rsBUFFERS.ptNBuffer->setPixel (unsigned(I), unsigned(J),
				   tSurfaceData.normal());
  }
  
  rsBUFFERS.ptImage->setPixel (unsigned(I), unsigned(J), tRadiance);

}  /* superSampleAdaptive() */


void TRaytracer::sampleFalseColor (TScalar I, TScalar J, SBuffers& rsBUFFERS)
{

  TColor         tRadiance;
  TColor         atRadiance [5];
  TSurfaceData   atSurfaceData [5];

  atRadiance[4] = shadePrimaryRay (I, J, atSurfaceData[4]);

  if ( wNeededBuffers & FX_ZBUFFER )
  {
    rsBUFFERS.ptZBuffer->setPixel (unsigned(I), unsigned(J),
				   atSurfaceData[4].distance());
  }

  if ( wNeededBuffers & FX_NBUFFER )
  {
    rsBUFFERS.ptNBuffer->setPixel (unsigned(I), unsigned(J),
				   atSurfaceData[4].normal());
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

  rsBUFFERS.ptImage->setPixel (unsigned(I), unsigned(J), tRadiance);

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
  rtLIST ["sampling"] = FX_STRING;  

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


TColor TRaytracer::mediaRadiance (const TSurfaceData& rktDATA, const TColor& rktRAD) const
{

  TColor   tRad = rktRAD;
  TSurfaceData tsd = rktDATA;

  for (vector<TLight*>::const_iterator tIter = ptScene->lightList().begin();
       ( tIter != ptScene->lightList().end() );
       tIter++)
  {
    tRad += (*tIter)->scatteredLight (rktDATA);
  }
  // Note that the above does NOT need to be done with area lights unless area
  // lights are allowed to have a halo.  If that is the case, then there will
  // need to be some serious work on area lights, and not just the emission
  // property which is currently in existance.

  if ( ptScene->participatingMedia() )
  {
    tRad = ptScene->atmosphere()->filterRadiance (rktDATA, rktRAD);
  }

  return tRad;
  
}  /* mediaRadiance() */


TColor TRaytracer::ambientLight (const TSurfaceData& rktDATA, Word wDEPTH) const
{

  TMaterial*   ptMat = rktDATA.object()->material();
  TColor       tRad  = tAmbientLight * ptMat->color (rktDATA) * ptMat->ambientReflection (rktDATA);

  return tRad;

}  /* ambientLight() */


TColor TRaytracer::directLight (const TSurfaceData& rktDATA) const
{

  const TLight*   ptLight;
  TColor    tTotalRadiance;
    
  for (vector<TLight*>::const_iterator tIter1 = ptScene->lightList().begin(); ( tIter1 != ptScene->lightList().end() ) ;tIter1++)
  {
    ptLight         = *tIter1;
    tTotalRadiance += directLight (rktDATA, ptLight);
  }
  const vector<TObject*>& alv = ptScene->areaLightList();
  for (vector<TObject*>::const_iterator tIter2 = alv.begin(); ( tIter2 != alv.end() ) ;tIter2++)
  {
    tTotalRadiance += directLight (rktDATA, *tIter2);
  }  

  return tTotalRadiance;

}  /* directLight() */


TColor TRaytracer::directLight (const TSurfaceData& rktDATA, const TLight* pktLIGHT) const
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


TColor TRaytracer::directLight (const TSurfaceData& rktDATA, const TObject* pktALIGHT) const
{
  TScalar   tCosNL;
  TColor    rho;
  TColor    tTotalRadiance;
  TColor    tRadiance;
  TVector   rand_point = pktALIGHT->RandomPointOnSurface();

  //  cerr << "Rand point="; rand_point.printDebug();
  TVector   light_point = (*pktALIGHT->transformMatrix()) * rand_point;
  //  cerr << "light point="; light_point.printDebug();  
  
  TRay      tRay (rktDATA.point(), light_point - rktDATA.point());

  tRay.normalize();

  if ( rktDATA.object() )
  {
    tCosNL = dotProduct (rktDATA.normal(), tRay.direction());
    
    if ( tCosNL > 0 )
    {
      if ( traceShadowRay (tRay, *pktALIGHT, light_point, tRadiance) )
      {
        rho            = rktDATA.object()->material()->bsdf()->evaluateReflection (rktDATA, tRay.direction(), tCosNL, tRadiance);
        tTotalRadiance = tRadiance * rho;
      }
    }
  }
  else
  {
    if ( traceShadowRay (tRay, *pktALIGHT, light_point, tRadiance) )
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
  TVector        tNormal          = rktDATA.normal();
  TVector        tOrigNormal      = rktDATA.unperturbedNormal();
  TMaterial*     ptMaterial       = rktDATA.object()->material();

  if ( wDEPTH-- )
  {
    tRay = rktDATA.ray();
    tRay.setLimit (SCALAR_MAX);
    tRay.setLocation (rktDATA.point());

    if ( ptMaterial->transparent (rktDATA) && dotProduct (rktDATA.ray().direction(), tNormal) > 0 )
    {
      tNormal = -tNormal;
    }
    
    tRay.reflect (tNormal, tOrigNormal);

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
  TSurfaceData   tSurfaceData;
  bool           gTIR       = false;
  TRay           tRay       = rktDATA.ray();
  TVector        tNormal    = rktDATA.normal();
  TMaterial*     ptMaterial = rktDATA.object()->material();

  if ( wDEPTH-- )
  {
    tRay.setLimit (SCALAR_MAX);

    tRay.refract (tNormal, ptMaterial->ior (rktDATA), gTIR);

    tRay.setLocation (rktDATA.point());

    if ( !gTIR )
    {
      traceRay (tRay, tSurfaceData);
    }

    if ( pzOBJ_CODE )
    {
      *pzOBJ_CODE = tSurfaceData.objectCode();
    }
    
    rho = ptMaterial->bsdf()->evaluateTransmission (rktDATA, tRay.direction(), tRadiance);

    tRadiance  = rho * ptMaterial->opacity(rktDATA);
    tRadiance += getRadiance (tSurfaceData, wDEPTH) * (1.0 - ptMaterial->opacity(rktDATA));
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

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
#include "llapi/atmospheric_object.h"
#include "llapi/atmosphere.h"
#include "llapi/renderer.h"
#include "llapi/scene.h"
#include "llapi/attribute.h"

TColor TAtmosphericObject::evaluateScattering (const TSurfaceData& rktDATA) const
{

  magic_pointer<TLight> ptLight;
  TScalar       tPhase      = 1;
  TColor        tScattering = TColor::_null();

  for (vector<magic_pointer<TLight> >::const_iterator tIter = ptScene->lightList().begin(); ( tIter != ptScene->lightList().end() ) ;tIter++)
  {
    ptLight = *tIter;
    if ( ptLight->shadow() && ptLight->volumetric() )
    {
      // Rayleigh scattering phase function
//      tPhase = 1 + sqr (dotProduct (rktDATA.ray().direction(), ptLight->location() - rktDATA.point()));
      
      //
      // Calculate scattering due to this light.
      //
      tScattering += ptScene->renderer()->directLight (rktDATA, ptLight) * tPhase;
    }
  }

  return tScattering;
  
}  /* evaluateScattering() */


TColor TAtmosphericObject::evaluateInterval (const TVector& rktPOINT1,
                                             const TVector& rktPOINT2,
                                             TScalar tSTEP_SIZE,
                                             TScalar& rtTRANSPARENCY,
                                             TColor& rtTOTAL_SCAT,
                                             const TColor& rktSCAT1,
                                             const TSurfaceData& rktDATA) const
{

  TColor   tScattering2 = evaluateScattering (rktDATA);
  TColor   tDiff        = tScattering2 - rktSCAT1;

  if ( ( ( ( rktSCAT1 == TColor::_null() ) && ( tScattering2 != TColor::_null() ) ) ||
         ( ( rktSCAT1 != TColor::_null() ) && ( tScattering2 == TColor::_null() ) ) ||
         ( (fabs (tDiff.red()) / tSTEP_SIZE) > tSlopeThreshold )   ||
         ( (fabs (tDiff.green()) / tSTEP_SIZE) > tSlopeThreshold ) ||
         ( (fabs (tDiff.blue()) / tSTEP_SIZE) > tSlopeThreshold )   ) &&
       ( tSTEP_SIZE > tMinStepSize ) )
  {
    TColor         tLastScattering = rktSCAT1;
    TVector        tStep           = (rktPOINT2 - rktPOINT1) * 0.5;
    TVector        tMidPoint       = rktPOINT1 + tStep;// + (tStep * (TScalar) srand() * tJitter);
    TSurfaceData   tSurfaceData    = rktDATA;

    tSurfaceData.setPoint (tMidPoint);

    tLastScattering = evaluateInterval (rktPOINT1,
                                        tMidPoint,
                                        tSTEP_SIZE * 0.5,
                                        rtTRANSPARENCY,
                                        rtTOTAL_SCAT,
                                        tLastScattering,
                                        tSurfaceData);

    tLastScattering = evaluateInterval (tMidPoint,
                                        rktPOINT2,
                                        tSTEP_SIZE * 0.5,
                                        rtTRANSPARENCY,
                                        rtTOTAL_SCAT,
                                        tLastScattering,
                                        rktDATA);
  }
  else
  {
    TAtmSampleData   tSampleData         = sampleData (rktPOINT2);
    TColor           tIntervalScattering = (rktSCAT1 + tScattering2) * tSTEP_SIZE * 0.5;

    rtTRANSPARENCY *= exp (-tSTEP_SIZE * tSampleData.tExtinction);
    rtTOTAL_SCAT    = rtTOTAL_SCAT + tIntervalScattering * tSampleData.tAlbedo * rtTRANSPARENCY;

    wSamplesTaken++;
  }

  return tScattering2;
  
}  /* evaluateInterval() */


int TAtmosphericObject::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "samples" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_REAL )
    {
      wSamples = Word (nVALUE.dValue);
    }
#else
    magic_pointer<TAttribInt> i = get_int (nVALUE);
    if( !!i )
    {
      wSamples = i->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "jitter" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      tJitter = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real (nVALUE);
    if( !!r )
    {
      tJitter = r->tValue;
    }    
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "min_step_size" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_REAL )
    {
      tMinStepSize = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real (nVALUE);
    if( !!r )
    {
      tMinStepSize = r->tValue;
    }    
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "transp_th" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_REAL )
    {
      tTransparencyThreshold = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real (nVALUE);
    if( !!r )
    {
      tTransparencyThreshold = r->tValue;
    }    
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "slope_th" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_REAL )
    {
      tSlopeThreshold = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real (nVALUE);
    if( !!r )
    {
      tSlopeThreshold = r->tValue;
    }    
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TProcedural::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TAtmosphericObject::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)  
  if ( rktNAME == "samples" )
  {
    rnVALUE.dValue = wSamples;
  }
  else if ( rktNAME == "jitter" )
  {
    rnVALUE.dValue = tJitter;
  }
  else if ( rktNAME == "min_step_size" )
  {
    rnVALUE.dValue = tMinStepSize;
  }
  else if ( rktNAME == "transp_th" )
  {
    rnVALUE.dValue = tTransparencyThreshold;
  }
  else if ( rktNAME == "slope_th" )
  {
    rnVALUE.dValue = tSlopeThreshold;
  }
#else
  if ( rktNAME == "samples" )
  {
    rnVALUE = (user_arg_type)new TAttribInt (wSamples);
  }
  else if ( rktNAME == "jitter" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tJitter);
  }
  else if ( rktNAME == "min_step_size" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tMinStepSize);
  }
  else if ( rktNAME == "transp_th" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tTransparencyThreshold);
  }
  else if ( rktNAME == "slope_th" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tSlopeThreshold);
  }  
#endif
  else
  {
    return TProcedural::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TAtmosphericObject::getAttributeList (TAttributeList& rtLIST) const
{

  TProcedural::getAttributeList (rtLIST);

  rtLIST ["samples"]       = FX_INTEGER;
  rtLIST ["jitter"]        = FX_REAL;
  rtLIST ["min_step_size"] = FX_REAL;
  rtLIST ["transp_th"]     = FX_REAL;
  rtLIST ["slope_th"]      = FX_REAL;

}  /* getAttributeList() */


TColor TAtmosphericObject::filterRadiance (const TSurfaceData& rktDATA, const TColor& rktRAD) const
{

  TScalar        tStepSize;
  TInterval      tInt;
  Word           wSample;
  TVector        tStep;
  TVector        tStart;
  TVector        tPoint;
  TColor         tLastScattering;
  TSurfaceData   tSurfaceData;
  TRay           tRay             = rktDATA.ray();
  TScalar        tTransparency    = 1;
  TColor         tTotalScattering = TColor::_null();

  wSamplesTaken = 0;

  if ( rktDATA.object() )
  {
    tRay.setRange( FX_EPSILON, rktDATA.distance() );
  }

  tInt = tBoundingBox.clipRay (tRay);
  
  if ( ( tInt.size() > FX_EPSILON ) && ( tInt.size() < FX_HUGE ) )
  {
    tStart = rktDATA.ray().location() + rktDATA.ray().direction() * tInt.min();

    tSurfaceData.setPoint (tStart);
    
    tLastScattering = evaluateScattering (tSurfaceData);

    //
    // Step vector to be added for each sample point
    //
    tStepSize = (tInt.size() / wSamples);
    tStep     = rktDATA.ray().direction() * tStepSize;

    tPoint  = tStart;
    wSample = 0;
    while ( ( wSample < wSamples ) && ( tTransparency >= tTransparencyThreshold ) )
    {
      TVector   tNextPoint = tPoint + tStep;

      tSurfaceData.setPoint (tNextPoint);

      tLastScattering = evaluateInterval (tPoint,
                                          tNextPoint,
                                          tStepSize,
                                          tTransparency,
                                          tTotalScattering,
                                          tLastScattering,
                                          tSurfaceData);

      tPoint = tNextPoint;
      wSample++;
    }
  }

//  GOM.debug() << "Samples : " << wSamplesTaken << endl;

  return tTotalScattering + rktRAD * tTransparency;

}  /* filterRadiance() */




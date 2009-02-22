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

namespace panorama
{

  TColor TAtmosphericObject::evaluateScattering (const TSurfaceData& rktDATA) const
  {

    rc_pointer<TLight> ptLight;
    TScalar       tPhase      = 1;
    TColor        tScattering = TColor::_null();

    for (std::vector<rc_pointer<TLight> >::const_iterator tIter = ptScene->lightList().begin(); ( tIter != ptScene->lightList().end() ) ;tIter++)
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


  TColor TAtmosphericObject::evaluateInterval (const TPoint& rktPOINT1,
    const TPoint& rktPOINT2,
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
      TColor tLastScattering = rktSCAT1;
      TVector tStep = (rktPOINT2 - rktPOINT1) * 0.5;
      TPoint tMidPoint = rktPOINT1 + tStep;// + (tStep * (TScalar) srand() * tJitter);
      TSurfaceData tSurfaceData = rktDATA;

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
      TAtmSampleData tSampleData = sampleData (rktPOINT2);
      TColor tIntervalScattering = (rktSCAT1 + tScattering2) * tSTEP_SIZE * 0.5;

      rtTRANSPARENCY *= exp (-tSTEP_SIZE * tSampleData.tExtinction);
      rtTOTAL_SCAT    = rtTOTAL_SCAT + tIntervalScattering * tSampleData.tAlbedo * rtTRANSPARENCY;

      wSamplesTaken++;
    }

    return tScattering2;

  }  /* evaluateInterval() */


  AttributeErrorCode TAtmosphericObject::setAttribute (const std::string& rktNAME, const Attribute& nVALUE)
  {

    if ( rktNAME == "samples" )
    {
      wSamples = nVALUE.convertTo<Word>();
    }
    else if ( rktNAME == "jitter" )
    {
      tJitter = nVALUE.convertTo<TScalar>();
    }
    else if ( rktNAME == "min_step_size" )
    {
      tMinStepSize = nVALUE.convertTo<TScalar>();
    }
    else if ( rktNAME == "transp_th" )
    {
      tTransparencyThreshold = nVALUE.convertTo<TScalar>();
    }
    else if ( rktNAME == "slope_th" )
    {
      tSlopeThreshold = nVALUE.convertTo<TScalar>();
    }
    else
    {
      return TProcedural::setAttribute (rktNAME, nVALUE);
    }

    return FX_ATTRIB_OK;

  }  /* setAttribute() */


  AttributeErrorCode TAtmosphericObject::getAttribute (const std::string& rktNAME, Attribute& rnVALUE)
  {
    if ( rktNAME == "samples" )
    {
      rnVALUE = Attribute(wSamples);
    }
    else if ( rktNAME == "jitter" )
    {
      rnVALUE = Attribute(tJitter);
    }
    else if ( rktNAME == "min_step_size" )
    {
      rnVALUE = Attribute(tMinStepSize);
    }
    else if ( rktNAME == "transp_th" )
    {
      rnVALUE = Attribute(tTransparencyThreshold);
    }
    else if ( rktNAME == "slope_th" )
    {
      rnVALUE = Attribute(tSlopeThreshold);
    }
    else
    {
      return TProcedural::getAttribute (rktNAME, rnVALUE);
    }

    return FX_ATTRIB_OK;

  }  /* getAttribute() */


  void TAtmosphericObject::getAttributeList (TAttributeList& rtLIST) const
  {

    rtLIST = TProcedural::getAttributeList();

    rtLIST ["samples"]       = Attribute::E_INTEGER;
    rtLIST ["jitter"]        = Attribute::E_REAL;
    rtLIST ["min_step_size"] = Attribute::E_REAL;
    rtLIST ["transp_th"]     = Attribute::E_REAL;
    rtLIST ["slope_th"]      = Attribute::E_REAL;

  }  /* getAttributeList() */


  TColor TAtmosphericObject::filterRadiance (const TSurfaceData& rktDATA, const TColor& rktRAD) const
  {

    TScalar tStepSize;
    TInterval tInt;
    Word wSample;
    TVector tStep;
    TPoint tStart;
    TPoint tPoint;
    TColor tLastScattering;
    TSurfaceData tSurfaceData;
    TRay tRay = rktDATA.ray();
    TScalar tTransparency = 1;
    TColor tTotalScattering = TColor::_null();

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
      // Step std::vector to be added for each sample point
      //
      tStepSize = (tInt.size() / wSamples);
      tStep     = rktDATA.ray().direction() * tStepSize;

      tPoint  = tStart;
      wSample = 0;
      while ( ( wSample < wSamples ) && ( tTransparency >= tTransparencyThreshold ) )
      {
        TPoint tNextPoint = tPoint + tStep;

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

    return tTotalScattering + rktRAD * tTransparency;

  }  /* filterRadiance() */

  std::string TAtmosphericObject::name() const
  {
    return "AtmosphericObject";
  }

  std::string TAtmosphericObject::internalMembers(const Indentation& indent, StringDumpable::PrefixType prefix) const
  {
    std::string tag = indent.level();
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag = indent.level() + TAtmosphericObject::name() + "::";
    }

    Indentation nextIndent = indent.nextLevel();

    std::string retval;

    retval += tag + "scene=";
    if( ptScene )
    {
      retval += ptScene->toString(nextIndent, prefix) + "\n";
    }
    else
    {
      retval +=  "NULL\n";
    }

    retval += tag + string_format("samples=%1\n", wSamples);
    retval += tag + string_format("jitter=%1\n", tJitter);
    retval += tag + string_format("transparencyThreshold=%1\n", tTransparencyThreshold);
    retval += tag + string_format("slopeThreshold=%1\n", tSlopeThreshold);
    retval += tag + string_format("minStepSize=%1\n", tMinStepSize);
    retval += tag + tBoundingBox.toString(nextIndent, prefix) + "\n";

    return retval;
  }
}




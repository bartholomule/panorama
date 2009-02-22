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

#ifndef _ATMOSPHERIC_OBJECT__
#define _ATMOSPHERIC_OBJECT__

#include "llapi/color.h"
#include "llapi/bounding_box.h"
#include "llapi/surface_data.h"

namespace panorama
{

  class TScene;

  struct TAtmSampleData
  {

    TScalar tExtinction; // Extinction coefficient at sample point
    TScalar tAlbedo;

  };  /* struct TAtmSampleData */


  class TAtmosphericObject : public TProcedural
  {

  protected:

    mutable Word   wSamplesTaken;

    TScene* ptScene;
    Word wSamples;
    TScalar tJitter;
    TScalar tTransparencyThreshold;
    TScalar tSlopeThreshold;
    TScalar tMinStepSize;
    TBoundingBox tBoundingBox;

    TColor evaluateScattering (const TSurfaceData& rktDATA) const;
    TColor evaluateInterval (const TPoint& rktPOINT1,
      const TPoint& rktPOINT2,
      TScalar tSTEP_SIZE,
      TScalar& rtTRANSPARENCY,
      TColor& rtTOTAL_SCAT,
      const TColor& rktSCAT1,
      const TSurfaceData& rktDATA) const;
  public:

    TAtmosphericObject (void) :
      TProcedural(),
      wSamples (10),
      tJitter (0),
      tTransparencyThreshold (0.01),
      tSlopeThreshold (1),
      tMinStepSize (1) {}

    AttributeErrorCode setAttribute (const std::string& rktNAME, const Attribute& nVALUE);
    AttributeErrorCode getAttribute (const std::string& rktNAME, Attribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    virtual TAtmSampleData sampleData (const TPoint& rktPOINT) const = 0;
    virtual TColor filterRadiance (const TSurfaceData& rktDATA, const TColor& rktRAD) const;
    virtual TScalar transparency (const TPoint& rktPOINT1, const TPoint& rktPOINT2) const = 0;

    EClass classType (void) const { return FX_ATM_OBJECT_CLASS; }

    virtual std::string internalMembers(const Indentation& indent, StringDumpable::PrefixType prefix) const;
    virtual std::string name() const;

  };  /* class TAtmosphericObject */
} // end namespace panorama

#endif  /* _ATMOSPHERIC_OBJECT__ */

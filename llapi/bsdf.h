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

#ifndef PANORAMA_BSDF_H_INCLUDED
#define PANORAMA_BSDF_H_INCLUDED

#include "llapi/procedural.h"
#include "llapi/color.h"
#include "llapi/llapi_defs.h"
#include "llapi/string_dumpable.hpp"

namespace panorama
{
  class TSurfaceData;

  class TBsdf : public TProcedural
  {

  public:

    virtual TColor evaluateReflection (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TScalar tCOSNL, TColor tRAD) const = 0;
    virtual TColor evaluateTransmission (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TColor tRAD) const;

    virtual void getRayDirection (const TSurfaceData& rktDATA, const TVector& rktREFLECTED, TVector& rtDIR) const = 0;

    virtual EClass classType (void) const { return FX_BSDF_CLASS; }

    virtual TBsdf* clone_new() const = 0;

    // FIXME! DELETEME!
    /**
     * These are from StringDumpable, but here (temporarily) to force
     * subclasses to override them.
     */
    virtual std::string internalMembers(const Indentation& indent, PrefixType prefix) const = 0;
    virtual std::string toString(const Indentation& indent, PrefixType prefix) const;
    virtual std::string name() const = 0;

  };  /* class TBsdf */
} // end namespace panorama

#endif  /* PANORAMA_BSDF_H_INCLUDED */

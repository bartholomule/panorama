/*
*  Copyright (C) 2000-2001 Jon Frydensbjerg and Kevin Harris
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

#ifndef PANORAMA_PATTERN_H_INCLUDED
#define PANORAMA_PATTERN_H_INCLUDED

#include "llapi/procedural.h"
#include "llapi/surface_data.h"

namespace panorama
{

  enum EWarps
  {

    FX_NO_WARP = 0,
    FX_SPHERICAL_WARP,
    FX_CYLINDRICAL_WARP

  };  /* enum EWarps */

  class TPattern : public TProcedural
  {

  protected:

    TVector tRotation;
    TVector tScaling;
    TVector tTranslation;
    TVector tRSTScaling;
    EWarps eWarp;

    mutable TColor tColor;

    TMatrix tMatrix;
    TMatrix tMatrixRotation;

    bool gTransformIdentity;

    void recalculateMatrix (void);

    void sphericalWarp (TPoint& rtPOINT) const;
    void cylindricalWarp (TPoint& rtPOINT) const;

    void sphericalAntiWarp (TPoint& rtPOINT) const;
    void cylindricalAntiWarp (TPoint& rtPOINT) const;

  public:

    TPattern()
    {
    }

    virtual ~TPattern();

    TColor color(const TSurfaceData& rktDATA) const;

    virtual TScalar scalar (const TSurfaceData& rktDATA) const;
    virtual TColor pattern(const TSurfaceData& rktDATA) const = 0;

    TPoint warp (const TPoint& rktPOINT) const;
    TVector antiWarp (const TVector& rktPOINT) const;

    EClass classType (void) const { return FX_PATTERN_CLASS; }

    virtual TUserFunctionMap getUserFunctions();

    AttributeErrorCode setAttribute (const std::string& rktNAME, Attribute nVALUE);
    AttributeErrorCode getAttribute (const std::string& rktNAME, Attribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;


    // FIXME! DELETEME!
    /**
     * These are from StringDumpable, but here (temporarily) to force
     * subclasses to override them.
     */
    virtual std::string name (void) const { return "Pattern"; }
    virtual std::string internalMembers(const Indentation& indent, PrefixType prefix) const = 0;
    virtual TPattern* clone_new() const = 0;
  };  /* class TPattern */
} // end namespace panorama

#endif  /* PANORAMA_PATTERN_H_INCLUDED */

/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _BSDF__
#define _BSDF__

#include "llapi/base_class.h"
#include "llapi/color.h"
#include "llapi/llapi_defs.h"

class TSurfaceData;

class TBsdf : public TBaseClass
{

  public:

    virtual TColor evaluateReflection (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TScalar tCOSNL, TColor tRAD) const = 0;
    virtual TColor evaluateTransmission (const TSurfaceData& rktDATA, const TVector& rktLIGHT, TColor tRAD) const;

    EClass classType (void) const { return FX_BSDF_CLASS; }
    
};  /* class TBsdf */

#endif  /* _BSDF__ */

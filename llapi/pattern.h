/*
*  Copyright (C) 2000 Jon Frydensbjerg
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

#ifndef _PATTERN__
#define _PATTERN__

#include "llapi/procedural.h"
#include "llapi/surface_data.h"

class TPattern : public TProcedural
{

  protected:

    mutable TColor   tColor;

  public:

    TPattern (void) {}
    TPattern (const TColor& rktCOLOR) :
      tColor (rktCOLOR) {}
    TPattern (const TScalar& rktSCALAR) 
    {
      setScalar (rktSCALAR);
    }

    virtual TScalar scalar (const TSurfaceData& rktDATA) const { return color (rktDATA).average(); }
    virtual TColor  color  (const TSurfaceData& rktDATA) const
    { 
      tColor = pattern (rktDATA);

      return tColor;
    }

    virtual TColor pattern (const TSurfaceData& rktDATA) const { return tColor; }

    void setColor (const TColor& rktCOLOR) { tColor = rktCOLOR; }
    void setScalar (const TScalar& rktSCALAR)
    {
      tColor.setRed (rktSCALAR);
      tColor.setGreen (rktSCALAR);
      tColor.setBlue (rktSCALAR);
    }
    
    TColor  lastColor  (void) const { return tColor; }
    TScalar lastScalar (void) const { return tColor.average(); }

    EClass classType (void) const { return FX_PATTERN_CLASS; }
    string className (void) const { return "Pattern"; }

};  /* class TPattern */

#endif  /* _PATTERN__ */


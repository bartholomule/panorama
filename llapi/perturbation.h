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

#ifndef _PERTURBATION__
#define _PERTURBATION__

#include "llapi/procedural.h"
#include "llapi/surface_data.h" 

class TPerturbation : public TProcedural
{
 
  public:

    virtual TVector perturbNormal (const TSurfaceData& rktDATA) const { return rktDATA.unperturbedNormal(); }

    EClass classType (void) const { return FX_PERTURBATION_CLASS; }
    string className (void) const { return "Perturbation"; }

};  /* class TPerturbation */

#endif  /* _PERTURBATION__ */


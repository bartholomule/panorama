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

#ifndef PANORAMA_OBJECT_FILTER_H_INCLUDED
#define PANORAMA_OBJECT_FILTER_H_INCLUDED

#include "llapi/warning_eliminator.h"
#include "llapi/procedural.h"
#include "llapi/surface_data.h"

namespace panorama
{

  class TObjectFilter : public TProcedural
  {

  public:

    virtual TColor filterRadiance (TSurfaceData& rtDATA, const TColor& rktRAD) const = 0;

    EClass classType (void) const { return FX_OBJECT_FILTER_CLASS; }
    virtual TObjectFilter* clone_new() const = 0;

  };  /* class TObjectFilter */
} // end namespace panorama

#endif  /* PANORAMA_OBJECT_FILTER_H_INCLUDED */

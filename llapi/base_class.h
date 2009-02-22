/*
 *  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
 *  Copyright (C) 2008 Kevin Harris
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

#ifndef BASE_CLASS_H_INCLUDED
#define BASE_CLASS_H_INCLUDED

#include <string>
#include <iosfwd>

#include "llapi/string_dumpable.hpp"
#include "llapi/cloneable.hpp"

#define printDebug () error()()()

namespace panorama
{

  enum EClass
  {
	  //    FX_COLOR_CLASS,
	  //    FX_VECTOR_CLASS,
	  //    FX_VECTOR2_CLASS,
    FX_PATTERN_CLASS,
    FX_PERTURBATION_CLASS,
    FX_MATERIAL_CLASS,
    FX_FRAME_CLASS,
    FX_IMAGE_CLASS,
    FX_SCENE_CLASS,
    FX_LIGHT_CLASS,
    FX_CAMERA_CLASS,
    FX_OBJECT_CLASS,
    FX_AGGREGATE_CLASS,
    FX_IMAGE_FILTER_CLASS,
    FX_RENDERER_CLASS,
    FX_BSDF_CLASS,
    FX_OBJECT_FILTER_CLASS,
    FX_BOUNDING_BOX_CLASS,
    FX_ATM_OBJECT_CLASS,
    FX_IMAGE_IO_CLASS,
    FX_SCENE_IO_CLASS

  };  /* enum EClass */

  class TBaseClass : public StringDumpable, public Cloneable
  {

  public:

    static std::string classTypeString (EClass eCLASS);

    virtual ~TBaseClass (void) {}

    virtual EClass classType (void) const = 0;

  };  /* class TBaseClass */

} // end namespace panorama

#endif  /* BASE_CLASS_H_INCLUDED */

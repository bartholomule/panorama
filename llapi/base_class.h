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

#ifndef _BASE_CLASS__
#define _BASE_CLASS__

#include <string>

enum EClass
{

  FX_COLOR_CLASS,
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
  FX_IMAGE_IO_CLASS

};  /* enum EClass */

class TBaseClass
{

  public:

    static string classTypeString (EClass eCLASS);
      
    virtual ~TBaseClass (void) {}
    
    virtual void printDebug (void) const {};

    virtual EClass classType (void) const = 0;
    virtual string className (void) const = 0;

};  /* class TBaseClass */

#endif  /* _BASE_CLASS__ */

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

#include "llapi/base_class.h"

string TBaseClass::classTypeString (EClass eCLASS)
{

  switch ( eCLASS )
  {
    case FX_COLOR_CLASS:
    {
      return "Color";
    }
    break;

    case FX_MATERIAL_CLASS:
    {
      return "Material";
    }
    break;

    case FX_FRAME_CLASS:
    {
      return "Frame";
    }
    break;

    case FX_IMAGE_CLASS:
    {
      return "Image";
    }
    break;

    case FX_SCENE_CLASS:
    {
      return "Scene";
    }
    break;

    case FX_LIGHT_CLASS:
    {
      return "Light";
    }
    break;

    case FX_CAMERA_CLASS:
    {
      return "Camera";
    }
    break;

    case FX_OBJECT_CLASS:
    {
      return "Object";
    }
    break;

    case FX_AGGREGATE_CLASS:
    {
      return "Aggregate";
    }
    break;

    case FX_IMAGE_FILTER_CLASS:
    {
      return "Image filter";
    }
    break;

    case FX_RENDERER_CLASS:
    {
      return "Renderer";
    }
    break;

    case FX_BSDF_CLASS:
    {
      return "Bsdf";
    }
    break;

    case FX_OBJECT_FILTER_CLASS:
    {
      return "Object filter";
    }
    break;

    case FX_BOUNDING_BOX_CLASS:
    {
      return "Bounding box";
    }
    break;

    case FX_ATM_OBJECT_CLASS:
    {
      return "Atmospheric object";
    }
    break;

    case FX_IMAGE_IO_CLASS:
    {
      return "Image I/O";
    }
    break;
  }

  return "";
  
}  /* classTypeString() */

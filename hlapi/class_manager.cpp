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

#include "llapi/llapi_all.h"
#include "hlapi/hlapi_all.h"
#include "hlapi/plugins_all.h"
#include "hlapi/class_manager.h"
#include "hlapi/plugin_manager.h"

#define STATIC_CLASS(class, name) \
  if ( rktCLASS == name ) \
  { \
    ptChild = new class(); \
    if ( pktPARENT ) \
    { \
      *((class*) ptChild) = *((class*) pktPARENT); \
    } \
    return ptChild; \
  }


TBaseClass* TClassManager::_newObject (const string& rktCLASS, const TBaseClass* pktPARENT)
{

  TBaseClass*   ptChild;

  STATIC_CLASS (TAggregate, "Aggregate");
  STATIC_CLASS (TBox, "Box");
  STATIC_CLASS (TCircle, "Circle");
  STATIC_CLASS (TCone, "Cone");
  STATIC_CLASS (TCylinder, "Cylinder");
  STATIC_CLASS (TMaterial, "Material");
  STATIC_CLASS (TMeshObject, "Mesh");
  STATIC_CLASS (TPhongTriangle, "PhongTriangle");
  STATIC_CLASS (TPlane, "Plane");
  STATIC_CLASS (TRectangle, "Rectangle");
  STATIC_CLASS (TSphere, "Sphere");
  STATIC_CLASS (TTorus, "Torus");
  STATIC_CLASS (TTriangle, "Triangle");

#if ( STATIC_LINK == 1 )
  STATIC_CLASS (TAtmConst, "AtmConst");
  STATIC_CLASS (TBsdfLambertian, "BsdfLambertian");
  STATIC_CLASS (TBsdfPhong, "BsdfPhong");
  STATIC_CLASS (TPinholeCamera, "PinholeCamera");
  STATIC_CLASS (TIF_Cartoon, "IF_Cartoon");
  STATIC_CLASS (TIF_ConvertToGrey, "IF_ConvertToGrey");
  STATIC_CLASS (TIF_Fog, "IF_Fog");
  STATIC_CLASS (TPointLight, "PointLight");
  STATIC_CLASS (TProjector, "Projector");
  STATIC_CLASS (TWarnLight, "WarnLight");
  STATIC_CLASS (TMaterialBrick, "MaterialBrick");
  STATIC_CLASS (TMaterialChecker, "MaterialChecker");
  STATIC_CLASS (TMaterialCrackle, "MaterialCrackle");
  STATIC_CLASS (TMaterialLeopard, "MaterialLeopard");
  STATIC_CLASS (TMaterialMarble, "MaterialMarble");
  STATIC_CLASS (TMaterialNoise, "MaterialNoise");
  STATIC_CLASS (TMaterialParquet, "MaterialParquet");
  STATIC_CLASS (TMaterialWood, "MaterialWood");
  STATIC_CLASS (TMaterialWorley, "MaterialWorley");
  STATIC_CLASS (TABVH, "ABVH");
  STATIC_CLASS (TBezierSurface, "BezierSurface");
  STATIC_CLASS (THeightField, "HeightField");
  STATIC_CLASS (TLightWaveObject, "LightWaveObject");
  STATIC_CLASS (TPolyhedron, "Polyhedron");
  STATIC_CLASS (TOF_Cartoon, "OF_Cartoon");
  STATIC_CLASS (TRaytracer, "Raytracer");
  STATIC_CLASS (TZBufferRenderer, "ZBufferRenderer");
#endif

  return tPluginManager.newObject (rktCLASS, pktPARENT);
  
}  /* _newObject() */

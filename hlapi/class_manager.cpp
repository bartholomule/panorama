/*
*  Copyright (C) 1998, 1999, 2000 Angel Jimenez Jimenez
*                                 Carlos Jimenez Moreno
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

#include "llapi/warning_eliminator.h"
#include "llapi/llapi_all.h"
#include "hlapi/hlapi_all.h"

#if ( STATIC_LINK == 1 )
#include "hlapi/plugins_all.h"
#endif /* ( STATIC_LINK == 1 ) */

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

TBaseClass* TClassManager::_newObject (const std::string& rktCLASS, const TBaseClass* pktPARENT)
{

  TBaseClass*   ptChild;

  STATIC_CLASS (TAggregate, "Aggregate");
  STATIC_CLASS (TBox, "Box");
  STATIC_CLASS (TCircle, "Circle");
  STATIC_CLASS (TCone, "Cone");
  STATIC_CLASS (TCsg, "Csg");
  STATIC_CLASS (TCylinder, "Cylinder");
  STATIC_CLASS (TMaterial, "Material");
  STATIC_CLASS (TMeshObject, "Mesh");
  STATIC_CLASS (TPattern, "Pattern");
  STATIC_CLASS (TPerturbation, "Perturbation");
  STATIC_CLASS (TPhongTriangle, "PhongTriangle");
  STATIC_CLASS (TPlane, "Plane");
  STATIC_CLASS (TQuadric, "Quadric");  
  STATIC_CLASS (TRectangle, "Rectangle");
  STATIC_CLASS (TSphere, "Sphere");
  STATIC_CLASS (TTorus, "Torus");
  STATIC_CLASS (TTriangle, "Triangle");
  STATIC_CLASS (TScene, "Scene");
  
#if ( USE_EXPERIMENTAL == 1 )  
  STATIC_CLASS (accel_grid, "AccelGrid");
#endif /* USE_EXPERIMENTAL */

#if ( STATIC_LINK == 1 )
  STATIC_CLASS (TAtmConst, "AtmConst");
  STATIC_CLASS (TBsdfCookTorrance, "BsdfCookTorrance");
  STATIC_CLASS (TBsdfLambertian, "BsdfLambertian");
  STATIC_CLASS (TBsdfPhong, "BsdfPhong");
  STATIC_CLASS (TBsdfSchlick, "BsdfSchlick");
  STATIC_CLASS (TBsdfSchlickDouble, "BsdfSchlickDouble");
  STATIC_CLASS (TBsdfWard, "BsdfWard");
  STATIC_CLASS (TParallelCamera, "ParallelCamera");
  STATIC_CLASS (TPinholeCamera, "PinholeCamera");
  STATIC_CLASS (TIF_Cartoon, "IF_Cartoon");
  STATIC_CLASS (TIF_ConvertToGrey, "IF_ConvertToGrey");
  STATIC_CLASS (TIF_Fog, "IF_Fog");
  STATIC_CLASS (TIF_Lens_Flare, "IF_Lens_Flare");
//  STATIC_CLASS (TIF_Text, "IF_Text");
  STATIC_CLASS (TPointLight, "PointLight");
  STATIC_CLASS (TProjector, "Projector");
  STATIC_CLASS (TWarnLight, "WarnLight");
  STATIC_CLASS (TPatternAmplifier, "PatternAmplifier");
  STATIC_CLASS (TPatternBrick, "PatternBrick");
  STATIC_CLASS (TPatternChecker, "PatternChecker");
  STATIC_CLASS (TPatternComposite, "PatternComposite");
  STATIC_CLASS (TPatternCrackle, "PatternCrackle");
  STATIC_CLASS (TPatternCylGrad, "PatternCylGrad");
  STATIC_CLASS (TPatternLeopard, "PatternLeopard");
  STATIC_CLASS (TPatternMarble, "PatternMarble");
  STATIC_CLASS (TPatternNoise, "PatternNoise");
  STATIC_CLASS (TPatternParquet, "PatternParquet");
  STATIC_CLASS (TPatternTexture, "PatternTexture");
  STATIC_CLASS (TPatternWood, "PatternWood");
  STATIC_CLASS (TPatternWorley, "PatternWorley");
  STATIC_CLASS (TPerturbationBrick, "PerturbationBrick");
  STATIC_CLASS (TPerturbationBump, "PerturbationBump");
  STATIC_CLASS (TPerturbationCrackle, "PerturbationCrackle");
  STATIC_CLASS (TPerturbationLeopard, "PerturbationLeopard");
  STATIC_CLASS (TPerturbationMarble, "PerturbationMarble");
  STATIC_CLASS (TPerturbationNoise, "PerturbationNoise");
  STATIC_CLASS (TPerturbationWave, "PerturbationWave");
  STATIC_CLASS (TPerturbationWorley, "PerturbationWorley");
  STATIC_CLASS (TAggregateUniformGrid, "AggregateUniformGrid");
  STATIC_CLASS (TBezierSurface, "BezierSurface");
  STATIC_CLASS (TOF_Cartoon, "OF_Cartoon");
  STATIC_CLASS (TOF_ConvertToGrey, "OF_ConvertToGrey");
  STATIC_CLASS (TRaytracer, "Raytracer");

#if ( USE_EXPERIMENTAL == 1 )
  STATIC_CLASS (TABVH, "ABVH");
  STATIC_CLASS (TSubdiv, "SubdivisionSurface");
  STATIC_CLASS (THeightField, "HeightField");
  STATIC_CLASS (TLightWaveObject, "LightWaveObject");
  STATIC_CLASS (TPolyhedron, "Polyhedron");
  STATIC_CLASS (TZBufferRenderer, "ZBufferRenderer");
#endif /* USE_EXPERIMENTALl */

#endif /* STATIC_LINK  */
 
  return tPluginManager.newObject (rktCLASS, pktPARENT);
  
}  /* _newObject() */

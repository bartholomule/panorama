/*
*  Copyright (C) 2001 Kevin Harris
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
#if       !defined(EXTENDED_TYPE_FUNCTIONS_H)
#define            EXTENDED_TYPE_FUNCTIONS_H

// extended_type_functions.h -- These are type functions (type_functions.h),
// overloaded, specialized, etc. to work with some of the other more commonly
// used items.  

#include "llapi/type_functions.h"
#include "llapi/image.h"
#include "llapi/camera.h"
#include "llapi/light.h"
#include "llapi/renderer.h"
#include "llapi/image_filter.h"
#include "hlapi/aggregate.h"
#include "llapi/extended_attribute.h"

// ---------------------------------------------------------------------------
// TImage (non-pointer)
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<TImage>(TImage i)
{
  return FX_IMAGE;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<TImage>(TImage i)
{
  return new TAttribImage(new TImage(i));
}

template <>
inline TImage attrib_to_type<TImage>(magic_pointer<TAttribute> atp, 
				     magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribImage> img = rcp_static_cast<TAttribImage>(atp);

  if( !!img && (img->eType == FX_IMAGE) )
  {
    if( !!img->tValue )
    {
      return *(img->tValue);
    }
  }
  return TImage(1,1);
}

template <>
inline magic_pointer<TAttribute> get_attrib<TImage>()
{
  return new TAttribImage;
}

// ---------------------------------------------------------------------------
// magic_pointer<TImage>
// ---------------------------------------------------------------------------
template <>
inline EAttribType
type_to_etype<magic_pointer<TImage> >(magic_pointer<TImage> i)
{
  return FX_IMAGE;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<magic_pointer<TImage> >(magic_pointer<TImage> i)
{
  return new TAttribImage(i);
}

template <>
inline magic_pointer<TImage>
attrib_to_type<magic_pointer<TImage> >(magic_pointer<TAttribute> atp, 
				       magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribImage> img = rcp_static_cast<TAttribImage>(atp);

  if( !!img && (img->eType == FX_IMAGE) )
  {
    return img->tValue;
  }
  return new TImage(1,1);
}

template <>
inline magic_pointer<TAttribute> get_attrib<magic_pointer<TImage> >()
{
  return new TAttribImage;
}

// ---------------------------------------------------------------------------
// const magic_pointer<TImage>
// ---------------------------------------------------------------------------
template <>
inline EAttribType
type_to_etype<const magic_pointer<TImage> >(const magic_pointer<TImage> i)
{
  return FX_IMAGE;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<const magic_pointer<TImage> >(const magic_pointer<TImage> i)
{
  return new TAttribImage(i);
}

template <>
inline const magic_pointer<TImage>
attrib_to_type<const magic_pointer<TImage> >(magic_pointer<TAttribute> atp, 
					     magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribImage> img = rcp_static_cast<TAttribImage>(atp);

  if( !!img && (img->eType == FX_IMAGE) )
  {
    return img->tValue;
  }
  return new TImage(1,1);
}

template <>
inline magic_pointer<TAttribute> get_attrib<const magic_pointer<TImage> >()
{
  return new TAttribImage;
}


// ---------------------------------------------------------------------------
// magic_pointer<TBsdf>
// ---------------------------------------------------------------------------
template<>
inline EAttribType type_to_etype<magic_pointer<TBsdf> >(magic_pointer<TBsdf> p)
{
  return FX_BSDF;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<magic_pointer<TBsdf> >(magic_pointer<TBsdf> p)
{
  return new TAttribBsdf(p);
}

template <>
inline magic_pointer<TBsdf>
attrib_to_type<magic_pointer<TBsdf> >(magic_pointer<TAttribute> atp, 
				      magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribBsdf> bsdf = get_bsdf(atp);

  if( !!bsdf )
  {
    data = rcp_static_cast<TAttribute>(bsdf);
    return bsdf->tValue;
  }
  
  string barf = "NULL attribute";
  if( !!atp )
  {
    barf = atp->toString();
  }
  cerr << "Error: Cannot extract bsdf from " << barf << endl;
  exit(1);
}

template <>
inline magic_pointer<TAttribute> get_attrib<magic_pointer<TBsdf> >()
{
  return new TAttribBsdf();
}

// ---------------------------------------------------------------------------
// const magic_pointer<TBsdf>
// ---------------------------------------------------------------------------
template<>
inline EAttribType type_to_etype<const magic_pointer<TBsdf> >(const magic_pointer<TBsdf> p)
{
  return FX_BSDF;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<const magic_pointer<TBsdf> >(const magic_pointer<TBsdf> p)
{
  return new TAttribBsdf(p);
}

template <>
inline const magic_pointer<TBsdf>
attrib_to_type<const magic_pointer<TBsdf> >(magic_pointer<TAttribute> atp, 
					    magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribBsdf> bsdf = get_bsdf(atp);

  if( !!bsdf )
  {
    data = rcp_static_cast<TAttribute>(bsdf);
    return bsdf->tValue;
  }  

  string barf = "NULL attribute";
  if( !!atp )
  {
    barf = atp->toString();
  }
  cerr << "Error: Cannot extract bsdf from " << barf << endl;
  exit(1);  
}

template <>
inline magic_pointer<TAttribute> get_attrib<const magic_pointer<TBsdf> >()
{
  return new TAttribBsdf();
}

// ---------------------------------------------------------------------------
// magic_pointer<TCamera>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<magic_pointer<TCamera> >(magic_pointer<TCamera> p)
{
  return FX_CAMERA;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<magic_pointer<TCamera> >(magic_pointer<TCamera> p)
{
  return new TAttribCamera(p);
}

template <>
inline magic_pointer<TCamera>
attrib_to_type<magic_pointer<TCamera> >(magic_pointer<TAttribute> atp, 
					magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribCamera> cam = rcp_static_cast<TAttribCamera>(atp);

  if( !!cam && (cam->eType == FX_CAMERA) )
  {
    return cam->tValue;
  }
  string barf = "NULL attribute";
  if( !!atp )
  {
    barf = atp->toString();
  }
  cerr << "Error: Cannot extract camera from " << barf << endl;
  exit(1);    
}

template <>
inline magic_pointer<TAttribute> get_attrib<magic_pointer<TCamera> >()
{
  return new TAttribCamera();
}

// ---------------------------------------------------------------------------
// const magic_pointer<TCamera>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const magic_pointer<TCamera> >(const magic_pointer<TCamera> p)
{
  return FX_CAMERA;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<const magic_pointer<TCamera> >(const magic_pointer<TCamera> p)
{
  return new TAttribCamera(p);
}

template <>
inline const magic_pointer<TCamera>
attrib_to_type<const magic_pointer<TCamera> >(magic_pointer<TAttribute> atp, 
					      magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribCamera> cam = rcp_static_cast<TAttribCamera>(atp);

  if( !!cam && (cam->eType == FX_CAMERA) )
  {
    return cam->tValue;
  }
  string barf = "NULL attribute";
  if( !!atp )
  {
    barf = atp->toString();
  }
  cerr << "Error: Cannot extract camera from " << barf << endl;
  exit(1);    
}

template <>
inline magic_pointer<TAttribute> get_attrib<const magic_pointer<TCamera> >()
{
  return new TAttribCamera();
}

// ---------------------------------------------------------------------------
// magic_pointer<TPattern>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<magic_pointer<TPattern> >(magic_pointer<TPattern> p)
{
  return FX_PATTERN;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<magic_pointer<TPattern> >(magic_pointer<TPattern> p)
{
  return new TAttribPattern(p);
}

template <>
inline magic_pointer<TPattern>
attrib_to_type<magic_pointer<TPattern> >(magic_pointer<TAttribute> atp, 
					 magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribPattern> pat = get_pattern(atp);

  if( !!pat )
  {
    data = rcp_static_cast<TAttribute>(pat);
    return pat->tValue;
  }
  return new TPattern;
}

template <>
inline magic_pointer<TAttribute> get_attrib<magic_pointer<TPattern> >()
{
  return new TAttribPattern();
}

// ---------------------------------------------------------------------------
// const magic_pointer<TPattern>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const magic_pointer<TPattern> >(const magic_pointer<TPattern> p)
{
  return FX_PATTERN;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<const magic_pointer<TPattern> >(const magic_pointer<TPattern> p)
{
  return new TAttribPattern(p);
}

template <>
inline const magic_pointer<TPattern>
attrib_to_type<const magic_pointer<TPattern> >(magic_pointer<TAttribute> atp, 
					       magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribPattern> pat = get_pattern(atp);

  if( !!pat )
  {
    data = rcp_static_cast<TAttribute>(pat);
    return pat->tValue;
  }  
  return new TPattern;
}

template <>
inline magic_pointer<TAttribute> get_attrib<const magic_pointer<TPattern> >()
{
  return new TAttribPattern();
}

// ---------------------------------------------------------------------------
// magic_pointer<TPerturbation>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<magic_pointer<TPerturbation> >(magic_pointer<TPerturbation> p)
{
  return FX_PERTURBATION;
}

template <>
inline magic_pointer<TPerturbation>
attrib_to_type<magic_pointer<TPerturbation> >(magic_pointer<TAttribute> atp, 
					      magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribPerturbation> pert = rcp_static_cast<TAttribPerturbation>(atp);

  if( !!pert && (pert->eType == FX_PERTURBATION) )
  {
    return pert->tValue;
  }
  return new TPerturbation;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<magic_pointer<TPerturbation> >(magic_pointer<TPerturbation> p)
{
  return new TAttribPerturbation(p);
}

template <>
inline magic_pointer<TAttribute> get_attrib<magic_pointer<TPerturbation> >()
{
  return new TAttribPerturbation();
}

// ---------------------------------------------------------------------------
// const magic_pointer<TPerturbation>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const magic_pointer<TPerturbation> >(const magic_pointer<TPerturbation> p)
{
  return FX_PERTURBATION;
}

template <>
inline const magic_pointer<TPerturbation>
attrib_to_type<const magic_pointer<TPerturbation> >(magic_pointer<TAttribute> atp, 
						    magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribPerturbation> pert = rcp_static_cast<TAttribPerturbation>(atp);

  if( !!pert && (pert->eType == FX_PERTURBATION) )
  {
    return pert->tValue;
  }
  return new TPerturbation;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<const magic_pointer<TPerturbation> >(const magic_pointer<TPerturbation> p)
{
  return new TAttribPerturbation(p);
}

template <>
inline magic_pointer<TAttribute> get_attrib<const magic_pointer<TPerturbation> >()
{
  return new TAttribPerturbation();
}

// ---------------------------------------------------------------------------
// magic_pointer<TMaterial>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<magic_pointer<TMaterial> >(magic_pointer<TMaterial> p)
{
  return FX_MATERIAL;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<magic_pointer<TMaterial> >(magic_pointer<TMaterial> p)
{
  return new TAttribMaterial(p);
}

template <>
inline magic_pointer<TMaterial>
attrib_to_type<magic_pointer<TMaterial> >(magic_pointer<TAttribute> atp, 
					  magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribMaterial> mat = rcp_static_cast<TAttribMaterial>(atp);

  if( !!mat && (mat->eType == FX_MATERIAL) )
  {
    return mat->tValue;
  }
  return new TMaterial;
}

template <>
inline magic_pointer<TAttribute> get_attrib<magic_pointer<TMaterial> >()
{
  return new TAttribMaterial();
}

// ---------------------------------------------------------------------------
// const magic_pointer<TMaterial>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const magic_pointer<TMaterial> >(const magic_pointer<TMaterial> p)
{
  return FX_MATERIAL;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<const magic_pointer<TMaterial> >(const magic_pointer<TMaterial> p)
{
  return new TAttribMaterial(p);
}

template <>
inline const magic_pointer<TMaterial>
attrib_to_type<const magic_pointer<TMaterial> >(magic_pointer<TAttribute> atp, 
						magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribMaterial> mat = rcp_static_cast<TAttribMaterial>(atp);

  if( !!mat && (mat->eType == FX_MATERIAL) )
  {
    return mat->tValue;
  }
  return new TMaterial;
}

template <>
inline magic_pointer<TAttribute> get_attrib<const magic_pointer<TMaterial> >()
{
  return new TAttribMaterial();
}

// ---------------------------------------------------------------------------
// magic_pointer<TRenderer>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<magic_pointer<TRenderer> >(magic_pointer<TRenderer> p)
{
  return FX_RENDERER;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<magic_pointer<TRenderer> >(magic_pointer<TRenderer> p)
{
  return new TAttribRenderer(p);
}

template <>
inline magic_pointer<TRenderer>
attrib_to_type<magic_pointer<TRenderer> >(magic_pointer<TAttribute> atp, 
					  magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribRenderer> rend = rcp_static_cast<TAttribRenderer>(atp);

  if( !!rend && (rend->eType == FX_RENDERER) )
  {
    return rend->tValue;
  }
  cerr << "attrib_to_type(renderer): Cannot extract renderer!" << endl;
  return NULL;
}

template <>
inline magic_pointer<TAttribute> get_attrib<magic_pointer<TRenderer> >()
{
  return new TAttribRenderer();
}

// ---------------------------------------------------------------------------
// const magic_pointer<TRenderer>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const magic_pointer<TRenderer> >(const magic_pointer<TRenderer> p)
{
  return FX_RENDERER;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<const magic_pointer<TRenderer> >(const magic_pointer<TRenderer> p)
{
  return new TAttribRenderer(p);
}

template <>
inline const magic_pointer<TRenderer>
attrib_to_type<const magic_pointer<TRenderer> >(magic_pointer<TAttribute> atp, 
						magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribRenderer> rend = rcp_static_cast<TAttribRenderer>(atp);

  if( !!rend && (rend->eType == FX_RENDERER) )
  {
    return rend->tValue;
  }
  cerr << "attrib_to_type(renderer): Cannot extract renderer!" << endl;
  return NULL;
}

template <>
inline magic_pointer<TAttribute> get_attrib<const magic_pointer<TRenderer> >()
{
  return new TAttribRenderer();
}

// ---------------------------------------------------------------------------
// magic_pointer<TObject>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<magic_pointer<TObject> >(magic_pointer<TObject> p)
{
  return FX_OBJECT;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<magic_pointer<TObject> >(magic_pointer<TObject> p)
{
  return new TAttribObject(p);
}

template <>
inline magic_pointer<TObject>
attrib_to_type<magic_pointer<TObject> >(magic_pointer<TAttribute> atp, 
					magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribObject> obj = rcp_static_cast<TAttribObject>(atp);

  if( !!obj && (obj->eType == FX_OBJECT) )
  {
    return obj->tValue;
  }

  magic_pointer<TAttribAggregate> agg = rcp_static_cast<TAttribAggregate>(atp);

  if( !!agg && (agg->eType == FX_AGGREGATE) )
  {
    return rcp_static_cast<TObject>(agg->tValue);
  }  

  cerr << "attrib_to_type(object): Cannot extract object!" << endl;
  return NULL;
}

template <>
inline magic_pointer<TAttribute> get_attrib<magic_pointer<TObject> >()
{
  return new TAttribObject();
}

// ---------------------------------------------------------------------------
// const magic_pointer<TObject>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const magic_pointer<TObject> >(const magic_pointer<TObject> p)
{
  return FX_OBJECT;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<const magic_pointer<TObject> >(const magic_pointer<TObject> p)
{
  return new TAttribObject(p);
}

template <>
inline const magic_pointer<TObject>
attrib_to_type<const magic_pointer<TObject> >(magic_pointer<TAttribute> atp, 
					      magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribObject> obj = rcp_static_cast<TAttribObject>(atp);

  if( !!obj && (obj->eType == FX_OBJECT) )
  {
    return obj->tValue;
  }
  cerr << "attrib_to_type(object): Cannot extract object!" << endl;
  return NULL;
}

template <>
inline magic_pointer<TAttribute> get_attrib<const magic_pointer<TObject> >()
{
  return new TAttribObject();
}


// ---------------------------------------------------------------------------
// magic_pointer<TImageIO>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<magic_pointer<TImageIO> >(magic_pointer<TImageIO> p)
{
  return FX_IMAGE_IO;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<magic_pointer<TImageIO> >(magic_pointer<TImageIO> p)
{
  return new TAttribImageIO(p);
}

template <>
inline magic_pointer<TImageIO>
attrib_to_type<magic_pointer<TImageIO> >(magic_pointer<TAttribute> atp, 
					 magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribImageIO> io = rcp_static_cast<TAttribImageIO>(atp);

  if( !!io && (io->eType == FX_IMAGE_IO) )
  {
    return io->tValue;
  }
  cerr << "attrib_to_type(ImageIO): Cannot extract ImageIO!" << endl;
  return NULL;
}

template <>
inline magic_pointer<TAttribute> get_attrib<magic_pointer<TImageIO> >()
{
  return new TAttribImageIO();
}

// ---------------------------------------------------------------------------
// const magic_pointer<TImageIO>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const magic_pointer<TImageIO> >(const magic_pointer<TImageIO> p)
{
  return FX_IMAGE_IO;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<const magic_pointer<TImageIO> >(const magic_pointer<TImageIO> p)
{
  return new TAttribImageIO(p);
}

template <>
inline const magic_pointer<TImageIO>
attrib_to_type<const magic_pointer<TImageIO> >(magic_pointer<TAttribute> atp, 
					       magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribImageIO> io = rcp_static_cast<TAttribImageIO>(atp);

  if( !!io && (io->eType == FX_IMAGE_IO) )
  {
    return io->tValue;
  }
  cerr << "attrib_to_type(ImageIO): Cannot extract ImageIO!" << endl;
  return NULL;
}

template <>
inline magic_pointer<TAttribute> get_attrib<const magic_pointer<TImageIO> >()
{
  return new TAttribImageIO();
}

// ---------------------------------------------------------------------------
// magic_pointer<TScene>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<magic_pointer<TScene> >(magic_pointer<TScene> p)
{
  return FX_SCENE;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<magic_pointer<TScene> >(magic_pointer<TScene> p)
{
  return new TAttribScene(p);
}

template <>
inline magic_pointer<TScene>
attrib_to_type<magic_pointer<TScene> >(magic_pointer<TAttribute> atp, 
				       magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribScene> scene = rcp_static_cast<TAttribScene>(atp);

  if( !!scene && (scene->eType == FX_SCENE) )
  {
    return scene->tValue;
  }
  cerr << "attrib_to_type(scene): Cannot extract scene!" << endl;
  return NULL;
}

template <>
inline magic_pointer<TAttribute> get_attrib<magic_pointer<TScene> >()
{
  return new TAttribScene();
}

// ---------------------------------------------------------------------------
// const magic_pointer<TScene>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const magic_pointer<TScene> >(const magic_pointer<TScene> p)
{
  return FX_SCENE;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<const magic_pointer<TScene> >(const magic_pointer<TScene> p)
{
  return new TAttribScene(p);
}

template <>
inline const magic_pointer<TScene>
attrib_to_type<const magic_pointer<TScene> >(magic_pointer<TAttribute> atp, 
					     magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribScene> scene = rcp_static_cast<TAttribScene>(atp);

  if( !!scene && (scene->eType == FX_SCENE) )
  {
    return scene->tValue;
  }
  cerr << "attrib_to_type(scene): Cannot extract scene!" << endl;
  return NULL;
}

template <>
inline magic_pointer<TAttribute> get_attrib<const magic_pointer<TScene> >()
{
  return new TAttribScene();
}

// ---------------------------------------------------------------------------
// magic_pointer<TAggregate>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<magic_pointer<TAggregate> >(magic_pointer<TAggregate> p)
{
  return FX_AGGREGATE;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<magic_pointer<TAggregate> >(magic_pointer<TAggregate> p)
{
  return new TAttribAggregate(p);
}

template <>
inline magic_pointer<TAggregate>
attrib_to_type<magic_pointer<TAggregate> >(magic_pointer<TAttribute> atp, 
					   magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribAggregate> obj = rcp_static_cast<TAttribAggregate>(atp);

  if( !!obj && (obj->eType == FX_AGGREGATE) )
  {
    if( !!obj->tValue )
    {
      if( obj->tValue->classType() == FX_AGGREGATE_CLASS )
      {
	return rcp_static_cast<TAggregate>(obj->tValue);
      }
    }
  }
  cerr << "attrib_to_type(aggregate): Cannot extract aggregate!" << endl;
  return NULL;
}

template <>
inline magic_pointer<TAttribute> get_attrib<magic_pointer<TAggregate> >()
{
  return new TAttribAggregate();
}

// ---------------------------------------------------------------------------
// const magic_pointer<TAggregate>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const magic_pointer<TAggregate> >(const magic_pointer<TAggregate> p)
{
  return FX_AGGREGATE;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<const magic_pointer<TAggregate> >(const magic_pointer<TAggregate> p)
{
  return new TAttribAggregate(p);
}

template <>
inline const magic_pointer<TAggregate>
attrib_to_type<const magic_pointer<TAggregate> >(magic_pointer<TAttribute> atp, 
						 magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribAggregate> obj = rcp_static_cast<TAttribAggregate>(atp);

  if( !!obj && (obj->eType == FX_AGGREGATE) )
  {
    if( !!obj->tValue )
    {
      if( obj->tValue->classType() == FX_AGGREGATE_CLASS )
      {
	return rcp_static_cast<TAggregate>(obj->tValue);
      }
    }
  }
  cerr << "attrib_to_type(aggregate): Cannot extract aggregate!" << endl;
  return NULL;
}

template <>
inline magic_pointer<TAttribute> get_attrib<const magic_pointer<TAggregate> >()
{
  return new TAttribAggregate();
}

/* =================================== */
template <>
inline EAttribType type_to_etype<magic_pointer<TObjectFilter> >(magic_pointer<TObjectFilter> p)
{
  return FX_OBJECT_FILTER;
}

template <>
inline EAttribType type_to_etype<magic_pointer<TImageFilter> >(magic_pointer<TImageFilter> p)
{
  return FX_IMAGE_FILTER;
}

// Junk to delete...
/*
inline EAttribType type_to_etype(magic_pointer<TLight> p)        { return FX_LIGHT; }

template <class T>
inline magic_pointer<TAttribute> type_to_attrib2(void)
{
  return type_to_attrib(T());
}

inline magic_pointer<TAttribute> type_to_attrib(void)
{
  cerr << "type_to_attrib: Non-templated version called";
  exit(1);
  return new TAttribute(FX_NONE);
}
*/

#endif /* !defined(EXTENDED_TYPE_FUNCTIONS_H) */

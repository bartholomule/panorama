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
#if       !defined(EXTENDED_ATTRIBUTE_H)
#define            EXTENDED_ATTRIBUTE_H

// extended_attribute.h -- An extension of the attribute heirarchy (from
// attribs.h and attribute.h) to work on some commonly used items.

#include "llapi/attribute.h"
#include "llapi/pattern.h"

struct TAttribPattern : public TAttribute
{

  magic_pointer<TPattern> tValue;
  
  TAttribPattern (void)                                 { eType = FX_PATTERN; }
  TAttribPattern (magic_pointer<TPattern> p): tValue(p) { eType = FX_PATTERN; }
  TAttribPattern (TColor c)
  {
    eType = FX_PATTERN;
    tValue = new TPattern(c);
  }
  TAttribPattern (TScalar s)
  {
    eType = FX_PATTERN;
    tValue = new TPattern(s);
  }
  TAttribPattern (TVector v)
  {
    eType = FX_PATTERN;
    tValue = new TPattern(TColor(v.x(),v.y(),v.z()));
  }  
  
  virtual string AttributeName() const { return "pattern"; }
  TATTRIB_CLONE_NEW_DEF(TAttribPattern);
  virtual string toString() const
  {
    string s = "pattern(";
    if( tValue )
    {
      s += tValue->className();
    }
    else
    {
      s += "NULL";
    }
    return s + ")";
  };
  
};  /* struct TAttribPattern */

#include "llapi/bsdf.h"

struct TAttribBsdf : public TAttribute
{

  magic_pointer<TBsdf> tValue;
  
  TAttribBsdf (void)                                   { eType = FX_BSDF; }
  TAttribBsdf (magic_pointer<TBsdf> p): tValue(p)      { eType = FX_BSDF; }
  
  virtual string AttributeName() const { return "bsdf"; }
  TATTRIB_CLONE_NEW_DEF(TAttribBsdf);
  virtual string toString() const
  {
    string s = "bsdf(";
    if( tValue )
    {
      s += tValue->className();
    }
    else
    {
      s += "NULL";
    }
    return s + ")";
  };  
};  /* struct TAttribBsdf */

#include "llapi/perturbation.h"

struct TAttribPerturbation : public TAttribute
{

  magic_pointer<TPerturbation> tValue;
  
  TAttribPerturbation (void)
  {
    eType = FX_PERTURBATION;
  }
  TAttribPerturbation (magic_pointer<TPerturbation> p):
    tValue(p)
  {
    eType = FX_PERTURBATION;
  }
  
  virtual string AttributeName() const { return "perturbation"; }
  TATTRIB_CLONE_NEW_DEF(TAttribPerturbation);
 
  virtual string toString() const
  {
    string s = "perturbation(";
    if( tValue )
    {
      s += tValue->className();
    }
    else
    {
      s += "NULL";
    }
    return s + ")";
  };  
};  /* struct TAttribPerturbation */

#include "llapi/image.h"
struct TAttribImage : public TAttribute
{
  magic_pointer<TImage> tValue;
  
  TAttribImage (void)
  {
    eType = FX_IMAGE;
  }
  TAttribImage (magic_pointer<TImage> p):
    tValue(p)
  {
    eType = FX_IMAGE;
  }
  
  virtual string AttributeName() const { return "image"; }
  TATTRIB_CLONE_NEW_DEF(TAttribImage);

  virtual string toString() const
  {
    if( tValue )
    {
      char buffer[1024];
      sprintf( buffer, "image(%d x %d)", int(tValue->width()), int(tValue->height()) );
      return buffer;
    }
    else
    {
      return "image(NULL)";
    }
  }  
}; /* struct TAttribImage */

#include "llapi/renderer.h"
struct TAttribRenderer : public TAttribute
{
  magic_pointer<TRenderer> tValue;
  
  TAttribRenderer (void)
  {
    eType = FX_RENDERER;
  }
  TAttribRenderer (magic_pointer<TRenderer> p):
    tValue(p)
  {
    eType = FX_RENDERER;
  }
  
  virtual string AttributeName() const { return "renderer"; }
  TATTRIB_CLONE_NEW_DEF(TAttribRenderer);

  virtual string toString() const
  {
    string s = "renderer(";
    if( tValue )
    {
      s += tValue->className();
    }
    else
    {
      s += "NULL";
    }
    return s + ")";
  }
}; /* struct TAttribRenderer */

#include "llapi/camera.h"
struct TAttribCamera : public TAttribute
{
  magic_pointer<TCamera> tValue;
  
  TAttribCamera (void)
  {
    eType = FX_CAMERA;
  }
  TAttribCamera (magic_pointer<TCamera> p):
    tValue(p)
  {
    eType = FX_CAMERA;
  }
  
  virtual string AttributeName() const { return "camera"; }
  TATTRIB_CLONE_NEW_DEF(TAttribCamera);
  virtual string toString() const
  {
    string s = "camera(";
    if( tValue )
    {
      s += tValue->className();
    }
    else
    {
      s += "NULL";
    }
    return s + ")";
  }
}; /* struct TAttribCamera */

#include "llapi/object.h"
struct TAttribObject : public TAttribute
{
  magic_pointer<TObject> tValue;

  TAttribObject (void)
  {
    eType = FX_OBJECT;
  }
  TAttribObject ( magic_pointer<TObject> p ):
    tValue(p)
  {
    eType = FX_OBJECT;
  }

  virtual string AttributeName() const { return "object"; }
  TATTRIB_CLONE_NEW_DEF(TAttribObject);

  virtual string toString() const
  {
    string s = "object(";
    if( tValue )
    {
      s += tValue->className();
    }
    else
    {
      s += "NULL";
    }
    return s + ")";
  }  
}; /* struct TAttribObject */

#include "llapi/scene.h"
struct TAttribScene : public TAttribute
{
  magic_pointer<TScene> tValue;

  TAttribScene (void)
  {
    eType = FX_SCENE;
  }
  TAttribScene ( magic_pointer<TScene> p ):
    tValue(p)
  {
    eType = FX_SCENE;
  }

  virtual string AttributeName() const { return "scene"; }
  TATTRIB_CLONE_NEW_DEF(TAttribScene);

  virtual string toString() const
  {
    string s = "scene(";
    if( tValue )
    {
      s += tValue->className();
    }
    else
    {
      s += "NULL";
    }
    return s + ")";
  }  
}; /* struct TAttribScene */

#include "llapi/material.h"
struct TAttribMaterial : public TAttribute
{
  magic_pointer<TMaterial> tValue;

  TAttribMaterial (void)
  {
    eType = FX_MATERIAL;
  }
  TAttribMaterial ( magic_pointer<TMaterial> p ):
    tValue(p)
  {
    eType = FX_MATERIAL;
  }

  virtual string AttributeName() const { return "material"; }
  TATTRIB_CLONE_NEW_DEF(TAttribMaterial);

  virtual string toString() const
  {
    string s = "material(";
    if( tValue )
    {
      s += tValue->className();
    }
    else
    {
      s += "NULL";
    }
    return s + ")";
  }
}; /* struct TAttribMaterial */

#include "llapi/image_io.h"
struct TAttribImageIO : public TAttribute
{
  magic_pointer<TImageIO> tValue;

  TAttribImageIO (void)
  {
    eType = FX_IMAGE_IO;
  }
  TAttribImageIO ( magic_pointer<TImageIO> p ):
    tValue(p)
  {
    eType = FX_IMAGE_IO;
  }

  virtual string AttributeName() const { return "imageio"; }
  TATTRIB_CLONE_NEW_DEF(TAttribImageIO);

  virtual string toString() const
  {
    string s = "imageio(";
    if( tValue )
    {
      s += tValue->className();
    }
    else
    {
      s += "NULL";
    }
    return s + ")";
  }
}; /* struct TAttribImageIO */

#include "hlapi/aggregate.h"
struct TAttribAggregate : public TAttribute
{
  magic_pointer<TAggregate> tValue;

  TAttribAggregate (void)
  {
    eType = FX_AGGREGATE;
  }
  TAttribAggregate ( magic_pointer<TAggregate> p ):
    tValue(p)
  {
    eType = FX_AGGREGATE;
  }

  virtual string AttributeName() const { return "aggregate"; }
  TATTRIB_CLONE_NEW_DEF(TAttribAggregate);

  virtual string toString() const
  {
    string s = "aggregate(";
    if( tValue )
    {
      s += tValue->className();
    }
    else
    {
      s += "NULL";
    }
    return s + ")";
  }  
}; /* struct TAttribAggregate */

magic_pointer<TAttribPattern> get_pattern(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribBsdf>    get_bsdf(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribPerturbation> get_perturbation(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribImage> get_image(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribRenderer> get_renderer(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribCamera> get_camera(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribObject> get_object(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribScene> get_scene(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribMaterial> get_material(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribImageIO> get_imageio(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribAggregate> get_aggregate(const magic_pointer<TAttribute> attr);

#endif /* !defined(EXTENDED_ATTRIBUTE_H) */

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

#include "llapi/bsdf.h"
#include "llapi/perturbation.h"
#include "llapi/image.h"
#include "llapi/renderer.h"
#include "llapi/camera.h"
#include "llapi/object.h"
#include "llapi/scene.h"
#include "llapi/material.h"
#include "llapi/image_io.h"
#include "hlapi/aggregate.h"


namespace panorama
{

#if 0
  struct TAttribPattern : public TAttribute
  {

    rc_pointer<TPattern> tValue;

    TAttribPattern(void) { eType = FX_PATTERN; }
    TAttribPattern(rc_pointer<TPattern> p): tValue(p) { eType = FX_PATTERN; }
    TAttribPattern(TColor c)
    {
      eType = FX_PATTERN;
      tValue.set(new TPattern(c));
    }
    TAttribPattern (TScalar s)
    {
      eType = FX_PATTERN;
      tValue.set(new TPattern(s));
    }
    TAttribPattern (TVector v)
    {
      eType = FX_PATTERN;
      tValue.set(new TPattern(TColor(v.x(),v.y(),v.z())));
    }

    virtual std::string AttributeName() const { return "pattern"; }
    virtual TAttribPattern* clone_new() const { return new TAttribPattern(*this); }
    virtual std::string toString() const
    {
      std::string s = "pattern(";
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


  struct TAttribBsdf : public TAttribute
  {

    rc_pointer<TBsdf> tValue;

    TAttribBsdf (void)                                   { eType = FX_BSDF; }
    TAttribBsdf (rc_pointer<TBsdf> p): tValue(p)      { eType = FX_BSDF; }

    virtual std::string AttributeName() const { return "bsdf"; }
    virtual TAttribBsdf* clone_new() const { return new TAttribBsdf(*this); }
    virtual std::string toString() const
    {
      std::string s = "bsdf(";
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

  struct TAttribPerturbation : public TAttribute
  {

    rc_pointer<TPerturbation> tValue;

    TAttribPerturbation (void)
    {
      eType = FX_PERTURBATION;
    }
    TAttribPerturbation (rc_pointer<TPerturbation> p):
      tValue(p)
    {
      eType = FX_PERTURBATION;
    }

    virtual std::string AttributeName() const { return "perturbation"; }
    virtual TAttribPerturbation* clone_new() const { return new TAttribPerturbation(*this); }

    virtual std::string toString() const
    {
      std::string s = "perturbation(";
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

  struct TAttribImage : public TAttribute
  {
    rc_pointer<TImage> tValue;

    TAttribImage (void)
    {
      eType = FX_IMAGE;
    }
    TAttribImage (rc_pointer<TImage> p):
      tValue(p)
    {
      eType = FX_IMAGE;
    }

    virtual std::string AttributeName() const { return "image"; }
    virtual TAttribImage* clone_new() const { return new TAttribImage(*this); }

    virtual std::string toString() const
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

  struct TAttribRenderer : public TAttribute
  {
    rc_pointer<TRenderer> tValue;

    TAttribRenderer (void)
    {
      eType = FX_RENDERER;
    }
    TAttribRenderer (rc_pointer<TRenderer> p):
      tValue(p)
    {
      eType = FX_RENDERER;
    }

    virtual std::string AttributeName() const { return "renderer"; }
    virtual TAttribRenderer* clone_new() const { return new TAttribRenderer(*this); }

    virtual std::string toString() const
    {
      std::string s = "renderer(";
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

  struct TAttribCamera : public TAttribute
  {
    rc_pointer<TCamera> tValue;

    TAttribCamera (void)
    {
      eType = FX_CAMERA;
    }
    TAttribCamera (rc_pointer<TCamera> p):
      tValue(p)
    {
      eType = FX_CAMERA;
    }

    virtual std::string AttributeName() const { return "camera"; }
    virtual TAttribCamera* clone_new() const { return new TAttribCamera(*this); }
    virtual std::string toString() const
    {
      std::string s = "camera(";
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

  struct TAttribObject : public TAttribute
  {
    rc_pointer<TObject> tValue;

    TAttribObject (void)
    {
      eType = FX_OBJECT;
    }
    TAttribObject ( rc_pointer<TObject> p ):
      tValue(p)
    {
      eType = FX_OBJECT;
    }

    virtual std::string AttributeName() const { return "object"; }
    virtual TAttribObject* clone_new() const { return new TAttribObject(*this); }

    virtual std::string toString() const
    {
      std::string s = "object(";
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

  struct TAttribScene : public TAttribute
  {
    rc_pointer<TScene> tValue;

    TAttribScene (void)
    {
      eType = FX_SCENE;
    }
    TAttribScene ( rc_pointer<TScene> p ):
      tValue(p)
    {
      eType = FX_SCENE;
    }

    virtual std::string AttributeName() const { return "scene"; }
    virtual TAttribScene* clone_new() const { return new TAttribScene(*this); }

    virtual std::string toString() const
    {
      std::string s = "scene(";
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

  struct TAttribMaterial : public TAttribute
  {
    rc_pointer<TMaterial> tValue;

    TAttribMaterial (void)
    {
      eType = FX_MATERIAL;
    }
    TAttribMaterial ( rc_pointer<TMaterial> p ):
      tValue(p)
    {
      eType = FX_MATERIAL;
    }

    virtual std::string AttributeName() const { return "material"; }
    virtual TAttribMaterial* clone_new() const { return new TAttribMaterial(*this); }

    virtual std::string toString() const
    {
      std::string s = "material(";
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

  struct TAttribImageIO : public TAttribute
  {
    rc_pointer<TImageIO> tValue;

    TAttribImageIO (void)
    {
      eType = FX_IMAGE_IO;
    }
    TAttribImageIO ( rc_pointer<TImageIO> p ):
      tValue(p)
    {
      eType = FX_IMAGE_IO;
    }

    virtual std::string AttributeName() const { return "imageio"; }
    virtual TAttribImageIO* clone_new() const { return new TAttribImageIO(*this); }

    virtual std::string toString() const
    {
      std::string s = "imageio(";
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

  struct TAttribAggregate : public TAttribute
  {
    rc_pointer<TAggregate> tValue;

    TAttribAggregate (void)
    {
      eType = FX_AGGREGATE;
    }
    TAttribAggregate ( rc_pointer<TAggregate> p ):
      tValue(p)
    {
      eType = FX_AGGREGATE;
    }

    virtual std::string AttributeName() const { return "aggregate"; }
    virtual TAttribAggregate* clone_new() const { return new TAttribAggregate(*this); }

    virtual std::string toString() const
    {
      std::string s = "aggregate(";
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

  rc_pointer<TAttribPattern> get_pattern(const rc_pointer<TAttribute> attr);
  rc_pointer<TAttribBsdf>    get_bsdf(const rc_pointer<TAttribute> attr);
  rc_pointer<TAttribPerturbation> get_perturbation(const rc_pointer<TAttribute> attr);
  rc_pointer<TAttribImage> get_image(const rc_pointer<TAttribute> attr);
  rc_pointer<TAttribRenderer> get_renderer(const rc_pointer<TAttribute> attr);
  rc_pointer<TAttribCamera> get_camera(const rc_pointer<TAttribute> attr);
  rc_pointer<TAttribObject> get_object(const rc_pointer<TAttribute> attr);
  rc_pointer<TAttribScene> get_scene(const rc_pointer<TAttribute> attr);
  rc_pointer<TAttribMaterial> get_material(const rc_pointer<TAttribute> attr);
  rc_pointer<TAttribImageIO> get_imageio(const rc_pointer<TAttribute> attr);
  rc_pointer<TAttribAggregate> get_aggregate(const rc_pointer<TAttribute> attr);
#endif /* 0 */

} // end namespace panorama

#endif /* !defined(EXTENDED_ATTRIBUTE_H) */

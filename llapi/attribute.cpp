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

#include "attribute.h"
#include "extended_attribute.h"
#include <cstdio>
#include <cstdlib>
#include <strings.h>

magic_pointer<TAttribInt>     get_int(magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribInt> retval;
  if( !!attr )
  {
    switch(attr->eType)
    {
    case FX_INTEGER:
      retval = rcp_static_cast<TAttribInt>(attr);
      break;
    case FX_REAL:
      retval = (magic_pointer<TAttribInt>)new TAttribInt(int(rcp_static_cast<TAttribReal>(attr)->tValue));
      break;
    case FX_BOOL:
      retval = (magic_pointer<TAttribInt>)new TAttribInt(int(rcp_static_cast<TAttribBool>(attr)->tValue));
      break;
    case FX_STRING:
    case FX_STRING_LIST:
      {
	magic_pointer<TAttribString> tas = rcp_static_cast<TAttribString>(attr);
	string s = tas->tValue;

	const char* scp = s.c_str();
	char* ptr;

	long value = strtol(scp, &ptr, 10);

	if( (ptr - scp) == int(s.length()) )
	{
	  retval = (magic_pointer<TAttribInt>)new TAttribInt(value);
	}
      }
      break;
    default:
      // Retval is NULL!!!
      break;
    }
  }
  return retval;
}

magic_pointer<TAttribReal>    get_real(magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribReal> retval;
  if( !!attr )
  {
    switch(attr->eType)
    {
    case FX_INTEGER:
      retval = (magic_pointer<TAttribReal>)new TAttribReal(TScalar(rcp_static_cast<TAttribInt>(attr)->tValue));
      break;
    case FX_REAL:
      retval = (magic_pointer<TAttribReal>)rcp_static_cast<TAttribReal>(attr);
      break;
    case FX_BOOL:
      retval = (magic_pointer<TAttribReal>)new TAttribReal(TScalar(int(rcp_static_cast<TAttribBool>(attr)->tValue)));
      break;
    case FX_STRING:
    case FX_STRING_LIST:
      {
	magic_pointer<TAttribString> tas = rcp_static_cast<TAttribString>(attr);
	string s = tas->tValue;

	const char* scp = s.c_str();
	char* ptr;

	double value = strtod(scp, &ptr);

	if( (ptr - scp) == int(s.length()) )
	{
	  retval = (magic_pointer<TAttribReal>)new TAttribReal(value);
	}
      }
      break;
    default:
      // Retval is NULL!!!
      break;
    }
  }
  return retval;  
}

magic_pointer<TAttribBool>    get_bool(magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribBool> retval;
  if( !!attr )
  {
    switch(attr->eType)
    {
    case FX_BOOL:
      retval = rcp_static_cast<TAttribBool>(attr);
      break;
    case FX_INTEGER:
      retval = (magic_pointer<TAttribBool>)new TAttribBool(!!(rcp_static_cast<TAttribInt>(attr)->tValue));
      break;
    case FX_STRING:
    case FX_STRING_LIST:
      {
	magic_pointer<TAttribString> tas = rcp_static_cast<TAttribString>(attr);
	const string& s = tas->tValue;
	
	const char* scp = s.c_str();
	char* ptr;
	
	if(strcasecmp(scp, "true") == 0)
	{
	  retval = (magic_pointer<TAttribBool>)new TAttribBool(true);
	}
	else if(strcasecmp(scp, "false") == 0)
	{
	  retval = (magic_pointer<TAttribBool>)new TAttribBool(false);	  
	}
	else
	{
	  long value = strtol(scp, &ptr, 10);
	  
	  if( (ptr - scp) == int(s.length()) )
	  {
	    retval = (magic_pointer<TAttribBool>)new TAttribBool(!!value);
	  }
	}
      }
      break;
    default:
      // else retval is NULL!
      break;
    }
  }
  return retval;
}
  

magic_pointer<TAttribString>  get_string(magic_pointer<TAttribute> attr)
{
  char junk_buffer[1024];
  
  magic_pointer<TAttribString> retval;
  if( !!attr )
  {
    switch(attr->eType)
    {
      // These two are treated identically, as the stringlist is a subclass.
    case FX_STRING:
    case FX_STRING_LIST:      
      retval = rcp_static_cast<TAttribString>(attr);
      break;      
    case FX_INTEGER:
      sprintf(junk_buffer,"%d", rcp_static_cast<TAttribInt>(attr)->tValue);
      retval = (magic_pointer<TAttribString>)new TAttribString(junk_buffer);
      break;
    case FX_REAL:
      sprintf(junk_buffer,"%12.7f",rcp_static_cast<TAttribReal>(attr)->tValue);
      retval = (magic_pointer<TAttribString>)new TAttribString(junk_buffer);      
      break;
    case FX_BOOL:
      sprintf(junk_buffer,"%d", rcp_static_cast<TAttribInt>(attr)->tValue);
      retval = (magic_pointer<TAttribString>)new TAttribString(junk_buffer);      
      break;      
    default:
      // Retval is NULL!!!
      break;
    }
  }
  return retval;  
}

magic_pointer<TAttribStringList>
get_stringlist(const magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribStringList> retval;
  if( !!attr )
  {
    switch(attr->eType)
    {
    case FX_STRING:
      {
	string value = rcp_static_cast<TAttribString>(attr)->tValue;
	vector<string> choices(1,value);
	retval = (magic_pointer<TAttribStringList>)new TAttribStringList (choices);
      }
      break;
    case FX_STRING_LIST:
      retval = rcp_static_cast<TAttribStringList>(attr);
      break;
    default:
      // retval == NULL
      break;
    }
  }
  return retval;
}

magic_pointer<TAttribColor>   get_color(magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribColor> retval;
  if( !!attr )
  {
    switch(attr->eType)
    {
    case FX_INTEGER:
      retval = (magic_pointer<TAttribColor>)new TAttribColor((double)rcp_static_cast<TAttribInt>(attr)->tValue);
      break;      
    case FX_REAL:
      retval = (magic_pointer<TAttribColor>)new TAttribColor(rcp_static_cast<TAttribReal>(attr)->tValue);
      break;
    case FX_VECTOR:
      retval = (magic_pointer<TAttribColor>)new TAttribColor(rcp_static_cast<TAttribVector>(attr)->tValue);
      break;      
    case FX_COLOR:
      retval = rcp_static_cast<TAttribColor>(attr);
      break;      
    default:
      // Retval is NULL!!!
      break;
    }
  }
  return retval;    
}

magic_pointer<TAttribVector>  get_vector(magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribVector> retval;
  if( !!attr )
  {
    switch(attr->eType)
    {
    case FX_INTEGER:
      retval = (magic_pointer<TAttribVector>)new TAttribVector((double)rcp_static_cast<TAttribInt>(attr)->tValue);
      break;      
    case FX_REAL:
      retval = (magic_pointer<TAttribVector>)new TAttribVector(rcp_static_cast<TAttribReal>(attr)->tValue);
      break;
    case FX_VECTOR:
      retval = rcp_static_cast<TAttribVector>(attr);
      break;      
    default:
      // Retval is NULL!!!
      break;
    }
  }
  return retval;  
}

magic_pointer<TAttribVector2> get_vector2(magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribVector2> retval;
  if( !!attr )
  {
    switch(attr->eType)
    {
    case FX_INTEGER:
      retval = (magic_pointer<TAttribVector2>)new TAttribVector2((double)rcp_static_cast<TAttribInt>(attr)->tValue);
      break;      
    case FX_REAL:
      retval = (magic_pointer<TAttribVector2>)new TAttribVector2(rcp_static_cast<TAttribReal>(attr)->tValue);
      break;
    case FX_VECTOR2:
      retval = rcp_static_cast<TAttribVector2>(attr);
      break;      
    default:
      // Retval is NULL!!!
      break;
    }
  }
  return retval;  
}

magic_pointer<TAttribPattern> get_pattern(const magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribPattern> retval;
  if( !!attr )
  {
    switch(attr->eType)
    {
    case FX_INTEGER:
      {
	TScalar s = rcp_static_cast<TAttribInt>(attr)->tValue;
	cout << "attr: creating pattern from int " << s << endl;
	retval = (magic_pointer<TAttribPattern>)new TAttribPattern(s);
      }
      break;      
    case FX_REAL:
      {
	TScalar s = rcp_static_cast<TAttribReal>(attr)->tValue;
	cout << "attr: creating pattern from real " << s << endl;
	retval = (magic_pointer<TAttribPattern>)new TAttribPattern(s);
      }
      break;
    case FX_VECTOR:
      {
	TVector v = rcp_static_cast<TAttribVector>(attr)->tValue;
	cout << "attr: creating pattern from vector" << endl;
	retval = (magic_pointer<TAttribPattern>)new TAttribPattern(v);
      }
      break;      
    case FX_COLOR:
      {
	cout << "ick.....:" << attr->toString() << endl;
	TColor c = rcp_static_cast<TAttribColor>(attr)->tValue;
	cout << "attr: creating pattern from color"
	     << " (" << c.red() << "," << c.green() << "," << c.blue() << ")"
	     << endl;			    			    	
	retval = (magic_pointer<TAttribPattern>)new TAttribPattern(c);
      }
      break;
    case FX_PATTERN:
      {
	retval = rcp_static_cast<TAttribPattern>(attr);
	cout << "attr: creating pattern from pattern" << endl;
      }
      break;      
    default:
      // Retval is NULL!!!
      break;
    }
  }
  return retval;      
}


magic_pointer<TAttribBsdf> get_bsdf(const magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribBsdf> retval;
  if( !!attr )
  {
    if( attr->eType == FX_BSDF )
    {
      retval = rcp_static_cast<TAttribBsdf>(attr);
    }
  }
  return retval;
}

magic_pointer<TAttribPerturbation>
get_perturbation(const magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribPerturbation> retval;
  if( !!attr )
  {
    if( attr->eType == FX_PERTURBATION )
    {
      retval = rcp_static_cast<TAttribPerturbation>(attr);
    }    
  }
  return retval;  
}

magic_pointer<TAttribImage>
get_image(const magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribImage> retval;
  if( !!attr )
  {
    if( attr->eType == FX_IMAGE )
    {
      retval = rcp_static_cast<TAttribImage>(attr);
    }    
  }
  return retval;    
}

magic_pointer<TAttribRenderer>
get_renderer(const magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribRenderer> retval;
  if( !!attr )
  {
    if( attr->eType == FX_RENDERER )
    {
      retval = rcp_static_cast<TAttribRenderer>(attr);
    }    
  }
  return retval;    
}

magic_pointer<TAttribCamera>
get_camera(const magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribCamera> retval;
  if( !!attr )
  {
    if( attr->eType == FX_CAMERA )
    {
      retval = rcp_static_cast<TAttribCamera>(attr);
    }    
  }
  return retval;    
}


magic_pointer<TAttribObject>
get_object(const magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribObject> retval;
  if( !!attr )
  {
    if( attr->eType == FX_OBJECT )
    {
      retval = rcp_static_cast<TAttribObject>(attr);
    }
    else if( attr->eType == FX_AGGREGATE )
    {
      magic_pointer<TAttribAggregate> agg = rcp_static_cast<TAttribAggregate>(attr);
      magic_pointer<TObject> obj = rcp_static_cast<TObject>(agg->tValue);
      retval = (magic_pointer<TAttribObject>)new TAttribObject(obj);
    }
  }
  return retval;    
}

magic_pointer<TAttribAggregate>
get_aggregate(const magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribAggregate> retval;
  if( !!attr )
  {
    if( attr->eType == FX_AGGREGATE )
    {
      retval = rcp_static_cast<TAttribAggregate>(attr);
    }    
  }
  return retval;    
}

magic_pointer<TAttribScene>
get_scene(const magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribScene> retval;
  if( !!attr )
  {
    if( attr->eType == FX_SCENE )
    {
      retval = rcp_static_cast<TAttribScene>(attr);
    }    
  }
  return retval;    
}

magic_pointer<TAttribMaterial>
get_material(const magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribMaterial> retval;
  if( !!attr )
  {
    if( attr->eType == FX_MATERIAL )
    {
      retval = rcp_static_cast<TAttribMaterial>(attr);
    }    
  }
  return retval;    
}

magic_pointer<TAttribImageIO>
get_imageio(const magic_pointer<TAttribute> attr)
{
  magic_pointer<TAttribImageIO> retval;
  if( !!attr )
  {
    if( attr->eType == FX_IMAGE_IO )
    {
      retval = rcp_static_cast<TAttribImageIO>(attr);
    }    
  }
  return retval;    
}



magic_pointer<TBaseClass> attr_to_base(const magic_pointer<TAttribute> attr)
{
  if( !!attr )
  {
    switch( attr->eType )
    {
    case FX_COLOR:
      return (magic_pointer<TBaseClass>)new TColor(get_color(attr)->tValue);
    case FX_VECTOR:
      return (magic_pointer<TBaseClass>)new TVector(get_vector(attr)->tValue);
    case FX_MATERIAL:
      return rcp_static_cast<TBaseClass>(get_material(attr)->tValue);
    case FX_PATTERN:
      return rcp_static_cast<TBaseClass>(get_pattern(attr)->tValue);
    case FX_PERTURBATION:
      return rcp_static_cast<TBaseClass>(get_perturbation(attr)->tValue);      
    case FX_OBJECT:
      return rcp_static_cast<TBaseClass>(get_object(attr)->tValue);
    case FX_AGGREGATE:
      return rcp_static_cast<TBaseClass>(get_aggregate(attr)->tValue);      
    case FX_RENDERER:
      return rcp_static_cast<TBaseClass>(get_renderer(attr)->tValue);
    case FX_SCENE:
      return rcp_static_cast<TBaseClass>(get_scene(attr)->tValue);
    case FX_BSDF:
      return rcp_static_cast<TBaseClass>(get_bsdf(attr)->tValue);
    case FX_CAMERA:
      return rcp_static_cast<TBaseClass>(get_camera(attr)->tValue);
    case FX_IMAGE_IO:
      return rcp_static_cast<TBaseClass>(get_imageio(attr)->tValue);

    // image filter?
    // object filter?
    // bounding box?
    // atm object?
    // scene io?      
    default:
      break;
    }
  }
  return magic_pointer<TBaseClass>();
}

magic_pointer<TAttribute> base_to_attr(const magic_pointer<TBaseClass> base)
{
  if( !!base )
  {
    switch( base->classType() )
    {
    case FX_COLOR_CLASS:
      return (user_arg_type)new TAttribColor(*rcp_static_cast<TColor>(base));
      break;
    case FX_VECTOR_CLASS:
      return (user_arg_type)new TAttribVector(*rcp_static_cast<TVector>(base));
      break;
    case FX_PATTERN_CLASS:
      return (user_arg_type)new TAttribPattern(rcp_static_cast<TPattern>(base));
      break;
    case FX_PERTURBATION_CLASS:
      return (user_arg_type)new TAttribPerturbation(rcp_static_cast<TPerturbation>(base));
      break;
    case FX_MATERIAL_CLASS:
      return (user_arg_type)new TAttribMaterial(rcp_static_cast<TMaterial>(base));
      break;
    case FX_LIGHT_CLASS:
      return (user_arg_type)new TAttribObject(rcp_static_cast<TObject>(base));
      break;
    case FX_CAMERA_CLASS:
      return (user_arg_type)new TAttribCamera(rcp_static_cast<TCamera>(base));
      break;
    case FX_OBJECT_CLASS:
      return (user_arg_type)new TAttribObject(rcp_static_cast<TObject>(base));
      break;
    case FX_AGGREGATE_CLASS:
      return (user_arg_type)new TAttribAggregate(rcp_static_cast<TAggregate>(base));
      break;      
    case FX_RENDERER_CLASS:
      return (user_arg_type)new TAttribRenderer(rcp_static_cast<TRenderer>(base));
      break;
    case FX_SCENE_CLASS:
      return (user_arg_type)new TAttribScene(rcp_static_cast<TScene>(base));
      break;
    case FX_BSDF_CLASS:
      return (user_arg_type)new TAttribBsdf(rcp_static_cast<TBsdf>(base));
      break;
    case FX_IMAGE_IO_CLASS:
      return (user_arg_type)new TAttribImageIO(rcp_static_cast<TImageIO>(base));
      break;
    default:
      break;
    }
    // image filter?
    // object filter?
    // bounding box?
    // atm object?
    // scene io?
    cerr << "base_to_attr: Cannot determine classtype of " << base->className() << endl;
    return (user_arg_type)new TAttribute();
  }
  else
  {
    cerr << "base_to_attr: given a null base" << endl;
    return (user_arg_type)new TAttribute();
  }  
}

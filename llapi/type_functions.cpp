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
#include "procedural.h"
#include "type_functions.h"

string EAttribType_to_str (EAttribType eTYPE)
{

  /* This function is pretty dumb, but I (KH) couldn't find another one
     anywhere else.  Added on 07Aug2000 to the parser, moved here on 01Sep2001,
     while attempting to further expand the abilities of panorama. */ 

  switch ( eTYPE )
  {
  case FX_NONE: 
    return "none";
    
  case FX_INTEGER: 
    return "int";
    
  case FX_REAL: 
    return "real";
    
  case FX_BOOL: 
    return "bool";
    
  case FX_STRING: 
    return "string";
    
  case FX_STRING_LIST: 
    return "string_list";

  case FX_COLOR: 
    return "color";
    
  case FX_VECTOR: 
    return "vector";
    
  case FX_VECTOR2: 
    return "2d_vector";
    
  case FX_IMAGE: 
    return "image";
    
  case FX_BSDF: 
    return "bsdf";
    
  case FX_CAMERA: 
    return "camera";
    
  case FX_LIGHT: 
    return "light";
    
  case FX_MATERIAL: 
    return "material";
    
  case FX_PATTERN: 
    return "pattern";
    
  case FX_PERTURBATION: 
    return "perturbation";
    
  case FX_RENDERER: 
    return "renderer";
    
  case FX_OBJECT: 
    return "object";
    
  case FX_OBJECT_FILTER: 
    return "object_filter";
    
  case FX_IMAGE_FILTER: 
    return "image_filter";
    
  case FX_IMAGE_IO:
    return "image_io";

  case FX_SCENE:
    return "scene";

  default: 
    return "unknown";
  }

}  /* EAttribType_to_str() */


EAttribType str_to_EAttribType (const string& s)
{
  if( s == "none" )
  {
    return FX_NONE;
  }
  else if( s == "int" )
  {
    return FX_INTEGER;
  }
  else if( s == "real" )
  {
    return FX_REAL;
  }
  else if( s == "bool" )
  {
    return FX_BOOL;
  }
  else if( s == "string" )
  {
    return FX_STRING;
  }
  else if( s == "string_list" )
  {
    return FX_STRING_LIST;
  }
  else if( s == "color" )
  {
    return FX_COLOR;
  }
  else if( s == "vector" )
  {
    return FX_VECTOR;
  }
  else if( s == "2d_vector" )
  {
    return FX_VECTOR2;
  }
  else if( s == "image" )
  {
    return FX_IMAGE;
  }
  else if( s == "bsdf" )
  {
    return FX_BSDF;
  }
  else if( s == "camera" )
  {
    return FX_CAMERA;
  }
  else if( s == "light" )
  {
    return FX_LIGHT;
  }
  else if( s == "material" )
  {
    return FX_MATERIAL;
  }
  else if( s == "pattern" )
  {
    return FX_PATTERN;
  }
  else if( s == "perturbation" )
  {
    return FX_PERTURBATION;
  }
  else if( s == "renderer" )
  {
    return FX_RENDERER;
  }
  else if( s == "object" )
  {
    return FX_OBJECT;
  }
  else if( s == "object_filter" )
  {
    return FX_OBJECT_FILTER;
  }
  else if( s == "image_filter" )
  {
    return FX_IMAGE_FILTER;
  }
  else if( s == "image_io" )
  {
    return FX_IMAGE_IO;
  }
  else if( s == "scene" )
  {
    return FX_SCENE;
  }
  else if( s == "unknown" )
  {
    return FX_NONE;
  }
  else
  {
    return FX_NONE;
  }  
}

bool types_match(const magic_pointer<TAttribute>& a1,
		 const magic_pointer<TAttribute>& a2)
{
  if( !a1 || !a2 )
  {
    GOM.error() << "One of the args is NULL!" << endl;
    if( !a1 )
      GOM.error() << "it is a1! [ the required parameter ]" << endl;
    else
      GOM.error() << "it is a2! [ the coerceable argument passed in ]" << endl;
    return false;
  }
  //  GOM.debug() << "types_match: comparing " << a1->AttributeName()
  //       << " and " << a2->AttributeName() << endl;
  
  if( a1->eType == a2->eType )
  {
    return true;
  }
  switch( a1->eType )
  {
    case FX_NONE:
      // Must be none to match...
      //      return ( a2->eType == FX_NONE );
      return true;

    case FX_INTEGER:
      // int, or convertables...
      if( a2->eType == FX_INTEGER ||
	  a2->eType == FX_REAL ||
	  a2->eType == FX_BOOL )
      {
	return true;
      }
      else
      {
	return false;
      }
      
    case FX_REAL:
      // Real, or convertables...
      if( a2->eType == FX_INTEGER ||
	  a2->eType == FX_REAL ||
	  a2->eType == FX_BOOL )
      {
	return true;
      }
      else
      {
	return false;
      }      

    case FX_BOOL:
      // int/bool
      if( a2->eType == FX_INTEGER || a2->eType == FX_BOOL )
      {
	return true;
      }
      else
      {
	return false;
      }

    case FX_STRING:
      // String types...
      if( a2->eType == FX_STRING || a2->eType == FX_STRING_LIST )
      {
	return true;
      }
      // convertables...
      else if( a2->eType == FX_INTEGER ||
	       a2->eType == FX_REAL ||
	       a2->eType == FX_BOOL )
      {
	return true;
      }
      else
      {
	return false;
      }
    case FX_STRING_LIST:
      // String types...
      if( a2->eType == FX_STRING || a2->eType == FX_STRING_LIST )
      {
	return true;
      }
      else
      {
	return false;
      }
    case FX_COLOR:
      if( a2->eType == FX_REAL ||
	  a2->eType == FX_VECTOR ||
	  a2->eType == FX_COLOR ||
          a2->eType == FX_ARRAY )
      {
	return true;
      }
      else
      {
	return false;
      }
    case FX_VECTOR:
      if( a2->eType == FX_REAL ||
	  a2->eType == FX_VECTOR ||
          a2->eType == FX_ARRAY )
      {
	return true;
      }
      else
      {
	return false;
      }      
    case FX_VECTOR2:
      if( a2->eType == FX_REAL ||
	  a2->eType == FX_VECTOR2 ||
          a2->eType == FX_ARRAY )
      {
	return true;
      }
      else
      {
	return false;
      }      
    case FX_IMAGE:
      return (a2->eType == FX_IMAGE);
    case FX_BSDF:
      return ( a2->eType == FX_BSDF );
    case FX_CAMERA:
      return ( a2->eType == FX_CAMERA );
    case FX_LIGHT:
      return ( a2->eType == FX_LIGHT );
    case FX_MATERIAL:
      return ( a2->eType == FX_MATERIAL );
    case FX_PATTERN:
      if( a2->eType == FX_REAL ||
	  a2->eType == FX_VECTOR ||
	  a2->eType == FX_COLOR ||
	  a2->eType == FX_PATTERN ||
          a2->eType == FX_ARRAY )
      {
	return true;
      }
      else
      {
	return false;
      }      
    case FX_PERTURBATION:
      return ( a2->eType == FX_PERTURBATION );
    case FX_RENDERER:
      return ( a2->eType == FX_RENDERER );
    case FX_OBJECT:
      return ( a2->eType == FX_OBJECT || a2->eType == FX_AGGREGATE );
    case FX_OBJECT_FILTER:
      return ( a2->eType == FX_OBJECT_FILTER );      
    case FX_IMAGE_FILTER:
      return ( a2->eType == FX_IMAGE_FILTER );
    case FX_SCENE:
      return ( a2->eType == FX_SCENE );            
    default: 
      return false;
  }
}









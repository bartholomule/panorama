/*
*  Copyright (C) 2002 Kevin Harris
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
#include "attrib_tweak.h"
#include "rt_io.h"


// The next section is taken from the parser.y file.  Where does it truly
// belong so that multiple files can use it?  
//---------------------------------------------------------------------------
typedef TSceneRT::BASE_OBJECT_TYPE BASE_OBJECT_TYPE;
typedef TSceneRT::attrib_type attrib_type;

#define POP()           top(); TSceneRT::_tDataStack.pop()  // Fix to STL's pop()

#define DATA		(TSceneRT::_tDataStack.top())
#define DATAMAP         (TSceneRT::_tDataMap)
#define DATASTACK       (TSceneRT::_tDataStack) 
#define SCENE		(TSceneRT::_ptParsedScene)
#define PARENT_OBJECT   (TSceneRT::_ptParent)
#define WORLD           (TSceneRT::_ptWorld)
extern void rt_error (const std::string& rksTEXT);
extern void rt_warning (const std::string& rksTEXT);
//---------------------------------------------------------------------------

magic_pointer<TProcedural> get_procedural_var(magic_pointer<TAttribute> p, bool active)
{

  if( !p )
  {
    if( active )
    {
      GOM.error() << "Cannot get a procedural var from a NULL object" << std::endl;
      exit(1);
    }
    else
    {
      return (magic_pointer<TProcedural>)NULL;
    }
  }

  //  GOM.debug() << "getting var from " << p->toString() << std::endl;

  //  GOM.debug() << "obj..." << std::endl;
  magic_pointer<TAttribObject> obj = get_object(p);
  if( !!obj )
  {
    return rcp_static_cast<TProcedural>(obj->tValue);
  }
  
  // GOM.debug() << "mat..." << std::endl;
  magic_pointer<TAttribMaterial> mat = get_material(p);
  if( !!mat )
  {
    return rcp_static_cast<TProcedural>(mat->tValue);    
  }
  
  // GOM.debug() << "bsdf..." << std::endl;
  magic_pointer<TAttribBsdf> bsdf = get_bsdf(p);
  if( !!bsdf )
  {
    return rcp_static_cast<TProcedural>(bsdf->tValue);    
  }
  
  // GOM.debug() << "pert..." << std::endl;
  magic_pointer<TAttribPerturbation> pert = get_perturbation(p); 
  if( !!pert )
  {
    return rcp_static_cast<TProcedural>(pert->tValue);    
  }
  
  // GOM.debug() << "scene..." << std::endl;
  magic_pointer<TAttribScene> scene = get_scene(p);
  if( !!scene )
  {
    // GOM.error() << "Warning: Ignoring locally defined scene, using global" << std::endl;
    return rcp_static_cast<TProcedural>(TSceneRT::_ptParsedScene);    
  }
  
  // GOM.debug() << "camera..." << std::endl;
  magic_pointer<TAttribCamera> camera = get_camera(p);
  if( !!camera )
  {
    return rcp_static_cast<TProcedural>(camera->tValue);    
  }
  
  // GOM.debug() << "rend..." << std::endl;
  magic_pointer<TAttribRenderer> rend = get_renderer(p);
  if( !!rend )
  {
    return rcp_static_cast<TProcedural>(rend->tValue);    
  }

  // GOM.debug() << "img..." << std::endl;
  magic_pointer<TAttribImageIO> img = get_imageio(p);
  if( !!img )
  {
    return rcp_static_cast<TProcedural>(img->tValue);        
  }
  
  // GOM.debug() << "pat..." << std::endl;
  magic_pointer<TAttribPattern> pat = get_pattern(p); // converts, do last.
  if( !!pat )
  {
    return rcp_static_cast<TProcedural>(pat->tValue);    
  }

  if( active )
  {
    GOM.error() << "Unable to get procedural var" << std::endl;
    exit(1);
  }
  else
  {
    return (magic_pointer<TProcedural>)NULL;
  }
}

magic_pointer<TAttribute> GetParameter (const std::string& rktATTRIB)
{
  magic_pointer<TProcedural> data = get_procedural_var(DATA);

  if( !data )
  {
    rt_error("Cannot extract procedural (to get parameter)");
    exit(1);
  }
  else
  {
    // GOM.debug() << "Data (as procedural) was apparently non-null" << std::endl;
  }
  magic_pointer<TAttribute> tattr;

  if(data->getAttribute(rktATTRIB, tattr) != FX_ATTRIB_OK)
  {
    rt_error("Item has no such attribute");
    exit(1);
  }
  return tattr;
}

void SetParameter (const std::string& rktATTRIB, magic_pointer<TAttribute> attr)
{
  if( !attr )
  {
    rt_error("SetParameter given a NULL attribute");
    return;
  }

  EAttribType eTYPE = attr->eType;
  int   iResult;
  // GOM.debug() << "Attempting to set value " << rktATTRIB << "(" << EAttribType_to_str(eTYPE) << ")" << std::endl;
  
  if( !!DATA )
  {
    // GOM.debug() << "Data is a " << DATA->toString() << std::endl;
  }
  
  magic_pointer<TProcedural> data = get_procedural_var(DATA);

  if( !data )
  {
    rt_error("Cannot extract procedural (to set parameter)");
    exit(1);
  }
  else
  {
    // GOM.debug() << "Data (as procedural) was apparently non-null" << std::endl;
  }

#if !defined(NEW_ATTRIBUTES)
  GOM.error() << "WARNING: old attributes are untested!" << std::endl;
  NAttribute nAttrib;

  switch(eTYPE)
  {
  case FX_INTEGER:
    nAttrib.iValue = get_int(attr)->tValue;
    break;
  case FX_REAL:
    nAttrib.dValue = get_real(attr)->tValue;
    break;
  case FX_BOOL:
    nAttrib.gValue = get_bool(attr)->tValue;
    break;
  case FX_STRING:
    nAttrib.pvValue = (void*)rcp_static_cast<TAttribString>(attr)->tValue.c_str();
    break;
  case FX_COLOR:
    nAttrib.pvValue = (void*)&rcp_static_cast<TAttribColor>(attr)->tValue;
    break;
  case FX_VECTOR:
    nAttrib.pvValue = (void*)&rcp_static_cast<TAttribVector>(attr)->tValue;
    break;
  case FX_VECTOR2:
    nAttrib.pvValue = (void*)&rcp_static_cast<TAttribVector2>(attr)->tValue;
    break;
  case FX_IMAGE:
    nAttrib.pvValue = (void*)rcp_static_cast<TAttribImage>(attr)->tValue.get_pointer();
    break;
  case FX_BSDF:
    nAttrib.pvValue = (void*)rcp_static_cast<TAttribBsdf>(attr)->tValue.get_pointer();
    break;
  case FX_CAMERA:
    nAttrib.pvValue = (void*)rcp_static_cast<TAttribCamera>(attr)->tValue.get_pointer();
    break;
  case FX_PATTERN:
    nAttrib.pvValue = (void*)rcp_static_cast<TAttribPattern>(attr)->tValue.get_pointer();
    break;
  case FX_PERTURBATION:
    nAttrib.pvValue = (void*)rcp_static_cast<TAttribPerturbation>(attr)->tValue.get_pointer();
    break;
  case FX_MATERIAL:
    nAttrib.pvValue = (void*)rcp_static_cast<TAttribMaterial>(attr)->tValue.get_pointer();
    break;
  default:
    rt_error("I can't use old attributes with " + EAttribType_to_str(eTYPE));
    return;
  }
  iResult = data->setAttribute (rktATTRIB, nAttrib, eTYPE);
#else
  // GOM.debug() << "Identifier check:" << std::endl;
  // GOM.debug() << "it is \"" << data->identifier() << "\"" << std::endl;
  // GOM.debug() << "Attempting to call setAttribute" << std::endl;
  iResult = data->setAttribute (rktATTRIB, attr, eTYPE);
  // GOM.debug() << "Called, returned." << std::endl;
#endif

  if ( iResult == FX_ATTRIB_WRONG_PARAM )
  {
    rt_error ("object does not have such attribute");
    exit (1);
  }
  else if ( iResult == FX_ATTRIB_WRONG_TYPE )
  {
    std::string type_given = EAttribType_to_str(eTYPE);
    std::string type_expected;
    TAttributeList tal;

    data->getAttributeList (tal);

    type_expected = EAttribType_to_str (tal[rktATTRIB]);
    
    rt_error (std::string("incorrect type in attribute value: " +
		    type_given + " expected "
		    + type_expected).c_str());
    exit (1);
  }
  else if ( iResult == FX_ATTRIB_WRONG_VALUE )
  {
    rt_error ("value not accepted for this attribute");
    exit (1);
  }
  else if ( iResult == FX_ATTRIB_USER_ERROR )
  {
    rt_error (TProcedural::_tUserErrorMessage.c_str());
    exit (1);
  }
  // GOM.debug() << "Parameter was successfully set" << std::endl;

}  /* SetParameter() */

std::string check_get_string(const magic_pointer<TAttribute> t)
{
  std::string s;
  if( !!t )
  {
    if( t->eType == FX_STRING || t->eType == FX_STRING_LIST )
    {
      magic_pointer<TAttribString> sa = get_string(t);
      if( !!sa )
      {
	s = sa->tValue;
      }
      else
      {
	rt_error("Cannot extract std::string from a real std::string (BUG?!?)");
      }
    }
    else
    {
      GOM.error() << "Warning: usage on line " << TSceneRT::_dwLineNumber
	   << " as a std::string requires conversion" << std::endl;
      magic_pointer<TAttribString> sa = get_string(t);
      if( !!sa )
      {
	s = sa->tValue;
      }
      else
      {
	rt_error("Cannot extract std::string");
      }      
    }
  }
  return s;
}

bool check_get_bool(const magic_pointer<TAttribute> t)
{
  magic_pointer<TAttribBool> b = get_bool(t);
  if( !!b )
  {
    return b->tValue;
  }
  else
  {
    rt_error("cannot extract bool");
    return 0;
  }
}


double check_get_real(const magic_pointer<TAttribute> t)
{
  magic_pointer<TAttribReal> r = get_real(t);
  if( !!r )
  {
    return r->tValue;
  }
  else
  {
    rt_error("cannot extract real");
    return 0;
  }
}

magic_pointer<TObject> check_get_object(const magic_pointer<TAttribute> t)
{
  magic_pointer<TAttribObject> r = get_object(t);
  if( !!r )
  {
    return r->tValue;
  }
  else
  {
    rt_error("cannot extract object");
    return magic_pointer<TObject>();
  }
}

magic_pointer<TScene> check_get_scene(const magic_pointer<TAttribute> t)
{
  magic_pointer<TAttribScene> r = get_scene(t);
  if( !!r )
  {
    return r->tValue;
  }
  else
  {
    rt_error("cannot extract scene");
    return magic_pointer<TScene>();
  }
}

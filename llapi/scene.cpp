/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  Copyright (C) 1999 Jon Frydensbjerg
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
#include "hlapi/aggregate.h"
#include "hlapi/image_manager.h"
#include "llapi/object.h"
#include "llapi/scene.h"
#include "llapi/material.h"
#include "llapi/object_required.h"

TScene::TScene (void) :
  ptWorld (NULL),
  ptCamera (NULL),
  ptRenderer (NULL),
  gParticipatingMedia (false),
  wNeededBuffers (0),
  ptImageIO (NULL) 
{

  ptBackgroundColor = new TPattern (TColor::_black());

}


void TScene::addObject(magic_pointer<TObject> ptOBJECT)
{
  if( !!ptWorld )
  {
    if( ptWorld->classType() == FX_AGGREGATE_CLASS )
    {
      magic_pointer<TAggregate> world = rcp_static_cast<TAggregate>(ptWorld);

      if( !world->containsObject(ptOBJECT) )
      {
	world->add(ptOBJECT);
      }
    }
  }
}

void TScene::addLight(TLight* ptLIGHT)
{
  // It is important to make a note here that the light being added should have
  // a correct matrix, but an incorrect location.  This leads to some
  // weirdness.  Because of that, I am multiplying it's transform matrix by the
  // zero point to find the actual location of the light.
  // __FIXME__ -- Whenever anyone finds out why the light does NOT have a
  // correct location, this should be modified so that a second copy is not
  // required (I hate to change the original). 
  
  static TVector zero(0,0,0);

  const TMatrix& transform = (*ptLIGHT->transformMatrix());
  const TMatrix& inverse = (*ptLIGHT->inverseTransformMatrix());

  // Now that we have the two matricies, it's time to make an instance of the
  // object in question...
  TLight* instance = (TLight*) TClassManager::_newObject
    (ptLIGHT->className(), ptLIGHT);
  if( ! instance )
  {
    string err = "Cannot instantiate pure light " + ptLIGHT->className();
    cerr << err << endl;
    exit(1);
  }
  // Now that we have an object, set it's matricies to those already
  // calculated by the other instance.  .
  TVector location = transform * zero;
  instance->setTransformMatrix(transform);
  instance->setInverseTransformMatrix(inverse);
  instance->setLocation(location);

  cout << "Adding pure light \"" << instance->className()
       << "\" at <" << location.x() << ", " << location.y() << ", " << location.z() << ">" << endl;
  
  // The instance should be ok at this point... 
  tLightList.push_back(instance);
}

void TScene::addAreaLight(TObject* ptALIGHT)
{
  cout << "Adding area light with shape \"" << ptALIGHT->className() << "\"" << endl;	
  tAreaLightList.push_back(ptALIGHT);
}

bool TScene::recursiveLocateLights(TObject* obj, TObjectVector& light_manip_list, bool addlights)
{
  // FIXME!  This does not work correctly.  Pure lights (halo, etc), do not get
  // translated correctly (esp. when in an aggregate).
  if( obj != NULL )
  {
    NAttribute trash;
    
    if( obj->getAttribute("lightonly",trash) == FX_ATTRIB_OK )
    {
#if !defined(NEW_ATTRIBUTES)
      bool val = trash.gValue;
#else
      magic_pointer<TAttribBool> b = get_bool(trash);
      bool val = false;
      if( !!b )
      {
	val = b->tValue;
      }
#endif      
      if( val && addlights )
      {

	TLight* instance = (TLight*)TClassManager::_newObject(obj->className(), obj);

	if( instance )
	{
	  TMatrix manip_matrix, inv_manip_matrix;
	  
	  manip_matrix.setIdentity();

	  // [FIXME!] Matrix generation/inversion.
	  // I am generating the full matrix here, and inverting it below,
	  // because I am not certain yet if all objects are filling out their
	  // inverse matrix.  A lot of time could be saved by using the
	  // inverted matrices to generate location.
	  for(TObjectVector::iterator i = light_manip_list.begin();
	      i != light_manip_list.end();
	      ++i)
	  {
	    manip_matrix = manip_matrix * *((*i)->transformMatrix());
	  }
	  
	  manip_matrix = manip_matrix * *(obj->transformMatrix());
					 
	  inv_manip_matrix = invert(manip_matrix);
	  

	  static TMatrix ones;
	  static const TVector zero(0,0,0);
	  static bool initialized = false;

	  if(!initialized)
	  {
	    initialized = true;
	    ones.setIdentity();
	  }
	  TVector location = manip_matrix * zero;


	  // [FIXME!] What about other factors of the light that may be
	  // affected by the scale, skew, or other nasty matrix artifacts?
	  // Should the matrices be stripped of their translations, since the
	  // location is changing, and then have the remaining matrix reapplied
	  // to the new light?
	  
	  instance->setTransformMatrix(ones);
	  instance->setInverseTransformMatrix(ones);
	  
	  instance->translate(location);
	  
	  addLight (instance);
	}
	else
	{
	  string err = "Cannot instantiate pure light " + obj->className();
	  cerr << err << endl;
	  exit(1);	  
	}
	return true;
      } // if it was a light (lightonly attribute was true)
    } // if it had the lightonly attribute
    
    bool container = false;
    
    if( obj->getAttribute("containsobjects",trash) == FX_ATTRIB_OK )
    {
#if !defined(NEW_ATTRIBUTES)      
      bool val = trash.gValue;
#else
      magic_pointer<TAttribBool> b = get_bool(trash);
      bool val = false;
      if( !!b )
      {
	val = b->tValue;
      }
#endif
      if( val )
      {
	magic_pointer<TMaterial> mat = obj->material ();
	if( !!mat )
	{
	  // If the object has some emission, it's an area light...
	  // In this case, there should be no reason to add sub-objects as
	  // lights, as the entire thing is a light. 
	  if( !!mat->emission () )
	  {
	    addAreaLight (obj);
	    addlights = false;
	  }	  
	}
	  
	
	container = true;
	TAggregate* tag = (TAggregate*)obj;
	TObjectList* tol = tag->objectList ();

	light_manip_list.push_back(obj);

	for( int i = 0; i < int(tol->size()); ++i)
	{
	  if(recursiveLocateLights ((*tol)[i], light_manip_list, addlights) )
	  {
	    cout << "FIXME: erase light from object list (for speed)" << endl;
	    // Note here... If the light is deleted, and it happens to be in an
	    // aggregate which was duplicated some number of times, all of the
	    // duplicate lights will be deleted.  A more intelligent check is
	    // required before deleting any lights. 
	    
	    //	    tol->erase(tol->begin() + i);
	    //	    --i;
	  }
	}

	light_manip_list.erase(light_manip_list.begin() +
			       light_manip_list.size() - 1 );
	// If there is nothing left in the container, remove it.  This is
	// useful for a collection of light sources defined as an aggregate,
	// where after all of the lights have been instantiated, the container
	// is no longer needed.
	if( tol->empty() )
	{
	  return true;
	}
      }
      else
      {
	container = false;
      }
    } /* if obj is a container */

    // If not a container, check its material, add one if needed, and add it as
    // a light source if need be.
    if( !container )
    {
      magic_pointer<TMaterial> mat = obj->material ();
      if( !mat )
      {
	obj->setMaterial(ptDefaultMaterial);
	mat = obj->material ();
	if( !mat )
	{
	  cerr << "Object \"" << obj->className() << "\" has no material, and 'defaultmaterial' is not set in the scene." << endl;
	  exit(1);
	}
      }
      
      if( !!mat )
      {
	// If the object has some emission, it's an area light...
	if( !!mat->emission () )
	{
	  addAreaLight (obj);
	}
      }      
    } /* not a container */
  } /* if( obj != NULL ) */
  return false;
} /* recursiveLocateLights() */

bool TScene::create_buffers(void)
{
  delete sBuffers.ptImage;
  delete sBuffers.ptZBuffer;
  delete sBuffers.ptNBuffer;

  sBuffers.ptZBuffer = NULL;
  sBuffers.ptImage = NULL;
  sBuffers.ptNBuffer = NULL;
  

  sBuffers.ptImage = new TImage (zWidth, zHeight);

  if ( wNeededBuffers & FX_ZBUFFER )
  {
    sBuffers.ptZBuffer = new TZBuffer (zWidth, zHeight);
  }
  if ( wNeededBuffers & FX_NBUFFER )
  {
    sBuffers.ptNBuffer = new TNBuffer (zWidth, zHeight);
  }

  return true;
}

bool TScene::initialize (void)
{
  ptWorld->initialize();

  TObjectVector tol;
  recursiveLocateLights(ptWorld,tol);

  magic_pointer<TAggregate> tag = rcp_static_cast<TAggregate>(ptWorld);
  
  if ( tag->objectList()->empty() )
  {
    cout << "Warning: Scene has no objects" << endl;
  }
  
  ptWorld->setObjectCode (1);
  
  if ( (tLightList.empty()) && (tAreaLightList.empty()) )
  {
    cout << "Warning: Scene has no lights" << endl;
  }
  else
  {
    // Initialize the 'pure' lights
    for (vector<TLight*>::iterator tIter = tLightList.begin();
	 ( tIter != tLightList.end() );
	 tIter++)
    {
      (*tIter)->initialize();
    }
  }
  
  assert ( !!ptRenderer );
  ptRenderer->initialize (*this);

  wNeededBuffers |= ptRenderer->neededBuffers();

  assert ( !!ptCamera );
  ptCamera->setImageResolution (zWidth, zHeight);
  ptCamera->initialize();

  if ( gParticipatingMedia )
  {
    tAtmosphere.initialize (this);
  }

  if ( !!ptImageIO )
  {
    ptImageIO->initialize();
  }
  
  create_buffers();

  return true;

}  /* initialize() */


bool TScene::finalize (void)
{

  delete sBuffers.ptImage;
  delete sBuffers.ptZBuffer;
  delete sBuffers.ptNBuffer;

  ptWorld->finalize();
  
  ptRenderer->finalize();
  
  return true;
  
}  /* finalize() */


bool TScene::render (TUserFunction* pfUSER, void* pvDATA)
{

  if ( !ptWorld )
  {
    return false;
  }

  ptRenderer->setUserFunction (pfUSER, pvDATA);
  ptRenderer->render (sBuffers);

  return true;

}  /* render() */


bool TScene::postprocess (void)
{

  TImageFilter*   ptFilter;

  for (list<TImageFilter*>::iterator tIter = tFilterList.begin(); ( tIter != tFilterList.end() ) ;tIter++)
  {
    ptFilter = *tIter;
    assert ( ptFilter );
    
    ptFilter->setScene (this);

    ptFilter->filter (sBuffers);
  }

  return true;

}  /* postprocess() */


bool TScene::saveImage (void)
{
  int   iResult;
  
  if ( !sBuffers.ptImage )
  {
    cout << "Noting to save" << endl;
    return false;
  }

  if( !!ptImageIO )
  {
    iResult = ptImageIO->save (sBuffers.ptImage);
  }
  else
  {
    cerr << "Warning: ImageIO is NULL. No output will be done." << endl;
    return false;
  }

  return ( iResult == 0 );

}  /* saveImage() */


void TScene::addImageFilter (TImageFilter* ptFILTER)
{

  tFilterList.push_back (ptFILTER);
  wNeededBuffers |= ptFILTER->neededBuffers();

}  /* addImageFilter() */


int TScene::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  cout << "TScene::setAttribute(" << rktNAME << ")" << endl;
  
  if ( rktNAME == "background" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_PATTERN )
    {
      setBackgroundColor ((TPattern*) nVALUE.pvValue);
    }
    else if ( eTYPE == FX_REAL )
    {
      setBackgroundColor (new TPattern (nVALUE.dValue));
    }
    else if ( eTYPE == FX_COLOR )
    {
      setBackgroundColor (new TPattern (*((TColor*) nVALUE.pvValue)));
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      setBackgroundColor (pat->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "camera" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_CAMERA )
    {
      setCamera (((TCamera*) nVALUE.pvValue)->clone_new());
    }
#else
    magic_pointer<TAttribCamera> cam = get_camera(nVALUE);
    if( !!cam )
    {
      setCamera ( cam->tValue );
    }
#endif    
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "renderer" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_RENDERER )
    {
      setRenderer (((TRenderer*) nVALUE.pvValue)->clone_new());
    }
      
#else
    magic_pointer<TAttribRenderer> ren = get_renderer(nVALUE);
    if( !!ren )
    {
      setRenderer ( ren->tValue );
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "width" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_REAL )
    {
      setWidth (size_t (nVALUE.dValue));
    }
    else if( eTYPE == FX_INTEGER )
    {
      setWidth (nVALUE.iValue);
    }
#else
    cout << "Getting int" << endl;
    magic_pointer<TAttribInt> i = get_int(nVALUE);
    if( !!i )
    {
      cout << "Have int (" << i->tValue << ") calling setWidth" << endl;
      setWidth (i->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "height" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_REAL )
    {
      setHeight (size_t (nVALUE.dValue));
    }
    else if( eTYPE == FX_INTEGER )
    {
      setHeight (nVALUE.iValue);
    }
#else
    magic_pointer<TAttribInt> i = get_int(nVALUE);
    if( !!i )
    {
      setHeight (i->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "participating" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_BOOL )
    {
      setParticipatingMedia (nVALUE.gValue);
    }
#else
    magic_pointer<TAttribBool> b = get_bool(nVALUE);
    if( !!b )
    {
      setParticipatingMedia (b->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if (rktNAME == "defaultmaterial" )
  {
#if !defined(NEW_ATTRIBUTES)
    cerr << "ERROR! Materials can only be passed with NEW attributes" << endl;
    return FX_ATTRIB_USER_ERROR;
    
#else
    magic_pointer<TAttribMaterial> m = get_material(nVALUE);
    if( !!m )
    {
      ptDefaultMaterial = m->tValue;
    }
#endif    
  }
  else
  {
    return TProcedural::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */

int TScene::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)  
  if ( rktNAME == "background" )
  {
    rnVALUE.pvValue = ptBackgroundColor.get_pointer();
  }
  else if ( rktNAME == "camera" )
  {
    rnVALUE.pvValue = ptCamera.get_pointer();
  }
  else if ( rktNAME == "renderer" )
  {
    rnVALUE.pvValue = ptRenderer.get_pointer();
  }
  else if ( rktNAME == "width" )
  {
    rnVALUE.dValue = zWidth;
  }
  else if ( rktNAME == "height" )
  {
    rnVALUE.dValue = zHeight;
  }
  else if ( rktNAME == "participating" )
  {
    rnVALUE.gValue = gParticipatingMedia;
  }
#else
  if ( rktNAME == "background" )
  {
    rnVALUE = new TAttribPattern (ptBackgroundColor);
  }
  else if ( rktNAME == "camera" )
  {
    rnVALUE = new TAttribCamera(ptCamera);
  }
  else if ( rktNAME == "renderer" )
  {
    rnVALUE = new TAttribRenderer(ptRenderer);
  }
  else if ( rktNAME == "width" )
  {
    rnVALUE = new TAttribInt (zWidth);
  }
  else if ( rktNAME == "height" )
  {
    rnVALUE = new TAttribInt (zHeight);    
  }
  else if ( rktNAME == "participating" )
  {
    rnVALUE = new TAttribBool (gParticipatingMedia);
  }
  else if (rktNAME == "defaultmaterial" )
  {
    rnVALUE = new TAttribMaterial (ptDefaultMaterial);
  }
#endif
  else
  {
    return TProcedural::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TScene::getAttributeList (TAttributeList& rtLIST) const
{

  TProcedural::getAttributeList (rtLIST);

  rtLIST ["background"]    = FX_PATTERN;
  rtLIST ["camera"]        = FX_CAMERA;
  rtLIST ["renderer"]      = FX_RENDERER;
  rtLIST ["width"]         = FX_REAL;
  rtLIST ["height"]        = FX_REAL;
  rtLIST ["participating"] = FX_BOOL;
  rtLIST ["defaultmaterial"] = FX_MATERIAL;

}  /* getAttributeList() */


void TScene::setOutputFileName (const string& rktNAME)
{

  NAttribute   nAttrib;

  if ( !!ptImageIO )
  {
#if !defined(NEW_ATTRIBUTES)    
    nAttrib.pvValue = (char*) rktNAME.c_str();
#else
    nAttrib = new TAttribString (rktNAME);
#endif
    ptImageIO->setAttribute ("name", nAttrib, FX_STRING);
  }
  
}  /* setOutputFileName() */


void TScene::printDebug (const string& indent) const
{

  cerr << indent << "[_Scene_]" << endl;

  string new_indent = TDebug::Indent(indent);
  
  cerr << new_indent << "Height               : " << zHeight << endl;
  cerr << new_indent << "Width                : " << zWidth << endl;
  cerr << new_indent << "Last background color: "; ptBackgroundColor->lastColor().printDebug(new_indent); cerr << endl;

  ptWorld->printDebug(new_indent);
  cerr << indent << "." << endl;

}  /* printDebug() */


TUserFunctionMap TScene::getUserFunctions()
{
  TUserFunctionMap ufm = TProcedural::getUserFunctions();

  ufm["getCamera"]       = create_user_function(this,&TScene::camera);
  ufm["setCamera"]       = create_user_function(this,&TScene::setCamera);  
  ufm["getWorld"]        = create_user_function(this,&TScene::world);
  ufm["getRenderer"]     = create_user_function(this,&TScene::renderer);
  ufm["setRenderer"]     = create_user_function(this,&TScene::setRenderer);
  ufm["getImageIO"]      = create_user_function(this,&TScene::imageIO);
  ufm["setImageIO"]      = create_user_function(this,&TScene::setImageOutput);
  ufm["addObject"]       = create_user_function(this,&TScene::addObject);
  ufm["setWidth"]        = create_user_function(this,&TScene::setWidth);
  ufm["setHeight"]       = create_user_function(this,&TScene::setHeight);    

  ufm["getClassName"]    = create_user_function(this,&TScene::className);  
  
  return ufm;
}


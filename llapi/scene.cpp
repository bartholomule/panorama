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

bool TScene::recursiveLocateLights(TObject* obj, TObjectList& light_manip_list)
{
  if( obj != NULL )
  {
    NAttribute trash;
    
    if( obj->getAttribute("lightonly",trash) == FX_ATTRIB_OK )
    {
      if( trash.gValue )
      {
	addLight ((TLight*)obj);
	return true;
      } // if it was a light (lightonly attribute was true)
    } // if it had the lightonly attribute
    TMaterial* mat = obj->material ();
    if( mat )
    {
      // If the object has some emission, it's an area light...
      if( mat->emission () )
      {
	addAreaLight (obj);
      }
    }
    if( obj->getAttribute("containsobjects",trash) == FX_ATTRIB_OK )
    {
      if( trash.gValue )
      {
	TAggregate* tag = (TAggregate*)obj;
	TObjectList* tol = tag->objectList ();

	light_manip_list.push_back(obj);

	for( int i = 0; i < int(tol->size()); ++i)
	{
	  if(recursiveLocateLights ((*tol)[i], light_manip_list) )
	  {
	    tol->erase(tol->begin() + i);
	    --i;
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
    } /* if obj is a container */
  } /* if( obj != NULL ) */
  return false;
} /* recursiveLocateLights() */

bool TScene::initialize (void)
{
  ptWorld->initialize();

  TObjectList tol;
  recursiveLocateLights(ptWorld,tol);

  if ( ((TAggregate*) ptWorld)->objectList()->empty() )
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
  
  assert ( ptRenderer );
  ptRenderer->initialize (*this);

  wNeededBuffers |= ptRenderer->neededBuffers();

  assert ( ptCamera );
  ptCamera->setImageResolution (zWidth, zHeight);
  ptCamera->initialize();

  if ( gParticipatingMedia )
  {
    tAtmosphere.initialize (this);
  }

  if ( ptImageIO )
  {
    ptImageIO->initialize();
  }
  
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
    return false;
  }

  iResult = ptImageIO->save (sBuffers.ptImage);

  return ( iResult == 0 );

}  /* saveImage() */


void TScene::addImageFilter (TImageFilter* ptFILTER)
{

  tFilterList.push_back (ptFILTER);
  wNeededBuffers |= ptFILTER->neededBuffers();

}  /* addImageFilter() */


int TScene::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "background" )
  {
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
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "camera" )
  {
    if ( eTYPE == FX_CAMERA )
    {
      setCamera ((TCamera*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "renderer" )
  {
    if ( eTYPE == FX_RENDERER )
    {
      setRenderer ((TRenderer*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "width" )
  {
    if ( eTYPE == FX_REAL )
    {
      setWidth (size_t (nVALUE.dValue));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "height" )
  {
    if ( eTYPE == FX_REAL )
    {
      setHeight (size_t (nVALUE.dValue));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "participating" )
  {
    if ( eTYPE == FX_BOOL )
    {
      setParticipatingMedia (nVALUE.gValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TProcedural::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TScene::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "background" )
  {
    rnVALUE.pvValue = ptBackgroundColor;
  }
  else if ( rktNAME == "camera" )
  {
    rnVALUE.pvValue = ptCamera;
  }
  else if ( rktNAME == "renderer" )
  {
    rnVALUE.pvValue = ptRenderer;
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

}  /* getAttributeList() */


void TScene::setOutputFileName (const string& rktNAME)
{

  NAttribute   nAttrib;

  if ( ptImageIO )
  {
    nAttrib.pvValue = (char*) rktNAME.c_str();
    ptImageIO->setAttribute ("name", nAttrib, FX_STRING);
  }
  
}  /* setOutputFileName() */


void TScene::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_Scene_]" << endl;

  TDebug::_push();
  
  cerr << TDebug::_indent() << "Height               : " << zHeight << endl;
  cerr << TDebug::_indent() << "Width                : " << zWidth << endl;
  cerr << TDebug::_indent() << "Last background color: "; ptBackgroundColor->lastColor().printDebug(); cerr << endl;

  ptWorld->printDebug();

  TDebug::_pop();
  
}  /* printDebug() */




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

#include "hlapi/image_manager.h"
#include "llapi/object.h"
#include "llapi/scene.h"

TScene::TScene (void) :
  ptWorld (NULL),
  ptCamera (NULL),
  ptRenderer (NULL),
  gParticipatingMedia (false),
  wNeededBuffers (0),
  ptImageIO (NULL) {}


bool TScene::initialize (void)
{

  ptWorld->initialize();

  ptWorld->setObjectCode (1);
  
  for (vector<TLight*>::iterator tIter = tLightList.begin(); ( tIter != tLightList.end() ) ;tIter++)
  {
    (*tIter)->initialize();
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
    if ( eTYPE == FX_COLOR )
    {
      setBackgroundColor (*((TColor*) nVALUE.pvValue));
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
    rnVALUE.pvValue = &tBackgroundColor;
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

  rtLIST ["background"]    = FX_COLOR;
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
  
  cerr << TDebug::_indent() << "Height     : " << zHeight << endl;
  cerr << TDebug::_indent() << "Width      : " << zWidth << endl;
  cerr << TDebug::_indent() << "Background : "; tBackgroundColor.printDebug(); cerr << endl;

  ptWorld->printDebug();

  TDebug::_pop();
  
}  /* printDebug() */

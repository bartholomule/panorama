/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#include <iostream>
#include "llapi/file.h"
#include "hlapi/image_manager.h"
#include "hlapi/plugin_manager.h"
#include "plugins/image_io/tga/tga_io.h"
#include "plugins/image_io/jpeg/jpeg_io.h"
#include "plugins/image_io/png/png_io.h"
#include "plugins/image_io/gif/gif_io.h"

extern multimap<string, string>   tConfigData;

TImageManager     tImageManager;
TImageFormatMap   TImageManager::_tImageFormatMap;

TImage* TImageManager::_load (const string& rktNAME, const string& rktFORMAT)
{

  TImage*      ptImage;
  TImageIO*    ptImageIO;
  NAttribute   nAttrib;

  ptImageIO = _getImageIO (rktFORMAT);

  if ( !ptImageIO )
  {
    return 0;
  }

  nAttrib.pvValue = (char*) rktNAME.c_str();
  ptImageIO->setAttribute ("name", nAttrib, FX_STRING);
  
  ptImage = ptImageIO->load();

  delete ptImageIO;
  
  return ptImage;
  
}  /* _load() */


int TImageManager::_save (const string& rktNAME, const string& rktFORMAT, const TImage* ptIMAGE)
{

  int          iResult;
  TImageIO*    ptImageIO;
  NAttribute   nAttrib;

  ptImageIO = _getImageIO (rktFORMAT);

  if ( !ptImageIO )
  {
    return -1;
  }

  nAttrib.pvValue = (char*) rktNAME.c_str();
  ptImageIO->setAttribute ("name", nAttrib, FX_STRING);
  
  iResult = ptImageIO->save (ptIMAGE);

  delete ptImageIO;
  
  return iResult;

}  /* _save() */


bool TImageManager::_knownFormat (const string& rktFORMAT)
{

  return ( _tImageFormatMap.find (rktFORMAT) != _tImageFormatMap.end() );

}  /* _knownFormat() */


void TImageManager::_addFormat (const string& rktFORMAT, TCreateFunction* pfCREATE)
{

  // [_TODO_] Check if this format is already registered.
  _tImageFormatMap [rktFORMAT] = pfCREATE;

}  /* _addFormat() */


TImageIO* TImageManager::_getImageIO (const string& rktFORMAT)
{

  TCreateFunction*   pfCreate;
  
  if ( _knownFormat (rktFORMAT) )
  {
    pfCreate = _tImageFormatMap [rktFORMAT];
    
    return (TImageIO*) (*pfCreate)(NULL);
  }

  return NULL;
  
}  /* _getImageIO() */


void TImageManager::_initialize (void)
{

#if ( STATIC_LINK == 1 )
  _addFormat ("tga", &TImageTga::_create);
//  _addFormat ("jpeg", &TImageJpeg::_create);
//  _addFormat ("png", &TImagePng::_create);
//  _addFormat ("gif", &TImageGif::_create);
#endif
  
}  /* _initialize() */


TImage* TImageManager::loadImage (const string& rktNAME, const string& rktFORMAT)
{

  string        tFileName;
  TImageData*   ptImageData;
  TImage*       ptImage = NULL;

  cout << "Loading image : " << rktNAME << endl;

  bool   gAbsolutePath = ( rktNAME[0] == '/' );

  if ( gAbsolutePath )
  {
    ptImage = TImageManager::_load (rktNAME, rktFORMAT);
  }
  else
  {
    multimap<string, string>::const_iterator   iter;

    iter = tConfigData.find ("TexturePath");
    while ( ( iter != tConfigData.end() ) && ( (*iter).first == "TexturePath" ) )
    {
      if ( FileExists ((*iter).second + "/" + rktNAME) )
      {
        ptImage = TImageManager::_load ((*iter).second + "/" + rktNAME, rktFORMAT);
        break;
      }
      iter++;
    }
  }

  if ( ptImage )
  {
    ptImageData = new TImageData();

    ptImageData->ptImage    = ptImage;
    ptImageData->gLoaded    = true;
    tImageDataMap [rktNAME] = ptImageData;
  }

  return ptImage;

}  /* loadImage() */


TImageManager::~TImageManager (void)
{

  TImageData*   ptImageData;

  for (TImageDataMap::iterator tIter = tImageDataMap.begin(); ( tIter != tImageDataMap.end() ) ;tIter++)
  {
    ptImageData = (*tIter).second;

    delete ptImageData->ptImage;
    delete ptImageData;
  }

  tImageDataMap.clear();
  
}  /* ~TImageManager() */


TImage* TImageManager::newImage (const string& rktNAME, const string& rktFORMAT)
{

  TImageData*               ptImageData;
  TImageDataMap::iterator   tIter = tImageDataMap.find (rktNAME);
  
  if ( tIter == tImageDataMap.end() )
  {
    return loadImage (rktNAME, rktFORMAT);
  }

  ptImageData = (*tIter).second;
  
  return ptImageData->ptImage;

}  /* newImage() */

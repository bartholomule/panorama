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

#ifndef _IMAGE_MANAGER__
#define _IMAGE_MANAGER__

#include "llapi/warning_eliminator.h"
#include <map>
#include "llapi/image.h"
#include "llapi/image_io.h"
#include "hlapi/plugin_manager.h"

typedef map<string, TCreateFunction*, less<string> > TImageFormatMap;

struct TImageData
{

  TImage*   ptImage;
  bool      gLoaded;

};  /* struct TImageData */

typedef map<string, TImageData*, less <string> > TImageDataMap;

class TImageManager
{

  protected:

    TImageDataMap   tImageDataMap;

    static TImageFormatMap   _tImageFormatMap;

    TImage* loadImage (const string& rktNAME, const string& rktFORMAT);

  public:

    static TImage* _load (const string& rktNAME, const string& rktFORMAT);
    static int _save (const string& rktNAME, const string& rktFORMAT, const TImage* pktIMAGE);
    static bool _knownFormat (const string& rktFORMAT);
    static void _addFormat (const string& rktFORMAT, TCreateFunction* pfCREATE);
    static void _addFormat (const string& rktFORMAT, TCreateFunction* pfCREATE, const string& rktALIAS);
    static TImageIO* _getImageIO (const string& rktFORMAT);
    static void _initialize (void);
      
    ~TImageManager (void);
    
    bool initialize (void) { return true; }

    TImage* newImage (const string& rktNAME, const string& rktFORMAT);

};  /* class TImageManager */

extern TImageManager   tImageManager;

#endif  /* _IMAGE_MANAGER__ */

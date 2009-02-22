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

typedef std::map<std::string, TCreateFunction*, std::less<std::string> > TImageFormatMap;

struct TImageData
{

  TImage*   ptImage;
  bool      gLoaded;

};  /* struct TImageData */

typedef std::map<std::string, TImageData*, std::less<std::string> > TImageDataMap;

class TImageManager
{

  protected:

    TImageDataMap   tImageDataMap;

    static TImageFormatMap   _tImageFormatMap;

    TImage* loadImage (const std::string& rktNAME, const std::string& rktFORMAT);

  public:

    static TImage* _load (const std::string& rktNAME, const std::string& rktFORMAT);
    static int _save (const std::string& rktNAME, const std::string& rktFORMAT, const TImage* pktIMAGE);
    static bool _knownFormat (const std::string& rktFORMAT);
    static void _addFormat (const std::string& rktFORMAT, TCreateFunction* pfCREATE);
    static void _addFormat (const std::string& rktFORMAT, TCreateFunction* pfCREATE, const std::string& rktALIAS);
    static TImageIO* _getImageIO (const std::string& rktFORMAT);
    static void _initialize (void);
      
    ~TImageManager (void);
    
    bool initialize (void) { return true; }

    TImage* newImage (const std::string& rktNAME, const std::string& rktFORMAT);

};  /* class TImageManager */

extern TImageManager   tImageManager;

#endif  /* _IMAGE_MANAGER__ */

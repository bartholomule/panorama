/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  Copyright (C) 1999 Jose Antonio Robles Ordoñez  
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

#ifndef _JPEG_IO__
#define _JPEG_IO__

#include <string>
#include "llapi/image_io.h"
#include "hlapi/plugin_manager.h"

class TImageJpeg : public TImageIO
{

  protected:

    float fQuality;
    float fSmoothing;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TImageJpeg(void) :
      fQuality(75.0), // Default values
      fSmoothing(0.0){};

    int save (const TImage* pktIMAGE);
    TImage* load (void);

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;      

    string className (void) const { return "ImageJpeg"; }
    
};  /* class TImageJpeg */

#endif  /* _JPEG_IO__ */

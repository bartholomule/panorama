/*
 *  Copyright (C) 1999 Ken Geis
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

#ifndef _RT_PNG_IO__
#define _RT_PNG_IO__

#include <string>

#include "llapi/image.h"
#include "hlapi/plugin_manager.h"

class TImagePng : public TImageIO
{

  public:

    TImagePng (void) :
      iCompression (-1) {}

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    int save (const TImage* pktIMAGE);
    TImage* load (void);

    string className (void) const { return "ImagePng"; }
    
    int setAttribute (const string& rktNAME, NAttribute nVALUE,
		      EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setCompression (int iComp) { iCompression = iComp; }

  protected:

    int iCompression;

};  /* class TImagePng */

#endif  /* _RT_PNG_IO__ */

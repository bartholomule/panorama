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

#ifndef _IMAGE_IO__
#define _IMAGE_IO__

#include <string>
#include "llapi/image.h"
#include "llapi/procedural.h"

class TImageIO : public TProcedural
{

  protected:

    string   tFileName;
    
  public:

    virtual void initialize (void) {}
    
    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    virtual int save (const TImage* pktIMAGE) = 0;
    virtual TImage* load (void) = 0;

    EClass classType (void) const { return FX_IMAGE_IO_CLASS; }
    
};  /* class TImageIO */

#endif  /* _IMAGE_IO__ */

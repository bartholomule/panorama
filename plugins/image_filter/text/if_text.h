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

#ifndef _IF_TEXT__
#define _IF_TEXT__

#include "llapi/image_filter.h"
#include "hlapi/plugin_manager.h"

class TIF_Text : public TImageFilter
{

  protected:

    std::string   tFontFile;
    std::string   tText;
    Word     wSize;
    Word     wFaceNumber;
    TColor   tColor;
    TVector2 tTranslate;
    
  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TIF_Text (void);

    void filter (SBuffers& rsBUFFERS);

    int setAttribute (const std::string& rktNAME, NAttribute nVALUE,
                      EAttribType eTYPE);
    int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    std::string className (void) const { return "IF_Text"; }

    virtual TIF_Text* clone_new() const { return new TIF_Text(*this); }
  
};  /* class TIF_Text */

#endif  /* _IF_TEXT__ */

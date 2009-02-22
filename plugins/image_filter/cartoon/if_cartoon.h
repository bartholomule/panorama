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

#ifndef _IF_CARTOON__
#define _IF_CARTOON__

#include "llapi/image_filter.h"
#include "hlapi/plugin_manager.h"

class TIF_Cartoon : public TImageFilter
{

  protected:

    Byte     bColorLevels;
    float    fNThreshold;
    float    fZThreshold;
    TColor   tOutlineColor;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TIF_Cartoon (void);

    void filter (SBuffers& rsBUFFERS);

    int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    std::string className (void) const { return "IF_Cartoon"; }

    virtual TIF_Cartoon* clone_new() const { return new TIF_Cartoon(*this); }

};  /* class TIF_Cartoon */

#endif  /* _IF_CARTOON__ */

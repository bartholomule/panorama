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

#ifndef _OF_CARTOON__
#define _OF_CARTOON__

#include "llapi/object_filter.h"
#include "hlapi/plugin_manager.h"

class TOF_Cartoon : public TObjectFilter
{

  protected:

    Byte     bColorLevels;
    TColor   tOutlineColor;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TOF_Cartoon (void) :
      TObjectFilter(),
      bColorLevels (2),
      tOutlineColor (TColor::_black()) {}

    TColor filterRadiance (TSurfaceData& rtDATA, const TColor& rktRAD) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    string className (void) const { return "OF_Cartoon"; }

    virtual TOF_Cartoon* clone_new() const { return new TOF_Cartoon(*this); }
  
};  /* class TOF_Cartoon */

#endif  /* _OF_CARTOON__ */

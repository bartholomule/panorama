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

#ifndef _MATERIAL_CHECKER__
#define _MATERIAL_CHECKER__

#include "llapi/checkerboard.h"
#include "llapi/material.h"
#include "hlapi/plugin_manager.h"

class TMaterialChecker : public TMaterial
{

  protected:

    TColor          tBaseColor;
    TCheckerBoard   tCheckerBoard;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TColor color (const TSurfaceData& rktDATA) const
    {
      return ( tCheckerBoard.evaluate (rktDATA.localPoint()) == 1 ) ? tColor : tBaseColor;
    }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    virtual void setBaseColor (const TColor& rktCOLOR)
    {
      tBaseColor = rktCOLOR;
    }
    virtual void setSize (TScalar tSIZE)
    {
      tCheckerBoard.setSize (tSIZE);
    }
    virtual void setBorder (TScalar tSIZE)
    {
      tCheckerBoard.setBorder (tSIZE);
    }

    string className (void) const { return "MaterialChecker"; }

};  /* class TMaterialChecker */

#endif  /* _MATERIAL_CHECKER__ */

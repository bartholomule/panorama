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

#ifndef _HEIGHT_FIELD__
#define _HEIGHT_FIELD__

#include "llapi/image.h"
#include "llapi/object.h"
#include "hlapi/plugin_manager.h"

class THeightField : public TObject
{

  protected:

    TImage*   ptImage;
    TScalar   tHalfWidth, tHalfHeight;
    TScalar   tMinY, tMaxY;

    TScalar getHeight (size_t I, size_t J) const;
    bool checkIntersection (int iCELLX, int iCELLZ, const TRay& rktRAY, const TInterval& rktINTY, TSurfaceData& rtDATA) const;
    bool traverseGrid (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    
  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    THeightField (void) :
      TObject()
    {
      sCapabilities.gInfinite = false;
    }
      
    ~THeightField (void)
    {
      delete ptImage;
    }
    
    bool initialize (void);
    
    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;
    
    bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    TVector normal (const TSurfaceData& rktDATA) const { return rktDATA.normal(); }

    string className (void) const { return "HeightField"; }

};  /* class THeightField */

#endif  /* _HEIGHT_FIELD__ */

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

#ifndef _BOX__
#define _BOX__

#include "llapi/object.h"

class TBox : public TObject
{

  protected:

    TVector localNormal (const TVector& rktPOINT) const;

  public:

    TBox (void) :
      TObject()
    {
      sCapabilities.gInfinite = false;
    }
      
    void initialize (void);
    
    bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    void getMesh (list<TMesh*>& rtMESH_LIST) const;
    
    string className (void) const { return "Box"; }

};  /* class TBox */

#endif  /* _BOX__ */

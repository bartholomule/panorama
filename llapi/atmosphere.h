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

#ifndef _ATMOSPHERE__
#define _ATMOSPHERE__

#include <vector>
#include "llapi/bounding_box.h"
#include "llapi/atmospheric_object.h"

class TScene;

class TAtmosphere
{

  protected:

    TScene*                       ptScene;
    vector<TAtmosphericObject*>   tAtmObjectList;
    
  public:

    TColor filterRadiance (const TSurfaceData& rktDATA, const TColor& rktRAD) const;
    TScalar transparency (const TVector& rktPOINT1, const TVector& rktPOINT2) const;

    void addObject (TAtmosphericObject* ptATM_OBJ)
    {
      tAtmObjectList.push_back (ptATM_OBJ);
    }

    bool initialize (TScene* ptSCENE);
    
};  /* class TAtmosphere */

#endif  /* _ATMOSPHERE__ */

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

#include "llapi/atmosphere.h"

namespace panorama
{

  TColor TAtmosphere::filterRadiance (const TSurfaceData& rktDATA, const TColor& rktRAD) const
  {

    TColor   tRadiance = rktRAD;

    //
    // [_ERROR_] This code is not finished. It will only work if the objects do not intersect,
    // and the objects are accesed in back to front order.
    //
    for (std::vector<rc_pointer<TAtmosphericObject> >::const_iterator tIter = tAtmObjectList.begin(); ( tIter != tAtmObjectList.end() ) ;tIter++)
    {
      tRadiance = (*tIter)->filterRadiance (rktDATA, tRadiance);
    }

    return tRadiance;

  }  /* filterRadiance() */


  TScalar TAtmosphere::transparency (const TPoint& rktPOINT1, const TPoint& rktPOINT2) const
  {

    TScalar   tTransparency = 1;

    for (std::vector<rc_pointer<TAtmosphericObject> >::const_iterator tIter = tAtmObjectList.begin(); ( tIter != tAtmObjectList.end() ) ;tIter++)
    {
      tTransparency *= (*tIter)->transparency (rktPOINT1, rktPOINT2);
    }

    return tTransparency;

  }  /* transparency() */

}

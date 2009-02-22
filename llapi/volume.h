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

#ifndef PANORAMA_VOLUME_H_INCLUDED
#define PANORAMA_VOLUME_H_INCLUDED

#include "llapi/ray.h"
#include "llapi/entity.h"

namespace panorama
{
  class TVolume : public TEntity
  {

  public:

    virtual bool intersects (const TRay& rktRAY) const = 0;

    virtual void scale (const TVector& rktSCALING_XYZ, const TVector& rktPOINT) {}

  };  /* class TVolume */

} // end namespace panorama

#endif  /* PANORAMA_VOLUME_H_INCLUDED */

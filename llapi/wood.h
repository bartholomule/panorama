/*
*  Copyright (C) 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _WOOD__
#define _WOOD__

#include "llapi/llapi_defs.h"
#include "llapi/perlin_noise.h"

class TWood
{

  protected:

    TPerlinNoise tNoise;
    

  public:

    
    TScalar wood (const TScalar ktX,
                  const TScalar ktY,
                  const TScalar ktZ,
                  const TScalar ktRINGSCALE,
                  const TScalar ktGRAINFACTOR) const;
    
};  /* class TWood */

#endif  /* _WOOD__ */

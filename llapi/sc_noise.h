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

#ifndef _SC_NOISE__
#define _SC_NOISE__


#include "llapi/llapi_defs.h"
#include "llapi/mat_utils.h"
#include "llapi/catrom2.h"


#define TABSIZE   256
#define TABMASK   (TABSIZE - 1)
#define NIMPULSES 3


class TScNoise
{

  protected:

    TCatRom2        tCatRom2;
    
    mutable TScalar atImpulseTab[TABSIZE * 4];

    int   perm  (int ix) const;
    int   index (int ix, int iy, int iz) const;
    
  public:

    TScNoise (void);  
    
    TScalar noise (const TVector& rktPOINT) const;
};  /* class TScNoise */

#endif  /* _SC_NOISE__ */

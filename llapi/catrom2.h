/*
*  Copyright (C) 1999 Peter Barnett
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

#ifndef _CATROM2__
#define _CATROM2__

#include "llapi/llapi_defs.h"
#include "llapi/mat_utils.h"

#define SAMPRATE 100
#define NENTRIES (4 * SAMPRATE + 1)


class TCatRom2
{

  protected:
    
    mutable TScalar atTable [NENTRIES];

        
  public:

    TCatRom2 (void);
    TScalar filter (const TScalar tValue) const; 
    
};  /* class TCatRom2 */

#endif  /* _CATROM2__ */

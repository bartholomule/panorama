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

#ifndef _ENTITY__
#define _ENTITY__

#include "llapi/llapi_defs.h"
#include "llapi/base_class.h"

class TEntity : public TBaseClass
{

  protected:

    TVector   tLocation;

    virtual void update (void) {};

  public:

    virtual void translate (const TVector& rktNEW_POS)
    {
      tLocation = rktNEW_POS;
      update();
    }
    virtual void rotate (const TVector& rktAXISPOINT1, const TVector& rktAXISPOINT2, TScalar tANGLE) {}
    virtual void rotate (const TVector& rktANGLESXYZ) {}

    TVector location (void) const { return tLocation; }

};  /* class TEntity */

#endif  /* _ENTITY__ */

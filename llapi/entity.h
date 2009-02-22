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

#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "llapi/llapi_defs.h"
#include "llapi/procedural.h"

namespace panorama
{

  class TEntity : public TProcedural
  {
  private:
    // This is private, because I (KH) want to phase it out.  location() should
    // always be called to retrieve the location.
    TVector tLocation;

  protected:
    virtual void update (void) {};

  public:

    virtual void translate (const TVector& rktNEW_POS);

    virtual void rotate (const TVector& rktAXISPOINT1, const TVector& rktAXISPOINT2, TScalar tANGLE);
    virtual void rotate (const TVector& rktANGLESXYZ);

    virtual void rotate (const TQuaternion& rktQUAT);

    virtual TVector location (void) const { return tLocation; }

    virtual void setLocation (const TVector& rktLOCATION)
    {
      tLocation = rktLOCATION; update();
    }

    virtual TUserFunctionMap getUserFunctions();

  };  /* class TEntity */
} // end namespace panorama

#endif  /* ENTITY_H_INCLUDED */

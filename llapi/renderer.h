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

#ifndef _RENDERER__
#define _RENDERER__

#include "llapi/frame.h"
#include "llapi/surface_data.h"
#include "llapi/light.h"
#include "llapi/procedural.h"

typedef void (TUserFunction) (size_t, void*);

struct SBuffers;
class TScene;

class TRenderer : public TProcedural
{

  protected:

    TUserFunction*   pfUserFunction;
    void*            pvUserData;
    
  public:

    virtual void initialize (TScene& rtSCENE) {}
    virtual void finalize (void) {}
    virtual void render (SBuffers& rsBUFFERS) = 0;

    void setUserFunction (TUserFunction* pfUSER, void* pvDATA)
    {
      pfUserFunction = pfUSER;
      pvUserData     = pvDATA;
    }

    virtual TColor mediaRadiance (const TSurfaceData& rktDATA, const TColor& rktRAD) const = 0;
    virtual TColor directLight (const TSurfaceData& rktDATA) const = 0;
    virtual TColor directLight (const TSurfaceData& rktDATA, const TLight* pktLIGHT) const = 0;
    virtual TColor ambientLight (const TSurfaceData& rktDATA, Word wDEPTH) const = 0;
    virtual TColor specularReflectedLight (const TSurfaceData& rktDATA, Word wDEPTH, size_t* pzOBJ_CODE) const = 0;
    virtual TColor specularTransmittedLight (const TSurfaceData& rktDATA, Word wDEPTH, size_t* pzOBJ_CODE) const = 0;

    virtual Word neededBuffers (void) const { return 0; }

    EClass classType (void) const { return FX_RENDERER_CLASS; }
    
};  /* class TRenderer */

#endif  /* _RENDERER__ */

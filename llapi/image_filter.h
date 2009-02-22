/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  Copyright (C) 1999 Jon Frydensbjerg
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

#ifndef PANORAMA_IMAGE_FILTER_H_INCLUDED
#define PANORAMA_IMAGE_FILTER_H_INCLUDED

#include "llapi/procedural.h"
#include "llapi/llapi_defs.h"

namespace panorama
{

  struct SBuffers;

  class TScene;

  typedef bool (TUserUpdateFunction) (double, void*);

  class TImageFilter : public TProcedural
  {

  protected:

    Word wNeededBuffers;
    TScene* ptScene;
    TUserUpdateFunction* pfUserUpdate;
    void* pvUserData;

  public:

    TImageFilter (void) :
      wNeededBuffers (0),
      ptScene(NULL),
      pfUserUpdate(NULL),
      pvUserData(NULL)
    {
    }

    virtual void filter (SBuffers& rsBUFFERS) = 0;

    Word neededBuffers (void) { return wNeededBuffers; }

    void setUserFunction (TUserUpdateFunction* pfUSER, void* pvDATA)
    {
      pfUserUpdate = pfUSER;
      pvUserData   = pvDATA;
    }

    void setScene (TScene* ptSCENE)
    {
      ptScene = ptSCENE;
    }

    EClass classType (void) const { return FX_IMAGE_FILTER_CLASS; }

    virtual TImageFilter* clone_new() const = 0;

  };  /* class TImageFilter */

} // end namespace panorama

#endif  /* PANORAMA_IMAGE_FILTER_H_INCLUDED */





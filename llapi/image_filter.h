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

#ifndef _IMAGE_FILTER__
#define _IMAGE_FILTER__

#include "llapi/base_class.h"
#include "llapi/llapi_defs.h"

struct SBuffers;

class TImageFilter : public TBaseClass
{

  protected:

    Word   wNeededBuffers;

  public:

    TImageFilter (void) :
      wNeededBuffers (0) {}
      
    virtual void filter (SBuffers& rsBUFFERS) = 0;

    Word neededBuffers (void) { return wNeededBuffers; }

    EClass classType (void) const { return FX_IMAGE_FILTER_CLASS; }
    
};  /* class TImageFilter */

#endif  /* _IMAGE_FILTER__ */

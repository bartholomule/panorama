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

#ifndef _IF_CONVERT_TO_GREY__
#define _IF_CONVERT_TO_GREY__

#include "llapi/image_filter.h"
#include "hlapi/plugin_manager.h"

class TIF_ConvertToGrey : public TImageFilter
{

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TIF_ConvertToGrey (void) :
      TImageFilter() {}

    void filter (SBuffers& rsBUFFERS);

    string className (void) const { return "IF_ConvertToGrey"; }

};  /* class TIF_ConvertToGrey */

#endif  /* _IF_CONVERT_TO_GREY__ */

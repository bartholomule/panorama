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

#ifndef _OF_CONVERT_TO_GREY__
#define _OF_CONVERT_TO_GREY__

#include "llapi/object_filter.h"
#include "hlapi/plugin_manager.h"

class TOF_ConvertToGrey : public TObjectFilter
{

  protected:

    Byte     bColorLevels;
    TColor   tOutlineColor;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TColor filterRadiance (TSurfaceData& rtDATA, const TColor& rktRAD) const
    {
      return rktRAD.convertToGrey();
    }

    string className (void) const { return "OF_ConvertToGrey"; }

};  /* class TOF_ConvertToGrey */

#endif  /* _OF_CONVERT_TO_GREY__ */

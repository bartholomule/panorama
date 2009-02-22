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

#ifndef PANORAMA_CLASS_MANAGER_H_INCLUDED
#define PANORAMA_CLASS_MANAGER_H_INCLUDED

#include <string>
#include "llapi/base_class.h"

namespace panorama
{

  class TClassManager
  {

  public:

    static TBaseClass* _newObject (const std::string& rktCLASS, const TBaseClass* pktPARENT);

  };  /* class TClassManager */
}

#endif  /* PANORAMA_CLASS_MANAGER_H_INCLUDED */

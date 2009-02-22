/*
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

#ifndef _RT_GIF_IO__
#define _RT_GIF_IO__

#include <string>

#include "llapi/image.h"
#include "hlapi/plugin_manager.h"

class TImageGif : public TImageIO
{

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    int save (const TImage* pktIMAGE);
    TImage* load (void);

    std::string className (void) const { return "ImageGif"; }
  
};  /* class TImageGif */

#endif  /* _RT_GIF_IO__ */

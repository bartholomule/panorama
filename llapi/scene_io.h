/*
*  Copyright (C) 2002 Kevin Harris
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

#ifndef _SCENE_IO__
#define _SCENE_IO__

#include <string>
#include "llapi/scene.h"
#include "llapi/procedural.h"
#include "generic/magic_pointer.h"

class TSceneIO : public TProcedural
{

  public:

    virtual bool initialize (void) { return TProcedural::initialize(); }
    
    virtual int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    virtual int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
    virtual void getAttributeList (TAttributeList& rtLIST) const;

    virtual int save (const std::string& rktNAME, const TScene* pktSCENE) = 0;
    virtual magic_pointer<TScene> load (const std::string& rktNAME) = 0;
    virtual TSceneIO* clone_new() const = 0;

    EClass classType (void) const { return FX_SCENE_IO_CLASS; }
    
};  /* class TSceneIO */

#endif  /* _SCENE_IO__ */

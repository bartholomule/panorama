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

#if       !defined(ATTRIB_TWEAK_H)
#define            ATTRIB_TWEAK_H

#include "llapi/object_required.h"
#include "llapi/user_functions.h"

magic_pointer<TProcedural> get_procedural_var(magic_pointer<TAttribute> p,
					      bool active = true);
void SetParameter (const std::string& rktATTRIB, magic_pointer<TAttribute> attr);
magic_pointer<TAttribute> GetParameter (const std::string& rktATTRIB);

bool    check_get_bool(const magic_pointer<TAttribute> t);
std::string check_get_string(const magic_pointer<TAttribute> t);
double  check_get_real(const magic_pointer<TAttribute> t);
magic_pointer<TObject>   check_get_object(const magic_pointer<TAttribute> t);
magic_pointer<TScene>    check_get_scene(const magic_pointer<TAttribute> t); 


#endif /* !defined(ATTRIB_TWEAK_H) */

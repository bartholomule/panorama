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

#if       !defined(ATTRIBUTE_MATH_H)
#define            ATTRIBUTE_MATH_H

/*
  This file contains helper functions for the parser to do math on attributes.
  They are useful anywhere that unknown types must be manipulated by use of
  addition, subtraction, multiplication, or division. 
 */

#include "generic/magic_pointer.h"
#include "llapi/object_required.h"

magic_pointer<TAttribute> add(const magic_pointer<TAttribute> a1,
			      const magic_pointer<TAttribute> a2);

magic_pointer<TAttribute> sub(const magic_pointer<TAttribute> a1,
			      const magic_pointer<TAttribute> a2);

magic_pointer<TAttribute> mul(const magic_pointer<TAttribute> a1,
			      const magic_pointer<TAttribute> a2);

magic_pointer<TAttribute> div(const magic_pointer<TAttribute> a1,
			      const magic_pointer<TAttribute> a2);


#endif /* !defined(ATTRIBUTE_MATH_H) */

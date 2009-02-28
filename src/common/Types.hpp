/*
 * $Id: Types.hpp,v 1.1.2.2 2009/02/28 22:16:36 kpharris Exp $
 *
 * Part of GNU Panorama -- A framework for graphics production.
 * Copyright (C) 2009 Kevin Harris
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#if       !defined(PANORAMA_TYPES_HPP)
#define            PANORAMA_TYPES_HPP

/*
 * @author Kevin Harris
 */

#include "panorama/common/GenericCoord2.hpp"
#include "panorama/common/GenericCoord3.hpp"

namespace panorama
{
	typedef double NumberType;
	typedef GenericCoord2<NumberType> Coord2;
	typedef GenericCoord3<NumberType> Coord3;
}

#endif /* !defined(PANORAMA_TYPES_HPP) */

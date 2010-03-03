/*
 * $Id: Types.hpp,v 1.1.2.5 2010/03/03 18:07:21 kpharris Exp $
 *
 * Part of GNU Panorama -- A framework for graphics production.
 * Copyright (C) 2010 Kevin Harris
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
#include "panorama/common/GenericVector2.hpp"
#include "panorama/common/GenericVector3.hpp"
#include "panorama/common/GenericPoint2.hpp"
#include "panorama/common/GenericPoint3.hpp"
#include "panorama/common/GenericONB.hpp"

namespace panorama
{
	typedef double NumberType;
	typedef GenericCoord2<NumberType> Coord2;
	typedef GenericCoord3<NumberType> Coord3;
	typedef GenericVector2<NumberType> Vector2;
	typedef GenericVector3<NumberType> Vector3;
	typedef GenericPoint2<NumberType> Point2;
	typedef GenericPoint3<NumberType> Point3;
	typedef GenericONB<NumberType> ONB;
}

#endif /* !defined(PANORAMA_TYPES_HPP) */

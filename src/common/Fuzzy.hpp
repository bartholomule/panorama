/*
 * $Id: Fuzzy.hpp,v 1.1.2.1 2011/11/06 03:34:56 kpharris Exp $
 *
 * Part of GNU Panorama
 * Copyright (C) 2011 Kevin Harris
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

#if       !defined(PANORAMA_FUZZY_HPP)
#define            PANORAMA_FUZZY_HPP

#include <limits>

namespace panorama
{
	const int FUZZ_FACTOR = 4;

	template <typename T>
	inline T fuzzy(const T& t)
	{
		if( std::numeric_limits<T>::is_exact )
		{
			return t;
		}
		return t + (FUZZ_FACTOR * std::numeric_limits<T>::epsilon() );
	}

	template <typename T>
	inline bool fuzzyLess(const T& t1, const T& t2)
	{
		return t1 < fuzzy(t2);
	}

	template <typename T>
	inline bool fuzzyGreater(const T& t1, const T& t2)
	{
		return fuzzy(t1) > t2;
	}

	template <typename T>
	inline bool fuzzyEquals(const T& t1, const T& t2)
	{
		if( std::numeric_limits<T>::is_exact )
		{
			return t1 == t2;
		}
		return (fuzzy(t1) >= t2) && (fuzzy(t2 >= t1));
	}
}

#endif /* !defined(PANORAMA_FUZZY_HPP) */

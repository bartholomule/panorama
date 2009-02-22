/*
 * $Id: template_math.hpp,v 1.1.2.1 2009/02/22 10:22:10 kpharris Exp $
 *
 * Part of GNU Panorama
 * Copyright (C) 2008 Kevin Harris
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

#if       !defined(PANORAMA__TEMPLATE_MATH_HPP)
#define            PANORAMA__TEMPLATE_MATH_HPP

namespace panorama
{
  template <typename T>
  T tfabs(const T& t)
  {
    if( t < 0 )
    {
      return -t;
    }
    return t;
  }
} // namespace panorama

#endif /* !defined(PANORAMA__TEMPLATE_MATH_HPP) */

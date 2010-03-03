/*
 * $Id: GenericONB.hpp,v 1.1.2.1 2010/03/03 18:07:21 kpharris Exp $
 *
 * Part of GNU Panorama
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

#if    !defined(PANORAMA__GENERIC_ONB_HPP)
#define         PANORAMA__GENERIC_ONB_HPP

/*
  GenericONB.hpp -- A class to represent an ortho-normal basis.

  An ortho-normal basis is a set of 3 mutually perpendicular (ortho) vectors
  which are all unit-length (normal).  As such, it can be used for simple
  transformations on vectors, points, and coordinates involving only a single
  rotation.
*/

/*
  Revision History:
  18May2001 Created this file.  Wrote constructors, accessors, and functions to
  convert to/from the ONB.
  18Sep2003 Set a namespace, renamed the file (hpp instead of h), added another
  constructor, changed the internal types to be GenericVector3 instead of
  GenericCoord3.
  ...
  02Mar2010 Converted for use in panorama.  Added string dumping functions.
*/

/**
 * @author Kevin Harris
 */


#include <cmath>
#include <algorithm>
#include "panorama/common/StringDumpable.hpp"
#include "panorama/common/GenericVector3.hpp"

namespace panorama
{
	template <class T>
	class GenericONB
	{
	public:
		// This tag allows use in the StringDumpable.hpp toString functions
		// without requiring the overridden virtual functions.
		typedef bool CanBeStringDumpedTag;

		GenericONB():
			m_u(1,0,0),
			m_v(0,1,0),
			m_w(0,0,1)
		{
		}

		// An ONB where only the direction of w matters...
		GenericONB(const GenericVector3<T>& a):
			m_w(unit(a))
		{
			v = perp_vector(w);
			u = crossprod(v,w);
		}

		// An ONB where the direction of u,v, and w matter...
		// a and b define a plane, where a is in the direction of w, b is in the
		// direction of v, and u is the normal to this plane.
		GenericONB(const GenericVector3<T>& a, const GenericVector3<T>& b):
			m_v(unit(b)),
			m_w(unit(a))
		{
			u = crossprod(v,w);
		}

		// An ONB where the direction of u,v, and w are fully specified.
		GenericONB(const GenericVector3<T>& a, const GenericVector3<T>& b, const GenericVector3<T>& c):
			m_u(unit(a)),
			m_v(unit(b)),
			m_w(unit(c))
		{
		}

		GenericONB(const GenericONB<T>& o): m_u(o.m_u), m_v(o.m_v), m_w(o.m_w)
		{
		}

		GenericONB<T>& operator=(const GenericONB<T>& o)
		{
			if( &o != this )
			{
				m_u = o.u;
				m_v = o.v;
				m_w = o.w;
			}
			return(*this);
		}

		// Take an external coord, and convert to one for this ONB
		GenericCoord3<T> into_onb(const GenericCoord3<T>& c) const
		{
			GenericVector3<T> cv(c);
			return GenericCoord3<T>(dotprod(cv,m_u),dotprod(cv,m_v),dotprod(cv,m_w));
		}

		// Take an external point, and convert to one for this ONB
		GenericPoint3<T> into_onb(const GenericPoint3<T>& c) const
		{
			GenericVector3<T> cv(c.x(), c.y(), c.z());
			return GenericPoint3<T>(dotprod(cv,m_u),dotprod(cv,m_v),dotprod(cv,m_w));
		}

		// Take an external vector, and convert to one for this ONB
		GenericVector3<T> into_onb(const GenericVector3<T>& c) const
		{
			return GenericVector3<T>(dotprod(c,m_u),dotprod(c,m_v),dotprod(c,m_w));
		}

		// Take an internal coord, and convert to one for a 'global' ONB.
		GenericCoord3<T> outof_onb(const GenericCoord3<T>& c) const
		{
			GenericVector3<T> cv(m_u * c.x() + m_v * c.y() + m_w * c.z());
			return( GenericCoord3<T>(cv.x(), cv.y(), cv.z()) );
		}

		// Take an internal point, and convert to one for a 'global' ONB.
		GenericPoint3<T> outof_onb(const GenericPoint3<T>& c) const
		{
			GenericVector3<T> cv(m_u * c.x() + m_v * c.y() + m_w * c.z());
			return( GenericPoint3<T>(cv.x(), cv.y(), cv.z()) );
		}

		// Take an internal vector, and convert to one for a 'global' ONB.
		GenericVector3<T> outof_onb(const GenericVector3<T>& c) const
		{
			return(m_u * c.x() + m_v * c.y() + m_w * c.z());
		}

		const GenericVector3<T>& u() const
		{
			return m_u;
		}
		const GenericVector3<T>& v() const
		{
			return m_v;
		}
		const GenericVector3<T>& w() const
		{
			return m_w;
		}

		GenericVector3<T>& u()
		{
			return m_u;
		}
		GenericVector3<T>& v()
		{
			return m_v;
		}
		GenericVector3<T>& w()
		{
			return m_w;
		}

		// Functions required for the tag-based toString interface
		void collectInternalMembers(MemberStringDumpCollector& collector) const;
		blocxx::String toString(const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE ) const;
		blocxx::String name() const { return "ONB"; }

	private:
		GenericVector3<T> m_u;
		GenericVector3<T> m_v;
		GenericVector3<T> m_w;
	}; // class ONB

	template <class T>
	void GenericONB<T>::collectInternalMembers(MemberStringDumpCollector& collector) const
	{
		collector.addMember("u", u());
		collector.addMember("v", v());
		collector.addMember("w", w());
	}

	template <class T>
	blocxx::String GenericONB<T>::toString(const Indentation& indent, StringDumpable::PrefixType prefix) const
	{
		blocxx::String tag;
		if( prefix == StringDumpable::E_PREFIX_CLASSNAME )
		{
			tag = GenericONB<T>::name();
		}
		Indentation internalIndent("", "", "");
		return indent.initial() + tag +
			"{" +
			panorama::toString(u(), indent.indentInside(), prefix) +
			"," +
			panorama::toString(v(), indent.indentInside(), prefix) +
			"," +
			panorama::toString(w(), indent.indentInside(), prefix) +
			"}";
	}

} // namespace panorama

#endif /* !defined(PANORAMA__GENERIC_ONB_HPP) */

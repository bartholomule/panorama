/*
 * $Id: GenericFrame.hpp,v 1.1.2.1 2010/03/06 20:44:07 kpharris Exp $
 *
 * Part of "Panorama" a playground for graphics development
 * Copyright (C) 2003 Kevin Harris
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
#if       !defined(PANORAMA__GENERIC_FRAME_HPP)
#define            PANORAMA__GENERIC_FRAME_HPP

/*
  GenericFrame.hpp -- A class to represent a complete coordinate system.

  Defining a frame with the u,v,w axii (think of them as x,y,z renamed
  to avoid any confusion) and the origin, will allow transformation
  from the global frame into that frame (globalToLocal), and from
  that frame into the global frame (localToGlobal).

  All transformations are simple rotations and translations.  No skew,
  scale, or any other such nasties can be performed.
*/

/*
  Revision History:
  18May2001 Created this file.
  18Sep2003 Renamed this file--(frame.hpp instead of frame.h), added
  the namespace, removed the matrix (as I don't think it is
  needed for simple coordinate system changes).  Also most
  things were rewritten to use vectors and points instead of
  coords.
*/

#include "panorama/common/StringDumpable.hpp"
#include "panorama/common/GenericPoint3.hpp"
#include "panorama/common/GenericVector3.hpp"
#include "panorama/common/GenericONB.hpp"

namespace panorama
{
	template <class T>
	class GenericFrame
	{
	public:
		// This tag allows use in the StringDumpable.hpp toString functions
		// without requiring the overridden virtual functions.
		typedef bool CanBeStringDumpedTag;

		GenericFrame()
			: m_basis()
			, m_origin(0,0,0)
		{
		}

		GenericFrame(const GenericPoint3<T>& origin, const GenericVector3<T>& w):
			m_basis(w),
			m_origin(origin)
		{
		}
		GenericFrame(const GenericPoint3<T>& origin,
			const GenericVector3<T>& a, const GenericVector3<T>& b):
			m_basis(a,b),
			m_origin(origin)
		{
		}

		GenericFrame(const GenericPoint3<T>& origin,
			const GenericVector3<T>& a, const GenericVector3<T>& b, const GenericVector3<T>& c):
			m_basis(a,b,c),
			m_origin(origin)
		{
		}

		GenericFrame(const GenericFrame<T>& f):
			m_basis(f.m_basis),
			m_origin(f.m_origin)
		{
		}

		GenericFrame<T>& operator=(const GenericFrame<T>& f)
		{
			if( &f != this )
			{
				m_basis = f.m_basis;
				m_origin = f.m_origin;
			}
			return(*this);
		}

		GenericVector3<T> u() const
		{
			return m_basis.u();
		}
		GenericVector3<T> v() const
		{
			return m_basis.v();
		}
		GenericVector3<T> w() const
		{
			return m_basis.w();
		}
		GenericPoint3<T> o() const
		{
			return m_origin;
		}

		GenericONB<T>& basis()
		{
			return m_basis;
		}
		GenericPoint3<T>& origin()
		{
			return m_origin;
		}
		const GenericONB<T>& basis() const
		{
			return m_basis;
		}
		const GenericPoint3<T>& origin() const
		{
			return m_origin;
		}

		//
		// Transfrom from external GenericFrame INTO this GenericFrame.
		//
		GenericVector3<T> globalToLocal(const GenericVector3<T>& v) const
		{
			return m_basis.globalToLocal(v);
		}

		GenericPoint3<T> globalToLocal(const GenericPoint3<T>& p) const
		{
			GenericVector3<T> v = p - origin();
			return m_basis.globalToLocal(GenericPoint3<T>(v.x(),v.y(),v.z()));
		}

		GenericCoord3<T> globalToLocal(const GenericCoord3<T>& c) const
		{
			GenericCoord3<T> c2(m_origin.x(), m_origin.y(), m_origin.z());
			return m_basis.globalToLocal(c - c2);
		}

		//
		// Transform OUT OF this frame into the 'global' frame.
		//
		GenericVector3<T> localToGlobal(const GenericVector3<T>& v) const
		{
			return m_basis.localToGlobal(v);
		}

		GenericPoint3<T> localToGlobal(const GenericPoint3<T>& p) const
		{
			return(m_basis.localToGlobal(p) +
				GenericVector3<T>(m_origin.x(), m_origin.y(), m_origin.z()));
		}

		GenericCoord3<T> localToGlobal(const GenericCoord3<T>& c) const
		{
			GenericCoord3<T> c2(m_origin.x(), m_origin.y(), m_origin.z());
			return m_basis.localToGlobal(c) + c2;
		}

		// Functions required for the tag-based toString interface
		void collectInternalMembers(MemberStringDumpCollector& collector) const;
		blocxx::String toString(const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE ) const;
		blocxx::String name() const { return "Frame"; }

	private:
		GenericONB<T> m_basis;
		GenericPoint3<T> m_origin;
	}; // class GenericFrame

	template <class T>
	void GenericFrame<T>::collectInternalMembers(MemberStringDumpCollector& collector) const
	{
		collector.addMember("origin", o());
		collector.addMember("u", u());
		collector.addMember("v", v());
		collector.addMember("w", w());
	}

	template <class T>
	blocxx::String GenericFrame<T>::toString(const Indentation& indent, StringDumpable::PrefixType prefix) const
	{
		blocxx::String tag;
		if( prefix == StringDumpable::E_PREFIX_CLASSNAME )
		{
			tag = GenericFrame<T>::name();
		}
		Indentation internalIndent("", "", "");
		return indent.initial() + tag +
			"{" +
			panorama::toString(o(), indent.indentInside(), prefix) +
			"," +
			panorama::toString(u(), indent.indentInside(), prefix) +
			"," +
			panorama::toString(v(), indent.indentInside(), prefix) +
			"," +
			panorama::toString(w(), indent.indentInside(), prefix) +
			"}";
	}

	//
	// This function will give the single frame which allows the
	// complete transformation of both frames (applied as inner first,
	// then outer).
	//
	template <class T>
	GenericFrame<T> mergeFrames(const GenericFrame<T>& outer_frame,
		const GenericFrame<T>& inner_frame)
	{
		return GenericFrame<T>(outer_frame.localToGlobal(inner_frame.o()),
			outer_frame.localToGlobal(inner_frame.u()),
			outer_frame.localToGlobal(inner_frame.v()),
			outer_frame.localToGlobal(inner_frame.w()));
	} // mergeFrames(GenericFrame, GenericFrame)

} // namespace panorama



#endif /* !defined(PANORAMA__GENERIC_FRAME_HPP) */

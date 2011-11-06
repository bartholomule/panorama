/*
 * $Id: GenericLine2.hpp,v 1.1.2.3 2011/11/06 03:42:06 kpharris Exp $
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

#if       !defined(PANORAMA_GENERICLINE2_HPP)
#define            PANORAMA_GENERICLINE2_HPP

#include "panorama/common/GenericPoint2.hpp"
#include "panorama/common/GenericVector2.hpp"
#include "panorama/common/Interval.hpp"
#include <limits>

namespace panorama
{

	/**
	 *
	 * A simple 2d line.
	 *
	 * @author Kevin Harris <kpharris@users.sourceforge.net>
	 * @version $Revision: 1.1.2.3 $
	 *
	 */
	template<class T>
	class GenericLine2
	{
	protected:
		GenericPoint2<T> m_origin;
		GenericVector2<T> m_direction;
		Interval<T> m_limits;

	public:
		// This tag allows use in the StringDumpable.hpp toString functions
		// without requiring the overridden virtual functions.
		typedef bool CanBeStringDumpedTag;

		GenericLine2();

		GenericLine2(const GenericPoint2<T>& o,
			const GenericVector2<T>& v,
			const Interval<T>& limits = Interval<T>(
				numeric_limits<T>::min(),
				numeric_limits<T>::max() ));
		GenericLine2(const GenericPoint2<T>& p1, const GenericPoint2<T>& p2);

		virtual ~GenericLine2();

		GenericLine2(const GenericLine2& old);

		GenericLine2& operator= (const GenericLine2& old);

		GenericPoint2<T> o() const
		{
			return m_origin;
		}
		GenericPoint2<T> origin() const
		{
			return m_origin;
		}

		GenericVector2<T> v() const
		{
			return m_direction;
		}
		GenericVector2<T> direction() const
		{
			return m_direction;
		}

		GenericPoint2<T> minimum() const
		{
			return(m_origin +
				m_limits.begin() * direction());
		}
		GenericPoint2<T> maximum() const
		{
			return(m_origin +
				m_limits.end() * direction());
		}
		GenericPoint2<T> point_at(const T& t) const
		{
			return(m_origin + direction() * t);
		}

		bool infinite() const
		{
			// Yes, I know that floating-point comparisons of this sort is usually bad,
			// but if they set it to something other than the default, this should
			// fail, so this wouldn't be infinite.
			return ( (m_limits.begin() <= -numeric_limits<T>::max()) &&
				(m_limits.end() >= numeric_limits<T>::max()) );
		}

		Interval<T> limits() const
		{
			return m_limits;
		}

		template<typename U>
		bool inside(U u) const
		{
			return m_limits.inside(u);
		}

		// Functions required for the tag-based toString interface
		void collectInternalMembers(MemberStringDumpCollector& collector) const;
		blocxx::String toString(const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE ) const;
		blocxx::String name() const { return "Line2"; }

	}; // class GenericLine2


	template<class T>
	GenericLine2<T>::GenericLine2():
		m_origin(),
		m_direction(),
		m_limits( -numeric_limits<T>::max(), numeric_limits<T>::max )
	{

	} // GenericLine2()

	template<class T>
	GenericLine2<T>::GenericLine2(const GenericPoint2<T>& o, const GenericVector2<T>& v,
		const Interval<T>& limits):
		m_origin(o),
		m_direction(v),
		m_limits(limits)
	{
	} // GenericLine2()

	template<class T>
	GenericLine2<T>::GenericLine2(const GenericPoint2<T>& p1, const GenericPoint2<T>& p2):
		m_origin(p1),
		m_direction(p2 - p1),
		m_limits( numeric_limits<T>::min(),
			T(1) - numeric_limits<T>::epsilon() )
	{

	} // GenericLine2()


	template<class T>
	GenericLine2<T>::~GenericLine2()
	{

	} // ~GenericLine2()

	template<class T>
	GenericLine2<T>::GenericLine2(const GenericLine2<T>& old):
		m_origin(old.m_origin),
		m_direction(old.m_direction),
		m_limits(old.m_limits)
	{

	} // GenericLine2(GenericLine2)

	template<class T>
	GenericLine2<T>& GenericLine2<T>::operator= (const GenericLine2<T>& old)
	{
		// Generic check for self-assignment
		if( &old != this )
		{
			m_origin = old.m_origin;
			m_direction = old.m_direction;
			m_limits = old.m_limits;
		}
		return(*this);
	} // GenericLine2::operator=(GenericLine2)

	template <class T>
	void GenericLine2<T>::collectInternalMembers(MemberStringDumpCollector& collector) const
	{
		collector.addMember("origin", o());
		collector.addMember("direction", v());
		collector.addMember("limits", limits());
	}

	template <class T>
	blocxx::String GenericLine2<T>::toString(const Indentation& indent, StringDumpable::PrefixType prefix) const
	{
		blocxx::String tag;
		if( prefix == StringDumpable::E_PREFIX_CLASSNAME )
		{
			tag = GenericLine2<T>::name();
		}

		return indent.initial() + tag +
			"|" +
			panorama::toString(o(), indent.indentInside(), prefix) +
			"," +
			panorama::toString(v(), indent.indentInside(), prefix) +
			"," +
			panorama::toString(limits(), indent.indentInside(), prefix) +
			"|";
	}

} // namespace panorama


#endif /* !defined(PANORAMA_GENERICLINE2_HPP) */


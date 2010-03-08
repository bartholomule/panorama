/*
 * $Id: GenericLine.hpp,v 1.1.2.1 2010/03/08 03:00:40 kpharris Exp $
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

#if       !defined(PANORAMA_GENERICLINE3_HPP)
#define            PANORAMA_GENERICLINE3_HPP

#include "panorama/common/GenericPoint3.hpp"
#include "panorama/common/GenericVector3.hpp"
#include "panorama/common/GenericInterval.hpp"
#include <limits>

namespace panorama
{

	/**
	 *
	 * A simple 3d line.
	 *
	 * @author Kevin Harris <kpharris@users.sourceforge.net>
	 * @version $Revision: 1.1.2.1 $
	 *
	 */
	template<class T, class PointType, class VectorType>
	class GenericLine
	{
	protected:
		PointType m_origin;
		VectorType m_direction;
		GenericInterval<T> m_limits;

	public:
		// This tag allows use in the StringDumpable.hpp toString functions
		// without requiring the overridden virtual functions.
		typedef bool CanBeStringDumpedTag;

		GenericLine();

		GenericLine(const PointType& o,
			const VectorType& v,
			const GenericInterval<T>& limits = GenericInterval<T>(
				std::numeric_limits<T>::min(),
				std::numeric_limits<T>::max() ));
		GenericLine(const PointType& p1, const PointType& p2);

		virtual ~GenericLine();

		GenericLine(const GenericLine& old);

		GenericLine& operator= (const GenericLine& old);

		PointType o() const
		{
			return m_origin;
		}
		PointType origin() const
		{
			return m_origin;
		}

		VectorType v() const
		{
			return m_direction;
		}
		VectorType direction() const
		{
			return m_direction;
		}

		PointType minimum() const
		{
			return(m_origin +
				m_limits.begin() * direction());
		}
		PointType maximum() const
		{
			return(m_origin +
				m_limits.end() * direction());
		}
		PointType point_at(const T& t) const
		{
			return(m_origin + direction() * t);
		}

		bool infinite() const
		{
			return ( (m_limits.begin() <= -std::numeric_limits<T>::max()) &&
				(m_limits.end() >= std::numeric_limits<T>::max()) );
		}

		GenericInterval<T> limits() const
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
		blocxx::String name() const { return "Line"; }

	}; // class GenericLine


	template<class T, class PointType, class VectorType>
	GenericLine<T,PointType,VectorType>::GenericLine():
		m_origin(T(0),T(0)),
		m_direction(T(1),T(0)),
		m_limits( -std::numeric_limits<T>::max(), std::numeric_limits<T>::max() )
	{

	} // GenericLine()

	template<class T, class PointType, class VectorType>
	GenericLine<T,PointType,VectorType>::GenericLine(const PointType& o, const VectorType& v,
		const GenericInterval<T>& limits):
		m_origin(o),
		m_direction(v),
		m_limits(limits)
	{
	} // GenericLine()

	template<class T, class PointType, class VectorType>
	GenericLine<T,PointType,VectorType>::GenericLine(const PointType& p1, const PointType& p2):
		m_origin(p1),
		m_direction(p2 - p1),
		m_limits( std::numeric_limits<T>::min(),
			T(1) - std::numeric_limits<T>::epsilon() )
	{

	} // GenericLine()


	template<class T, class PointType, class VectorType>
	GenericLine<T,PointType,VectorType>::~GenericLine()
	{

	} // ~GenericLine()

	template<class T, class PointType, class VectorType>
	GenericLine<T,PointType,VectorType>::GenericLine(const GenericLine<T,PointType,VectorType>& old):
		m_origin(old.m_origin),
		m_direction(old.m_direction),
		m_limits(old.m_limits)
	{

	} // GenericLine(GenericLine)

	template<class T, class PointType, class VectorType>
	GenericLine<T,PointType,VectorType>& GenericLine<T,PointType,VectorType>::operator= (const GenericLine<T,PointType,VectorType>& old)
	{
		// Generic check for self-assignment
		if( &old != this )
		{
			m_origin = old.m_origin;
			m_direction = old.m_direction;
			m_limits = old.m_limits;
		}
		return(*this);
	} // GenericLine::operator=(GenericLine)

	template<class T, class PointType, class VectorType>
	void GenericLine<T,PointType,VectorType>::collectInternalMembers(MemberStringDumpCollector& collector) const
	{
		collector.addMember("origin", o());
		collector.addMember("direction", v());
		collector.addMember("limits", limits());
	}

	template<class T, class PointType, class VectorType>
	blocxx::String GenericLine<T,PointType,VectorType>::toString(const Indentation& indent, StringDumpable::PrefixType prefix) const
	{
		blocxx::String tag;
		if( prefix == StringDumpable::E_PREFIX_CLASSNAME )
		{
			tag = GenericLine<T,PointType,VectorType>::name();
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


#endif /* !defined(PANORAMA_GENERICLINE3_HPP) */


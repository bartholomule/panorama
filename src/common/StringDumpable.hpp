/*
 * $Id: StringDumpable.hpp,v 1.1.2.2 2009/02/25 04:48:11 kpharris Exp $
 *
 * Part of GNU Panorama
 *
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

#if       !defined(PANORAMA__STRING_DUMPABLE_HPP)
#define            PANORAMA__STRING_DUMPABLE_HPP

/**
 * @author Kevin Harris
 */

#include "blocxx/String.hpp"
#include "blocxx/Array.hpp"
#include "blocxx/Format.hpp"
#include "blocxx/Reference.hpp"
#include "blocxx/IntrusiveReference.hpp"
#include <iosfwd>
#include <vector>

namespace panorama
{
	class Indentation;
	class MemberStringDumpCollector;

	/**
	 *
	 * The base class for string dumpable objects.  Anything derived
	 * from this can have its members converted (one way) to a string.
	 *
	 * @author Kevin Harris <kpharris@users.sourceforge.net>
	 * @version $Revision: 1.1.2.2 $
	 *
	 */
	class StringDumpable
	{
	public:
		enum PrefixType { E_PREFIX_NONE, E_PREFIX_CLASSNAME };

		typedef bool CanBeStringDumpedTag;

		StringDumpable();
		virtual ~StringDumpable();

		virtual void collectInternalMembers(MemberStringDumpCollector& collector) const = 0;

		virtual blocxx::String toString(const Indentation& indent, PrefixType prefix) const;
		virtual blocxx::String name() const = 0;

		blocxx::String toString() const;

	}; // class StringDumpable

	std::ostream& operator<<(std::ostream& o, const StringDumpable& s);

	class Indentation
	{
	public:
		Indentation();
		Indentation(const blocxx::String& initial, const blocxx::String& base, const blocxx::String& level);

		blocxx::String initial() const;
		blocxx::String level() const;

		Indentation indent() const;
		Indentation indentInside() const;

	private:
		blocxx::String m_initialIndent;
		blocxx::String m_baseIndent;
		blocxx::String m_levelIndent;
	};

	// This prefixes the given string with the indent.
	blocxx::String operator+(const Indentation& indent, const blocxx::String& s);

	// This one appends the indent to the string.  This is normally only used to
	// concatenate a bunch of strings together while formatting some output.
	blocxx::String operator+(const blocxx::String& s, const Indentation& indent);

	std::ostream& operator<<(std::ostream& o, const Indentation& indent);

	template <typename RefType>
	blocxx::String refToString(const RefType& p,
		const Indentation& indent = Indentation(),
		StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE)
	{
		if( p )
		{
			return indent.initial() +
				blocxx::Format("(%1)->", reinterpret_cast<const void*>(p.getPtr())) +
				toString(*p, indent.indentInside(), prefix);
		}
		else
		{
			return "NULL";
		}
	}

	template <typename T>
	blocxx::String toString(
		const blocxx::Reference<T>& p,
		const Indentation& indent = Indentation(),
		StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE)
	{
		return refToString(p, indent, prefix);
	}

	template <typename T>
	blocxx::String toString(
		const blocxx::IntrusiveReference<T>& p,
		const Indentation& indent = Indentation(),
		StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE)
	{
		return refToString(p, indent, prefix);
	}

	blocxx::String toString(const StringDumpable& object,
		const Indentation& indent = Indentation(),
		StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);


	// A generic templated toString() can't be used because it eats classes
	// derived from StringDumpable.  Provide string conversions for the common
	// native types to avoid the need.
	blocxx::String toString(char i, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);
	blocxx::String toString(unsigned char c, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);
	blocxx::String toString(short i, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);
	blocxx::String toString(unsigned short i, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);
	blocxx::String toString(int i, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);
	blocxx::String toString(unsigned int i, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);
	blocxx::String toString(long i, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);
	blocxx::String toString(unsigned long i, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);
 	blocxx::String toString(float i, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);
	blocxx::String toString(double i, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);
	blocxx::String toString(long double i, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);	
	blocxx::String toString(const std::string& i, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);
	blocxx::String toString(const blocxx::String& i, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);
	blocxx::String toString(const char* i, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE);

	template <typename ArrayType>
	blocxx::String arrayToString(const ArrayType& vec,
		const Indentation& indent = Indentation(),
		StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE)
	{
		blocxx::String retval = indent.initial() + "array\n";

		retval += indent + "{\n";

		Indentation nextIndent = indent.indent();

		typename ArrayType::const_iterator iter = vec.begin();
		if( iter != vec.end() )
		{
			retval += toString(*iter, nextIndent, prefix);
			for( ++iter; iter != vec.end(); ++iter )
			{
				retval += ",\n" + toString(*iter, nextIndent, prefix);
			}
			retval += "\n";
		}
		retval += indent + "}";

		return retval;
	}

	template <typename T>
	blocxx::String toString(const blocxx::Array<T>& vec,
		const Indentation& indent = Indentation(),
		StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE)
	{
		return arrayToString(vec, indent, prefix);
	}

	template <typename T>
	blocxx::String toString(const std::vector<T>& vec,
		const Indentation& indent = Indentation(),
		StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE)
	{
		return arrayToString(vec, indent, prefix);
	}

	class MemberStringDumpCollector
	{
	public:
		MemberStringDumpCollector(StringDumpable::PrefixType prefix, const Indentation& indent);

		template <typename T>
		void addMember(const blocxx::String& name, const T& value)
		{
			m_text += m_indent + name + " = " + ::panorama::toString(value, m_indent.indentInside(), const_cast<const StringDumpable::PrefixType&>(m_prefix)) + ";\n";
		}

		blocxx::String toString() const;
	private:
		StringDumpable::PrefixType m_prefix;
		Indentation m_indent;
		blocxx::String m_text;
	};

	template <typename T>
	blocxx::String toStringAsMembers(const T& object, const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE, typename T::CanBeStringDumpedTag tag = typename T::CanBeStringDumpedTag())
	{
		MemberStringDumpCollector collector(prefix, indent.indent());
		object.collectInternalMembers(collector);
		return (
			indent.initial() + object.name() + "\n" +
			indent + "{\n" +
			collector.toString() +
			indent + "}"
		);
	}

	// This version uses a simplified tag-based operation instead of requiring
	// virtual functions.  This makes it more suitable for use in objects such
	// as numeric types where the virtual function calls would be undesirable.
	template <typename T>
	blocxx::String toString(const T& object,
		const Indentation& indent = Indentation(),
		StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE,
		typename T::CanBeStringDumpedTag tag = typename T::CanBeStringDumpedTag())
	{
		return object.toString(indent, prefix);
	}

} // namespace panorama


#endif /* !defined(PANORAMA__STRING_DUMPABLE_HPP) */


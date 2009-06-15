/*
 * $Id: StringDumpable.cpp,v 1.1.2.3 2009/06/15 01:26:18 kpharris Exp $
 *
 * Part of GNU Panorama
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

/*
 * @author Kevin Harris
 */


#include "StringDumpable.hpp"

namespace panorama
{
	Indentation::Indentation()
		: m_initialIndent()
		, m_baseIndent()
		, m_levelIndent("  ")
	{
	}

	Indentation::Indentation(const blocxx::String& initial,
		const blocxx::String& base, const blocxx::String& level)
		: m_initialIndent(initial)
		, m_baseIndent(base)
		, m_levelIndent(level)
	{
	}

	blocxx::String Indentation::initial() const
	{
		return m_initialIndent;
	}

	blocxx::String Indentation::level() const
	{
		return m_baseIndent;
	}

	Indentation Indentation::indentInside() const
	{
		return Indentation(blocxx::String(), m_baseIndent + m_levelIndent, m_levelIndent);
	}

	Indentation Indentation::indent() const
	{
		blocxx::String indented = m_baseIndent + m_levelIndent;
		return Indentation(indented, indented, m_levelIndent);
	}

	blocxx::String operator+(const Indentation& indent, const blocxx::String& s)
	{
		return indent.level() + s;
	}

	blocxx::String operator+(const blocxx::String& s, const Indentation& indent)
	{
		return s + indent.level();
	}

	std::ostream& operator<<(std::ostream& o, const Indentation& indent)
	{
		return o << indent.level();
	}

	StringDumpable::StringDumpable()
	{
	} // StringDumpable()

	StringDumpable::~StringDumpable()
	{
	} // ~StringDumpable()

	blocxx::String StringDumpable::toString(const Indentation& indent, PrefixType prefix) const
	{
		return toStringAsMembers(*this, indent, prefix);
	}

	blocxx::String StringDumpable::toString() const
	{
		return toString(Indentation(), E_PREFIX_NONE);
	}

	blocxx::String StringDumpable::prefixName(PrefixType prefix) const
	{
		if( prefix == StringDumpable::E_PREFIX_CLASSNAME )
		{
			return name();
		}
		return blocxx::String();
	}

	std::ostream& operator<<(std::ostream& o, const StringDumpable& s)
	{
		o << s.toString();
		return o;
	}

	blocxx::String toString(char i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + blocxx::Format("%1", int(i));
	}
	blocxx::String toString(unsigned char i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + blocxx::Format("%<1:x!>", unsigned(i));
	}
	blocxx::String toString(short i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + blocxx::Format("%1", i);
	}
	blocxx::String toString(unsigned short i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + blocxx::Format("%1", i);
	}
	blocxx::String toString(int i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + blocxx::Format("%1", i);
	}
	blocxx::String toString(unsigned int i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + blocxx::Format("%1", i);
	}
	blocxx::String toString(long i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + blocxx::Format("%1", i);
	}
	blocxx::String toString(unsigned long i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + blocxx::Format("%1", i);
	}
 	blocxx::String toString(float i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + blocxx::Format("%1", i);
	}
	blocxx::String toString(double i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + blocxx::Format("%1", i);
	}
	blocxx::String toString(long double i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + blocxx::Format("%1", i);
	}
	blocxx::String toString(const std::string& i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + blocxx::String(i);
	}
	blocxx::String toString(const blocxx::String& i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + i;
	}
	blocxx::String toString(const char* i, const Indentation& indent, StringDumpable::PrefixType prefix)
	{
		return indent.initial() + i;
	}

	MemberStringDumpCollector::MemberStringDumpCollector(StringDumpable::PrefixType prefix, const Indentation& indent)
		: m_prefix(prefix), m_indent(indent)
	{
	}

	blocxx::String MemberStringDumpCollector::toString() const
	{
		return m_text;
	}

	blocxx::String toString(const StringDumpable& object,
		const Indentation& indent,	StringDumpable::PrefixType prefix)
	{
		return object.toString(indent, prefix);
	}
} // namespace panorama


/*
 * $Id: TextUtils.hpp,v 1.1.2.1 2011/11/06 03:41:35 kpharris Exp $
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

#if       !defined(PANORAMA_TEXT_UTILS_HPP)
#define            PANORAMA_TEXT_UTILS_HPP

/**
 * @author Kevin Harris
 */

#include <ctype.h>

namespace panorama
{
	// Advance the pointer to the next spot beyond whitespace.
	void skipSpaces(const char*& text);
	void skipSpaces(const char*& text, unsigned& len);
	unsigned lengthToNewline(const char* str);
	unsigned lengthToNewline(const char* str, unsigned len);
	unsigned long dehexify(const char* str, unsigned length);

	template<typename T>
	bool readInteger(const char*& text, T& value)
	{
		if( text )
		{
			skipSpaces(text);
			value = T(0);
			const char* current = text;

			while( *current && isdigit(*current) )
			{
				value = value * 10 + (*current - '0');
				++current;
			}
			// If we hit the end of the text or hit some whitespace, we ate it completely.
			if( (current != text) && (!*current || isspace(*current)) )
			{
				text = current;
				return true;
			}
		}
		return false;
	}

	template<typename T>
	bool readInteger(const char*& text, unsigned& length, T& value)
	{
		if( text && length > 0 )
		{
			skipSpaces(text);
			value = T(0);
			const char* current = text;
			unsigned len = length;

			while( (len > 0) && *current && isdigit(*current) )
			{
				value = value * 10 + (*current - '0');
				++current;
				--len;
			}
			// If we hit the end of the text or hit some whitespace, we ate it completely.
			if( (current != text) && (!*current || isspace(*current)) )
			{
				length = len;
				text = current;
				return true;
			}
		}
		return false;
	}
} // namespace panorama

#endif /* !defined(PANORAMA_TEXT_UTILS_HPP) */

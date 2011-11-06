/*
 * $Id: TextUtils.cpp,v 1.1.2.1 2011/11/06 03:41:35 kpharris Exp $
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

#include "panorama/common/TextUtils.hpp"

namespace graphlib
{
	void skipSpaces(const char*& text)
	{
		if( text )
		{
			while( isspace(*text) )
			{
				++text;
			}
		}
	}

	void skipSpaces(const char*& text, unsigned& len)
	{
		if( text )
		{
			while( (len > 0) && isspace(*text) )
			{
				++text;
				--len;
			}
		}
	}

	unsigned lengthToNewline(const char* str)
	{
		unsigned length = 0;

		if( str )
		{
			for(; str[length] && (str[length] != '\n'); ++length )
			{
			}
		}

		return length;
	}

	unsigned lengthToNewline(const char* str, unsigned len)
	{
		unsigned length = 0;

		if( str )
		{
			for(; (length < len) && str[length] && (str[length] != '\n'); ++length )
			{
			}
		}

		return length;
	}

	unsigned long dehexify(const char* str, unsigned length)
	{
		unsigned long retval = 0;

		if( str )
		{
			while(*str && length > 0)
			{
				if( (*str >= '0') && (*str <= '9') )
				{
					retval = (retval << 4) | (0 + unsigned(*str - '0'));
				}
				else if( (*str >= 'a') && (*str <= 'f') )
				{
					retval = (retval << 4) | (10 + unsigned(*str - 'a'));
				}
				else if( (*str >= 'A') && (*str <= 'F') )
				{
					retval = (retval << 4) | (10 + unsigned(*str - 'A'));
				}
				else
				{
					break;
				}
				++str;
				--length;
			}
		}
		return retval;
	}
}

/*
 * $Id: Capabilities.cpp,v 1.1.2.1 2009/07/19 17:32:34 kpharris Exp $
 *
 * Part of GNU Panorama
 *
 * Copyright (C) 2004 Kevin Harris
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

#include "panorama/common/Capabilities.hpp"

namespace panorama
{

	namespace // anonymous
	{
      void add_to_string_list(blocxx::String& s, const blocxx::String& item)
      {
			if( !s.empty() )
			{
            s += ", " + item;
			}
			else
			{
            s += item;
			}
      }

#define ADD_TO_RESULT_LONG(flag, name)          \
      do                                        \
      {                                         \
			if( (*this & (flag)) != NONE )			\
			{													\
            add_to_string_list(retval, name);   \
			}													\
      } while(0)
#define ADD_TO_RESULT_SHORT(flag, character)    \
      do                                        \
      {                                         \
			if( (*this & (flag)) != NONE )			\
			{													\
            retval += character;                \
			}													\
      } while(0)

#define CAPABILITIES_DEFINITION(cap_name)                               \
      cap_name& cap_name::operator |=(const cap_name::capabilities c)   \
      {                                                                 \
			my_capabilities = (cap_name::capabilities)(unsigned(c) | unsigned(my_capabilities)); \
			return *this;																	\
      }                                                                 \
                                                                        \
      cap_name& cap_name::operator |=(const cap_name& c)                \
      {                                                                 \
			my_capabilities = (cap_name::capabilities)(unsigned(c.my_capabilities) | unsigned(my_capabilities)); \
			return *this;																	\
      }                                                                 \
                                                                        \
      cap_name& cap_name::operator &=(const cap_name::capabilities c)   \
      {                                                                 \
			my_capabilities = (cap_name::capabilities)(unsigned(c) & unsigned(my_capabilities)); \
			return *this;																	\
      }                                                                 \
      cap_name& cap_name::operator &=(const cap_name& c)                \
      {                                                                 \
			my_capabilities = (cap_name::capabilities)(unsigned(c.my_capabilities) & unsigned(my_capabilities)); \
			return *this;																	\
      }                                                                 \
                                                                        \
      cap_name operator &(const cap_name& c1, cap_name::capabilities c2)    \
      {                                                                 \
			return cap_name(cap_name::capabilities(unsigned(c1.my_capabilities) & unsigned(c2))); \
      }                                                                 \
      cap_name operator &(cap_name::capabilities c1, const cap_name& c2)    \
      {                                                                 \
			return cap_name(cap_name::capabilities(unsigned(c1) & unsigned(c2.my_capabilities))); \
      }                                                                 \
      cap_name operator &(const cap_name& c1, const cap_name& c2)       \
      {                                                                 \
			return cap_name(cap_name::capabilities(unsigned(c1.my_capabilities) & unsigned(c2.my_capabilities))); \
      }                                                                 \
      cap_name operator |(const cap_name& c1, const cap_name& c2)       \
      {                                                                 \
			return cap_name(cap_name::capabilities(unsigned(c1.my_capabilities) | unsigned(c2.my_capabilities))); \
      }                                                                 \
      cap_name operator ~(const cap_name::capabilities& c)              \
      {                                                                 \
			return cap_name(cap_name::capabilities(cap_name::ALL & ~unsigned(c))); \
      }                                                                 \
                                                                        \
      cap_name operator ~(const cap_name& c)                            \
      {                                                                 \
			return cap_name(cap_name::capabilities(cap_name::ALL & ~unsigned(c.my_capabilities))); \
      }                                                                 \
                                                                        \
      bool operator==(const cap_name& i1, const cap_name& i2)           \
      {                                                                 \
			return unsigned(i1.my_capabilities) == unsigned(i2.my_capabilities); \
      }                                                                 \
      bool operator!=(const cap_name& i1, const cap_name& i2)           \
      {                                                                 \
			return unsigned(i1.my_capabilities) != unsigned(i2.my_capabilities); \
      }																						\
		std::ostream& operator<<(std::ostream& o, const cap_name& c)		\
		{																						\
			return o << c.toString();													\
		}																						\
		std::ostream& operator<<(std::ostream& o, cap_name::capabilities c) \
		{																						\
			return o << cap_name(c).toString();										\
		}


	} // end anonymous namespace

	blocxx::String IntersectionCapabilities::toString(const Indentation& indent, StringDumpable::PrefixType prefix) const
	{
		blocxx::String retval;

		ADD_TO_RESULT_LONG(IntersectionCapabilities::HIT_FIRST, "First Object Hit");
		ADD_TO_RESULT_LONG(IntersectionCapabilities::HIT_ALL, "All Objects Hit");
		ADD_TO_RESULT_LONG(IntersectionCapabilities::HIT_CONTAINERS, "Containers Hit");
		ADD_TO_RESULT_LONG(IntersectionCapabilities::NORMAL_CALCULATION, "Normal Calculation");
		ADD_TO_RESULT_LONG(IntersectionCapabilities::UV_CALCULATION, "UV Calculation");
		ADD_TO_RESULT_LONG(IntersectionCapabilities::LOCAL_SYSTEM_CALCULATION, "Local Coord System Calculation");
		ADD_TO_RESULT_LONG(IntersectionCapabilities::TIME_SAMPLING, "Time Sampling");

		if( retval.empty() )
		{
			retval = "NONE";
		}

		return "{" + retval + "}";
	}


	blocxx::String IntersectionCapabilities::toStringShort() const
	{
      blocxx::String retval;

      ADD_TO_RESULT_SHORT(IntersectionCapabilities::HIT_FIRST, "F");
      ADD_TO_RESULT_SHORT(IntersectionCapabilities::HIT_ALL, "A");
      ADD_TO_RESULT_SHORT(IntersectionCapabilities::HIT_CONTAINERS, "C");
      ADD_TO_RESULT_SHORT(IntersectionCapabilities::NORMAL_CALCULATION, "N");
      ADD_TO_RESULT_SHORT(IntersectionCapabilities::UV_CALCULATION, "U");
      ADD_TO_RESULT_SHORT(IntersectionCapabilities::LOCAL_SYSTEM_CALCULATION, "L");
      ADD_TO_RESULT_SHORT(IntersectionCapabilities::TIME_SAMPLING, "T");

      return retval;
	}

	CAPABILITIES_DEFINITION(IntersectionCapabilities);

	blocxx::String ObjectCapabilities::toString(const Indentation& indent, StringDumpable::PrefixType prefix) const
	{
      blocxx::String retval;

      ADD_TO_RESULT_LONG(ObjectCapabilities::INFINITE, "Infinite");
      ADD_TO_RESULT_LONG(ObjectCapabilities::BOUNDABLE, "Boundable");
      ADD_TO_RESULT_LONG(ObjectCapabilities::MOVABLE, "Movable");
      ADD_TO_RESULT_LONG(ObjectCapabilities::POLYGONIZATION, "Polygonization");
      ADD_TO_RESULT_LONG(ObjectCapabilities::CONTAINER, "Container");
      ADD_TO_RESULT_LONG(ObjectCapabilities::IMPLICIT, "Implicit Surface");

      if( retval.empty() )
      {
			retval = "NONE";
      }

      return "{" + retval + "}";
	}


	blocxx::String ObjectCapabilities::toStringShort() const
	{
      blocxx::String retval;

      ADD_TO_RESULT_SHORT(ObjectCapabilities::INFINITE, "I");
      ADD_TO_RESULT_SHORT(ObjectCapabilities::BOUNDABLE, "B");
      ADD_TO_RESULT_SHORT(ObjectCapabilities::MOVABLE, "M");
      ADD_TO_RESULT_SHORT(ObjectCapabilities::POLYGONIZATION, "P");
      ADD_TO_RESULT_SHORT(ObjectCapabilities::CONTAINER, "C");
      ADD_TO_RESULT_SHORT(ObjectCapabilities::IMPLICIT, "F");
      return retval;
	}

	CAPABILITIES_DEFINITION(ObjectCapabilities);

	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	blocxx::String MaterialCapabilities::toString(const Indentation& indent, StringDumpable::PrefixType prefix) const
	{
      blocxx::String retval;

      ADD_TO_RESULT_LONG(MaterialCapabilities::DIFFUSE, "Diffuse");
      ADD_TO_RESULT_LONG(MaterialCapabilities::EMISSIVE, "Emissive");
      ADD_TO_RESULT_LONG(MaterialCapabilities::REFLECTIVE, "Reflective");
      ADD_TO_RESULT_LONG(MaterialCapabilities::TRANSMISSIVE, "Transmissive");

      if( retval.empty() )
      {
			retval = "NONE";
      }

      return "{" + retval + "}";
	}


	blocxx::String MaterialCapabilities::toStringShort() const
	{
      blocxx::String retval;

      ADD_TO_RESULT_SHORT(MaterialCapabilities::DIFFUSE, "D");
      ADD_TO_RESULT_SHORT(MaterialCapabilities::EMISSIVE, "E");
      ADD_TO_RESULT_SHORT(MaterialCapabilities::REFLECTIVE, "R");
      ADD_TO_RESULT_SHORT(MaterialCapabilities::TRANSMISSIVE, "T");

      return retval;
	}

	CAPABILITIES_DEFINITION(MaterialCapabilities);

} // namespace amethyst

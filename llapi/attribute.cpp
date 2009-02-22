/*
*  Copyright (C) 2001 Kevin Harris
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful, but
*  WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "llapi/attribute.h"
#include "llapi/string_format.hpp"

namespace panorama
{

  DEFINE_EXCEPTION(AttributeException);
  DEFINE_EXCEPTION_BASE(AttributeConversionException, AttributeException);

  class Attribute::AttributeImpl : public Cloneable
  {
  public:

    virtual std::string name() const = 0;
    virtual std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const = 0;
    virtual Attribute::AttributeType getType() const = 0;
    virtual Attribute::AttributeImpl* clone_new() const = 0;
  };

  struct TAttribInt : public Attribute::AttributeImpl
  {
    TAttribInt (int i): m_value(i) { }

    Attribute::AttributeType getType() const { return Attribute::E_INTEGER; }
    std::string name() const { return "integer"; }
    TAttribInt* clone_new() const { return new TAttribInt(*this); }
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const { return string_format("integer(%1)", m_value); }

    int m_value;
  };  /* struct TAttribInt */


  struct TAttribReal : public Attribute::AttributeImpl
  {
    TAttribReal (TScalar s): m_value(s) { }

    Attribute::AttributeType getType() const { return Attribute::E_REAL; }
    std::string name() const { return "real"; }
    TAttribReal* clone_new() const { return new TAttribReal(*this); }
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const { return string_format("real(%1)", m_value); }

    TScalar m_value;
  };  /* struct TAttribReal */


  struct TAttribBool : public Attribute::AttributeImpl
  {
    TAttribBool (bool b): m_value(b) { }

    Attribute::AttributeType getType() const { return Attribute::E_BOOL; }
    std::string name() const { return "bool"; }
    TAttribBool* clone_new() const { return new TAttribBool(*this); }
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const { return string_format("bool(%1)", m_value); }

    bool m_value;
  };  /* struct TAttribBool */


  struct TAttribString : public Attribute::AttributeImpl
  {
    TAttribString (const std::string& s): m_value(s) { }

    Attribute::AttributeType getType() const { return Attribute::E_STRING; }
    std::string name() const { return "string"; }
    TAttribString* clone_new() const { return new TAttribString(*this); }
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const { return string_format("string(%1)", m_value); }

    std::string m_value;
  };  /* struct TAttribString */


  struct TAttribStringList : public TAttribString
  {
    TAttribStringList (const std::vector<std::string>& s, const std::string& defaultValue = std::string())
      : TAttribString(defaultValue)
      , m_choices(s)
    {
      if( TAttribString::m_value.empty() && !m_choices.empty() )
      {
        TAttribString::m_value = *m_choices.begin();
      }
    }

    Attribute::AttributeType getType() const { return Attribute::E_STRING_LIST; }
    std::string name() const { return "stringlist"; }
    TAttribStringList* clone_new() const { return new TAttribStringList(*this); }
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const
    {
      Indentation next = indent.nextLevel();
      return indent.initial() + TAttribStringList::name() + "\n" +
        indent + "{\n" +
        next + string_format("default=\"%1\"\n", TAttribString::m_value) +
        next + "values=" + ::panorama::toString(m_choices, next.nextLevel(), prefix) + "\n" +
        indent + "}\n";
    }

    std::vector<std::string> m_choices;
  };  /* struct TAttribStringList */


  struct TAttribColor : public Attribute::AttributeImpl
  {
    TAttribColor (const TColor& c): m_value(c) { }
    TAttribColor (const TVector& v): m_value(v.x(), v.y(), v.z()) { }
    TAttribColor (TScalar s): m_value(s, s, s) { }

    Attribute::AttributeType getType() const { return Attribute::E_COLOR; }
    std::string name() const { return "color"; }
    TAttribColor* clone_new() const { return new TAttribColor(*this); }
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const { return m_value.toString(indent, prefix); }

    TColor m_value;
  };  /* struct TAttribColor */

  struct TAttribVector : public Attribute::AttributeImpl
  {
    TAttribVector (const TVector& v): m_value(v) { }
    TAttribVector (TScalar s): m_value(s, s, s) { }

    Attribute::AttributeType getType() const { return Attribute::E_VECTOR; }
    std::string name() const { return "vector"; }
    TAttribVector* clone_new() const { return new TAttribVector(*this); }
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const { return m_value.toString(indent, prefix); }

    TVector m_value;
  };  /* struct TAttribVector */

  struct TAttribVector2 : public Attribute::AttributeImpl
  {
    TAttribVector2 (const TVector2& v): m_value(v) { }
    TAttribVector2 (TScalar s): m_value(s, s) { }

    Attribute::AttributeType getType() const { return Attribute::E_VECTOR2; }
    std::string name() const { return "vector2"; }
    TAttribVector2* clone_new() const { return new TAttribVector2(*this); }
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const { return m_value.toString(indent, prefix); }

    TVector2 m_value;
  };  /* struct TAttribVector2 */

  struct TAttribPoint : public Attribute::AttributeImpl
  {
    TAttribPoint (const TPoint& v): m_value(v) { }
    TAttribPoint (TScalar s): m_value(s, s, s) { }

    Attribute::AttributeType getType() const { return Attribute::E_POINT; }
    std::string name() const { return "point"; }
    TAttribPoint* clone_new() const { return new TAttribPoint(*this); }
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const { return m_value.toString(indent, prefix); }

    TPoint m_value;
  };  /* struct TAttribPoint */

  struct TAttribPoint2 : public Attribute::AttributeImpl
  {
    TAttribPoint2 (TPoint2 v): m_value(v) { }
    TAttribPoint2 (TScalar s): m_value(s, s) { }

    Attribute::AttributeType getType() const { return Attribute::E_POINT2; }
    std::string name() const { return "point2"; }
    TAttribPoint2* clone_new() const { return new TAttribPoint2(*this); }
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const { return m_value.toString(indent, prefix); }

    TPoint2 m_value;
  };  /* struct TAttribPoint2 */

  struct TAttribArray : public Attribute::AttributeImpl
  {
    TAttribArray (TVector v): m_value() { m_value.push_back(v.x()); m_value.push_back(v.y()); m_value.push_back(v.z()); }
    TAttribArray (TVector2 v): m_value() { m_value.push_back(v.x()); m_value.push_back(v.y()); }
    TAttribArray (TScalar s): m_value(1, s) { }
    TAttribArray (const std::vector<TScalar>& v): m_value(v) { }

    Attribute::AttributeType getType() const { return Attribute::E_ARRAY; }
    std::string name() const { return "array"; }
    TAttribArray* clone_new() const { return new TAttribArray(*this); }
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const { return ::panorama::toString(m_value, indent, prefix); }

    std::vector<TScalar> m_value;
  };  /* struct TAttribArray */


  struct TAttribGenericArray : public Attribute::AttributeImpl
  {
    TAttribGenericArray (): m_value() { }
    TAttribGenericArray (const std::vector<Attribute>& va): m_value(va) { }

    Attribute::AttributeType getType() const { return Attribute::E_ARRAY; }
    std::string name() const { return "GenericArray"; }
    TAttribGenericArray* clone_new() const { return new TAttribGenericArray(*this); }
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const { return ::panorama::toString(m_value, indent, prefix); }

    std::vector<Attribute> m_value;
  };  /* struct TAttribGenericArray */

  Attribute::Attribute(AttributeType type)
  {
    switch(type)
    {
    case E_INTEGER:
      m_impl.set(new TAttribInt(0));
      break;
    case E_REAL:
      m_impl.set(new TAttribReal(0));
      break;
    case E_BOOL:
      m_impl.set(new TAttribBool(false));
      break;
    case E_STRING:
      m_impl.set(new TAttribString(""));
      break;
      // FIXME!
    }
  }
} // end namespace panorama

/*
 *  Copyright (C) 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef PANORAMA_ATTRIBUTE_H_INCLUDED
#define PANORAMA_ATTRIBUTE_H_INCLUDED

#include <string>
#include <vector>
#include "llapi/attribs.h"
#include "llapi/llapi_defs.h"
#include "llapi/color.h"
#include "llapi/exception.hpp"
#include "llapi/string_format.hpp"

namespace panorama
{
  DECLARE_EXCEPTION(AttributeException);
  DECLARE_EXCEPTION_BASE(AttributeConversionException, AttributeException);

  /**
   * A base class (struct) for attribute values.
   */
  class Attribute : public StringDumpable
  {
  public:
    Attribute();
    virtual ~Attribute();

    virtual std::string name() const;
    virtual std::string toString() const;
    virtual std::string internalMembers(const Indentation& indent, PrefixType prefix) const;

    enum AttributeType
    {
      E_NONE,
      E_ANY,
      E_INTEGER,
      E_REAL,
      E_BOOL,
      E_STRING,
      E_COLOR,
      E_VECTOR,
      E_VECTOR2,
      E_POINT,
      E_POINT2,

      // These next ones are for returning from something, to show a list of
      // possible options.  The results are read-only!!!  When making a
      // selection, send the value back as its normal type (without the _LIST).
      // They will be returned as a pointer to a vector of the type (pvValue).
      E_INTEGER_LIST, // vector<int>
      E_REAL_LIST, // vector<TScalar>
      E_BOOL_LIST, // vector<bool>
      E_STRING_LIST, // vector<std::string>
      E_COLOR_LIST, // vector<TColor>
      E_VECTOR_LIST, // vector<TVector>
      E_VECTOR2_LIST, // vector<TVector2>
      E_POINT_LIST, // vector<TPoint>
      E_POINT2_LIST, // vector<TPoint2>

      E_IMAGE,
      E_BSDF,
      E_CAMERA,
      E_LIGHT,
      E_PATTERN,
      E_PERTURBATION,
      E_MATERIAL,
      E_RENDERER,
      E_OBJECT,
      E_AGGREGATE,
      E_OBJECT_FILTER,
      E_IMAGE_FILTER,
      E_SCENE,
      E_IMAGE_IO,
      E_ARRAY,
      E_GENERIC_ARRAY
    };

    // Creates an empty shell of a type...
    Attribute(AttributeType type);

    AttributeType getType() const;

    // Specialized constructors
    Attribute(int value);
    Attribute(TScalar value);
    Attribute(const TVector& value);
    Attribute(const TVector2& value);
    Attribute(const TPoint& value);
    Attribute(const TPoint2& value);
    Attribute(const TColor& value);

    template <class T>
    T get() const
    {
      T value;
      get(value);
      return value;
    }

    template <class T>
    T convertTo() const;

    void get(int&) const;
    void get(TScalar&) const;
    void get(TVector&) const;
    void get(TVector2&) const;
    void get(TPoint&) const;
    void get(TPoint2&) const;
    void get(TColor&) const;

    // Accessors.  These will throw an AttributeException if the value is of an
    // incorrect type.
    int getInt() const { return get<int>(); }
    TScalar getFloat() const { return get<TScalar>(); }
    TVector getVector() const { return get<TVector>(); }
    TVector2 getVector2() const { return get<TVector2>(); }
    TPoint getPoint() const { return get<TPoint>(); }
    TPoint2 getPoint2() const { return get<TPoint2>(); }
    TColor getColor() const { return get<TColor>(); }

    // Conversions.  These will throw an AttributeConversionException if the
    // value is of an incorrect type.
    int convertToInt() const;

    // This is not for general use.
    class AttributeImpl;
  private:

    template <typename T>
    void assertSameType();

    rc_pointer<AttributeImpl> m_impl;
  };  /* struct Attribute */

  typedef std::vector<Attribute> AttributeArray;

  template <class T> struct AttributeValueType { };

#define ATTRIB_VALUE_TYPE_DECL1(nativetype, typecode) \
  template <> \
  struct AttributeValueType<nativetype> \
  { \
    static const Attribute::AttributeType type = Attribute::typecode; \
  };

#define ATTRIB_VALUE_TYPE_DECL2(nativetype, typecode) \
  template <> \
  struct AttributeValueType<const nativetype&> \
  { \
    static const Attribute::AttributeType type = Attribute::typecode; \
  };

#define ATTRIB_VALUE_TYPE_DECL(nativetype, typecode) \
  ATTRIB_VALUE_TYPE_DECL1(nativetype, typecode) \
  ATTRIB_VALUE_TYPE_DECL2(nativetype, typecode)

  ATTRIB_VALUE_TYPE_DECL1(void, E_NONE);
  ATTRIB_VALUE_TYPE_DECL(Attribute, E_ANY);
  ATTRIB_VALUE_TYPE_DECL(int, E_INTEGER);
  ATTRIB_VALUE_TYPE_DECL(bool, E_BOOL);
  ATTRIB_VALUE_TYPE_DECL(std::string, E_STRING);
  ATTRIB_VALUE_TYPE_DECL(char*, E_STRING);
  ATTRIB_VALUE_TYPE_DECL(TScalar, E_REAL);
  ATTRIB_VALUE_TYPE_DECL(TColor, E_COLOR);
  ATTRIB_VALUE_TYPE_DECL(TVector, E_VECTOR);
  ATTRIB_VALUE_TYPE_DECL(TVector2, E_VECTOR2);
  ATTRIB_VALUE_TYPE_DECL(TPoint, E_POINT);
  ATTRIB_VALUE_TYPE_DECL(TPoint2, E_POINT2);
  ATTRIB_VALUE_TYPE_DECL(std::vector<int>, E_INTEGER_LIST);
  ATTRIB_VALUE_TYPE_DECL(std::vector<TScalar>, E_REAL_LIST);
  ATTRIB_VALUE_TYPE_DECL(std::vector<bool>, E_BOOL_LIST);
  ATTRIB_VALUE_TYPE_DECL(std::vector<std::string>, E_STRING_LIST);
  ATTRIB_VALUE_TYPE_DECL(std::vector<TColor>, E_COLOR_LIST);
  ATTRIB_VALUE_TYPE_DECL(std::vector<TVector>, E_VECTOR_LIST);
  ATTRIB_VALUE_TYPE_DECL(std::vector<TVector2>, E_VECTOR2_LIST);
  ATTRIB_VALUE_TYPE_DECL(std::vector<TPoint>, E_POINT_LIST);
  ATTRIB_VALUE_TYPE_DECL(std::vector<TPoint2>, E_POINT2_LIST);


  template <typename T>
  void Attribute::assertSameType()
  {
    if( getType() != AttributeValueType<T>::typecode )
    {
      THROW(AttributeException, string_format("Types do not match: %1 and %2", getType(), AttributeValueType<T>::typecode).c_str());
    }
  }
}

#endif  /* PANORAMA_ATTRIBUTE_H_INCLUDED */

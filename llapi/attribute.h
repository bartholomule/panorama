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

#ifndef _ATTRIBUTE__
#define _ATTRIBUTE__

#include <string>
#include "llapi/attribs.h"
#include "llapi/llapi_defs.h"

/* The base struct is now in attribs.h */

struct TAttribInt : public TAttribute
{

  int   tValue;

  TAttribInt (void)  { eType = FX_INTEGER; }
  TAttribInt (int i) { eType = FX_INTEGER; tValue = i; }  

  virtual string AttributeName() const { return "integer"; }
  TATTRIB_CLONE_NEW_DEF(TAttribInt);
  
  virtual string toString() const
  {
    char buffer[100];
    sprintf(buffer,"int(%d)",tValue);
    return buffer;
  }
  
};  /* struct TAttribInt */

struct TAttribReal : public TAttribute
{

  TScalar   tValue;

  TAttribReal (void) { eType = FX_REAL; }
  TAttribReal (TScalar s) { eType = FX_REAL; tValue = s; }  

  virtual string AttributeName() const { return "real"; }
  TATTRIB_CLONE_NEW_DEF(TAttribReal);
  
  virtual string toString() const
  {
    char buffer[100];
    sprintf(buffer,"real(%f)",float(tValue));
    return buffer;
  }  
};  /* struct TAttribReal */


struct TAttribBool : public TAttribute
{

  bool   tValue;
  
  TAttribBool (void)   { eType = FX_BOOL; }
  TAttribBool (bool b) { eType = FX_BOOL; tValue = b; }
  
  virtual string AttributeName() const { return "bool"; }
  TATTRIB_CLONE_NEW_DEF(TAttribBool);
  
  virtual string toString() const
  {
    return string("bool(") + (tValue?("true"):("false")) + ")";
  }  
  
};  /* struct TAttribBool */


struct TAttribString : public TAttribute
{

  string   tValue;
  
  TAttribString (void) { eType = FX_STRING; }
  TAttribString (const string& s):tValue(s) { eType = FX_STRING; }  

  virtual string AttributeName() const { return "string"; }
  TATTRIB_CLONE_NEW_DEF(TAttribString);
  
  virtual string toString() const
  {
    return "string(" + tValue + ")";
  }
  
};  /* struct TAttribString */


#include <vector>
using std::vector;

struct TAttribStringList : public TAttribString
{

  vector<string> choices;
  
  TAttribStringList (void) { eType = FX_STRING_LIST; }
  TAttribStringList (const vector<string>& sv,
		     const string& s = "") :
    TAttribString(s),
    choices(sv)
  {
    eType = FX_STRING_LIST;
    if( tValue.empty() && !choices.empty() )
    {
	tValue = *choices.begin();
    }
  }  

  virtual string AttributeName() const { return "stringlist"; }
  TATTRIB_CLONE_NEW_DEF(TAttribStringList);
  
  virtual string toString() const
  {
    string s = "stringlist(" + tValue + ":";

    vector<string>::const_iterator i = choices.begin();

    if( i != choices.end() )
    {
      s += *i;

      for(++i; i != choices.end(); ++i)
      {
	s += ", " + *i;
      }
    }
    return s + ")";
  }
  
};  /* struct TAttribStringList */


struct TAttribColor : public TAttribute
{

  TColor   tValue;
  
  TAttribColor (void) { eType = FX_COLOR; }
  TAttribColor (const TColor& c) : tValue(c)     { eType = FX_COLOR; }
  TAttribColor (TScalar s)       : tValue(s,s,s) { eType = FX_COLOR; }    
  TAttribColor (const TVector& v): tValue(v[0],v[1],v[2]) { eType = FX_COLOR; }
  
  virtual string AttributeName() const { return "color"; }
  TATTRIB_CLONE_NEW_DEF(TAttribColor);
  
  virtual string toString() const
  {
    char buffer[1024];
    sprintf( buffer, "color(%f,%f,%f)", tValue.red(), tValue.green(), tValue.blue() );
    return string(buffer);
  }
  
};  /* struct TAttribColor */


struct TAttribVector : public TAttribute
{

  TVector   tValue;
  
  TAttribVector (void) { eType = FX_VECTOR; }
  TAttribVector (const TVector& v) : tValue(v)     { eType = FX_VECTOR; }
  TAttribVector (TScalar s )       : tValue(s,s,s) { eType = FX_VECTOR; }    
  virtual string AttributeName() const { return "vector"; }
  TATTRIB_CLONE_NEW_DEF(TAttribVector);
  
  virtual string toString() const
  {
    char buffer[1024];
    sprintf( buffer, "vector(%f,%f,%f)", tValue.x(), tValue.y(), tValue.z() );
    return string(buffer);
  }
  
};  /* struct TAttribVector */


struct TAttribVector2 : public TAttribute
{

  TVector2   tValue;
  
  TAttribVector2 (void)                           { eType = FX_VECTOR2; }
  TAttribVector2 (const TVector2& v): tValue(v)   { eType = FX_VECTOR2; }
  TAttribVector2 (TScalar s)        : tValue(s,s) { eType = FX_VECTOR2; }  
  
  virtual string AttributeName() const { return "vector2"; }
  TATTRIB_CLONE_NEW_DEF(TAttribVector2);
  
  virtual string toString() const
  {
    char buffer[1024];
    sprintf( buffer, "vector2(%f,%f)", tValue.x(), tValue.y() );
    return string(buffer);    
  }
  
};  /* struct TAttribVector2 */


magic_pointer<TAttribInt>     get_int(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribReal>    get_real(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribBool>    get_bool(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribString>  get_string(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribStringList> get_stringlist(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribColor>   get_color(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribVector>  get_vector(const magic_pointer<TAttribute> attr);
magic_pointer<TAttribVector2> get_vector2(const magic_pointer<TAttribute> attr);

magic_pointer<TAttribute> base_to_attr(const magic_pointer<TBaseClass> base);
magic_pointer<TBaseClass> attr_to_base(const magic_pointer<TAttribute> attr);

#endif  /* _ATTRIBUTE__ */

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

#if defined(BROKEN_RETURN_SUBTYPES_ON_VIRTUAL)
// The compiler is BROKEN!  It does not recognize that returning a pointer to a subtype 
// can be converted (virtually) to the base pointer (on singly derived, public subclasses).
//
#define TATTRIB_CLONE_NEW_DEF(name) virtual TAttribute* clone_new() const { return new name(*this); }
#else
// Do it the right way!
#define TATTRIB_CLONE_NEW_DEF(name) virtual name* clone_new() const { return new name(*this); }
#endif /* defined(BROKEN_RETURN_SUBTYPES_ON_VIRTUAL) */

/*
  A base class (struct) for attribute values.
 */
struct TAttribute
{

  EAttribType   eType;

  virtual ~TAttribute() { }
  virtual string AttributeName() const { return "NONE"; }
  TATTRIB_CLONE_NEW_DEF(TAttribute);
  
};  /* struct TAttribute */


struct TAttribReal : public TAttribute
{

  TScalar   tValue;

  TAttribReal (void)
  {
    eType = FX_REAL;
  }

  virtual string AttributeName() const { return "real"; }
  TATTRIB_CLONE_NEW_DEF(TAttribReal);
  
};  /* struct TAttribReal */


struct TAttribBool : public TAttribute
{

  bool   gValue;
  
  TAttribBool (void)
  {
    eType = FX_BOOL;
  }
  virtual string AttributeName() const { return "bool"; }
  TATTRIB_CLONE_NEW_DEF(TAttribBool);
    
};  /* struct TAttribBool */


struct TAttribString : public TAttribute
{

  string   tValue;
  
  TAttribString (void)
  {
    eType = FX_STRING;
  }

  virtual string AttributeName() const { return "string"; }
  TATTRIB_CLONE_NEW_DEF(TAttribString);
  
};  /* struct TAttribString */


struct TAttribColor : public TAttribute
{

  TColor   tValue;
  
  TAttribColor (void)
  {
    eType = FX_COLOR;
  }
  virtual string AttributeName() const { return "color"; }
  TATTRIB_CLONE_NEW_DEF(TAttribColor);
    
};  /* struct TAttribColor */


struct TAttribVector : public TAttribute
{

  TVector   tValue;
  
  TAttribVector (void)
  {
    eType = FX_VECTOR;
  }
  virtual string AttributeName() const { return "vector"; }
  TATTRIB_CLONE_NEW_DEF(TAttribVector);
    
};  /* struct TAttribVector */


struct TAttribVector2 : public TAttribute
{

  TVector2   tValue;
  
  TAttribVector2 (void)
  {
    eType = FX_VECTOR2;
  }
  
  virtual string AttributeName() const { return "vector2"; }
  TATTRIB_CLONE_NEW_DEF(TAttribVector2);
    
};  /* struct TAttribVector2 */

/* A generic attribute type which can be used where any of the TAttribute
   derived classes can be used.

   This requires that a clone and destroy function be set on all instances
   where the data is non-null.
*/
struct TAttribOther : public TAttribute
{
  void* tValue;
  void  (*Destroy)(void*);           // A destructor/deallocator (delete)
  void* (*Clone)(const void*);       // Allocate and copy        (new)

  TAttribOther ( EAttribType eTYPE )
  {
    eType = eTYPE;
    tValue = NULL;
    Clone = NULL;
    Destroy = NULL;
  }
  
  TAttribOther ( const TAttribOther& tao )
  {
    Destroy = tao.Destroy;
    Clone = tao.Clone;        
    eType = tao.eType;    
    
    if ( ( tao.tValue != NULL ) && ( Clone != NULL ) )
    {
      tValue = Clone ( tao.tValue );
    }
  }
  
  ~TAttribOther (void)
  {
    if ( ( tValue != NULL ) && ( Destroy != NULL ) )
    {
      Destroy ( tValue );
    }
  }
  
  TAttribOther& operator=(const TAttribOther& tao)
  {
    if ( &tao != this )
    {
      eType = tao.eType;
      
      if ( ( tValue != NULL ) && ( Destroy != NULL ) )	
      {
	Destroy ( tValue );
      }
      
      Clone = tao.Clone;
      Destroy = tao.Destroy;

      if ( ( tao.tValue != NULL ) && ( Clone != NULL ) )
      {
	tValue = Clone ( tao.tValue );
      }
    }
    
    return *this;
  }

  virtual string AttributeName() const { return "other"; }
  TATTRIB_CLONE_NEW_DEF(TAttribOther);

};

template <class T>
T* FX_New(const T& t)
{
  return ::new T(t);
}

template <class T>
void FX_Delete(T* t)
{
  ::delete t;
}


template <class T>
TAttribOther create_other_attribute(const T& t, EAttribType eTYPE)
{
  typedef void* (*Cloner)(const void*);
  typedef void (*Destroyer)(void*);
  
  TAttribOther tao(eTYPE);
  
  T* (*cl)(const T&) = &FX_New<T>;
  void (*de)(T*) = &FX_Delete<T>;

  tao.Destroy = Destroyer(de);
  tao.Clone = Cloner(cl);

  tao.tValue = tao.Clone(&t);

  return tao;
}


#endif  /* _ATTRIBUTE__ */

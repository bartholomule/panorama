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

/*
  A base class (struct) for attribute values.
 */
struct TAttribute
{

  EAttribType   eType;

  virtual ~TAttribute() { }
  virtual string AttributeName() const { return "NONE"; }
  virtual TAttribute* clone_new() const { return new TAttribute(*this); }
  
};  /* struct TAttribute */


struct TAttribReal : public TAttribute
{

  TScalar   tValue;

  TAttribReal (void)
  {
    eType = FX_REAL;
  }

  virtual string AttributeName() const { return "real"; }
  virtual TAttribReal* clone_new() const { return new TAttribReal(*this); }  
  
};  /* struct TAttribReal */


struct TAttribBool : public TAttribute
{

  bool   gValue;
  
  TAttribBool (void)
  {
    eType = FX_BOOL;
  }
  virtual string AttributeName() const { return "bool"; }
  virtual TAttribBool* clone_new() const { return new TAttribBool(*this); }    
  
};  /* struct TAttribBool */


struct TAttribString : public TAttribute
{

  string   tValue;
  
  TAttribString (void)
  {
    eType = FX_STRING;
  }

  virtual string AttributeName() const { return "string"; }
  virtual TAttribString* clone_new() const { return new TAttribString(*this); }
  
};  /* struct TAttribString */


struct TAttribColor : public TAttribute
{

  TColor   tValue;
  
  TAttribColor (void)
  {
    eType = FX_COLOR;
  }
  virtual string AttributeName() const { return "color"; }
  virtual TAttribColor* clone_new() const { return new TAttribColor(*this); }
  
};  /* struct TAttribColor */


struct TAttribVector : public TAttribute
{

  TVector   tValue;
  
  TAttribVector (void)
  {
    eType = FX_VECTOR;
  }
  virtual string AttributeName() const { return "vector"; }
  virtual TAttribVector* clone_new() const { return new TAttribVector(*this); }  
  
};  /* struct TAttribVector */


struct TAttribVector2 : public TAttribute
{

  TVector2   tValue;
  
  TAttribVector2 (void)
  {
    eType = FX_VECTOR2;
  }
  
  virtual string AttributeName() const { return "vector2"; }
  virtual TAttribVector2* clone_new() const { return new TAttribVector2(*this); }  
  
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
      
      Clone = tValue.Clone;
      Destroy = tValue.Destroy;

      if ( ( tao.tValue != NULL ) && ( Clone != NULL ) )
      {
	tValue = Clone ( tao.tValue );
      }
    }
    
    return *this;
  }

  virtual string AttributeName() const { return "other"; }
  virtual TAttribOther* clone_new() const { return new TAttribOther(*this); }  
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

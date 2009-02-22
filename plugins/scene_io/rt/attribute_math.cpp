/*
*  Copyright (C) 2002 Kevin Harris
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
#include "attribute_math.h"

// These are temp, as we need some better form of error reporting.
extern void rt_error (const std::string& rksTEXT);
extern void rt_warning (const std::string& rksTEXT);

magic_pointer<TAttribute> add(const magic_pointer<TAttribute> a1,
			      const magic_pointer<TAttribute> a2)
{
  if( !a1 || !a2 )
  {
    rt_error("add: one of the given values is NULL");
    // BAD, but I don't want to chain errors...
    exit(1);
  }
  
  EAttribType e1 = a1->eType;
  EAttribType e2 = a2->eType;

  if( (e1 == FX_STRING) || (e2 == FX_STRING) )
  {
    magic_pointer<TAttribString> s1 = get_string(a1);
    magic_pointer<TAttribString> s2 = get_string(a2);

    if( !!s1 && !!s2 )
    {
      return (user_arg_type)new TAttribString(s1->tValue + s2->tValue);
    }
    else if( !s1 )
    {
      rt_error("add: cannot convert a " + a1->AttributeName() + " to a std::string");
    }
    else 
    {
      rt_error("add: cannot convert a " + a2->AttributeName() + " to a std::string");
    }    
  }
  else if( (e1 == FX_VECTOR) || (e2 == FX_VECTOR) )
  {
    magic_pointer<TAttribVector> v1 = get_vector(a1);
    magic_pointer<TAttribVector> v2 = get_vector(a2);

    if( !!v1 && !!v2 )
    {
      return (user_arg_type)new TAttribVector(v1->tValue + v2->tValue);
    }
    else if( !v1 )
    {
      rt_error("add: cannot convert a " + a1->AttributeName() + " to a std::vector");
    }
    else 
    {
      rt_error("add: cannot convert a " + a2->AttributeName() + " to a std::vector");
    }    
  }
  else if( (e1 == FX_VECTOR2) || (e2 == FX_VECTOR2) )
  {
    magic_pointer<TAttribVector2> v1 = get_vector2(a1);
    magic_pointer<TAttribVector2> v2 = get_vector2(a2);

    if( !!v1 && !!v2 )
    {
      return (user_arg_type)new TAttribVector2(v1->tValue + v2->tValue);
    }
    else if( !v1 )
    {
      rt_error("add: cannot convert a " + a1->AttributeName() + " to a std::vector2");
    }
    else 
    {
      rt_error("add: cannot convert a " + a2->AttributeName() + " to a std::vector2");
    }    
  }  
  else if( (e1 == FX_REAL) || (e2 == FX_REAL) )
  {
    magic_pointer<TAttribReal> v1 = get_real(a1);
    magic_pointer<TAttribReal> v2 = get_real(a2);

    if( !!v1 && !!v2 )
    {
      return (user_arg_type)new TAttribReal(v1->tValue + v2->tValue);
    }
    else if( !v1 )
    {
      rt_error("add: cannot convert a " + a1->AttributeName() + " to a real");
    }
    else 
    {
      rt_error("add: cannot convert a " + a2->AttributeName() + " to a real");
    }    
  }
  else if( (e1 == FX_INTEGER) || (e2 == FX_INTEGER) )
  {
    magic_pointer<TAttribInt> v1 = get_int(a1);
    magic_pointer<TAttribInt> v2 = get_int(a2);

    if( !!v1 && !!v2 )
    {
      return (user_arg_type)new TAttribInt(v1->tValue + v2->tValue);
    }
    else if( !v1 )
    {
      rt_error("add: cannot convert a " + a1->AttributeName() + " to an integer");
    }
    else 
    {
      rt_error("add: cannot convert a " + a2->AttributeName() + " to an integer");
    }    
  }
  else if( (e1 == FX_ARRAY) || (e2 == FX_ARRAY) )
  {
    magic_pointer<TAttribArray> v1 = get_array(a1);
    magic_pointer<TAttribArray> v2 = get_array(a2);

    if( v1 && v2 )
    {
      if( v1->tValue.size() == v2->tValue.size() )
      {
	std::vector<TScalar> ret_vec(v1->tValue.size());
	for(unsigned i = 0; i < v1->tValue.size(); ++i)
	{
	  ret_vec[i] = v1->tValue[i] + v2->tValue[i];
	}
	return (user_arg_type)new TAttribArray(ret_vec);
      }
      else
      {
	rt_error("add: array sizes do not match");
      }
    }
    else if( !v1 )
    {
      rt_error("add: cannot convert a " + a1->AttributeName() + " to an array");
    }
    else 
    {
      rt_error("add: cannot convert a " + a2->AttributeName() + " to an array");
    }    
  }    
  else
  {
    rt_error("add: cannot add a " + a1->AttributeName() + " and a " + a1->AttributeName());
  }
  return (user_arg_type)new TAttribute();
}


magic_pointer<TAttribute> sub(const magic_pointer<TAttribute> a1,
			      const magic_pointer<TAttribute> a2)
{
  if( !a1 || !a2 )
  {
    rt_error("sub: one of the given values is NULL");
    // BAD, but I don't want to chain errors...
    exit(1);
  }
  
  EAttribType e1 = a1->eType;
  EAttribType e2 = a2->eType;

  if( (e1 == FX_VECTOR) || (e2 == FX_VECTOR) )
  {
    magic_pointer<TAttribVector> v1 = get_vector(a1);
    magic_pointer<TAttribVector> v2 = get_vector(a2);

    if( !!v1 && !!v2 )
    {
      return (user_arg_type)new TAttribVector(v1->tValue - v2->tValue);
    }
    else if( !v1 )
    {
      rt_error("sub: cannot convert a " + a1->AttributeName() + " to a std::vector");
    }
    else 
    {
      rt_error("sub: cannot convert a " + a2->AttributeName() + " to a std::vector");
    }    
  }
  else if( (e1 == FX_VECTOR2) || (e2 == FX_VECTOR2) )
  {
    magic_pointer<TAttribVector2> v1 = get_vector2(a1);
    magic_pointer<TAttribVector2> v2 = get_vector2(a2);

    if( !!v1 && !!v2 )
    {
      return (user_arg_type)new TAttribVector2(v1->tValue - v2->tValue);
    }
    else if( !v1 )
    {
      rt_error("sub: cannot convert a " + a1->AttributeName() + " to a std::vector2");
    }
    else 
    {
      rt_error("sub: cannot convert a " + a2->AttributeName() + " to a std::vector2");
    }    
  }  
  else if( (e1 == FX_REAL) || (e2 == FX_REAL) )
  {
    magic_pointer<TAttribReal> v1 = get_real(a1);
    magic_pointer<TAttribReal> v2 = get_real(a2);

    if( !!v1 && !!v2 )
    {
      return (user_arg_type)new TAttribReal(v1->tValue - v2->tValue);
    }
    else if( !v1 )
    {
      rt_error("sub: cannot convert a " + a1->AttributeName() + " to a real");
    }
    else 
    {
      rt_error("sub: cannot convert a " + a2->AttributeName() + " to a real");
    }    
  }
  else if( (e1 == FX_INTEGER) || (e2 == FX_INTEGER) )
  {
    magic_pointer<TAttribInt> v1 = get_int(a1);
    magic_pointer<TAttribInt> v2 = get_int(a2);

    if( !!v1 && !!v2 )
    {
      return (user_arg_type)new TAttribInt(v1->tValue - v2->tValue);
    }
    else if( !v1 )
    {
      rt_error("sub: cannot convert a " + a1->AttributeName() + " to an integer");
    }
    else 
    {
      rt_error("sub: cannot convert a " + a2->AttributeName() + " to an integer");
    }    
  }
  else if( (e1 == FX_ARRAY) || (e2 == FX_ARRAY) )
  {
    magic_pointer<TAttribArray> v1 = get_array(a1);
    magic_pointer<TAttribArray> v2 = get_array(a2);

    if( v1 && v2 )
    {
      if( v1->tValue.size() == v2->tValue.size() )
      {
	std::vector<TScalar> ret_vec(v1->tValue.size());
	for(unsigned i = 0; i < v1->tValue.size(); ++i)
	{
	  ret_vec[i] = v1->tValue[i] - v2->tValue[i];
	}
	return (user_arg_type)new TAttribArray(ret_vec);
      }
      else
      {
	rt_error("sub: array sizes do not match");
      }
    }
    else if( !v1 )
    {
      rt_error("sub: cannot convert a " + a1->AttributeName() + " to an array");
    }
    else 
    {
      rt_error("sub: cannot convert a " + a2->AttributeName() + " to an array");
    }    
  }  
  else
  {
    rt_error("sub: cannot subtract a " + a1->AttributeName() + " and a " + a1->AttributeName());
  }
  return (user_arg_type)new TAttribute();
}


magic_pointer<TAttribute> mul(const magic_pointer<TAttribute> a1,
			      const magic_pointer<TAttribute> a2)
{
  if( !a1 || !a2 )
  {
    rt_error("mul: one of the given values is NULL");
    // BAD, but I don't want to chain errors...
    exit(1);
  }
  
  EAttribType e1 = a1->eType;
  EAttribType e2 = a2->eType;

  if( e1 == FX_ARRAY )
  {
    magic_pointer<TAttribReal> r = get_real(a2);
    if( r )
    {
      std::vector<TScalar> barf = rcp_static_cast<TAttribArray>(a1)->tValue;
      for(unsigned i = 0; i < barf.size(); ++i)
      {
	barf[i] *= r->tValue;
      }
      return (user_arg_type)new TAttribArray(barf);
    }
  }
  else if( e1 == FX_VECTOR )
  {
    magic_pointer<TAttribReal> r = get_real(a2);
    if( !!r )
    {
      return (user_arg_type)new TAttribVector(get_vector(a1)->tValue * r->tValue);
    }
  }
  else if( e2 == FX_ARRAY )
  {
    magic_pointer<TAttribReal> r = get_real(a1);
    if( r )
    {
      std::vector<TScalar> barf = rcp_static_cast<TAttribArray>(a2)->tValue;
      for(unsigned i = 0; i < barf.size(); ++i)
      {
	barf[i] *= r->tValue;
      }
      return (user_arg_type)new TAttribArray(barf);
    }
  }
  else if( e2 == FX_VECTOR )
  {
    magic_pointer<TAttribReal> r = get_real(a1);
    if( !!r )
    {
      return (user_arg_type)new TAttribVector(get_vector(a2)->tValue * r->tValue);
    }    
  }
  else if( e1 == FX_REAL )
  {
    magic_pointer<TAttribReal> r = get_real(a2);
    if( !!r )
    {
      return (user_arg_type)new TAttribReal(get_real(a1)->tValue * r->tValue);
    }    
  }
  else if( e2 == FX_REAL )
  {
    magic_pointer<TAttribReal> r = get_real(a1);
    if( !!r )
    {
      return (user_arg_type)new TAttribReal(get_real(a2)->tValue * r->tValue);
    }    
  }
  else if( e1 == FX_INTEGER )
  {
    magic_pointer<TAttribInt> i = get_int(a2);
    if( !!i )
    {
      return (user_arg_type)new TAttribInt(get_int(a1)->tValue * i->tValue);
    }    
  }
  else if( e2 == FX_INTEGER )
  {
    magic_pointer<TAttribInt> i = get_int(a1);
    if( !!i )
    {
      return (user_arg_type)new TAttribInt(get_int(a2)->tValue * i->tValue);
    }    
  }  

  rt_error("mul: cannot multiply a " + a1->AttributeName() + " and a " + a2->AttributeName());
  
  return (user_arg_type)new TAttribute();
}

magic_pointer<TAttribute> div(const magic_pointer<TAttribute> a1,
			      const magic_pointer<TAttribute> a2)
{
  static double NEG_INF = log(0.0);
  static double INF = -NEG_INF;
  
  if( !a1 || !a2 )
  {
    rt_error("div: one of the given values is NULL");
    // BAD, but I don't want to chain errors...
    exit(1);
  }
  
  EAttribType e1 = a1->eType;
  EAttribType e2 = a2->eType;

  if( e1 == FX_ARRAY )
  {
    magic_pointer<TAttribReal> r = get_real(a2);
    if( r )
    {
      std::vector<TScalar> barf = rcp_static_cast<TAttribArray>(a1)->tValue;
      for(unsigned i = 0; i < barf.size(); ++i)
      {
	barf[i] /= r->tValue;
      }
      return (user_arg_type)new TAttribArray(barf);
    }
  }
  else if( e1 == FX_VECTOR )
  {
    magic_pointer<TAttribReal> r = get_real(a2);
    if( !!r )
    {
      return (user_arg_type)new TAttribVector(get_vector(a1)->tValue / r->tValue);
    }
  }
  else if( e1 == FX_REAL )
  {
    magic_pointer<TAttribReal> r = get_real(a2);
    if( !!r )
    {
      return (user_arg_type)new TAttribReal(get_real(a1)->tValue / r->tValue);
    }    
  }
  else if( e2 == FX_REAL )
  {
    magic_pointer<TAttribReal> r = get_real(a1);
    if( !!r )
    {
      return (user_arg_type)new TAttribReal(r->tValue / get_real(a2)->tValue);
    }    
  }
  else if( e1 == FX_INTEGER )
  {
    magic_pointer<TAttribInt> i = get_int(a2);
    if( !!i )
    {
      int i1 = get_int(a1)->tValue;
      int i2 = i->tValue;

      // Handle integer division by 0.
      if( i2 == 0 )
      {
	// Purposely create an infinite number (with the correct sign).
	if( i1 > 0 )
	{
	  return (user_arg_type)new TAttribReal(INF);
	}
	else
	{
	  return (user_arg_type)new TAttribReal(NEG_INF);
	}
	//	return (user_arg_type)new TAttribReal(copysign(log(double(0)),i1));
      }
      
      if( i1 % i2 == 0 )
      {
	return (user_arg_type)new TAttribInt(i1 / i2);
      }
      else
      {
	return (user_arg_type)new TAttribReal(i1 / double(i2));
      }
    }    
  }
  else if( e2 == FX_INTEGER )
  {
    magic_pointer<TAttribInt> i = get_int(a1);
    if( !!i )
    {
      int i1 = i->tValue;
      int i2 = get_int(a2)->tValue;

      // Handle integer division by 0.
      if( i2 == 0 )
      {
	// Purposely create an infinite number (with the correct sign).
	if( i1 > 0 )
	{
	  return (user_arg_type)new TAttribReal(INF);
	}
	else
	{
	  return (user_arg_type)new TAttribReal(NEG_INF);
	}
	//	return (user_arg_type)new TAttribReal(copysign(log(double(0)),i1));
      }
      if( i1 % i2 == 0 )
      {
	return (user_arg_type)new TAttribInt(i1 / i2);
      }
      else
      {
	return (user_arg_type)new TAttribReal(i1 / double(i2));
      }
    }    
  }

  rt_error("div: cannot divide a " + a1->AttributeName() + " and a " + a2->AttributeName());
  
  return (user_arg_type)new TAttribute();
}

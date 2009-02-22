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

#if !defined(PANORAMA_EXTENDED_USER_FUNCTIONS_H)
#define PANORAMA_EXTENDED_USER_FUNCTIONS_H

// extended_user_functions.h -- A continuation of the classes in
// user_functions.h (it is included by user_functions.h), in an attempt to make
// the file shorter and more manageable.  This file has classes for functions
// with two arguments.
//
// See the notes there.

namespace panorama
{
  // A useable user function, 2 arguments.
  template <class fn_arg_type1, class fn_arg_type2, class ret_type>
  class user_function_2: public user_function
  {
  public:
    typedef ret_type (*function_type)(fn_arg_type1,fn_arg_type2);
    typedef user_function_2<fn_arg_type1,fn_arg_type2,ret_type> self_type;

    user_function_2(function_type fn): user_function() { sig = fn; }
    virtual ~user_function_2() { }

    virtual self_type* clone_new() const { return new self_type(*this); }
    virtual AttributeArray required_args() const
    {
      AttributeArray vec;
      vec.push_back(get_attrib<fn_arg_type1>());
      vec.push_back(get_attrib<fn_arg_type2>());
      return vec;
    }
    virtual Attribute return_type() const { return get_attrib<ret_type>(); }

    virtual Attribute call(const AttributeArray& args)
    {
      if(args.size() != 2)
      {
        THROW(InvalidArgumentException, "Incorrect number of arguments (should be 2)");
      }
      // Perform type checking...
      AttributeArray fn_args = required_args();
      if( types_match(fn_args, args) )
      {
        return Attribute(sig(
            args[0].convertTo<fn_arg_type1>(),
            args[1].convertTo<fn_arg_type2>()));
      }
      else
      {
        THROW(InvalidArgumentException, "Types did not match.");
      }
    }

    function_type sig;
  };

  // A useable user function (void return), 2 arguments.
  template <class fn_arg_type1, class fn_arg_type2>
  class void_user_function_2: public user_function
  {
  public:
    typedef void (*function_type)(fn_arg_type1, fn_arg_type2);
    typedef void_user_function_2<fn_arg_type1,fn_arg_type2> self_type;

    void_user_function_2(function_type fn): user_function(), sig(fn) { }
    virtual ~void_user_function_2() { }

    virtual self_type* clone_new() const { return new self_type(*this); }
    virtual AttributeArray required_args() const
    {
      AttributeArray vec;
      vec.push_back(get_attrib<fn_arg_type1>());
      vec.push_back(get_attrib<fn_arg_type2>());
      return vec;
    }
    virtual Attribute return_type() const { return get_attrib<void>(); }

    virtual Attribute call(const AttributeArray& args)
    {
      if(args.size() != 2)
      {
        THROW(InvalidArgumentException, "Incorrect number of arguments (should be 2)");
      }
      // Perform type checking...
      AttributeArray fn_args = required_args();
      if( types_match(fn_args, args) )
      {
        sig(args[0].convertTo<fn_arg_type1>(), args[1].convertTo<fn_arg_type2>());
        return Attribute();
      }
      else
      {
        THROW(InvalidArgumentException, "Types did not match.");
      }
    }

    function_type sig;
  };

  // A useable user member function, 2 arguments.
  template <class class_type, class fn_arg_type1, class fn_arg_type2, class ret_type>
  class user_member_function_2: public user_function
  {
  public:
    typedef ret_type (class_type::*function_type)(fn_arg_type1,fn_arg_type2);
    typedef user_member_function_2<class_type,fn_arg_type1,fn_arg_type2,ret_type> self_type;

    user_member_function_2(class_type* ptr, function_type fn):
      user_function(),
      sig(fn),
      instance_ptr(ptr)
    {
    }
    virtual ~user_member_function_2() { }

    virtual self_type* clone_new() const { return new self_type(*this); }
    virtual AttributeArray required_args() const
    {
      AttributeArray vec;
      vec.push_back(get_attrib<fn_arg_type1>());
      vec.push_back(get_attrib<fn_arg_type2>());
      return vec;
    }
    virtual Attribute return_type() const { return get_attrib<ret_type>(); }

    virtual Attribute call(const AttributeArray& args)
    {
      if(args.size() != 2)
      {
        THROW(InvalidArgumentException, "Incorrect number of arguments (should be 2)");
      }
      // Perform type checking...
      AttributeArray fn_args = required_args();
      if( types_match(fn_args, args) )
      {
        return Attribute((instance_ptr->*sig)(
            args[0].get<fn_arg_type1>(),
            args[1].get<fn_arg_type2>()));
      }
      else
      {
        THROW(InvalidArgumentException, "Types did not match.");
      }
    }

    function_type sig;
    class_type* instance_ptr;
  };


  // A useable user member function (void return), 2 arguments.
  template <class class_type, class fn_arg_type1, class fn_arg_type2>
  class void_user_member_function_2: public user_function
  {
  public:
    typedef void (class_type::*function_type)(fn_arg_type1,fn_arg_type2);
    typedef void_user_member_function_2<class_type,fn_arg_type1,fn_arg_type2> self_type;

    void_user_member_function_2(class_type* ptr, function_type fn):
      user_function(),
      sig(fn),
      instance_ptr(ptr)
    {
    }
    virtual ~void_user_member_function_2() { }

    virtual self_type* clone_new() const { return new self_type(*this); }
    virtual AttributeArray required_args() const
    {
      AttributeArray vec;
      vec.push_back(get_attrib<fn_arg_type1>());
      vec.push_back(get_attrib<fn_arg_type2>());
      return vec;
    }
    virtual Attribute return_type() const { return get_attrib<void>(); }

    virtual Attribute call(const AttributeArray& args)
    {
      if(args.size() != 2)
      {
        THROW(InvalidArgumentException, "Incorrect number of arguments (should be 2)");
      }
      // Perform type checking...
      AttributeArray fn_args = required_args();
      if( types_match(fn_args, args) )
      {
        (instance_ptr->*sig)(
          args[0].convertTo<fn_arg_type1>(),
          args[1].convertTo<fn_arg_type2>());
        return Attribute();
      }
      else
      {
        THROW(InvalidArgumentException, "Types did not match.");
      }
    }

    function_type sig;
    class_type* instance_ptr;
  };



  // Member, 2 args
  template <class class_type, class ret_type, class arg_type1, class arg_type2>
  inline rc_pointer<user_function>
  create_user_function(class_type* t, ret_type (class_type::*f)(arg_type1,arg_type2))
  {
    return (rc_pointer<user_function>)new user_member_function_2<class_type,arg_type1,arg_type2,ret_type>(t,f);
  }

  // const Member, 2 args
  template <class class_type, class ret_type, class arg_type1, class arg_type2>
  inline rc_pointer<user_function>
  create_user_function(const class_type* t,
    ret_type (class_type::*f)(arg_type1,arg_type2) const)
  {
    typedef ret_type (class_type::*function_type)(arg_type1,arg_type2);
    typedef user_member_function_2<class_type,arg_type1,arg_type2,ret_type> classtype;

    return (rc_pointer<user_function>)new classtype(const_cast<class_type*>(t),(function_type)f);
  }

  // void Member, 2 args
  template <class class_type, class arg_type1, class arg_type2>
  inline rc_pointer<user_function>
  create_user_function(class_type* t, void (class_type::*f)(arg_type1,arg_type2))
  {
    return rc_pointer<user_function>(new void_user_member_function_2<class_type,arg_type1,arg_type2>(t,f));
  }

  // void const Member, 2 args
  template <class class_type, class arg_type1, class arg_type2>
  inline
  rc_pointer<user_function>
  create_user_function(const class_type* t,
    void (class_type::*f)(arg_type1,arg_type2) const)
  {
    typedef void (class_type::*function_type)(arg_type1,arg_type2);
    typedef void_user_member_function_2<class_type,arg_type1,arg_type2> classtype;

    return (rc_pointer<user_function>)new classtype(const_cast<class_type*>(t),(function_type)f);
  }
  // Non-member, 2 args
  template <class ret_type, class arg_type1, class arg_type2>
  inline rc_pointer<user_function>
  create_user_function(ret_type (*f)(arg_type1, arg_type2))
  {
    return (rc_pointer<user_function>)new user_function_2<arg_type1,arg_type2,ret_type>(f);
  }

  // void Non-member, 2 args
  template <class arg_type1, class arg_type2>
  inline rc_pointer<user_function> create_user_function(void (*f)(arg_type1, arg_type2))
  {
    return (rc_pointer<user_function>)new void_user_function_2<arg_type1,arg_type2>(f);
  }

} // end namespace panorama


#endif /* !defined(PANORAMA_EXTENDED_USER_FUNCTIONS_H) */

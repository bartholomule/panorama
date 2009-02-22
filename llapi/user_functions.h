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
#if       !defined(USER_FUNCTIONS_H)
#define            USER_FUNCTIONS_H

#include "llapi/type_functions.h"
#include "llapi/exception.hpp"

// user_functions.h -- A set of classes/functions which allow the creation of
// functions which can be called to provide an easy interface for use in
// created languages.
//
// Notes:
// 1. NEVER USE NON-CONST REFERENCES FOR ARGUMENTS!!!  Instead, return the
//    values as magic_pointers, or such.
// 2. Be VERY careful when using your own types, making sure to create
//    specialized versions of the functions "attrib_to_type", "type_to_attrib",
//    and "get_attrib" for the type, and a const reference to the type.
//
//    For the const reference specialization, if the conversion cannot be done,
//    do NOT return a bad reference, instead, bail (ie. exit(1)).  An exception
//    would be a better method, but exceptions are currently disabled for
//    panorama (I would like to re-enable them, if they don't cause much
//    runtime overhead).  I hope there is some way to easily overcome this
//    (without much more overhead).  If you can think of one, PLEASE FIX THIS!
// 3. There is quite a bit of trash in here that I do not like.  I wrote
//    seperate classes for member/non-member functions that have a void return.
//    The reason for this, is that I could not find a way to allow generic
//    implementation for type conversion (although it should not be used), and
//    have void returns as well (cannot create an instance of void, or pass
//    void to another function as void() ).
//
// Here's an example of use
/*
  class foo
  {
  public:
  int do_something() { return 0xBADF00D; }
  typedef map<std::string,magic_pointer<user_function> > fn_map_type;

  fn_map_type get_user_functions()
  {
  fn_map_type fns;

  fns["do_something"] = create_user_function(this,&foo::do_something);

  return fns;
  }
  };

  int main()
  {
  foo f;
  foo::fn_type_map fns = foo.get_user_functions();
  user_arg_vector empty_args;
  int i = attrib_to_type<int>(fns["do_something"]->call(empty_args));
  GOM.debug() << "0x" << hex << i << std::endl;
  }
*/

namespace panorama
{
  DECLARE_EXCEPTION(InvalidArgumentException);

  // Check the length of the given args and throw an InvalidArgumentException
  // if they do not match.
  void checkParameterLength(const AttributeArray& args, size_t required);
  void checkTypesMatch(const AttributeArray& required, const AttributeArray& supplied);

  template <class A>
  Attribute makeAttribType()
  {
    return Attribute(AttributeValueType<A>::type);
  }

  template <class A>
  AttributeArray makeAttribTypeArray()
  {
    return AttributeArray(1, makeAttribType<A>());
  }

  template <class A>
  AttributeArray makeAttribArray(const A& a)
  {
    return AttributeArray(1, Attribute(a));
  }

  template <typename A, typename B>
  AttributeArray makeAttribTypeArray()
  {
    AttributeArray retval(2);
    retval[0] = makeAttribType<A>();
    retval[1] = makeAttribType<B>();
    return retval;
  }

  template <typename A, typename B>
  AttributeArray makeAttribArray(const A& a, const B& b)
  {
    AttributeArray retval(2);
    retval[0] = Attribute(a);
    retval[1] = Attribute(b);
    return retval;
  }

  // Base class for user functions...
  class user_function
  {
  public:
    user_function() { }
    virtual ~user_function() { }
    virtual AttributeArray required_args() const = 0;
    virtual user_function* clone_new() const = 0;
    virtual Attribute return_type() const = 0;
    virtual Attribute call(const AttributeArray& args)
    {
      return Attribute();
    }
  };


  // A useable user function, 0 arguments.
  template <class ret_type>
  class user_function_0: public user_function
  {
  public:
    typedef ret_type (*function_type)();
    typedef user_function_0<ret_type> self_type;

    user_function_0(function_type fn): user_function(), sig(fn) { }
    virtual ~user_function_0() { }

    virtual self_type* clone_new() const { return new self_type(*this); }
    virtual AttributeArray required_args() const { return AttributeArray(); }
    virtual Attribute return_type() const { return makeAttribType<ret_type>(); }
    virtual Attribute call(const AttributeArray& args)
    {
      checkTypesMatch(required_args(), args);
      return Attribute(sig());
    }
    Attribute operator()() { return call(AttributeArray()); }

    function_type sig;
  };

  // A useable user function (void return), 0 arguments.
  class void_user_function_0: public user_function
  {
  public:
    typedef void (*function_type)();
    typedef void_user_function_0 self_type;

    void_user_function_0(function_type fn): user_function(), sig(fn) { }
    virtual ~void_user_function_0() { }

    virtual self_type* clone_new() const { return new self_type(*this); }
    virtual AttributeArray required_args() const { return AttributeArray(); }
    virtual Attribute return_type() const { return makeAttribType<void>(); }
    virtual Attribute call(const AttributeArray& args)
    {
      checkTypesMatch(required_args(), args);
      sig();
      return Attribute();
    }
    Attribute operator()() { return call(AttributeArray()); }

    function_type sig;
  };

  // A useable user member function, 0 arguments.
  template <class class_type, class ret_type>
  class user_member_function_0: public user_function
  {
  public:
    typedef ret_type (class_type::*function_type)();
    typedef user_member_function_0<class_type,ret_type> self_type;

    user_member_function_0(class_type* ptr, function_type fn):
      user_function(),
      sig(fn),
      instance_ptr(ptr)
    {
    }

    virtual ~user_member_function_0() { }

    virtual self_type* clone_new() const { return new self_type(*this); }
    virtual AttributeArray required_args() const { return AttributeArray(); }
    virtual Attribute return_type() const { return makeAttribType<ret_type>(); }
    virtual Attribute call(const AttributeArray& args)
    {
      checkTypesMatch(required_args(), args);
      return Attribute((instance_ptr->*sig)());
    }
    Attribute operator()() { return call(AttributeArray()); }

    function_type sig;
    class_type* instance_ptr;
  };

  // A useable user member function (void return), 0 arguments.
  template <class class_type>
  class void_user_member_function_0: public user_function
  {
  public:
    typedef void (class_type::*function_type)();
    typedef void_user_member_function_0<class_type> self_type;

    void_user_member_function_0(class_type* ptr, function_type fn):
      user_function(),
      sig(fn),
      instance_ptr(ptr)
    {
    }

    virtual ~void_user_member_function_0() { }

    virtual self_type* clone_new() const { return new self_type(*this); }
    virtual AttributeArray required_args() const { return AttributeArray(); }
    virtual Attribute return_type() const { return makeAttribType<void>(); }
    virtual Attribute call(const AttributeArray& args)
    {
      checkTypesMatch(required_args(), args);
      (instance_ptr->*sig)();
      return Attribute();
    }
    Attribute operator()() { return call(AttributeArray()); }

    function_type sig;
    class_type* instance_ptr;
  };


  // A useable user function, 1 argument.
  template <class fn_arg_type, class ret_type>
  class user_function_1: public user_function
  {
  public:
    typedef ret_type (*function_type)(fn_arg_type);
    typedef user_function_1<fn_arg_type,ret_type> self_type;

    user_function_1(function_type fn): user_function() { sig = fn; }
    virtual ~user_function_1() { }

    virtual self_type* clone_new() const { return new self_type(*this); }
    virtual AttributeArray required_args() const { return makeAttribTypeArray<fn_arg_type>(); }
    virtual Attribute return_type() const { return makeAttribType<ret_type>(); }

    virtual Attribute call(const AttributeArray& args)
    {
      checkTypesMatch(required_args(), args);
      return Attribute(sig(args[0].convertTo<fn_arg_type>()));
    }

    Attribute operator()(fn_arg_type a) { return call(makeAttribArray(a)); }
    function_type sig;
  };

  // A useable user function (void return), 1 argument.
  template <class fn_arg_type>
  class void_user_function_1: public user_function
  {
  public:
    typedef void (*function_type)(fn_arg_type);
    typedef void_user_function_1<fn_arg_type> self_type;

    void_user_function_1(function_type fn): user_function(), sig(fn) { }
    virtual ~void_user_function_1() { }

    virtual self_type* clone_new() const { return new self_type(*this); }
    virtual AttributeArray required_args() const { return makeAttribTypeArray<fn_arg_type>(); }
    virtual Attribute return_type() const { return makeAttribType<void>(); }

    virtual Attribute call(const AttributeArray& args)
    {
      checkTypesMatch(required_args(), args);
      sig(args[0].convertTo<fn_arg_type>());
      return Attribute();
    }

    Attribute operator()(fn_arg_type a) { return call(makeAttribArray(a)); }
    function_type sig;
  };

  // A useable user member function, 1 argument.
  template <class class_type, class fn_arg_type, class ret_type>
  class user_member_function_1: public user_function
  {
  public:
    typedef ret_type (class_type::*function_type)(fn_arg_type);
    typedef user_member_function_1<class_type,fn_arg_type,ret_type> self_type;

    user_member_function_1(class_type* ptr, function_type fn):
      user_function(),
      sig(fn),
      instance_ptr(ptr)
    {
    }
    virtual ~user_member_function_1() { }

    virtual self_type* clone_new() const { return new self_type(*this); }
    virtual AttributeArray required_args() const { return makeAttribTypeArray<fn_arg_type>(); }
    virtual Attribute return_type() const { return makeAttribType<ret_type>(); }

    virtual Attribute call(const AttributeArray& args)
    {
      checkTypesMatch(required_args(), args);
      return Attribute((instance_ptr->*sig)(args[0].convertTo<fn_arg_type>(args[0])));
    }

    Attribute operator()(fn_arg_type a) { return call(makeAttribArray(a)); }
    function_type sig;
    class_type* instance_ptr;
  };


  // A useable user member function (void return), 1 argument.
  template <class class_type, class fn_arg_type>
  class void_user_member_function_1: public user_function
  {
  public:
    typedef void (class_type::*function_type)(fn_arg_type);
    typedef void_user_member_function_1<class_type,fn_arg_type> self_type;

    void_user_member_function_1(class_type* ptr, function_type fn):
      user_function(),
      sig(fn),
      instance_ptr(ptr)
    {
    }
    virtual ~void_user_member_function_1() { }

    virtual self_type* clone_new() const { return new self_type(*this); }
    virtual AttributeArray required_args() const
    {
      return makeAttribTypeArray<fn_arg_type>();
    }
    virtual Attribute return_type() const { return makeAttribType<void>(); }

    virtual Attribute call(const AttributeArray& args)
    {
      checkTypesMatch(required_args(), args);
      (instance_ptr->*sig)(args[0].convertTo<fn_arg_type>());
      return Attribute();
    }

    Attribute operator()(fn_arg_type a) { return call(makeAttribArray(a)); }
    function_type sig;
    class_type* instance_ptr;
  };

  //---------------------------------------------------------------------------
  // A set of functions to generate the correct user function from the arguments
  // (simple).
  //---------------------------------------------------------------------------

  // Member function, 0 args...
  template <class class_type, class ret_type>
  inline
  rc_pointer<user_function> create_user_function(class_type* t,
    ret_type (class_type::*f)())
  {
    return rc_pointer<user_function>(new user_member_function_0<class_type,ret_type>(t,f));
  }

  // const Member function, 0 args...
  template <class class_type, class ret_type>
  inline
  rc_pointer<user_function> create_user_function(const class_type* t,
    ret_type (class_type::*f)() const)
  {
    return rc_pointer<user_function>(new user_member_function_0<class_type,ret_type>(const_cast<class_type*>(t),
        (ret_type (class_type::*)())f));
  }
  // void Member function, 0 args...
  template <class class_type>
  inline
  rc_pointer<user_function> create_user_function(class_type* t,
    void (class_type::*f)())
  {
    return rc_pointer<user_function>(new void_user_member_function_0<class_type>(t,f));
  }

  // void const Member function, 0 args...
  template <class class_type>
  inline
  rc_pointer<user_function> create_user_function(const class_type* t,
    void (class_type::*f)() const)
  {
    return rc_pointer<user_function>(new void_user_member_function_0<class_type>(const_cast<class_type*>(t),
        (void (class_type::*)())f));
  }

  // Member, 1 arg (not pointer, non-const-ref, etc)
  template <class class_type, class ret_type, class arg_type>
  inline
  rc_pointer<user_function>
  create_user_function(class_type* t, ret_type (class_type::*f)(arg_type))
  {
    return rc_pointer<user_function>(new user_member_function_1<class_type,arg_type,ret_type>(t,f));
  }

  // const Member, 1 arg (not pointer, non-const-ref, etc)
  template <class class_type, class ret_type, class arg_type>
  inline
  rc_pointer<user_function>
  create_user_function(const class_type* t,
    ret_type (class_type::*f)(arg_type) const)
  {
    typedef ret_type (class_type::*function_type)(arg_type);

    return rc_pointer<user_function>(new user_member_function_1<class_type,arg_type,ret_type>(const_cast<class_type*>(t),
        (function_type)f));
  }

  // void Member, 1 arg (not pointer, non-const-ref, etc)
  template <class class_type, class arg_type>
  inline
  rc_pointer<user_function>
  create_user_function(class_type* t, void (class_type::*f)(arg_type))
  {
    return rc_pointer<user_function>(new void_user_member_function_1<class_type,arg_type>(t,f));
  }

  // void const Member, 1 arg (not pointer, non-const-ref, etc)
  template <class class_type, class arg_type>
  inline
  rc_pointer<user_function>
  create_user_function(const class_type* t,
    void (class_type::*f)(arg_type) const)
  {
    typedef void (class_type::*function_type)(arg_type);

    return rc_pointer<user_function>(new void_user_member_function_1<class_type,arg_type>(const_cast<class_type*>(t),
        (function_type)f));
  }

  // Non-member, 0 args
  template <class ret_type>
  inline
  rc_pointer<user_function> create_user_function(ret_type (*f)())
  {
    return rc_pointer<user_function>(new user_function_0<ret_type>(f));
  }

  // Non-member, 1 arg
  template <class ret_type, class arg_type>
  inline rc_pointer<user_function> create_user_function(ret_type (*f)(arg_type))
  {
    return rc_pointer<user_function>(new user_function_1<arg_type,ret_type>(f));
  }

  // void Non-member, 0 args
  static inline rc_pointer<user_function> create_user_function(void (*f)())
  {
    return rc_pointer<user_function>(new void_user_function_0(f));
  }


  // void Non-member, 1 arg
  template <class arg_type>
  inline rc_pointer<user_function> create_user_function(void (*f)(arg_type))
  {
    return rc_pointer<user_function>(new void_user_function_1<arg_type>(f));
  }

} // end namespace panorama

// functions with 2 arguments [ void/non-void [member [const/non], global ] ]
#include "llapi/extended_user_functions.h"

#endif /* !defined(USER_FUNCTIONS_H) */

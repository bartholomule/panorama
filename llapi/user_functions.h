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
  typedef map<string,magic_pointer<user_function> > fn_map_type;

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
  cout << "0x" << hex << i << endl;
}
*/


// Typedefs to make your typing shorter and less error-prone.
typedef magic_pointer<TAttribute> user_arg_type;
typedef vector<user_arg_type> user_arg_vector;

// Base class for user functions...
class user_function
{
public:
  user_function() { }
  virtual ~user_function() { }
  virtual vector<user_arg_type> required_args() const = 0;
  virtual user_function* clone_new() const = 0;
  virtual user_arg_type return_type() const = 0;
  virtual user_arg_type call(const user_arg_vector& args)
  {
    return user_arg_type(new TAttribute());    
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

  virtual self_type* clone_new() const         { return new self_type(*this); }
  virtual user_arg_vector required_args() const { return user_arg_vector(); }
  virtual user_arg_type return_type() const { return get_attrib<ret_type>(); }
  virtual user_arg_type call(const user_arg_vector& args)
  {
    if(args.size() > 0)
    {
      // [REPORT ERROR HERE]
      cerr << "Incorrect number of arguments (should be 0)" << endl;      
      return user_arg_type(new TAttribute());
    }
    return type_to_attrib(sig());    
  }
  user_arg_type operator()() { return call(user_arg_vector()); }

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

  virtual self_type* clone_new() const         { return new self_type(*this); }
  virtual user_arg_vector required_args() const { return user_arg_vector(); }
  virtual user_arg_type return_type() const { return type_to_attrib(); }
  virtual user_arg_type call(const user_arg_vector& args)
  {
    if(args.size() > 0)
    {
      // [REPORT ERROR HERE]
      cerr << "Incorrect number of arguments (should be 0)" << endl;      
      return user_arg_type(new TAttribute());
    }
    sig();
    return user_arg_type(new TAttribute);
  }
  user_arg_type operator()() { return call(user_arg_vector()); }

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
  virtual user_arg_vector required_args() const { return user_arg_vector(); }
  virtual user_arg_type return_type() const { return get_attrib<ret_type>(); }
  virtual user_arg_type call(const user_arg_vector& args)
  {
    if(args.size() > 0)
    {
      // [REPORT ERROR HERE]
      cerr << "Incorrect number of arguments (should be 0)" << endl;      
      return user_arg_type(new TAttribute());
    }
    return type_to_attrib((instance_ptr->*sig)());    
  }
  user_arg_type operator()() { return call(user_arg_vector()); }

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
  virtual user_arg_vector required_args() const { return user_arg_vector(); }
  virtual user_arg_type return_type() const { return get_attrib<void>(); }
  virtual user_arg_type call(const user_arg_vector& args)
  {
    if(args.size() > 0)
    {
      // [REPORT ERROR HERE]
      cerr << "Incorrect number of arguments (should be 0)" << endl;      
      return user_arg_type(new TAttribute());
    }
    (instance_ptr->*sig)();        
    return user_arg_type(new TAttribute());
  }
  user_arg_type operator()() { return call(user_arg_vector()); }

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
  virtual user_arg_vector required_args() const
  {
    return user_arg_vector(1,get_attrib<fn_arg_type>());
  }
  virtual user_arg_type return_type() const { return get_attrib<ret_type>(); }

  virtual user_arg_type call(const user_arg_vector& args)
  { 
    //    cout << __PRETTY_FUNCTION__ << endl;
    if(args.size() != 1)
    {
      // [REPORT ERROR HERE]
      cerr << "Incorrect number of arguments (should be 1)" << endl;
      return user_arg_type(new TAttribute());
    }
    // Perform type checking...
    user_arg_vector fn_args = required_args();
    if( types_match(fn_args[0], args[0]) )
    {
      //      cout << "Calling for reals now..." << endl;
      magic_pointer<TAttribute> c;
      return type_to_attrib(sig(attrib_to_type<fn_arg_type>(args[0],c)));
    }
    else
    {
      // [REPORT ERROR HERE]
      cerr << "Types did not match." << endl;
      return user_arg_type(new TAttribute());
    }
  }
  
  user_arg_type operator()(fn_arg_type a)
  {
    user_arg_vector args(1,a);
    return call(args);
  }
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
  virtual user_arg_vector required_args() const
  {
    return user_arg_vector(1,get_attrib<fn_arg_type>());
  }
  virtual user_arg_type return_type() const { return get_attrib<void>(); }

  virtual user_arg_type call(const user_arg_vector& args)
  { 
    //    cout << __PRETTY_FUNCTION__ << endl;
    if(args.size() != 1)
    {
      // [REPORT ERROR HERE]
      cerr << "Incorrect number of arguments (should be 1)" << endl;
      return user_arg_type(new TAttribute());
    }
    // Perform type checking...
    user_arg_vector fn_args = required_args();
    if( types_match(fn_args[0], args[0]) )
    {
      //      cout << "Calling for reals now..." << endl;
      magic_pointer<TAttribute> c;      
      sig(attrib_to_type<fn_arg_type>(args[0],c));
      return user_arg_type(new TAttribute());
    }
    else
    {
      // [REPORT ERROR HERE]
      cerr << "Types did not match." << endl;
      return user_arg_type(new TAttribute());
    }
  }
  
  user_arg_type operator()(fn_arg_type a)
  {
    user_arg_vector args(1,a);
    return call(args);
  }
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
  virtual user_arg_vector required_args() const
  {
    return user_arg_vector(1, get_attrib<fn_arg_type>());
  }
  virtual user_arg_type return_type() const { return get_attrib<ret_type>(); }

  virtual user_arg_type call(const user_arg_vector& args)
  {
    if(args.size() != 1)
    {
      // [REPORT ERROR HERE]
      cerr << "Incorrect number of arguments (should be 1)" << endl;      
      return user_arg_type(new TAttribute());
    }
    // Perform type checking...
    user_arg_vector fn_args = required_args();
    if( types_match(fn_args[0], args[0]) )
    {
      //      cout << "Calling for reals now..." << endl;
      magic_pointer<TAttribute> c;      
      return type_to_attrib<ret_type>((instance_ptr->*sig)(attrib_to_type<fn_arg_type>(args[0],c)));
    }
    else
    {
      // [REPORT ERROR HERE]
      cerr << "Types did not match." << endl;      
      return user_arg_type(new TAttribute());
    }
  }  
  
  user_arg_type operator()(fn_arg_type a)
  {
    user_arg_vector args(1,a);
    return call(args);
  }
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
  virtual user_arg_vector required_args() const
  {
    return user_arg_vector(1, get_attrib<fn_arg_type>());
  }
  virtual user_arg_type return_type() const { return get_attrib<void>(); }

  virtual user_arg_type call(const user_arg_vector& args)
  {
    if(args.size() != 1)
    {
      // [REPORT ERROR HERE]
      cerr << "Incorrect number of arguments (should be 1)" << endl;      
      return user_arg_type(new TAttribute());
    }
    // Perform type checking...
    user_arg_vector fn_args = required_args();
    if( types_match(fn_args[0], args[0]) )
    {
      //      cout << "Calling for reals now..." << endl;
      magic_pointer<TAttribute> c;      
      (instance_ptr->*sig)(attrib_to_type<fn_arg_type>(args[0],c));      
      return user_arg_type(new TAttribute());
    }
    else
    {
      // [REPORT ERROR HERE]
      cerr << "Types did not match." << endl;      
      return user_arg_type(new TAttribute());
    }
  }  
  
  user_arg_type operator()(fn_arg_type a)
  {
    user_arg_vector args(1,a);
    return call(args);
  }
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
magic_pointer<user_function> create_user_function(class_type* t,
						  ret_type (class_type::*f)())
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return magic_pointer<user_function>(new user_member_function_0<class_type,ret_type>(t,f));
}

// const Member function, 0 args...
template <class class_type, class ret_type>
inline
magic_pointer<user_function> create_user_function(const class_type* t,
						  ret_type (class_type::*f)() const)
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return magic_pointer<user_function>(new user_member_function_0<class_type,ret_type>(const_cast<class_type*>(t),
							 (ret_type (class_type::*)())f));
}
// void Member function, 0 args...
template <class class_type>
inline
magic_pointer<user_function> create_user_function(class_type* t,
						  void (class_type::*f)())
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return magic_pointer<user_function>(new void_user_member_function_0<class_type>(t,f));
}

// void const Member function, 0 args...
template <class class_type>
inline
magic_pointer<user_function> create_user_function(const class_type* t,
						  void (class_type::*f)() const)
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return magic_pointer<user_function>(new void_user_member_function_0<class_type>(const_cast<class_type*>(t),
										  (void (class_type::*)())f));
}

// Member, 1 arg (not pointer, non-const-ref, etc)
template <class class_type, class ret_type, class arg_type>
inline
magic_pointer<user_function>
create_user_function(class_type* t, ret_type (class_type::*f)(arg_type))
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return magic_pointer<user_function>(new user_member_function_1<class_type,arg_type,ret_type>(t,f));
}

// const Member, 1 arg (not pointer, non-const-ref, etc)
template <class class_type, class ret_type, class arg_type>
inline
magic_pointer<user_function>
create_user_function(const class_type* t,
		     ret_type (class_type::*f)(arg_type) const)
{
  typedef ret_type (class_type::*function_type)(arg_type);

  //  cout << __PRETTY_FUNCTION__ << endl;
  return magic_pointer<user_function>(new user_member_function_1<class_type,arg_type,ret_type>(const_cast<class_type*>(t),
											       (function_type)f));
}

// void Member, 1 arg (not pointer, non-const-ref, etc)
template <class class_type, class arg_type>
inline
magic_pointer<user_function>
create_user_function(class_type* t, void (class_type::*f)(arg_type))
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return magic_pointer<user_function>(new void_user_member_function_1<class_type,arg_type>(t,f));
}

// void const Member, 1 arg (not pointer, non-const-ref, etc)
template <class class_type, class arg_type>
inline
magic_pointer<user_function>
create_user_function(const class_type* t,
		     void (class_type::*f)(arg_type) const)
{
  typedef void (class_type::*function_type)(arg_type);

  //  cout << __PRETTY_FUNCTION__ << endl;
  return magic_pointer<user_function>(new void_user_member_function_1<class_type,arg_type>(const_cast<class_type*>(t),
							      (function_type)f));
}

// Non-member, 0 args
template <class ret_type>
inline
magic_pointer<user_function> create_user_function(ret_type (*f)())
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return magic_pointer<user_function>(new user_function_0<ret_type>(f));
}

// Non-member, 1 arg
template <class ret_type, class arg_type>
inline magic_pointer<user_function> create_user_function(ret_type (*f)(arg_type))
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return magic_pointer<user_function>(new user_function_1<arg_type,ret_type>(f));
}

// void Non-member, 0 args
static inline magic_pointer<user_function> create_user_function(void (*f)())
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return magic_pointer<user_function>(new void_user_function_0(f));
}  


// void Non-member, 1 arg
template <class arg_type>
inline magic_pointer<user_function> create_user_function(void (*f)(arg_type))
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return magic_pointer<user_function>(new void_user_function_1<arg_type>(f));
}

// functions with 2 arguments [ void/non-void [member [const/non], global ] ]
#include "llapi/extended_user_functions.h"

#endif /* !defined(USER_FUNCTIONS_H) */

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

// extended_user_functions.h -- A continuation of the classes in
// user_functions.h (it is included by user_functions.h), in an attempt to make
// the file shorter and more manageable.  This file has classes for functions
// with two arguments.
//
// See the notes there.

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
  virtual user_arg_vector required_args() const
  {
    user_arg_vector vec;
    vec.push_back(get_attrib<fn_arg_type1>());
    vec.push_back(get_attrib<fn_arg_type2>());    
    return vec;
  }
  virtual user_arg_type return_type() const { return get_attrib<ret_type>(); }

  virtual user_arg_type call(const user_arg_vector& args)
  { 
    //    cout << __PRETTY_FUNCTION__ << endl;
    if(args.size() != 2)
    {
      // [REPORT ERROR HERE]
      cerr << "Incorrect number of arguments (should be 2)" << endl;
      return new TAttribute();
    }
    // Perform type checking...
    user_arg_vector fn_args = required_args();
    if( types_match(fn_args[0], args[0]) )
    {
      //      cout << "Calling for reals now..." << endl;
      magic_pointer<TAttribute> c1;
      magic_pointer<TAttribute> c2;      
      return type_to_attrib(sig(attrib_to_type<fn_arg_type1>(args[0],c1),
				attrib_to_type<fn_arg_type2>(args[1],c2)));
    }
    else
    {
      // [REPORT ERROR HERE]
      cerr << "Types did not match." << endl;
      return new TAttribute();
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
  virtual user_arg_vector required_args() const
  {
    user_arg_vector vec;
    vec.push_back(get_attrib<fn_arg_type1>());
    vec.push_back(get_attrib<fn_arg_type2>());    
    return vec;    
  }
  virtual user_arg_type return_type() const { return get_attrib<void>(); }

  virtual user_arg_type call(const user_arg_vector& args)
  { 
    //    cout << __PRETTY_FUNCTION__ << endl;
    if(args.size() != 2)
    {
      // [REPORT ERROR HERE]
      cerr << "Incorrect number of arguments (should be 2)" << endl;
      return new TAttribute();
    }
    // Perform type checking...
    user_arg_vector fn_args = required_args();
    if( types_match(fn_args[0], args[0]) )
    {
      //      cout << "Calling for reals now..." << endl;
      magic_pointer<TAttribute> c1;      
      magic_pointer<TAttribute> c2;
      sig(attrib_to_type<fn_arg_type1>(args[0],c1),
	  attrib_to_type<fn_arg_type2>(args[1],c2));	  
      return new TAttribute();
    }
    else
    {
      // [REPORT ERROR HERE]
      cerr << "Types did not match." << endl;
      return new TAttribute();
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
  virtual user_arg_vector required_args() const
  {
    user_arg_vector vec;
    vec.push_back(get_attrib<fn_arg_type1>());
    vec.push_back(get_attrib<fn_arg_type2>());    
    return vec;    
  }
  virtual user_arg_type return_type() const { return get_attrib<ret_type>(); }

  virtual user_arg_type call(const user_arg_vector& args)
  {
    if(args.size() != 2)
    {
      // [REPORT ERROR HERE]
      cerr << "Incorrect number of arguments (should be 2)" << endl;      
      return new TAttribute();
    }
    // Perform type checking...
    user_arg_vector fn_args = required_args();
    if( types_match(fn_args[0], args[0]) )
    {
      //      cout << "Calling for reals now..." << endl;
      magic_pointer<TAttribute> c1;
      magic_pointer<TAttribute> c2;            
      return type_to_attrib<ret_type>((instance_ptr->*sig)(attrib_to_type<fn_arg_type1>(args[0],c1),
							   attrib_to_type<fn_arg_type2>(args[1],c2)));
    }
    else
    {
      // [REPORT ERROR HERE]
      cerr << "Types did not match." << endl;      
      return new TAttribute();
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
  virtual user_arg_vector required_args() const
  {
    user_arg_vector vec;
    vec.push_back(get_attrib<fn_arg_type1>());
    vec.push_back(get_attrib<fn_arg_type2>());    
    return vec;    
  }
  virtual user_arg_type return_type() const { return get_attrib<void>(); }

  virtual user_arg_type call(const user_arg_vector& args)
  {
    if(args.size() != 2)
    {
      // [REPORT ERROR HERE]
      cerr << "Incorrect number of arguments (should be 2)" << endl;      
      return new TAttribute();
    }
    // Perform type checking...
    user_arg_vector fn_args = required_args();
    if( types_match(fn_args[0], args[0]) )
    {
      //      cout << "Calling for reals now..." << endl;
      magic_pointer<TAttribute> c1;
      magic_pointer<TAttribute> c2;
      (instance_ptr->*sig)(attrib_to_type<fn_arg_type1>(args[0],c1),
			   attrib_to_type<fn_arg_type2>(args[1],c2));      
      return new TAttribute();
    }
    else
    {
      // [REPORT ERROR HERE]
      cerr << "Types did not match." << endl;      
      return new TAttribute();
    }
  }  
  
  function_type sig;
  class_type* instance_ptr;
};



// Member, 2 args 
template <class class_type, class ret_type, class arg_type1, class arg_type2>
inline magic_pointer<user_function>
create_user_function(class_type* t, ret_type (class_type::*f)(arg_type1,arg_type2))
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return new user_member_function_2<class_type,arg_type1,arg_type2,ret_type>(t,f);
}

// const Member, 2 args 
template <class class_type, class ret_type, class arg_type1, class arg_type2>
inline magic_pointer<user_function>
create_user_function(const class_type* t,
		     ret_type (class_type::*f)(arg_type1,arg_type2) const)
{
  typedef ret_type (class_type::*function_type)(arg_type1,arg_type2);
  typedef user_member_function_2<class_type,arg_type1,arg_type2,ret_type> classtype;
  
  //  cout << __PRETTY_FUNCTION__ << endl;
  return new classtype(const_cast<class_type*>(t),(function_type)f);
}

// void Member, 2 args 
template <class class_type, class arg_type1, class arg_type2>
inline magic_pointer<user_function>
create_user_function(class_type* t, void (class_type::*f)(arg_type1,arg_type2))
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return new void_user_member_function_2<class_type,arg_type1,arg_type2>(t,f);
}

// void const Member, 2 args 
template <class class_type, class arg_type1, class arg_type2>
inline
magic_pointer<user_function>
create_user_function(const class_type* t,
		     void (class_type::*f)(arg_type1,arg_type2) const)
{
  typedef void (class_type::*function_type)(arg_type1,arg_type2);
  typedef void_user_member_function_2<class_type,arg_type1,arg_type2> classtype;
  
  //  cout << __PRETTY_FUNCTION__ << endl;
  return new classtype(const_cast<class_type*>(t),(function_type)f);
}
// Non-member, 2 args
template <class ret_type, class arg_type1, class arg_type2>
inline magic_pointer<user_function>
create_user_function(ret_type (*f)(arg_type1, arg_type2))
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return new user_function_2<arg_type1,arg_type2,ret_type>(f);
}

// void Non-member, 2 args
template <class arg_type1, class arg_type2>
inline magic_pointer<user_function> create_user_function(void (*f)(arg_type1, arg_type2))
{
  //  cout << __PRETTY_FUNCTION__ << endl;
  return new void_user_function_2<arg_type1,arg_type2>(f);
}


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

#include "language_functions.h"
#include "rt_io.h"
#include "attrib_tweak.h"

#define GLOBAL_FUNCTIONS (TSceneRT::_global_functions)

//---------------------------------------------------------------------------
typedef TSceneRT::BASE_OBJECT_TYPE BASE_OBJECT_TYPE;
typedef TSceneRT::attrib_type attrib_type;

#define POP()           top(); TSceneRT::_tDataStack.pop()  // Fix to STL's pop()

#define DATA		(TSceneRT::_tDataStack.top())
#define DATAMAP         (TSceneRT::_tDataMap)
#define DATASTACK       (TSceneRT::_tDataStack) 
#define SCENE		(TSceneRT::_ptParsedScene)
#define PARENT_OBJECT   (TSceneRT::_ptParent)
#define WORLD           (TSceneRT::_ptWorld)
extern void rt_error (const string& rksTEXT);
extern void rt_warning (const string& rksTEXT);
//---------------------------------------------------------------------------

static void PrintJunk(magic_pointer<TAttribute> attr)
{
  GOM.out() << attr->toString() << endl;
}

static string env(string s)
{
  char* env_text = getenv(s.c_str());
  if( env_text != NULL )
  {
    return string(env_text);
  }
  else
  {
    rt_error("Environment Variable \"" + s + "\" is not defined");
    return("");
  }
}

static void PrintFunctionList()
{
  TUserFunctionMap all_functions = all_user_functions();

  GOM.out() << "Currently accessable functions are:" << endl;
  for( TUserFunctionMap::iterator i = all_functions.begin();
       i != all_functions.end();
       ++i )
  {
    string function_name = i->first;
    vector<user_arg_type> args = i->second->required_args();

    GOM.out() << "  " << function_name << "(";

    vector<user_arg_type>::iterator i = args.begin();

    if( i != args.end() )
    {
      GOM.out() << (*i)->AttributeName();
      for( ++i;
	   i != args.end();
	   ++i )
      {
	GOM.out() << ", " << (*i)->AttributeName();
      }
    }

    GOM.out() << ")" << endl;
    
  }
}

static void Halt()
{
  GOM.error() << "Terminating due to halt request on line "
       << TSceneRT::_dwLineNumber
       << "."
       << endl;
  exit(1);  
}

static string AttributeType(magic_pointer<TAttribute> attr)
{
  if( !!attr )
  {
    return attr->AttributeName();
  }
  else
  {
    return "undefined";
  }  
}

static string AttributeList(magic_pointer<TAttribute> attr)
{
  magic_pointer<TProcedural> proc = get_procedural_var(attr);
  if( !proc )
  {
    rt_error("type is not procedural (has no attributes)");
    return "NONE";
  }
  else
  {
    string attr_str = "";
    
    attr_str = "( ";
    TAttributeList attr_list;
    proc->getAttributeList(attr_list);
    for(TAttributeList::const_iterator i = attr_list.begin();
	i != attr_list.end();
	++i)
    {
      attr_str += i->first + " ";
    }
    attr_str += ")";
    return attr_str;
  }  
}

static TVector getVector(magic_pointer<TAttribute> atp)
{
  magic_pointer<TAttribVector> vec = get_vector(atp);
  if( !!vec )
  {
    return vec->tValue;
  }
  rt_error("cannot extract vector from " + ((!!atp)?(atp->toString()):("NULL attribute")));
  return TVector();
}

static TColor getColor(magic_pointer<TAttribute> atp)
{
  magic_pointer<TAttribColor> vec = get_color(atp);
  if( !!vec )
  {
    return vec->tValue;
  }
  rt_error("cannot extract color from " + ((!!atp)?(atp->toString()):("NULL attribute")));
  return TColor();
}

static TVector2 getVector2(magic_pointer<TAttribute> atp)
{
  magic_pointer<TAttribVector2> vec = get_vector2(atp);
  if( !!vec )
  {
    return vec->tValue;
  }
  rt_error("cannot extract vector2 from " + ((!!atp)?(atp->toString()):("NULL attribute")));
  return TVector2();
}

static int getInt(magic_pointer<TAttribute> atp)
{
  magic_pointer<TAttribInt> i = get_int(atp);
  if( !!i )
  {
    return i->tValue;
  }
  rt_error("cannot extract int from " + ((!!atp)?(atp->toString()):("NULL attribute")));
  return 0;
}

static bool getBool(magic_pointer<TAttribute> atp)
{
  magic_pointer<TAttribBool> i = get_bool(atp);
  if( !!i )
  {
    return i->tValue;
  }
  rt_error("cannot extract bool from " + ((!!atp)?(atp->toString()):("NULL attribute")));
  return false;
}

static TScalar getScalar(magic_pointer<TAttribute> atp)
{
  magic_pointer<TAttribReal> r = get_real(atp);
  if( !!r )
  {
    return r->tValue;
  }
  rt_error("cannot extract real from " + ((!!atp)?(atp->toString()):("NULL attribute")));
  return TScalar(0);
}

static void evaluate(const string& s)
{
  rt_error("EVAL DOES NOT WORK! DO NOT USE IT!");
  exit(1);
  //  scanner_unput_string(s);
  // This needs work.  It will cause problems if it is used.
}

static void debug(bool b)
{
  if( b )
  {
    GOM.EnableStream("debug");
  }
  else
  {
    GOM.DisableStream("debug");    
  }
}


#include <cmath>

void GlobalInitFunctions (void)
{

  double (*fn)(double);
  double (*fn2)(double,double);
#if defined(MATH_USE_INF_TESTS)  
#if defined(INF_TEST_REQUIRES_THROW)
  int (*fn3)(double) throw();
#else
  int (*fn3)(double);
#endif /* defined(INF_TEST_REQUIRES_THROW) */
#endif /* defined(MATH_USE_INF_TESTS) */

  GLOBAL_FUNCTIONS.clear();

  // Functions for random numbers
  GLOBAL_FUNCTIONS["setRandSeed"] = create_user_function(&SeedRandom);  
  GLOBAL_FUNCTIONS["rand"] = create_user_function(&frand);

  // Functions for language features
  GLOBAL_FUNCTIONS["print"] = create_user_function(&PrintJunk);
  GLOBAL_FUNCTIONS["functionlist"] = create_user_function(&PrintFunctionList);
  GLOBAL_FUNCTIONS["halt"] = create_user_function(&Halt);
  GLOBAL_FUNCTIONS["attributelist"] = create_user_function(&AttributeList);
  GLOBAL_FUNCTIONS["type"] = create_user_function(&AttributeType);
  // EVAL DOES NOT WORK YET!!!
  GLOBAL_FUNCTIONS["eval"] = create_user_function(&evaluate);
  GLOBAL_FUNCTIONS["env"] = create_user_function(&env);
  GLOBAL_FUNCTIONS["debug"] = create_user_function(&debug);  
  
  // Functions for type conversions
  GLOBAL_FUNCTIONS["vector"]  = create_user_function(&getVector);
  GLOBAL_FUNCTIONS["vector2"] = create_user_function(&getVector2);
  GLOBAL_FUNCTIONS["real"]    = create_user_function(&getScalar);
  GLOBAL_FUNCTIONS["int"]     = create_user_function(&getInt);
  GLOBAL_FUNCTIONS["bool"]    = create_user_function(&getBool);  
  GLOBAL_FUNCTIONS["color"]   = create_user_function(&getColor);        

  // Math functions
  // Trig functions
  fn = &std::sin;
  GLOBAL_FUNCTIONS["sin"] = create_user_function(fn);
  fn = &std::cos;
  GLOBAL_FUNCTIONS["cos"] = create_user_function(fn);
  fn = &std::tan;
  GLOBAL_FUNCTIONS["tan"] = create_user_function(fn);
  fn = &std::asin;
  GLOBAL_FUNCTIONS["asin"] = create_user_function(fn);
  fn = &std::acos;
  GLOBAL_FUNCTIONS["acos"] = create_user_function(fn);
  fn = &std::atan;
  GLOBAL_FUNCTIONS["atan"] = create_user_function(fn);
  fn2 = &std::atan2;
  GLOBAL_FUNCTIONS["atan2"] = create_user_function(fn2);

  // hyperbolic trig functions
  fn = &std::sinh;
  GLOBAL_FUNCTIONS["sinh"] = create_user_function(fn);
  fn = &std::cosh;
  GLOBAL_FUNCTIONS["cosh"] = create_user_function(fn);
  fn = &std::tanh;
  GLOBAL_FUNCTIONS["tanh"] = create_user_function(fn);

  #if 0
  FIXME!!!!! This does not work for some reason, even when the tests in the configure script work.
#if defined(MATH_USE_ARC_HYP_TRIG)
#undef asinh
#undef acosh
#undef atanh  

  fn = &std::asinh;
  GLOBAL_FUNCTIONS["asinh"] = create_user_function(fn);
  fn = &std::acosh;
  GLOBAL_FUNCTIONS["acosh"] = create_user_function(fn);
  fn = &std::atanh;
  GLOBAL_FUNCTIONS["atanh"] = create_user_function(fn);
#endif
#endif /* 0 */
  
  // Logarithmic functions
  fn = &std::exp;
  GLOBAL_FUNCTIONS["exp"] = create_user_function(fn);
  fn = &std::log;
  GLOBAL_FUNCTIONS["log"] = create_user_function(fn);
  GLOBAL_FUNCTIONS["ln"]  = create_user_function(fn);
  fn2 = &std::pow;
  GLOBAL_FUNCTIONS["pow"] = create_user_function(fn2);

#if defined(MATH_USE_HYPOT)
  //  extern double hypot(double,double);
  fn2 = &std::hypot;
  GLOBAL_FUNCTIONS["hypot"] = create_user_function(fn2);
#endif
  

  // Misc math functions
  fn = &std::sqrt;
  GLOBAL_FUNCTIONS["sqrt"] = create_user_function(fn);
#if 0
  FIXME! This should work, as it does in the configure script... WHY DOES IT NOT?!?!?
#if defined(MATH_USE_CBRT)
  fn = &std::cbrt;
  GLOBAL_FUNCTIONS["cbrt"] = create_user_function(fn);
#endif /* defined(MATH_USE_CBRT) */
#endif /* 0 */
  fn = &std::ceil;
  GLOBAL_FUNCTIONS["ceil"] = create_user_function(fn);
  fn = &std::fabs;
  GLOBAL_FUNCTIONS["fabs"] = create_user_function(fn);
  fn = &std::floor;
  GLOBAL_FUNCTIONS["floor"] = create_user_function(fn);
  fn2 = &std::fmod;
  GLOBAL_FUNCTIONS["fmod"] = create_user_function(fn2);

#if 0
  FIXME these are almost the same as the aXXXh functions above.
#if defined(MATH_USE_INF_TESTS)
#undef isinf
#undef finite
#undef isnan
  fn3 = &std::isinf;
  GLOBAL_FUNCTIONS["isinf"] = create_user_function(fn3);
  fn3 = &std::finite;
  GLOBAL_FUNCTIONS["finite"] = create_user_function(fn3);
  fn3 = &std::isnan;
  GLOBAL_FUNCTIONS["isnan"] = create_user_function(fn3);
#endif /* MATH_USE_INF_TESTS */
#endif /* 0 */

#if defined(MATH_USE_COPYSIGN)
  extern double copysign(double,double);
  fn2 = &std::copysign;
  GLOBAL_FUNCTIONS["copysign"] = create_user_function(fn2);
#endif /* MATH_USE_COPYSIGN */
  
  GLOBAL_FUNCTIONS["sign"] = create_user_function(&sign);

}  /* InitFunctions() */


TUserFunctionMap all_user_functions()
{
  TUserFunctionMap temp_map;

  // GOM.debug() << "Getting global functions." << endl;
  temp_map.insert(GLOBAL_FUNCTIONS.begin(),
		  GLOBAL_FUNCTIONS.end());
  

  stack<attrib_type> temp_stack;

  // Copy from the current stack to a new one...
  while( !DATASTACK.empty() )
  {
    magic_pointer<TAttribute> attr = DATASTACK.top();
    DATASTACK.pop();
    
    temp_stack.push(attr);
  }

  // Now, copy back, collecting any procedural variables in the stack...
  // GOM.debug() << "Getting all local functions (in all scopes)." << endl;

  while( !temp_stack.empty() )
  {
    magic_pointer<TAttribute> attr = temp_stack.top();
    temp_stack.pop();

    //    GOM.debug() << "Adding functions from " << attr->toString() << endl;
    

    DATASTACK.push(attr);

    if( !!attr)
    {
      magic_pointer<TProcedural> proc = get_procedural_var(attr);
      
      if( !!proc )
      {
	TUserFunctionMap new_map = proc->getUserFunctions();

	// I (KH) believe that the following line is failing (new values are
	// NOT overwriting previous values) on gcc-2.95.3.  Therefore, I am
	// going to try to manually insert all of the items.
	//    temp_map.insert(new_map.begin(), new_map.end());

	for(TUserFunctionMap::iterator i = new_map.begin();
	    i != new_map.end();
	    ++i)
	{
	  //	  GOM.debug() << "Manually placing " << i->first << " into the map." << endl;
	  temp_map[i->first] = i->second;
	}
      }
    }
  }

  // GOM.debug() << "Returning functions..." << endl;
  return temp_map;
}

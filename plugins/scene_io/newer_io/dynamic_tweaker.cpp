#include "dynamic_tweaker.h"
#include <cstdio>

// An extern for writing errors...
extern int yyerror(const char*);



//
// Convert a value returned from a 'getAttribute' function into a dynamic_base object.
// If no conversion is possible, a NULL pointer is returned.
//
magic_pointer<Tdynamic_base> convert_object(NAttribute nVALUE, EAttribType eTYPE)
{
  switch(eTYPE)
  {
  case FX_BOOL:
    return new Tdynamic_bool(nVALUE.gValue);
  case FX_REAL:
    return new Tdynamic_real(nVALUE.dValue);
  case FX_STRING:
    printf("Created a dynamic string from barf\n");
    return new Tdynamic_string(string((const char*)nVALUE.pvValue));
  case FX_COLOR:
  case FX_VECTOR:
    return new Tdynamic_vector(*(const TVector*)nVALUE.pvValue);
  case FX_VECTOR2:
    return NULL;
  case FX_IMAGE:
  case FX_BSDF:
  case FX_CAMERA:
  case FX_LIGHT:
  case FX_MATERIAL:
  case FX_RENDERER:
  case FX_OBJECT:
  case FX_AGGREGATE:
  case FX_OBJECT_FILTER:
  case FX_IMAGE_FILTER:
    return new Tdynamic_object(((const TProcedural*)nVALUE.pvValue)->clone());    
  default:
    return NULL;
  }
}




//
// Convert a dynamic object into something suitable for use in a call to setAttribute.
// If the conversion was done, true will be returned.
// NOTE: it is important to call the set attribute function BEFORE the object
// passed here goes out of scope (if any attribute type that involves copying
// of the pointer is used).  If it goes out of scope before, very bad things
// will happen.  Also, the call to setAttribute must NOT copy the pointer from
// here.  It should first 'clone' the object, or use the assignment operator,
// etc.
//
bool convert_object ( const magic_pointer<Tdynamic_base>& mpdb, NAttribute& rnVALUE, EAttribType eTYPE)
{
  // If it is a reference, call a read on it.
  if( rcp_dynamic_cast<Tdynamic_reference>(mpdb) != NULL )
  {
    const Tdynamic_reference* tdr = (const Tdynamic_reference*)mpdb.get_pointer();
    if( eTYPE == tdr->getAttribType() )
    {
      return tdr->read(rnVALUE) == FX_ATTRIB_OK;
    }
    return false;
  }    
  
  switch(eTYPE)
  {
  case FX_BOOL:
    if( rcp_dynamic_cast<Tdynamic_bool>(mpdb) != NULL )
    {
      return ((Tdynamic_bool*)mpdb.get_pointer())->getAttribute("value",rnVALUE) != FX_ATTRIB_WRONG_PARAM;
    }
    return false;
  case FX_REAL:
    if( rcp_dynamic_cast<Tdynamic_real>(mpdb) != NULL )
    {
      return ((Tdynamic_real*)mpdb.get_pointer())->getAttribute("value",rnVALUE) != FX_ATTRIB_WRONG_PARAM;
    }
    return false;
  case FX_STRING:
    if( rcp_dynamic_cast<Tdynamic_string>(mpdb) != NULL )
    {
      return ((Tdynamic_string*)mpdb.get_pointer())->getAttribute("value",rnVALUE) != FX_ATTRIB_WRONG_PARAM;
    }
    return false;    
  case FX_COLOR:
    if( rcp_dynamic_cast<Tdynamic_vector>(mpdb) != NULL )
    {
      return ((Tdynamic_vector*)mpdb.get_pointer())->getAttribute("value",rnVALUE) != FX_ATTRIB_WRONG_PARAM;
    }
    return false;    
  case FX_VECTOR:
    if( rcp_dynamic_cast<Tdynamic_vector>(mpdb) != NULL )
    {
      return ((Tdynamic_vector*)mpdb.get_pointer())->getAttribute("value",rnVALUE) != FX_ATTRIB_WRONG_PARAM;
    }
    return false;        
  case FX_VECTOR2:
    return NULL;
  case FX_IMAGE:          // falls through to the FX_IMAGE_FILTER case
  case FX_BSDF:   
  case FX_CAMERA:
  case FX_LIGHT:
  case FX_MATERIAL:
  case FX_RENDERER:
  case FX_OBJECT:
  case FX_AGGREGATE:
  case FX_OBJECT_FILTER:
  case FX_IMAGE_FILTER:
    if( rcp_dynamic_cast<Tdynamic_object>(mpdb) != NULL )
    {
      rnVALUE.pvValue = (void*)mpdb.get_pointer();
      return true;
    }
    return false;    
   default:
    return false;
  }  
}


// A horrible macro for use in dynamic casting, type checking, and perform some operator.
#define cast_check_and_op(OP, TYPE1, TYPE2, TYPE3, FUNCTION1, FUNCTION2)  \
{                                                                         \
  if( rcp_dynamic_cast<TYPE1>(mp1) != NULL )                              \
  {                                                                       \
    if( rcp_dynamic_cast<TYPE2>(mp2) != NULL )                            \
    {                                                                     \
      return new TYPE3(((const TYPE1*)mp1.get_pointer())->FUNCTION1()   \
		       OP                                                 \
		       ((const TYPE2*)mp2.get_pointer())->FUNCTION2()); \
    }                                                                     \
  }                                                                       \
}

// 
// Attempt to perform some addition of the object in mp1 and in mp2.  If it is
// successful, a non-null object will be returned.
//
magic_pointer<Tdynamic_base> add(const magic_pointer<Tdynamic_base>& mp1,
				 const magic_pointer<Tdynamic_base>& mp2)
{
  // Add is valid for (real,real), (vector,vector), (string,string)
  cast_check_and_op(+, Tdynamic_real,   Tdynamic_real,   Tdynamic_real,   getValue, getValue);
  cast_check_and_op(+, Tdynamic_vector, Tdynamic_vector, Tdynamic_vector, getValue, getValue);
  //  cast_check_and_op(+, Tdynamic_string, Tdynamic_string, Tdynamic_string, getValue, getValue);  


  // THE REFERENCE TYPE NEEDS TO BE CHECKED!!!
  
  return NULL;
}


// 
// Attempt to perform some subtraction of the object in mp1 and in mp2.  If it
// is successful, a non-null object will be returned.
//
magic_pointer<Tdynamic_base> sub(const magic_pointer<Tdynamic_base>& mp1,
				 const magic_pointer<Tdynamic_base>& mp2)
{
  // Sub is valid for (real,real), (vector,vector)
  cast_check_and_op(-, Tdynamic_real,   Tdynamic_real,   Tdynamic_real,   getValue, getValue);
  cast_check_and_op(-, Tdynamic_vector, Tdynamic_vector, Tdynamic_vector, getValue, getValue);

  // THE REFERENCE TYPE NEEDS TO BE CHECKED!!!
  
  return NULL;
}  


// 
// Attempt to perform some multiplication of the object in mp1 and in mp2.  If
// it is successful, a non-null object will be returned.
//
magic_pointer<Tdynamic_base> mul(const magic_pointer<Tdynamic_base>& mp1,
				 const magic_pointer<Tdynamic_base>& mp2)
{
  // Mul is valid for (real,real), (real,vector), (vector,real)
  cast_check_and_op(*, Tdynamic_real,   Tdynamic_real,   Tdynamic_real,   getValue, getValue);
  cast_check_and_op(*, Tdynamic_real,   Tdynamic_vector, Tdynamic_vector, getValue, getValue);
  cast_check_and_op(*, Tdynamic_vector, Tdynamic_real,   Tdynamic_vector, getValue, getValue);  

  // THE REFERENCE TYPE NEEDS TO BE CHECKED!!!
  
  return NULL;
}    

// 
// Attempt to perform some multiplication of the object in mp1 and in mp2.  If
// it is successful, a non-null object will be returned.
//
magic_pointer<Tdynamic_base> div(const magic_pointer<Tdynamic_base>& mp1,
				 const magic_pointer<Tdynamic_base>& mp2)
{
  // Div is valid for (real,real), (vector,real)
  cast_check_and_op(/, Tdynamic_real,   Tdynamic_real,   Tdynamic_real,   getValue, getValue);
  cast_check_and_op(/, Tdynamic_vector, Tdynamic_real,   Tdynamic_vector, getValue, getValue);  

  // THE REFERENCE TYPE NEEDS TO BE CHECKED!!!
  
  return NULL;
}    


EAttribType guess_type(const magic_pointer<Tdynamic_base>& tdb)
{
  if( rcp_dynamic_cast<Tdynamic_real>(tdb) != NULL )
  {
    return FX_REAL;
  }
  else if( rcp_dynamic_cast<Tdynamic_bool>(tdb) != NULL )
  {
    return FX_BOOL;
  }
  else if( rcp_dynamic_cast<Tdynamic_vector>(tdb) != NULL )
  {
    return FX_VECTOR;
  }
  else if( rcp_dynamic_cast<Tdynamic_string>(tdb) != NULL )
  {
    return FX_STRING;
  }
  else if( rcp_dynamic_cast<Tdynamic_object>(tdb) != NULL )
  {
    return FX_OBJECT;
  }
  else if( rcp_dynamic_cast<Tdynamic_reference>(tdb) != NULL )
  {
    return ((const Tdynamic_reference*)tdb.get_pointer())->getAttribType();
  }
  else
  {
    return FX_NONE;
  }
}

bool is_bool(const magic_pointer<Tdynamic_base>& tdb)
{
  if( rcp_dynamic_cast<Tdynamic_bool>(tdb) != NULL )
  {
    return true;
  }
  else
  {
    NAttribute val;
    return convert_object(tdb, val, FX_BOOL);
  }    
} // is_bool
bool is_real(const magic_pointer<Tdynamic_base>& tdb)
{
  if( rcp_dynamic_cast<Tdynamic_real>(tdb) != NULL )
  {
    return true;
  }
  else
  {
    NAttribute val;
    return convert_object(tdb, val, FX_REAL);
  }  
} // is_real
bool is_string(const magic_pointer<Tdynamic_base>& tdb)
{
  if( rcp_dynamic_cast<Tdynamic_string>(tdb) != NULL )
  {
    return true;
  }
  else
  {
    NAttribute val;
    return convert_object(tdb, val, FX_STRING);
  }
} // is_string
bool is_vector(const magic_pointer<Tdynamic_base>& tdb)
{
  if( rcp_dynamic_cast<Tdynamic_vector>(tdb) != NULL )
  {
    return true;
  }
  else
  {
    NAttribute val;
    return convert_object(tdb, val, FX_VECTOR);
  }
} // is_vector


double get_real(const magic_pointer<Tdynamic_base>& tdb, bool bail)
{
  if( rcp_dynamic_cast<Tdynamic_real>(tdb) != NULL )
  {
    return ((const Tdynamic_real*)tdb.get_pointer())->getValue();
  }
  else
  {
    NAttribute val;
    if( convert_object(tdb, val, FX_REAL) )
    {
      return val.dValue;
    }
  }
  if( bail )
  {
    yyerror(string(string("Object of type ") + tdb->getDynamicType() + " cannot be converted to a \"real\"").c_str());
    exit(1);
  }
  return 0;
} // get_real

bool get_bool(const magic_pointer<Tdynamic_base>& tdb, bool bail)
{
  if( rcp_dynamic_cast<Tdynamic_bool>(tdb) != NULL )
  {
    return ((const Tdynamic_bool*)tdb.get_pointer())->getValue();
  }
  else
  {
    NAttribute val;
    if( convert_object(tdb, val, FX_BOOL) )
    {
      return val.gValue;
    }
  }
  if( bail )
  {
    yyerror(string(string("Object of type ") + tdb->getDynamicType() + " cannot be converted to a \"bool\"").c_str());
    exit(1);
  }
  return false;
} // get_bool

TVector get_vector(const magic_pointer<Tdynamic_base>& tdb, bool bail)
{
  if( rcp_dynamic_cast<Tdynamic_vector>(tdb) != NULL )
  {
    return ((const Tdynamic_vector*)tdb.get_pointer())->getValue();
  }
  else
  {
    NAttribute val;
    if( convert_object(tdb, val, FX_VECTOR) )
    {
      return *(const TVector*)val.pvValue;
    }
  }
  if( bail )
  {
    yyerror(string(string("Object of type ") + tdb->getDynamicType() + " cannot be converted to a \"vector\"").c_str());
    exit(1);
  }
  return TVector();
} // get_vector

// Trash for the 'get_object' function
extern magic_pointer<Tdynamic_base> current_object;
#include "symtab.h"

const TProcedural* get_object(const magic_pointer<Tdynamic_base>& tdb, bool bail)
{
  if( tdb == NULL )
  {
    yyerror("a null reference is not an object");
    exit(1);    
  }
  else if( rcp_dynamic_cast<Tdynamic_object>(tdb) != NULL )
  {
    return ((const Tdynamic_object*)tdb.get_pointer())->getObject();
  }
  else if( rcp_dynamic_cast<Tdynamic_reference>(tdb) != NULL )
  {
    const Tdynamic_reference* tdr = (const Tdynamic_reference*)(tdb.get_pointer());
    if( tdr->getAttribType() == FX_OBJECT )
    {
      NAttribute val;
      tdr->read(val);
      return (const TProcedural*)val.pvValue;
    }
  }
  else if( is_string(tdb) )
  {
    string name = get_string(tdb);

    // First, look at the attributes of the current object
    if( current_object != NULL )
    {
      TAttributeList attr_list;

      current_object->getAttributeList(attr_list);

      TAttributeList::const_iterator i = attr_list.find(name);

      if( i != attr_list.end() )
      {
	if( attr_list[name] == FX_OBJECT )
	{
	  NAttribute val;

	  if( current_object->getAttribute(name, val) == FX_ATTRIB_OK )
	  {
	    return  (TProcedural*)val.pvValue;
	  }
	}
	else
	{
	  string message = string("attribute ") + name + string(" is not an object");
	  yyerror(message.c_str());
	  exit(1);
	}
      }
    } // current object != NULL

    magic_pointer<Tdynamic_base> located_object = locate_reference(name);

    if( located_object != NULL )
    {
      return get_object(located_object);
    }

    string message = name + string(" could not be found");
    yyerror(message.c_str());
    exit(1);
  } // is_string(tdb)

  string message = string("I don't know how to extract an object from a \"") + tdb->getDynamicType() + string("\"");
  yyerror(message.c_str());
  exit(1);
} // get_object

string get_string(const magic_pointer<Tdynamic_base>& tdb, bool bail)
{
  if(tdb == NULL)
  {
    return "";
  }
  else if( rcp_dynamic_cast<Tdynamic_string>(tdb) != NULL )
  {
    return ((const Tdynamic_string*)tdb.get_pointer())->getValue();
  }
  else
  {
    NAttribute val;
    if( convert_object(tdb, val, FX_STRING) )
    {
      return string((const char*)val.pvValue);
    }
  }

  if( is_bool(tdb) )
  {
    if( get_bool(tdb) )
    {
      return "true";
    }
    else
    {
      return "false";      
    }
  }
  else if( is_real(tdb) )
  {
    char buffer[1024];
    memset(buffer,'\0',1024);
    sprintf(buffer,"%f",(float)get_real(tdb));
    return(string(buffer));
  }
  else if( is_vector(tdb) )
  {
    char buffer[1024];
    memset(buffer,'\0',1024);    
    TVector vec = get_vector(tdb);
    string ret_string = "";
    ret_string += "[";
    sprintf(buffer,"%f",(float)vec.x());
    ret_string += buffer;
    ret_string += ",";
    sprintf(buffer,"%f",(float)vec.y());
    ret_string += buffer;
    ret_string += ",";
    sprintf(buffer,"%f",(float)vec.z());
    ret_string += buffer;    
    ret_string += "]";
    return ret_string;
  }
  
  if( bail )
  {
    if( tdb->getDynamicType() == string("string") )
    {
      printf("FOOBAR!!! Something hosed!!!\n");
      printf("pointer=0x%06x, dynamic_string pointer=0x%06x\n",
	     int(tdb.get_pointer()),
	     int(rcp_dynamic_cast<Tdynamic_string>(tdb).get_pointer()));
      printf("%s\n!!!!",tdb->className().c_str());
      printf("%s\n!!!!",rcp_dynamic_cast<Tdynamic_string>(tdb)->className().c_str());
    }
    yyerror(string(string("Object of type ") + tdb->getDynamicType() + " cannot be converted to a \"string\"").c_str());
    exit(1);
  }
  return "";
} // get_string

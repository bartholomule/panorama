#if       !defined(KH_DYNAMIC_TWEAKER_H)
#define            KH_DYNAMIC_TWEAKER_H
/*
  Revision History:
  07Jun2000 (KH) Started writing this file.  Wrot the convert_object function
            (2 ways), add, sub, mul, and div.
 */

#include "dynamic_objects.h"
#include "magic_pointer.h"

//
// Convert a value returned from a 'getAttribute' function into a dynamic_base object.
// If no conversion is possible, a NULL pointer is returned.
//
magic_pointer<Tdynamic_base> convert_object(NAttribute nVALUE, EAttribType eTYPE);

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
bool convert_object ( const magic_pointer<Tdynamic_base>& mpdb, NAttribute& rnVALUE, EAttribType eTYPE);


// 
// Attempt to perform some addition of the object in mp1 and in mp2.  If it is
// successful, a non-null object will be returned.
//
magic_pointer<Tdynamic_base> add(const magic_pointer<Tdynamic_base>& mp1,
				 const magic_pointer<Tdynamic_base>& mp2);

// 
// Attempt to perform some subtraction of the object in mp1 and in mp2.  If it
// is successful, a non-null object will be returned.
//
magic_pointer<Tdynamic_base> sub(const magic_pointer<Tdynamic_base>& mp1,
				 const magic_pointer<Tdynamic_base>& mp2);

// 
// Attempt to perform some multiplication of the object in mp1 and in mp2.  If
// it is successful, a non-null object will be returned.
//
magic_pointer<Tdynamic_base> mul(const magic_pointer<Tdynamic_base>& mp1,
				 const magic_pointer<Tdynamic_base>& mp2);

// 
// Attempt to perform some multiplication of the object in mp1 and in mp2.  If
// it is successful, a non-null object will be returned.
//
magic_pointer<Tdynamic_base> div(const magic_pointer<Tdynamic_base>& mp1,
				 const magic_pointer<Tdynamic_base>& mp2);

//
// Return the most likely attribute type for the given object.
//
EAttribType guess_type(const magic_pointer<Tdynamic_base>& tdb);

bool is_bool(const magic_pointer<Tdynamic_base>& tdb);
bool is_real(const magic_pointer<Tdynamic_base>& tdb);
bool is_string(const magic_pointer<Tdynamic_base>& tdb);
bool is_vector(const magic_pointer<Tdynamic_base>& tdb);

double get_real(const magic_pointer<Tdynamic_base>& tdb, bool bail = true);
bool get_bool(const magic_pointer<Tdynamic_base>& tdb, bool bail = true); 
string get_string(const magic_pointer<Tdynamic_base>& tdb, bool bail = true);
TVector get_vector(const magic_pointer<Tdynamic_base>& tdb, bool bail = true);
const TProcedural* get_object(const magic_pointer<Tdynamic_base>& tdb, bool bail = true); 

#endif /* !defined(KH_DYNAMIC_TWEAKER_H) */

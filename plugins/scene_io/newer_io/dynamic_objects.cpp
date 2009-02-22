/*
  Revision History:
  06Jun2000 (KH) began writing this file.  Wrote members for the base object,
  bool, real, std::vector, and std::string classes (223 lines including comments).
 */
#include "dynamic_objects.h"
#include <cstdio>

#define CHECK_FX_TYPE(b) if ( eTYPE != (b) ) return FX_ATTRIB_WRONG_TYPE

//
// base dynamic object
//
const char* Tdynamic_base::skcpType = "none";
int Tdynamic_base::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  if( rktNAME == "typeof")
  {
    return FX_ATTRIB_WRONG_VALUE;
  }
  else
  {
    return TProcedural::setAttribute(rktNAME, nVALUE, eTYPE);
  }
}
int Tdynamic_base::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{
  if( rktNAME == "typeof")
  {
    rnVALUE.pvValue = (void*)getDynamicType();
    return FX_ATTRIB_OK;    
  }
  return TProcedural::getAttribute (rktNAME, rnVALUE);
}
void Tdynamic_base::getAttributeList (TAttributeList& rtLIST) const
{
  TProcedural::getAttributeList (rtLIST);

  // NOTE: typeof is a hidden attribute.  I find it annoying to see it on so many lists.  
  //  rtLIST ["typeof"] = FX_STRING;
}


//
// "real" number
//
const char* Tdynamic_real::skcpType = "real";
int Tdynamic_real::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  if( rktNAME == "value")
  {
    CHECK_FX_TYPE(FX_REAL);
      
    dValue = nVALUE.dValue;
    return FX_ATTRIB_OK;
  }
  else
  {
    return Tdynamic_base::setAttribute(rktNAME, nVALUE, eTYPE);
  }
}
int Tdynamic_real::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{
  if( rktNAME == "value")
  {
    rnVALUE.dValue = dValue;
    return FX_ATTRIB_OK;    
  }
  return Tdynamic_base::getAttribute (rktNAME, rnVALUE);
}
void Tdynamic_real::getAttributeList (TAttributeList& rtLIST) const
{
  Tdynamic_base::getAttributeList (rtLIST);
  
  rtLIST ["value"] = FX_REAL;
}

//
// boolean value
//
const char* Tdynamic_bool::skcpType = "bool";
int Tdynamic_bool::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  if( rktNAME == "value")
  {
    CHECK_FX_TYPE(FX_BOOL);    
    
    bValue = nVALUE.gValue;
    return FX_ATTRIB_OK;
  }
  else
  {
    return Tdynamic_base::setAttribute(rktNAME, nVALUE, eTYPE);
  }
}
int Tdynamic_bool::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{
  if( rktNAME == "value")
  {
    rnVALUE.gValue = bValue;
    return FX_ATTRIB_OK;
  }
  return Tdynamic_base::getAttribute (rktNAME, rnVALUE);
}
void Tdynamic_bool::getAttributeList (TAttributeList& rtLIST) const
{
  Tdynamic_base::getAttributeList (rtLIST);
  
  rtLIST ["value"] = FX_BOOL;
}

//
// std::vector
//
const char* Tdynamic_vector::skcpType = "vector";
int Tdynamic_vector::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  if( rktNAME == "value")
  {
    CHECK_FX_TYPE(FX_VECTOR);        

    if( nVALUE.pvValue != NULL )
    {
      tvValue =  *(const TVector*)nVALUE.pvValue;
      return FX_ATTRIB_OK;
    }
    else
    {
      return FX_ATTRIB_WRONG_VALUE;
    }
  }  
  else if( rktNAME == "x")
  {
    CHECK_FX_TYPE(FX_REAL);        
    
    tvValue.setX (nVALUE.dValue);
    return FX_ATTRIB_OK;
  }
  else if( rktNAME == "y")
  {
    CHECK_FX_TYPE(FX_REAL);            
    
    tvValue.setY (nVALUE.dValue);
    return FX_ATTRIB_OK;
  }
  else if( rktNAME == "z")
  {
    CHECK_FX_TYPE(FX_REAL);            
    
    tvValue.setZ (nVALUE.dValue);
    return FX_ATTRIB_OK;
  }  
  else
  {
    return Tdynamic_base::setAttribute(rktNAME, nVALUE, eTYPE);
  }
}
int Tdynamic_vector::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{
  if( rktNAME == "value")
  {
    rnVALUE.pvValue = (void*)&tvValue;
    return FX_ATTRIB_OK;
  }    
  else if( rktNAME == "x")
  {
    rnVALUE.dValue = tvValue.x();
    return FX_ATTRIB_OK;
  }
  else if( rktNAME == "y")
  {
    rnVALUE.dValue = tvValue.y();
    return FX_ATTRIB_OK;
  }
  else if( rktNAME == "z")
  {
    rnVALUE.dValue = tvValue.z();
    return FX_ATTRIB_OK;
  }
  else
  {
    return Tdynamic_base::getAttribute (rktNAME, rnVALUE);
  }
}
void Tdynamic_vector::getAttributeList (TAttributeList& rtLIST) const
{
  Tdynamic_base::getAttributeList (rtLIST);

  rtLIST ["value"] = FX_VECTOR;  
  rtLIST ["x"] = FX_REAL;
  rtLIST ["y"] = FX_REAL;
  rtLIST ["z"] = FX_REAL;  
}


//
// std::string value
//
const char* Tdynamic_string::skcpType = "string";
int Tdynamic_string::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  if( rktNAME == "value")
  {
    CHECK_FX_TYPE(FX_STRING);    
    
    Value = std::string((const char*)nVALUE.pvValue);
    return FX_ATTRIB_OK;
  }
  else
  {
    return Tdynamic_base::setAttribute(rktNAME, nVALUE, eTYPE);
  }
}
int Tdynamic_string::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{
  if( rktNAME == "value")
  {
    rnVALUE.pvValue = (void*)Value.c_str();
    return FX_ATTRIB_OK;
  }
  return Tdynamic_base::getAttribute (rktNAME, rnVALUE);
}
void Tdynamic_string::getAttributeList (TAttributeList& rtLIST) const
{
  Tdynamic_base::getAttributeList (rtLIST);
  
  rtLIST ["value"] = FX_STRING;
}

//
// object of some sort.
//
const char* Tdynamic_object::skcpType = "object";
const char* Tdynamic_object::getDynamicType (void) const
{
  static char buffer[4096];
  sprintf(buffer,"%s",className().c_str());
  return buffer;
}
int Tdynamic_object::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  if( rktNAME == "objptr")
  {
    CHECK_FX_TYPE(FX_OBJECT);    

    delete ptProcedural;
    
    ptProcedural = ((const TProcedural*)nVALUE.pvValue)->clone();
    return FX_ATTRIB_OK;
  }
  else
  {
    if( ptProcedural != NULL )
    {
      int retval = ptProcedural->setAttribute (rktNAME, nVALUE, eTYPE);
      if( retval != FX_ATTRIB_WRONG_PARAM )
      {
	return retval;
      }
    }
    return Tdynamic_base::setAttribute(rktNAME, nVALUE, eTYPE);
  }
}
int Tdynamic_object::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{
  if( rktNAME == "objptr")
  {
    if( ptProcedural != NULL )
    {
      rnVALUE.pvValue = (void*)ptProcedural;
      return FX_ATTRIB_OK;
    }
    else
    {
      return FX_ATTRIB_WRONG_VALUE;
    }
  }
  else if( ptProcedural != NULL )
  {
    int retval = ptProcedural->getAttribute (rktNAME, rnVALUE);
    if( retval != FX_ATTRIB_WRONG_PARAM )
    {
      return retval;
    }
    // Return the value from the base class...
  }
  return Tdynamic_base::getAttribute (rktNAME, rnVALUE);
}
void Tdynamic_object::getAttributeList (TAttributeList& rtLIST) const
{
  Tdynamic_base::getAttributeList (rtLIST);

  if( ptProcedural != NULL )
  {
    ptProcedural->getAttributeList (rtLIST);
  }

  // NOTE: objptr is a hidden attribute.  I find it annoying to see it on so many lists.
  //  rtLIST ["objptr"] = FX_OBJECT;
}


//
// reference of some sort.
//
const char* Tdynamic_reference::skcpType = "reference";
int Tdynamic_reference::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  return Tdynamic_object::setAttribute(rktNAME, nVALUE, eTYPE);
}
int Tdynamic_reference::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{
  return Tdynamic_object::getAttribute (rktNAME, rnVALUE);
}
void Tdynamic_reference::getAttributeList (TAttributeList& rtLIST) const
{
  Tdynamic_object::getAttributeList (rtLIST);
}


//
// dotted object...
//
#include "symtab.h"
extern int yyerror(const char*);

#define dotted_recover_last(BASE,INDEX,NEXT,RETVAL,ATTRIB)                  \
  if( is_string(BASE) )                                                     \
  {                                                                         \
    NEXT = locate_reference(get_string(BASE));                              \
  }                                                                         \
                                                                            \
  for(; (RETVAL == FX_ATTRIB_OK) && (INDEX < attrib_names.size()); ++INDEX) \
  {                                                                         \
    if( NEXT == NULL )                                                      \
    {                                                                       \
      ret_val = FX_ATTRIB_WRONG_PARAM;                                      \
    }                                                                       \
    else                                                                    \
    {                                                                       \
      ret_val = NEXT->getAttribute (attrib_names[INDEX], ATTRIB);           \
    }                                                                       \
                                                                            \
    if( ret_val == FX_ATTRIB_OK )                                           \
    {                                                                       \
      TAttributeList tlist;                                                 \
                                                                            \
      NEXT->getAttributeList(tlist);                                        \
      EAttribType attr_type = tlist[attrib_names[INDEX]];                   \
                                                                            \
      NEXT = convert_object(ATTRIB, attr_type);                             \
    }                                                                       \
  }

int Tdotted_list::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  magic_pointer<Tdynamic_base> next = base;
  int ret_val = FX_ATTRIB_OK;
  unsigned index = 0;
  NAttribute val;

  dotted_recover_last(base,index,next,ret_val,val);

  if( index == attrib_names.size() )
  {
    if( next != NULL )
    {
      //      printf("Setting attribute (%s) for 0x%06x\n", rktNAME.c_str(),(int)next.get_pointer());
      return next->setAttribute(rktNAME, nVALUE, eTYPE);
    }
    else
    {
      return FX_ATTRIB_WRONG_PARAM;
    }
  }
  else if( ret_val == FX_ATTRIB_WRONG_PARAM )
  {
    yyerror(string("object has no attribute named " + attrib_names[index]).c_str());
  }
  return FX_ATTRIB_WRONG_PARAM;
}

int Tdotted_list::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{
  magic_pointer<Tdynamic_base> next = base;
  int ret_val = FX_ATTRIB_OK;
  unsigned index = 0;

  dotted_recover_last(base,index,next,ret_val,rnVALUE);  

  if( index == attrib_names.size() )
  {
    if( next != NULL )
    {
      //      printf("Getting attribute (%s) for 0x%06x\n", rktNAME.c_str(),(int)next.get_pointer());      
      return next->getAttribute(rktNAME, rnVALUE);
    }
    else
    {
      return FX_ATTRIB_WRONG_PARAM;
    }
  }
  else if( ret_val == FX_ATTRIB_WRONG_PARAM )
  {
    yyerror(string("object has no attribute named " + attrib_names[index]).c_str());
  }
  return FX_ATTRIB_WRONG_PARAM;
}

void Tdotted_list::getAttributeList (TAttributeList& rtLIST) const
{
  magic_pointer<Tdynamic_base> next = base;
  int ret_val = FX_ATTRIB_OK;
  unsigned index = 0;
  NAttribute val;

  dotted_recover_last(base,index,next,ret_val,val);  
  
  if( index == attrib_names.size() )
  {
    if( next != NULL )
    {
      //      printf("Getting attribute list for 0x%06x\n", (int)next.get_pointer());
      next->getAttributeList(rtLIST);
    }
  }
  else if( ret_val == FX_ATTRIB_WRONG_PARAM )
  {
    yyerror(string("object has no attribute named " + attrib_names[index]).c_str());
  }
}

const char* Tdotted_list::getDynamicType (void) const
{
  magic_pointer<Tdynamic_base> next = base;
  int ret_val = FX_ATTRIB_OK;
  unsigned index = 0;
  NAttribute val;

  dotted_recover_last(base,index,next,ret_val,val);
  if( index == attrib_names.size() )
  {
    if( next != NULL )
    {    
      return next->getDynamicType ();
    }
  }
  return "dotted_list";
}


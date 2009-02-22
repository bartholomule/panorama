#if       !defined(KH_DYNAMIC_OBJECTS_H)
#define            KH_DYNAMIC_OBJECTS_H
/*
  Revision History:
  06Jun2000 (KH) Started writing this file.
            Added the Tdynamic_base, real, bool, vector, and std::string classes.
 */

#include "llapi/procedural.h"
#include "llapi/attribs.h"
#include "llapi/llapi_defs.h"

class Tdynamic_base : public TProcedural
{
private:
  static const char* skcpType;  
public:
  Tdynamic_base (void) { }
  virtual ~Tdynamic_base (void) { }
  virtual const char* getDynamicType (void) const { return skcpType; }
  
  virtual std::string className (void) const { return "dynamic_base"; }
  virtual EClass classType (void) const { return FX_SCENE_CLASS; /* FIXME!!! */ }
  // Attribute management
  virtual int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  virtual int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
  virtual void getAttributeList (TAttributeList& rtLIST) const;

};

class Tdynamic_real : public Tdynamic_base
{
private:
  static const char* skcpType;
  double dValue;
public:
  Tdynamic_real (void) { }
  Tdynamic_real (double d): dValue(d) { }  
  virtual ~Tdynamic_real (void) { }
  virtual const char* getDynamicType (void) const { return skcpType; }

  inline double getValue (void) const { return dValue; }
  
  virtual Tdynamic_real* clone (void) const { return(new Tdynamic_real(*this)); }
  virtual std::string className (void) const { return "dynamic_real"; }
  // Attribute management
  virtual int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  virtual int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
  virtual void getAttributeList (TAttributeList& rtLIST) const;  
};

class Tdynamic_bool : public Tdynamic_base
{
private:
  static const char* skcpType;
  bool bValue;
public:
  Tdynamic_bool (void) { }
  Tdynamic_bool (bool b): bValue(b) { }  
  virtual ~Tdynamic_bool (void) { }
  virtual const char* getDynamicType (void) const { return skcpType; }

  inline bool getValue (void) const { return bValue; }
  
  virtual Tdynamic_bool* clone (void) const { return(new Tdynamic_bool(*this)); }
  virtual std::string className (void) const { return "dynamic_bool"; }
  // Attribute management
  virtual int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  virtual int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
  virtual void getAttributeList (TAttributeList& rtLIST) const;  
};

class Tdynamic_vector : public Tdynamic_base
{
private:
  static const char* skcpType;
  TVector tvValue;
public:
  Tdynamic_vector (void) { }    
  Tdynamic_vector (const TVector& v): tvValue(v) { }  
  virtual ~Tdynamic_vector (void) { }
  virtual const char* getDynamicType (void) const { return skcpType; }

  inline TVector getValue (void) const { return tvValue; }
  
  virtual Tdynamic_vector* clone (void) const { return(new Tdynamic_vector(*this)); }
  virtual std::string className (void) const { return "dynamic_vector"; }
  // Attribute management
  virtual int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  virtual int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
  virtual void getAttributeList (TAttributeList& rtLIST) const;  
};

class Tdynamic_string : public Tdynamic_base
{
private:
  static const char* skcpType;
  std::string Value;
public:
  Tdynamic_string (void) { }
  Tdynamic_string (const std::string& s): Value(s) { }  
  virtual ~Tdynamic_string (void) { }
  virtual const char* getDynamicType (void) const { return skcpType; }

  inline std::string getValue (void) const { return Value; }
  
  virtual Tdynamic_string* clone (void) const { return(new Tdynamic_string(*this)); }
  virtual std::string className (void) const { return "dynamic_string"; }
  // Attribute management
  virtual int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  virtual int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
  virtual void getAttributeList (TAttributeList& rtLIST) const;  
};


// I now need to add a generic type (wrapper around a TProcedural to allow
// light sources and objects).
// Also, I need to make some form of a reference class, where it will be a
// reference to some kind of type, whether user-defined, or an attribute member
// of something.

class Tdynamic_object : public Tdynamic_base
{
private:
  static const char* skcpType;
  TProcedural* ptProcedural; // The object.
  bool free_after_done;
public:
  Tdynamic_object (void): ptProcedural(NULL), free_after_done(false) { }    
  Tdynamic_object (TProcedural* p, bool del = false): ptProcedural(p), free_after_done(del) { }  
  Tdynamic_object (const Tdynamic_object& ptdo):ptProcedural(ptdo.ptProcedural->clone()) { }  
  virtual ~Tdynamic_object (void)
  {
    if( free_after_done )
    {
      delete ptProcedural;
    }
  }
  Tdynamic_object& operator = (const Tdynamic_object& ptdo)
  {
    if( &ptdo != this )
    {
      if( free_after_done )
      {
	delete ptProcedural;
      }
      ptProcedural = ptdo.ptProcedural->clone();
    }
    return *this;
  }
  virtual const char* getDynamicType (void) const;
  const TProcedural* getObject (void) const { return ptProcedural; }
  
  virtual Tdynamic_object* clone (void) const { return(new Tdynamic_object(*this)); }
  virtual std::string className (void) const
  {
    if( ptProcedural != NULL )
    {
      return std::string("dynamic_object") + "(" + ptProcedural->className() + ")";
    }
    else
    {
      return "dynamic_object";
    }
  }
  // Attribute management
  virtual int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  virtual int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
  virtual void getAttributeList (TAttributeList& rtLIST) const;    
};


class Tdynamic_reference : public Tdynamic_object
{
private:
  static const char* skcpType;
  std::string attrib_name;
public:
  Tdynamic_reference (void): attrib_name("") { }    
  Tdynamic_reference (TProcedural* p, const std::string& name): Tdynamic_object(p), attrib_name(name) { }  
  virtual ~Tdynamic_reference (void) { }

  virtual const char* getDynamicType (void) const { return skcpType; }
  const std::string getAttribName (void) const { return attrib_name; }

  int read(NAttribute& rnVALUE) const
  {
    return getAttribute (attrib_name, rnVALUE);
  }
  int write(NAttribute nVALUE, EAttribType eTYPE)
  {
    return setAttribute (attrib_name, nVALUE, eTYPE);
  }
  EAttribType getAttribType (void) const
  {
    TAttributeList tal;
    getAttributeList (tal);
    
    TAttributeList::iterator loc = tal.find(attrib_name);
    if( loc != tal.end() )
    {
      return loc->second;
    }
    return FX_NONE;
  }
  
  virtual Tdynamic_reference* clone (void) const { return(new Tdynamic_reference(*this)); }
  virtual std::string className (void) const { return "dynamic_reference"; }
  // Attribute management
  virtual int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  virtual int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
  virtual void getAttributeList (TAttributeList& rtLIST) const;      
};


#include "magic_pointer.h"
#include <vector>

class Tdotted_list: public Tdynamic_base
{
private:
  magic_pointer<Tdynamic_base> base;
  std::vector<std::string> attrib_names;
public:
  Tdotted_list (const magic_pointer<Tdynamic_base>& base_object): base(base_object), attrib_names()
  {
  }
  Tdotted_list (const magic_pointer<Tdynamic_base>& base_object, std::string attrib):
    base(base_object),
    attrib_names()
  {
    attrib_names.push_back(attrib);
  }
  Tdotted_list (const Tdotted_list& tdo, std::string attrib): base(tdo.base), attrib_names(tdo.attrib_names)
  {
    attrib_names.push_back(attrib);    
  }
  virtual ~Tdotted_list (void) { }
  
  virtual const char* getDynamicType (void) const;

  magic_pointer<Tdynamic_base> get_base (void) const { return base; }
  unsigned get_chain_length (void) const { return attrib_names.size(); }
  const std::vector<std::string>& get_chain (void) const { return attrib_names; }
  
  IMPLEMENT_CLONE(Tdotted_list);
  
  virtual std::string className (void) const { return "dotted_list"; }
  // Attribute management
  virtual int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  virtual int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
  virtual void getAttributeList (TAttributeList& rtLIST) const;        
};

#endif /* !defined(KH_DYNAMIC_OBJECTS_H) */

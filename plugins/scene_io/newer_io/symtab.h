#if !defined(KH_SYMTAB_H)
#define KH_SYMTAB_H

#include <map>
#include <stack>
#include <string>
#include <vector>
#include "magic_pointer.h"
#include "dynamic_objects.h"
#include "dynamic_tweaker.h"


typedef magic_pointer<Tdynamic_base> item_type;
typedef map<string,item_type> scope_type;
typedef magic_pointer<scope_type> stack_item_type;
extern stack_item_type global_scope;
typedef stack<stack_item_type,vector<stack_item_type> > stack_type;
extern stack_type scope_stack;
typedef pair<string,item_type> scope_item;


// Initialize the symbol table.
void init_symtab();
void initialize_scope(stack_item_type& sit, const stack_item_type& parent_scope);

// Put it into the top scope of the scope_stack.
void put_top(const string& name, const item_type& it);

item_type locate_reference(const string& name);


class scope_object: public Tdynamic_base
{
private:
  stack_item_type scope;
  static const char* skcpType;
public:
  scope_object(stack_item_type& stuff): scope(stuff) { }
  virtual const char* getDynamicType (void) const { return skcpType; }
  virtual string className (void) const { return "scope_object"; }
  // Attribute management
  virtual int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  virtual int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
  virtual void getAttributeList (TAttributeList& rtLIST) const;      
};

#endif // !defined(KH_SYMTAB_H)

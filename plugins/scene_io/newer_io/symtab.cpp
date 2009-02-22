#include "symtab.h"
#include <cstdio>

// Global variables defined in symtab.h
stack_item_type global_scope = NULL;
stack_type scope_stack;

//
// A dynamic object that is a scope...
//




void initialize_scope(stack_item_type& sit, const stack_item_type& parent_scope)
{
  sit->insert(scope_item("global", new scope_object(global_scope)));
  if( parent_scope != NULL )
  {
    sit->insert(scope_item("parent", new scope_object((stack_item_type&)parent_scope)));
  }
  else
  {
    sit->insert(scope_item("parent", new scope_object(global_scope)));
  }
}

void put_top(const std::string& name, const item_type& it)
{
  scope_type& st=*scope_stack.top();

  scope_type::iterator i=st.find(name);
  
  if( i == st.end() )
  {
    st.insert(scope_item(name,it));
  }
  else
  {
    //    fprintf(stderr,"symtab: warning: %s redefined\n",name.c_str());

    st.erase(i);
    
    st.insert(scope_item(name,it));
  }
}


item_type locate_reference(const std::string& name, const stack_item_type& table)
{
  item_type located_reference = NULL;

  scope_type::const_iterator location = table->find(name);
  if( location != table->end() )
  {
    located_reference = location->second;
  }
  return located_reference;
}

item_type locate_reference(const std::string& name)
{
  item_type located_instance = NULL;

  // locate the item by modifing the stack (popping off to a different stack)
  stack_type temp_stack;
  while( !scope_stack.empty() )
  {
    located_instance = locate_reference(name, scope_stack.top());
    if( located_instance != NULL )
    {
      break;
    }

    temp_stack.push(scope_stack.top());
    scope_stack.pop();
  }
  // restore the stack.
  while( !temp_stack.empty() )
  {
    scope_stack.push(temp_stack.top());
    temp_stack.pop();
  }

  // a warning could be printed if located_instance is NULL at this point.
  
  return located_instance;
}


void init_symtab()
{
  global_scope = new scope_type();

  initialize_scope(global_scope, stack_item_type(NULL));
  
  scope_stack.push(global_scope);
}



//
// Members for the scope_object class.
//
const char* scope_object::skcpType = "scope";
int scope_object::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  scope_type::iterator i = scope->find(rktNAME);
  
  if( i != scope->end() )
  {
    if( (rktNAME == "this") || (rktNAME == "global") || (rktNAME == "parent") )
    {
      // Don't allow the user to change these.
      return FX_ATTRIB_WRONG_VALUE;
    }      
    
    magic_pointer<Tdynamic_base> obj = convert_object (nVALUE, eTYPE);

    if( obj != NULL )
    {
      i->second = obj;
      return FX_ATTRIB_OK;
    }
    else
    {
      // The tweaker function couldn't figure out how to convert it...
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return Tdynamic_base::setAttribute (rktNAME, nVALUE, eTYPE);
  }
}

int scope_object::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{
  scope_type::const_iterator i = scope->find(rktNAME);
  
  if( i != scope->end() )
  {
    EAttribType eType = guess_type(i->second);
    if( convert_object (i->second, rnVALUE, eType) )
    {
      return FX_ATTRIB_OK;
    }
    else
    {
      return FX_ATTRIB_WRONG_VALUE;
    }
  }
  else
  {
    return Tdynamic_base::getAttribute (rktNAME, rnVALUE);
  }  
}

void scope_object::getAttributeList (TAttributeList& rtLIST) const
{
  Tdynamic_base::getAttributeList (rtLIST);
  
  for ( scope_type::const_iterator i = scope->begin();
	i != scope->end();
	++i )
  {
    rtLIST [i->first] = guess_type(i->second);
  }
}


/*
*  Copyright (C) 2000 Kevin Harris
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
//
// The parser for a simple, yet fairly useful scene language.
// Originally written by Kevin Harris (kpharris@users.sourceforge.net) on 06Jun2000.
//
// Revision History:
// 06Jun2000 (KH) wrote the basic file (without any actions)
// 07Jun2000 (KH) wrote some functions to use types.  It now functions as a
//           simple calculator (if print, warning, or error is used to display
//           the results).
//           Wrote the basic boolean actions.
//           Added a bunch of "fixme" comments with a macro.  Added a new
//           terminal symbol 'DEFINED', to check to see if a variable has a
//           definition (useful, and I forgot about it until I tried to write
//           some language-checking examples).
// 08Jun2000 (KH) Did some more trash...  Fixed some bugs in the unary
//           operators.  Added a unary '+'.
//           Added a simple symbol table.  Made 'type', 'attribs', etc work.
//           This is starting to seem like it could actually work!
//
// Todo:
//  Fix the 'FIXME' sections below.
//  Create something (find out how) to allow the scoping via the 'dots'.


%{
#define YYERROR_VERBOSE
/*
  basic types possible:
  boolean
  constant (real number)
  vector ([ X, Y, Z])
  string (text)
  string (name) --> reference
  reference
*/
  //#define USE_STREAMS
#include <stdlib.h>
#include <vector>
#include "dynamic_objects.h"
#include "dynamic_tweaker.h"
#include "symtab.h"
  
#include "hlapi/class_manager.h"
  
  
int yyerror(const char* c);
extern int yylex();
extern int scanner_line_number; 
//
// Functions to deal with types...
// 


// Print debug info stating what needs to be modified. 
#define FIXME(str) printf("parser(%d): FIXME!: %s\n",__LINE__,(str))

// A vector, used as a stack to see if something should be evaluated. 
static vector<bool> evaluate_scope_stack(1,true);
// performs a simple calculation based on the above vector to determine if
// something should be evaluated at the current level in the nesting. 
static bool evaluate (void);
 
magic_pointer<Tdynamic_base> current_object;

// TEMP!!!
#include <cstdio> 
extern FILE* yyin;
 
// END OF TEMP!! 
 
 %}

//
//  Keywords/values
//
%token CONSTANT   //
%token TEXT       //
%token STRING     //
%token INCLUDE    //
%token IF         //
%token ELSE       //
%token DEFINE     //
%token DEFINED    //
%token OBJECT     //
%token SCENE      //
%token WARNING    //
%token ERROR      //
%token PARAM      //
%token ENV        //
%token PRINT      //
%token TYPE       //
%token ATTRIBS    //
%token THIS       //
%token PARENT     //
%token GLOBAL     //

%token PLUS       //
%token MINUS      // 
%token TIMES      // 
%token DIV        //

%token PLUS_EQ    //
%token MINUS_EQ   //
%token TIMES_EQ   //
%token DIV_EQ     //

%token DOT        //

%token AND_L      //
%token OR_L       // 
%token NOT        //
%token EQUAL      //
%token NOT_EQ     //
%token GREATER_EQ //
%token LESS_EQ    //
%token GREATER    //
%token LESS       //

%token ASSIGN     //
%token DEBUG      //

%%


//
// Rules go here.
//
parsed_file:
any_trash
;

any_trash:
/* EMPTY -- Allows for empty files */ { }
| any_trash statement
;

useful_trash:
INCLUDE STRING
{
  if( evaluate() )
  {
    // fixme!!! I want to be able to open the file given by $2, and use it as
    // input to the parser/scanner.  What does this require?
    FIXME(string(string("inclusion of a file (named \"") + get_string($2) + "\")").c_str());
  }
}
| object_use
| definition
;

definition:
DEFINE TEXT ASSIGN TEXT
{
  if( evaluate() )
  {
    //    FIXME("I have no clue how to make the plugin work...");
    
    string class_name = get_string($4);
    TProcedural* instance = (TProcedural*)TClassManager::_newObject(class_name.c_str(),NULL);
    //    printf("--- Newly allocated object is a %s\n",instance->className().c_str());
    if( instance == NULL )
    {
      string   tMessage = string ("class ") +  class_name + " does not exist";
      yyerror (tMessage.c_str());
      exit (1);    
    }
    // create an instance of the object...
    current_object = new Tdynamic_object(instance, true);

    //    GOM.debug() << "--- current_object is:" << current_object << endl;
    
    // The dynamic object cloned it... So the memory needs to be freed (not anymore).
    //    delete instance;
    
    put_top(get_string($2), current_object);

    //    GOM.debug() << "--- object in symtab is:" << locate_reference(get_string($2)) << endl;
    //    GOM.debug() << "--- object name is:" << get_string($2) << endl;

    //  FIXME("entering a new scope");
    scope_stack.push(new scope_type);
  }
}
scope // creates a new named instance of whatever text is given
{
  if( evaluate() )
  {
    //  FIXME("leaving a scope");
    scope_stack.pop();
    
    current_object = NULL;
  }
}
| DEFINE TEXT ASSIGN object_use // creates a new object, by copying an existing object with possible modifications
{
  if( evaluate() )
  {
    //   FIXME("definition of a [modified] predefined object");
    put_top(get_string($2),$4);
  }
}
| DEFINE TEXT ASSIGN expression ';' // allows definitions of named constants and stored strings
{
  if( evaluate() )
  {
    put_top(get_string($2), $4);
  }
}
;

object_use:
OBJECT TEXT
{
  if( evaluate() )
  {
    //  FIXME("entering a new scope");
    scope_stack.push(new scope_type);

    current_object = new Tdynamic_object((TProcedural*)get_object($2),false);
  }  
}
scope // use an object with the name given by the text
{
  if( evaluate() )
  {
    //  FIXME("leaving a scope");
    scope_stack.pop();    
    current_object = NULL;
  }
}
;

scope:
'{' '}'
| '{' statement_list '}'
;

statement_list:
statement
| statement_list statement
;

statement:
';'
| useful_trash
| if_head
{
  evaluate_scope_stack.erase(evaluate_scope_stack.end() - 1);
}
| if_head ELSE
{
  if( evaluate_scope_stack.size() >= 2 )
  {
    // If the if portion was the same as the previous if (outside), cary on.
    evaluate_scope_stack[evaluate_scope_stack.size() - 1] = !evaluate() && evaluate_scope_stack[evaluate_scope_stack.size()-2];
  }
}
scope
{
  evaluate_scope_stack.erase(evaluate_scope_stack.end() - 1);
}
| DEBUG expression ';'
{
  if( evaluate() )
  {
    //    FIXME("enter a call to printDebug for an object in an expression");
    get_object($2)->printDebug();
  }
}
| user_message
| expression ASSIGN expression ';'
{
  if( evaluate() )
  {
    FIXME("assignment to something");
  }
}
| expression ASSIGN object_use ';'
{
  if( evaluate() )
  {
    FIXME("assignment to something");
  }
}
| expression ASSIGN TEXT scope
{
  if( evaluate() )
  {
    FIXME("assignment to something");
  }
}
| expression PLUS_EQ expression ';'
{
  if( evaluate() )
  {
    FIXME("assignment (+=) to something");
  }
}
| expression MINUS_EQ expression ';'
{
  if( evaluate() )
  {
    FIXME("assignment (-=) to something");
  }
}
| expression TIMES_EQ expression ';'
{
  if( evaluate() )
  {
    FIXME("assignment (*=) to something");
  }
}
| expression DIV_EQ expression ';'
{
  if( evaluate() )
  {
    FIXME("assignment (/=) to something");
  }
}
;

user_message:
WARNING expression ';'
{
  if( evaluate() )
  {
    fprintf(stderr,"user warning: line %d: \"%s\"\n",scanner_line_number,get_string($2).c_str());
  }
}
| ERROR expression ';'
{
  if( evaluate() )
  {
    fprintf(stderr,"user error: line %d: \"%s\"\n",scanner_line_number,get_string($2).c_str());
    exit(1);
  }
}
| PRINT expression ';'
{
  if( evaluate() )
  {
    fprintf(stdout,"%s\n",get_string($2).c_str());
  }
}
;

if_head:
IF '(' expression ')'
{
  if( get_bool($3) )
  {
    if( evaluate() )
    {
      evaluate_scope_stack.push_back(true);
    }
    else
    {
      evaluate_scope_stack.push_back(false);      
    }
  }
  else
  {
    evaluate_scope_stack.push_back(false);    
  }
}
scope
{
  // nothing here
}
;

expression:
prec_8
| TYPE expression {
  if( $2 != NULL )
  {
    string base_string = $2->getDynamicType();
    $$ = new Tdynamic_string (base_string);
  }
  else
  {
    $$ = new Tdynamic_string("undefined");
  }
}
| ATTRIBS expression
{
  string attr_str = "";
  if( evaluate() )
  {
    //    FIXME("get an attribute list for something in a reference");
    attr_str = "( ";
    TAttributeList attr_list;

    
    $2->getAttributeList(attr_list);
    for(TAttributeList::const_iterator i = attr_list.begin();
	i != attr_list.end();
	++i)
    {
      attr_str += i->first + " ";
    }
    attr_str += ")";
  }
  $$ = new Tdynamic_string(attr_str);
}
;

prec_8:
prec_7
| prec_8 AND_L prec_7 { $$ = new Tdynamic_bool(get_bool($1) && get_bool($3)); }
;

prec_7:
prec_6
| prec_7 OR_L prec_6 { $$ = new Tdynamic_bool(get_bool($1) || get_bool($3)); }
;

prec_6:
prec_5
| prec_6 EQUAL prec_5
{
  if( is_real($1) )
  {
    $$ = new Tdynamic_bool(get_real($1) == get_real($3));
  }
  else if( is_bool($1) )
  {
    $$ = new Tdynamic_bool(get_bool($1) == get_bool($3));
  }
  else if( is_vector($1) )
  {
    $$ = new Tdynamic_bool(get_vector($1) == get_vector($3));
  }        
}
| prec_6 NOT_EQ prec_5
{
  if( is_real($1) )
  {
    $$ = new Tdynamic_bool(get_real($1) != get_real($3));
  }
  else if( is_bool($1) )
  {
    $$ = new Tdynamic_bool(get_bool($1) != get_bool($3));
  }
  else if( is_vector($1) )
  {
    $$ = new Tdynamic_bool(get_vector($1) != get_vector($3));
  }          
}
;

prec_5:
prec_4
| prec_4 GREATER_EQ prec_4 { $$ = new Tdynamic_bool(get_real($1) >= get_real($3)); }
| prec_4 GREATER prec_4 { $$ = new Tdynamic_bool(get_real($1) > get_real($3)); }
| prec_4 LESS_EQ prec_4 { $$ = new Tdynamic_bool(get_real($1) <= get_real($3)); }
| prec_4 LESS prec_4 { $$ = new Tdynamic_bool(get_real($1) < get_real($3)); } 
;

prec_4:
prec_3
| prec_4 PLUS prec_3
{
  if( is_string($1) || is_string($3) )
  {
    $$ = new Tdynamic_string(get_string($1) + get_string($3));
  }
  else
  {
    $$ = add($1,$3);
    if( $$ == NULL )
    {
      fprintf(stderr,"parser: line %d: addition of %s and %s failed\n",
	      scanner_line_number, $1->getDynamicType(), $3->getDynamicType()); 
      exit(1);
    }
  }
} 
| prec_4 MINUS prec_3
{
  $$ = sub($1,$3);
  if( $$ == NULL )
  {
    fprintf(stderr,"parser: line %d: subtraction of %s and %s failed\n",
	    scanner_line_number, $1->getDynamicType(), $2->getDynamicType());
    exit(1);
  }
} 
;

prec_3:
prec_2
| prec_3 TIMES prec_2
{
  $$ = mul($1,$3);
  if( $$ == NULL )
  {
    fprintf(stderr,"parser: line %d: multiplication of %s and %s failed\n",
	    scanner_line_number, $1->getDynamicType(), $2->getDynamicType());
    exit(1);
  }
}
| prec_3 DIV prec_2
{
  $$ = div($1,$3);
  if( $$ == NULL )
  {
    fprintf(stderr,"parser: line %d: addition of %s and %s failed\n",
	    scanner_line_number, $1->getDynamicType(), $2->getDynamicType());
    exit(1);
  }
}
;

prec_2:
prec_1
| NOT prec_2  { $$ = new Tdynamic_bool(!get_bool($2)); }
| PLUS prec_2  { $$ = $2; } 
| MINUS prec_2
{
  if( is_real($2) )
  {
    $$ = new Tdynamic_real(-get_real($2));
  }
  else
  {
    $$ = new Tdynamic_vector(-get_vector($2));
  }
}
;

prec_1:
dot_chain
{
  $$ = $1;
  Tdotted_list* list_ptr = (Tdotted_list*)$1.get_pointer();
  if( list_ptr->get_chain_length() == 0)
  {
    $$ = list_ptr->get_base();
  }
  
  if( $1 == NULL )
  {
    $$ = new Tdynamic_base();
  }
}
| element
;

dot_chain:
ref_element
{
  if( is_string($1) )
  {
    $$ = new Tdotted_list(locate_reference(get_string($1)));
  }
  else
  {
    $$ = new Tdotted_list($1);    
  }
}
| dot_chain DOT text_element
{
  if( evaluate() )
  {
    //    FIXME("change scope and create a reference because of a dot (.)");
    TAttributeList tlist ;
    $1->getAttributeList (tlist);
    string element_name = get_string($3);
    const Tdotted_list* parent_list = (const Tdotted_list*)$1.get_pointer();

    //    printf("base=%s list=",parent_list->get_base()->getDynamicType());
    
    if( element_name == "parent" )
    {
      if( tlist.find(element_name) == tlist.end() )
      {
	if( parent_list->get_chain_length() <= 1)
	{
	  //	  printf("(%s) ---parent of <=1 length chain\n", (parent_list->get_chain_length() == 1)?parent_list->get_chain()[0].c_str():"");
	  $$ = new Tdotted_list(new scope_object(global_scope));
	}
	else
	{
	  FIXME("faked parent attribute");
	  /*
	  // Since the item does not have an element named parent, fake one by
	  // copying the entire list of strings except for the last.
	  magic_pointer<Tdotted_list> result_list = new Tdotted_list(parent_list->get_base());
	  int i = 0;
	  const vector<string>& str_list = parent_list->get_chain();
	  for(i = 0; i < int(parent_list->get_chain_length()) - 1; ++i)
	  {
	    printf("%s ",str_list[i].c_str());
	    result_list = new Tdotted_list(*result_list, str_list[i]);
	  }
	  printf("(%s) ",str_list[i].c_str());
	  printf("---faked parent\n");	  
	  $$ = result_list->clone();
	  */
	  string error_msg = string("element has no attribute named ") + element_name;
	  yyerror(error_msg.c_str());
	  exit(1);	  
	}
      }
      else
      {
	$$ = new Tdotted_list(*parent_list, element_name);
	/*
	const vector<string>& str_list = parent_list->get_chain();	  
	for(unsigned i = 0; i < str_list.size(); ++i)
	{
	  printf("%s ",str_list[i].c_str());
	}
	printf("+%s ",element_name.c_str());
	printf("---appended parent\n");
	*/
      }
    }
    else
    {
      if( tlist.find(element_name) == tlist.end() )
      {
	string error_msg = string("element has no attribute named ") + element_name;
	yyerror(error_msg.c_str());
	exit(1);
      }
      $$ = new Tdotted_list(*parent_list, element_name);
      /*
      const vector<string>& str_list = parent_list->get_chain();	  
      for(unsigned i = 0; i < str_list.size(); ++i)
      {
	printf("%s ",str_list[i].c_str());
      }
      printf("+%s ",element_name.c_str());
      printf("---attribute parent\n");
      */
    }
  }
}
;

ref_element:
text_element
| SCENE
| GLOBAL
{
  $$ = new scope_object(global_scope);
}

element:
STRING
| PARAM STRING
{
  if( evaluate() )
  {
    FIXME("recovering a paramater (how?)");
  }
}
| ENV element
{
  const char* env_text = getenv(get_string($2).c_str());
  if( env_text != NULL )
  {
    // fixme!!! I want to be able to evaluate the text... using it as input to
    // the scanner/parser.  What does this require?
    FIXME(string(string("insert code to evaluate the text (") + get_string($2) + ")").c_str());
    $$ = new Tdynamic_string(env_text);
  }
  else
  {
    yyerror(string(get_string($2) + " is not an environment variable").c_str());
    $$ = new Tdynamic_string("");
  }
}
| DEFINED element
{
  FIXME("check to see if an element is defined in any of the current scopes (in the symtabs");
  $$ = new Tdynamic_bool(false);
}
| user_vector
| CONSTANT
| '(' expression ')' { $$ = $2; }
| THIS
{
  //  $$ = new Tdynamic_string("this");
  $$ = current_object;
}
;

text_element:
TEXT
{
  //  FIXME(string(string("perform a lookup of \"") + get_string($1) + "\"").c_str());
  $$ = $1;
}
| PARENT
{
  $$ = new Tdynamic_string("parent");
}

;

user_vector:
'[' expression ',' expression ',' expression ']' { $$ = new Tdynamic_vector(TVector(get_real($2),
										    get_real($4),
										    get_real($6))); }										    
;

%%

//
// Trash (functions) goes here.
//
#if defined(USE_STREAMS)
#include <iostream>

ostream& operator <<(ostream& o, const Tdynamic_base& tdb)
{
  o << tdb.getDynamicType();
  return o;
}
#endif // defined(USE_STREAMS)



bool evaluate (void)
{
  return(evaluate_scope_stack[evaluate_scope_stack.size() - 1]);
}

int yyerror(const char* text)
{
  fprintf(stderr,"parser error: line %d: %s\n", scanner_line_number,text);
  return(0);
}

int main(int argc, char** argv)
{
  yyin = stdin;
  init_symtab();
  yyparse();
}

/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  Copyright (C) 2001, 2002 Kevin Harris
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

/*
  TODO: Fix the FIXMEs. (added 15Oct2001 -- KH)
        Some of the things labeled fixme may have already been fixed and they
	should be checked for correctness/completeness.  In any case, the
	FIXMEs were labeled that way in the first place either because they
	were not possible to do with the structure of things at the time, or
	because I did not know a good way to approach them (or if it should be
	done) at the time they were labeled as such. 
  
        Real scoping. (added 15Oct2001 -- KH)
        Change the datamap into a stack of datamaps.
        This will allow defining of objects within a scope without affecting
	other scopes (would be great for aggregates, as an object can be
	defined once within and modified [translated/scaled] any number of
	times within the aggregate and nowhere else). 

        Attribute recovery. (added 15Oct2001 -- KH)
	If a name is NOT within a datamap, attempt to check the attribute list
	for the object corresponding to that scope before checking a higher
	scope.  Note the possibility to obscure an attribute by defining
	something of the same name.

	Potentially remove the define keyword. (added 15Oct2001 -- KH)
	It should be sufficient to use '=' for all operations instead of making
	the distinction of attrbutes and objects.  It may be of some bennefit
	to keep the define keyword and also allow the '=' form, as this could
	allow defining of some read-only values (such as global colors, shapes,
	etc), where it would be important to know when they are being
	overritten (possibly by mistake).

	Error handling. (added 15Oct2001 -- KH)
	If an error is detected, the resulting parsed scene should NOT be
	allowed to continue through the rendering process (It could be nice to
	activate an editor in the gui to edit the scene file at the point of
	the error -- this may require column tracking as well, which would slow
	down the parser even more).

 */

/*
  Notes:

    Function recovery -- (KH 15Oct2001) The reason that I query each object for
    its functions instead of storing the list along with it is that an object
    could potentially offer different functions based on some internal state
    (ie. the CSG object may offer different functions if it was a union than if
    it was an intersection.
 */

%{

  //#define REDUCTION_REPORTING
  
#include <map>
#include <string>
#include <iostream>
#include "llapi/llapi_all.h"
#include "hlapi/hlapi_all.h"
#include "hlapi/class_manager.h"
#include "hlapi/plugins_all.h"
#include "parser_defs.h"
#include "rt_io.h"
#include "llapi/object_required.h"

#include "parsed_types.h"
#include "attribute_math.h"
#include "language_functions.h"
#include "attrib_tweak.h"

#define YYDEBUG 1
#define YYERROR_VERBOSE 1

//---------------------------------------------------------------------------
typedef TSceneRT::BASE_OBJECT_TYPE BASE_OBJECT_TYPE;
typedef TSceneRT::attrib_type attrib_type;

// Fix to STL's pop() 
#define POP()           top(); TSceneRT::_tDataStack.pop()  

#define DATA		(TSceneRT::_tDataStack.top())
#define DATAMAP         (TSceneRT::_tDataMap)
#define DATASTACK       (TSceneRT::_tDataStack) 
#define SCENE		(TSceneRT::_ptParsedScene)
#define PARENT_OBJECT   (TSceneRT::_ptParent)
#define WORLD           (TSceneRT::_ptWorld)
extern void rt_error (const string& rksTEXT);
extern void rt_warning (const string& rksTEXT);
//---------------------------------------------------------------------------

  
static BASE_OBJECT_TYPE NewObject (const string& rktCLASS, const BASE_OBJECT_TYPE& pktPARENT);

static void CreateObject (const string& rktCLASS, const string& rktDEF_CLASS);

static magic_pointer<TAttribute> Instance(const string& s);
 
static void InitObjects (void);

static void report_reduction(const string& s);

static void FIXME(const string& s) { cerr << "FIXME: " << s << endl; }
%}

%token <gValue> T_BOOL
%token <dValue> T_REAL
%token <iValue> T_INTEGER
%token <sIdent> T_IDENTIFIER
%token <sIdent> T_QUOTED_STRING

/* "Reserved word" tokens.
   Modified to all act the same as identifiers (KH--07Aug2000)  */
%token <sIdent> T_BLUE
%token <sIdent> T_CAMERA
%token <sIdent> T_CLASS
%token <sIdent> T_DEFINE
%token <sIdent> T_EXTENDS
%token <sIdent> T_FILTER
%token <sIdent> T_GREEN
%token <sIdent> T_LIGHT
%token <sIdent> T_OUTPUT
%token <sIdent> T_RED
%token <sIdent> T_RENDERER

%token <gValue> AND_L
%token <gValue> OR_L
%token <gValue> EQUAL
%token <gValue> NOT_EQ
%token <gValue> GREATER
%token <gValue> GREATER_EQ
%token <gValue> LESS
%token <gValue> LESS_EQ
%token <sIdent> PARAM
%token <sIdent> DEFINED
%token <sIdent> THIS


/* Tokens to allow user requested information about types/attribute lists.
   Added 06/Aug/2000 */ 
%type <sIdent> reserved_words
%type <sIdent> potential_name
%type <ptAttribute> instance;

%type <sIdent> name
%type <sIdent> class
%type <ptColor> color
%type <ptVector> vector3
%type <ptVector2> vector2

%type <ptAttribute> function_call;
%type <ptAttribute> expression;
%type <ptAttribute> prec_8;
%type <ptAttribute> prec_7;
%type <ptAttribute> prec_6;
%type <ptAttribute> prec_5;
%type <ptAttribute> prec_4;
%type <ptAttribute> prec_3;
%type <ptAttribute> prec_2;
%type <ptAttribute> prec_1;

%left '+' '-'
%left '*' '/'
//%right UNARY_MINUS

%start everything

%%

everything		: /* Nothing */
                          {
			    report_reduction("everything <-- nothing");
			  }
			| everything expression ';'
                          {
			    report_reduction("everything <-- everything expression ';'");
			    magic_pointer<TAttribObject> ptobj = get_object($2);
			    if( !!ptobj )
			    {
			      magic_pointer<TObject> obj = ptobj->tValue;
			      if( !!obj )
			      {
				if( !WORLD->containsObject( obj ) )
				{
				  //				  cout << "Adding instance of " << obj->className() << " to world." << endl;
				  WORLD->add ( obj );
				}
			      }
			    }
			    else
			    {
			      magic_pointer<TProcedural> proc = get_procedural_var($2, false);
			      if( !!proc )
			      {
				FIXME("Potentially add instance (" + $2->toString() + " to the global scene");
			      }
			    }			      
			  }
			| everything definition
                          {
			    report_reduction("everything <-- everything definition");
			  }
			;
                        
definition		: T_DEFINE name expression ';'
                          {
			    report_reduction("definition <-- DEFINE name expression ;");
			    report_reduction(string("definition <-- DEFINE ") +
					     $2 + " " + $3->toString());

			    if( DATAMAP.find($2) != DATAMAP.end() )
			    {
			      rt_warning(string($2) + " redefined here");
			      rt_warning("previously defined here: " + DATAMAP[$2].first);
			    }
			    cout << "Defining \"" << string($2) << "\"" << endl;
			    
			    char buffer[1024];
			    sprintf(buffer,"%s line %d",
				    TSceneRT::_tInputFileName.c_str(),
				    int(TSceneRT::_dwLineNumber));
			    DATAMAP[$2] = pair<string,attrib_type>(string(buffer),$3);
			  }
                        | T_DEFINE reserved_words name instance ';'
                          {
			    report_reduction("definition <-- DEFINE reserved_words name instance");
			    cerr << "Warning: definition on line "
			         << TSceneRT::_dwLineNumber
				 << " should not have \"" << $2 << "\" anymore"
				 << endl;

			    if( DATAMAP.find($3) != DATAMAP.end() )
			    {
			      rt_warning(string($3) + " redefined here");
			      rt_warning("previously defined here: " + DATAMAP[$3].first);
			    }
			    char buffer[1024];
			    sprintf(buffer,"%s line %d",
				    TSceneRT::_tInputFileName.c_str(),
				    int(TSceneRT::_dwLineNumber));
			    DATAMAP[$2] = pair<string,attrib_type>(string(buffer),$4);
			  }
			;

instance                : name
                          {
			    report_reduction("instance <-- name");
			    report_reduction(string("instance <-- ") + $1);			    
			    $$ = Instance($1);
                          }
                        | class
			  {
			    //			    cout << "Creating object..." << endl;
			    CreateObject($1,"");
                          }
                          param_block
                          {
			    report_reduction("instance <--  class { params }");
			    report_reduction(string("instance <-- ") + DATA->toString());
			    
			    //			    cout << "Type is " << DATA->AttributeName() << endl;
			    $$ = DATASTACK.POP();
			  }
;

param_block             : '{' params '}'
                          {
			    report_reduction("param_block <-- { params }");
			  }
                        | '{' '}'
                          {
			    report_reduction("param_block <-- { }");
			  }
;

expression:
                        prec_8
                          {
			    $$ = $1;
			    report_reduction("expression <-- prec_8");
			    report_reduction("expression <-- " + $1->toString());
                          }
;

prec_8:
                        prec_7
                        {
			  report_reduction("prec_8 <-- prec_7");
			  report_reduction("prec_8 <-- " + $1->toString());
			  $$ = $1;
			}
			| prec_8 OR_L prec_7
                        {
			  report_reduction("prec_8 <-- prec_8 OR prec_7");
			  report_reduction("prec_8 <-- " + $1->toString() + " OR " + $3->toString());
			  $$ = (user_arg_type)new TAttribBool(check_get_bool($1) ||
					       check_get_bool($3));
			}
;

prec_7:
                        prec_6
                        {
			  report_reduction("prec_7 <-- prec_6");
			  report_reduction("prec_7 <-- " + $1->toString());			  
			  $$ = $1;
			}
                        | prec_7 AND_L prec_6
                        {
			  report_reduction("prec_7 <-- prec_7 AND prec_6");
			  report_reduction("prec_7 <-- " + $1->toString() + " AND " + $3->toString());
			  $$ = (user_arg_type)new TAttribBool(check_get_bool($1) &&
					       check_get_bool($3));
			}
;

prec_6:
			
                        prec_5
                        {
			  report_reduction("prec_6 <-- prec_5");
			  report_reduction("prec_6 <-- " + $1->toString());			  
			  $$ = $1;
			}
                        | prec_6 EQUAL prec_5
                        {
			  report_reduction("prec_6 <-- prec_6 EQUAL prec_5");
			  if( !types_match($1, $3 ) )
			  {
			    rt_error( ("Cannot convert " + EAttribType_to_str($3->eType) +
				       " to " + EAttribType_to_str($1->eType)) );
			  }
			  if( $1->eType == FX_REAL )
			  {
			    $$ = (user_arg_type)new TAttribBool(check_get_real($1) == check_get_real($3));
			  }
			  else if( $1->eType == FX_BOOL )
			  {
			    $$ = (user_arg_type)new TAttribBool(check_get_bool($1) ==
						 check_get_bool($3));
			  }
			  else if( $1->eType == FX_VECTOR )
			  {
			    $$ = (user_arg_type)new TAttribBool(get_vector($1)->tValue ==
						 get_vector($3)->tValue);
			  }
			  else if( $1->eType == FX_VECTOR2 )
			  {
			    $$ = (user_arg_type)new TAttribBool(get_vector2($1)->tValue ==
						 get_vector2($3)->tValue);
			  }
			  else if( $1->eType == FX_STRING || $1->eType == FX_STRING_LIST )
			  {
			    $$ = (user_arg_type)new TAttribBool(check_get_string($1) ==
						 check_get_string($3));	  
			  }
			  else if( $1->eType == FX_INTEGER )
			  {
			    $$ = (user_arg_type)new TAttribBool(get_int($1)->tValue ==
						 get_int($3)->tValue);	  
			  }			  
			  else
			  {
			    rt_error("I can't compare a " + EAttribType_to_str($3->eType));
			  }
			}
                        | prec_6 NOT_EQ prec_5
                        {
			  report_reduction("prec_6 <-- prec_6 NOT_EQ prec_5");
			  if( !types_match($1, $3 ) )
			  {
			    rt_error( ("Cannot convert " + EAttribType_to_str($3->eType) +
				       " to " + EAttribType_to_str($1->eType)) );
			  }
			  if( $1->eType == FX_REAL )
			  {
			    $$ = (user_arg_type)new TAttribBool(check_get_real($1) !=
						 check_get_real($3));
			  }
			  else if( $1->eType == FX_BOOL )
			  {
			    $$ = (user_arg_type)new TAttribBool(check_get_bool($1) !=
						 check_get_bool($3));
			  }
			  else if( $1->eType == FX_VECTOR )
			  {
			    $$ = (user_arg_type)new TAttribBool(get_vector($1) != get_vector($3));
			  }
			  else if( $1->eType == FX_VECTOR2 )
			  {
			    $$ = (user_arg_type)new TAttribBool(get_vector2($1) != get_vector2($3));
			  }
			  else if( $1->eType == FX_STRING || $1->eType == FX_STRING_LIST )
			  {
			    $$ = (user_arg_type)new TAttribBool(check_get_string($1) != check_get_string($3));	  
			  }
			  else if( $1->eType == FX_INTEGER )
			  {
			    $$ = (user_arg_type)new TAttribBool(get_int($1)->tValue == get_int($3)->tValue);	  
			  }
			  else
			  {
			    rt_error("I can't compare a " + EAttribType_to_str($3->eType));
			  }
			}
;

prec_5:
			prec_4
                        {
			  report_reduction("prec_5 <-- prec_4");
			  report_reduction("prec_5 <-- " + $1->toString());			  
			  
			  $$ = $1;
			}
			| prec_4 GREATER_EQ prec_4
                        {
			  report_reduction("prec_4 <-- prec_6 >= prec_5");
			  $$ = (user_arg_type)new TAttribBool(check_get_real($1) >= check_get_real($3));
			}
                        | prec_4 GREATER prec_4
                        {
			  report_reduction("prec_4 <-- prec_6 > prec_5");
			  $$ = (user_arg_type)new TAttribBool(check_get_real($1) > check_get_real($3));
			}
                        | prec_4 LESS_EQ prec_4
                        {
			  report_reduction("prec_4 <-- prec_6 <= prec_5");
			  $$ = (user_arg_type)new TAttribBool(check_get_real($1) <= check_get_real($3));
			}
                        | prec_4 LESS prec_4
                        {
			  report_reduction("prec_4 <-- prec_6 < prec_5");
			  $$ = (user_arg_type)new TAttribBool(check_get_real($1) < check_get_real($3));
			} 
;

prec_4:
			prec_3
                        {
			  report_reduction("prec_4 <-- prec_3");
			  report_reduction("prec_4 <-- " + $1->toString());			  
			  $$ = $1;
			}
                        | prec_4 '+' prec_3
                        {

			  report_reduction("prec_4 <-- prec_4 + prec_3");
			  report_reduction("prec_4 <-- " + $1->toString() + " + " + $3->toString());
			  
			  $$ = add($1,$3);
			  if( !$$ )
			  {
			    rt_error("addition of " + EAttribType_to_str($1->eType) +
				     " and " + EAttribType_to_str($3->eType) + " failed");
			  }
			} 
                        | prec_4 '-' prec_3
                        {
			  report_reduction("prec_4 <-- prec_4 - prec_3");
			  report_reduction("prec_4 <-- " + $1->toString() + " - " + $3->toString());			  
			  $$ = sub($1,$3);
			  if( !$$ )
			  {
			    rt_error("subtraction of " + EAttribType_to_str($1->eType) +
				     " and " + EAttribType_to_str($3->eType) + " failed");
			  }
			} 
;

prec_3:
			prec_2
                        {
			  report_reduction("prec_3 <-- prec_2");
			  report_reduction("prec_3 <-- " + $1->toString());			  
			  $$ = $1;
			}			
			| prec_3 '*' prec_2
                        {
			  report_reduction("prec_3 <-- prec_3 * prec_2");
			  report_reduction("prec_4 <-- " + $1->toString() + " * " + $3->toString());			  
			  
			  $$ = mul($1,$3);
			  if( !$$ )
			  {
			    rt_error("multiplication of " + EAttribType_to_str($1->eType) +
				     " and " + EAttribType_to_str($3->eType) + " failed");
			  }
			}
                        | prec_3 '/' prec_2
                        {
			  report_reduction("prec_3 <-- prec_3 / prec_2");
			  report_reduction("prec_4 <-- " + $1->toString() + " / " + $3->toString());			  
			  
			  $$ = div($1,$3);
			  if( !$$ )
			  {
			    rt_error("division of " + EAttribType_to_str($1->eType) +
				     " and " + EAttribType_to_str($3->eType) + " failed");
			  }
			}
;

prec_2:
			prec_1
                        {
			  report_reduction("prec_2 <-- prec_1");
			  report_reduction("prec_2 <-- " + $1->toString());			  
			  $$ = $1;
			}			
			| '!' prec_2
                        {
			  report_reduction("prec_2 <-- ! prec_2");
			  report_reduction("prec_2 <-- ! " + $2->toString());

			  $$ = (user_arg_type)new TAttribBool(!check_get_bool($2));
			}
                        | '+' prec_2
                        {
			  report_reduction("prec_2 <-- + prec_2");
			  report_reduction("prec_2 <-- + " + $2->toString());
			  
			  $$ = $2;
			} 
                        | '-' prec_2
                        {
			  report_reduction("prec_2 <-- - prec_2");
			  report_reduction("prec_2 <-- - " + $2->toString());
			  
			  $$ = sub((user_arg_type)new TAttribInt(0), $2);
			  if( !$$ )
			  {
			    rt_error("negation of " + EAttribType_to_str($2->eType) + " failed");
			  }			  
			}
;

prec_1:
			T_QUOTED_STRING
                        {
			  report_reduction("prec_1 <-- quoted_string");
			  report_reduction("prec_1 <-- " + string($1));
			  
			  $$ = (user_arg_type)new TAttribString($1);
			}
                        | PARAM prec_1
                        {
			  report_reduction("prec_1 <-- PARAM prec_1");
			  
			  FIXME("recovering a paramater (how?)");
			}
                        | DEFINED name
                        {
			  report_reduction("prec_1 <-- DEFINED name");

			  if( DATAMAP.find($2) != DATAMAP.end() )
			  {
			    $$ = (user_arg_type)new TAttribBool(true);
			  }
			  else
			  {
			    $$ = (user_arg_type)new TAttribBool(false);
			  }
			}
                        | T_BOOL
                        {
			  report_reduction("prec_1 <-- BOOL");
			  
			  $$ = (user_arg_type)new TAttribBool($1);
			}
                        | T_INTEGER
                        {
			  report_reduction("prec_1 <-- INTEGER");
			  
			  $$ = (user_arg_type)new TAttribInt($1);
			}
                        | T_REAL
                          {
			    report_reduction("prec_1 <-- REAL");
			    
			    $$ = (user_arg_type)new TAttribReal($1);
                          }

                        | '(' expression ')'
                        {
			  report_reduction("prec_1 <-- ( expression )");
			  report_reduction("prec_1 <-- ( " + $2->toString() + " )");

			  $$ = $2;
			}
                        | color
                        {
			  report_reduction("prec_1 <-- color");
			  $$ = (user_arg_type)new TAttribColor(*$1);
			}
                        | vector3
                        {
			  report_reduction("prec_1 <-- vector3");
			  $$ = (user_arg_type)new TAttribVector(*$1);
			}
                        | vector2
                        {
			  report_reduction("prec_1 <-- vector2");
			  $$ = (user_arg_type)new TAttribVector2(*$1);
			}
                        | THIS
                        {
			  report_reduction("prec_1 <-- THIS");
			  $$ = DATA;
			}
                        | instance
                        {
			  report_reduction("prec_1 <-- instance");
			  $$ = $1;			  
                        }
                        | function_call
;

function_call           : potential_name '(' ')'
                        {
			  report_reduction("function_call <-- potential_name ( )");
			  report_reduction("function_call <-- " + string($1) +  "( )");

#if defined(DEBUG_IT)
			  rt_error("about to call a function");
#endif /* defined(DEBUG_IT) */
			  
			  // Lookup using all objects in the current stack,
			  // then check the global table... 
			  TUserFunctionMap functions = all_user_functions();

			  if( functions.find($1) != functions.end() )
			  {
			    user_arg_vector empty_args;
			    $$ = functions[$1]->call(empty_args);
			  }
			  else
			  {
			    rt_error("function " + string($1) + " does not exist");
			    $$ = (user_arg_type)new TAttribute();
			  }
			}
                        | potential_name '(' expression ')'
                        {
			  report_reduction("function_call <-- potential_name ( expression )");
			  report_reduction("function_call <-- " + string($1) + "( " + $3->toString() + " )");
			  
			  
#if defined(DEBUG_IT)
			  rt_error("about to call a function");
#endif /* defined(DEBUG_IT) */
			  
			  // Lookup using all objects in the current stack,
			  // then check the global table...
			  TUserFunctionMap functions = all_user_functions();
			  
			  if( functions.find($1) != functions.end() )
			  {
			    user_arg_vector args;
			    args.push_back($3);
			    $$ = functions[$1]->call(args);

			  }
			  else
			  {
			    rt_error("function " + string($1) + " does not exist");
			    $$ = (user_arg_type)new TAttribute();
			  }			    
			}
                        | potential_name '(' expression ',' expression ')'
                        {
			  report_reduction("function_call <-- potential_name ( expression , expression )");
			  report_reduction("function_call <-- " + string($1) + "( " + $3->toString() + "," + $5->toString() + " )");
			  
			  
#if defined(DEBUG_IT)
			  rt_error("about to call a function");
#endif /* defined(DEBUG_IT) */
			  
			  // Lookup using all objects in the current stack,
			  // then check the global table...
			  TUserFunctionMap functions = all_user_functions();
			  
			  if( functions.find($1) != functions.end() )
			  {
			    user_arg_vector args;
			    args.push_back($3);
			    args.push_back($5);			    
			    $$ = functions[$1]->call(args);

			  }
			  else
			  {
			    rt_error("function " + string($1) + " does not exist");
			    $$ = (user_arg_type)new TAttribute();
			  }			    
			}
;


color                   : '{' T_RED expression T_GREEN expression T_BLUE expression '}'
                          {
			    report_reduction("color <-- { RED expression GREEN expression BLUE expression }");
			    report_reduction("color <-- { RED " + $3->toString() +
					     " GREEN " + $5->toString() +
					     " BLUE " + $7->toString() + " }");

			    double r = check_get_real($3);
			    double g = check_get_real($5);
			    double b = check_get_real($7);

			    cout << "r=" << r << " g=" << g << " b=" << b << endl;
			    TColor* c = new TColor(r,g,b);
			    cerr << "Here's what was really created: ";
			    c->printDebug(""); cerr << endl;
			    
			    $$ = magic_pointer<TColor>(c);
			  }
                       ;

vector3                 : '<' expression ',' expression ',' expression '>'
			  {
			    report_reduction("vector3 <-- < expression , expression , expression >");
			    TVector tVector;
			    double x = check_get_real($2);
			    double y = check_get_real($4);
			    double z = check_get_real($6);
#if defined(DEBUG_IT)
			    cout << "Creating vector ("
				 << x << ","
				 << y << ","
				 << z << ")" << endl;
#endif
			    tVector.set (x,y,z);
                            $$ = (magic_pointer<TVector>)new TVector(tVector);
			  }
			;
vector2			: '<' expression ',' expression '>'
			  {
			    report_reduction("vector2 <-- < expression , expression >");
			    TVector2 tVector2;
			    tVector2.set (check_get_real($2), check_get_real($4));
                            $$ = (magic_pointer<TVector2>)new TVector2(tVector2);
			  }
			;

name			:
                        /*
			  {
			    report_reduction("name <-- nothing");
			    $$ = "";
			  }
			|
                        Nothing */			
                        T_IDENTIFIER
			  {
			    report_reduction("name <-- IDENTIFIER");
			    $$ = $1;
			  }
			;

class			: /* Nothing 
			  {
			  
			    report_reduction("class <-- nothing");
			    $$ = "";
			  }
			| */
                          T_IDENTIFIER /*':' T_EXTENDS */
			  {
			    report_reduction("class <-- : EXTENDS IDENTIFIER");
                            if ( DATAMAP.find ($1) == DATAMAP.end() )
                            {
			      yyerror ("trying to extend from non existing object");
			      exit (1);
                            }

			    //			    cout << "the type of the parent is " << DATAMAP [$1].second->AttributeName() << endl;
                            PARENT_OBJECT = attr_to_base(DATAMAP [$1].second);
			    //			    cout << "the parent's classname is " << PARENT_OBJECT->className() << endl;
			    $$ = PARENT_OBJECT->className();
			  }
			| T_CLASS T_IDENTIFIER
			  {
			    report_reduction("class <-- : CLASS IDENTIFIER");
			    PARENT_OBJECT = (magic_pointer<TBaseClass>)NULL;
			    $$ = $2;
			  }
			;

params			: /* Nothing  
                          {
			    report_reduction("params <-- nothing");
                          }
                        | */
                        param ';'
                        {
			  report_reduction("params <-- param ;");
                        }
                        | error ';'
                        {
			  report_reduction("params <-- error ;");
			  rt_error("expected parameter expression");
                        }
			| params param ';'
                        {
			  report_reduction("params <-- params param ;");
			}
			| params error ';'
                        {
			  report_reduction("params <-- params error ;");
			  rt_error("expected parameter expression");
			}
                        ;

param			: T_IDENTIFIER '=' expression
			{
			  report_reduction("param <-- IDENTIFIER = expression");
			  SetParameter ($1, $3);
			}
                        | expression
                        {
			  report_reduction("param <-- expression");
			  
			  magic_pointer<TAttribObject> ptobj = get_object($1);

			  // If it is an object, check to see if there is an
			  // 'addObject' function in the current object. 
			  if( !!ptobj  && !!ptobj->tValue )
			  {

			    magic_pointer<TAttribute> attr = DATASTACK.top();
			    if( !!attr )
			    {
			      magic_pointer<TProcedural> proc = get_procedural_var(attr);
			      
			      if( !!proc )
			      {
				TUserFunctionMap functions = proc->getUserFunctions();
				if( functions.find("addObject") !=
				    functions.end() )
				{
				  user_arg_vector args;
				  args.push_back ($1);

				  functions["addObject"]->call(args);

				  static bool warned = false;
				  if( !warned )
				  {
				    rt_warning("DEPRECATION: adding instance of " +
					       ptobj->tValue->className() +
					       " to the current object (likely aggregate or CSG) instead of ignoring it.  This feature may soon be removed.");
				    warned = true;
				  }
				}
			      }
			    }
			  }
			  else
			  {
			    magic_pointer<TProcedural> proc = get_procedural_var($1, false);
			    if( !!proc )
			    {
			      FIXME("Potentially do something with (" + $1->toString() + ") in the current object");
			    }
			  }
			}
                        | reserved_words '=' expression
                        {
			  report_reduction("param <-- reserved_words = expression");
			  SetParameter ($1, $3);			    
			}
			| object_param
                        {
			  report_reduction("param <-- object_param");
			}
			| scene_param
                        {
			  report_reduction("param <-- scene_param");
			}
			;

object_param		: T_FILTER '=' instance
                        {
			  // If an object, object->addFilter.
			  // If a scene, scene->addImageFilter
			  report_reduction("object_param <-- FILTER = instance");
			  // The object will clone this filter (a good idea?)
			  // The alternative was to either:
			  // 1) Use a magic pointer for the filter.
			  // 2) Maintain a list of all object filters for
			  //    proper deletion/deallocation. 
			  //			    OBJECT->addFilter ($2.get_pointer());
			  
			  magic_pointer<TObject> obj = check_get_object(DATASTACK.top());
			  magic_pointer<TScene> scene = check_get_scene(DATASTACK.top());
			  if( !!obj )
			  {
			    // Do it (obj->addFilter)
			    FIXME("object filters need work");
			  }
			  else if ( scene )
			  {
			    // Do it (scene->addImageFilter)
			    FIXME("image filters need work");
			  }
			  else
			  {
			    SetParameter($1,$3);
			  }
			}
			;


scene_param		: T_LIGHT '=' instance
			{
			  report_reduction("scene_param <-- LIGHT = instance");
			  // This is no longer needed, as there are special
			  // cases for this in the light_instance rule.
			  if( !!$3 )
			  {
			    static bool gave_warning = false;
			    
			    if(!gave_warning)
			    {
			      cerr << "Note for light instance on line "
				   << TSceneRT::_dwLineNumber
				   << endl;
			      cerr << "  Usage of lights in the 'scene' section is no longer required" << endl;
			      cerr << "  They may now be added to aggregates, csg, etc., or used "
				   << endl
				   << "  external to the scene section (same syntax)." 
				   << endl;
			      gave_warning = true;
			    }
			    
			    magic_pointer<TObject> obj = check_get_object($3);
			    if( !!obj )
			    {
			      if( !WORLD->containsObject( obj ) )
			      {
				WORLD->add ( obj );
			      }
			      // The following does not work anymore, as lights
			      // added in this manor do not go through the
			      // re-translation process.  Check to see if it
			      // breaks anything!
			      // SCENE->addLight (rcp_static_cast<TLight>(obj)->clone_new());
			    }
			    else
			    {
			      rt_error("NULL light given (BUG?)");
			    }
			  }
			}
			| T_OUTPUT '=' instance
			{
			  report_reduction("scene_param <-- OUTPUT = instance");
			  FIXME("Image output");
			  magic_pointer<TAttribScene> pscene = get_scene(DATA);
			  if( !!pscene )
			  {
			    //			    magic_pointer<TScene> scene = pscene->tValue;
			    cout << "Warning: Ignoring locally defined scene" << endl;
			    magic_pointer<TScene> scene = TSceneRT::_ptParsedScene;
			    if( !!scene )
			    {
			      magic_pointer<TAttribImageIO> io = get_imageio($3);
			      if( !!io )
			      {
				//				cout << "Setting image IO to " << io->toString() << endl;
				scene->setImageOutput (io->tValue);
			      }
			      else
			      {
				rt_error("Not an image io");
			      }
			    }
			    else
			    {
			      rt_error("internal: scene is NULL");
			    }
			  }
			  else
			  {
			    SetParameter($1,$3);
			  }
			}
                        ;

potential_name          : name
                        {
			  report_reduction("potential_name <-- name");
			}
                        | reserved_words
                        {
			  report_reduction("potential_name <-- reserved_words");
			}
			;


reserved_words          : T_BLUE
                          {
			    report_reduction("reserved_words <-- BLUE");
			    $$ = $1;
			  }
			| T_CLASS
                          {
			    report_reduction("reserved_words <-- CLASS");
			    $$ = $1;
			  }
			| T_DEFINE
                          {
			    report_reduction("reserved_words <-- DEFINE");
			    $$ = $1;
			  }
			| T_EXTENDS
                          {
			    report_reduction("reserved_words <-- EXTENDS");
			    $$ = $1;
			  }
			| T_GREEN
                          {
			    report_reduction("reserved_words <-- GREEN");
			    $$ = $1;
			  }
			| T_RED
                          {
			    report_reduction("reserved_words <-- RED");
			    $$ = $1;
			  }
			| T_RENDERER
                          {
			    report_reduction("reserved_words <-- RENDERER");
			    $$ = $1;
			  }
			;

%%

void rt_error (const char* pkcTEXT)
{

  cerr << endl << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Error: " << pkcTEXT << endl;

}  /* rt_error() */

void rt_error (const string& rksTEXT)
{

  cerr << endl << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Error: " << rksTEXT << endl;

}  /* rt_error() */

void rt_warning (const string& rksTEXT)
{

  cerr << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Warning: " << rksTEXT << endl;

}  /* rt_error() */


void RT_InitParser (void)
{

  InitObjects();
  GlobalInitFunctions();

  while(!DATASTACK.empty()) DATASTACK.pop();

  WORLD = (magic_pointer<TAggregate>)new TAggregate();
  PARENT_OBJECT = (magic_pointer<TBaseClass>)NULL;
  
  TSceneRT::_ptParsedScene->setWorld (rcp_static_cast<TObject>(WORLD));

  // Set the globalmost object to be the scene.  This allows operation on the
  // scene without the need for a dedicated scene section.
  DATASTACK.push ((user_arg_type)new TAttribScene(TSceneRT::_ptParsedScene));
  
}  /* RT_InitParser() */


void RT_CloseParser (void)
{

  DATAMAP.clear();

}  /* RT_CloseParser() */




void InitObjects (void)
{
  DATAMAP.clear();
}  /* InitObjects() */


magic_pointer<TBaseClass> NewObject (const string& rktCLASS,
				     const magic_pointer<TBaseClass>& pktParent)
{
  TBaseClass* ptChild = TClassManager::_newObject (rktCLASS,
						   pktParent.get_pointer());

  if ( !ptChild )
  {
    string   tMessage = string ("class ") + rktCLASS + " does not exist";
    yyerror (tMessage.c_str());
    exit (1);
  }

  return magic_pointer<TBaseClass>(ptChild);

}  /* NewObject() */

void CreateObject (const string& rktCLASS, const string& rktDEF_CLASS)
{
  //  cout << "Attempting to create instance of " << rktCLASS << endl;
  magic_pointer<TBaseClass> ptData;
  if ( rktCLASS == "" )
  {
    ptData = NewObject (rktDEF_CLASS, PARENT_OBJECT);
  }
  else
  {
    ptData = NewObject (rktCLASS, PARENT_OBJECT);
  }
  //  cout << "Instance created... " << ptData->className() << endl;
  
  DATASTACK.push (base_to_attr(ptData));
  PARENT_OBJECT = (magic_pointer<TBaseClass>)NULL;

}  /* CreateObject() */



void report_reduction(const string& s)
{
#if defined(REDUCTION_REPORTING)
  cout << s << endl;
#endif
}

magic_pointer<TAttribute> Instance(const string& s)
{
  if( s == "" )
  {
    rt_error ("instanced object cannot be unnamed");
    exit (1);
  }

  if ( DATAMAP.find (s) == DATAMAP.end() )
  {
    rt_error ("\"" + s + "\" is not defined");
    exit (1);
  }

  magic_pointer<TAttribute> attr = DATAMAP [s].second;

  if( !!attr )
  {
    return attr;
  }
  else
  {
    rt_error("\"" + s + "\" is defined as NULL");
    exit(1);
  }
}


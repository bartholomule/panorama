/*
*  Copyright (C) 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

%{

#include <map>
#include <stack>
#include <string>
#include <iostream.h>
#include "hlapi/hlapi_all.h"
#include "llapi/llapi_all.h"
#include "parser_defs.h"
#include "psl_io.h"

enum EVarScope
{

  FX_GLOBAL_SCOPE,
  FX_OBJECT_SCOPE,
  FX_EVENT_SCOPE
  
};  /* enum EVarScope */

static map<string, TProcedural*, less<string> >   _tObjectMap;
static stack<TProcedural*>                        _tDataStack;

static TProcedural*   _ptData;
static TProcedural*   _ptParent;
static TAggregate*    _ptWorld;

static EVarScope     _eVarScope      = FX_GLOBAL_SCOPE;
static EAttribType   _eVarType       = FX_NONE;
static TEventCode*   _ptCurrentEvent = NULL;

#define POP()           top(); _tDataStack.pop()            // Fix to STL's pop()

#define YYDEBUG 1

static string DefaultClass (const string& rktTYPE);
static TProcedural* NewObject (const string& rktCLASS, const TProcedural* pktPARENT);
static void* UpdateObject (const string& rktNAME);
static void DefineObject (const string& rktNAME, const string& rktCLASS, const string& rktDEF_CLASS);
static void CreateObject (const string& rktCLASS, const string& rktDEF_CLASS);
static EAttribType GetTypeCode (const string& rktNAME);

static void InitObjects (void);

static void AddVariable (const string& rktNAME);
static void AddInstruction (EInstructionCode eCODE, EAttribType eTYPE, NAttribute nPARAM);

%}

%union {
         char          acString [200];
         double        dValue;
         bool          gValue;
         TScene*       ptScene;
         TObject*      ptObject;
         EAttribType   eType;
         struct
         {
           EAttribType   eType;
           NAttribute    nValue;
         } tExpressionData;
       }

%token <dValue> T_REAL
%token <gValue> T_BOOL
%token <acString> T_COMPLEX_TYPE
%token <acString> T_IDENTIFIER
%token <acString> T_QUOTED_STRING

%token T_DEFINE
%token T_CLASS
%token T_EXTENDS
%token T_NEW

%token T_BOX
%token T_CIRCLE
%token T_CONE
%token T_CYLINDER
%token T_DIFFERENCE
%token T_FILTER
%token T_INTERSECTION
%token T_MESH
%token T_PHONG_TRIANGLE
%token T_PLANE
%token T_RECTANGLE
%token T_SPHERE
%token T_TRIANGLE
%token T_UNION

%token T_TYPE_REAL
%token T_TYPE_BOOL
%token T_TYPE_STRING
%token T_TYPE_COLOR
%token T_TYPE_VECTOR
%token T_TYPE_VECTOR2

%token T_TYPE_IMAGE
%token T_TYPE_SCENE

%token T_TYPE_BSDF
%token T_TYPE_CAMERA
%token T_TYPE_LIGHT
%token T_TYPE_MATERIAL
%token T_TYPE_RENDERER
%token T_TYPE_OBJECT
%token T_TYPE_AGGREGATE
%token T_TYPE_OBJECT_FILTER
%token T_TYPE_IMAGE_FILTER

%type <acString> name
%type <acString> class
%type <tExpressionData> expression
%type <tExpressionData> real_expression
%type <tExpressionData> bool_expression
%type <tExpressionData> color_expression
%type <tExpressionData> vector_expression
%type <tExpressionData> vector2_expression
%type <tExpressionData> string_expression
%type <eType> lvalue

%left '+' '-'
%left '*' '/'
%right UNARY_MINUS

%start everything

%%

/*
*  Expressions
*/

real_expression         : T_REAL
                          {
                            $$.eType         = FX_REAL;
                            $$.nValue.dValue = $1;
                          }
                        ;

bool_expression         : T_BOOL
                          {
                            $$.eType         = FX_BOOL;
                            $$.nValue.gValue = $1;
                          }
                        ;

color_expression        : T_TYPE_COLOR '(' expression ',' expression ',' expression ')'
                          {
                            if ( ( $3.eType != FX_REAL ) || ( $5.eType != FX_REAL ) || ( $7.eType != FX_REAL ) )
                            {
                              psl_error ("wrong type for parameter (real expected).");
                              exit (1);
                            }
                            $$.eType          = FX_COLOR;
                          }
                        ;

vector_expression       : T_TYPE_VECTOR '(' expression ',' expression ',' expression ')'
                          {
                            if ( ( $3.eType != FX_REAL ) || ( $5.eType != FX_REAL ) || ( $7.eType != FX_REAL ) )
                            {
                              psl_error ("wrong type for parameter (real expected).");
                              exit (1);
                            }
                            $$.eType         = FX_VECTOR;
                          }
                        ;

vector2_expression      : T_TYPE_VECTOR2 '(' expression ',' expression ')'
                          {
                            if ( ( $3.eType != FX_REAL ) || ( $5.eType != FX_REAL ) )
                            {
                              psl_error ("wrong type for parameter (real expected).");
                              exit (1);
                            }
                            $$.eType         = FX_VECTOR2;
                          }
                        ;

string_expression       : T_QUOTED_STRING
                          {
                            $$.eType         = FX_STRING;
                          }
                        ;

expression              : real_expression
                          {
                            $$ = $1;
                          }
                        | bool_expression
                          {
                            $$ = $1;
                          }
                        | color_expression
                          {
                            $$ = $1;
                          }
                        | vector_expression
                          {
                            $$ = $1;
                          }
                        | vector2_expression
                          {
                            $$ = $1;
                          }
                        | string_expression
                          {
                            $$ = $1;
                          }
                        | T_IDENTIFIER
                          {}
                        | T_NEW T_IDENTIFIER
                          {
                            $$.eType = GetTypeCode ($2);
                          }
                        | function_call
                          {}
                        ;

function_call           : T_IDENTIFIER '(' function_params ')'
                          {}
                        ;

function_params		: /* Nothing */
                        | function_params1
                          {}
                        ;
                        
function_params1	: function_param
                          {}
                        | function_params ',' function_param
                          {}
                        ;
                        
function_param		: expression
                          {}
			;

/*
*  Variables
*/

variables               : /* Nothing */
                          {}
                        | variables variable
                          {}
                        ;

variable                : T_TYPE_REAL
                          {
                            _eVarType = FX_REAL;
                          }
                          var_list ';'
                        | T_TYPE_BOOL
                          {
                            _eVarType = FX_BOOL;
                          }
                          var_list ';'
                        | T_TYPE_STRING
                          {
                            _eVarType = FX_STRING;
                          }
                          var_list ';'
                        | T_TYPE_COLOR
                          {
                            _eVarType = FX_COLOR;
                          }
                          var_list ';'
                        | T_TYPE_VECTOR
                          {
                            _eVarType = FX_VECTOR;
                          }
                          var_list ';'
                        | T_TYPE_VECTOR2
                          {
                            _eVarType = FX_VECTOR2;
                          }
                          var_list ';'
                        | T_TYPE_IMAGE
                          {
                            _eVarType = FX_IMAGE;
                          }
                          var_list ';'
                        | T_COMPLEX_TYPE
                          {
                            if ( _eVarScope == FX_GLOBAL_SCOPE )
                            {
                              psl_error ("cannot use a complex type for a global variable");
                              exit (1);
                            }
                            _eVarType = GetTypeCode ($1);
                          }
                          var_list ';'
                        | T_IDENTIFIER
                          {
                            psl_error ("unknown type");
                            exit (1);
                          }
                          var_list ';'
                        ;
                        
var_list                : var
                          {}
                        | var_list ',' var
                          {}
                        ;

var                     : T_IDENTIFIER
                          {
                            AddVariable ($1);
                          }
                        | T_IDENTIFIER '=' expression
                          {
                            if ( _eVarType != $3.eType )
                            {
                              psl_error ("wrong type in assignment");
                              cout << "left = " << _eVarType << ", right = " << $3.eType << endl;
                              exit (1);
                            }
                            AddVariable ($1);
                          }
                        ;

/*
*  Sentences
*/

sentences               : sentence
                          {}
                        | sentences sentence
                          {}
                        ;

sentence                : assignment ';'
                          {}
                        | function_call ';'
                          {}
                        ;

assignment		: lvalue '=' expression
                          {
                            /*
                            if ( $1 != $3.eType )
                            {
                              psl_error ("wrong type in assignment");
                              exit (1);
                            }
                            */
                          }
                        ;

lvalue                  : T_IDENTIFIER
                          {
                            $$ = FX_NONE;
                          }
			| lvalue '.' T_IDENTIFIER
                          {
                            $$ = FX_NONE;
                          }
			;

/*
*  Object programs
*/

program			: /* Nothing */
			| variables event_list
                          {}
			;

event_list              : event
                          {}
                        | event_list event
                          {}
                        ;

event                   : T_IDENTIFIER '(' function_params ')' '{'
                          {
                            _eVarScope      = FX_EVENT_SCOPE;
                            _ptCurrentEvent = _tDataStack.top()->program()->getEventCode ($1);
                          }
			  code '}'
                          {}
                        ;

code                    : variables sentences
                          {}
                        ;

/*
*  Main structure
*/

everything		: /* Nothing */
                        | everything variable
                          {}
			| everything instance
                          {}
			| everything definition
                          {}
			;

instance		: scene_instance
                          {}
			| object_instance
                          {}
			;

definition		: T_DEFINE any_def
                          {}
			| T_DEFINE scene_def
			  {}
			;

name			: T_IDENTIFIER
			  {
			    strcpy ($$, $1);
			  }
			;

class			: /* Nothing */
                          {
                            strcpy ($$, "");
                          }
			| ':' T_EXTENDS T_IDENTIFIER
			  {
                            if ( _tObjectMap.find ($3) == _tObjectMap.end() )
                            {
			      psl_error ("trying to extend from non existing object");
			      exit (1);
                            }
                            _ptParent = _tObjectMap [$3];
			    strcpy ($$, _ptParent->className().c_str());
			  }
			| ':' T_CLASS T_IDENTIFIER
			  {
			    _ptParent = NULL;
			    strcpy ($$, $3);
			  }
			;

scene_def		: T_TYPE_SCENE name class '{'
			  {
			    DefineObject ($2, $3, "Scene");
                            _eVarScope = FX_OBJECT_SCOPE;
			  }
			  program '}'
			  {
			    UpdateObject ($2);
                            _eVarScope = FX_GLOBAL_SCOPE;
			  }
			;

scene_instance		: T_TYPE_SCENE class '{'
			  {
			    _ptData = TScenePsl::_ptParsedScene;
			    _tDataStack.push (_ptData);
                            _eVarScope = FX_OBJECT_SCOPE;
			  }
			  program '}'
			  {
			    _tDataStack.pop();
                            TScenePsl::_ptParsedScene->sendEvent ("init");
                            _eVarScope = FX_GLOBAL_SCOPE;

//                            TScenePsl::_ptParsedScene->globalData()->printDebug();
			  }
			;

object_instance		: T_COMPLEX_TYPE class '{'
			  {
                            if ( strcmp ($1, "Object") && strcmp ($1, "Aggregate") )
                            {
                              psl_error ("only objects and scene can be instanced");
                              exit (1);
                            }
			    CreateObject ($2, "");
                            _eVarScope = FX_OBJECT_SCOPE;
			  }
			  program '}'
			  {
                            _tDataStack.top()->sendEvent ("init");
                            _eVarScope = FX_GLOBAL_SCOPE;

//                            _tDataStack.top()->program()->printDebug();
			    _tDataStack.pop();
			  }
			;

any_def			: T_COMPLEX_TYPE name class '{'
			  {
			    DefineObject ($2, $3, DefaultClass ($1));
                            _eVarScope = FX_OBJECT_SCOPE;
			  }
			  program '}'
			  {
			    UpdateObject ($2);
                            _eVarScope = FX_GLOBAL_SCOPE;
			  }
			;

%%

void psl_error (const char* pkcTEXT)
{

  cerr << endl << TScenePsl::_tInputFileName << "(" << TScenePsl::_dwLineNumber << ") Error: " << pkcTEXT << endl;

}  /* psl_error() */


void PSL_InitParser (void)
{

  InitObjects();

  _ptWorld = new TAggregate();

  TScenePsl::_ptParsedScene->setWorld (_ptWorld);
  
}  /* PSL_InitParser() */


void PSL_CloseParser (void)
{

  _tObjectMap.clear();

}  /* PSL_CloseParser() */


void InitObjects (void)
{
}  /* InitObjects() */


void AddVariable (const string& rktNAME)
{

  NAttribute   nAttrib;

  if ( _eVarScope == FX_GLOBAL_SCOPE )
  {
    TScenePsl::_ptParsedScene->globalData()->addVariable (rktNAME, _eVarType, nAttrib);
  }
  else if ( _eVarScope == FX_OBJECT_SCOPE )
  {
  }
  else
  {
  }

}  /* AddVariable() */


void AddInstruction (EInstructionCode eCODE, EAttribType eTYPE, NAttribute nPARAM)
{

  TInstruction   tInst;

  tInst.eCode  = eCODE;
  tInst.eType  = eTYPE;
  tInst.nParam = nPARAM;

  _ptCurrentEvent->push_back (tInst);
  
}  /* AddInstruction() */


string DefaultClass (const string& rktTYPE)
{

  if ( rktTYPE == "Renderer" )
  {
    return "Raytracer";
  }
  else if ( rktTYPE == "ObjectFilter" )
  {
    return "";
  }
  else if ( rktTYPE == "ImageFilter" )
  {
    return "";
  }
  else if ( rktTYPE == "Material" )
  {
    return "Material";
  }
  else if ( rktTYPE == "Bsdf" )
  {
    return "BsdfPhong";
  }
  else if ( rktTYPE == "Light" )
  {
    return "PointLight";
  }
  else if ( rktTYPE == "Camera" )
  {
    return "PinholeCamera";
  }
  else if ( rktTYPE == "Object" )
  {
    return "";
  }
  else if ( rktTYPE == "Aggregate" )
  {
    return "Aggregate";
  }
  else
  {
    psl_error ("cannot use a simple type in define");
    exit (1);
  }

}  /* DefaultClass */


TProcedural* NewObject (const string& rktCLASS, const TProcedural* pktPARENT)
{

  TProcedural*   ptChild;

//  cout << "New object : \"" << rktCLASS << "\"" << endl;
  
  ptChild = (TProcedural*) TClassManager::_newObject (rktCLASS, pktPARENT);
  if ( !ptChild )
  {
    string   tMessage = string ("class ") + rktCLASS + " does not exist";
    psl_error (tMessage.c_str());
    exit (1);
  }

  return ptChild;

}  /* NewObject() */


void* UpdateObject (const string& rktNAME)
{

  TProcedural*   ptObject = _tDataStack.POP();

  _tObjectMap [rktNAME] = ptObject;

  return ptObject;

}  /* UpdateObject() */


void DefineObject (const string& rktNAME, const string& rktCLASS, const string& rktDEF_CLASS)
{

//  cout << "Defining object : \"" << rktNAME << "\", \"" << rktCLASS << "\", \"" << rktDEF_CLASS << "\"" << endl;

  if ( rktNAME == "" )
  {
    psl_error ("defined object cannot be unnamed");
    exit (1);
  }

  if ( _tObjectMap.find (rktNAME) != _tObjectMap.end() )
  {
    psl_error ("cannot redefine an existing object");
    exit (1);
  }

  if ( rktCLASS == "" )
  {
    _ptData = NewObject (rktDEF_CLASS, _ptParent);
  }
  else
  {
    _ptData = NewObject (rktCLASS, _ptParent);
  }

  _tDataStack.push (_ptData);
  _ptParent = NULL;

}  /* DefineObject() */


void CreateObject (const string& rktCLASS, const string& rktDEF_CLASS)
{

//  cout << "Creating object : \"" << rktCLASS << "\", \"" << rktDEF_CLASS << "\"" << endl;
  
  if ( rktCLASS == "" )
  {
    _ptData = NewObject (rktDEF_CLASS, _ptParent);
  }
  else
  {
    _ptData = NewObject (rktCLASS, _ptParent);
  }

  _tDataStack.push (_ptData);
  _ptParent = NULL;

}  /* CreateObject() */


EAttribType GetTypeCode (const string& rktNAME)
{

  if ( rktNAME == "Real" )
  {
    return FX_REAL;
  }
  else if ( rktNAME == "Bool" )
  {
    return FX_BOOL;
  }
  else if ( rktNAME == "String" )
  {
    return FX_STRING;
  }
  else if ( rktNAME == "Color" )
  {
    return FX_COLOR;
  }
  else if ( rktNAME == "Vector" )
  {
    return FX_VECTOR;
  }
  else if ( rktNAME == "Vector2" )
  {
    return FX_VECTOR2;
  }
  else if ( rktNAME == "Image" )
  {
    return FX_IMAGE;
  }
  else if ( rktNAME == "Bsdf" )
  {
    return FX_BSDF;
  }
  else if ( rktNAME == "Camera" )
  {
    return FX_CAMERA;
  }
  else if ( rktNAME == "Light" )
  {
    return FX_LIGHT;
  }
  else if ( rktNAME == "Material" )
  {
    return FX_MATERIAL;
  }
  else if ( rktNAME == "Renderer" )
  {
    return FX_RENDERER;
  }
  else if ( rktNAME == "Object" )
  {
    return FX_OBJECT;
  }
  else if ( rktNAME == "Aggregate" )
  {
    return FX_AGGREGATE;
  }
  else if ( rktNAME == "ObjectFilter" )
  {
    return FX_OBJECT_FILTER;
  }
  else if ( rktNAME == "ImageFilter" )
  {
    return FX_IMAGE_FILTER;
  }

  return FX_NONE;

}  /* GetTypeCode() */

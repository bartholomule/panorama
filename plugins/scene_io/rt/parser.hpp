/* A Bison parser, made by GNU Bison 1.875.  */

/* C++ Skeleton parser for LALR(1) parsing with Bison,
   Copyright (C) 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */
/* FIXME: This is wrong, we want computed header guards.
   I don't know why the macros are missing now. :( */
#ifndef PARSER_HEADER_H
# define PARSER_HEADER_H

#include "stack.hh"
#include "location.hh"

#include <string>
#include <iostream>

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_BOOL = 258,
     T_REAL = 259,
     T_INTEGER = 260,
     T_IDENTIFIER = 261,
     T_QUOTED_STRING = 262,
     T_BLUE = 263,
     T_CLASS = 264,
     T_DEFINE = 265,
     T_EXTENDS = 266,
     T_FILTER = 267,
     T_GREEN = 268,
     T_LIGHT = 269,
     T_OUTPUT = 270,
     T_RED = 271,
     T_RENDERER = 272,
     AND_L = 273,
     OR_L = 274,
     EQUAL = 275,
     NOT_EQ = 276,
     GREATER = 277,
     GREATER_EQ = 278,
     LESS = 279,
     LESS_EQ = 280,
     PARAM = 281,
     DEFINED = 282,
     THIS = 283
   };
#endif
#define T_BOOL 258
#define T_REAL 259
#define T_INTEGER 260
#define T_IDENTIFIER 261
#define T_QUOTED_STRING 262
#define T_BLUE 263
#define T_CLASS 264
#define T_DEFINE 265
#define T_EXTENDS 266
#define T_FILTER 267
#define T_GREEN 268
#define T_LIGHT 269
#define T_OUTPUT 270
#define T_RED 271
#define T_RENDERER 272
#define AND_L 273
#define OR_L 274
#define EQUAL 275
#define NOT_EQ 276
#define GREATER 277
#define GREATER_EQ 278
#define LESS 279
#define LESS_EQ 280
#define PARAM 281
#define DEFINED 282
#define THIS 283




/* Copy the first part of user declarations.  */
#line 70 "parser.y"


  //  #define REDUCTION_REPORTING
  
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

#define YYDEBUG 0
#define YYERROR_VERBOSE 1

  
// Fixes to allow bison v1.?? to work (the use of bison.simple has been lost).
typedef YYSTYPE yystype;
//typedef YYSTYPE yyltype;
typedef char yysigned_char;
extern int rt_lex(yystype *p);
namespace yy { int yylex(yystype *p); }

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

  
BASE_OBJECT_TYPE NewObject (const string& rktCLASS, const BASE_OBJECT_TYPE& pktPARENT);

void CreateObject (const string& rktCLASS, const string& rktDEF_CLASS);

magic_pointer<TAttribute> Instance(const string& s);
 
void InitObjects (void);

void report_reduction(const string& s);

static void FIXME(const string& s) { GOM.error() << "FIXME: " << s << endl; }



/* Line 112 of lalr1.cc.  */
#line 164 "parser.hpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error message.  */
#ifndef YYERROR_VERBOSE
# define YYERROR_VERBOSE 0
#endif

#ifndef YYSTYPE
typedef int yystype;
# define YYSTYPE yystype
#endif

/* Copy the second part of user declarations.  */


/* Line 138 of lalr1.cc.  */
#line 185 "parser.hpp"
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N) \
   Current.last.line = Rhs[N].last.line; \
   Current.last.column = Rhs[N].last.column;
#endif

namespace yy
{
  class Parser;

  template < typename P >
  struct Traits
  {
  };

  template < >
  struct Traits< Parser >
  {
    typedef unsigned char TokenNumberType;
    typedef signed char       RhsNumberType;
    typedef int      StateType;
    typedef yystype  SemanticType;
    typedef Location LocationType;
  };
}

namespace yy
{
  class Parser 
  {
  public:

    typedef Traits< Parser >::TokenNumberType TokenNumberType;
    typedef Traits< Parser >::RhsNumberType   RhsNumberType;
    typedef Traits< Parser >::StateType       StateType;
    typedef Traits< Parser >::SemanticType    SemanticType;
    typedef Traits< Parser >::LocationType    LocationType;

    typedef Stack< StateType >    StateStack;
    typedef Stack< SemanticType > SemanticStack;
    typedef Stack< LocationType > LocationStack;

#if YYLSP_NEEDED
    Parser (bool debug,
	    LocationType initlocation) :
      debug_ (debug),
      cdebug_ (std::cerr),
      initlocation_ (initlocation)
#else
    Parser (bool debug) :
      debug_ (debug),
      cdebug_ (std::cerr)
#endif
    {
    }

    virtual ~Parser ()
    {
    }

    virtual int parse ();

  private:

    virtual void lex_ ();
    virtual void error_ ();
    virtual void print_ ();

    /* Stacks.  */
    StateStack    state_stack_;
    SemanticStack semantic_stack_;
    LocationStack location_stack_;

    /* Tables.  */
    static const short pact_[];
    static const short pact_ninf_;
    static const unsigned char defact_[];
    static const signed char pgoto_[];
    static const signed char defgoto_[];
    static const short table_[];
    static const short table_ninf_;
    static const signed char check_[];
    static const unsigned char r1_[];
    static const unsigned char r2_[];

#if YYDEBUG || YYERROR_VERBOSE
    static const char* const name_[];
#endif

    /* More tables, for debugging.  */
#if YYDEBUG
    static const RhsNumberType rhs_[];
    static const unsigned char prhs_[];
    static const unsigned short rline_[];
    static const unsigned char stos_[];
    static const unsigned short token_number_[];
#endif

    /* Even more tables.  */
    static inline TokenNumberType translate_ (int token);

    /* Constants.  */
    static const int eof_;
    /* LAST_ -- Last index in TABLE_.  */
    static const int last_;
    static const int nnts_;
    static const int empty_;
    static const int final_;
    static const int terror_;
    static const int errcode_;
    static const int ntokens_;
    static const int initdepth_;
    static const unsigned user_token_number_max_;
    static const TokenNumberType undef_token_;

    /* State.  */
    int n_;
    int len_;
    int state_;

    /* Debugging.  */
    int debug_;
    std::ostream &cdebug_;

    /* Lookahead and lookahead in internal form.  */
    int looka_;
    int ilooka_;

    /* Message.  */
    std::string message;

    /* Semantic value and location of lookahead token.  */
    SemanticType value;
    LocationType location;

    /* @$ and $$.  */
    SemanticType yyval;
    LocationType yyloc;

    /* Initial location.  */
    LocationType initlocation_;
  };
}

#endif /* ! defined PARSER_HEADER_H */

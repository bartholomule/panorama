
/*  A Bison parser, made from parser.y
 by  GNU Bison version 1.27
  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse psl_parse
#define yylex psl_lex
#define yyerror psl_error
#define yylval psl_lval
#define yychar psl_char
#define yydebug psl_debug
#define yynerrs psl_nerrs
#define	T_REAL	257
#define	T_BOOL	258
#define	T_COMPLEX_TYPE	259
#define	T_IDENTIFIER	260
#define	T_QUOTED_STRING	261
#define	T_DEFINE	262
#define	T_CLASS	263
#define	T_EXTENDS	264
#define	T_NEW	265
#define	T_BOX	266
#define	T_CIRCLE	267
#define	T_CONE	268
#define	T_CYLINDER	269
#define	T_DIFFERENCE	270
#define	T_FILTER	271
#define	T_INTERSECTION	272
#define	T_MESH	273
#define	T_PHONG_TRIANGLE	274
#define	T_PLANE	275
#define	T_RECTANGLE	276
#define	T_SPHERE	277
#define	T_TRIANGLE	278
#define	T_UNION	279
#define	T_TYPE_REAL	280
#define	T_TYPE_BOOL	281
#define	T_TYPE_STRING	282
#define	T_TYPE_COLOR	283
#define	T_TYPE_VECTOR	284
#define	T_TYPE_VECTOR2	285
#define	T_TYPE_IMAGE	286
#define	T_TYPE_SCENE	287
#define	T_TYPE_BSDF	288
#define	T_TYPE_CAMERA	289
#define	T_TYPE_LIGHT	290
#define	T_TYPE_MATERIAL	291
#define	T_TYPE_RENDERER	292
#define	T_TYPE_OBJECT	293
#define	T_TYPE_AGGREGATE	294
#define	T_TYPE_OBJECT_FILTER	295
#define	T_TYPE_IMAGE_FILTER	296
#define	UNARY_MINUS	297

#line 19 "parser.y"


#include <map>
#include <stack>
#include <string>
#include <iostream.h>
#include "hlapi/hlapi_all.h"
#include "llapi/llapi_all.h"
#include "parser_defs.h"
#include "psl_io.h"

#define WRITE_CODE(s)        if ( DEBUG_CODE ) { _tDebugCodeFile << s; }
#define SET_CURRENT_CODE()   _ptCurrentCode = _ptCurrentProgram->getEventCode (_tCurrentEvent)

enum EVarScope
{

  FX_GLOBAL_SCOPE,
  FX_OBJECT_SCOPE,
  FX_EVENT_SCOPE
  
};  /* enum EVarScope */

// Auxiliar variables used for debugging
static string     _lvalueName;
static ofstream   _tDebugCodeFile;

static map<string, TProcedural*, less<string> >   _tObjectMap;
static stack<TProcedural*>                        _tDataStack;
static list<TInstruction>*                        _ptCurrentCode = NULL;

static TProcedural*   _ptData;
static TProcedural*   _ptParent;
static TAggregate*    _ptWorld;
static string         _tCurrentEvent;
static EVarScope      _eVarScope        = FX_GLOBAL_SCOPE;
static EAttribType    _eVarType         = FX_NONE;
static TProgram*      _ptCurrentProgram = NULL;

#define POP()           top(); _tDataStack.pop()            // Fix to STL's pop()

#define DEBUG_CODE 1
#define YYDEBUG 1

static string DefaultClass (const string& rktTYPE);
static TProcedural* NewObject (const string& rktCLASS, const TProcedural* pktPARENT);
static void* UpdateObject (const string& rktNAME);
static void DefineObject (const string& rktNAME, const string& rktCLASS, const string& rktDEF_CLASS);
static void CreateObject (const string& rktCLASS, const string& rktDEF_CLASS);
static EAttribType GetTypeCode (const string& rktNAME);

static void InitObjects (void);

static void AddVariable (const string& rktNAME);
static void AddInstruction (EInstructionCode eCODE);


#line 77 "parser.y"
typedef union {
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
       } YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		160
#define	YYFLAG		-32768
#define	YYNTBASE	57

#define YYTRANSLATE(x) ((unsigned)(x) <= 297 ? yytranslate[x] : 106)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    51,
    53,    45,    43,    52,    44,    56,    46,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    48,    54,     2,
    55,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    49,     2,    50,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37,    38,    39,    40,    41,    42,    47
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     7,    10,    12,    14,    15,    19,    20,
    24,    26,    27,    31,    35,    36,    44,    45,    52,    53,
    60,    61,    69,    71,    73,    82,    91,    98,   100,   102,
   104,   106,   108,   110,   112,   114,   117,   119,   124,   125,
   127,   129,   133,   135,   136,   139,   140,   145,   146,   151,
   152,   157,   158,   163,   164,   169,   170,   175,   176,   181,
   182,   187,   188,   193,   195,   199,   201,   205,   207,   210,
   213,   216,   220,   222,   226,   227,   230,   232,   235,   236,
   237,   247
};

static const short yyrhs[] = {    -1,
    57,    84,     0,    57,    58,     0,    57,    59,     0,    66,
     0,    68,     0,     0,     8,    60,    70,     0,     0,     8,
    61,    64,     0,     6,     0,     0,    48,    10,     6,     0,
    48,     9,     6,     0,     0,    33,    62,    63,    49,    65,
   100,    50,     0,     0,    33,    63,    49,    67,   100,    50,
     0,     0,     5,    63,    49,    69,   100,    50,     0,     0,
     5,    62,    63,    49,    71,   100,    50,     0,     3,     0,
     4,     0,    29,    51,    78,    52,    78,    52,    78,    53,
     0,    30,    51,    78,    52,    78,    52,    78,    53,     0,
    31,    51,    78,    52,    78,    53,     0,     7,     0,    72,
     0,    73,     0,    74,     0,    75,     0,    76,     0,    77,
     0,     6,     0,    11,     6,     0,    79,     0,     6,    51,
    80,    53,     0,     0,    81,     0,    82,     0,    80,    52,
    82,     0,    78,     0,     0,    83,    84,     0,     0,    26,
    85,    94,    54,     0,     0,    27,    86,    94,    54,     0,
     0,    28,    87,    94,    54,     0,     0,    29,    88,    94,
    54,     0,     0,    30,    89,    94,    54,     0,     0,    31,
    90,    94,    54,     0,     0,    32,    91,    94,    54,     0,
     0,     5,    92,    94,    54,     0,     0,     6,    93,    94,
    54,     0,    95,     0,    94,    52,    95,     0,     6,     0,
     6,    55,    78,     0,    97,     0,    96,    97,     0,    98,
    54,     0,    79,    54,     0,    99,    55,    78,     0,     6,
     0,    99,    56,     6,     0,     0,    83,   101,     0,   102,
     0,   101,   102,     0,     0,     0,     6,    51,   103,    80,
    53,    49,   104,   105,    50,     0,    83,    96,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   160,   161,   163,   165,   169,   171,   175,   180,   181,   186,
   189,   195,   199,   209,   216,   222,   229,   239,   253,   267,
   281,   287,   298,   305,   312,   323,   334,   345,   351,   356,
   361,   366,   371,   376,   381,   383,   387,   391,   397,   398,
   402,   404,   408,   416,   418,   422,   426,   427,   431,   432,
   436,   437,   441,   442,   446,   447,   451,   452,   456,   457,
   466,   467,   472,   475,   477,   481,   485,   501,   503,   507,
   509,   513,   526,   531,   542,   543,   547,   549,   553,   559,
   563,   570
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","T_REAL",
"T_BOOL","T_COMPLEX_TYPE","T_IDENTIFIER","T_QUOTED_STRING","T_DEFINE","T_CLASS",
"T_EXTENDS","T_NEW","T_BOX","T_CIRCLE","T_CONE","T_CYLINDER","T_DIFFERENCE",
"T_FILTER","T_INTERSECTION","T_MESH","T_PHONG_TRIANGLE","T_PLANE","T_RECTANGLE",
"T_SPHERE","T_TRIANGLE","T_UNION","T_TYPE_REAL","T_TYPE_BOOL","T_TYPE_STRING",
"T_TYPE_COLOR","T_TYPE_VECTOR","T_TYPE_VECTOR2","T_TYPE_IMAGE","T_TYPE_SCENE",
"T_TYPE_BSDF","T_TYPE_CAMERA","T_TYPE_LIGHT","T_TYPE_MATERIAL","T_TYPE_RENDERER",
"T_TYPE_OBJECT","T_TYPE_AGGREGATE","T_TYPE_OBJECT_FILTER","T_TYPE_IMAGE_FILTER",
"'+'","'-'","'*'","'/'","UNARY_MINUS","':'","'{'","'}'","'('","','","')'","';'",
"'='","'.'","everything","instance","definition","@1","@2","name","class","scene_def",
"@3","scene_instance","@4","object_instance","@5","any_def","@6","real_expression",
"bool_expression","color_expression","vector_expression","vector2_expression",
"string_expression","expression","function_call","function_params","function_params1",
"function_param","variables","variable","@7","@8","@9","@10","@11","@12","@13",
"@14","@15","var_list","var","sentences","sentence","assignment","lvalue","program",
"event_list","event","@16","@17","code", NULL
};
#endif

static const short yyr1[] = {     0,
    57,    57,    57,    57,    58,    58,    60,    59,    61,    59,
    62,    63,    63,    63,    65,    64,    67,    66,    69,    68,
    71,    70,    72,    73,    74,    75,    76,    77,    78,    78,
    78,    78,    78,    78,    78,    78,    78,    79,    80,    80,
    81,    81,    82,    83,    83,    85,    84,    86,    84,    87,
    84,    88,    84,    89,    84,    90,    84,    91,    84,    92,
    84,    93,    84,    94,    94,    95,    95,    96,    96,    97,
    97,    98,    99,    99,   100,   100,   101,   101,   103,   104,
   102,   105
};

static const short yyr2[] = {     0,
     0,     2,     2,     2,     1,     1,     0,     3,     0,     3,
     1,     0,     3,     3,     0,     7,     0,     6,     0,     6,
     0,     7,     1,     1,     8,     8,     6,     1,     1,     1,
     1,     1,     1,     1,     1,     2,     1,     4,     0,     1,
     1,     3,     1,     0,     2,     0,     4,     0,     4,     0,
     4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
     4,     0,     4,     1,     3,     1,     3,     1,     2,     2,
     2,     3,     1,     3,     0,     2,     1,     2,     0,     0,
     9,     2
};

static const short yydefact[] = {     1,
     0,    12,    62,     7,    46,    48,    50,    52,    54,    56,
    58,    12,     3,     4,     5,     6,     2,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    19,    66,     0,    64,     0,     0,     8,
     0,    10,     0,     0,     0,     0,     0,     0,     0,    17,
    14,    13,    44,     0,     0,    61,    63,    11,    12,    12,
    47,    49,    51,    53,    55,    57,    59,    44,     0,     0,
    23,    24,    35,    28,     0,     0,     0,     0,    29,    30,
    31,    32,    33,    34,    67,    37,    65,     0,     0,     0,
    60,    62,    45,    76,    77,    20,    39,    36,     0,     0,
     0,    21,    15,    18,    79,     0,    78,    43,     0,    40,
    41,     0,     0,     0,    44,    44,    39,     0,    38,     0,
     0,     0,     0,     0,     0,    42,     0,     0,     0,    22,
    16,     0,     0,     0,    27,    80,     0,     0,    44,    25,
    26,     0,     0,    73,     0,    82,    68,     0,     0,    81,
    71,    73,    69,    70,     0,     0,    72,    74,     0,     0
};

static const short yydefgoto[] = {     1,
    13,    14,    22,    23,    59,    19,    42,   116,    15,    68,
    16,    53,    40,   115,    79,    80,    81,    82,    83,    84,
   108,    86,   109,   110,   111,    69,    93,    24,    25,    26,
    27,    28,    29,    30,    20,    21,    36,    37,   146,   147,
   148,   149,    70,    94,    95,   117,   139,   143
};

static const short yypact[] = {-32768,
     4,    -4,-32768,   -28,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   -19,-32768,-32768,-32768,-32768,-32768,    33,    13,    32,
    32,    48,    31,    32,    32,    32,    32,    32,    32,    32,
    50,    94,    96,-32768,    49,   -46,-32768,   -34,    97,-32768,
    97,-32768,     2,     3,    11,    19,    20,    23,    24,-32768,
-32768,-32768,    56,    10,    32,-32768,-32768,-32768,   -19,   -19,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    56,    55,    57,
-32768,-32768,    54,-32768,   102,    58,    59,    60,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    63,    65,    66,
-32768,    62,-32768,   109,-32768,-32768,    10,-32768,    10,    10,
    10,-32768,-32768,-32768,-32768,    62,-32768,-32768,     6,-32768,
-32768,    67,    68,    69,    56,    56,    10,    10,-32768,    10,
    10,    10,    72,    73,    36,-32768,    74,    75,    71,-32768,
-32768,    76,    10,    10,-32768,-32768,    77,    78,-32768,-32768,
-32768,    64,    79,     1,    80,   111,-32768,    81,    42,-32768,
-32768,    54,-32768,-32768,    10,   112,-32768,-32768,   128,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,    91,   -11,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   -54,  -131,    16,-32768,    18,    -1,   136,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,    -2,    84,-32768,    -6,
-32768,-32768,   -65,-32768,    47,-32768,-32768,-32768
};


#define	YYLAST		141


static const short yytable[] = {    85,
    31,   -60,    90,   159,    -9,    55,   -62,    56,     2,     3,
   145,     4,    71,    72,   145,    73,    74,    55,    38,    57,
    75,    43,    44,    45,    46,    47,    48,    49,    18,     5,
     6,     7,     8,     9,    10,    11,    12,    35,    76,    77,
    78,    32,    33,    18,   112,   113,   114,    88,    89,   123,
   124,    97,    39,    55,    55,    61,    62,   118,   119,    91,
    92,    34,    55,    41,    63,   127,   128,   129,    91,   144,
    55,    55,    64,    65,    55,    55,    66,    67,   137,   138,
     5,     6,     7,     8,     9,    10,    11,   118,   132,     5,
     6,     7,     8,     9,    10,    11,   155,   156,    50,    51,
   157,    52,    58,    54,    97,   -75,    96,    98,    99,   100,
   101,   102,   105,   103,   106,   104,   152,   158,   120,   121,
   122,   130,   131,   135,   136,   133,   134,   160,   150,   140,
   141,    60,   125,   151,   154,   126,    17,   142,    87,   153,
   107
};

static const short yycheck[] = {    54,
    12,     6,    68,     0,    33,    52,     6,    54,     5,     6,
   142,     8,     3,     4,   146,     6,     7,    52,    21,    54,
    11,    24,    25,    26,    27,    28,    29,    30,    48,    26,
    27,    28,    29,    30,    31,    32,    33,     6,    29,    30,
    31,     9,    10,    48,    99,   100,   101,    59,    60,   115,
   116,    51,     5,    52,    52,    54,    54,    52,    53,     5,
     6,    49,    52,    33,    54,   120,   121,   122,     5,     6,
    52,    52,    54,    54,    52,    52,    54,    54,   133,   134,
    26,    27,    28,    29,    30,    31,    32,    52,    53,    26,
    27,    28,    29,    30,    31,    32,    55,    56,    49,     6,
   155,     6,     6,    55,    51,    50,    50,     6,    51,    51,
    51,    49,    51,    49,     6,    50,     6,     6,    52,    52,
    52,    50,    50,    53,    49,    52,    52,     0,    50,    53,
    53,    41,   117,    54,    54,   118,     1,   139,    55,   146,
    94
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/lib/bison.simple"
/* This file comes from bison-1.27.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

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

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 216 "/usr/lib/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 2:
#line 162 "parser.y"
{;
    break;}
case 3:
#line 164 "parser.y"
{;
    break;}
case 4:
#line 166 "parser.y"
{;
    break;}
case 5:
#line 170 "parser.y"
{;
    break;}
case 6:
#line 172 "parser.y"
{;
    break;}
case 7:
#line 176 "parser.y"
{
                            WRITE_CODE ("\ndefine ");
                          ;
    break;}
case 8:
#line 180 "parser.y"
{;
    break;}
case 9:
#line 182 "parser.y"
{
                            WRITE_CODE ("\ndefine ");
                          ;
    break;}
case 10:
#line 186 "parser.y"
{;
    break;}
case 11:
#line 190 "parser.y"
{
			    strcpy (yyval.acString, yyvsp[0].acString);
			  ;
    break;}
case 12:
#line 196 "parser.y"
{
                            strcpy (yyval.acString, "");
                          ;
    break;}
case 13:
#line 200 "parser.y"
{
                            if ( _tObjectMap.find (yyvsp[0].acString) == _tObjectMap.end() )
                            {
			      psl_error ("trying to extend from non existing object");
			      exit (1);
                            }
                            _ptParent = _tObjectMap [yyvsp[0].acString];
			    strcpy (yyval.acString, _ptParent->className().c_str());
			  ;
    break;}
case 14:
#line 210 "parser.y"
{
			    _ptParent = NULL;
			    strcpy (yyval.acString, yyvsp[0].acString);
			  ;
    break;}
case 15:
#line 217 "parser.y"
{
                            WRITE_CODE ("Scene\n");
			    DefineObject (yyvsp[-2].acString, yyvsp[-1].acString, "Scene");
                            _eVarScope = FX_OBJECT_SCOPE;
			  ;
    break;}
case 16:
#line 223 "parser.y"
{
			    UpdateObject (yyvsp[-5].acString);
                            _eVarScope = FX_GLOBAL_SCOPE;
			  ;
    break;}
case 17:
#line 230 "parser.y"
{
			    _ptData = TScenePsl::_ptParsedScene;
			    _tDataStack.push (_ptData);
                            _eVarScope = FX_OBJECT_SCOPE;

                            _ptCurrentProgram = TScenePsl::_ptParsedScene->program();
                            _tCurrentEvent    = EVENT_INIT_VARIABLES;
                            SET_CURRENT_CODE();
			  ;
    break;}
case 18:
#line 240 "parser.y"
{
			    _tDataStack.pop();
                            TScenePsl::_ptParsedScene->sendEvent ("init");
                            _eVarScope = FX_GLOBAL_SCOPE;

                            TScenePsl::_ptParsedScene->program()->printDebug();

                            _ptCurrentProgram = TScenePsl::_ptParsedScene->globalData();
                            _tCurrentEvent    = EVENT_INIT_VARIABLES;
                            SET_CURRENT_CODE();
			  ;
    break;}
case 19:
#line 254 "parser.y"
{
                            if ( strcmp (yyvsp[-2].acString, "Object") && strcmp (yyvsp[-2].acString, "Aggregate") )
                            {
                              psl_error ("only objects and scene can be instanced");
                              exit (1);
                            }
			    CreateObject (yyvsp[-1].acString, "");
                            _eVarScope = FX_OBJECT_SCOPE;

                            _ptCurrentProgram = _ptData->program();
                            _tCurrentEvent    = EVENT_INIT_VARIABLES;
                            SET_CURRENT_CODE();
			  ;
    break;}
case 20:
#line 268 "parser.y"
{
                            _tDataStack.top()->sendEvent ("init");
                            _eVarScope = FX_GLOBAL_SCOPE;

                            _tDataStack.top()->program()->printDebug();
			    _tDataStack.pop();

                            _ptCurrentProgram = TScenePsl::_ptParsedScene->globalData();
                            _tCurrentEvent    = EVENT_INIT_VARIABLES;
                            SET_CURRENT_CODE();
			  ;
    break;}
case 21:
#line 282 "parser.y"
{
                            WRITE_CODE (yyvsp[-3].acString << endl);
			    DefineObject (yyvsp[-2].acString, yyvsp[-1].acString, DefaultClass (yyvsp[-3].acString));
                            _eVarScope = FX_OBJECT_SCOPE;
			  ;
    break;}
case 22:
#line 288 "parser.y"
{
			    UpdateObject (yyvsp[-5].acString);
                            _eVarScope = FX_GLOBAL_SCOPE;
			  ;
    break;}
case 23:
#line 299 "parser.y"
{
                            yyval.tExpressionData.eType         = FX_REAL;
                            yyval.tExpressionData.nValue.dValue = yyvsp[0].dValue;
                          ;
    break;}
case 24:
#line 306 "parser.y"
{
                            yyval.tExpressionData.eType         = FX_BOOL;
                            yyval.tExpressionData.nValue.gValue = yyvsp[0].gValue;
                          ;
    break;}
case 25:
#line 313 "parser.y"
{
                            if ( ( yyvsp[-5].tExpressionData.eType != FX_REAL ) || ( yyvsp[-3].tExpressionData.eType != FX_REAL ) || ( yyvsp[-1].tExpressionData.eType != FX_REAL ) )
                            {
                              psl_error ("wrong type for parameter (real expected).");
                              exit (1);
                            }
                            yyval.tExpressionData.eType = FX_COLOR;
                          ;
    break;}
case 26:
#line 324 "parser.y"
{
                            if ( ( yyvsp[-5].tExpressionData.eType != FX_REAL ) || ( yyvsp[-3].tExpressionData.eType != FX_REAL ) || ( yyvsp[-1].tExpressionData.eType != FX_REAL ) )
                            {
                              psl_error ("wrong type for parameter (real expected).");
                              exit (1);
                            }
                            yyval.tExpressionData.eType = FX_VECTOR;
                          ;
    break;}
case 27:
#line 335 "parser.y"
{
                            if ( ( yyvsp[-3].tExpressionData.eType != FX_REAL ) || ( yyvsp[-1].tExpressionData.eType != FX_REAL ) )
                            {
                              psl_error ("wrong type for parameter (real expected).");
                              exit (1);
                            }
                            yyval.tExpressionData.eType = FX_VECTOR2;
                          ;
    break;}
case 28:
#line 346 "parser.y"
{
                            yyval.tExpressionData.eType = FX_STRING;
                          ;
    break;}
case 29:
#line 352 "parser.y"
{
                            yyval.tExpressionData = yyvsp[0].tExpressionData;
                            WRITE_CODE ("push_real " << yyvsp[0].tExpressionData.nValue.dValue << endl);
                          ;
    break;}
case 30:
#line 357 "parser.y"
{
                            yyval.tExpressionData = yyvsp[0].tExpressionData;
                            WRITE_CODE ("push_bool " << yyvsp[0].tExpressionData.nValue.gValue << endl);
                          ;
    break;}
case 31:
#line 362 "parser.y"
{
                            yyval.tExpressionData = yyvsp[0].tExpressionData;
                            WRITE_CODE ("push_color ...\n");
                          ;
    break;}
case 32:
#line 367 "parser.y"
{
                            yyval.tExpressionData = yyvsp[0].tExpressionData;
                            WRITE_CODE ("push_vector ...\n");
                          ;
    break;}
case 33:
#line 372 "parser.y"
{
                            yyval.tExpressionData = yyvsp[0].tExpressionData;
                            WRITE_CODE ("push_vector2 ...\n");
                          ;
    break;}
case 34:
#line 377 "parser.y"
{
                            yyval.tExpressionData = yyvsp[0].tExpressionData;
                            WRITE_CODE ("push_string ...\n");
                          ;
    break;}
case 35:
#line 382 "parser.y"
{;
    break;}
case 36:
#line 384 "parser.y"
{
                            yyval.tExpressionData.eType = GetTypeCode (yyvsp[0].acString);
                          ;
    break;}
case 37:
#line 388 "parser.y"
{;
    break;}
case 38:
#line 392 "parser.y"
{
                            WRITE_CODE ("call " << yyvsp[-3].acString << endl);
                          ;
    break;}
case 40:
#line 399 "parser.y"
{;
    break;}
case 41:
#line 403 "parser.y"
{;
    break;}
case 42:
#line 405 "parser.y"
{;
    break;}
case 43:
#line 409 "parser.y"
{;
    break;}
case 44:
#line 417 "parser.y"
{;
    break;}
case 45:
#line 419 "parser.y"
{;
    break;}
case 46:
#line 423 "parser.y"
{
                            _eVarType = FX_REAL;
                          ;
    break;}
case 48:
#line 428 "parser.y"
{
                            _eVarType = FX_BOOL;
                          ;
    break;}
case 50:
#line 433 "parser.y"
{
                            _eVarType = FX_STRING;
                          ;
    break;}
case 52:
#line 438 "parser.y"
{
                            _eVarType = FX_COLOR;
                          ;
    break;}
case 54:
#line 443 "parser.y"
{
                            _eVarType = FX_VECTOR;
                          ;
    break;}
case 56:
#line 448 "parser.y"
{
                            _eVarType = FX_VECTOR2;
                          ;
    break;}
case 58:
#line 453 "parser.y"
{
                            _eVarType = FX_IMAGE;
                          ;
    break;}
case 60:
#line 458 "parser.y"
{
                            if ( _eVarScope == FX_GLOBAL_SCOPE )
                            {
                              psl_error ("cannot use a complex type for a global variable");
                              exit (1);
                            }
                            _eVarType = GetTypeCode (yyvsp[0].acString);
                          ;
    break;}
case 62:
#line 468 "parser.y"
{
                            psl_error ("unknown type");
                            exit (1);
                          ;
    break;}
case 64:
#line 476 "parser.y"
{;
    break;}
case 65:
#line 478 "parser.y"
{;
    break;}
case 66:
#line 482 "parser.y"
{
                            AddVariable (yyvsp[0].acString);
                          ;
    break;}
case 67:
#line 486 "parser.y"
{
                            if ( _eVarType != yyvsp[0].tExpressionData.eType )
                            {
                              psl_error ("wrong type in assignment");
                              cout << "left = " << (int) _eVarType << ", right = " << (int) yyvsp[0].tExpressionData.eType << endl;
                              exit (1);
                            }
                            AddVariable (yyvsp[-2].acString);
                          ;
    break;}
case 68:
#line 502 "parser.y"
{;
    break;}
case 69:
#line 504 "parser.y"
{;
    break;}
case 70:
#line 508 "parser.y"
{;
    break;}
case 71:
#line 510 "parser.y"
{;
    break;}
case 72:
#line 514 "parser.y"
{
                            /*
                            if ( $1 != $3.eType )
                            {
                              psl_error ("wrong type in assignment");
                              exit (1);
                            }
                            */
                            WRITE_CODE ("pop " << _lvalueName << endl);
                          ;
    break;}
case 73:
#line 527 "parser.y"
{
                            yyval.eType = FX_NONE;
                            _lvalueName = yyvsp[0].acString;
                          ;
    break;}
case 74:
#line 532 "parser.y"
{
                            yyval.eType = FX_NONE;
                            _lvalueName += string (".") + yyvsp[0].acString;
                          ;
    break;}
case 76:
#line 544 "parser.y"
{;
    break;}
case 77:
#line 548 "parser.y"
{;
    break;}
case 78:
#line 550 "parser.y"
{;
    break;}
case 79:
#line 554 "parser.y"
{
                            _tCurrentEvent = yyvsp[-1].acString;
                            SET_CURRENT_CODE();
                            WRITE_CODE ("\nevent " << yyvsp[-1].acString << endl);
                          ;
    break;}
case 80:
#line 560 "parser.y"
{
                            _eVarScope = FX_EVENT_SCOPE;
                          ;
    break;}
case 81:
#line 564 "parser.y"
{
                            _tCurrentEvent = EVENT_INIT_VARIABLES;
                            SET_CURRENT_CODE();
                          ;
    break;}
case 82:
#line 571 "parser.y"
{;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 542 "/usr/lib/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 574 "parser.y"


void psl_error (const char* pkcTEXT)
{

  cerr << endl << TScenePsl::_tInputFileName << "(" << TScenePsl::_dwLineNumber << ") Error: " << pkcTEXT << endl;

}  /* psl_error() */


void PSL_InitParser (void)
{

  if ( DEBUG_CODE )
  {
    _tDebugCodeFile.open ((TScenePsl::_tInputFileName + ".code").c_str());
  }

  InitObjects();

  _ptWorld = new TAggregate();

  TScenePsl::_ptParsedScene->setWorld (_ptWorld);

  _ptCurrentProgram = TScenePsl::_ptParsedScene->globalData();
  _tCurrentEvent    = EVENT_INIT_VARIABLES;
  SET_CURRENT_CODE();
  
}  /* PSL_InitParser() */


void PSL_CloseParser (void)
{

  if ( DEBUG_CODE )
  {
    _tDebugCodeFile.close();
  }

  TScenePsl::_ptParsedScene->globalData()->printDebug();

  _tObjectMap.clear();

}  /* PSL_CloseParser() */


void InitObjects (void)
{
}  /* InitObjects() */


void AddVariable (const string& rktNAME)
{

  TVarReference   tRef;

  if ( _eVarScope == FX_GLOBAL_SCOPE )
  {
    tRef = tHeapManager.addVariable (_eVarType);
    
    TScenePsl::_ptParsedScene->globalData()->addVariable (rktNAME, tRef);
  }
  else if ( _eVarScope == FX_OBJECT_SCOPE )
  {
  }
  else
  {
  }

}  /* AddVariable() */


void AddInstruction (EInstructionCode eCODE)
{

  /*
  TInstruction   tInst;

  tInst.eCode  = eCODE;
  tInst.eType  = eTYPE;
  tInst.nParam = nPARAM;

  _ptCurrentEvent->push_back (tInst);
  */
  
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

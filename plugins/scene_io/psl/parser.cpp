
/*  A Bison parser, made from parser.y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse psl_parse
#define yylex psl_lex
#define yyerror psl_error
#define yylval psl_lval
#define yychar psl_char
#define yydebug psl_debug
#define yynerrs psl_nerrs
#define	T_REAL	258
#define	T_BOOL	259
#define	T_COMPLEX_TYPE	260
#define	T_IDENTIFIER	261
#define	T_QUOTED_STRING	262
#define	T_DEFINE	263
#define	T_CLASS	264
#define	T_EXTENDS	265
#define	T_NEW	266
#define	T_BOX	267
#define	T_CIRCLE	268
#define	T_CONE	269
#define	T_CYLINDER	270
#define	T_DIFFERENCE	271
#define	T_FILTER	272
#define	T_INTERSECTION	273
#define	T_MESH	274
#define	T_PHONG_TRIANGLE	275
#define	T_PLANE	276
#define	T_RECTANGLE	277
#define	T_SPHERE	278
#define	T_TRIANGLE	279
#define	T_UNION	280
#define	T_TYPE_REAL	281
#define	T_TYPE_BOOL	282
#define	T_TYPE_STRING	283
#define	T_TYPE_COLOR	284
#define	T_TYPE_VECTOR	285
#define	T_TYPE_VECTOR2	286
#define	T_TYPE_IMAGE	287
#define	T_TYPE_SCENE	288
#define	T_TYPE_BSDF	289
#define	T_TYPE_CAMERA	290
#define	T_TYPE_LIGHT	291
#define	T_TYPE_MATERIAL	292
#define	T_TYPE_RENDERER	293
#define	T_TYPE_OBJECT	294
#define	T_TYPE_AGGREGATE	295
#define	T_TYPE_OBJECT_FILTER	296
#define	T_TYPE_IMAGE_FILTER	297
#define	UNARY_MINUS	298

#line 19 "parser.y"


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


#line 68 "parser.y"
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



#define	YYFINAL		157
#define	YYFLAG		-32768
#define	YYNTBASE	57

#define YYTRANSLATE(x) ((unsigned)(x) <= 298 ? yytranslate[x] : 103)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    48,
    50,    45,    43,    49,    44,    53,    46,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    56,    51,     2,
    52,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    54,     2,    55,     2,     2,     2,     2,     2,
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
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    47
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,    13,    22,    29,    31,    33,    35,    37,
    39,    41,    43,    45,    48,    50,    55,    56,    58,    60,
    64,    66,    67,    70,    71,    76,    77,    82,    83,    88,
    89,    94,    95,   100,   101,   106,   107,   112,   113,   118,
   119,   124,   126,   130,   132,   136,   138,   141,   144,   147,
   151,   153,   157,   158,   161,   163,   166,   167,   176,   179,
   180,   183,   186,   189,   191,   193,   196,   199,   201,   202,
   206,   210,   211,   219,   220,   227,   228,   235,   236
};

static const short yyrhs[] = {     3,
     0,     4,     0,    29,    48,    63,    49,    63,    49,    63,
    50,     0,    30,    48,    63,    49,    63,    49,    63,    50,
     0,    31,    48,    63,    49,    63,    50,     0,     7,     0,
    57,     0,    58,     0,    59,     0,    60,     0,    61,     0,
    62,     0,     6,     0,    11,     6,     0,    64,     0,     6,
    48,    65,    50,     0,     0,    66,     0,    67,     0,    65,
    49,    67,     0,    63,     0,     0,    68,    69,     0,     0,
    26,    70,    79,    51,     0,     0,    27,    71,    79,    51,
     0,     0,    28,    72,    79,    51,     0,     0,    29,    73,
    79,    51,     0,     0,    30,    74,    79,    51,     0,     0,
    31,    75,    79,    51,     0,     0,    32,    76,    79,    51,
     0,     0,     5,    77,    79,    51,     0,     0,     6,    78,
    79,    51,     0,    80,     0,    79,    49,    80,     0,     6,
     0,     6,    52,    63,     0,    82,     0,    81,    82,     0,
    83,    51,     0,    64,    51,     0,    84,    52,    63,     0,
     6,     0,    84,    53,     6,     0,     0,    68,    86,     0,
    87,     0,    86,    87,     0,     0,     6,    48,    65,    50,
    54,    88,    89,    55,     0,    68,    81,     0,     0,    90,
    69,     0,    90,    91,     0,    90,    92,     0,    97,     0,
    99,     0,     8,   101,     0,     8,    95,     0,     6,     0,
     0,    56,    10,     6,     0,    56,     9,     6,     0,     0,
    33,    93,    94,    54,    96,    85,    55,     0,     0,    33,
    94,    54,    98,    85,    55,     0,     0,     5,    94,    54,
   100,    85,    55,     0,     0,     5,    93,    94,    54,   102,
    85,    55,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   151,   158,   165,   176,   187,   198,   204,   208,   212,   216,
   220,   224,   228,   230,   234,   238,   242,   243,   247,   249,
   253,   261,   263,   267,   271,   272,   276,   277,   281,   282,
   286,   287,   291,   292,   296,   297,   301,   302,   311,   312,
   317,   320,   322,   326,   330,   346,   348,   352,   354,   358,
   370,   374,   384,   385,   389,   391,   395,   400,   404,   412,
   413,   415,   417,   421,   423,   427,   429,   433,   439,   443,
   453,   460,   465,   472,   478,   488,   498,   508,   513
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
"'+'","'-'","'*'","'/'","UNARY_MINUS","'('","','","')'","';'","'='","'.'","'{'",
"'}'","':'","real_expression","bool_expression","color_expression","vector_expression",
"vector2_expression","string_expression","expression","function_call","function_params",
"function_params1","function_param","variables","variable","@1","@2","@3","@4",
"@5","@6","@7","@8","@9","var_list","var","sentences","sentence","assignment",
"lvalue","program","event_list","event","@10","code","everything","instance",
"definition","name","class","scene_def","@11","scene_instance","@12","object_instance",
"@13","any_def","@14", NULL
};
#endif

static const short yyr1[] = {     0,
    57,    58,    59,    60,    61,    62,    63,    63,    63,    63,
    63,    63,    63,    63,    63,    64,    65,    65,    66,    66,
    67,    68,    68,    70,    69,    71,    69,    72,    69,    73,
    69,    74,    69,    75,    69,    76,    69,    77,    69,    78,
    69,    79,    79,    80,    80,    81,    81,    82,    82,    83,
    84,    84,    85,    85,    86,    86,    88,    87,    89,    90,
    90,    90,    90,    91,    91,    92,    92,    93,    94,    94,
    94,    96,    95,    98,    97,   100,    99,   102,   101
};

static const short yyr2[] = {     0,
     1,     1,     8,     8,     6,     1,     1,     1,     1,     1,
     1,     1,     1,     2,     1,     4,     0,     1,     1,     3,
     1,     0,     2,     0,     4,     0,     4,     0,     4,     0,
     4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
     4,     1,     3,     1,     3,     1,     2,     2,     2,     3,
     1,     3,     0,     2,     1,     2,     0,     8,     2,     0,
     2,     2,     2,     1,     1,     2,     2,     1,     0,     3,
     3,     0,     7,     0,     6,     0,     6,     0,     7
};

static const short yydefact[] = {    60,
     0,    38,    40,     0,    24,    26,    28,    30,    32,    34,
    36,    69,    61,    62,    63,    64,    65,     0,     0,     0,
     0,     0,     0,    67,    66,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    44,     0,    42,    76,     0,
    68,    69,    69,     0,     0,     0,     0,     0,     0,     0,
    74,    71,    70,     0,     0,    39,    22,    41,     0,     0,
    25,    27,    29,    31,    33,    35,    37,    22,     1,     2,
    13,     6,     0,     0,     0,     0,     7,     8,     9,    10,
    11,    12,    45,    15,    43,     0,     0,    78,    72,     0,
    17,    14,     0,     0,     0,    38,    40,    23,    54,    55,
    77,    22,    22,    75,    21,     0,    18,    19,     0,     0,
     0,    17,     0,    56,     0,     0,     0,    16,     0,     0,
     0,     0,    79,    73,    20,     0,     0,     0,     0,     0,
     0,     5,    57,     0,     0,    22,     3,     4,     0,     0,
    51,     0,    59,    46,     0,     0,    58,    49,    51,    47,
    48,     0,     0,    50,    52,     0,     0
};

static const short yydefgoto[] = {    77,
    78,    79,    80,    81,    82,   105,    84,   106,   107,   108,
    86,    98,    26,    27,    28,    29,    30,    31,    32,    19,
    21,    37,    38,   143,   144,   145,   146,    87,    99,   100,
   136,   140,     1,    14,    15,    42,    20,    24,   103,    16,
    68,    17,    57,    25,   102
};

static const short yypact[] = {-32768,
    18,   -40,-32768,     5,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   -50,-32768,-32768,-32768,-32768,-32768,    19,    29,   -43,
    29,    36,    36,-32768,-32768,    29,    29,    29,    29,    29,
    29,    29,     2,    65,    69,    35,   -34,-32768,-32768,   -30,
-32768,   -50,   -50,   -29,   -24,     3,     4,    10,    11,    21,
-32768,-32768,-32768,     1,    29,-32768,    42,-32768,    34,    45,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    42,-32768,-32768,
    60,-32768,    94,    61,    62,    64,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,    52,    56,-32768,-32768,    58,
     1,-32768,     1,     1,     1,-32768,    66,-32768,   109,-32768,
-32768,    42,    42,-32768,-32768,    14,-32768,-32768,    67,    68,
    70,     1,    66,-32768,    71,    72,     1,-32768,     1,     1,
     1,    24,-32768,-32768,-32768,    73,    74,    78,    76,     1,
     1,-32768,-32768,    79,    81,-32768,-32768,-32768,    63,    77,
    -5,    82,   112,-32768,    83,    33,-32768,-32768,    60,-32768,
-32768,     1,   114,-32768,-32768,   121,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,   -54,  -130,    12,-32768,     8,
    -1,   135,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,    75,    84,-32768,    -6,-32768,-32768,   -66,-32768,    39,
-32768,-32768,-32768,-32768,-32768,   117,    -9,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768
};


#define	YYLAST		140


static const short yytable[] = {    83,
   -40,    90,    33,    69,    70,    18,    71,    72,   142,    22,
    39,    73,   142,   -69,    55,    18,    56,   156,    55,    55,
    58,    61,     2,     3,    55,     4,    62,    34,    35,    74,
    75,    76,    59,    60,    36,   115,   116,    23,   109,   110,
   111,    41,    91,     5,     6,     7,     8,     9,    10,    11,
    12,    55,    55,    63,    64,    51,    96,    97,    55,    55,
    65,    66,   117,   118,   126,   127,   128,    96,   141,    55,
    52,    67,   117,   129,    53,   134,   135,     5,     6,     7,
     8,     9,    10,    11,   152,   153,    54,    88,     5,     6,
     7,     8,     9,    10,    11,    40,   -53,   154,    89,    92,
    44,    45,    46,    47,    48,    49,    50,    91,    93,    94,
   101,    95,   104,   112,   113,   119,   120,   149,   121,   155,
   157,   130,   131,   122,   125,   123,   124,   132,   137,   133,
   138,   147,   148,   151,   139,    13,   150,   114,    85,    43
};

static const short yycheck[] = {    54,
     6,    68,    12,     3,     4,    56,     6,     7,   139,     5,
    54,    11,   143,    54,    49,    56,    51,     0,    49,    49,
    51,    51,     5,     6,    49,     8,    51,     9,    10,    29,
    30,    31,    42,    43,     6,   102,   103,    33,    93,    94,
    95,     6,    48,    26,    27,    28,    29,    30,    31,    32,
    33,    49,    49,    51,    51,    54,     5,     6,    49,    49,
    51,    51,    49,    50,   119,   120,   121,     5,     6,    49,
     6,    51,    49,    50,     6,   130,   131,    26,    27,    28,
    29,    30,    31,    32,    52,    53,    52,    54,    26,    27,
    28,    29,    30,    31,    32,    21,    55,   152,    54,     6,
    26,    27,    28,    29,    30,    31,    32,    48,    48,    48,
    55,    48,    55,    48,     6,    49,    49,     6,    49,     6,
     0,    49,    49,   112,   117,    55,    55,    50,    50,    54,
    50,    55,    51,    51,   136,     1,   143,    99,    55,    23
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/lib/bison.simple"

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
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
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

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

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
     int count;
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
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 196 "/usr/lib/bison.simple"

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
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
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

case 1:
#line 152 "parser.y"
{
                            yyval.tExpressionData.eType         = FX_REAL;
                            yyval.tExpressionData.nValue.dValue = yyvsp[0].dValue;
                          ;
    break;}
case 2:
#line 159 "parser.y"
{
                            yyval.tExpressionData.eType         = FX_BOOL;
                            yyval.tExpressionData.nValue.gValue = yyvsp[0].gValue;
                          ;
    break;}
case 3:
#line 166 "parser.y"
{
                            if ( ( yyvsp[-5].tExpressionData.eType != FX_REAL ) || ( yyvsp[-3].tExpressionData.eType != FX_REAL ) || ( yyvsp[-1].tExpressionData.eType != FX_REAL ) )
                            {
                              psl_error ("wrong type for parameter (real expected).");
                              exit (1);
                            }
                            yyval.tExpressionData.eType          = FX_COLOR;
                          ;
    break;}
case 4:
#line 177 "parser.y"
{
                            if ( ( yyvsp[-5].tExpressionData.eType != FX_REAL ) || ( yyvsp[-3].tExpressionData.eType != FX_REAL ) || ( yyvsp[-1].tExpressionData.eType != FX_REAL ) )
                            {
                              psl_error ("wrong type for parameter (real expected).");
                              exit (1);
                            }
                            yyval.tExpressionData.eType         = FX_VECTOR;
                          ;
    break;}
case 5:
#line 188 "parser.y"
{
                            if ( ( yyvsp[-3].tExpressionData.eType != FX_REAL ) || ( yyvsp[-1].tExpressionData.eType != FX_REAL ) )
                            {
                              psl_error ("wrong type for parameter (real expected).");
                              exit (1);
                            }
                            yyval.tExpressionData.eType         = FX_VECTOR2;
                          ;
    break;}
case 6:
#line 199 "parser.y"
{
                            yyval.tExpressionData.eType         = FX_STRING;
                          ;
    break;}
case 7:
#line 205 "parser.y"
{
                            yyval.tExpressionData = yyvsp[0].tExpressionData;
                          ;
    break;}
case 8:
#line 209 "parser.y"
{
                            yyval.tExpressionData = yyvsp[0].tExpressionData;
                          ;
    break;}
case 9:
#line 213 "parser.y"
{
                            yyval.tExpressionData = yyvsp[0].tExpressionData;
                          ;
    break;}
case 10:
#line 217 "parser.y"
{
                            yyval.tExpressionData = yyvsp[0].tExpressionData;
                          ;
    break;}
case 11:
#line 221 "parser.y"
{
                            yyval.tExpressionData = yyvsp[0].tExpressionData;
                          ;
    break;}
case 12:
#line 225 "parser.y"
{
                            yyval.tExpressionData = yyvsp[0].tExpressionData;
                          ;
    break;}
case 13:
#line 229 "parser.y"
{;
    break;}
case 14:
#line 231 "parser.y"
{
                            yyval.tExpressionData.eType = GetTypeCode (yyvsp[0].acString);
                          ;
    break;}
case 15:
#line 235 "parser.y"
{;
    break;}
case 16:
#line 239 "parser.y"
{;
    break;}
case 18:
#line 244 "parser.y"
{;
    break;}
case 19:
#line 248 "parser.y"
{;
    break;}
case 20:
#line 250 "parser.y"
{;
    break;}
case 21:
#line 254 "parser.y"
{;
    break;}
case 22:
#line 262 "parser.y"
{;
    break;}
case 23:
#line 264 "parser.y"
{;
    break;}
case 24:
#line 268 "parser.y"
{
                            _eVarType = FX_REAL;
                          ;
    break;}
case 26:
#line 273 "parser.y"
{
                            _eVarType = FX_BOOL;
                          ;
    break;}
case 28:
#line 278 "parser.y"
{
                            _eVarType = FX_STRING;
                          ;
    break;}
case 30:
#line 283 "parser.y"
{
                            _eVarType = FX_COLOR;
                          ;
    break;}
case 32:
#line 288 "parser.y"
{
                            _eVarType = FX_VECTOR;
                          ;
    break;}
case 34:
#line 293 "parser.y"
{
                            _eVarType = FX_VECTOR2;
                          ;
    break;}
case 36:
#line 298 "parser.y"
{
                            _eVarType = FX_IMAGE;
                          ;
    break;}
case 38:
#line 303 "parser.y"
{
                            if ( _eVarScope == FX_GLOBAL_SCOPE )
                            {
                              psl_error ("cannot use a complex type for a global variable");
                              exit (1);
                            }
                            _eVarType = GetTypeCode (yyvsp[0].acString);
                          ;
    break;}
case 40:
#line 313 "parser.y"
{
                            psl_error ("unknown type");
                            exit (1);
                          ;
    break;}
case 42:
#line 321 "parser.y"
{;
    break;}
case 43:
#line 323 "parser.y"
{;
    break;}
case 44:
#line 327 "parser.y"
{
                            AddVariable (yyvsp[0].acString);
                          ;
    break;}
case 45:
#line 331 "parser.y"
{
                            if ( _eVarType != yyvsp[0].tExpressionData.eType )
                            {
                              psl_error ("wrong type in assignment");
                              cout << "left = " << _eVarType << ", right = " << yyvsp[0].tExpressionData.eType << endl;
                              exit (1);
                            }
                            AddVariable (yyvsp[-2].acString);
                          ;
    break;}
case 46:
#line 347 "parser.y"
{;
    break;}
case 47:
#line 349 "parser.y"
{;
    break;}
case 48:
#line 353 "parser.y"
{;
    break;}
case 49:
#line 355 "parser.y"
{;
    break;}
case 50:
#line 359 "parser.y"
{
                            /*
                            if ( $1 != $3.eType )
                            {
                              psl_error ("wrong type in assignment");
                              exit (1);
                            }
                            */
                          ;
    break;}
case 51:
#line 371 "parser.y"
{
                            yyval.eType = FX_NONE;
                          ;
    break;}
case 52:
#line 375 "parser.y"
{
                            yyval.eType = FX_NONE;
                          ;
    break;}
case 54:
#line 386 "parser.y"
{;
    break;}
case 55:
#line 390 "parser.y"
{;
    break;}
case 56:
#line 392 "parser.y"
{;
    break;}
case 57:
#line 396 "parser.y"
{
                            _eVarScope      = FX_EVENT_SCOPE;
                            _ptCurrentEvent = _tDataStack.top()->program()->getEventCode (yyvsp[-4].acString);
                          ;
    break;}
case 58:
#line 401 "parser.y"
{;
    break;}
case 59:
#line 405 "parser.y"
{;
    break;}
case 61:
#line 414 "parser.y"
{;
    break;}
case 62:
#line 416 "parser.y"
{;
    break;}
case 63:
#line 418 "parser.y"
{;
    break;}
case 64:
#line 422 "parser.y"
{;
    break;}
case 65:
#line 424 "parser.y"
{;
    break;}
case 66:
#line 428 "parser.y"
{;
    break;}
case 67:
#line 430 "parser.y"
{;
    break;}
case 68:
#line 434 "parser.y"
{
			    strcpy (yyval.acString, yyvsp[0].acString);
			  ;
    break;}
case 69:
#line 440 "parser.y"
{
                            strcpy (yyval.acString, "");
                          ;
    break;}
case 70:
#line 444 "parser.y"
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
case 71:
#line 454 "parser.y"
{
			    _ptParent = NULL;
			    strcpy (yyval.acString, yyvsp[0].acString);
			  ;
    break;}
case 72:
#line 461 "parser.y"
{
			    DefineObject (yyvsp[-2].acString, yyvsp[-1].acString, "Scene");
                            _eVarScope = FX_OBJECT_SCOPE;
			  ;
    break;}
case 73:
#line 466 "parser.y"
{
			    UpdateObject (yyvsp[-5].acString);
                            _eVarScope = FX_GLOBAL_SCOPE;
			  ;
    break;}
case 74:
#line 473 "parser.y"
{
			    _ptData = TScenePsl::_ptParsedScene;
			    _tDataStack.push (_ptData);
                            _eVarScope = FX_OBJECT_SCOPE;
			  ;
    break;}
case 75:
#line 479 "parser.y"
{
			    _tDataStack.pop();
                            TScenePsl::_ptParsedScene->sendEvent ("init");
                            _eVarScope = FX_GLOBAL_SCOPE;

//                            TScenePsl::_ptParsedScene->globalData()->printDebug();
			  ;
    break;}
case 76:
#line 489 "parser.y"
{
                            if ( strcmp (yyvsp[-2].acString, "Object") && strcmp (yyvsp[-2].acString, "Aggregate") )
                            {
                              psl_error ("only objects and scene can be instanced");
                              exit (1);
                            }
			    CreateObject (yyvsp[-1].acString, "");
                            _eVarScope = FX_OBJECT_SCOPE;
			  ;
    break;}
case 77:
#line 499 "parser.y"
{
                            _tDataStack.top()->sendEvent ("init");
                            _eVarScope = FX_GLOBAL_SCOPE;

//                            _tDataStack.top()->program()->printDebug();
			    _tDataStack.pop();
			  ;
    break;}
case 78:
#line 509 "parser.y"
{
			    DefineObject (yyvsp[-2].acString, yyvsp[-1].acString, DefaultClass (yyvsp[-3].acString));
                            _eVarScope = FX_OBJECT_SCOPE;
			  ;
    break;}
case 79:
#line 514 "parser.y"
{
			    UpdateObject (yyvsp[-5].acString);
                            _eVarScope = FX_GLOBAL_SCOPE;
			  ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 498 "/usr/lib/bison.simple"

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
}
#line 520 "parser.y"


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

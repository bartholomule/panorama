
/*  A Bison parser, made from parser.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse rt_parse
#define yylex rt_lex
#define yyerror rt_error
#define yylval rt_lval
#define yychar rt_char
#define yydebug rt_debug
#define yynerrs rt_nerrs
#define	T_BOOL	257
#define	T_REAL	258
#define	T_INTEGER	259
#define	T_IDENTIFIER	260
#define	T_QUOTED_STRING	261
#define	T_BLUE	262
#define	T_CAMERA	263
#define	T_CLASS	264
#define	T_DEFINE	265
#define	T_EXTENDS	266
#define	T_FILTER	267
#define	T_GREEN	268
#define	T_LIGHT	269
#define	T_OUTPUT	270
#define	T_RED	271
#define	T_RENDERER	272
#define	AND_L	273
#define	OR_L	274
#define	EQUAL	275
#define	NOT_EQ	276
#define	GREATER	277
#define	GREATER_EQ	278
#define	LESS	279
#define	LESS_EQ	280
#define	PARAM	281
#define	DEFINED	282
#define	THIS	283

#line 69 "parser.y"


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
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		141
#define	YYFLAG		-32768
#define	YYNTBASE	44

#define YYTRANSLATE(x) ((unsigned)(x) <= 283 ? yytranslate[x] : 70)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    37,     2,     2,     2,     2,     2,     2,    38,
    39,    32,    30,    40,    31,     2,    33,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    34,    41,
    43,    42,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    35,     2,    36,     2,     2,     2,     2,     2,
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
    27,    28,    29
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     5,     8,    13,    19,    21,    22,    26,    30,
    33,    35,    37,    41,    43,    47,    49,    53,    57,    59,
    63,    67,    71,    75,    77,    81,    85,    87,    91,    95,
    97,   100,   103,   106,   108,   111,   114,   116,   118,   120,
   124,   126,   128,   130,   132,   134,   136,   140,   145,   152,
   161,   169,   175,   177,   179,   182,   185,   188,   192,   196,
   200,   202,   206,   208,   210,   214,   218,   222,   224,   226,
   228,   230,   232,   234,   236,   238
};

static const short yyrhs[] = {    -1,
    44,    49,    34,     0,    44,    45,     0,    11,    62,    49,
    34,     0,    11,    69,    62,    46,    34,     0,    62,     0,
     0,    63,    47,    48,     0,    35,    64,    36,     0,    35,
    36,     0,    50,     0,    51,     0,    50,    20,    51,     0,
    52,     0,    51,    19,    52,     0,    53,     0,    52,    21,
    53,     0,    52,    22,    53,     0,    54,     0,    54,    24,
    54,     0,    54,    23,    54,     0,    54,    26,    54,     0,
    54,    25,    54,     0,    55,     0,    54,    30,    55,     0,
    54,    31,    55,     0,    56,     0,    55,    32,    56,     0,
    55,    33,    56,     0,    57,     0,    37,    56,     0,    30,
    56,     0,    31,    56,     0,     7,     0,    27,    57,     0,
    28,    62,     0,     3,     0,     5,     0,     4,     0,    38,
    49,    39,     0,    59,     0,    60,     0,    61,     0,    29,
     0,    46,     0,    58,     0,    68,    38,    39,     0,    68,
    38,    49,    39,     0,    68,    38,    49,    40,    49,    39,
     0,    35,    17,    49,    14,    49,     8,    49,    36,     0,
    41,    49,    40,    49,    40,    49,    42,     0,    41,    49,
    40,    49,    42,     0,     6,     0,     6,     0,    10,     6,
     0,    65,    34,     0,     1,    34,     0,    64,    65,    34,
     0,    64,     1,    34,     0,     6,    43,    49,     0,    49,
     0,    69,    43,    49,     0,    66,     0,    67,     0,    13,
    43,    46,     0,    15,    43,    46,     0,    16,    43,    46,
     0,    62,     0,    69,     0,     8,     0,    10,     0,    11,
     0,    12,     0,    14,     0,    17,     0,    18,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   187,   191,   216,   222,   241,   262,   268,   274,   283,   287,
   293,   302,   309,   318,   325,   334,   342,   384,   425,   433,
   438,   443,   448,   455,   462,   475,   488,   495,   507,   521,
   528,   535,   542,   555,   563,   569,   582,   588,   594,   601,
   608,   613,   618,   623,   628,   633,   636,   660,   687,   718,
   738,   755,   764,   779,   800,   808,   817,   822,   826,   833,
   838,   886,   891,   895,   901,   933,   974,  1009,  1013,  1020,
  1025,  1030,  1035,  1040,  1045,  1050
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","T_BOOL",
"T_REAL","T_INTEGER","T_IDENTIFIER","T_QUOTED_STRING","T_BLUE","T_CAMERA","T_CLASS",
"T_DEFINE","T_EXTENDS","T_FILTER","T_GREEN","T_LIGHT","T_OUTPUT","T_RED","T_RENDERER",
"AND_L","OR_L","EQUAL","NOT_EQ","GREATER","GREATER_EQ","LESS","LESS_EQ","PARAM",
"DEFINED","THIS","'+'","'-'","'*'","'/'","';'","'{'","'}'","'!'","'('","')'",
"','","'<'","'>'","'='","everything","definition","instance","@1","param_block",
"expression","prec_8","prec_7","prec_6","prec_5","prec_4","prec_3","prec_2",
"prec_1","function_call","color","vector3","vector2","name","class","params",
"param","object_param","scene_param","potential_name","reserved_words", NULL
};
#endif

static const short yyr1[] = {     0,
    44,    44,    44,    45,    45,    46,    47,    46,    48,    48,
    49,    50,    50,    51,    51,    52,    52,    52,    53,    53,
    53,    53,    53,    54,    54,    54,    55,    55,    55,    56,
    56,    56,    56,    57,    57,    57,    57,    57,    57,    57,
    57,    57,    57,    57,    57,    57,    58,    58,    58,    59,
    60,    61,    62,    63,    63,    64,    64,    64,    64,    65,
    65,    65,    65,    65,    66,    67,    67,    68,    68,    69,
    69,    69,    69,    69,    69,    69
};

static const short yyr2[] = {     0,
     0,     3,     2,     4,     5,     1,     0,     3,     3,     2,
     1,     1,     3,     1,     3,     1,     3,     3,     1,     3,
     3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
     2,     2,     2,     1,     2,     2,     1,     1,     1,     3,
     1,     1,     1,     1,     1,     1,     3,     4,     6,     8,
     7,     5,     1,     1,     2,     2,     2,     3,     3,     3,
     1,     3,     1,     1,     3,     3,     3,     1,     1,     1,
     1,     1,     1,     1,     1,     1
};

static const short yydefact[] = {     1,
     0,    37,    39,    38,    53,    34,    70,    71,    72,    73,
    74,    75,    76,     0,     0,    44,     0,     0,     0,     0,
     0,     0,     3,    45,     0,    11,    12,    14,    16,    19,
    24,    27,    30,    46,    41,    42,    43,     6,     7,     0,
    69,    55,    53,    71,    72,     0,     0,    35,    36,    32,
    33,     0,    31,     0,     0,     2,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    40,     0,    13,    15,    17,    18,    21,
    20,    23,    22,    25,    26,    28,    29,     0,     8,    47,
     0,     4,     0,     0,     6,     0,     0,     0,    53,     0,
     0,     0,    10,    61,     0,     0,    63,    64,    69,    48,
     0,     5,     0,     0,    52,    57,     0,     0,     0,     0,
     0,     9,     0,    56,     0,     0,     0,     0,    60,    65,
    66,    67,    59,    58,    62,    49,     0,    51,    50,     0,
     0
};

static const short yydefgoto[] = {     1,
    23,    24,    69,    89,   104,    26,    27,    28,    29,    30,
    31,    32,    33,    34,    35,    36,    37,    38,    39,   105,
   106,   107,   108,    40,    41
};

static const short yypact[] = {-32768,
   125,-32768,-32768,-32768,   -31,-32768,-32768,    10,    16,-32768,
-32768,-32768,-32768,    32,    19,-32768,   281,   281,   -10,   281,
   281,   281,-32768,-32768,    -2,    21,    29,    36,-32768,   -13,
    43,-32768,-32768,-32768,-32768,-32768,-32768,    28,-32768,    30,
-32768,-32768,-32768,-32768,-32768,   281,    19,-32768,-32768,-32768,
-32768,   281,-32768,    40,    31,-32768,   281,   281,   281,   281,
   281,   281,   281,   281,   281,   281,   281,   281,    52,   242,
    54,    13,    75,-32768,   281,    29,    36,-32768,-32768,    47,
    47,    47,    47,    43,    43,-32768,-32768,   164,-32768,-32768,
    42,-32768,    10,    56,-32768,   281,   -11,    57,   -29,    49,
    50,    51,-32768,-32768,   203,    62,-32768,-32768,    55,-32768,
   281,-32768,    91,   281,-32768,-32768,   281,    13,    13,    13,
    66,-32768,    67,-32768,   281,    63,   281,    61,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,    68,-32768,-32768,   105,
-32768
};

static const short yypgoto[] = {-32768,
-32768,   -64,-32768,-32768,    -1,-32768,    58,    48,    24,     1,
    20,   -15,    93,-32768,-32768,-32768,-32768,     0,-32768,-32768,
     3,-32768,-32768,-32768,    -8
};


#define	YYLAST		322


static const short yytable[] = {    25,
    47,    50,    51,   -54,    53,   -54,    52,    94,    46,    61,
    62,    63,    64,   117,    49,    42,    65,    66,     5,    54,
    55,    43,    93,     7,    43,    44,    45,    10,   114,    11,
   115,    56,    12,    13,     2,     3,     4,     5,     6,     7,
    57,     8,    45,    10,    71,    11,    72,    58,    12,    13,
    73,    86,    87,   130,   131,   132,    59,    60,    14,    15,
    16,    80,    81,    82,    83,   -68,    19,    70,    91,    21,
    75,    95,    22,    97,    67,    68,    65,    66,    74,   109,
   110,   111,    78,    79,    84,    85,    88,    92,    96,   112,
   116,   118,   119,   120,   113,   124,   109,   125,   127,   133,
   134,   136,   138,   139,   141,    77,    48,   123,     0,   126,
     0,     0,   128,     0,    76,   129,     0,    95,    95,    95,
     0,     0,     0,   135,   140,   137,     0,     2,     3,     4,
     5,     6,     7,     0,     8,     9,    10,     0,    11,     0,
     0,    12,    13,     0,     0,     0,     0,     0,     0,     0,
     0,    14,    15,    16,    17,    18,     0,     0,     0,    19,
     0,    20,    21,     0,    98,    22,     2,     3,     4,    99,
     6,     7,     0,     8,    45,    10,   100,    11,   101,   102,
    12,    13,     0,     0,     0,     0,     0,     0,     0,     0,
    14,    15,    16,    17,    18,     0,     0,     0,    19,   103,
    20,    21,     0,   121,    22,     2,     3,     4,    99,     6,
     7,     0,     8,    45,    10,   100,    11,   101,   102,    12,
    13,     0,     0,     0,     0,     0,     0,     0,     0,    14,
    15,    16,    17,    18,     0,     0,     0,    19,   122,    20,
    21,     0,     0,    22,     2,     3,     4,     5,     6,     7,
     0,     8,    45,    10,     0,    11,     0,     0,    12,    13,
     0,     0,     0,     0,     0,     0,     0,     0,    14,    15,
    16,    17,    18,     0,     0,     0,    19,     0,    20,    21,
    90,     0,    22,     2,     3,     4,     5,     6,     7,     0,
     8,    45,    10,     0,    11,     0,     0,    12,    13,     0,
     0,     0,     0,     0,     0,     0,     0,    14,    15,    16,
    17,    18,     0,     0,     0,    19,     0,    20,    21,     0,
     0,    22
};

static const short yycheck[] = {     1,
     9,    17,    18,    35,    20,    35,    17,    72,     9,    23,
    24,    25,    26,    43,    15,     6,    30,    31,     6,    21,
    22,     6,    10,     8,     6,    10,    11,    12,    40,    14,
    42,    34,    17,    18,     3,     4,     5,     6,     7,     8,
    20,    10,    11,    12,    46,    14,    47,    19,    17,    18,
    52,    67,    68,   118,   119,   120,    21,    22,    27,    28,
    29,    61,    62,    63,    64,    38,    35,    38,    70,    38,
    40,    72,    41,    75,    32,    33,    30,    31,    39,    88,
    39,    40,    59,    60,    65,    66,    35,    34,    14,    34,
    34,    43,    43,    43,    96,    34,   105,    43,     8,    34,
    34,    39,    42,    36,     0,    58,    14,   105,    -1,   111,
    -1,    -1,   114,    -1,    57,   117,    -1,   118,   119,   120,
    -1,    -1,    -1,   125,     0,   127,    -1,     3,     4,     5,
     6,     7,     8,    -1,    10,    11,    12,    -1,    14,    -1,
    -1,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    27,    28,    29,    30,    31,    -1,    -1,    -1,    35,
    -1,    37,    38,    -1,     1,    41,     3,     4,     5,     6,
     7,     8,    -1,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    27,    28,    29,    30,    31,    -1,    -1,    -1,    35,    36,
    37,    38,    -1,     1,    41,     3,     4,     5,     6,     7,
     8,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
    28,    29,    30,    31,    -1,    -1,    -1,    35,    36,    37,
    38,    -1,    -1,    41,     3,     4,     5,     6,     7,     8,
    -1,    10,    11,    12,    -1,    14,    -1,    -1,    17,    18,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,
    29,    30,    31,    -1,    -1,    -1,    35,    -1,    37,    38,
    39,    -1,    41,     3,     4,     5,     6,     7,     8,    -1,
    10,    11,    12,    -1,    14,    -1,    -1,    17,    18,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,
    30,    31,    -1,    -1,    -1,    35,    -1,    37,    38,    -1,
    -1,    41
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

#ifndef __cplusplus
#error This bison.simple now requires C++
#endif

/* This file originally came from bison-1.27.  */

/*
---------------------------------------------------------------------------
  This file has been completely hacked (Kevin Harris--18Feb2000), to remove any
  apparent trace of C++ incompatability.  Depending on your choice of YYSTYPE,
  this may NOT work for you (due to macro expansions).  Whatever the choice of
  your YYSTYPE, it must be able to be passed to the array form of new.
  ie. new YYSTYPE[some_size];  must be possible for a valid some_size.
---------------------------------------------------------------------------
 */

#include <string.h>

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

#define YYSTACK_ALLOC new 

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

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
/*
  None of what that just said is of any use any more. (KH -- 18Feb2000)
 */
template <class T>
static void
__yy_memcpy (T *to, T *from, unsigned int count)
{
  register T *t = to;
  register T *f = from;
  register unsigned int i = count;

  while (i-- > 0)
    *t++ = *f++; 
}

#line 160 "bison.simple"

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

  YYSTYPE yyval = YYSTYPE();		/*  the variable used to return		*/
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
#error yyoverflow is NOT supported with this hack.
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
#else /* Not YYLSP_NEEDED */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif /* YYLSP_NEEDED */

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
	  delete[]yyss;
	  delete[]yyvs;
#ifdef YYLSP_NEEDED
	  delete[]yyls;
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
      yyss = new short[yystacksize];
      __yy_memcpy (yyss, yyss1, size);
      yyvs = new YYSTYPE[yystacksize];
      __yy_memcpy (yyvs, yyvs1, size);
#ifdef YYLSP_NEEDED
      yyls = new (YYLTYPE)[yystacksize];
      __yy_memcpy (yyls, yyls1, size);
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

#line 444 "bison.simple"
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
#line 188 "parser.y"
{
			    report_reduction("everything <-- nothing");
			  ;
    break;}
case 2:
#line 192 "parser.y"
{
			    report_reduction("everything <-- everything expression ';'");
			    magic_pointer<TAttribObject> ptobj = get_object(yyvsp[-1].ptAttribute);
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
			      magic_pointer<TProcedural> proc = get_procedural_var(yyvsp[-1].ptAttribute, false);
			      if( !!proc )
			      {
				FIXME("Potentially add instance (" + yyvsp[-1].ptAttribute->toString() + " to the global scene");
			      }
			    }			      
			  ;
    break;}
case 3:
#line 217 "parser.y"
{
			    report_reduction("everything <-- everything definition");
			  ;
    break;}
case 4:
#line 223 "parser.y"
{
			    report_reduction("definition <-- DEFINE name expression ;");
			    report_reduction(string("definition <-- DEFINE ") +
					     yyvsp[-2].sIdent + " " + yyvsp[-1].ptAttribute->toString());

			    if( DATAMAP.find(yyvsp[-2].sIdent) != DATAMAP.end() )
			    {
			      rt_warning(string(yyvsp[-2].sIdent) + " redefined here");
			      rt_warning("previously defined here: " + DATAMAP[yyvsp[-2].sIdent].first);
			    }
			    cout << "Defining \"" << string(yyvsp[-2].sIdent) << "\"" << endl;
			    
			    char buffer[1024];
			    sprintf(buffer,"%s line %d",
				    TSceneRT::_tInputFileName.c_str(),
				    int(TSceneRT::_dwLineNumber));
			    DATAMAP[yyvsp[-2].sIdent] = pair<string,attrib_type>(string(buffer),yyvsp[-1].ptAttribute);
			  ;
    break;}
case 5:
#line 242 "parser.y"
{
			    report_reduction("definition <-- DEFINE reserved_words name instance");
			    cerr << "Warning: definition on line "
			         << TSceneRT::_dwLineNumber
				 << " should not have \"" << yyvsp[-3].sIdent << "\" anymore"
				 << endl;

			    if( DATAMAP.find(yyvsp[-2].sIdent) != DATAMAP.end() )
			    {
			      rt_warning(string(yyvsp[-2].sIdent) + " redefined here");
			      rt_warning("previously defined here: " + DATAMAP[yyvsp[-2].sIdent].first);
			    }
			    char buffer[1024];
			    sprintf(buffer,"%s line %d",
				    TSceneRT::_tInputFileName.c_str(),
				    int(TSceneRT::_dwLineNumber));
			    DATAMAP[yyvsp[-3].sIdent] = pair<string,attrib_type>(string(buffer),yyvsp[-1].ptAttribute);
			  ;
    break;}
case 6:
#line 263 "parser.y"
{
			    report_reduction("instance <-- name");
			    report_reduction(string("instance <-- ") + yyvsp[0].sIdent);			    
			    yyval.ptAttribute = Instance(yyvsp[0].sIdent);
                          ;
    break;}
case 7:
#line 269 "parser.y"
{
			    //			    cout << "Creating object..." << endl;
			    CreateObject(yyvsp[0].sIdent,"");
                          ;
    break;}
case 8:
#line 274 "parser.y"
{
			    report_reduction("instance <--  class { params }");
			    report_reduction(string("instance <-- ") + DATA->toString());
			    
			    //			    cout << "Type is " << DATA->AttributeName() << endl;
			    yyval.ptAttribute = DATASTACK.POP();
			  ;
    break;}
case 9:
#line 284 "parser.y"
{
			    report_reduction("param_block <-- { params }");
			  ;
    break;}
case 10:
#line 288 "parser.y"
{
			    report_reduction("param_block <-- { }");
			  ;
    break;}
case 11:
#line 295 "parser.y"
{
			    yyval.ptAttribute = yyvsp[0].ptAttribute;
			    report_reduction("expression <-- prec_8");
			    report_reduction("expression <-- " + yyvsp[0].ptAttribute->toString());
                          ;
    break;}
case 12:
#line 304 "parser.y"
{
			  report_reduction("prec_8 <-- prec_7");
			  report_reduction("prec_8 <-- " + yyvsp[0].ptAttribute->toString());
			  yyval.ptAttribute = yyvsp[0].ptAttribute;
			;
    break;}
case 13:
#line 310 "parser.y"
{
			  report_reduction("prec_8 <-- prec_8 OR prec_7");
			  report_reduction("prec_8 <-- " + yyvsp[-2].ptAttribute->toString() + " OR " + yyvsp[0].ptAttribute->toString());
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_bool(yyvsp[-2].ptAttribute) ||
					       check_get_bool(yyvsp[0].ptAttribute));
			;
    break;}
case 14:
#line 320 "parser.y"
{
			  report_reduction("prec_7 <-- prec_6");
			  report_reduction("prec_7 <-- " + yyvsp[0].ptAttribute->toString());			  
			  yyval.ptAttribute = yyvsp[0].ptAttribute;
			;
    break;}
case 15:
#line 326 "parser.y"
{
			  report_reduction("prec_7 <-- prec_7 AND prec_6");
			  report_reduction("prec_7 <-- " + yyvsp[-2].ptAttribute->toString() + " AND " + yyvsp[0].ptAttribute->toString());
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_bool(yyvsp[-2].ptAttribute) &&
					       check_get_bool(yyvsp[0].ptAttribute));
			;
    break;}
case 16:
#line 337 "parser.y"
{
			  report_reduction("prec_6 <-- prec_5");
			  report_reduction("prec_6 <-- " + yyvsp[0].ptAttribute->toString());			  
			  yyval.ptAttribute = yyvsp[0].ptAttribute;
			;
    break;}
case 17:
#line 343 "parser.y"
{
			  report_reduction("prec_6 <-- prec_6 EQUAL prec_5");
			  if( !types_match(yyvsp[-2].ptAttribute, yyvsp[0].ptAttribute ) )
			  {
			    rt_error( ("Cannot convert " + EAttribType_to_str(yyvsp[0].ptAttribute->eType) +
				       " to " + EAttribType_to_str(yyvsp[-2].ptAttribute->eType)) );
			  }
			  if( yyvsp[-2].ptAttribute->eType == FX_REAL )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(yyvsp[-2].ptAttribute) == check_get_real(yyvsp[0].ptAttribute));
			  }
			  else if( yyvsp[-2].ptAttribute->eType == FX_BOOL )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_bool(yyvsp[-2].ptAttribute) ==
						 check_get_bool(yyvsp[0].ptAttribute));
			  }
			  else if( yyvsp[-2].ptAttribute->eType == FX_VECTOR )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(get_vector(yyvsp[-2].ptAttribute)->tValue ==
						 get_vector(yyvsp[0].ptAttribute)->tValue);
			  }
			  else if( yyvsp[-2].ptAttribute->eType == FX_VECTOR2 )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(get_vector2(yyvsp[-2].ptAttribute)->tValue ==
						 get_vector2(yyvsp[0].ptAttribute)->tValue);
			  }
			  else if( yyvsp[-2].ptAttribute->eType == FX_STRING || yyvsp[-2].ptAttribute->eType == FX_STRING_LIST )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_string(yyvsp[-2].ptAttribute) ==
						 check_get_string(yyvsp[0].ptAttribute));	  
			  }
			  else if( yyvsp[-2].ptAttribute->eType == FX_INTEGER )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(get_int(yyvsp[-2].ptAttribute)->tValue ==
						 get_int(yyvsp[0].ptAttribute)->tValue);	  
			  }			  
			  else
			  {
			    rt_error("I can't compare a " + EAttribType_to_str(yyvsp[0].ptAttribute->eType));
			  }
			;
    break;}
case 18:
#line 385 "parser.y"
{
			  report_reduction("prec_6 <-- prec_6 NOT_EQ prec_5");
			  if( !types_match(yyvsp[-2].ptAttribute, yyvsp[0].ptAttribute ) )
			  {
			    rt_error( ("Cannot convert " + EAttribType_to_str(yyvsp[0].ptAttribute->eType) +
				       " to " + EAttribType_to_str(yyvsp[-2].ptAttribute->eType)) );
			  }
			  if( yyvsp[-2].ptAttribute->eType == FX_REAL )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(yyvsp[-2].ptAttribute) !=
						 check_get_real(yyvsp[0].ptAttribute));
			  }
			  else if( yyvsp[-2].ptAttribute->eType == FX_BOOL )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_bool(yyvsp[-2].ptAttribute) !=
						 check_get_bool(yyvsp[0].ptAttribute));
			  }
			  else if( yyvsp[-2].ptAttribute->eType == FX_VECTOR )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(get_vector(yyvsp[-2].ptAttribute) != get_vector(yyvsp[0].ptAttribute));
			  }
			  else if( yyvsp[-2].ptAttribute->eType == FX_VECTOR2 )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(get_vector2(yyvsp[-2].ptAttribute) != get_vector2(yyvsp[0].ptAttribute));
			  }
			  else if( yyvsp[-2].ptAttribute->eType == FX_STRING || yyvsp[-2].ptAttribute->eType == FX_STRING_LIST )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_string(yyvsp[-2].ptAttribute) != check_get_string(yyvsp[0].ptAttribute));	  
			  }
			  else if( yyvsp[-2].ptAttribute->eType == FX_INTEGER )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(get_int(yyvsp[-2].ptAttribute)->tValue == get_int(yyvsp[0].ptAttribute)->tValue);	  
			  }
			  else
			  {
			    rt_error("I can't compare a " + EAttribType_to_str(yyvsp[0].ptAttribute->eType));
			  }
			;
    break;}
case 19:
#line 427 "parser.y"
{
			  report_reduction("prec_5 <-- prec_4");
			  report_reduction("prec_5 <-- " + yyvsp[0].ptAttribute->toString());			  
			  
			  yyval.ptAttribute = yyvsp[0].ptAttribute;
			;
    break;}
case 20:
#line 434 "parser.y"
{
			  report_reduction("prec_4 <-- prec_6 >= prec_5");
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(yyvsp[-2].ptAttribute) >= check_get_real(yyvsp[0].ptAttribute));
			;
    break;}
case 21:
#line 439 "parser.y"
{
			  report_reduction("prec_4 <-- prec_6 > prec_5");
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(yyvsp[-2].ptAttribute) > check_get_real(yyvsp[0].ptAttribute));
			;
    break;}
case 22:
#line 444 "parser.y"
{
			  report_reduction("prec_4 <-- prec_6 <= prec_5");
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(yyvsp[-2].ptAttribute) <= check_get_real(yyvsp[0].ptAttribute));
			;
    break;}
case 23:
#line 449 "parser.y"
{
			  report_reduction("prec_4 <-- prec_6 < prec_5");
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(check_get_real(yyvsp[-2].ptAttribute) < check_get_real(yyvsp[0].ptAttribute));
			;
    break;}
case 24:
#line 457 "parser.y"
{
			  report_reduction("prec_4 <-- prec_3");
			  report_reduction("prec_4 <-- " + yyvsp[0].ptAttribute->toString());			  
			  yyval.ptAttribute = yyvsp[0].ptAttribute;
			;
    break;}
case 25:
#line 463 "parser.y"
{

			  report_reduction("prec_4 <-- prec_4 + prec_3");
			  report_reduction("prec_4 <-- " + yyvsp[-2].ptAttribute->toString() + " + " + yyvsp[0].ptAttribute->toString());
			  
			  yyval.ptAttribute = add(yyvsp[-2].ptAttribute,yyvsp[0].ptAttribute);
			  if( !yyval.ptAttribute )
			  {
			    rt_error("addition of " + EAttribType_to_str(yyvsp[-2].ptAttribute->eType) +
				     " and " + EAttribType_to_str(yyvsp[0].ptAttribute->eType) + " failed");
			  }
			;
    break;}
case 26:
#line 476 "parser.y"
{
			  report_reduction("prec_4 <-- prec_4 - prec_3");
			  report_reduction("prec_4 <-- " + yyvsp[-2].ptAttribute->toString() + " - " + yyvsp[0].ptAttribute->toString());			  
			  yyval.ptAttribute = sub(yyvsp[-2].ptAttribute,yyvsp[0].ptAttribute);
			  if( !yyval.ptAttribute )
			  {
			    rt_error("subtraction of " + EAttribType_to_str(yyvsp[-2].ptAttribute->eType) +
				     " and " + EAttribType_to_str(yyvsp[0].ptAttribute->eType) + " failed");
			  }
			;
    break;}
case 27:
#line 490 "parser.y"
{
			  report_reduction("prec_3 <-- prec_2");
			  report_reduction("prec_3 <-- " + yyvsp[0].ptAttribute->toString());			  
			  yyval.ptAttribute = yyvsp[0].ptAttribute;
			;
    break;}
case 28:
#line 496 "parser.y"
{
			  report_reduction("prec_3 <-- prec_3 * prec_2");
			  report_reduction("prec_4 <-- " + yyvsp[-2].ptAttribute->toString() + " * " + yyvsp[0].ptAttribute->toString());			  
			  
			  yyval.ptAttribute = mul(yyvsp[-2].ptAttribute,yyvsp[0].ptAttribute);
			  if( !yyval.ptAttribute )
			  {
			    rt_error("multiplication of " + EAttribType_to_str(yyvsp[-2].ptAttribute->eType) +
				     " and " + EAttribType_to_str(yyvsp[0].ptAttribute->eType) + " failed");
			  }
			;
    break;}
case 29:
#line 508 "parser.y"
{
			  report_reduction("prec_3 <-- prec_3 / prec_2");
			  report_reduction("prec_4 <-- " + yyvsp[-2].ptAttribute->toString() + " / " + yyvsp[0].ptAttribute->toString());			  
			  
			  yyval.ptAttribute = div(yyvsp[-2].ptAttribute,yyvsp[0].ptAttribute);
			  if( !yyval.ptAttribute )
			  {
			    rt_error("division of " + EAttribType_to_str(yyvsp[-2].ptAttribute->eType) +
				     " and " + EAttribType_to_str(yyvsp[0].ptAttribute->eType) + " failed");
			  }
			;
    break;}
case 30:
#line 523 "parser.y"
{
			  report_reduction("prec_2 <-- prec_1");
			  report_reduction("prec_2 <-- " + yyvsp[0].ptAttribute->toString());			  
			  yyval.ptAttribute = yyvsp[0].ptAttribute;
			;
    break;}
case 31:
#line 529 "parser.y"
{
			  report_reduction("prec_2 <-- ! prec_2");
			  report_reduction("prec_2 <-- ! " + yyvsp[0].ptAttribute->toString());

			  yyval.ptAttribute = (user_arg_type)new TAttribBool(!check_get_bool(yyvsp[0].ptAttribute));
			;
    break;}
case 32:
#line 536 "parser.y"
{
			  report_reduction("prec_2 <-- + prec_2");
			  report_reduction("prec_2 <-- + " + yyvsp[0].ptAttribute->toString());
			  
			  yyval.ptAttribute = yyvsp[0].ptAttribute;
			;
    break;}
case 33:
#line 543 "parser.y"
{
			  report_reduction("prec_2 <-- - prec_2");
			  report_reduction("prec_2 <-- - " + yyvsp[0].ptAttribute->toString());
			  
			  yyval.ptAttribute = sub((user_arg_type)new TAttribInt(0), yyvsp[0].ptAttribute);
			  if( !yyval.ptAttribute )
			  {
			    rt_error("negation of " + EAttribType_to_str(yyvsp[0].ptAttribute->eType) + " failed");
			  }			  
			;
    break;}
case 34:
#line 557 "parser.y"
{
			  report_reduction("prec_1 <-- quoted_string");
			  report_reduction("prec_1 <-- " + string(yyvsp[0].sIdent));
			  
			  yyval.ptAttribute = (user_arg_type)new TAttribString(yyvsp[0].sIdent);
			;
    break;}
case 35:
#line 564 "parser.y"
{
			  report_reduction("prec_1 <-- PARAM prec_1");
			  
			  FIXME("recovering a paramater (how?)");
			;
    break;}
case 36:
#line 570 "parser.y"
{
			  report_reduction("prec_1 <-- DEFINED name");

			  if( DATAMAP.find(yyvsp[0].sIdent) != DATAMAP.end() )
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(true);
			  }
			  else
			  {
			    yyval.ptAttribute = (user_arg_type)new TAttribBool(false);
			  }
			;
    break;}
case 37:
#line 583 "parser.y"
{
			  report_reduction("prec_1 <-- BOOL");
			  
			  yyval.ptAttribute = (user_arg_type)new TAttribBool(yyvsp[0].gValue);
			;
    break;}
case 38:
#line 589 "parser.y"
{
			  report_reduction("prec_1 <-- INTEGER");
			  
			  yyval.ptAttribute = (user_arg_type)new TAttribInt(yyvsp[0].iValue);
			;
    break;}
case 39:
#line 595 "parser.y"
{
			    report_reduction("prec_1 <-- REAL");
			    
			    yyval.ptAttribute = (user_arg_type)new TAttribReal(yyvsp[0].dValue);
                          ;
    break;}
case 40:
#line 602 "parser.y"
{
			  report_reduction("prec_1 <-- ( expression )");
			  report_reduction("prec_1 <-- ( " + yyvsp[-1].ptAttribute->toString() + " )");

			  yyval.ptAttribute = yyvsp[-1].ptAttribute;
			;
    break;}
case 41:
#line 609 "parser.y"
{
			  report_reduction("prec_1 <-- color");
			  yyval.ptAttribute = (user_arg_type)new TAttribColor(*yyvsp[0].ptColor);
			;
    break;}
case 42:
#line 614 "parser.y"
{
			  report_reduction("prec_1 <-- vector3");
			  yyval.ptAttribute = (user_arg_type)new TAttribVector(*yyvsp[0].ptVector);
			;
    break;}
case 43:
#line 619 "parser.y"
{
			  report_reduction("prec_1 <-- vector2");
			  yyval.ptAttribute = (user_arg_type)new TAttribVector2(*yyvsp[0].ptVector2);
			;
    break;}
case 44:
#line 624 "parser.y"
{
			  report_reduction("prec_1 <-- THIS");
			  yyval.ptAttribute = DATA;
			;
    break;}
case 45:
#line 629 "parser.y"
{
			  report_reduction("prec_1 <-- instance");
			  yyval.ptAttribute = yyvsp[0].ptAttribute;			  
                        ;
    break;}
case 47:
#line 637 "parser.y"
{
			  report_reduction("function_call <-- potential_name ( )");
			  report_reduction("function_call <-- " + string(yyvsp[-2].sIdent) +  "( )");

#if defined(DEBUG_IT)
			  rt_error("about to call a function");
#endif /* defined(DEBUG_IT) */
			  
			  // Lookup using all objects in the current stack,
			  // then check the global table... 
			  TUserFunctionMap functions = all_user_functions();

			  if( functions.find(yyvsp[-2].sIdent) != functions.end() )
			  {
			    user_arg_vector empty_args;
			    yyval.ptAttribute = functions[yyvsp[-2].sIdent]->call(empty_args);
			  }
			  else
			  {
			    rt_error("function " + string(yyvsp[-2].sIdent) + " does not exist");
			    yyval.ptAttribute = (user_arg_type)new TAttribute();
			  }
			;
    break;}
case 48:
#line 661 "parser.y"
{
			  report_reduction("function_call <-- potential_name ( expression )");
			  report_reduction("function_call <-- " + string(yyvsp[-3].sIdent) + "( " + yyvsp[-1].ptAttribute->toString() + " )");
			  
			  
#if defined(DEBUG_IT)
			  rt_error("about to call a function");
#endif /* defined(DEBUG_IT) */
			  
			  // Lookup using all objects in the current stack,
			  // then check the global table...
			  TUserFunctionMap functions = all_user_functions();
			  
			  if( functions.find(yyvsp[-3].sIdent) != functions.end() )
			  {
			    user_arg_vector args;
			    args.push_back(yyvsp[-1].ptAttribute);
			    yyval.ptAttribute = functions[yyvsp[-3].sIdent]->call(args);

			  }
			  else
			  {
			    rt_error("function " + string(yyvsp[-3].sIdent) + " does not exist");
			    yyval.ptAttribute = (user_arg_type)new TAttribute();
			  }			    
			;
    break;}
case 49:
#line 688 "parser.y"
{
			  report_reduction("function_call <-- potential_name ( expression , expression )");
			  report_reduction("function_call <-- " + string(yyvsp[-5].sIdent) + "( " + yyvsp[-3].ptAttribute->toString() + "," + yyvsp[-1].ptAttribute->toString() + " )");
			  
			  
#if defined(DEBUG_IT)
			  rt_error("about to call a function");
#endif /* defined(DEBUG_IT) */
			  
			  // Lookup using all objects in the current stack,
			  // then check the global table...
			  TUserFunctionMap functions = all_user_functions();
			  
			  if( functions.find(yyvsp[-5].sIdent) != functions.end() )
			  {
			    user_arg_vector args;
			    args.push_back(yyvsp[-3].ptAttribute);
			    args.push_back(yyvsp[-1].ptAttribute);			    
			    yyval.ptAttribute = functions[yyvsp[-5].sIdent]->call(args);

			  }
			  else
			  {
			    rt_error("function " + string(yyvsp[-5].sIdent) + " does not exist");
			    yyval.ptAttribute = (user_arg_type)new TAttribute();
			  }			    
			;
    break;}
case 50:
#line 719 "parser.y"
{
			    report_reduction("color <-- { RED expression GREEN expression BLUE expression }");
			    report_reduction("color <-- { RED " + yyvsp[-5].ptAttribute->toString() +
					     " GREEN " + yyvsp[-3].ptAttribute->toString() +
					     " BLUE " + yyvsp[-1].ptAttribute->toString() + " }");

			    double r = check_get_real(yyvsp[-5].ptAttribute);
			    double g = check_get_real(yyvsp[-3].ptAttribute);
			    double b = check_get_real(yyvsp[-1].ptAttribute);

			    cout << "r=" << r << " g=" << g << " b=" << b << endl;
			    TColor* c = new TColor(r,g,b);
			    cerr << "Here's what was really created: ";
			    c->printDebug(""); cerr << endl;
			    
			    yyval.ptColor = magic_pointer<TColor>(c);
			  ;
    break;}
case 51:
#line 739 "parser.y"
{
			    report_reduction("vector3 <-- < expression , expression , expression >");
			    TVector tVector;
			    double x = check_get_real(yyvsp[-5].ptAttribute);
			    double y = check_get_real(yyvsp[-3].ptAttribute);
			    double z = check_get_real(yyvsp[-1].ptAttribute);
#if defined(DEBUG_IT)
			    cout << "Creating vector ("
				 << x << ","
				 << y << ","
				 << z << ")" << endl;
#endif
			    tVector.set (x,y,z);
                            yyval.ptVector = (magic_pointer<TVector>)new TVector(tVector);
			  ;
    break;}
case 52:
#line 756 "parser.y"
{
			    report_reduction("vector2 <-- < expression , expression >");
			    TVector2 tVector2;
			    tVector2.set (check_get_real(yyvsp[-3].ptAttribute), check_get_real(yyvsp[-1].ptAttribute));
                            yyval.ptVector2 = (magic_pointer<TVector2>)new TVector2(tVector2);
			  ;
    break;}
case 53:
#line 773 "parser.y"
{
			    report_reduction("name <-- IDENTIFIER");
			    yyval.sIdent = yyvsp[0].sIdent;
			  ;
    break;}
case 54:
#line 787 "parser.y"
{
			    report_reduction("class <-- : EXTENDS IDENTIFIER");
                            if ( DATAMAP.find (yyvsp[0].sIdent) == DATAMAP.end() )
                            {
			      yyerror ("trying to extend from non existing object");
			      exit (1);
                            }

			    //			    cout << "the type of the parent is " << DATAMAP [$1].second->AttributeName() << endl;
                            PARENT_OBJECT = attr_to_base(DATAMAP [yyvsp[0].sIdent].second);
			    //			    cout << "the parent's classname is " << PARENT_OBJECT->className() << endl;
			    yyval.sIdent = PARENT_OBJECT->className();
			  ;
    break;}
case 55:
#line 801 "parser.y"
{
			    report_reduction("class <-- : CLASS IDENTIFIER");
			    PARENT_OBJECT = (magic_pointer<TBaseClass>)NULL;
			    yyval.sIdent = yyvsp[0].sIdent;
			  ;
    break;}
case 56:
#line 814 "parser.y"
{
			  report_reduction("params <-- param ;");
                        ;
    break;}
case 57:
#line 818 "parser.y"
{
			  report_reduction("params <-- error ;");
			  rt_error("expected parameter expression");
                        ;
    break;}
case 58:
#line 823 "parser.y"
{
			  report_reduction("params <-- params param ;");
			;
    break;}
case 59:
#line 827 "parser.y"
{
			  report_reduction("params <-- params error ;");
			  rt_error("expected parameter expression");
			;
    break;}
case 60:
#line 834 "parser.y"
{
			  report_reduction("param <-- IDENTIFIER = expression");
			  SetParameter (yyvsp[-2].sIdent, yyvsp[0].ptAttribute);
			;
    break;}
case 61:
#line 839 "parser.y"
{
			  report_reduction("param <-- expression");
			  
			  magic_pointer<TAttribObject> ptobj = get_object(yyvsp[0].ptAttribute);

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
				  args.push_back (yyvsp[0].ptAttribute);

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
			    magic_pointer<TProcedural> proc = get_procedural_var(yyvsp[0].ptAttribute, false);
			    if( !!proc )
			    {
			      FIXME("Potentially do something with (" + yyvsp[0].ptAttribute->toString() + ") in the current object");
			    }
			  }
			;
    break;}
case 62:
#line 887 "parser.y"
{
			  report_reduction("param <-- reserved_words = expression");
			  SetParameter (yyvsp[-2].sIdent, yyvsp[0].ptAttribute);			    
			;
    break;}
case 63:
#line 892 "parser.y"
{
			  report_reduction("param <-- object_param");
			;
    break;}
case 64:
#line 896 "parser.y"
{
			  report_reduction("param <-- scene_param");
			;
    break;}
case 65:
#line 902 "parser.y"
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
			    SetParameter(yyvsp[-2].sIdent,yyvsp[0].ptAttribute);
			  }
			;
    break;}
case 66:
#line 934 "parser.y"
{
			  report_reduction("scene_param <-- LIGHT = instance");
			  // This is no longer needed, as there are special
			  // cases for this in the light_instance rule.
			  if( !!yyvsp[0].ptAttribute )
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
			    
			    magic_pointer<TObject> obj = check_get_object(yyvsp[0].ptAttribute);
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
			;
    break;}
case 67:
#line 975 "parser.y"
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
			      magic_pointer<TAttribImageIO> io = get_imageio(yyvsp[0].ptAttribute);
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
			    SetParameter(yyvsp[-2].sIdent,yyvsp[0].ptAttribute);
			  }
			;
    break;}
case 68:
#line 1010 "parser.y"
{
			  report_reduction("potential_name <-- name");
			;
    break;}
case 69:
#line 1014 "parser.y"
{
			  report_reduction("potential_name <-- reserved_words");
			;
    break;}
case 70:
#line 1021 "parser.y"
{
			    report_reduction("reserved_words <-- BLUE");
			    yyval.sIdent = yyvsp[0].sIdent;
			  ;
    break;}
case 71:
#line 1026 "parser.y"
{
			    report_reduction("reserved_words <-- CLASS");
			    yyval.sIdent = yyvsp[0].sIdent;
			  ;
    break;}
case 72:
#line 1031 "parser.y"
{
			    report_reduction("reserved_words <-- DEFINE");
			    yyval.sIdent = yyvsp[0].sIdent;
			  ;
    break;}
case 73:
#line 1036 "parser.y"
{
			    report_reduction("reserved_words <-- EXTENDS");
			    yyval.sIdent = yyvsp[0].sIdent;
			  ;
    break;}
case 74:
#line 1041 "parser.y"
{
			    report_reduction("reserved_words <-- GREEN");
			    yyval.sIdent = yyvsp[0].sIdent;
			  ;
    break;}
case 75:
#line 1046 "parser.y"
{
			    report_reduction("reserved_words <-- RED");
			    yyval.sIdent = yyvsp[0].sIdent;
			  ;
    break;}
case 76:
#line 1051 "parser.y"
{
			    report_reduction("reserved_words <-- RENDERER");
			    yyval.sIdent = yyvsp[0].sIdent;
			  ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 485 "bison.simple"

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

  *++yyvsp = yyval; // POSSIBLE PROBLEM!!!

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
	   (unsigned)x < (sizeof(yytname) / sizeof(char *)); x++)
	if (yycheck[x + yyn] == x)
	  size += strlen(yytname[x]) + 15, count++;
      msg = new char[size + 15];
      if (msg != 0)
      {
	strcpy(msg, "parse error");
	
	if (count < 5)
	{
	  count = 0;
	  for (x = (yyn < 0 ? -yyn : 0);
	       (unsigned)x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	    {
	      strcat(msg, count == 0 ? ", expecting `" : " or `");
	      strcat(msg, yytname[x]);
	      strcat(msg, "'");
	      count++;
	    }
	}
	yyerror(msg);
	delete[]msg;
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
    delete[] yyss; 
    delete[] yyvs; 
#ifdef YYLSP_NEEDED
    delete[] yyls; 
#endif
  }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
  {
    delete[] yyss; 
    delete[] yyvs; 
#ifdef YYLSP_NEEDED
    delete[] yyls;
#endif
    }
  return 1;
}
#line 1057 "parser.y"


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


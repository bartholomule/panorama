
/*  A Bison parser, made from parser.y
 by  GNU Bison version 1.27
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	CONSTANT	257
#define	TEXT	258
#define	STRING	259
#define	INCLUDE	260
#define	IF	261
#define	ELSE	262
#define	DEFINE	263
#define	DEFINED	264
#define	OBJECT	265
#define	SCENE	266
#define	WARNING	267
#define	ERROR	268
#define	PARAM	269
#define	ENV	270
#define	PRINT	271
#define	TYPE	272
#define	ATTRIBS	273
#define	THIS	274
#define	PARENT	275
#define	GLOBAL	276
#define	PLUS	277
#define	MINUS	278
#define	TIMES	279
#define	DIV	280
#define	PLUS_EQ	281
#define	MINUS_EQ	282
#define	TIMES_EQ	283
#define	DIV_EQ	284
#define	DOT	285
#define	AND_L	286
#define	OR_L	287
#define	NOT	288
#define	EQUAL	289
#define	NOT_EQ	290
#define	GREATER_EQ	291
#define	LESS_EQ	292
#define	GREATER	293
#define	LESS	294
#define	ASSIGN	295
#define	DEBUG	296

#line 42 "parser.y"

#define YYERROR_VERBOSE
/*
  basic types possible:
  boolean
  constant (real number)
  std::vector ([ X, Y, Z])
  std::string (text)
  std::string (name) --> reference
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

// A std::vector, used as a stack to see if something should be evaluated. 
static std::vector<bool> evaluate_scope_stack(1,true);
// performs a simple calculation based on the above std::vector to determine if
// something should be evaluated at the current level in the nesting. 
static bool evaluate (void);
 
magic_pointer<Tdynamic_base> current_object;

// TEMP!!!
#include <cstdio> 
extern FILE* yyin;
 
// END OF TEMP!! 
 
 #ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		145
#define	YYFLAG		-32768
#define	YYNTBASE	51

#define YYTRANSLATE(x) ((unsigned)(x) <= 296 ? yytranslate[x] : 79)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
    47,     2,     2,    49,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    43,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    48,     2,    50,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    44,     2,    45,     2,     2,     2,     2,     2,
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
    37,    38,    39,    40,    41,    42
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     3,     6,     9,    11,    13,    14,    21,    26,
    32,    33,    38,    41,    45,    47,    50,    52,    54,    56,
    57,    62,    66,    68,    73,    78,    83,    88,    93,    98,
   103,   107,   111,   115,   116,   123,   125,   128,   131,   133,
   137,   139,   143,   145,   149,   153,   155,   159,   163,   167,
   171,   173,   177,   181,   183,   187,   191,   193,   196,   199,
   202,   204,   206,   208,   212,   214,   216,   218,   220,   223,
   226,   229,   231,   233,   237,   239,   241,   243
};

static const short yyrhs[] = {    52,
     0,     0,    52,    60,     0,     6,     5,     0,    56,     0,
    54,     0,     0,     9,     4,    41,     4,    55,    58,     0,
     9,     4,    41,    56,     0,     9,     4,    41,    65,    43,
     0,     0,    11,     4,    57,    58,     0,    44,    45,     0,
    44,    59,    45,     0,    60,     0,    59,    60,     0,    43,
     0,    53,     0,    63,     0,     0,    63,     8,    61,    58,
     0,    42,    65,    43,     0,    62,     0,    65,    41,    65,
    43,     0,    65,    41,    56,    43,     0,    65,    41,     4,
    58,     0,    65,    27,    65,    43,     0,    65,    28,    65,
    43,     0,    65,    29,    65,    43,     0,    65,    30,    65,
    43,     0,    13,    65,    43,     0,    14,    65,    43,     0,
    17,    65,    43,     0,     0,     7,    46,    65,    47,    64,
    58,     0,    66,     0,    18,    65,     0,    19,    65,     0,
    67,     0,    66,    32,    67,     0,    68,     0,    67,    33,
    68,     0,    69,     0,    68,    35,    69,     0,    68,    36,
    69,     0,    70,     0,    70,    37,    70,     0,    70,    39,
    70,     0,    70,    38,    70,     0,    70,    40,    70,     0,
    71,     0,    70,    23,    71,     0,    70,    24,    71,     0,
    72,     0,    71,    25,    72,     0,    71,    26,    72,     0,
    73,     0,    34,    72,     0,    23,    72,     0,    24,    72,
     0,    74,     0,    76,     0,    75,     0,    74,    31,    77,
     0,    77,     0,    12,     0,    22,     0,     5,     0,    15,
     5,     0,    16,    76,     0,    10,    76,     0,    78,     0,
     3,     0,    46,    65,    47,     0,    20,     0,     4,     0,
    21,     0,    48,    65,    49,    65,    49,    65,    50,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   145,   149,   151,   154,   164,   165,   168,   202,   211,   219,
   228,   240,   250,   252,   255,   257,   260,   262,   263,   267,
   276,   279,   287,   288,   295,   302,   309,   316,   323,   330,
   339,   347,   355,   364,   384,   389,   391,   402,   425,   427,
   430,   432,   435,   437,   452,   469,   471,   472,   473,   474,
   477,   479,   496,   508,   510,   520,   532,   534,   535,   536,
   549,   564,   567,   579,   660,   662,   663,   668,   670,   677,
   693,   698,   699,   700,   701,   708,   714,   721
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","CONSTANT",
"TEXT","STRING","INCLUDE","IF","ELSE","DEFINE","DEFINED","OBJECT","SCENE","WARNING",
"ERROR","PARAM","ENV","PRINT","TYPE","ATTRIBS","THIS","PARENT","GLOBAL","PLUS",
"MINUS","TIMES","DIV","PLUS_EQ","MINUS_EQ","TIMES_EQ","DIV_EQ","DOT","AND_L",
"OR_L","NOT","EQUAL","NOT_EQ","GREATER_EQ","LESS_EQ","GREATER","LESS","ASSIGN",
"DEBUG","';'","'{'","'}'","'('","')'","'['","','","']'","parsed_file","any_trash",
"useful_trash","definition","@1","object_use","@2","scope","statement_list",
"statement","@3","user_message","if_head","@4","expression","prec_8","prec_7",
"prec_6","prec_5","prec_4","prec_3","prec_2","prec_1","dot_chain","ref_element",
"element","text_element","user_vector", NULL
};
#endif

static const short yyr1[] = {     0,
    51,    52,    52,    53,    53,    53,    55,    54,    54,    54,
    57,    56,    58,    58,    59,    59,    60,    60,    60,    61,
    60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
    62,    62,    62,    64,    63,    65,    65,    65,    66,    66,
    67,    67,    68,    68,    68,    69,    69,    69,    69,    69,
    70,    70,    70,    71,    71,    71,    72,    72,    72,    72,
    73,    73,    74,    74,    75,    75,    75,    76,    76,    76,
    76,    76,    76,    76,    76,    77,    77,    78
};

static const short yyr2[] = {     0,
     1,     0,     2,     2,     1,     1,     0,     6,     4,     5,
     0,     4,     2,     3,     1,     2,     1,     1,     1,     0,
     4,     3,     1,     4,     4,     4,     4,     4,     4,     4,
     3,     3,     3,     0,     6,     1,     2,     2,     1,     3,
     1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
     1,     3,     3,     1,     3,     3,     1,     2,     2,     2,
     1,     1,     1,     3,     1,     1,     1,     1,     2,     2,
     2,     1,     1,     3,     1,     1,     1,     7
};

static const short yydefact[] = {     2,
     1,    73,    76,    68,     0,     0,     0,     0,     0,    66,
     0,     0,     0,     0,     0,     0,     0,    75,    77,    67,
     0,     0,     0,     0,    17,     0,     0,    18,     6,     5,
     3,    23,    19,     0,    36,    39,    41,    43,    46,    51,
    54,    57,    61,    63,    62,    65,    72,     4,     0,     0,
    71,    11,     0,     0,    69,    70,     0,    37,    38,    59,
    60,    58,     0,     0,     0,    20,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    31,    32,    33,
    22,    74,     0,     0,     0,     0,     0,     0,    76,     0,
     0,    40,    42,    44,    45,    52,    53,    47,    49,    48,
    50,    55,    56,    64,    34,    76,     9,     0,     0,    12,
     0,    21,    27,    28,    29,    30,    26,    25,    24,     0,
     0,    10,    13,     0,    15,     0,    35,     8,    14,    16,
     0,    78,     0,     0,     0
};

static const short yydefgoto[] = {   143,
     1,    28,    29,   131,    30,    87,   120,   134,    31,    94,
    32,    33,   130,    34,    35,    36,    37,    38,    39,    40,
    41,    42,    43,    44,    45,    46,    47
};

static const short yypact[] = {-32768,
   169,-32768,-32768,-32768,    -3,   -32,    20,   194,    36,-32768,
   250,   250,    37,   194,   250,   250,   250,-32768,-32768,-32768,
   285,   285,   285,   250,-32768,   250,   250,-32768,-32768,-32768,
-32768,-32768,    46,    35,    42,    28,    16,-32768,     9,    19,
-32768,-32768,    75,-32768,-32768,-32768,-32768,-32768,   250,    64,
-32768,-32768,    66,    67,-32768,-32768,    68,-32768,-32768,-32768,
-32768,-32768,    69,    60,    65,-32768,   250,   250,   250,   250,
     7,   285,   285,   285,   285,   285,   285,   285,   285,   285,
   285,   285,   285,    -1,    71,   215,    77,-32768,-32768,-32768,
-32768,-32768,   250,    77,    70,    72,    80,    81,    77,    88,
   105,    28,    16,-32768,-32768,    19,    19,    43,    43,    43,
    43,-32768,-32768,-32768,-32768,   106,-32768,   108,    74,-32768,
   100,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    77,
    77,-32768,-32768,   123,-32768,   250,-32768,-32768,-32768,-32768,
   102,-32768,   153,   154,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,   -50,-32768,   -60,-32768,   -84,-32768,
-32768,-32768,-32768,   -11,-32768,    83,    85,    -2,    21,    27,
   -14,-32768,-32768,-32768,    29,    76,-32768
};


#define	YYLAST		333


static const short yytable[] = {    53,
    54,    48,     3,    57,    58,    59,    60,    61,    62,     2,
    99,     4,    63,    49,    64,    65,     8,     9,    10,    19,
   100,    13,    14,    50,    16,    17,    18,    19,    20,    21,
    22,    76,    77,   122,   135,   117,    51,    85,   127,    52,
    23,    55,    56,    82,    83,    78,    79,    80,    81,   140,
    74,    75,    26,    66,    27,    95,    96,    97,    98,   101,
    73,    67,    68,    69,    70,    76,    77,   112,   113,   137,
   138,   104,   105,    72,   118,    71,     2,     3,     4,     5,
     6,   121,     7,     8,     9,    10,    11,    12,    13,    14,
    15,    16,    17,    18,    19,    20,    21,    22,   108,   109,
   110,   111,   106,   107,    86,    84,    92,    23,    88,    89,
    90,    91,   123,    93,   124,    24,    25,   115,   133,    26,
   119,    27,   125,   126,   141,     2,     3,     4,     5,     6,
   128,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,   129,   136,    -7,
   132,   142,   144,   145,   102,     0,    23,   103,     0,   114,
     0,     0,     0,     0,    24,    25,     0,   139,    26,     0,
    27,     2,     3,     4,     5,     6,     0,     7,     8,     9,
    10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
    20,    21,    22,     0,     0,     0,     2,     0,     4,     0,
     0,     0,    23,     8,     0,     0,     0,     0,    13,    14,
    24,    25,     0,    18,    26,     0,    27,     2,   116,     4,
     0,     0,     0,     0,     8,     9,    10,     0,     0,    13,
    14,     0,    16,    17,    18,    19,    20,    21,    22,    26,
     0,    27,     0,     0,     0,     0,     0,     0,    23,     0,
     0,     0,     2,     3,     4,     0,     0,     0,     0,     8,
    26,    10,    27,     0,    13,    14,     0,    16,    17,    18,
    19,    20,    21,    22,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    23,     0,     0,     0,     2,     3,     4,
     0,     0,     0,     0,     8,    26,    10,    27,     0,    13,
    14,     0,     0,     0,    18,    19,    20,    21,    22,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    23,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    26,     0,    27
};

static const short yycheck[] = {    11,
    12,     5,     4,    15,    16,    17,    21,    22,    23,     3,
     4,     5,    24,    46,    26,    27,    10,    11,    12,    21,
    71,    15,    16,     4,    18,    19,    20,    21,    22,    23,
    24,    23,    24,    94,   119,    86,     8,    49,    99,     4,
    34,     5,    14,    25,    26,    37,    38,    39,    40,   134,
    35,    36,    46,     8,    48,    67,    68,    69,    70,    71,
    33,    27,    28,    29,    30,    23,    24,    82,    83,   130,
   131,    74,    75,    32,    86,    41,     3,     4,     5,     6,
     7,    93,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    78,    79,
    80,    81,    76,    77,    41,    31,    47,    34,    43,    43,
    43,    43,    43,    49,    43,    42,    43,    47,    45,    46,
    44,    48,    43,    43,   136,     3,     4,     5,     6,     7,
    43,     9,    10,    11,    12,    13,    14,    15,    16,    17,
    18,    19,    20,    21,    22,    23,    24,    43,    49,    44,
    43,    50,     0,     0,    72,    -1,    34,    73,    -1,    84,
    -1,    -1,    -1,    -1,    42,    43,    -1,    45,    46,    -1,
    48,     3,     4,     5,     6,     7,    -1,     9,    10,    11,
    12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
    22,    23,    24,    -1,    -1,    -1,     3,    -1,     5,    -1,
    -1,    -1,    34,    10,    -1,    -1,    -1,    -1,    15,    16,
    42,    43,    -1,    20,    46,    -1,    48,     3,     4,     5,
    -1,    -1,    -1,    -1,    10,    11,    12,    -1,    -1,    15,
    16,    -1,    18,    19,    20,    21,    22,    23,    24,    46,
    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,
    -1,    -1,     3,     4,     5,    -1,    -1,    -1,    -1,    10,
    46,    12,    48,    -1,    15,    16,    -1,    18,    19,    20,
    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    34,    -1,    -1,    -1,     3,     4,     5,
    -1,    -1,    -1,    -1,    10,    46,    12,    48,    -1,    15,
    16,    -1,    -1,    -1,    20,    21,    22,    23,    24,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    46,    -1,    48
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

#ifndef __cplusplus
#error This bison.simple now requires C++
#endif

/* This file originally came from bison-1.27.  */

/*
  This file has been completely hacked (Kevin Harris--18Feb2000), to remove any
  apparent trace of C++ incompatability.  Depending on your choice of YYSTYPE,
  this may NOT work for you (due to macro expansions).  Whatever the choice of
  your YYSTYPE, it must be able to be passed to the array form of new.
  ie. new YYSTYPE[some_size];  must be possible for a valid some_size.
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

case 2:
#line 150 "parser.y"
{ ;
    break;}
case 4:
#line 156 "parser.y"
{
  if( evaluate() )
  {
    // fixme!!! I want to be able to open the file given by $2, and use it as
    // input to the parser/scanner.  What does this require?
    FIXME(string(string("inclusion of a file (named \"") + get_string(yyvsp[0]) + "\")").c_str());
  }
;
    break;}
case 7:
#line 170 "parser.y"
{
  if( evaluate() )
  {
    //    FIXME("I have no clue how to make the plugin work...");
    
    std::string class_name = get_string(yyvsp[0]);
    TProcedural* instance = (TProcedural*)TClassManager::_newObject(class_name.c_str(),NULL);
    //    printf("--- Newly allocated object is a %s\n",instance->className().c_str());
    if( instance == NULL )
    {
      std::string   tMessage = std::string ("class ") +  class_name + " does not exist";
      yyerror (tMessage.c_str());
      exit (1);    
    }
    // create an instance of the object...
    current_object = new Tdynamic_object(instance, true);

    //    cout << "--- current_object is:" << current_object << std::endl;
    
    // The dynamic object cloned it... So the memory needs to be freed (not anymore).
    //    delete instance;
    
    put_top(get_string(yyvsp[-2]), current_object);

    //    cout << "--- object in symtab is:" << locate_reference(get_string($2)) << std::endl;
    //    cout << "--- object name is:" << get_string($2) << std::endl;

    //  FIXME("entering a new scope");
    scope_stack.push(new scope_type);
  }
;
    break;}
case 8:
#line 202 "parser.y"
{
  if( evaluate() )
  {
    //  FIXME("leaving a scope");
    scope_stack.pop();
    
    current_object = NULL;
  }
;
    break;}
case 9:
#line 212 "parser.y"
{
  if( evaluate() )
  {
    //   FIXME("definition of a [modified] predefined object");
    put_top(get_string(yyvsp[-2]),yyvsp[0]);
  }
;
    break;}
case 10:
#line 220 "parser.y"
{
  if( evaluate() )
  {
    put_top(get_string(yyvsp[-3]), yyvsp[-1]);
  }
;
    break;}
case 11:
#line 230 "parser.y"
{
  if( evaluate() )
  {
    //  FIXME("entering a new scope");
    scope_stack.push(new scope_type);

    current_object = new Tdynamic_object((TProcedural*)get_object(yyvsp[0]),false);
  }  
;
    break;}
case 12:
#line 240 "parser.y"
{
  if( evaluate() )
  {
    //  FIXME("leaving a scope");
    scope_stack.pop();    
    current_object = NULL;
  }
;
    break;}
case 19:
#line 264 "parser.y"
{
  evaluate_scope_stack.erase(evaluate_scope_stack.end() - 1);
;
    break;}
case 20:
#line 268 "parser.y"
{
  if( evaluate_scope_stack.size() >= 2 )
  {
    // If the if portion was the same as the previous if (outside), cary on.
    evaluate_scope_stack[evaluate_scope_stack.size() - 1] = !evaluate() && evaluate_scope_stack[evaluate_scope_stack.size()-2];
  }
;
    break;}
case 21:
#line 276 "parser.y"
{
  evaluate_scope_stack.erase(evaluate_scope_stack.end() - 1);
;
    break;}
case 22:
#line 280 "parser.y"
{
  if( evaluate() )
  {
    //    FIXME("enter a call to printDebug for an object in an expression");
    get_object(yyvsp[-1])->printDebug();
  }
;
    break;}
case 24:
#line 289 "parser.y"
{
  if( evaluate() )
  {
    FIXME("assignment to something");
  }
;
    break;}
case 25:
#line 296 "parser.y"
{
  if( evaluate() )
  {
    FIXME("assignment to something");
  }
;
    break;}
case 26:
#line 303 "parser.y"
{
  if( evaluate() )
  {
    FIXME("assignment to something");
  }
;
    break;}
case 27:
#line 310 "parser.y"
{
  if( evaluate() )
  {
    FIXME("assignment (+=) to something");
  }
;
    break;}
case 28:
#line 317 "parser.y"
{
  if( evaluate() )
  {
    FIXME("assignment (-=) to something");
  }
;
    break;}
case 29:
#line 324 "parser.y"
{
  if( evaluate() )
  {
    FIXME("assignment (*=) to something");
  }
;
    break;}
case 30:
#line 331 "parser.y"
{
  if( evaluate() )
  {
    FIXME("assignment (/=) to something");
  }
;
    break;}
case 31:
#line 341 "parser.y"
{
  if( evaluate() )
  {
    fprintf(stderr,"user warning: line %d: \"%s\"\n",scanner_line_number,get_string(yyvsp[-1]).c_str());
  }
;
    break;}
case 32:
#line 348 "parser.y"
{
  if( evaluate() )
  {
    fprintf(stderr,"user error: line %d: \"%s\"\n",scanner_line_number,get_string(yyvsp[-1]).c_str());
    exit(1);
  }
;
    break;}
case 33:
#line 356 "parser.y"
{
  if( evaluate() )
  {
    fprintf(stdout,"%s\n",get_string(yyvsp[-1]).c_str());
  }
;
    break;}
case 34:
#line 366 "parser.y"
{
  if( get_bool(yyvsp[-1]) )
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
;
    break;}
case 35:
#line 384 "parser.y"
{
  // nothing here
;
    break;}
case 37:
#line 391 "parser.y"
{
  if( yyvsp[0] != NULL )
  {
    std::string base_string = yyvsp[0]->getDynamicType();
    yyval = new Tdynamic_string (base_string);
  }
  else
  {
    yyval = new Tdynamic_string("undefined");
  }
;
    break;}
case 38:
#line 403 "parser.y"
{
  std::string attr_str = "";
  if( evaluate() )
  {
    //    FIXME("get an attribute list for something in a reference");
    attr_str = "( ";
    TAttributeList attr_list;

    
    yyvsp[0]->getAttributeList(attr_list);
    for(TAttributeList::const_iterator i = attr_list.begin();
	i != attr_list.end();
	++i)
    {
      attr_str += i->first + " ";
    }
    attr_str += ")";
  }
  yyval = new Tdynamic_string(attr_str);
;
    break;}
case 40:
#line 427 "parser.y"
{ yyval = new Tdynamic_bool(get_bool(yyvsp[-2]) && get_bool(yyvsp[0])); ;
    break;}
case 42:
#line 432 "parser.y"
{ yyval = new Tdynamic_bool(get_bool(yyvsp[-2]) || get_bool(yyvsp[0])); ;
    break;}
case 44:
#line 438 "parser.y"
{
  if( is_real(yyvsp[-2]) )
  {
    yyval = new Tdynamic_bool(get_real(yyvsp[-2]) == get_real(yyvsp[0]));
  }
  else if( is_bool(yyvsp[-2]) )
  {
    yyval = new Tdynamic_bool(get_bool(yyvsp[-2]) == get_bool(yyvsp[0]));
  }
  else if( is_vector(yyvsp[-2]) )
  {
    yyval = new Tdynamic_bool(get_vector(yyvsp[-2]) == get_vector(yyvsp[0]));
  }        
;
    break;}
case 45:
#line 453 "parser.y"
{
  if( is_real(yyvsp[-2]) )
  {
    yyval = new Tdynamic_bool(get_real(yyvsp[-2]) != get_real(yyvsp[0]));
  }
  else if( is_bool(yyvsp[-2]) )
  {
    yyval = new Tdynamic_bool(get_bool(yyvsp[-2]) != get_bool(yyvsp[0]));
  }
  else if( is_vector(yyvsp[-2]) )
  {
    yyval = new Tdynamic_bool(get_vector(yyvsp[-2]) != get_vector(yyvsp[0]));
  }          
;
    break;}
case 47:
#line 471 "parser.y"
{ yyval = new Tdynamic_bool(get_real(yyvsp[-2]) >= get_real(yyvsp[0])); ;
    break;}
case 48:
#line 472 "parser.y"
{ yyval = new Tdynamic_bool(get_real(yyvsp[-2]) > get_real(yyvsp[0])); ;
    break;}
case 49:
#line 473 "parser.y"
{ yyval = new Tdynamic_bool(get_real(yyvsp[-2]) <= get_real(yyvsp[0])); ;
    break;}
case 50:
#line 474 "parser.y"
{ yyval = new Tdynamic_bool(get_real(yyvsp[-2]) < get_real(yyvsp[0])); ;
    break;}
case 52:
#line 480 "parser.y"
{
  if( is_string(yyvsp[-2]) || is_string(yyvsp[0]) )
  {
    yyval = new Tdynamic_string(get_string(yyvsp[-2]) + get_string(yyvsp[0]));
  }
  else
  {
    yyval = add(yyvsp[-2],yyvsp[0]);
    if( yyval == NULL )
    {
      fprintf(stderr,"parser: line %d: addition of %s and %s failed\n",
	      scanner_line_number, yyvsp[-2]->getDynamicType(), yyvsp[0]->getDynamicType()); 
      exit(1);
    }
  }
;
    break;}
case 53:
#line 497 "parser.y"
{
  yyval = sub(yyvsp[-2],yyvsp[0]);
  if( yyval == NULL )
  {
    fprintf(stderr,"parser: line %d: subtraction of %s and %s failed\n",
	    scanner_line_number, yyvsp[-2]->getDynamicType(), yyvsp[-1]->getDynamicType());
    exit(1);
  }
;
    break;}
case 55:
#line 511 "parser.y"
{
  yyval = mul(yyvsp[-2],yyvsp[0]);
  if( yyval == NULL )
  {
    fprintf(stderr,"parser: line %d: multiplication of %s and %s failed\n",
	    scanner_line_number, yyvsp[-2]->getDynamicType(), yyvsp[-1]->getDynamicType());
    exit(1);
  }
;
    break;}
case 56:
#line 521 "parser.y"
{
  yyval = div(yyvsp[-2],yyvsp[0]);
  if( yyval == NULL )
  {
    fprintf(stderr,"parser: line %d: addition of %s and %s failed\n",
	    scanner_line_number, yyvsp[-2]->getDynamicType(), yyvsp[-1]->getDynamicType());
    exit(1);
  }
;
    break;}
case 58:
#line 534 "parser.y"
{ yyval = new Tdynamic_bool(!get_bool(yyvsp[0])); ;
    break;}
case 59:
#line 535 "parser.y"
{ yyval = yyvsp[0]; ;
    break;}
case 60:
#line 537 "parser.y"
{
  if( is_real(yyvsp[0]) )
  {
    yyval = new Tdynamic_real(-get_real(yyvsp[0]));
  }
  else
  {
    yyval = new Tdynamic_vector(-get_vector(yyvsp[0]));
  }
;
    break;}
case 61:
#line 551 "parser.y"
{
  yyval = yyvsp[0];
  Tdotted_list* list_ptr = (Tdotted_list*)yyvsp[0].get_pointer();
  if( list_ptr->get_chain_length() == 0)
  {
    yyval = list_ptr->get_base();
  }
  
  if( yyvsp[0] == NULL )
  {
    yyval = new Tdynamic_base();
  }
;
    break;}
case 63:
#line 569 "parser.y"
{
  if( is_string(yyvsp[0]) )
  {
    yyval = new Tdotted_list(locate_reference(get_string(yyvsp[0])));
  }
  else
  {
    yyval = new Tdotted_list(yyvsp[0]);    
  }
;
    break;}
case 64:
#line 580 "parser.y"
{
  if( evaluate() )
  {
    //    FIXME("change scope and create a reference because of a dot (.)");
    TAttributeList tlist ;
    yyvsp[-2]->getAttributeList (tlist);
    std::string element_name = get_string(yyvsp[0]);
    const Tdotted_list* parent_list = (const Tdotted_list*)yyvsp[-2].get_pointer();

    //    printf("base=%s list=",parent_list->get_base()->getDynamicType());
    
    if( element_name == "parent" )
    {
      if( tlist.find(element_name) == tlist.end() )
      {
	if( parent_list->get_chain_length() <= 1)
	{
	  //	  printf("(%s) ---parent of <=1 length chain\n", (parent_list->get_chain_length() == 1)?parent_list->get_chain()[0].c_str():"");
	  yyval = new Tdotted_list(new scope_object(global_scope));
	}
	else
	{
	  FIXME("faked parent attribute");
	  /*
	  // Since the item does not have an element named parent, fake one by
	  // copying the entire list of std::strings except for the last.
	  magic_pointer<Tdotted_list> result_list = new Tdotted_list(parent_list->get_base());
	  int i = 0;
	  const std::vector<std::string>& str_list = parent_list->get_chain();
	  for(i = 0; i < int(parent_list->get_chain_length()) - 1; ++i)
	  {
	    printf("%s ",str_list[i].c_str());
	    result_list = new Tdotted_list(*result_list, str_list[i]);
	  }
	  printf("(%s) ",str_list[i].c_str());
	  printf("---faked parent\n");	  
	  $$ = result_list->clone();
	  */
	  std::string error_msg = std::string("element has no attribute named ") + element_name;
	  yyerror(error_msg.c_str());
	  exit(1);	  
	}
      }
      else
      {
	yyval = new Tdotted_list(*parent_list, element_name);
	/*
	const std::vector<std::string>& str_list = parent_list->get_chain();	  
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
	string error_msg = std::string("element has no attribute named ") + element_name;
	yyerror(error_msg.c_str());
	exit(1);
      }
      yyval = new Tdotted_list(*parent_list, element_name);
      /*
      const std::vector<std::string>& str_list = parent_list->get_chain();	  
      for(unsigned i = 0; i < str_list.size(); ++i)
      {
	printf("%s ",str_list[i].c_str());
      }
      printf("+%s ",element_name.c_str());
      printf("---attribute parent\n");
      */
    }
  }
;
    break;}
case 67:
#line 664 "parser.y"
{
  yyval = new scope_object(global_scope);
;
    break;}
case 69:
#line 671 "parser.y"
{
  if( evaluate() )
  {
    FIXME("recovering a paramater (how?)");
  }
;
    break;}
case 70:
#line 678 "parser.y"
{
  const char* env_text = getenv(get_string(yyvsp[0]).c_str());
  if( env_text != NULL )
  {
    // fixme!!! I want to be able to evaluate the text... using it as input to
    // the scanner/parser.  What does this require?
    FIXME(string(string("insert code to evaluate the text (") + get_string(yyvsp[0]) + ")").c_str());
    yyval = new Tdynamic_string(env_text);
  }
  else
  {
    yyerror(string(get_string(yyvsp[0]) + " is not an environment variable").c_str());
    yyval = new Tdynamic_string("");
  }
;
    break;}
case 71:
#line 694 "parser.y"
{
  FIXME("check to see if an element is defined in any of the current scopes (in the symtabs");
  yyval = new Tdynamic_bool(false);
;
    break;}
case 74:
#line 700 "parser.y"
{ yyval = yyvsp[-1]; ;
    break;}
case 75:
#line 702 "parser.y"
{
  //  $$ = new Tdynamic_string("this");
  yyval = current_object;
;
    break;}
case 76:
#line 710 "parser.y"
{
  //  FIXME(string(string("perform a lookup of \"") + get_string($1) + "\"").c_str());
  yyval = yyvsp[0];
;
    break;}
case 77:
#line 715 "parser.y"
{
  yyval = new Tdynamic_string("parent");
;
    break;}
case 78:
#line 722 "parser.y"
{ yyval = new Tdynamic_vector(TVector(get_real(yyvsp[-5]),
										    get_real(yyvsp[-3]),
										    get_real(yyvsp[-1]))); ;
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
#line 727 "parser.y"


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

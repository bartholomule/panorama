
/*  A Bison parser, made from parser.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse rt_conv_parse
#define yylex rt_conv_lex
#define yyerror rt_conv_error
#define yylval rt_conv_lval
#define yychar rt_conv_char
#define yydebug rt_conv_debug
#define yynerrs rt_conv_nerrs
#define	T_BOOL	257
#define	T_REAL	258
#define	T_IDENTIFIER	259
#define	T_QUOTED_STRING	260
#define	T_VERBATIM	261
#define	T_AGGREGATE	262
#define	T_ATM_OBJECT	263
#define	T_BLUE	264
#define	T_BOX	265
#define	T_BSDF	266
#define	T_CAMERA	267
#define	T_CIRCLE	268
#define	T_CLASS	269
#define	T_COLOR	270
#define	T_CONE	271
#define	T_CYLINDER	272
#define	T_DEFINE	273
#define	T_DIFFERENCE	274
#define	T_EXTENDS	275
#define	T_FILTER	276
#define	T_GREEN	277
#define	T_IMAGE_FILTER	278
#define	T_INTERSECTION	279
#define	T_LIGHT	280
#define	T_MATERIAL	281
#define	T_MESH	282
#define	T_OBJECT	283
#define	T_OBJECT_FILTER	284
#define	T_OUTPUT	285
#define	T_PATTERN	286
#define	T_PERTURBATION	287
#define	T_PHONG_TRIANGLE	288
#define	T_PLANE	289
#define	T_RECTANGLE	290
#define	T_RED	291
#define	T_RENDERER	292
#define	T_ROTATE	293
#define	T_SCALE	294
#define	T_SCENE	295
#define	T_SPHERE	296
#define	T_TORUS	297
#define	T_TRANSLATE	298
#define	T_TRIANGLE	299
#define	T_TYPE	300
#define	T_UNION	301
#define	T_VECTOR	302
#define	T_VERTEX	303
#define	T_X	304
#define	T_Y	305
#define	T_Z	306
#define	UNARY_MINUS	307

#line 20 "parser.y"

#include <string>
using std::string;
//#define YYSTYPE string;
 
#define YYDEBUG 1
#define YYERROR_VERBOSE 

static const string newline = "\n";

 unsigned line_number;
 string file_name;
 
 static string x;
 static string y;
 static string z;
 static string image_output_type;

 static string extract_class(const string& cls, const string& def);

#include "parser_defs.h"

 
#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		249
#define	YYFLAG		-32768
#define	YYNTBASE	66

#define YYTRANSLATE(x) ((unsigned)(x) <= 307 ? yytranslate[x] : 108)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    60,
    61,    55,    53,    63,    54,     2,    56,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    65,     2,    62,
     2,    64,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    58,     2,    59,     2,     2,     2,     2,     2,
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
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    57
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     3,     5,     6,     9,    13,    17,    20,    23,
    25,    29,    33,    37,    41,    43,    50,    55,    57,    59,
    63,    67,    71,    75,    79,    82,    86,    95,   103,   109,
   110,   112,   113,   117,   121,   122,   125,   127,   129,   131,
   133,   135,   136,   139,   142,   145,   148,   151,   154,   157,
   160,   163,   166,   169,   172,   175,   178,   181,   184,   187,
   190,   191,   194,   195,   198,   201,   204,   209,   212,   215,
   220,   222,   225,   227,   230,   233,   235,   238,   241,   244,
   246,   249,   251,   255,   256,   259,   265,   267,   272,   278,
   280,   285,   287,   289,   295,   297,   300,   303,   306,   309,
   315,   317,   322,   324,   327,   330,   333,   336,   338,   340,
   342,   344,   346,   348,   350,   352,   354,   356,   358,   360,
   362,   364,   366,   368,   370,   372,   374,   376,   378,   380,
   382,   384,   386,   388,   390,   392,   394,   396,   398,   400,
   402,   404,   406,   408,   410,   412,   414,   416,   418,   420,
   422,   424,   426,   428,   430,   432
};

static const short yyrhs[] = {    68,
     0,     0,     7,     0,     0,    68,    67,     0,    68,    69,
    67,     0,    68,    70,    67,     0,    41,    93,     0,     9,
    72,     0,    73,     0,    19,    16,    97,     0,    19,    48,
   100,     0,    19,    29,    94,     0,    19,    41,    92,     0,
    71,     0,   105,    78,    79,    58,    83,    59,     0,    79,
    58,    80,    59,     0,    95,     0,     4,     0,     5,    60,
    61,     0,    74,    53,    74,     0,    74,    54,    74,     0,
    74,    55,    74,     0,    74,    56,    74,     0,    54,    74,
     0,    60,    74,    61,     0,    58,    37,    74,    23,    74,
    10,    74,    59,     0,    62,    74,    63,    74,    63,    74,
    64,     0,    62,    74,    63,    74,    64,     0,     0,     5,
     0,     0,    65,    21,     5,     0,    65,    15,     5,     0,
     0,    80,    81,     0,    87,     0,    88,     0,    89,     0,
    96,     0,    82,     0,     0,     0,    82,     0,     5,   104,
     0,     5,    76,     0,     5,    77,     0,     5,    74,     0,
     5,     3,     0,     5,     6,     0,     5,    75,     0,     5,
    78,     0,    16,    78,     0,    16,    74,     0,    16,    75,
     0,    16,    72,     0,    48,   101,     0,    13,    72,     0,
    38,    72,     0,    12,    72,     0,   106,    72,     0,     0,
    83,    87,     0,     0,    84,    88,     0,    44,    76,     0,
    39,    76,     0,    39,    74,    63,    76,     0,    44,   101,
     0,    39,   101,     0,    39,    74,    63,   101,     0,    82,
     0,    40,    76,     0,    85,     0,    27,    72,     0,    22,
    72,     0,    86,     0,    26,    72,     0,    22,    72,     0,
    31,    90,     0,    82,     0,    46,     6,     0,    82,     0,
    58,    91,    59,     0,     0,    91,    89,     0,    78,    79,
    58,    84,    59,     0,    78,     0,    79,    58,    84,    59,
     0,    78,    79,    58,    83,    59,     0,    78,     0,    79,
    58,    83,    59,     0,    73,     0,    87,     0,    78,    79,
    58,    98,    59,     0,    99,     0,    98,    99,     0,    37,
    74,     0,    23,    74,     0,    10,    74,     0,    78,    79,
    58,   102,    59,     0,    78,     0,    79,    58,   102,    59,
     0,   103,     0,   102,   103,     0,    50,    74,     0,    51,
    74,     0,    52,    74,     0,     5,     0,   107,     0,     8,
     0,     9,     0,    11,     0,    13,     0,    14,     0,    17,
     0,    18,     0,    20,     0,    47,     0,    25,     0,    24,
     0,    30,     0,    26,     0,    28,     0,    29,     0,    12,
     0,    27,     0,    32,     0,    33,     0,    34,     0,    35,
     0,    36,     0,    38,     0,    41,     0,    42,     0,    43,
     0,    45,     0,    31,     0,    16,     0,    40,     0,    49,
     0,    22,     0,    46,     0,   105,     0,   106,     0,    15,
     0,    19,     0,    21,     0,    23,     0,    37,     0,    10,
     0,    39,     0,    44,     0,    48,     0,    50,     0,    51,
     0,    52,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   107,   114,   120,   127,   132,   136,   140,   146,   151,   155,
   161,   166,   170,   174,   178,   184,   191,   199,   206,   211,
   215,   219,   223,   227,   231,   235,   240,   247,   253,   260,
   264,   270,   275,   279,   286,   291,   297,   299,   300,   301,
   302,   306,   311,   317,   322,   326,   330,   334,   338,   342,
   346,   350,   354,   358,   362,   366,   370,   374,   378,   382,
   385,   390,   396,   401,   407,   412,   416,   420,   424,   428,
   432,   438,   443,   449,   454,   458,   465,   470,   474,   478,
   484,   490,   497,   504,   509,   515,   522,   527,   533,   540,
   545,   551,   556,   562,   569,   574,   580,   585,   589,   595,
   602,   607,   616,   621,   627,   633,   638,   645,   646,   650,
   652,   653,   654,   655,   656,   657,   658,   659,   660,   661,
   662,   663,   664,   665,   666,   667,   668,   669,   670,   671,
   672,   673,   674,   675,   676,   677,   680,   682,   683,   684,
   685,   686,   689,   691,   692,   693,   694,   695,   696,   697,
   698,   699,   700,   701,   702,   703
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","T_BOOL",
"T_REAL","T_IDENTIFIER","T_QUOTED_STRING","T_VERBATIM","T_AGGREGATE","T_ATM_OBJECT",
"T_BLUE","T_BOX","T_BSDF","T_CAMERA","T_CIRCLE","T_CLASS","T_COLOR","T_CONE",
"T_CYLINDER","T_DEFINE","T_DIFFERENCE","T_EXTENDS","T_FILTER","T_GREEN","T_IMAGE_FILTER",
"T_INTERSECTION","T_LIGHT","T_MATERIAL","T_MESH","T_OBJECT","T_OBJECT_FILTER",
"T_OUTPUT","T_PATTERN","T_PERTURBATION","T_PHONG_TRIANGLE","T_PLANE","T_RECTANGLE",
"T_RED","T_RENDERER","T_ROTATE","T_SCALE","T_SCENE","T_SPHERE","T_TORUS","T_TRANSLATE",
"T_TRIANGLE","T_TYPE","T_UNION","T_VECTOR","T_VERTEX","T_X","T_Y","T_Z","'+'",
"'-'","'*'","'/'","UNARY_MINUS","'{'","'}'","'('","')'","'<'","','","'>'","':'",
"scene_file","optional_comments","everything","instance","definition","type_def",
"type_instance","object","real_expr","color","vector3","vector2","name","class",
"any_params","any_param","param","object_params","scene_params","entity_param",
"volume_param","object_param","scene_param","image_io_param","image_io_instance",
"image_io_params","scene_def","scene_instance","object_def","object_instance",
"aggregate_param","color_def","color_params","color_param","vector_def","vector_instance",
"vector_params","vector_param","potential_string","reserved_types","reserved_fields",
"reserved_words", NULL
};
#endif

static const short yyr1[] = {     0,
    66,    67,    67,    68,    68,    68,    68,    69,    69,    69,
    70,    70,    70,    70,    70,    71,    72,    73,    74,    74,
    74,    74,    74,    74,    74,    74,    75,    76,    77,    78,
    78,    79,    79,    79,    80,    80,    81,    81,    81,    81,
    81,    -1,    -1,    82,    82,    82,    82,    82,    82,    82,
    82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
    83,    83,    84,    84,    85,    85,    85,    85,    85,    85,
    85,    86,    86,    87,    87,    87,    88,    88,    88,    88,
    89,    89,    90,    91,    91,    92,    93,    93,    94,    95,
    95,    96,    96,    97,    98,    98,    99,    99,    99,   100,
   101,   101,   102,   102,   103,   103,   103,   104,   104,   105,
   105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
   105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
   105,   105,   105,   105,   105,   105,   106,   106,   106,   106,
   106,   106,   107,   107,   107,   107,   107,   107,   107,   107,
   107,   107,   107,   107,   107,   107
};

static const short yyr2[] = {     0,
     1,     0,     1,     0,     2,     3,     3,     2,     2,     1,
     3,     3,     3,     3,     1,     6,     4,     1,     1,     3,
     3,     3,     3,     3,     2,     3,     8,     7,     5,     0,
     1,     0,     3,     3,     0,     2,     1,     1,     1,     1,
     1,     0,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     0,     2,     0,     2,     2,     2,     4,     2,     2,     4,
     1,     2,     1,     2,     2,     1,     2,     2,     2,     1,
     2,     1,     3,     0,     2,     5,     1,     4,     5,     1,
     4,     1,     1,     5,     1,     2,     2,     2,     2,     5,
     1,     4,     1,     2,     2,     2,     2,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1
};

static const short yydefact[] = {     4,
     1,    31,     3,   110,    32,   112,   125,   113,   114,   115,
   116,     0,   117,   120,   119,   122,   126,   123,   124,   121,
   127,   128,   129,   130,   131,   132,    30,   134,   135,   136,
   118,     0,     5,     2,     2,    15,    10,    90,     0,    18,
    30,     9,     0,    30,    30,    30,    30,    87,     0,     8,
     0,     0,     6,     7,    61,    32,    35,    32,    11,    32,
    13,    32,    14,    32,    12,    63,    34,    33,     0,     0,
    30,     0,     0,     0,     0,     0,    30,    32,    32,    30,
    32,    32,   137,    32,    30,   139,    30,   142,    30,   140,
    91,    71,    73,    76,    62,    32,    61,    30,    32,    32,
   137,   142,    17,    92,    36,    41,    37,    38,    39,    40,
     0,    61,    63,     0,    32,   139,    88,    80,    64,    48,
    19,    31,    49,   111,   150,   145,   138,   146,   147,   141,
   148,   149,   151,   133,   152,   153,   154,   155,   156,     0,
     0,     0,     0,    47,    50,    45,    46,    51,    44,   143,
   144,   109,    59,    57,    31,    55,    53,    54,    52,    75,
    74,    58,     0,     0,    66,   101,     0,    69,    72,    65,
    68,    56,    60,     0,    75,    77,    84,    79,    81,     0,
     0,     0,     0,    95,     0,     0,     0,     0,     0,     0,
   103,    78,     0,     0,    25,     0,     0,     0,     0,     0,
     0,     0,     0,    30,     0,    16,     0,    99,    98,    97,
    94,    96,    89,    86,   105,   106,   107,   100,   104,    20,
     0,    26,     0,    21,    22,    23,    24,     0,    67,    70,
     0,    83,    82,    85,     0,     0,     0,   102,     0,     0,
    29,     0,     0,     0,    28,    27,     0,     0,     0
};

static const short yydefgoto[] = {   247,
    33,     1,    34,    35,    36,    42,    37,   144,   145,   146,
   147,   166,    43,    71,   105,    92,    69,    76,    93,    94,
    95,   119,   109,   178,   207,    63,    50,    61,    40,   110,
    59,   183,   184,    65,   168,   190,   191,   149,   150,    96,
   152
};

static const short yypact[] = {-32768,
   163,-32768,-32768,-32768,    10,-32768,-32768,-32768,-32768,-32768,
-32768,    -2,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,    11,-32768,-32768,-32768,
-32768,    22,-32768,    21,    21,-32768,-32768,-32768,   -25,-32768,
    30,-32768,   -13,    30,    30,    30,    30,-32768,    -7,-32768,
    47,    48,-32768,-32768,-32768,    12,-32768,    12,-32768,    12,
-32768,    12,-32768,    12,-32768,-32768,-32768,-32768,   313,     0,
   204,    33,    49,    50,    61,   400,   262,    12,    12,    13,
    12,    12,-32768,    12,    27,     6,     7,-32768,    11,-32768,
-32768,-32768,-32768,-32768,-32768,    12,-32768,   262,    12,    12,
    67,    73,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
    19,-32768,-32768,    43,    12,-32768,-32768,-32768,-32768,-32768,
-32768,    45,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    36,
    69,    36,    36,   205,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,    45,-32768,   205,-32768,-32768,-32768,
-32768,-32768,    36,   100,-32768,-32768,    68,-32768,-32768,-32768,
-32768,-32768,-32768,   342,-32768,-32768,-32768,-32768,-32768,    36,
    36,    36,     1,-32768,   371,   429,    36,    36,    36,   182,
-32768,-32768,    56,    45,-32768,    36,   105,   183,    36,    36,
    36,    36,   201,     7,    43,-32768,   449,   205,   205,   205,
-32768,-32768,-32768,-32768,   205,   205,   205,-32768,-32768,-32768,
    59,-32768,    36,   -36,   -36,-32768,-32768,    36,-32768,-32768,
   286,-32768,-32768,-32768,    36,   159,   278,-32768,    44,    36,
-32768,    36,    85,   312,-32768,-32768,   128,   129,-32768
};

static const short yypgoto[] = {-32768,
   -12,-32768,-32768,-32768,-32768,    52,    64,   -78,    62,   -77,
-32768,     3,    -1,-32768,-32768,   -70,   -76,    31,-32768,-32768,
    72,    75,   -60,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   -18,-32768,   -84,   -32,  -165,-32768,   168,   -64,
-32768
};


#define	YYLAST		508


static const short yytable[] = {    39,
   106,   157,   171,    38,   172,   118,   164,   165,   169,   170,
   180,     2,   151,    44,  -111,     2,   121,   155,   201,   202,
   174,    53,    54,   181,   219,    49,    45,     3,   180,    48,
   121,   155,    55,   151,     2,   185,    51,   182,    46,   121,
   194,   181,    52,    56,    57,    47,    58,    60,    62,    64,
    66,    67,    68,   242,    70,   182,    72,    97,    73,   211,
    74,   195,    75,   197,   198,   219,   140,   163,   163,    39,
   141,    32,   142,    38,    32,    32,    32,    32,   179,   148,
   140,   235,   159,   167,   203,   167,   142,   167,   163,   140,
   111,    32,   187,   188,   189,   142,   199,   200,   201,   202,
   148,   208,   209,   210,   193,   196,   112,   113,   215,   216,
   217,   199,   200,   201,   202,   118,   220,   221,   114,   230,
   224,   225,   226,   227,   177,   205,   229,   248,   249,   153,
   154,   156,   160,   161,   104,   162,   233,   199,   200,   201,
   202,   158,   107,   186,   236,   108,   234,   173,   245,   237,
   175,   176,   199,   200,   201,   202,   239,   199,   200,   201,
   202,   243,   204,   244,   212,   222,   192,     2,    41,     3,
     4,     5,   231,     6,     7,     8,     9,     0,     0,    10,
    11,    12,    13,     0,     0,     0,    14,    15,    16,    17,
    18,    19,    20,     0,    21,    22,    23,    24,    25,     0,
    26,     0,   167,    27,    28,    29,     0,    30,    98,    31,
     0,   199,   200,   201,   202,    78,    79,     0,     0,    80,
    -2,   240,   241,     0,     0,    99,     0,    32,     0,   100,
    82,   187,   188,   189,   101,   199,   200,   201,   202,     0,
   218,    84,    85,    86,     0,   223,     0,    87,     0,   102,
     0,    89,    90,   199,   200,   201,   202,   199,   200,   201,
   202,     0,   103,   228,   120,   121,   122,   123,    32,     4,
   124,   125,     6,     7,     8,     9,   126,   127,    10,    11,
   128,    13,   129,   130,   131,    14,    15,    16,    17,    18,
    19,    20,    83,    21,    22,    23,    24,    25,   132,    26,
   133,   116,   134,    28,    29,   135,    30,    88,    31,   136,
    90,   137,   138,   139,     0,   140,     0,    77,     0,   141,
     0,   142,     0,   143,    78,    79,     0,     0,    80,     0,
   199,   200,   201,   202,    81,   187,   188,   189,     0,    82,
   240,     0,     0,    83,   238,     0,    77,     0,     0,     0,
    84,    85,    86,    78,    79,     0,    87,    80,    88,     0,
    89,    90,     0,    81,   199,   200,   201,   202,    82,     0,
   246,    91,    83,     0,     0,    77,     0,     0,     0,    84,
    85,    86,    78,    79,     0,    87,    80,    88,     0,    89,
    90,     0,    81,     0,     0,     0,     0,    82,     0,     0,
   206,    83,     0,     0,    77,     0,     0,     0,    84,    85,
    86,    78,    79,     0,    87,    80,    88,     0,    89,    90,
     0,   115,     0,     0,     0,   100,     0,     0,     0,   213,
   101,     0,     0,    77,     0,     0,     0,    84,     0,   116,
    78,    79,     0,     0,    80,    88,     0,    89,    90,     0,
   115,     0,     0,    77,   100,     0,     0,     0,   117,   101,
    78,    79,     0,     0,    80,     0,    84,     0,   116,     0,
   130,     0,     0,     0,    88,     0,    89,    90,     0,    83,
     0,     0,     0,     0,     0,     0,    84,   214,   116,     0,
     0,     0,     0,     0,   102,     0,    89,    90,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   232
};

static const short yycheck[] = {     1,
    71,    80,    87,     1,    89,    76,    85,    85,    86,    87,
    10,     5,    77,    16,     5,     5,     4,     5,    55,    56,
    97,    34,    35,    23,   190,    27,    29,     7,    10,    27,
     4,     5,    58,    98,     5,   112,    15,    37,    41,     4,
     5,    23,    21,    41,    58,    48,    44,    45,    46,    47,
    58,     5,     5,    10,    56,    37,    58,    58,    60,    59,
    62,   140,    64,   142,   143,   231,    54,    62,    62,    71,
    58,    65,    60,    71,    65,    65,    65,    65,     6,    77,
    54,    23,    80,    85,   163,    87,    60,    89,    62,    54,
    58,    65,    50,    51,    52,    60,    53,    54,    55,    56,
    98,   180,   181,   182,    60,    37,    58,    58,   187,   188,
   189,    53,    54,    55,    56,   186,    61,   196,    58,   204,
   199,   200,   201,   202,    58,    58,   204,     0,     0,    78,
    79,    80,    81,    82,    71,    84,   207,    53,    54,    55,
    56,    80,    71,   113,   223,    71,   207,    96,    64,   228,
    99,   100,    53,    54,    55,    56,   235,    53,    54,    55,
    56,   240,    63,   242,   183,    61,   115,     5,     1,     7,
     8,     9,   205,    11,    12,    13,    14,    -1,    -1,    17,
    18,    19,    20,    -1,    -1,    -1,    24,    25,    26,    27,
    28,    29,    30,    -1,    32,    33,    34,    35,    36,    -1,
    38,    -1,   204,    41,    42,    43,    -1,    45,     5,    47,
    -1,    53,    54,    55,    56,    12,    13,    -1,    -1,    16,
    58,    63,    64,    -1,    -1,    22,    -1,    65,    -1,    26,
    27,    50,    51,    52,    31,    53,    54,    55,    56,    -1,
    59,    38,    39,    40,    -1,    63,    -1,    44,    -1,    46,
    -1,    48,    49,    53,    54,    55,    56,    53,    54,    55,
    56,    -1,    59,    63,     3,     4,     5,     6,    65,     8,
     9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
    19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
    29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
    39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
    49,    50,    51,    52,    -1,    54,    -1,     5,    -1,    58,
    -1,    60,    -1,    62,    12,    13,    -1,    -1,    16,    -1,
    53,    54,    55,    56,    22,    50,    51,    52,    -1,    27,
    63,    -1,    -1,    31,    59,    -1,     5,    -1,    -1,    -1,
    38,    39,    40,    12,    13,    -1,    44,    16,    46,    -1,
    48,    49,    -1,    22,    53,    54,    55,    56,    27,    -1,
    59,    59,    31,    -1,    -1,     5,    -1,    -1,    -1,    38,
    39,    40,    12,    13,    -1,    44,    16,    46,    -1,    48,
    49,    -1,    22,    -1,    -1,    -1,    -1,    27,    -1,    -1,
    59,    31,    -1,    -1,     5,    -1,    -1,    -1,    38,    39,
    40,    12,    13,    -1,    44,    16,    46,    -1,    48,    49,
    -1,    22,    -1,    -1,    -1,    26,    -1,    -1,    -1,    59,
    31,    -1,    -1,     5,    -1,    -1,    -1,    38,    -1,    40,
    12,    13,    -1,    -1,    16,    46,    -1,    48,    49,    -1,
    22,    -1,    -1,     5,    26,    -1,    -1,    -1,    59,    31,
    12,    13,    -1,    -1,    16,    -1,    38,    -1,    40,    -1,
    22,    -1,    -1,    -1,    46,    -1,    48,    49,    -1,    31,
    -1,    -1,    -1,    -1,    -1,    -1,    38,    59,    40,    -1,
    -1,    -1,    -1,    -1,    46,    -1,    48,    49,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59
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
#line 108 "parser.y"
{
  cout << "// This is a converted RT scene file.  Check for correctness." << endl;
  cout << "#include \"shapes.inc\"" << endl;
  cout << yyvsp[0] << endl;
;
    break;}
case 2:
#line 116 "parser.y"
{
  yyval = "";
  cout << "parser:optional_comments (empty)" << endl;
;
    break;}
case 3:
#line 121 "parser.y"
{
  cout << "parser:optional_comments (verbatim)" << endl;
  yyval = yyvsp[0];
;
    break;}
case 4:
#line 129 "parser.y"
{
  yyval = "";
;
    break;}
case 5:
#line 133 "parser.y"
{
  yyval = yyvsp[-1] + yyvsp[0];
;
    break;}
case 6:
#line 137 "parser.y"
{
  yyval = yyvsp[-2] + yyvsp[-1] + yyvsp[0];
;
    break;}
case 7:
#line 141 "parser.y"
{
  yyval = yyvsp[-2] + yyvsp[-1] + yyvsp[0];
;
    break;}
case 8:
#line 148 "parser.y"
{
  yyval = string("scene") + newline + yyvsp[0] + newline;
;
    break;}
case 9:
#line 152 "parser.y"
{
  yyval = yyvsp[-1] + newline + yyvsp[0] + newline;
;
    break;}
case 10:
#line 156 "parser.y"
{
  yyval = yyvsp[0];  
;
    break;}
case 11:
#line 163 "parser.y"
{
  yyval = yyvsp[0] + newline;
;
    break;}
case 12:
#line 167 "parser.y"
{
  yyval = yyvsp[0] + newline;
;
    break;}
case 13:
#line 171 "parser.y"
{
  yyval = yyvsp[0] + newline;
;
    break;}
case 14:
#line 175 "parser.y"
{
  yyval = yyvsp[0] + newline;
;
    break;}
case 15:
#line 179 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 16:
#line 186 "parser.y"
{
  yyval = string("define ") + yyvsp[-4] + " " + extract_class(yyvsp[-3],yyvsp[-5]) + " { " + newline + yyvsp[-2] + newline + " };";  
;
    break;}
case 17:
#line 193 "parser.y"
{
  yyval = string("define ") + yyvsp[-2] + " " + extract_class(yyvsp[-3],"/* unknown instance */") + " { " + newline + yyvsp[-1] + newline + " }";  
;
    break;}
case 18:
#line 201 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 19:
#line 208 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 20:
#line 212 "parser.y"
{
  yyval = yyvsp[-2] + "()";
;
    break;}
case 21:
#line 216 "parser.y"
{
  yyval = yyvsp[-2] + "+" + yyvsp[0];
;
    break;}
case 22:
#line 220 "parser.y"
{
  yyval = yyvsp[-2] + "-" + yyvsp[0];
;
    break;}
case 23:
#line 224 "parser.y"
{
  yyval = yyvsp[-2] + "*" + yyvsp[0];
;
    break;}
case 24:
#line 228 "parser.y"
{
  yyval = yyvsp[-2] + "/" + yyvsp[0];
;
    break;}
case 25:
#line 232 "parser.y"
{
  yyval = "-" + yyvsp[0];
;
    break;}
case 26:
#line 236 "parser.y"
{
  yyval = string("(") + yyvsp[-1] + ")";
;
    break;}
case 27:
#line 242 "parser.y"
{
  yyval = string("{ red ") + yyvsp[-5] + " green " + yyvsp[-3] + " blue " + yyvsp[-1] + " }";
;
    break;}
case 28:
#line 249 "parser.y"
{
  yyval = string("< ") + yyvsp[-5] + ", " + yyvsp[-3] + ", " + yyvsp[-1] + " >";   
;
    break;}
case 29:
#line 255 "parser.y"
{
  yyval = string("< ") + yyvsp[-3] + ", " + yyvsp[-1] + " >";   
;
    break;}
case 30:
#line 261 "parser.y"
{
  yyval = "";
;
    break;}
case 31:
#line 265 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 32:
#line 272 "parser.y"
{
  yyval = "";
;
    break;}
case 33:
#line 276 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 34:
#line 280 "parser.y"
{
  yyval = "class " + yyvsp[0];
;
    break;}
case 35:
#line 288 "parser.y"
{
  yyval = "";
;
    break;}
case 36:
#line 292 "parser.y"
{
  yyval = yyvsp[-1] + yyvsp[0] + newline;
;
    break;}
case 37:
#line 298 "parser.y"
{ yyval = yyvsp[0]; ;
    break;}
case 38:
#line 299 "parser.y"
{ yyval = yyvsp[0]; ;
    break;}
case 39:
#line 300 "parser.y"
{ yyval = yyvsp[0]; ;
    break;}
case 40:
#line 301 "parser.y"
{ yyval = yyvsp[0]; ;
    break;}
case 41:
#line 302 "parser.y"
{ yyval = yyvsp[0]; ;
    break;}
case 42:
#line 308 "parser.y"
{
  yyval = "";
;
    break;}
case 43:
#line 312 "parser.y"
{
  yyval = yyvsp[-1] + yyvsp[0] + ";" + newline;
;
    break;}
case 44:
#line 319 "parser.y"
{
  yyval = yyvsp[-1] + " = " + yyvsp[0];
;
    break;}
case 45:
#line 323 "parser.y"
{
  yyval = yyvsp[-1] + " = " + yyvsp[0];
;
    break;}
case 46:
#line 327 "parser.y"
{
  yyval = yyvsp[-1] + " = " + yyvsp[0];			    
;
    break;}
case 47:
#line 331 "parser.y"
{
  yyval = yyvsp[-1] + " = " + yyvsp[0];			    
;
    break;}
case 48:
#line 335 "parser.y"
{
  yyval = yyvsp[-1] + " = " + yyvsp[0];			    
;
    break;}
case 49:
#line 339 "parser.y"
{
  yyval = yyvsp[-1] + " = " + yyvsp[0];			    
;
    break;}
case 50:
#line 343 "parser.y"
{
  yyval = yyvsp[-1] + " = " + yyvsp[0];			    
;
    break;}
case 51:
#line 347 "parser.y"
{
  yyval = yyvsp[-1] + " = " + yyvsp[0];			    
;
    break;}
case 52:
#line 351 "parser.y"
{
  yyval = "color = " + yyvsp[0];			    
;
    break;}
case 53:
#line 355 "parser.y"
{
  yyval = "color = " + yyvsp[0];			    
;
    break;}
case 54:
#line 359 "parser.y"
{
  yyval = "color = " + yyvsp[0];			    
;
    break;}
case 55:
#line 363 "parser.y"
{
  yyval = "color = " + yyvsp[0];			    
;
    break;}
case 56:
#line 367 "parser.y"
{
  yyval = "vector = " + yyvsp[0];			    
;
    break;}
case 57:
#line 371 "parser.y"
{
  yyval = "camera = " + yyvsp[0];			    
;
    break;}
case 58:
#line 375 "parser.y"
{
  yyval = "renderer = " + yyvsp[0];			    
;
    break;}
case 59:
#line 379 "parser.y"
{
  yyval = "bsdf = " + yyvsp[0];			    
;
    break;}
case 60:
#line 382 "parser.y"
{ yyval = yyvsp[-1] + " = " + yyvsp[0] ;
    break;}
case 61:
#line 387 "parser.y"
{
  yyval = "";
;
    break;}
case 62:
#line 391 "parser.y"
{
  yyval = yyvsp[-1] + yyvsp[0] + newline;
;
    break;}
case 63:
#line 398 "parser.y"
{
  yyval = "";
;
    break;}
case 64:
#line 402 "parser.y"
{
  yyval = yyvsp[-1] + yyvsp[0] + newline;
;
    break;}
case 65:
#line 409 "parser.y"
{
  yyval = "translate( " + yyvsp[0] + ");";
;
    break;}
case 66:
#line 413 "parser.y"
{
  yyval = "rotate( " + yyvsp[0] + ");";
;
    break;}
case 67:
#line 417 "parser.y"
{
  yyval = "quaternion_rotate(" + yyvsp[-2] + "," + yyvsp[0] + ");";
;
    break;}
case 68:
#line 421 "parser.y"
{
  yyval = "translate( " + yyvsp[0] + ");";
;
    break;}
case 69:
#line 425 "parser.y"
{
  yyval = "rotate( " + yyvsp[0] + ");";
;
    break;}
case 70:
#line 429 "parser.y"
{
  yyval = "quaternion_rotate(" + yyvsp[-2] + "," + yyvsp[0] + ");";
;
    break;}
case 71:
#line 433 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 72:
#line 440 "parser.y"
{
  yyval = "scale( " + yyvsp[0] + ");";
;
    break;}
case 73:
#line 444 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 74:
#line 451 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 75:
#line 455 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 76:
#line 459 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 77:
#line 467 "parser.y"
{
  yyval = "light = " + yyvsp[0] + ";";
;
    break;}
case 78:
#line 471 "parser.y"
{
  yyval = "filter = " + yyvsp[0] + ";";
;
    break;}
case 79:
#line 475 "parser.y"
{
  yyval = "output = " + yyvsp[0] + ";";
;
    break;}
case 80:
#line 479 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 81:
#line 486 "parser.y"
{
  image_output_type = yyvsp[0].substr(1,yyvsp[0].length() - 2);
  yyval = "";
;
    break;}
case 82:
#line 491 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 83:
#line 499 "parser.y"
{
  yyval = "class " + image_output_type + newline + "{ " + newline + yyvsp[-1] + newline + "}";
;
    break;}
case 84:
#line 506 "parser.y"
{
  image_output_type = "tga";
;
    break;}
case 85:
#line 510 "parser.y"
{
  yyval = yyvsp[-1] + yyvsp[0] + newline;
;
    break;}
case 86:
#line 517 "parser.y"
{
  yyval = string("define ") + yyvsp[-4] + " " + extract_class(yyvsp[-3], "class Scene") + " { " + newline + yyvsp[-1] + newline + " };";
;
    break;}
case 87:
#line 524 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 88:
#line 528 "parser.y"
{
  yyval = extract_class(yyvsp[-3], "class Scene") + " { " + newline + yyvsp[-1] + newline + " }";
;
    break;}
case 89:
#line 535 "parser.y"
{
  yyval = string("define ") + yyvsp[-4] + " " + extract_class(yyvsp[-3], "/* unknown class */") + " { " + newline + yyvsp[-1] + newline + " };";  
;
    break;}
case 90:
#line 542 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 91:
#line 546 "parser.y"
{
  yyval = extract_class(yyvsp[-3], "/* unknown class */") + " { " + newline + yyvsp[-1] + newline + " }";  
;
    break;}
case 92:
#line 553 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 93:
#line 557 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 94:
#line 564 "parser.y"
{
  yyval = string("define ") + yyvsp[-4] + "{ " + yyvsp[-1] + " };";
;
    break;}
case 95:
#line 571 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 96:
#line 575 "parser.y"
{
  yyval = yyvsp[-1] + yyvsp[0] + " ";
;
    break;}
case 97:
#line 582 "parser.y"
{
  yyval = "red " + yyvsp[0];
;
    break;}
case 98:
#line 586 "parser.y"
{
  yyval = "green " + yyvsp[0];
;
    break;}
case 99:
#line 590 "parser.y"
{
  yyval = "blue " + yyvsp[0];
;
    break;}
case 100:
#line 597 "parser.y"
{
  yyval = string("define ") + yyvsp[-4] + "{ " + yyvsp[-1] + " };";
;
    break;}
case 101:
#line 604 "parser.y"
{
  yyval = yyvsp[0];
;
    break;}
case 102:
#line 608 "parser.y"
{
  yyval = "< " + x + ", " + y + ", " + z + " >";
  x = "";
  y = "";
  z = "";
;
    break;}
case 103:
#line 618 "parser.y"
{
  yyval = "vector_param (not to be used)";
;
    break;}
case 104:
#line 622 "parser.y"
{
  yyval = "vector_param (not to be used)";
;
    break;}
case 105:
#line 629 "parser.y"
{
  x = yyvsp[0];
  yyval = "";
;
    break;}
case 106:
#line 634 "parser.y"
{
  y = yyvsp[0];
  yyval = "";
;
    break;}
case 107:
#line 639 "parser.y"
{
  z = yyvsp[0];
  yyval = "";
;
    break;}
case 110:
#line 651 "parser.y"
{ yyval = "class Aggregate"; ;
    break;}
case 111:
#line 652 "parser.y"
{ yyval = "class AtmConst"; ;
    break;}
case 112:
#line 653 "parser.y"
{ yyval = "class Box"; ;
    break;}
case 113:
#line 654 "parser.y"
{ yyval = "class PinholeCamera"; ;
    break;}
case 114:
#line 655 "parser.y"
{ yyval = "class Circle"; ;
    break;}
case 115:
#line 656 "parser.y"
{ yyval = "class Cone"; ;
    break;}
case 116:
#line 657 "parser.y"
{ yyval = "class Cylinder"; ;
    break;}
case 117:
#line 658 "parser.y"
{ yyval = "/* [FIXME!]  difference  */ class Csg"; ;
    break;}
case 118:
#line 659 "parser.y"
{ yyval = "/* [FIXME!]    union     */ class Csg"; ;
    break;}
case 119:
#line 660 "parser.y"
{ yyval = "/* [FIXME!] intersection */ class Csg"; ;
    break;}
case 120:
#line 661 "parser.y"
{ yyval = "/* unknown image filter */"; ;
    break;}
case 121:
#line 662 "parser.y"
{ yyval = "/* unknown object filter */"; ;
    break;}
case 122:
#line 663 "parser.y"
{ yyval = "class PointLight"; ;
    break;}
case 123:
#line 664 "parser.y"
{ yyval = "class Mesh"; ;
    break;}
case 124:
#line 665 "parser.y"
{ yyval = "/* uknown object class */"; ;
    break;}
case 125:
#line 666 "parser.y"
{ yyval = "class Bsdf"; ;
    break;}
case 126:
#line 667 "parser.y"
{ yyval = "class Material"; ;
    break;}
case 127:
#line 668 "parser.y"
{ yyval = "class Pattern"; ;
    break;}
case 128:
#line 669 "parser.y"
{ yyval = "class Perturbation"; ;
    break;}
case 129:
#line 670 "parser.y"
{ yyval = "class PhongTriangle"; ;
    break;}
case 130:
#line 671 "parser.y"
{ yyval = "class Plane"; ;
    break;}
case 131:
#line 672 "parser.y"
{ yyval = "class Rectangle"; ;
    break;}
case 132:
#line 673 "parser.y"
{ yyval = "class Raytracer"; ;
    break;}
case 133:
#line 674 "parser.y"
{ yyval = "class Scene"; ;
    break;}
case 134:
#line 675 "parser.y"
{ yyval = "class Sphere"; ;
    break;}
case 135:
#line 676 "parser.y"
{ yyval = "class Torus"; ;
    break;}
case 136:
#line 677 "parser.y"
{ yyval = "class Triangle"; ;
    break;}
case 137:
#line 681 "parser.y"
{ yyval = "output"; ;
    break;}
case 138:
#line 682 "parser.y"
{ yyval = "color"; ;
    break;}
case 139:
#line 683 "parser.y"
{ yyval = "scale"; ;
    break;}
case 140:
#line 684 "parser.y"
{ yyval = "vertex"; ;
    break;}
case 141:
#line 685 "parser.y"
{ yyval = "filter"; ;
    break;}
case 142:
#line 686 "parser.y"
{ yyval = "type"; ;
    break;}
case 143:
#line 690 "parser.y"
{ yyval = yyvsp[0]; ;
    break;}
case 144:
#line 691 "parser.y"
{ yyval = yyvsp[0]; ;
    break;}
case 145:
#line 692 "parser.y"
{ yyval = "class"; ;
    break;}
case 146:
#line 693 "parser.y"
{ yyval = "define"; ;
    break;}
case 147:
#line 694 "parser.y"
{ yyval = "extends"; ;
    break;}
case 148:
#line 695 "parser.y"
{ yyval = "green"; ;
    break;}
case 149:
#line 696 "parser.y"
{ yyval = "red"; ;
    break;}
case 150:
#line 697 "parser.y"
{ yyval = "blue"; ;
    break;}
case 151:
#line 698 "parser.y"
{ yyval = "rotate"; ;
    break;}
case 152:
#line 699 "parser.y"
{ yyval = "translate"; ;
    break;}
case 153:
#line 700 "parser.y"
{ yyval = "vector"; ;
    break;}
case 154:
#line 701 "parser.y"
{ yyval = "x"; ;
    break;}
case 155:
#line 702 "parser.y"
{ yyval = "y"; ;
    break;}
case 156:
#line 703 "parser.y"
{ yyval = "z"; ;
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
#line 706 "parser.y"


void rt_conv_error (const char* pkcTEXT)
{

  cerr << endl << file_name << "(" << line_number << ") Error: " << pkcTEXT << endl;

}  /* rt_conv_error() */

void rt_conv_error (const string& rksTEXT)
{

  cerr << endl << file_name << "(" << line_number << ") Error: " << rksTEXT << endl;

}  /* rt_conv_error() */


void RT_CONV_InitParser (void)
{
  
}  /* RT_CONV_InitParser() */


void RT_CONV_CloseParser (void)
{

}  /* RT_CONV_CloseParser() */


string extract_class(const string& cls, const string& def)
{
  if( cls.length() >= 1 )
  {
    return cls;
  }
  return def;
}

/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         rt_parse
#define yylex           rt_lex
#define yyerror         rt_error
#define yydebug         rt_debug
#define yynerrs         rt_nerrs

#define yylval          rt_lval
#define yychar          rt_char

/* Copy the first part of user declarations.  */
#line 19 "parser.y" /* yacc.c:339  */


#include <map>
#include <stack>
#include <string>
#include <cstring>
#include <iostream>
#include "llapi/llapi_all.h"
#include "hlapi/hlapi_all.h"
#include "hlapi/class_manager.h"
#include "hlapi/plugins_all.h"
#include "parser_defs.h"
#include "rt_io.h"

static map<string, TProcedural*, less<string> >       _tObjectMap;
static map<string, TColor, less<string> >             _tColorMap;
static map<string, TVector, less<string> >            _tVectorMap;
static map<string, double(*)(void), less<string> >    _tFunctionMap;
static map<string, EClass, less<string> >             _tTypeMap;
static stack<TProcedural*>                            _tDataStack;

static TProcedural*   _ptData;
static TProcedural*   _ptParent;
static Byte           _bVertices;
static TVector        _tVector;
static TVector2       _tVector2;
static TColor         _tColor;
static TAggregate*    _ptWorld;
static NAttribute     _nAttrib;
static TImageIO*      _ptImageIO;

static double (*_pfFunction)(void);

#define POP()           top(); _tDataStack.pop()            // Fix to STL's pop()

#define DATA		(_tDataStack.top())
#define ENTITY		((TEntity*) _tDataStack.top())
#define VOLUME		((TVolume*) _tDataStack.top())
#define VECTOR		((TVector*) _tDataStack.top())
#define COLOR		((TColor*) _tDataStack.top())
#define SCENE		(TSceneRT::_ptParsedScene)
#define MATERIAL	((TMaterial*) _tDataStack.top())
#define OBJECT		((TObject*) _tDataStack.top())
#define AGGREGATE	((TAggregate*) _tDataStack.top())
#define TRIANGLE	((TTriangle*) _tDataStack.top())
#define RECTANGLE	((TRectangle*) _tDataStack.top())
#define MESH		((TMeshObject*) _tDataStack.top())

#define YYDEBUG 1
#define YYERROR_VERBOSE 

static TProcedural* NewObject (const string& rktCLASS, const TProcedural* pktPARENT);
static void* InstanceObject (const string& rktNAME);
static void* UpdateObject (const string& rktNAME);
static void DefineObject (const string& rktNAME, const string& rktCLASS, const string& rktDEF_CLASS);
static void CreateObject (const string& rktCLASS, const string& rktDEF_CLASS);
static void SetParameter (const string& rktATTRIB, EAttribType eTYPE);

static void DefineColor (const string& rktNAME);
static TColor* InstanceColor (const string& rktNAME);

static void DefineVector (const string& rktNAME);
static TVector* InstanceVector (const string& rktNAME);

static void UpdateAttribute (const string& rktATTRIBUTE, const string& rktIDENT);

static void InitObjects (void);
static void InitFunctions (void);

static EAttribType MapClassToAttribute (const TBaseClass* pktClass);

static string EAttribType_to_str (EAttribType eat);
 

#line 149 "parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_RT_PARSER_H_INCLUDED
# define YY_RT_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int rt_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_BOOL = 258,
    T_REAL = 259,
    T_INTEGER = 260,
    T_IDENTIFIER = 261,
    T_QUOTED_STRING = 262,
    T_AGGREGATE = 263,
    T_ATM_OBJECT = 264,
    T_BLUE = 265,
    T_BOX = 266,
    T_BSDF = 267,
    T_CAMERA = 268,
    T_CIRCLE = 269,
    T_CLASS = 270,
    T_COLOR = 271,
    T_CONE = 272,
    T_CYLINDER = 273,
    T_DEFINE = 274,
    T_DIFFERENCE = 275,
    T_EXTENDS = 276,
    T_FILTER = 277,
    T_GREEN = 278,
    T_IMAGE_FILTER = 279,
    T_INTERSECTION = 280,
    T_LIGHT = 281,
    T_MATERIAL = 282,
    T_MESH = 283,
    T_OBJECT = 284,
    T_OBJECT_FILTER = 285,
    T_OUTPUT = 286,
    T_PATTERN = 287,
    T_PERTURBATION = 288,
    T_PHONG_TRIANGLE = 289,
    T_PLANE = 290,
    T_RECTANGLE = 291,
    T_RED = 292,
    T_RENDERER = 293,
    T_ROTATE = 294,
    T_SCALE = 295,
    T_SCENE = 296,
    T_SPHERE = 297,
    T_TORUS = 298,
    T_TRANSLATE = 299,
    T_TRIANGLE = 300,
    T_TYPE = 301,
    T_UNION = 302,
    T_VECTOR = 303,
    T_VERTEX = 304,
    T_X = 305,
    T_Y = 306,
    T_Z = 307,
    T_ATTR_LIST = 308,
    T_ATTR_TYPE = 309,
    UNARY_MINUS = 310
  };
#endif
/* Tokens.  */
#define T_BOOL 258
#define T_REAL 259
#define T_INTEGER 260
#define T_IDENTIFIER 261
#define T_QUOTED_STRING 262
#define T_AGGREGATE 263
#define T_ATM_OBJECT 264
#define T_BLUE 265
#define T_BOX 266
#define T_BSDF 267
#define T_CAMERA 268
#define T_CIRCLE 269
#define T_CLASS 270
#define T_COLOR 271
#define T_CONE 272
#define T_CYLINDER 273
#define T_DEFINE 274
#define T_DIFFERENCE 275
#define T_EXTENDS 276
#define T_FILTER 277
#define T_GREEN 278
#define T_IMAGE_FILTER 279
#define T_INTERSECTION 280
#define T_LIGHT 281
#define T_MATERIAL 282
#define T_MESH 283
#define T_OBJECT 284
#define T_OBJECT_FILTER 285
#define T_OUTPUT 286
#define T_PATTERN 287
#define T_PERTURBATION 288
#define T_PHONG_TRIANGLE 289
#define T_PLANE 290
#define T_RECTANGLE 291
#define T_RED 292
#define T_RENDERER 293
#define T_ROTATE 294
#define T_SCALE 295
#define T_SCENE 296
#define T_SPHERE 297
#define T_TORUS 298
#define T_TRANSLATE 299
#define T_TRIANGLE 300
#define T_TYPE 301
#define T_UNION 302
#define T_VECTOR 303
#define T_VERTEX 304
#define T_X 305
#define T_Y 306
#define T_Z 307
#define T_ATTR_LIST 308
#define T_ATTR_TYPE 309
#define UNARY_MINUS 310

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 94 "parser.y" /* yacc.c:355  */

         char                  acIdent [200];
         double                dValue;
         bool                  gValue;
         TColor*               ptColor;
         TVector*              ptVector;
         TVector2*             ptVector2;
         TScene*               ptScene;
         TRenderer*            ptRenderer;
         TCamera*              ptCamera;
         TLight*               ptLight;
         TBsdf*                ptBsdf;
         TMaterial*            ptMaterial;
         TPattern*             ptPattern;
         TPerturbation*        ptPerturbation; 
         TObject*              ptObject;
         TImageFilter*         ptIFilter;
         TObjectFilter*        ptOFilter;
         TAtmosphericObject*   ptAtmObject;
         TImageIO*             ptImageIO;
       

#line 322 "parser.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE rt_lval;

int rt_parse (void);

#endif /* !YY_RT_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 337 "parser.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1744

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  147
/* YYNRULES -- Number of rules.  */
#define YYNRULES  331
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  613

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   310

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      60,    61,    57,    55,    65,    56,     2,    58,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    67,     2,
      64,     2,    66,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,     2,    63,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      59
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   248,   248,   249,   250,   253,   255,   259,   277,   279,
     281,   283,   285,   287,   289,   291,   293,   295,   297,   299,
     301,   303,   305,   307,   309,   311,   313,   315,   317,   319,
     321,   323,   325,   327,   329,   331,   333,   337,   341,   345,
     349,   353,   357,   361,   365,   369,   373,   377,   381,   385,
     389,   393,   398,   403,   410,   414,   426,   430,   434,   438,
     442,   446,   451,   460,   466,   473,   477,   484,   487,   494,
     497,   507,   514,   515,   518,   539,   561,   566,   571,   576,
     581,   586,   591,   596,   601,   605,   609,   614,   619,   624,
     629,   634,   639,   646,   647,   650,   654,   658,   662,   666,
     670,   674,   677,   681,   684,   685,   688,   692,   696,   700,
     699,   729,   730,   733,   737,   741,   748,   747,   760,   765,
     764,   774,   775,   778,   782,   786,   793,   792,   802,   803,
     806,   819,   823,   822,   832,   838,   837,   850,   851,   854,
     877,   881,   885,   889,   888,   898,   903,   902,   914,   913,
     923,   928,   927,   938,   937,   947,   952,   951,   962,   961,
     971,   976,   975,   986,   985,   995,  1000,   999,  1010,  1009,
    1019,  1024,  1023,  1034,  1033,  1043,  1048,  1047,  1058,  1057,
    1067,  1072,  1071,  1082,  1081,  1091,  1096,  1095,  1106,  1105,
    1115,  1120,  1119,  1130,  1129,  1139,  1144,  1143,  1154,  1153,
    1163,  1168,  1167,  1178,  1177,  1193,  1198,  1197,  1213,  1214,
    1217,  1222,  1226,  1225,  1241,  1246,  1245,  1261,  1262,  1265,
    1270,  1274,  1273,  1289,  1294,  1293,  1309,  1310,  1313,  1318,
    1322,  1321,  1331,  1336,  1335,  1345,  1346,  1349,  1353,  1357,
    1356,  1366,  1371,  1370,  1381,  1380,  1390,  1395,  1394,  1405,
    1404,  1414,  1419,  1418,  1429,  1428,  1438,  1443,  1442,  1453,
    1452,  1462,  1467,  1466,  1477,  1476,  1486,  1491,  1490,  1501,
    1500,  1510,  1515,  1514,  1524,  1525,  1528,  1533,  1537,  1536,
    1546,  1551,  1550,  1560,  1561,  1565,  1566,  1567,  1568,  1569,
    1570,  1571,  1572,  1573,  1574,  1575,  1576,  1577,  1578,  1579,
    1580,  1581,  1582,  1583,  1584,  1585,  1586,  1587,  1588,  1589,
    1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,  1598,  1599,
    1600,  1601,  1602,  1603,  1604,  1605,  1606,  1607,  1608,  1609,
    1610,  1611
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_BOOL", "T_REAL", "T_INTEGER",
  "T_IDENTIFIER", "T_QUOTED_STRING", "T_AGGREGATE", "T_ATM_OBJECT",
  "T_BLUE", "T_BOX", "T_BSDF", "T_CAMERA", "T_CIRCLE", "T_CLASS",
  "T_COLOR", "T_CONE", "T_CYLINDER", "T_DEFINE", "T_DIFFERENCE",
  "T_EXTENDS", "T_FILTER", "T_GREEN", "T_IMAGE_FILTER", "T_INTERSECTION",
  "T_LIGHT", "T_MATERIAL", "T_MESH", "T_OBJECT", "T_OBJECT_FILTER",
  "T_OUTPUT", "T_PATTERN", "T_PERTURBATION", "T_PHONG_TRIANGLE", "T_PLANE",
  "T_RECTANGLE", "T_RED", "T_RENDERER", "T_ROTATE", "T_SCALE", "T_SCENE",
  "T_SPHERE", "T_TORUS", "T_TRANSLATE", "T_TRIANGLE", "T_TYPE", "T_UNION",
  "T_VECTOR", "T_VERTEX", "T_X", "T_Y", "T_Z", "T_ATTR_LIST",
  "T_ATTR_TYPE", "'+'", "'-'", "'*'", "'/'", "UNARY_MINUS", "'('", "')'",
  "'{'", "'}'", "'<'", "','", "'>'", "':'", "$accept", "everything",
  "instance", "definition", "object", "real_expr", "color", "vector3",
  "vector2", "vertex_instance", "name", "class", "params", "param",
  "entity_params", "entity_param", "volume_param", "object_params",
  "object_param", "color_def", "$@1", "color_params", "color_param",
  "vector_def", "$@2", "vector_instance", "$@3", "vector_params",
  "vector_param", "image_io_instance", "$@4", "image_io_params",
  "image_io_param", "scene_def", "$@5", "scene_instance", "$@6",
  "scene_params", "scene_param", "light_def", "$@7", "light_instance",
  "$@8", "bsdf_def", "$@9", "bsdf_instance", "$@10", "renderer_def",
  "$@11", "renderer_instance", "$@12", "material_def", "$@13",
  "material_instance", "$@14", "pattern_def", "$@15", "pattern_instance",
  "$@16", "perturbation_def", "$@17", "perturbation_instance", "$@18",
  "ifilter_def", "$@19", "ifilter_instance", "$@20", "ofilter_def", "$@21",
  "ofilter_instance", "$@22", "camera_def", "$@23", "camera_instance",
  "$@24", "object_def", "$@25", "object_instance", "$@26", "plane_def",
  "$@27", "plane_instance", "$@28", "sphere_def", "$@29",
  "sphere_instance", "$@30", "triangle_def", "$@31", "triangle_instance",
  "$@32", "triangle_params", "triangle_param", "phong_triangle_def",
  "$@33", "phong_triangle_instance", "$@34", "phong_triangle_params",
  "phong_triangle_param", "rectangle_def", "$@35", "rectangle_instance",
  "$@36", "rectangle_params", "rectangle_param", "circle_def", "$@37",
  "circle_instance", "$@38", "aggregate_params", "aggregate_param",
  "aggregate_def", "$@39", "aggregate_instance", "$@40", "atm_object_def",
  "$@41", "atm_object_instance", "$@42", "box_def", "$@43", "box_instance",
  "$@44", "cylinder_def", "$@45", "cylinder_instance", "$@46", "cone_def",
  "$@47", "cone_instance", "$@48", "torus_def", "$@49", "torus_instance",
  "$@50", "mesh_def", "$@51", "mesh_instance", "$@52", "mesh_params",
  "mesh_param", "csg_def", "$@53", "csg_instance", "$@54",
  "potential_string", "reserved_words", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,    43,    45,    42,    47,   310,
      40,    41,   123,   125,    60,    44,    62,    58
};
# endif

#define YYPACT_NINF -283

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-283)))

#define YYTABLE_NINF -70

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -283,  1656,  -283,    70,    70,    70,    70,    70,    70,  1696,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,  -283,  -283,  -283,  -283,   129,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,    23,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      23,    23,    23,    23,    23,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
      31,   109,    54,    55,    84,    87,    95,   100,    97,  -283,
      97,  -283,    97,  -283,    97,  -283,    97,  -283,    97,  -283,
      97,  -283,    97,  -283,    97,  -283,    97,  -283,    97,  -283,
    -283,    97,  -283,    97,  -283,    97,  -283,    97,  -283,    97,
    -283,    97,  -283,    97,  -283,    97,  -283,    97,  -283,    97,
    -283,    97,  -283,    97,  -283,    97,  -283,    97,  -283,    97,
    -283,  -283,    97,  -283,   113,   123,   125,   133,   140,   144,
     146,   148,   150,   152,   154,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,   641,  1346,   879,   899,   928,   948,   156,   158,   160,
     162,   163,   165,   167,   169,   171,   173,   175,   177,   179,
     181,   183,   185,   187,   189,   191,   193,   194,   196,   197,
     204,   205,   206,   227,   685,   280,   816,   977,   409,   997,
     469,   407,  1026,  1046,   498,   107,    70,    70,   134,    70,
      70,    70,   116,   117,   106,    70,   231,   237,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,    70,  -283,  -283,  -283,  -283,   117,  -283,    71,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,    70,
      70,   238,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,   239,  -283,    71,    71,   264,    71,   335,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,   335,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,    29,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,   245,  1601,   729,  1354,
    1075,  1365,   834,  1095,   119,  1124,  1144,   773,  1373,  1288,
    1417,   836,  1173,  1419,  1431,  1448,   528,  1193,   557,  1450,
    1261,  1222,  1242,   587,   102,  -283,  -283,   239,   281,  -283,
    -283,  -283,  -283,  -283,  -283,   248,  -283,   -23,    71,   341,
      71,    71,    71,    71,   253,   254,   255,   258,   261,   263,
     265,   106,   267,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,   269,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
      71,    71,    71,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,    71,    71,    71,  -283,  -283,    71,
     270,  -283,  -283,  -283,   -15,    71,    22,    22,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,   335,   335,   335,   335,   335,   335,   353,  -283,  1334,
      71,   207,  1462,  1493,  1506,  1300,  1514,  1526,  1537,   232,
      71,  1545,   319,  -283,  -283,  -283,    68,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,   256,  -283,  -283,    71,
    -283,   103,  -283
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,    67,    67,    67,    67,    67,    67,     0,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,     3,     4,     7,    68,     0,   241,   242,
      45,   246,   247,     6,   251,   252,    46,   232,   233,    44,
     261,   262,    48,   256,   257,    47,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,   280,   281,    53,    52,   145,
     146,    38,   271,   272,    50,   190,   191,    37,   214,   215,
      42,   195,   196,    39,   223,   224,    43,   134,   135,     5,
     200,   201,    40,   266,   267,    49,   205,   206,    41,    51,
       0,     0,     0,     0,     0,     0,     0,     0,    69,    27,
      69,    33,    69,    28,    69,    14,    69,    12,    69,    26,
      69,     8,    69,    30,    69,    29,    69,    36,    69,    15,
      35,    69,    13,    69,    18,    69,    32,    69,    10,    69,
      16,    69,    19,    69,    20,    69,    24,    69,    21,    69,
      25,    69,    17,    69,    11,    69,    22,    69,    31,    69,
      23,    34,    69,     9,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    71,    70,   235,    72,   104,
     104,   104,   104,   239,   244,   249,   148,   183,   230,   109,
     259,   254,   278,   173,   143,   158,   269,   188,   178,   163,
     168,   212,   193,   221,   153,   132,   198,   264,   203,   116,
     235,    93,   274,   104,   217,   104,   226,   137,   104,   104,
     208,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    67,    67,    67,    67,    67,
      67,    67,    67,     0,    67,    67,     0,     0,   243,   237,
     101,   103,   108,   238,   236,   248,    73,   253,   105,   234,
     263,   258,   235,    72,   104,    72,    93,   104,   111,   104,
     104,   235,    72,    93,    72,   274,   104,    72,    72,    72,
     217,   104,   226,    72,   137,   104,   104,   208,   121,   282,
     147,    94,    67,   273,   277,   275,   192,     0,   216,     0,
      65,   219,   220,   218,   197,   225,   228,   229,   227,    67,
      67,     0,   136,   142,   138,   202,   268,   207,   210,   211,
     209,    79,    54,    68,    80,     0,     0,     0,     0,    78,
      83,    76,    77,    84,   166,    81,    82,   150,   151,    92,
     185,   186,    90,    86,    87,    85,   166,    88,   180,   181,
     107,   160,   161,   106,   155,   156,    91,     0,    96,   118,
     119,    99,   102,    95,    98,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   276,    66,     0,     0,   175,
     176,   140,   139,   126,   141,     0,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    67,     0,    74,   283,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,     0,   284,   240,   245,   250,   149,   184,   231,
       0,     0,     0,   110,   112,   260,   255,   279,   174,   144,
     159,   270,   189,   179,   164,   169,   213,   194,   222,   154,
     133,   199,   265,   204,     0,     0,     0,   117,   122,     0,
       0,   128,    55,    61,     0,     0,    56,    57,    58,    59,
      72,    72,    72,    93,    72,    72,    72,    97,   100,   121,
      75,   115,   114,   113,   123,   124,   125,     0,    72,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   127,   131,   129,     0,    64,   167,   172,
     152,   187,   182,   162,   157,   120,     0,   177,   130,     0,
      63,     0,    62
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -283,  -283,  -283,  -283,   334,   -78,    62,  -201,  -283,  -244,
      -1,    85,  -184,  -232,  -282,  -264,  -283,    79,  -123,  -283,
    -283,  -283,  -283,  -283,  -283,  -262,  -283,  -228,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,    18,  -283,  -283,
    -283,    -6,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,    67,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,    21,
    -283,    30,  -283,  -283,  -283,  -283,  -283,    38,  -283,  -283,
    -283,  -283,  -283,    45,  -283,  -283,  -283,  -283,  -283,  -193,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,
    -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,  -283,    53,
    -283,   -29,  -283,    14,  -283,  -283,  -283
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    23,    24,   289,   369,   370,   340,   372,   341,
     399,   400,   232,   290,   265,   291,   292,   233,   298,   131,
     243,   414,   524,   173,   263,   401,   462,   434,   548,   444,
     551,   579,   595,   164,   259,    99,   181,   271,   354,   142,
     248,    81,   175,   125,   240,   379,   456,   162,   258,   396,
     460,   144,   249,   393,   459,   152,   253,   375,   454,   154,
     254,   376,   455,   139,   247,   441,   550,   150,   252,   390,
     458,   127,   241,   382,   457,   148,   251,    87,   177,   158,
     256,    93,   179,   166,   260,   102,   182,   170,   262,   108,
     184,   274,   360,   156,   255,    90,   178,   268,   343,   160,
     257,    96,   180,   270,   348,   129,   242,    39,   115,   231,
     294,   119,   237,    30,   112,   121,   238,    33,   113,   123,
     239,    36,   114,   135,   245,    45,   117,   133,   244,    42,
     116,   168,   261,   105,   183,   146,   250,    84,   176,   266,
     335,   137,   246,    77,   174,   512,   513
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     296,   331,    28,    31,    34,    37,    40,    43,   580,    75,
      75,    79,    82,    85,    88,    91,    94,    97,   100,   103,
     106,    75,   404,   405,   412,    78,   346,   264,   140,    26,
     358,   419,   450,   451,   452,   453,   109,   185,   553,   353,
     450,   451,   452,   453,   171,   118,   120,   122,   124,   126,
     128,   130,   132,   134,   136,   138,   136,   141,   143,   145,
     147,   149,   151,   153,   155,   157,   159,   161,   163,   165,
     167,   169,   136,   172,   371,   362,    26,   437,   609,   452,
     453,   398,   402,   403,   450,   451,   452,   453,    29,    32,
      35,    38,    41,    44,   461,    76,    76,    80,    83,    86,
      89,    92,    95,    98,   101,   104,   107,    76,   293,   408,
     361,   362,    26,   363,   364,   186,   187,   188,   417,   409,
     362,   411,   363,   450,   451,   452,   453,   365,   418,   520,
     420,   366,   -69,   423,   424,   425,   436,    27,   362,   429,
     363,   293,   521,   334,   110,   342,   189,   347,   331,   190,
     111,   359,   544,   545,   546,   331,   522,   191,   450,   451,
     452,   453,   192,   365,    27,   547,   612,   366,   -69,   367,
     339,   368,   365,    27,    27,   220,   366,   296,   -69,   296,
     339,   339,   523,    27,   346,   221,   296,   222,   296,   358,
     365,   296,   296,   296,   366,   223,   367,   296,   353,   568,
     383,    27,   224,   193,   397,   194,   225,   195,   226,   196,
     227,   197,   228,   198,   229,   199,   230,   200,   302,   201,
     303,   202,   304,   203,   305,   306,   204,   307,   205,   308,
     206,   309,   207,   310,   208,   311,   209,   312,   210,   313,
     211,   314,   212,   315,   213,   316,   214,   317,   215,   318,
     216,   319,   217,   320,   218,   321,   322,   219,   323,   324,
     567,   438,   450,   451,   452,   453,   325,   326,   327,   234,
     235,   236,   590,   597,   373,   377,   380,   385,   388,   391,
     394,   585,   544,   545,   546,   293,   275,   446,   447,   328,
     449,   406,   276,   277,   293,   605,   278,   407,   334,   445,
     443,   448,   267,   342,   269,   347,   463,   272,   273,   552,
     359,   450,   451,   452,   453,   560,   561,   562,   281,   282,
     563,   331,   610,   564,   284,   565,   608,   566,   285,   569,
     570,   106,   578,   286,   287,    25,   450,   451,   452,   453,
     384,   589,   430,   330,   442,   387,   549,   594,   439,    79,
     296,   296,   296,   435,   296,   296,   296,   433,   426,   296,
     374,   378,   381,   386,   389,   392,   395,   428,   421,     0,
     554,     0,   556,   557,   558,   559,   582,   583,   584,     0,
     586,   587,   588,   410,     0,     0,   413,     0,   415,   416,
     450,   451,   452,   453,   591,   422,   450,   451,   452,   453,
     427,     0,     0,     0,   431,   432,   555,     0,   450,   451,
     452,   453,     0,   275,     0,   275,     0,   107,   590,   276,
     277,   276,   277,   278,     0,   278,     0,     0,     0,   349,
       0,   279,     0,   350,   440,    80,   280,     0,   351,     0,
       0,     0,   571,   572,   573,   281,     0,   281,   282,   283,
       0,     0,     0,   284,     0,   285,     0,   285,   337,     0,
     286,   287,   286,   287,     0,     0,   574,   575,   576,     0,
     352,   577,   338,   339,     0,   275,     0,   581,     0,     0,
       0,   276,   277,     0,     0,   278,     0,     0,     0,     0,
       0,   279,     0,     0,     0,     0,   280,     0,     0,     0,
       0,     0,   596,     0,   275,     0,     0,   281,   282,   283,
     276,   277,   606,   284,   278,     0,     0,   285,   337,     0,
     279,     0,   286,   287,     0,   280,     0,     0,     0,     0,
       0,   611,   345,   339,   275,     0,   281,   282,   283,     0,
     276,   277,   284,     0,   278,     0,   285,   337,     0,     0,
     279,   286,   287,     0,     0,   280,     0,     0,     0,     0,
       0,   357,   339,   275,     0,     0,   281,   282,   283,   276,
     277,     0,   284,   278,     0,     0,   285,   337,     0,   279,
       0,   286,   287,     0,   280,     0,     0,     0,     0,     0,
       0,   536,   339,   275,     0,   281,   282,   283,     0,   276,
     277,   284,     0,   278,     0,   285,   337,     0,     0,   279,
     286,   287,     0,     0,   280,     0,     0,     0,     0,     0,
     538,   339,     0,     0,     0,   281,   282,   283,     0,     0,
       0,   284,     0,     0,     0,   285,   337,     0,     0,     0,
     286,   287,     0,     0,     0,     0,     0,   275,     0,     3,
     543,   339,     5,   276,   277,     6,     0,   278,     7,     8,
       0,    10,     0,   279,     0,     0,    11,    12,   280,    13,
      14,     0,     0,     0,     0,    15,    16,    17,     0,   281,
     282,   283,     0,    19,    20,   284,    21,     0,    22,   285,
       0,   275,     0,     3,   286,   287,     5,   276,   277,     6,
       0,   278,     7,     8,   288,    10,     0,   279,     0,     0,
      11,    12,   280,    13,    14,     0,     0,     0,     0,    15,
      16,    17,     0,   281,   282,   283,     0,    19,    20,   284,
      21,     0,    22,   285,     0,   275,     0,     3,   286,   287,
       5,   276,   277,     6,     0,   278,     7,     8,   329,    10,
       0,   279,     0,     0,    11,    12,   280,    13,    14,     0,
       0,     0,     0,    15,    16,    17,     0,   281,   282,   283,
       0,    19,    20,   284,    21,     0,    22,   285,     0,   275,
       0,     3,   286,   287,     5,   276,   277,     6,     0,   278,
       7,     8,   514,    10,     0,   279,     0,     0,    11,    12,
     280,    13,    14,     0,     0,     0,     0,    15,    16,    17,
       0,   281,   282,   283,     0,    19,    20,   284,    21,     0,
      22,   285,   275,     0,     0,     0,   286,   287,   276,   277,
       0,     0,   278,     0,     0,     0,   527,     0,   279,     0,
     275,     0,   275,   280,     0,     0,   276,   277,   276,   277,
     278,     0,   278,     0,   281,   282,   283,     0,   279,     0,
     284,   332,     0,   280,   285,     0,     0,     0,     0,   286,
     287,     0,   281,   282,   281,   282,   283,     0,   284,   333,
     284,   332,   285,     0,   285,   275,     0,   286,   287,   286,
     287,   276,   277,     0,     0,   278,     0,   518,     0,   531,
       0,   279,     0,     0,     0,   275,   280,     0,     0,     0,
       0,   276,   277,     0,     0,   278,     0,   281,   282,   283,
       0,   279,     0,   284,     0,     0,   280,   285,     0,     0,
       0,     0,   286,   287,   275,     0,     0,   281,   282,   283,
     276,   277,   297,   284,   278,     0,     0,   285,     0,     0,
     279,     0,   286,   287,   275,   280,     0,     0,     0,     0,
     276,   277,   299,     0,   278,     0,   281,   282,   283,     0,
     279,     0,   284,     0,     0,   280,   285,     0,     0,     0,
       0,   286,   287,   275,     0,     0,   281,   282,   283,   276,
     277,   300,   284,   278,     0,     0,   285,     0,     0,   279,
       0,   286,   287,   275,   280,     0,     0,     0,     0,   276,
     277,   301,     0,   278,     0,   281,   282,   283,     0,   279,
       0,   284,     0,     0,   280,   285,     0,     0,     0,     0,
     286,   287,   275,     0,     0,   281,   282,   283,   276,   277,
     336,   284,   278,     0,     0,   285,     0,     0,   279,     0,
     286,   287,   275,   280,     0,     0,     0,     0,   276,   277,
     344,     0,   278,     0,   281,   282,   283,     0,   279,     0,
     284,     0,     0,   280,   285,     0,     0,     0,     0,   286,
     287,   275,     0,     0,   281,   282,   283,   276,   277,   355,
     284,   278,     0,     0,   285,     0,     0,   279,     0,   286,
     287,   275,   280,     0,     0,     0,     0,   276,   277,   356,
       0,   278,     0,   281,   282,   283,     0,   279,     0,   284,
       0,     0,   280,   285,     0,     0,     0,     0,   286,   287,
     275,     0,     0,   281,   282,   283,   276,   277,   516,   284,
     278,     0,     0,   285,     0,     0,   279,     0,   286,   287,
     275,   280,     0,     0,     0,     0,   276,   277,   519,     0,
     278,     0,   281,   282,   283,     0,   279,     0,   284,     0,
       0,   280,   285,     0,     0,     0,     0,   286,   287,   275,
       0,     0,   281,   282,   283,   276,   277,   525,   284,   278,
       0,     0,   285,     0,     0,   279,     0,   286,   287,   275,
     280,     0,     0,     0,     0,   276,   277,   526,     0,   278,
       0,   281,   282,   283,     0,   279,     0,   284,     0,     0,
     280,   285,     0,     0,     0,     0,   286,   287,   275,     0,
       0,   281,   282,   283,   276,   277,   532,   284,   278,     0,
       0,   285,     0,     0,   279,     0,   286,   287,   275,   280,
       0,     0,     0,     0,   276,   277,   537,     0,   278,     0,
     281,   282,   283,     0,   279,     0,   284,   275,     0,   280,
     285,     0,     0,   276,   277,   286,   287,   278,     0,     0,
     281,   282,   283,   349,     0,   541,   284,   350,     0,     0,
     285,     0,   351,     0,   275,   286,   287,     0,     0,   281,
     276,   277,     0,     0,   278,   542,   275,     0,     0,   285,
       0,     0,   276,   277,   286,   287,   278,     0,     0,     0,
       0,     0,     0,     0,   540,     0,   281,   282,     0,     0,
       0,     0,   284,     0,     0,     0,   285,     0,   281,   282,
     275,   286,   287,     0,   284,     0,   276,   277,   285,     0,
     278,   529,   275,   286,   287,     0,     0,     0,   276,   277,
     275,     0,   278,   601,     0,     0,   276,   277,     0,     0,
     278,   275,   281,     0,     0,     0,     0,   276,   277,   275,
     592,   278,   285,     0,   281,   276,   277,   286,   287,   278,
       0,     0,   281,     0,   285,     0,     0,   593,     0,   286,
     287,     0,   285,   281,     0,     0,     0,   286,   287,   295,
       0,   281,     0,   285,     0,     0,     0,   515,   286,   287,
       0,   285,     0,   275,     0,   275,   286,   287,   517,   276,
     277,   276,   277,   278,     0,   278,   528,   275,     0,     0,
       0,     0,     0,   276,   277,     0,     0,   278,     0,     0,
       0,     0,     0,     0,   275,   281,   275,   281,     0,     0,
     276,   277,   276,   277,   278,   285,   278,   285,   275,   281,
     286,   287,   286,   287,   276,   277,     0,     0,   278,   285,
     530,     0,   533,     0,   286,   287,   281,     0,   281,     0,
       0,     0,     0,     0,   534,     0,   285,     0,   285,   275,
     281,   286,   287,   286,   287,   276,   277,     0,     0,   278,
     285,   535,   275,   539,     0,   286,   287,     0,   276,   277,
     275,     0,   278,     0,     0,   598,   276,   277,     0,     0,
     278,   281,   275,     0,     0,     0,     0,     0,   276,   277,
       0,   285,   278,   275,   281,     0,   286,   287,     0,   276,
     277,   275,   281,   278,   285,     0,   599,   276,   277,   286,
     287,   278,   285,     0,   281,     0,     0,   286,   287,   600,
       0,     0,     0,     0,   285,   281,     0,   602,     0,   286,
     287,     0,     0,   281,     0,   285,     0,     0,     0,   603,
     286,   287,     0,   285,     0,     0,     0,     0,   286,   287,
     604,     0,     0,     0,     0,     0,     0,   464,   607,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   503,   504,   505,
     506,   507,   508,   509,   510,   511,     2,     0,     0,     0,
       0,     0,     0,     0,     3,     4,     0,     5,     0,     0,
       6,     0,     0,     7,     8,     9,    10,     0,     0,     0,
       0,    11,    12,     0,    13,    14,     0,     0,     0,     0,
      15,    16,    17,     0,     0,     0,     0,    18,    19,    20,
       0,    21,     0,    22,    46,    47,     0,    48,    49,    50,
      51,     0,    52,    53,    54,     0,    55,     0,     0,     0,
      56,    57,    58,    59,    60,    61,    62,     0,    63,    64,
      65,    66,    67,     0,    68,     0,     0,    69,    70,    71,
       0,    72,     0,    73,    74
};

static const yytype_int16 yycheck[] =
{
     232,   265,     3,     4,     5,     6,     7,     8,    23,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,   284,   285,   306,    11,   270,   220,    57,     6,
     274,   313,    55,    56,    57,    58,    22,     6,    61,   271,
      55,    56,    57,    58,    73,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,   275,     4,     6,     6,    10,    57,
      58,   282,   283,   284,    55,    56,    57,    58,     3,     4,
       5,     6,     7,     8,    65,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,   231,   302,
       3,     4,     6,     6,     7,     6,    62,    62,   311,   303,
       4,   305,     6,    55,    56,    57,    58,    56,   312,    10,
     314,    60,    62,   317,   318,   319,   337,    67,     4,   323,
       6,   264,    23,   266,    15,   268,    62,   270,   412,    62,
      21,   274,    50,    51,    52,   419,    37,    62,    55,    56,
      57,    58,    62,    56,    67,    63,    63,    60,    62,    62,
      64,    64,    56,    67,    67,    62,    60,   409,    62,   411,
      64,    64,    63,    67,   428,    62,   418,    62,   420,   433,
      56,   423,   424,   425,    60,    62,    62,   429,   430,   461,
     278,    67,    62,   118,   282,   120,    62,   122,    62,   124,
      62,   126,    62,   128,    62,   130,    62,   132,    62,   134,
      62,   136,    62,   138,    62,    62,   141,    62,   143,    62,
     145,    62,   147,    62,   149,    62,   151,    62,   153,    62,
     155,    62,   157,    62,   159,    62,   161,    62,   163,    62,
     165,    62,   167,    62,   169,    62,    62,   172,    62,    62,
     461,   339,    55,    56,    57,    58,    62,    62,    62,   190,
     191,   192,    65,    66,   275,   276,   277,   278,   279,   280,
     281,   563,    50,    51,    52,   408,     6,   365,   366,    62,
     368,    60,    12,    13,   417,    63,    16,    60,   421,    60,
      62,    37,   223,   426,   225,   428,    61,   228,   229,    61,
     433,    55,    56,    57,    58,    62,    62,    62,    38,    39,
      62,   585,    66,    62,    44,    62,     7,    62,    48,    62,
      61,   332,    62,    53,    54,     1,    55,    56,    57,    58,
     278,   569,   324,    63,   350,   278,    65,   579,   349,   350,
     582,   583,   584,   332,   586,   587,   588,   327,   320,   591,
     275,   276,   277,   278,   279,   280,   281,   322,   315,    -1,
     448,    -1,   450,   451,   452,   453,   560,   561,   562,    -1,
     564,   565,   566,   304,    -1,    -1,   307,    -1,   309,   310,
      55,    56,    57,    58,   578,   316,    55,    56,    57,    58,
     321,    -1,    -1,    -1,   325,   326,    65,    -1,    55,    56,
      57,    58,    -1,     6,    -1,     6,    -1,   332,    65,    12,
      13,    12,    13,    16,    -1,    16,    -1,    -1,    -1,    22,
      -1,    22,    -1,    26,   349,   350,    27,    -1,    31,    -1,
      -1,    -1,   520,   521,   522,    38,    -1,    38,    39,    40,
      -1,    -1,    -1,    44,    -1,    48,    -1,    48,    49,    -1,
      53,    54,    53,    54,    -1,    -1,   544,   545,   546,    -1,
      63,   549,    63,    64,    -1,     6,    -1,   555,    -1,    -1,
      -1,    12,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,
      -1,    22,    -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,
      -1,    -1,   580,    -1,     6,    -1,    -1,    38,    39,    40,
      12,    13,   590,    44,    16,    -1,    -1,    48,    49,    -1,
      22,    -1,    53,    54,    -1,    27,    -1,    -1,    -1,    -1,
      -1,   609,    63,    64,     6,    -1,    38,    39,    40,    -1,
      12,    13,    44,    -1,    16,    -1,    48,    49,    -1,    -1,
      22,    53,    54,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    63,    64,     6,    -1,    -1,    38,    39,    40,    12,
      13,    -1,    44,    16,    -1,    -1,    48,    49,    -1,    22,
      -1,    53,    54,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,     6,    -1,    38,    39,    40,    -1,    12,
      13,    44,    -1,    16,    -1,    48,    49,    -1,    -1,    22,
      53,    54,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      63,    64,    -1,    -1,    -1,    38,    39,    40,    -1,    -1,
      -1,    44,    -1,    -1,    -1,    48,    49,    -1,    -1,    -1,
      53,    54,    -1,    -1,    -1,    -1,    -1,     6,    -1,     8,
      63,    64,    11,    12,    13,    14,    -1,    16,    17,    18,
      -1,    20,    -1,    22,    -1,    -1,    25,    26,    27,    28,
      29,    -1,    -1,    -1,    -1,    34,    35,    36,    -1,    38,
      39,    40,    -1,    42,    43,    44,    45,    -1,    47,    48,
      -1,     6,    -1,     8,    53,    54,    11,    12,    13,    14,
      -1,    16,    17,    18,    63,    20,    -1,    22,    -1,    -1,
      25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    34,
      35,    36,    -1,    38,    39,    40,    -1,    42,    43,    44,
      45,    -1,    47,    48,    -1,     6,    -1,     8,    53,    54,
      11,    12,    13,    14,    -1,    16,    17,    18,    63,    20,
      -1,    22,    -1,    -1,    25,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    34,    35,    36,    -1,    38,    39,    40,
      -1,    42,    43,    44,    45,    -1,    47,    48,    -1,     6,
      -1,     8,    53,    54,    11,    12,    13,    14,    -1,    16,
      17,    18,    63,    20,    -1,    22,    -1,    -1,    25,    26,
      27,    28,    29,    -1,    -1,    -1,    -1,    34,    35,    36,
      -1,    38,    39,    40,    -1,    42,    43,    44,    45,    -1,
      47,    48,     6,    -1,    -1,    -1,    53,    54,    12,    13,
      -1,    -1,    16,    -1,    -1,    -1,    63,    -1,    22,    -1,
       6,    -1,     6,    27,    -1,    -1,    12,    13,    12,    13,
      16,    -1,    16,    -1,    38,    39,    40,    -1,    22,    -1,
      44,    45,    -1,    27,    48,    -1,    -1,    -1,    -1,    53,
      54,    -1,    38,    39,    38,    39,    40,    -1,    44,    63,
      44,    45,    48,    -1,    48,     6,    -1,    53,    54,    53,
      54,    12,    13,    -1,    -1,    16,    -1,    63,    -1,    63,
      -1,    22,    -1,    -1,    -1,     6,    27,    -1,    -1,    -1,
      -1,    12,    13,    -1,    -1,    16,    -1,    38,    39,    40,
      -1,    22,    -1,    44,    -1,    -1,    27,    48,    -1,    -1,
      -1,    -1,    53,    54,     6,    -1,    -1,    38,    39,    40,
      12,    13,    63,    44,    16,    -1,    -1,    48,    -1,    -1,
      22,    -1,    53,    54,     6,    27,    -1,    -1,    -1,    -1,
      12,    13,    63,    -1,    16,    -1,    38,    39,    40,    -1,
      22,    -1,    44,    -1,    -1,    27,    48,    -1,    -1,    -1,
      -1,    53,    54,     6,    -1,    -1,    38,    39,    40,    12,
      13,    63,    44,    16,    -1,    -1,    48,    -1,    -1,    22,
      -1,    53,    54,     6,    27,    -1,    -1,    -1,    -1,    12,
      13,    63,    -1,    16,    -1,    38,    39,    40,    -1,    22,
      -1,    44,    -1,    -1,    27,    48,    -1,    -1,    -1,    -1,
      53,    54,     6,    -1,    -1,    38,    39,    40,    12,    13,
      63,    44,    16,    -1,    -1,    48,    -1,    -1,    22,    -1,
      53,    54,     6,    27,    -1,    -1,    -1,    -1,    12,    13,
      63,    -1,    16,    -1,    38,    39,    40,    -1,    22,    -1,
      44,    -1,    -1,    27,    48,    -1,    -1,    -1,    -1,    53,
      54,     6,    -1,    -1,    38,    39,    40,    12,    13,    63,
      44,    16,    -1,    -1,    48,    -1,    -1,    22,    -1,    53,
      54,     6,    27,    -1,    -1,    -1,    -1,    12,    13,    63,
      -1,    16,    -1,    38,    39,    40,    -1,    22,    -1,    44,
      -1,    -1,    27,    48,    -1,    -1,    -1,    -1,    53,    54,
       6,    -1,    -1,    38,    39,    40,    12,    13,    63,    44,
      16,    -1,    -1,    48,    -1,    -1,    22,    -1,    53,    54,
       6,    27,    -1,    -1,    -1,    -1,    12,    13,    63,    -1,
      16,    -1,    38,    39,    40,    -1,    22,    -1,    44,    -1,
      -1,    27,    48,    -1,    -1,    -1,    -1,    53,    54,     6,
      -1,    -1,    38,    39,    40,    12,    13,    63,    44,    16,
      -1,    -1,    48,    -1,    -1,    22,    -1,    53,    54,     6,
      27,    -1,    -1,    -1,    -1,    12,    13,    63,    -1,    16,
      -1,    38,    39,    40,    -1,    22,    -1,    44,    -1,    -1,
      27,    48,    -1,    -1,    -1,    -1,    53,    54,     6,    -1,
      -1,    38,    39,    40,    12,    13,    63,    44,    16,    -1,
      -1,    48,    -1,    -1,    22,    -1,    53,    54,     6,    27,
      -1,    -1,    -1,    -1,    12,    13,    63,    -1,    16,    -1,
      38,    39,    40,    -1,    22,    -1,    44,     6,    -1,    27,
      48,    -1,    -1,    12,    13,    53,    54,    16,    -1,    -1,
      38,    39,    40,    22,    -1,    63,    44,    26,    -1,    -1,
      48,    -1,    31,    -1,     6,    53,    54,    -1,    -1,    38,
      12,    13,    -1,    -1,    16,    63,     6,    -1,    -1,    48,
      -1,    -1,    12,    13,    53,    54,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    38,    39,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    48,    -1,    38,    39,
       6,    53,    54,    -1,    44,    -1,    12,    13,    48,    -1,
      16,    63,     6,    53,    54,    -1,    -1,    -1,    12,    13,
       6,    -1,    16,    63,    -1,    -1,    12,    13,    -1,    -1,
      16,     6,    38,    -1,    -1,    -1,    -1,    12,    13,     6,
      46,    16,    48,    -1,    38,    12,    13,    53,    54,    16,
      -1,    -1,    38,    -1,    48,    -1,    -1,    63,    -1,    53,
      54,    -1,    48,    38,    -1,    -1,    -1,    53,    54,    63,
      -1,    38,    -1,    48,    -1,    -1,    -1,    63,    53,    54,
      -1,    48,    -1,     6,    -1,     6,    53,    54,    63,    12,
      13,    12,    13,    16,    -1,    16,    63,     6,    -1,    -1,
      -1,    -1,    -1,    12,    13,    -1,    -1,    16,    -1,    -1,
      -1,    -1,    -1,    -1,     6,    38,     6,    38,    -1,    -1,
      12,    13,    12,    13,    16,    48,    16,    48,     6,    38,
      53,    54,    53,    54,    12,    13,    -1,    -1,    16,    48,
      63,    -1,    63,    -1,    53,    54,    38,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    48,    -1,    48,     6,
      38,    53,    54,    53,    54,    12,    13,    -1,    -1,    16,
      48,    63,     6,    63,    -1,    53,    54,    -1,    12,    13,
       6,    -1,    16,    -1,    -1,    63,    12,    13,    -1,    -1,
      16,    38,     6,    -1,    -1,    -1,    -1,    -1,    12,    13,
      -1,    48,    16,     6,    38,    -1,    53,    54,    -1,    12,
      13,     6,    38,    16,    48,    -1,    63,    12,    13,    53,
      54,    16,    48,    -1,    38,    -1,    -1,    53,    54,    63,
      -1,    -1,    -1,    -1,    48,    38,    -1,    63,    -1,    53,
      54,    -1,    -1,    38,    -1,    48,    -1,    -1,    -1,    63,
      53,    54,    -1,    48,    -1,    -1,    -1,    -1,    53,    54,
      63,    -1,    -1,    -1,    -1,    -1,    -1,     6,    63,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,     0,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     8,     9,    -1,    11,    -1,    -1,
      14,    -1,    -1,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    25,    26,    -1,    28,    29,    -1,    -1,    -1,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    41,    42,    43,
      -1,    45,    -1,    47,     8,     9,    -1,    11,    12,    13,
      14,    -1,    16,    17,    18,    -1,    20,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    -1,    32,    33,
      34,    35,    36,    -1,    38,    -1,    -1,    41,    42,    43,
      -1,    45,    -1,    47,    48
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    69,     0,     8,     9,    11,    14,    17,    18,    19,
      20,    25,    26,    28,    29,    34,    35,    36,    41,    42,
      43,    45,    47,    70,    71,    72,     6,    67,    78,    79,
     181,    78,    79,   185,    78,    79,   189,    78,    79,   175,
      78,    79,   197,    78,    79,   193,     8,     9,    11,    12,
      13,    14,    16,    17,    18,    20,    24,    25,    26,    27,
      28,    29,    30,    32,    33,    34,    35,    36,    38,    41,
      42,    43,    45,    47,    48,    78,    79,   211,   211,    78,
      79,   109,    78,    79,   205,    78,    79,   145,    78,    79,
     163,    78,    79,   149,    78,    79,   169,    78,    79,   103,
      78,    79,   153,    78,    79,   201,    78,    79,   157,   211,
      15,    21,   182,   186,   190,   176,   198,   194,    78,   179,
      78,   183,    78,   187,    78,   111,    78,   139,    78,   173,
      78,    87,    78,   195,    78,   191,    78,   209,    78,   131,
     209,    78,   107,    78,   119,    78,   203,    78,   143,    78,
     135,    78,   123,    78,   127,    78,   161,    78,   147,    78,
     167,    78,   115,    78,   101,    78,   151,    78,   199,    78,
     155,   209,    78,    91,   212,   110,   206,   146,   164,   150,
     170,   104,   154,   202,   158,     6,     6,    62,    62,    62,
      62,    62,    62,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,   177,    80,    85,    85,    85,    85,   180,   184,   188,
     112,   140,   174,    88,   196,   192,   210,   132,   108,   120,
     204,   144,   136,   124,   128,   162,   148,   168,   116,   102,
     152,   200,   156,    92,   177,    82,   207,    85,   165,    85,
     171,   105,    85,    85,   159,     6,    12,    13,    16,    22,
      27,    38,    39,    40,    44,    48,    53,    54,    63,    72,
      81,    83,    84,    86,   178,    63,    81,    63,    86,    63,
      63,    63,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    63,
      63,    83,    45,    63,    86,   208,    63,    49,    63,    64,
      75,    77,    86,   166,    63,    63,    77,    86,   172,    22,
      26,    31,    63,    81,   106,    63,    63,    63,    77,    86,
     160,     3,     4,     6,     7,    56,    60,    62,    64,    73,
      74,    75,    76,    78,    79,   125,   129,    78,    79,   113,
      78,    79,   141,    73,    74,    78,    79,   125,    78,    79,
     137,    78,    79,   121,    78,    79,   117,    73,    75,    78,
      79,    93,    75,    75,    93,    93,    60,    60,   177,    80,
      85,    80,    82,    85,    89,    85,    85,   177,    80,    82,
      80,   207,    85,    80,    80,    80,   165,    85,   171,    80,
     105,    85,    85,   159,    95,   157,    75,     6,    73,    78,
      79,   133,   109,    62,    97,    60,    73,    73,    37,    73,
      55,    56,    57,    58,   126,   130,   114,   142,   138,   122,
     118,    65,    94,    61,     6,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,   213,   214,    63,    63,    63,    63,    63,    63,
      10,    23,    37,    63,    90,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    50,    51,    52,    63,    96,    65,
     134,    98,    61,    61,    73,    65,    73,    73,    73,    73,
      62,    62,    62,    62,    62,    62,    62,    75,    93,    62,
      61,    73,    73,    73,    73,    73,    73,    73,    62,    99,
      23,    73,    80,    80,    80,    82,    80,    80,    80,    95,
      65,    80,    46,    63,    81,   100,    73,    66,    63,    63,
      63,    63,    63,    63,    63,    63,    73,    63,     7,    10,
      66,    73,    63
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    68,    69,    69,    69,    70,    70,    70,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    73,    73,    73,    73,    73,    73,
      73,    73,    74,    75,    76,    77,    77,    78,    78,    79,
      79,    79,    80,    80,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    82,    82,    83,    83,    83,    83,    83,
      83,    83,    84,    84,    85,    85,    86,    86,    86,    88,
      87,    89,    89,    90,    90,    90,    92,    91,    93,    94,
      93,    95,    95,    96,    96,    96,    98,    97,    99,    99,
     100,   100,   102,   101,   103,   104,   103,   105,   105,   106,
     106,   106,   106,   108,   107,   109,   110,   109,   112,   111,
     113,   114,   113,   116,   115,   117,   118,   117,   120,   119,
     121,   122,   121,   124,   123,   125,   126,   125,   128,   127,
     129,   130,   129,   132,   131,   133,   134,   133,   136,   135,
     137,   138,   137,   140,   139,   141,   142,   141,   144,   143,
     145,   146,   145,   148,   147,   149,   150,   149,   152,   151,
     153,   154,   153,   156,   155,   157,   158,   157,   159,   159,
     160,   160,   162,   161,   163,   164,   163,   165,   165,   166,
     166,   168,   167,   169,   170,   169,   171,   171,   172,   172,
     174,   173,   175,   176,   175,   177,   177,   178,   178,   180,
     179,   181,   182,   181,   184,   183,   185,   186,   185,   188,
     187,   189,   190,   189,   192,   191,   193,   194,   193,   196,
     195,   197,   198,   197,   200,   199,   201,   202,   201,   204,
     203,   205,   206,   205,   207,   207,   208,   208,   210,   209,
     211,   212,   211,   213,   213,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,   214,   214,
     214,   214
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     1,     3,     3,     3,     3,     3,
       2,     3,     8,     7,     5,     1,     2,     0,     1,     0,
       3,     3,     0,     2,     3,     4,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     0,     2,     2,     2,     4,     2,     2,
       4,     1,     2,     1,     0,     2,     2,     2,     1,     0,
       6,     0,     2,     2,     2,     2,     0,     6,     1,     0,
       5,     0,     2,     2,     2,     2,     0,     4,     0,     2,
       2,     1,     0,     6,     1,     0,     5,     0,     2,     2,
       2,     2,     1,     0,     6,     1,     0,     5,     0,     6,
       1,     0,     5,     0,     6,     1,     0,     5,     0,     6,
       1,     0,     5,     0,     6,     1,     0,     5,     0,     6,
       1,     0,     5,     0,     6,     1,     0,     5,     0,     6,
       1,     0,     5,     0,     6,     1,     0,     5,     0,     6,
       1,     0,     5,     0,     6,     1,     0,     5,     0,     6,
       1,     0,     5,     0,     6,     1,     0,     5,     0,     2,
       1,     1,     0,     6,     1,     0,     5,     0,     2,     1,
       1,     0,     6,     1,     0,     5,     0,     2,     1,     1,
       0,     6,     1,     0,     5,     0,     2,     1,     1,     0,
       6,     1,     0,     5,     0,     6,     1,     0,     5,     0,
       6,     1,     0,     5,     0,     6,     1,     0,     5,     0,
       6,     1,     0,     5,     0,     6,     1,     0,     5,     0,
       6,     1,     0,     5,     0,     2,     2,     1,     0,     6,
       1,     0,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:
#line 254 "parser.y" /* yacc.c:1646  */
    {}
#line 2111 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 256 "parser.y" /* yacc.c:1646  */
    {
                            SCENE->atmosphere()->addObject ((yyvsp[0].ptAtmObject));
                          }
#line 2119 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 260 "parser.y" /* yacc.c:1646  */
    {
			    // Sanity check to avoid adding an object more than
			    // once. 
			    if( !_ptWorld->containsObject( (yyvsp[0].ptObject) ) )
			    {
			      _ptWorld->add ((yyvsp[0].ptObject));
			    }
			    else
			    {
			      // Somehow, the object was added more than
			      // once... 
			      string s = "This object is already in the scene: ";
			      rt_error(s + (yyvsp[0].ptObject)->className());
			    }
                          }
#line 2139 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 278 "parser.y" /* yacc.c:1646  */
    {}
#line 2145 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 280 "parser.y" /* yacc.c:1646  */
    {}
#line 2151 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 282 "parser.y" /* yacc.c:1646  */
    {}
#line 2157 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 284 "parser.y" /* yacc.c:1646  */
    {}
#line 2163 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 286 "parser.y" /* yacc.c:1646  */
    {}
#line 2169 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 288 "parser.y" /* yacc.c:1646  */
    {}
#line 2175 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 290 "parser.y" /* yacc.c:1646  */
    {}
#line 2181 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 292 "parser.y" /* yacc.c:1646  */
    {}
#line 2187 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 294 "parser.y" /* yacc.c:1646  */
    {}
#line 2193 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 296 "parser.y" /* yacc.c:1646  */
    {}
#line 2199 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 298 "parser.y" /* yacc.c:1646  */
    {}
#line 2205 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 300 "parser.y" /* yacc.c:1646  */
    {}
#line 2211 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 302 "parser.y" /* yacc.c:1646  */
    {}
#line 2217 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 304 "parser.y" /* yacc.c:1646  */
    {}
#line 2223 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 306 "parser.y" /* yacc.c:1646  */
    {}
#line 2229 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 308 "parser.y" /* yacc.c:1646  */
    {}
#line 2235 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 310 "parser.y" /* yacc.c:1646  */
    {}
#line 2241 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 312 "parser.y" /* yacc.c:1646  */
    {}
#line 2247 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 314 "parser.y" /* yacc.c:1646  */
    {}
#line 2253 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 316 "parser.y" /* yacc.c:1646  */
    {}
#line 2259 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 318 "parser.y" /* yacc.c:1646  */
    {}
#line 2265 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 320 "parser.y" /* yacc.c:1646  */
    {}
#line 2271 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 322 "parser.y" /* yacc.c:1646  */
    {}
#line 2277 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 324 "parser.y" /* yacc.c:1646  */
    {}
#line 2283 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 326 "parser.y" /* yacc.c:1646  */
    {}
#line 2289 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 328 "parser.y" /* yacc.c:1646  */
    {}
#line 2295 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 330 "parser.y" /* yacc.c:1646  */
    {}
#line 2301 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 332 "parser.y" /* yacc.c:1646  */
    {}
#line 2307 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 334 "parser.y" /* yacc.c:1646  */
    {}
#line 2313 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 338 "parser.y" /* yacc.c:1646  */
    {
                            (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2321 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 342 "parser.y" /* yacc.c:1646  */
    {
                            (yyval.ptObject) = (yyvsp[0].ptLight);
			  }
#line 2329 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 346 "parser.y" /* yacc.c:1646  */
    {
                            (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2337 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 350 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (yyvsp[0].ptObject);
			  }
#line 2345 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 354 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2353 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 358 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2361 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 362 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2369 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 366 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2377 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 370 "parser.y" /* yacc.c:1646  */
    {
                            (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2385 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 374 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2393 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 378 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2401 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 382 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2409 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 386 "parser.y" /* yacc.c:1646  */
    {
                            (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2417 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 390 "parser.y" /* yacc.c:1646  */
    {
                            (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2425 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 394 "parser.y" /* yacc.c:1646  */
    {
                            ((TCsg*) (yyvsp[0].ptObject))->setOperation (FX_CSG_UNION);
                            (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2434 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 399 "parser.y" /* yacc.c:1646  */
    {
                            ((TCsg*) (yyvsp[0].ptObject))->setOperation (FX_CSG_INTERSECTION);
                            (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2443 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 404 "parser.y" /* yacc.c:1646  */
    {
                            ((TCsg*) (yyvsp[0].ptObject))->setOperation (FX_CSG_DIFFERENCE);
                            (yyval.ptObject) = (yyvsp[0].ptObject);
                          }
#line 2452 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 411 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.dValue) = (yyvsp[0].dValue);
			  }
#line 2460 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 415 "parser.y" /* yacc.c:1646  */
    {
                            if ( _tFunctionMap.find ((yyvsp[-2].acIdent)) == _tFunctionMap.end() )
                            {
			      yyerror ("function does not exist");
			      exit (1);
                            }

			    _pfFunction = _tFunctionMap [(yyvsp[-2].acIdent)];

			    (yyval.dValue) = (*_pfFunction)();
			  }
#line 2476 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 427 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.dValue) = (yyvsp[-2].dValue) + (yyvsp[0].dValue);
			  }
#line 2484 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 431 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.dValue) = (yyvsp[-2].dValue) - (yyvsp[0].dValue);
			  }
#line 2492 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 435 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.dValue) = (yyvsp[-2].dValue) * (yyvsp[0].dValue);
			  }
#line 2500 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 439 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.dValue) = (yyvsp[-2].dValue) / (yyvsp[0].dValue);
			  }
#line 2508 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 443 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.dValue) = -(yyvsp[0].dValue);
			  }
#line 2516 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 447 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.dValue) = (yyvsp[-1].dValue);
			  }
#line 2524 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 452 "parser.y" /* yacc.c:1646  */
    {
			    _tColor.setRed ((yyvsp[-5].dValue));
			    _tColor.setGreen ((yyvsp[-3].dValue));
			    _tColor.setBlue ((yyvsp[-1].dValue));
			    (yyval.ptColor) = (TColor*) &_tColor;
			  }
#line 2535 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 461 "parser.y" /* yacc.c:1646  */
    {
			    _tVector.set ((yyvsp[-5].dValue), (yyvsp[-3].dValue), (yyvsp[-1].dValue));
			    (yyval.ptVector) = &_tVector;
			  }
#line 2544 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 467 "parser.y" /* yacc.c:1646  */
    {
			    _tVector2.set ((yyvsp[-3].dValue), (yyvsp[-1].dValue));
			    (yyval.ptVector2) = &_tVector2;
			  }
#line 2553 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 474 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptVector) = (yyvsp[0].ptVector);
			  }
#line 2561 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 478 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptVector) = (yyvsp[0].ptVector);
			  }
#line 2569 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 484 "parser.y" /* yacc.c:1646  */
    {
			    strcpy ((yyval.acIdent), "");
			  }
#line 2577 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 488 "parser.y" /* yacc.c:1646  */
    {
			    strcpy ((yyval.acIdent), (yyvsp[0].acIdent));
			  }
#line 2585 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 494 "parser.y" /* yacc.c:1646  */
    {
			    strcpy ((yyval.acIdent), "");
			  }
#line 2593 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 498 "parser.y" /* yacc.c:1646  */
    {
                            if ( _tObjectMap.find ((yyvsp[0].acIdent)) == _tObjectMap.end() )
                            {
			      yyerror ("trying to extend from non existing object");
			      exit (1);
                            }
                            _ptParent = _tObjectMap [(yyvsp[0].acIdent)];
			    strcpy ((yyval.acIdent), _ptParent->className().c_str());
			  }
#line 2607 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 508 "parser.y" /* yacc.c:1646  */
    {
			    _ptParent = NULL;
			    strcpy ((yyval.acIdent), (yyvsp[0].acIdent));
			  }
#line 2616 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 519 "parser.y" /* yacc.c:1646  */
    {
			    /* Print out an attribute list [names w/types] for
			       the current object */ 
			    TAttributeList   tal;
			  
			    DATA->getAttributeList (tal);
			    
			    cout << "Requested attribute list for \""
				 << DATA->className() << "\"" << endl;
			    
			    for(TAttributeList::const_iterator i = tal.begin();
				i != tal.end();
				++i)
			    {
			      cout << "  ("
				   << EAttribType_to_str (i->second)
				   << ") "
				   << i->first << endl;
			    }
			  }
#line 2641 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 540 "parser.y" /* yacc.c:1646  */
    {
			    /* Print out the type of the given attribute */
			    TAttributeList                   tal;
			    TAttributeList::const_iterator   loc;
			    
			    DATA->getAttributeList (tal);
			    
			    loc = tal.find (string((yyvsp[-1].acIdent))); 
			    
			    cout << "Requested attribute type for \"" << (yyvsp[-1].acIdent)
				 << "\" in \"" << DATA->className() << "\": ";
			    
			    if ( loc != tal.end() )
			    {
			      cout << EAttribType_to_str (loc->second) << endl;
			    }
			    else
			    {
			      cout << "no such attribute" << endl;
			    }
			  }
#line 2667 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 562 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.pvValue = (yyvsp[0].ptVector);
			    SetParameter ((yyvsp[-1].acIdent), FX_VECTOR);
                          }
#line 2676 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 567 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.pvValue = (yyvsp[0].ptVector2);
			    SetParameter ((yyvsp[-1].acIdent), FX_VECTOR2);
			  }
#line 2685 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 572 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.dValue = (yyvsp[0].dValue);
			    SetParameter ((yyvsp[-1].acIdent), FX_REAL);
			  }
#line 2694 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 577 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.gValue = (yyvsp[0].gValue);
			    SetParameter ((yyvsp[-1].acIdent), FX_BOOL);
			  }
#line 2703 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 582 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.pvValue = (yyvsp[0].acIdent);
			    SetParameter ((yyvsp[-1].acIdent), FX_STRING);
			  }
#line 2712 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 587 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.pvValue = (yyvsp[0].ptPattern);
			    SetParameter ((yyvsp[-1].acIdent), MapClassToAttribute ((TBaseClass*) (yyvsp[0].ptPattern)));
                          }
#line 2721 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 592 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.pvValue = (yyvsp[0].ptPerturbation);
			    SetParameter ((yyvsp[-1].acIdent), MapClassToAttribute ((TBaseClass*) (yyvsp[0].ptPerturbation)));
                          }
#line 2730 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 597 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.pvValue = (yyvsp[0].ptColor);
			    SetParameter ((yyvsp[-1].acIdent), FX_COLOR);
			  }
#line 2739 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 602 "parser.y" /* yacc.c:1646  */
    {
			    UpdateAttribute ((yyvsp[-1].acIdent), (yyvsp[0].acIdent));
			  }
#line 2747 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 606 "parser.y" /* yacc.c:1646  */
    {
			    UpdateAttribute ("color", (yyvsp[0].acIdent));
			  }
#line 2755 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 610 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.dValue = (yyvsp[0].dValue);
			    SetParameter ("color", FX_REAL);
			  }
#line 2764 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 615 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.pvValue = (yyvsp[0].ptColor);
			    SetParameter ("color", FX_COLOR);
			  }
#line 2773 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 620 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.pvValue = (yyvsp[0].ptPattern);
			    SetParameter ("color", FX_PATTERN);
                          }
#line 2782 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 625 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.pvValue = (yyvsp[0].ptVector);
			    SetParameter ("vector", FX_VECTOR);
			  }
#line 2791 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 630 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.pvValue = (yyvsp[0].ptCamera);
			    SetParameter ("camera", FX_CAMERA);
			  }
#line 2800 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 635 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.pvValue = (yyvsp[0].ptRenderer);
			    SetParameter ("renderer", FX_RENDERER);
			  }
#line 2809 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 640 "parser.y" /* yacc.c:1646  */
    {
			    _nAttrib.pvValue = (yyvsp[0].ptBsdf);
			    SetParameter ("bsdf", FX_BSDF);
			  }
#line 2818 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 651 "parser.y" /* yacc.c:1646  */
    {
			    ENTITY->translate (*(yyvsp[0].ptVector));
			  }
#line 2826 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 655 "parser.y" /* yacc.c:1646  */
    {
			    ENTITY->rotate (*(yyvsp[0].ptVector));
			  }
#line 2834 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 659 "parser.y" /* yacc.c:1646  */
    {
			    ENTITY->rotate (makeUnitQuaternion ((yyvsp[-2].dValue), *(yyvsp[0].ptVector)));
                          }
#line 2842 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 663 "parser.y" /* yacc.c:1646  */
    {
			    ENTITY->translate (*(yyvsp[0].ptVector));
			  }
#line 2850 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 667 "parser.y" /* yacc.c:1646  */
    {
			    ENTITY->rotate (*(yyvsp[0].ptVector));
			  }
#line 2858 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 671 "parser.y" /* yacc.c:1646  */
    {
			    ENTITY->rotate (makeUnitQuaternion ((yyvsp[-2].dValue), *(yyvsp[0].ptVector)));
                          }
#line 2866 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 678 "parser.y" /* yacc.c:1646  */
    {
			    VOLUME->scale (*(yyvsp[0].ptVector), TVector (0, 0, 0));
			  }
#line 2874 "parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 689 "parser.y" /* yacc.c:1646  */
    {
			    OBJECT->setMaterial ((yyvsp[0].ptMaterial));
			  }
#line 2882 "parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 693 "parser.y" /* yacc.c:1646  */
    {
			    OBJECT->addFilter ((yyvsp[0].ptOFilter));
			  }
#line 2890 "parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 700 "parser.y" /* yacc.c:1646  */
    {
			    DefineColor ((yyvsp[-1].acIdent));
			  }
#line 2898 "parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 704 "parser.y" /* yacc.c:1646  */
    {
                            _tColorMap [(yyvsp[-5].acIdent)] = _tColor;
			    _tTypeMap  [(yyvsp[-5].acIdent)] = FX_COLOR_CLASS;
                            
                            (yyval.ptColor) = &_tColor;
			  }
#line 2909 "parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 734 "parser.y" /* yacc.c:1646  */
    {
			    _tColor.setRed ((yyvsp[0].dValue));
			  }
#line 2917 "parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 738 "parser.y" /* yacc.c:1646  */
    {
			    _tColor.setGreen ((yyvsp[0].dValue));
			  }
#line 2925 "parser.c" /* yacc.c:1646  */
    break;

  case 115:
#line 742 "parser.y" /* yacc.c:1646  */
    {
			    _tColor.setBlue ((yyvsp[0].dValue));
			  }
#line 2933 "parser.c" /* yacc.c:1646  */
    break;

  case 116:
#line 748 "parser.y" /* yacc.c:1646  */
    {
			    DefineVector ((yyvsp[-1].acIdent));
			  }
#line 2941 "parser.c" /* yacc.c:1646  */
    break;

  case 117:
#line 752 "parser.y" /* yacc.c:1646  */
    {
                            _tVectorMap [(yyvsp[-5].acIdent)] = _tVector;
			    _tTypeMap   [(yyvsp[-5].acIdent)] = FX_VECTOR_CLASS;
                            
                            (yyval.ptVector) = &_tVector;
			  }
#line 2952 "parser.c" /* yacc.c:1646  */
    break;

  case 118:
#line 761 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptVector) = InstanceVector ((yyvsp[0].acIdent));
			  }
#line 2960 "parser.c" /* yacc.c:1646  */
    break;

  case 119:
#line 765 "parser.y" /* yacc.c:1646  */
    {
                            _tVector = TVector (0, 0, 0);
			  }
#line 2968 "parser.c" /* yacc.c:1646  */
    break;

  case 120:
#line 769 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptVector) = (TVector*) &_tVector;
			  }
#line 2976 "parser.c" /* yacc.c:1646  */
    break;

  case 123:
#line 779 "parser.y" /* yacc.c:1646  */
    {
			    _tVector.setX ((yyvsp[0].dValue));
			  }
#line 2984 "parser.c" /* yacc.c:1646  */
    break;

  case 124:
#line 783 "parser.y" /* yacc.c:1646  */
    {
			    _tVector.setY ((yyvsp[0].dValue));
			  }
#line 2992 "parser.c" /* yacc.c:1646  */
    break;

  case 125:
#line 787 "parser.y" /* yacc.c:1646  */
    {
			    _tVector.setZ ((yyvsp[0].dValue));
			  }
#line 3000 "parser.c" /* yacc.c:1646  */
    break;

  case 126:
#line 793 "parser.y" /* yacc.c:1646  */
    {
                            _tDataStack.push (TImageManager::_getImageIO ("tga"));
                          }
#line 3008 "parser.c" /* yacc.c:1646  */
    break;

  case 127:
#line 797 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptImageIO) = (TImageIO*) _tDataStack.POP();
			  }
#line 3016 "parser.c" /* yacc.c:1646  */
    break;

  case 130:
#line 807 "parser.y" /* yacc.c:1646  */
    {
                            _ptImageIO = (TImageIO*) _tDataStack.POP();
                            delete _ptImageIO;
                            
                            _ptImageIO = TImageManager::_getImageIO ((yyvsp[0].acIdent));
                            if ( !_ptImageIO )
                            {
                              yyerror ("Image output type not available");
                              exit (1);
                            }
                            _tDataStack.push (_ptImageIO);
			  }
#line 3033 "parser.c" /* yacc.c:1646  */
    break;

  case 132:
#line 823 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Scene");
			  }
#line 3041 "parser.c" /* yacc.c:1646  */
    break;

  case 133:
#line 827 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptScene) = (TScene*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3049 "parser.c" /* yacc.c:1646  */
    break;

  case 134:
#line 833 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptScene) = (TScene*) InstanceObject ((yyvsp[0].acIdent));
			    TSceneRT::_ptParsedScene = (yyval.ptScene);
			  }
#line 3058 "parser.c" /* yacc.c:1646  */
    break;

  case 135:
#line 838 "parser.y" /* yacc.c:1646  */
    {
//			    CreateObject ($1, "Scene");
			    _ptData = TSceneRT::_ptParsedScene;
			    _tDataStack.push (_ptData);
			  }
#line 3068 "parser.c" /* yacc.c:1646  */
    break;

  case 136:
#line 844 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptScene) = (TScene*) _tDataStack.POP();
//			    $$ = &tScene;
			  }
#line 3077 "parser.c" /* yacc.c:1646  */
    break;

  case 139:
#line 855 "parser.y" /* yacc.c:1646  */
    {
			    // This is no longer needed, as there are speial
			    // cases for this in the light_instance rule.
			    if( (yyvsp[0].ptLight) )
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
			      SCENE->addLight ((yyvsp[0].ptLight));
			    }
			  }
#line 3104 "parser.c" /* yacc.c:1646  */
    break;

  case 140:
#line 878 "parser.y" /* yacc.c:1646  */
    {
			    SCENE->addImageFilter ((yyvsp[0].ptIFilter));
			  }
#line 3112 "parser.c" /* yacc.c:1646  */
    break;

  case 141:
#line 882 "parser.y" /* yacc.c:1646  */
    {
			    SCENE->setImageOutput ((yyvsp[0].ptImageIO));
			  }
#line 3120 "parser.c" /* yacc.c:1646  */
    break;

  case 143:
#line 889 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "PointLight");
			  }
#line 3128 "parser.c" /* yacc.c:1646  */
    break;

  case 144:
#line 893 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptLight) = (TLight*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3136 "parser.c" /* yacc.c:1646  */
    break;

  case 145:
#line 899 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptLight) = (TLight*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3144 "parser.c" /* yacc.c:1646  */
    break;

  case 146:
#line 903 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "PointLight");
			  }
#line 3152 "parser.c" /* yacc.c:1646  */
    break;

  case 147:
#line 907 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptLight) = (TLight*) _tDataStack.POP();
			    // This one is passed back to the scene instance...
			  }
#line 3161 "parser.c" /* yacc.c:1646  */
    break;

  case 148:
#line 914 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Bsdf");
			  }
#line 3169 "parser.c" /* yacc.c:1646  */
    break;

  case 149:
#line 918 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptBsdf) = (TBsdf*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3177 "parser.c" /* yacc.c:1646  */
    break;

  case 150:
#line 924 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptBsdf) = (TBsdf*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3185 "parser.c" /* yacc.c:1646  */
    break;

  case 151:
#line 928 "parser.y" /* yacc.c:1646  */
    {
                            CreateObject ((yyvsp[0].acIdent), "Bsdf");
			  }
#line 3193 "parser.c" /* yacc.c:1646  */
    break;

  case 152:
#line 932 "parser.y" /* yacc.c:1646  */
    {
                            (yyval.ptBsdf) = (TBsdf*) _tDataStack.POP();
			  }
#line 3201 "parser.c" /* yacc.c:1646  */
    break;

  case 153:
#line 938 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Raytracer");
			  }
#line 3209 "parser.c" /* yacc.c:1646  */
    break;

  case 154:
#line 942 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptRenderer) = (TRenderer*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3217 "parser.c" /* yacc.c:1646  */
    break;

  case 155:
#line 948 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptRenderer) = (TRenderer*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3225 "parser.c" /* yacc.c:1646  */
    break;

  case 156:
#line 952 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Raytracer");
			  }
#line 3233 "parser.c" /* yacc.c:1646  */
    break;

  case 157:
#line 956 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptRenderer) = (TRenderer*) _tDataStack.POP();
			  }
#line 3241 "parser.c" /* yacc.c:1646  */
    break;

  case 158:
#line 962 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Material");
			  }
#line 3249 "parser.c" /* yacc.c:1646  */
    break;

  case 159:
#line 966 "parser.y" /* yacc.c:1646  */
    {
                            (yyval.ptMaterial) = (TMaterial*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3257 "parser.c" /* yacc.c:1646  */
    break;

  case 160:
#line 972 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptMaterial) = (TMaterial*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3265 "parser.c" /* yacc.c:1646  */
    break;

  case 161:
#line 976 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Material");
			  }
#line 3273 "parser.c" /* yacc.c:1646  */
    break;

  case 162:
#line 980 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptMaterial) = (TMaterial*) _tDataStack.POP();
			  }
#line 3281 "parser.c" /* yacc.c:1646  */
    break;

  case 163:
#line 986 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Pattern");
			  }
#line 3289 "parser.c" /* yacc.c:1646  */
    break;

  case 164:
#line 990 "parser.y" /* yacc.c:1646  */
    {
                            (yyval.ptPattern) = (TPattern*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3297 "parser.c" /* yacc.c:1646  */
    break;

  case 165:
#line 996 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptPattern) = (TPattern*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3305 "parser.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1000 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Pattern");
			  }
#line 3313 "parser.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1004 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptPattern) = (TPattern*) _tDataStack.POP();
			  }
#line 3321 "parser.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1010 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Perturbation");
			  }
#line 3329 "parser.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1014 "parser.y" /* yacc.c:1646  */
    {
                            (yyval.ptPerturbation) = (TPerturbation*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3337 "parser.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1020 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptPerturbation) = (TPerturbation*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3345 "parser.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1024 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Perturbation");
			  }
#line 3353 "parser.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1028 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptPerturbation) = (TPerturbation*) _tDataStack.POP();
			  }
#line 3361 "parser.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1034 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "");
			  }
#line 3369 "parser.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1038 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptIFilter) = (TImageFilter*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3377 "parser.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1044 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptIFilter) = (TImageFilter*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3385 "parser.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1048 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "");
			  }
#line 3393 "parser.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1052 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptIFilter) = (TImageFilter*) _tDataStack.POP();
			  }
#line 3401 "parser.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1058 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "");
			  }
#line 3409 "parser.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1062 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptOFilter) = (TObjectFilter*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3417 "parser.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1068 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptOFilter) = (TObjectFilter*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3425 "parser.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1072 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "");
			  }
#line 3433 "parser.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1076 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptOFilter) = (TObjectFilter*) _tDataStack.POP();
			  }
#line 3441 "parser.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1082 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "PinholeCamera");
			  }
#line 3449 "parser.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1086 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptCamera) = (TCamera*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3457 "parser.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1092 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptCamera) = (TCamera*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3465 "parser.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1096 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "PinholeCamera");
			  }
#line 3473 "parser.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1100 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptCamera) = (TCamera*) _tDataStack.POP();
			  }
#line 3481 "parser.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1106 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "");
			  }
#line 3489 "parser.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1110 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TObject*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3497 "parser.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1116 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TObject*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3505 "parser.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1120 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "");
			  }
#line 3513 "parser.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1124 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TObject*) _tDataStack.POP();
			  }
#line 3521 "parser.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1130 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Plane");
			  }
#line 3529 "parser.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1134 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TPlane*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3537 "parser.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1140 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TPlane*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3545 "parser.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1144 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Plane");
			  }
#line 3553 "parser.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1148 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TPlane*) _tDataStack.POP();
			  }
#line 3561 "parser.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1154 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Sphere");
			  }
#line 3569 "parser.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1158 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TSphere*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3577 "parser.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1164 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TSphere*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3585 "parser.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1168 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Sphere");
			  }
#line 3593 "parser.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1172 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TSphere*) _tDataStack.POP();
			  }
#line 3601 "parser.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1178 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Triangle");
			    _bVertices = 0;
			  }
#line 3610 "parser.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1183 "parser.y" /* yacc.c:1646  */
    {
			    if ( _bVertices != 3 )
			    {
			      yyerror ("wrong number of vertices in triangle");
			      exit (1);
			    }
			    (yyval.ptObject) = (TTriangle*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3623 "parser.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1194 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TTriangle*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3631 "parser.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1198 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Triangle");
			    _bVertices = 0;
			  }
#line 3640 "parser.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1203 "parser.y" /* yacc.c:1646  */
    {
			    if ( _bVertices != 3 )
			    {
			      yyerror ("wrong number of vertices in triangle");
			      exit (1);
			    }
			    (yyval.ptObject) = (TTriangle*) _tDataStack.POP();
			  }
#line 3653 "parser.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1218 "parser.y" /* yacc.c:1646  */
    {
			    TRIANGLE->setVertex (*(yyvsp[0].ptVector));
			    _bVertices++;
			  }
#line 3662 "parser.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1226 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "PhongTriangle");
			    _bVertices = 0;
			  }
#line 3671 "parser.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1231 "parser.y" /* yacc.c:1646  */
    {
			    if ( _bVertices != 3 )
			    {
			      yyerror ("wrong number of vertices in phong_triangle");
			      exit (1);
			    }
			    (yyval.ptObject) = (TPhongTriangle*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3684 "parser.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1242 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TPhongTriangle*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3692 "parser.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1246 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "PhongTriangle");
			    _bVertices = 0;
			  }
#line 3701 "parser.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1251 "parser.y" /* yacc.c:1646  */
    {
			    if ( _bVertices != 3 )
			    {
			      yyerror ("wrong number of vertices in phong_triangle");
			      exit (1);
			    }
			    (yyval.ptObject) = (TPhongTriangle*) _tDataStack.POP();
			  }
#line 3714 "parser.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1266 "parser.y" /* yacc.c:1646  */
    {
			    TRIANGLE->setVertex (*(yyvsp[0].ptVector));
			    _bVertices++;
			  }
#line 3723 "parser.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1274 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Rectangle");
			    _bVertices = 0;
			  }
#line 3732 "parser.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1279 "parser.y" /* yacc.c:1646  */
    {
			    if ( _bVertices != 4 )
			    {
			      yyerror ("wrong number of vertices in rectangle");
			      exit (1);
			    }
			    (yyval.ptObject) = (TRectangle*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3745 "parser.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1290 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TRectangle*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3753 "parser.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1294 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Rectangle");
			    _bVertices = 0;
			  }
#line 3762 "parser.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1299 "parser.y" /* yacc.c:1646  */
    {
			    if ( _bVertices != 4 )
			    {
			      yyerror ("wrong number of vertices in rectangle");
			      exit (1);
			    }
			    (yyval.ptObject) = (TRectangle*) _tDataStack.POP();
			  }
#line 3775 "parser.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1314 "parser.y" /* yacc.c:1646  */
    {
			    RECTANGLE->setVertex (*(yyvsp[0].ptVector));
			    _bVertices++;
			  }
#line 3784 "parser.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1322 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Circle");
			  }
#line 3792 "parser.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1326 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TCircle*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3800 "parser.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1332 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TCircle*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3808 "parser.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1336 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Circle");
			  }
#line 3816 "parser.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1340 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TCircle*) _tDataStack.POP();
			  }
#line 3824 "parser.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1350 "parser.y" /* yacc.c:1646  */
    {
			    AGGREGATE->add ((yyvsp[0].ptObject));
			  }
#line 3832 "parser.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1357 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Aggregate");
			  }
#line 3840 "parser.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1361 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TAggregate*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3848 "parser.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1367 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TAggregate*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3856 "parser.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1371 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Aggregate");
			  }
#line 3864 "parser.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1375 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TAggregate*) _tDataStack.POP();
			  }
#line 3872 "parser.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1381 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "AtmConst");
			  }
#line 3880 "parser.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1385 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptAtmObject) = (TAtmosphericObject*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3888 "parser.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1391 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptAtmObject) = (TAtmosphericObject*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3896 "parser.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1395 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "AtmConst");
			  }
#line 3904 "parser.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1399 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptAtmObject) = (TAtmosphericObject*) _tDataStack.POP();
			  }
#line 3912 "parser.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1405 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Box");
			  }
#line 3920 "parser.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1409 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TBox*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3928 "parser.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1415 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TBox*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3936 "parser.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1419 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Box");
			  }
#line 3944 "parser.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1423 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TBox*) _tDataStack.POP();
			  }
#line 3952 "parser.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1429 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Cylinder");
			  }
#line 3960 "parser.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1433 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TCylinder*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 3968 "parser.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1439 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TCylinder*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 3976 "parser.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1443 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Cylinder");
			  }
#line 3984 "parser.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1447 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TCylinder*) _tDataStack.POP();
			  }
#line 3992 "parser.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1453 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Cone");
			  }
#line 4000 "parser.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1457 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TCone*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 4008 "parser.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1463 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TCone*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 4016 "parser.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1467 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Cone");
			  }
#line 4024 "parser.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1471 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TCone*) _tDataStack.POP();
	       		  }
#line 4032 "parser.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1477 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Torus");
			  }
#line 4040 "parser.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1481 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TTorus*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 4048 "parser.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1487 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TTorus*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 4056 "parser.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1491 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Torus");
			  }
#line 4064 "parser.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1495 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TTorus*) _tDataStack.POP();
			  }
#line 4072 "parser.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1501 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Mesh");
			  }
#line 4080 "parser.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1505 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TMeshObject*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 4088 "parser.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1511 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TMeshObject*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 4096 "parser.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1515 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Mesh");
			  }
#line 4104 "parser.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1519 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TMeshObject*) _tDataStack.POP();
			  }
#line 4112 "parser.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1529 "parser.y" /* yacc.c:1646  */
    {
			    MESH->addTriangle ((TTriangle*) (yyvsp[0].ptObject));
                            delete (yyvsp[0].ptObject);
			  }
#line 4121 "parser.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1537 "parser.y" /* yacc.c:1646  */
    {
			    DefineObject ((yyvsp[-1].acIdent), (yyvsp[0].acIdent), "Csg");
			  }
#line 4129 "parser.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1541 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TCsg*) UpdateObject ((yyvsp[-5].acIdent));
			  }
#line 4137 "parser.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1547 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TCsg*) InstanceObject ((yyvsp[0].acIdent));
			  }
#line 4145 "parser.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1551 "parser.y" /* yacc.c:1646  */
    {
			    CreateObject ((yyvsp[0].acIdent), "Csg");
			  }
#line 4153 "parser.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1555 "parser.y" /* yacc.c:1646  */
    {
			    (yyval.ptObject) = (TCsg*) _tDataStack.POP();
			  }
#line 4161 "parser.c" /* yacc.c:1646  */
    break;


#line 4165 "parser.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1614 "parser.y" /* yacc.c:1906  */


void rt_error (const char* pkcTEXT)
{

  cerr << endl << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Error: " << pkcTEXT << endl;

}  /* rt_error() */

void rt_error (const string& rksTEXT)
{

  cerr << endl << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Error: " << rksTEXT << endl;

}  /* rt_error() */


void RT_InitParser (void)
{

  InitObjects();
  InitFunctions();

  _tColorMap.clear();
  _tVectorMap.clear();
  _tTypeMap.clear();  
  while(!_tDataStack.empty()) _tDataStack.pop();

  _ptWorld = new TAggregate();
  
  TSceneRT::_ptParsedScene->setWorld (_ptWorld);
  
}  /* RT_InitParser() */


void RT_CloseParser (void)
{

  _tObjectMap.clear();

}  /* RT_CloseParser() */


void InitFunctions (void)
{
  _tFunctionMap.clear();
  _tFunctionMap ["rand"] = (double(*)(void)) &frand;
}  /* InitFunctions() */


void InitObjects (void)
{
  _tObjectMap.clear();
}  /* InitObjects() */


TProcedural* NewObject (const string& rktCLASS, const TProcedural* pktPARENT)
{

  TProcedural*   ptChild;

  //  cout << "New object : \"" << rktCLASS << "\"" << endl;

  ptChild = (TProcedural*) TClassManager::_newObject (rktCLASS, pktPARENT);
  if ( !ptChild )
  {
    string   tMessage = string ("class ") + rktCLASS + " does not exist";
    yyerror (tMessage.c_str());
    exit (1);
  }

  return ptChild;

}  /* NewObject() */


void* InstanceObject (const string& rktNAME)
{

  void*   pvObject;

  if ( rktNAME == "" )
  {
    yyerror ("instanced object cannot be unnamed");
    exit (1);
  }

  if ( _tObjectMap.find (rktNAME) == _tObjectMap.end() )
  {
    yyerror ("object does not exist");
    exit (1);
  }

  pvObject = _tObjectMap [rktNAME];

  return pvObject;

}  /* InstanceObject() */


void* UpdateObject (const string& rktNAME)
{

  TProcedural*   ptObject;

  // cout << "Updating object : \"" << rktNAME << "\"" << endl;

  ptObject = _tDataStack.POP();

  _tObjectMap [rktNAME] = ptObject;
  _tTypeMap   [rktNAME] = ptObject->classType();

  return ptObject;

}  /* UpdateObject() */


void DefineObject (const string& rktNAME, const string& rktCLASS, const string& rktDEF_CLASS)
{

  // cout << "Defining object : \"" << rktNAME << "\", \"" << rktCLASS << "\", \"" << rktDEF_CLASS << "\"" << endl;

  if ( rktNAME == "" )
  {
    yyerror ("defined object cannot be unnamed");
    exit (1);
  }

  if ( _tTypeMap.find (rktNAME) != _tTypeMap.end() )
  {
    yyerror ("cannot redefine an existing object");
    exit (1);
  }

  if ( ( _tObjectMap.find (rktNAME) != _tObjectMap.end() ) ||
       ( _tTypeMap  .find (rktNAME) != _tTypeMap.  end() ) )
  {
    yyerror ("cannot redefine an existing object");
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

  // cout << "Creating object : \"" << rktCLASS << "\", \"" << rktDEF_CLASS << "\"" << endl;
  
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


void DefineColor (const string& rktNAME)
{

  if ( rktNAME == "" )
  {
    yyerror ("cannot define unnamed color");
    exit (1);
  }

  if ( _tColorMap.find (rktNAME) != _tColorMap.end() )
  {
    yyerror ("cannot redefine an existing color");
    exit (1);
  }

  if ( _tTypeMap.find (rktNAME) != _tTypeMap.end() )
  {
    yyerror ("cannot redefine an existing object");
    exit (1);
  }

  _tColor = TColor::_black();
  
  _ptParent = NULL;

}  /* DefineColor() */


TColor* InstanceColor (const string& rktNAME)
{

  TColor*   ptColor;

  if ( rktNAME == "" )
  {
    yyerror ("instanced object cannot be unnamed");
    exit (1);
  }
  
  if ( _tColorMap.find (rktNAME) == _tColorMap.end() )
  {
    yyerror ("pattern/color does not exist");
    exit (1);
  }
  
  ptColor = (TColor*) &(_tColorMap [rktNAME]);
  
  return ptColor;

}  /* InstanceColor() */


void DefineVector (const string& rktNAME)
{

  if ( rktNAME == "" )
  {
    yyerror ("cannot define unnamed vector");
    exit (1);
  }
  
  if ( _tVectorMap.find (rktNAME) != _tVectorMap.end() )
  {
    yyerror ("cannot redefine an existing vector");
    exit (1);
  }

  if ( _tTypeMap.find (rktNAME) != _tTypeMap.end() )
  {
    yyerror ("cannot redefine an existing object");
    exit (1);
  }
  
  _tVector = TVector (0, 0, 0);
  
  _ptParent = NULL;

}  /* DefineVector() */


TVector* InstanceVector (const string& rktNAME)
{

  TVector*   ptVector;

  if ( rktNAME == "" )
  {
    yyerror ("instanced object cannot be unnamed");
    exit (1);
  }
  
  if ( _tVectorMap.find (rktNAME) == _tVectorMap.end() )
  {
    yyerror ("vector does not exist");
    exit (1);
  }
  
  ptVector = (TVector*) &(_tVectorMap [rktNAME]);
  
  return ptVector;

}  /* InstanceVector() */


EAttribType MapClassToAttribute (const TBaseClass* pktClass)
{

  EClass   eIdentifierClass = pktClass->classType();

  switch (eIdentifierClass) 
  {
    case FX_PATTERN_CLASS:
      return FX_PATTERN;

    case FX_PERTURBATION_CLASS:
      return FX_PERTURBATION;

    default:
      return FX_NONE;
  }

}  /* MapClassToAttribute() */


void UpdateAttribute (const string& rktATTRIBUTE, const string& rktIDENT)
{

  EClass        eIdentifierClass = _tTypeMap [rktIDENT];
  EAttribType   eAttribute;
  void*         vpInstance;
  
  switch (eIdentifierClass) 
  {
    case FX_COLOR_CLASS:
      vpInstance = InstanceColor (rktIDENT);
      eAttribute = FX_COLOR;
      break;

    case FX_VECTOR_CLASS:
      vpInstance = InstanceVector (rktIDENT);
      eAttribute = FX_VECTOR;
      break;
      
    case FX_BSDF_CLASS:
      vpInstance = InstanceObject (rktIDENT);
      eAttribute = FX_BSDF;
      break;

    case FX_PATTERN_CLASS:
      vpInstance = InstanceObject (rktIDENT);
      eAttribute = FX_PATTERN;
      break;

    case FX_PERTURBATION_CLASS:
      vpInstance = InstanceObject (rktIDENT);
      eAttribute = FX_PERTURBATION;
      break;

    default:
      vpInstance = NULL;
      eAttribute = FX_NONE;

      cerr << "Warning: identifier class not recognized." << endl;
  }
  
  _nAttrib.pvValue = vpInstance;
  SetParameter (rktATTRIBUTE, eAttribute);
  
}  /* UpdateAttribute() */


void SetParameter (const string& rktATTRIB, EAttribType eTYPE)
{

  int   iResult;

  iResult = DATA->setAttribute (rktATTRIB, _nAttrib, eTYPE);

  if ( iResult == FX_ATTRIB_WRONG_PARAM )
  {
    yyerror ("object does not have such attribute");
    exit (1);
  }
  else if ( iResult == FX_ATTRIB_WRONG_TYPE )
  {
    yyerror ("incorrect type in attribute value");
    exit (1);
  }
  else if ( iResult == FX_ATTRIB_WRONG_VALUE )
  {
    yyerror ("value not accepted for this attribute");
    exit (1);
  }
  else if ( iResult == FX_ATTRIB_USER_ERROR )
  {
    yyerror (TProcedural::_tUserErrorMessage.c_str());
    exit (1);
  }

}  /* SetParameter() */


string EAttribType_to_str (EAttribType eTYPE)
{

  /* This function is pretty dumb, but I (KH) couldn't find another one
     anywhere else.  Added on 07Aug2000  */ 

  switch ( eTYPE )
  {
    case FX_NONE: 
      return "none";

    case FX_REAL: 
      return "real";

    case FX_BOOL: 
      return "bool";

    case FX_STRING: 
      return "string";

    case FX_COLOR: 
      return "color";

    case FX_VECTOR: 
      return "vector";

    case FX_VECTOR2: 
      return "2d_vector";

    case FX_IMAGE: 
      return "image";

    case FX_BSDF: 
      return "bsdf";

    case FX_CAMERA: 
      return "camera";

    case FX_LIGHT: 
      return "light";

    case FX_MATERIAL: 
      return "material";

    case FX_PATTERN: 
      return "pattern";

    case FX_PERTURBATION: 
      return "perturbation";

    case FX_RENDERER: 
      return "renderer";

    case FX_OBJECT: 
      return "object";

    case FX_OBJECT_FILTER: 
      return "object_filter";

    case FX_IMAGE_FILTER: 
      return "image_filter";

    default: 
      return "unknown";
  }

}  /* EAttribType_to_str() */

/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
#line 94 "parser.y" /* yacc.c:1909  */

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
       

#line 187 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE rt_lval;

int rt_parse (void);

#endif /* !YY_RT_PARSER_H_INCLUDED  */

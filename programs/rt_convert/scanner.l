/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  Copyright (C) 2002 Kevin Harris
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

#include <string>
#include <iostream>
#include "parser_defs.h"
#include "parser.h"

#undef yywrap

#if BROKEN_FILENO_INCLUDE
/* Under IRIX 6.5, fileno does not get defined using g++, which does not
   provide a C library; it assumes one will be provided by the OS, 
   or some 3rd party. 
 */
extern "C" {
   /* The C89, C99, and C++98 standards allow any standard C function to be
    * masked by a macro.
    * The Freebsd libc is one of many which define such a macro.
    * The right fix would be to make autoconf detect the lack of a fileno
    * declaration.
    * [LLeweLLyn Reese 20Nov2002]
    */
#undef fileno  
  extern int fileno(FILE *);
}
#endif

// Macro to allow reserved words to be returned with their actual text.  This
// is useful for words that are considered reserved words but may be needed as
// strings at some point in the parser.
#define RESERVED(x)                 \
{                                   \
  rt_conv_lval = string(yytext,yyleng);  \
  return x;                           \
} 
//"/*".*"*/"		//RESERVED(T_VERBATIM);

 
%}

alpha			[a-zA-Z]
digit			[0-9]
identifier		[a-zA-Z_][a-zA-Z0-9_]*
horizontal_space	[ \t\r]
quoted_string		\"[^\"]*\"
line_comment		"//".*\n
include_line		"#include".*\n
natural			{digit}+
integer			[+-]?{digit}+
exponent		[eE]{integer}
float			({integer}|{integer}?"."{natural}?)
real			{float}({exponent})?

%%


{include_line}		{ RESERVED(T_VERBATIM); } 
aggregate               RESERVED (T_AGGREGATE);
atm_object              RESERVED (T_ATM_OBJECT);
blue			RESERVED (T_BLUE);
box			RESERVED (T_BOX);
bsdf			RESERVED (T_BSDF);
camera			RESERVED (T_CAMERA);
circle			RESERVED (T_CIRCLE);
class			RESERVED (T_CLASS);
color			RESERVED (T_COLOR);
colour			RESERVED (T_COLOR);
cone                    RESERVED (T_CONE);
cylinder		RESERVED (T_CYLINDER);
define			RESERVED (T_DEFINE);
difference              RESERVED (T_DIFFERENCE);
extends			RESERVED (T_EXTENDS);
filter			RESERVED (T_FILTER);
green			RESERVED (T_GREEN);
image_filter            RESERVED (T_IMAGE_FILTER);
intersection            RESERVED (T_INTERSECTION);
light			RESERVED (T_LIGHT);
material		RESERVED (T_MATERIAL);
mesh			RESERVED (T_MESH);
object			RESERVED (T_OBJECT);
object_filter           RESERVED (T_OBJECT_FILTER);
output                  RESERVED (T_OUTPUT);
pattern                 RESERVED (T_PATTERN);
perturbation            RESERVED (T_PERTURBATION);
phong_triangle		RESERVED (T_PHONG_TRIANGLE);
plane			RESERVED (T_PLANE);
rectangle		RESERVED (T_RECTANGLE);
red			RESERVED (T_RED);
renderer		RESERVED (T_RENDERER);
rotate			RESERVED (T_ROTATE);
scale                   RESERVED (T_SCALE);
scene			RESERVED (T_SCENE);
sphere			RESERVED (T_SPHERE);
torus                   RESERVED (T_TORUS);
translate		RESERVED (T_TRANSLATE);
triangle		RESERVED (T_TRIANGLE);
type			RESERVED (T_TYPE);
union                   RESERVED (T_UNION);
vector			RESERVED (T_VECTOR);
vertex			RESERVED (T_VERTEX);
x                       RESERVED (T_X);
y                       RESERVED (T_Y);
z                       RESERVED (T_Z);
"halt()"                RESERVED(T_VERBATIM);

on			RESERVED(T_BOOL);
off                     RESERVED(T_BOOL);
true                    RESERVED(T_BOOL);
false                   RESERVED(T_BOOL);

"//"		        {
                          // This is much safer than the old rule:
                          // "//".*\n     TSceneRT::_dwLineNumber++;
                          // It now should act in the proper manner when the
                          // file ends within a line comment. 
                          int c;
			  for( c = yyinput();
			       (c != EOF) && (c != '\n');
			       c = yyinput() )
			  {
			    // Eat up the whole line of comments
			  }
			  if( c == EOF )
			  {
			    rt_conv_error("end of file within single line comment");
			    // Put the char back, so that the end of file can
			    // be matched correctly.
			    unput(c);
			  }
			  else
			  {
			    ++line_number;
			  };
                        }

{horizontal_space}	;

\n			++line_number;

{identifier}		RESERVED(T_IDENTIFIER); 

"/*" {
  int    iChar;
  bool   gEnd = false;

  iChar = yyinput();
  while ( !gEnd )
  {
    while ( iChar != '*' )
    {
      if ( iChar == EOF )
      {
	rt_conv_error ("EOF found inside multiline comment");
	exit (1);
      }
      if ( iChar == '\n' )
      {
        ++line_number;
      }
      iChar = yyinput();
    }
    iChar = yyinput();
    if ( iChar == '/' )
    {
      gEnd = true;
    }
  }
}

{real}			RESERVED(T_REAL);

{quoted_string}		RESERVED(T_QUOTED_STRING);

.			return yytext[0];

<<EOF>>			yyterminate();

%%

int yywrap (void)
{

  return 1;

}  /* yywrap() */

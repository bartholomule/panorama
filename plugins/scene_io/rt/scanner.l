/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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
#include "llapi/llapi_all.h"
#include "hlapi/mesh_object.h"
#include "parser_defs.h"
#include "rt_io.h"
#include "parser.h"

#undef yywrap

//
//  Prototypes
//
void DeleteComments (void);
bool ProcessInclude (void);
bool IncludeFile (void);

//
//  Types
//
struct TIncludeFileData
{

  string            tFileName;
  DWord             dwLineNumber;
  DWord             dwFilePos;
  YY_BUFFER_STATE   yyBuffer;

};  /* struct TIncludeFileData */

//
//  Global variables
//
static string             _tIncludeFileName;
static TIncludeFileData   _tIncludeFileData;
static TIncludeFileData   _atIncludeStack [MAX_INCLUDE_DEPTH];
static Byte               _bIncludeLevel = 0;

%}

alpha			[a-zA-Z]
digit			[0-9]
identifier		[a-zA-Z_][a-zA-Z0-9_]*
horizontal_space	[ \t]
quoted_string		\"[^\"]*\"
line_comment		"//".*\n
natural			{digit}+
integer			[+-]?{digit}+
exponent		[eE]{integer}
float			({integer}|{integer}?"."{natural}?)
real			{float}({exponent})?

%%

aggregate               return T_AGGREGATE;
atm_object              return T_ATM_OBJECT;
blue			return T_BLUE;
box			return T_BOX;
bsdf			return T_BSDF;
camera			return T_CAMERA;
circle			return T_CIRCLE;
class			return T_CLASS;
color			return T_COLOR;
cone                    return T_CONE;
cylinder		return T_CYLINDER;
define			return T_DEFINE;
difference              return T_DIFFERENCE;
extends			return T_EXTENDS;
filter			return T_FILTER;
green			return T_GREEN;
image_filter            return T_IMAGE_FILTER;
intersection            return T_INTERSECTION;
light			return T_LIGHT;
material		return T_MATERIAL;
mesh			return T_MESH;
object			return T_OBJECT;
object_filter           return T_OBJECT_FILTER;
output                  return T_OUTPUT;
phong_triangle		return T_PHONG_TRIANGLE;
plane			return T_PLANE;
rectangle		return T_RECTANGLE;
red			return T_RED;
renderer		return T_RENDERER;
rotate			return T_ROTATE;
scale                   return T_SCALE;
scene			return T_SCENE;
sphere			return T_SPHERE;
torus                   return T_TORUS;
translate		return T_TRANSLATE;
triangle		return T_TRIANGLE;
type			return T_TYPE;
union                   return T_UNION;
vertex			return T_VERTEX;

on			{
			  yylval.gValue = true;
			  return T_BOOL;
			}
 
off			{
			  yylval.gValue = false;
			  return T_BOOL;
			}

{line_comment}		TSceneRT::_dwLineNumber++;

{horizontal_space}	;

\n			TSceneRT::_dwLineNumber++;

{identifier}		{
			  strcpy (yylval.acIdent, yytext);
			  yylval.acIdent [MAX_IDENTIFIER] = 0;
			  return T_IDENTIFIER;
			}

"/*"			{
			  DeleteComments();
			}

#include		ProcessInclude();

{real}			{
			  yylval.dValue = atof (yytext);
			  return T_REAL;
			}

{quoted_string}		{
			  strncpy (yylval.acIdent, yytext + 1, yyleng - 2);
			  yylval.acIdent [yyleng - 2] = 0;
			  return T_QUOTED_STRING;
			}

.			return yytext[0];

<<EOF>>			{
			  if ( _bIncludeLevel == 0 )
			  {
			    yyterminate();
			  }
			  else
			  {
			    _bIncludeLevel--;
			    yy_delete_buffer (YY_CURRENT_BUFFER);
			    _tIncludeFileData         = _atIncludeStack [_bIncludeLevel];
			    TSceneRT::_tInputFileName = _tIncludeFileData.tFileName;
//			    cout << "Returning to file : " << TSceneRT::_tInputFileName << endl;
			    TSceneRT::_dwLineNumber = _tIncludeFileData.dwLineNumber;
			    yy_switch_to_buffer (_tIncludeFileData.yyBuffer);
			  }
			}

%%

int yywrap (void)
{

  return 1;

}  /* yywrap() */


void DeleteComments (void)
{

  int    iChar;
  bool   gEnd = false;

  iChar = yyinput();
  while ( !gEnd )
  {
    while ( iChar != '*' )
    {
      if ( iChar == EOF )
      {
	yyerror ("EOF found inside multiline comment");
	exit (1);
      }
      if ( iChar == '\n' )
      {
        TSceneRT::_dwLineNumber++;
      }
      iChar = yyinput();
    }
    iChar = yyinput();
    if ( iChar == '/' )
    {
      gEnd = true;
    }
  }

}  /* DeleteComments() */


bool ProcessInclude (void)
{

  int   iChar;

  do
  {
    iChar = yyinput();
  } while ( (iChar == ' ') || (iChar == '\t') );

  if ( iChar != '"' )
  {
    yyerror ("'\"' expected");
    exit (1);
  }
  else
  {
    iChar             = yyinput();
    _tIncludeFileName = "";
    while ( iChar != '"' )
    {
      if ( (iChar == '\n') || (iChar == EOF) )
      {
        yyerror ("'\"' expected");
        exit (1);
      }
      _tIncludeFileName += char (iChar);
      iChar = yyinput();
    }
   }
   return IncludeFile();

}  /* ProcessInclude() */


bool IncludeFile (void)
{

  _tIncludeFileData.tFileName    = TSceneRT::_tInputFileName;
  _tIncludeFileData.dwLineNumber = TSceneRT::_dwLineNumber;
  _tIncludeFileData.dwFilePos    = ftell (yyin);
  _tIncludeFileData.yyBuffer     = YY_CURRENT_BUFFER;
  if ( _bIncludeLevel == MAX_INCLUDE_DEPTH )
  {
    yyerror ("Maximum include level reached");
    exit (1);
  }
  else
  {
    _atIncludeStack [_bIncludeLevel++] = _tIncludeFileData;
  }
  yyin = fopen (_tIncludeFileName.c_str(), "r");
  if ( !yyin )
  {
    string   tString = TScene::_tIncludePath + _tIncludeFileName;
    yyin    = fopen (tString.c_str(), "r");
    if ( !yyin )
    {
      yyerror ("Include file could not be opened");
      exit (1);
    }
  }
  TSceneRT::_tInputFileName = _tIncludeFileName;
  TSceneRT::_dwLineNumber   = 1L;
  yy_switch_to_buffer (yy_create_buffer (yyin, YY_BUF_SIZE));

//  cout << "Including file : " << TSceneRT::tInputFileName << endl;

  return true;

}  /* IncludeFile() */

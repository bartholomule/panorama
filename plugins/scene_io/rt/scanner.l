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

#if BROKEN_FILENO_INCLUDE
/* Under IRIX 6.5, fileno does not get defined using g++ */
extern "C" {
  extern int fileno(FILE *);
}
#endif

extern multimap<string, string>   tConfigData;

//
//  Prototypes
//
static void DeleteComments (void);
static bool ProcessInclude (void);
static bool IncludeFile (void);

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

// Macro to allow reserved words to be returned with their actual text.  This
// is useful for words that are considered reserved words but may be needed as
// strings at some point in the parser.
#define RESERVED(x)                 \
{                                   \
  strcpy (rt_lval.acIdent, yytext); \
  rt_lval.acIdent [yyleng] = '\0';  \
  return x;                         \
} 
 
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

aggregate               RESERVED (T_AGGREGATE);
atm_object              RESERVED (T_ATM_OBJECT);
attribute_list          RESERVED (T_ATTR_LIST);
attribute_type          RESERVED (T_ATTR_TYPE);
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
"halt()"                {
                          /* This simple rule is an easy way to get panorama to
			     terminate before any expensive calculations are
			     performed.  This may be useful for checking the
			     syntax of a source file and terminating before any
			     work is done on it.
			  */ 
                          cout << "Terminating due to halt request on line "
			       << TSceneRT::_dwLineNumber
			       << "."
			       << endl;
			  exit(1);
                        }

on			{
			  rt_lval.gValue = true;
			  return T_BOOL;
			}
 
off			{
			  rt_lval.gValue = false;
			  return T_BOOL;
			}

{line_comment}		TSceneRT::_dwLineNumber++;

{horizontal_space}	;

\n			TSceneRT::_dwLineNumber++;

{identifier}		{
			  strcpy (rt_lval.acIdent, yytext);
			  rt_lval.acIdent [MAX_IDENTIFIER] = 0;
			  return T_IDENTIFIER;
			}

"/*"			{
			  DeleteComments();
			}

#include		ProcessInclude();

{real}			{
			  rt_lval.dValue = atof (yytext);
			  return T_REAL;
			}

{quoted_string}		{
			  strncpy (rt_lval.acIdent, yytext + 1, yyleng - 2);
			  rt_lval.acIdent [yyleng - 2] = 0;
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
	rt_error ("EOF found inside multiline comment");
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
    rt_error ("'\"' expected");
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
        rt_error ("'\"' expected");
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
    rt_error ("Maximum include level reached");
    exit (1);
  }
  else
  {
    _atIncludeStack [_bIncludeLevel++] = _tIncludeFileData;
  }

  yyin = fopen (_tIncludeFileName.c_str(), "r");

  if ( !yyin )
  {
    if ( _tIncludeFileName[0] != '/' )
    {
      multimap<string, string>::const_iterator   iter;

      iter = tConfigData.find ("IncludePath");
      while ( ( iter != tConfigData.end() ) && ( (*iter).first == "IncludePath" ) )
      {
        string   tAux = (*iter).second + "/" + _tIncludeFileName;
        
        if ( FileExists (tAux) )
        {
          yyin = fopen (tAux.c_str(), "r");
          break;
        }
        iter++;
      }
    }
  }

  if ( !yyin )
  {
    rt_error ("Include file could not be opened");
    exit (1);
  }

  TSceneRT::_tInputFileName = _tIncludeFileName;
  TSceneRT::_dwLineNumber   = 1L;
  yy_switch_to_buffer (yy_create_buffer (yyin, YY_BUF_SIZE));

//  cout << "Including file : " << TSceneRT::tInputFileName << endl;

  return true;

}  /* IncludeFile() */

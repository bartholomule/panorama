/*
*  Copyright (C) 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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
#include <iostream.h>
#include "llapi/file.h"
#include "parser_defs.h"
#include "psl_io.h"
#include "parser.h"

#undef yywrap

extern multimap<string, string>   tConfigData;

//
//  Prototypes
//
static int ComplexType (void);
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
//  Static variables
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
float			({integer}"."?|{integer}"."{natural}|"."{natural})
real			{float}({exponent})?

%%

define			return T_DEFINE;
class			return T_CLASS;
extends			return T_EXTENDS;
new			return T_NEW;

Real                    return T_TYPE_REAL;
Bool                    return T_TYPE_BOOL;
String                  return T_TYPE_STRING;
Color                   return T_TYPE_COLOR;
Vector                  return T_TYPE_VECTOR;
Vector2                 return T_TYPE_VECTOR2;

Image                   return T_TYPE_IMAGE;
Scene                   return T_TYPE_SCENE;

Bsdf                    return ComplexType();
Camera                  return ComplexType();
Light                   return ComplexType();
Material                return ComplexType();
Renderer                return ComplexType();
Object                  return ComplexType();
Aggregate               return ComplexType();
ObjectFilter            return ComplexType();
ImageFilter             return ComplexType();

true                    {
                          psl_lval.gValue = true;
                          return T_BOOL;
                        }
                        
false                   {
                          psl_lval.gValue = false;
                          return T_BOOL;
                        }
                        
{line_comment}		TScenePsl::_dwLineNumber++;

{horizontal_space}	;

\n			TScenePsl::_dwLineNumber++;

{identifier}		{
			  strcpy (psl_lval.acString, yytext);
			  psl_lval.acString [MAX_IDENTIFIER] = 0;
			  return T_IDENTIFIER;
			}

"/*"			{
			  DeleteComments();
			}

#include		ProcessInclude();

{real}			{
			  psl_lval.dValue = atof (yytext);
			  return T_REAL;
			}

{quoted_string}		{
			  strncpy (psl_lval.acString, yytext + 1, yyleng - 2);
			  psl_lval.acString [yyleng - 2] = 0;
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
	       		    _tIncludeFileData           = _atIncludeStack [_bIncludeLevel];
			    TScenePsl::_tInputFileName = _tIncludeFileData.tFileName;
//			    cout << "Returning to file : " << TScenePsl::_tInputFileName << endl;
			    TScenePsl::_dwLineNumber = _tIncludeFileData.dwLineNumber;
			    yy_switch_to_buffer (_tIncludeFileData.yyBuffer);
			  }
			}

%%

int yywrap (void)
{

  return 1;

}  /* yywrap() */


int ComplexType (void)
{

  strcpy (psl_lval.acString, yytext);
  psl_lval.acString [MAX_IDENTIFIER] = 0;

  return T_COMPLEX_TYPE;

}  /* ComplexType() */


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
	psl_error ("EOF found inside multiline comment");
	exit (1);
      }
      if ( iChar == '\n' )
      {
        TScenePsl::_dwLineNumber++;
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
    psl_error ("'\"' expected");
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
        psl_error ("'\"' expected");
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

  _tIncludeFileData.tFileName    = TScenePsl::_tInputFileName;
  _tIncludeFileData.dwLineNumber = TScenePsl::_dwLineNumber;
  _tIncludeFileData.dwFilePos    = ftell (yyin);
  _tIncludeFileData.yyBuffer     = YY_CURRENT_BUFFER;
  if ( _bIncludeLevel == MAX_INCLUDE_DEPTH )
  {
    psl_error ("Maximum include level reached");
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
    psl_error ("Include file could not be opened");
    exit (1);
  }

  TScenePsl::_tInputFileName = _tIncludeFileName;
  TScenePsl::_dwLineNumber   = 1L;
  yy_switch_to_buffer (yy_create_buffer (yyin, YY_BUF_SIZE));

//  cout << "Including file : " << TScenePsl::_tInputFileName << endl;

  return true;

}  /* IncludeFile() */

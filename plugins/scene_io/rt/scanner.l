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
#include "parsed_types.h"
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

using std::multimap;
using std::string;
 
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
  rt_lval.sIdent.assign(yytext, yyleng); \
/*  cout << "scanner returning: \"" << rt_lval.sIdent << "\"" << endl; */ \
  return x;                         \
} 
 
%}

alpha			[a-zA-Z]
digit			[0-9]
identifier		[a-zA-Z_][a-zA-Z0-9_]*
horizontal_space	[ \t\r]
quoted_string		\"[^\"]*\"
line_comment		"//".*\n
natural			{digit}+
integer			[+-]?{digit}+
exponent		[eE]{integer}
float			{integer}?"."{natural}?
real			{float}({exponent})?

%%

"<="                    RESERVED (LESS_EQ);
">="                    RESERVED (GREATER_EQ);
"=="                    RESERVED (EQUAL);
"!="                    RESERVED (NOT_EQ);
blue			RESERVED (T_BLUE);
class			RESERVED (T_CLASS);
define			RESERVED (T_DEFINE);
difference              RESERVED (T_DIFFERENCE);
extends			RESERVED (T_EXTENDS);
filter			RESERVED (T_FILTER);
green			RESERVED (T_GREEN);
intersection            RESERVED (T_INTERSECTION);
light			RESERVED (T_LIGHT);
output                  RESERVED (T_OUTPUT);
red			RESERVED (T_RED);
renderer		RESERVED (T_RENDERER);
this                    RESERVED (THIS);
union                   RESERVED (T_UNION);

on			{
			  rt_lval.gValue = true;
			  return T_BOOL;
			}
 
off			{
			  rt_lval.gValue = false;
			  return T_BOOL;
			}

true			{
			  rt_lval.gValue = true;
			  return T_BOOL;
			}
 
false			{
			  rt_lval.gValue = false;
			  return T_BOOL;
			}

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
			    rt_warning("end of file within single line comment");
			    // Put the char back, so that the end of file can
			    // be matched correctly.
			    unput(c);
			  }
			  else
			  {
			    TSceneRT::_dwLineNumber++;
			  };
                        }

{horizontal_space}	;

\n			TSceneRT::_dwLineNumber++;

{identifier}		{
                          rt_lval.sIdent.assign(yytext, yyleng);
			  /*			  cout << "scanner returning: \"" << rt_lval.sIdent << "\"" << endl; */
			  return T_IDENTIFIER;
			}

"/*"			{
			  DeleteComments();
			}

#include		ProcessInclude();

{integer}		{
			  rt_lval.iValue = atoi (yytext);
			  return T_INTEGER;
			}

{real}			{
			  rt_lval.dValue = atof (yytext);
			  return T_REAL;
			}

{quoted_string}		{
                          rt_lval.sIdent.assign(yytext+1, yyleng-2);
			  /*			  cout << "scanner returning: \"" << rt_lval.sIdent << "\"" << endl;			   */
			  return T_QUOTED_STRING;
			}

.			/* cout << "scanner returning: '" << yytext[0] << "'" << endl; */ return yytext[0];

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

  string name = FilenameConvert(_tIncludeFileName);
  // cout << "Attempting to open \"" + name + "\" for include" << endl;

  yyin = fopen (name.c_str(), "r");

  if ( !yyin )
  {
    if ( FilenameConvert(_tIncludeFileName)[0] != FilenameConvert("/")[0] )
    {
      multimap<string, string>::const_iterator   iter;

      iter = tConfigData.find ("IncludePath");
      while ( ( iter != tConfigData.end() ) && ( (*iter).first == "IncludePath" ) )
      {
	    string   tAux = FilenameConvert((*iter).second + "/" + _tIncludeFileName);
        
        if ( FileExists (tAux) )
        {
          yyin = fopen (tAux.c_str(), "r");
          break;
        }
		else
		{
		  rt_error("Include file \"" + tAux + "\" could not be opened!");
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


void scanner_unput_string(const string& s)
{
  // Unput the current yytext...
  string old_text = string(yytext,yyleng);
  string new_text = s;// + old_text;

  for(int i = new_text.length() - 1;
      i >= 0;
      --i)
  {
    unput(new_text[i]);
  }
  cout << "Scanner: Just unput: \"" << new_text << "\"" << endl;

  YY_FLUSH_BUFFER;
  
  string trash_text = string(yytext,yyleng);
  cout << "  new yytext=\"" << trash_text << "\"" << endl;
}

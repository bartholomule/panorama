/*
*  Copyright (C) 2000 Kevin Harris
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
%x COMMENTED_REGION STRING_REGION
/* option c++ */
%option noyywrap
%{
  #include <cstdio>
  #include "dynamic_objects.h"
  #include "magic_pointer.h"
  #include "parser.h"
  
  // This section is temp
  //  #include <FlexLexer.h>
  //  yyFlexLexer* lexer = NULL;
  //  int yylex()
  //  {
  //    if(lexer == NULL)
  //      lexer = new yyFlexLexer();
  //    return(lexer->yylex());
  //  }
  #include <stdio.h>
  extern FILE* yyin;
  // end of temp section
int scanner_line_number = 1;
  
  
#define RETURN_TRASH(id) { return id; }
  //#define RETURN_TRASH(id) { fprintf(stderr,"scanner: found token " #id " (%d -- '%c')\n",(id),((id) < 127)?(id):0); return id; }
%}

whitespace [ \t]
letter [A-Za-z]
digit [0-9]

integer {digit}+
floating   {integer}|{integer}[\.]{integer}
identifier [A-Za-z_][A-Za-z0-9_]*

%%

<INITIAL>
{
  {floating} {
    char buffer[1024];
    memcpy(buffer, yytext, yyleng);
    double value;
    sscanf(buffer,"%lf",&value);
    yylval = new Tdynamic_real(value);
    RETURN_TRASH(CONSTANT);
  }
  "include"  { yylval = NULL; RETURN_TRASH(INCLUDE); }
  "if"       { yylval = NULL; RETURN_TRASH(IF); }
  "else"     { yylval = NULL; RETURN_TRASH(ELSE); }
  "defined"  { yylval = NULL; RETURN_TRASH(DEFINED); }
  "define"   { yylval = NULL; RETURN_TRASH(DEFINE); }  
  "object"   { yylval = NULL; RETURN_TRASH(OBJECT); }
  "scene"    { yylval = NULL; RETURN_TRASH(SCENE); }
  "warning"  { yylval = NULL; RETURN_TRASH(WARNING); }
  "error"    { yylval = NULL; RETURN_TRASH(ERROR); }
  "param"    { yylval = NULL; RETURN_TRASH(PARAM); }
  "env"      { yylval = NULL; RETURN_TRASH(ENV); }
  "print"    { yylval = NULL; RETURN_TRASH(PRINT); }
  "type"     { yylval = NULL; RETURN_TRASH(TYPE); }
  "attribs"  { yylval = NULL; RETURN_TRASH(ATTRIBS); }
  "this"     { yylval = NULL; RETURN_TRASH(THIS); }
  "parent"   { yylval = NULL; RETURN_TRASH(PARENT); }
  "global"   { yylval = NULL; RETURN_TRASH(GLOBAL); }
  "+"        { yylval = NULL; RETURN_TRASH(PLUS); }
  "-"        { yylval = NULL; RETURN_TRASH(MINUS); }
  "*"        { yylval = NULL; RETURN_TRASH(TIMES); }
  "/"        { yylval = NULL; RETURN_TRASH(DIV); }
  "+="       { yylval = NULL; RETURN_TRASH(PLUS_EQ); }
  "-="       { yylval = NULL; RETURN_TRASH(MINUS_EQ); }
  "*="       { yylval = NULL; RETURN_TRASH(TIMES_EQ); }
  "/="       { yylval = NULL; RETURN_TRASH(DIV_EQ); }
  "."        { yylval = NULL; RETURN_TRASH(DOT); }
  "&&"       { yylval = NULL; RETURN_TRASH(AND_L); }
  "||"       { yylval = NULL; RETURN_TRASH(OR_L); }
  "!"        { yylval = NULL; RETURN_TRASH(NOT); }
  "=="       { yylval = NULL; RETURN_TRASH(EQUAL); }
  "!="       { yylval = NULL; RETURN_TRASH(NOT_EQ); }
  ">="       { yylval = NULL; RETURN_TRASH(GREATER_EQ); }
  "<="       { yylval = NULL; RETURN_TRASH(LESS_EQ); }
  ">"        { yylval = NULL; RETURN_TRASH(GREATER); }
  "<"        { yylval = NULL; RETURN_TRASH(LESS); }
  "="        { yylval = NULL; RETURN_TRASH(ASSIGN); }
  "debug"    { yylval = NULL; RETURN_TRASH(DEBUG); }
  "/*"       { BEGIN(COMMENTED_REGION); }
  "\""       { yymore(); BEGIN(STRING_REGION); }
  {identifier} { yylval = new Tdynamic_string(string(yytext,yyleng)); RETURN_TRASH(TEXT); }
  {whitespace}
  \n         { ++scanner_line_number; }
  .          { RETURN_TRASH(*yytext);  /* Return all unknown characters to the parser */ }
}

<COMMENTED_REGION>
{
  "*/" { BEGIN(INITIAL); }
  .
  \n { ++scanner_line_number; }
    <<EOF>> %{
               fprintf(stderr,"scanner: line %d: EOF within comment.\n",scanner_line_number);
	       return 0;
	    %}
}

<STRING_REGION>
{
  "\"" %{
         BEGIN(INITIAL);
	 {
	   char buffer[1024];
	   int string_length = 0;
	   // 
	   // Copy the string (not including the quotes on either side) and
	   // convert commonly used escape sequences to their proper
	   // characters. 
	   // 
	   for(int i = 1; i < yyleng - 1; ++i)
	   {
	     if( yytext[i] != '\\' )
	     {
	       buffer[string_length++] = yytext[i];
	     }
	     else
	     {
	       switch(yytext[i+1])
	       {
	       case '\"':
	       case '\\':
		 buffer[string_length++] = yytext[++i];
		 break;
	       case 'n':
		 buffer[string_length++] = '\n'; ++i;
		 break;
	       case 'r':
		 buffer[string_length++] = '\r'; ++i;
		 break;
	       case 'a':
		 buffer[string_length++] = '\a'; ++i;
		 break;
	       case 't':
		 buffer[string_length++] = '\t'; ++i;
		 break;
	       case 'b':
		 buffer[string_length++] = '\b'; ++i;
		 break;
	       default:
		 printf("scanner: warning: Unknown escape sequence '\\%c'\n",yytext[i+1]);
		 buffer[string_length++] = yytext[i];
		 buffer[string_length++] = yytext[i+1];
		 ++i;
	       }
	     }	     
	   }
	   buffer[string_length++] = '\0';
	   yylval = new Tdynamic_string(string(buffer)); RETURN_TRASH(STRING);
	 }
       %}
  .    { yymore(); }
  \\.  { yymore(); }
  \\\n %{
           ++scanner_line_number;
           fprintf(stderr,"scanner: line %d: unterminated string.\n",scanner_line_number);
           return 0;
        %}        
  \n  %{
         ++scanner_line_number;
         fprintf(stderr,"scanner: line %d: unterminated string.\n",scanner_line_number);
         return 0;
      %}    
  <<EOF>> %{
             fprintf(stderr,"scanner: line %d: unterminated string.\n",scanner_line_number);
             return 0;
          %}
}


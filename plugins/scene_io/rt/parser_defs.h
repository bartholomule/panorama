/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _PARSER_DEFS__
#define _PARSER_DEFS__

#include <cstdio>
#include <string>

#define MAX_IDENTIFIER		31
#define MAX_INCLUDE_DEPTH	10

//
//  Extern variables
//
extern FILE*   rt_in;
extern FILE*   rt_out;
extern int     rt_debug;

//
//  Prototypes
//
void rt_error (const char* pkcTEXT);
void rt_error (const string& rksTEXT);
void rt_warning (const string& pkcTEXT); 
int rt_parse (void);
int rt_lex (void);
void RT_InitParser (void);
void RT_CloseParser (void);
void scanner_unput_string(const string& s);
  
#endif  /* _PARSER_DEFS__ */

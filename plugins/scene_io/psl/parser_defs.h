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

#ifndef _PARSER_DEFS__
#define _PARSER_DEFS__

#include <cstdio>
#include <string>

#define MAX_IDENTIFIER		31
#define MAX_INCLUDE_DEPTH	10

//
//  Extern variables
//
extern FILE*   psl_in;
extern FILE*   psl_out;
extern int     psl_debug;

//
//  Prototypes
//
void psl_error (const char* pkcTEXT);
int psl_parse (void);
int psl_lex (void);
void PSL_InitParser (void);
void PSL_CloseParser (void);

#endif  /* _PARSER_DEFS__ */

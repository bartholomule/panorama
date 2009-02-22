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

#ifndef _MACHINE__
#define _MACHINE__

#ifdef WORDS_BIGENDIAN
#define FX_BIG_ENDIAN_SYSTEM               (1)
#else
#define FX_BIG_ENDIAN_SYSTEM               (0)
#endif

//
// Some definitions
//

//
// Useful types
//
typedef unsigned char        Byte;
typedef unsigned short int   Word;
typedef unsigned long int    DWord;


//
// Remove stupid warnings (that show the limits of the compiler) from the compilation 
// on some compilers (MSVC++ for example).
//
#include "llapi/warning_eliminator.h"

#endif  /* _MACHINE__ */

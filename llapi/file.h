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

#ifndef _FILE__
#define _FILE__

#include <string>
#include <fstream.h>
#include "llapi/machine.h"

#define FX_LITTLE_ENDIAN         (0)
#define FX_BIG_ENDIAN            (1)

bool FileExists (const string& rktNAME);
string FileExtension (const string& rktNAME);

Word GetWord (istream& rsSTREAM, int iBIG_ENDIAN = FX_LITTLE_ENDIAN);
DWord GetDWord (istream& rsSTREAM, int iBIG_ENDIAN = FX_LITTLE_ENDIAN);
float GetFloat (istream& rsSTREAM, int iBIG_ENDIAN = FX_LITTLE_ENDIAN);
string GetString (istream& rsSTREAM);

#endif  /* _FILE__ */

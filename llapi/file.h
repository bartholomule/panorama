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
#include <fstream>
#include "llapi/machine.h"

#define FX_LITTLE_ENDIAN         (0)
#define FX_BIG_ENDIAN            (1)

// Convert from the default naming convention (unix) to whatever naming convention is required.
std::string FilenameConvert(const std::string& rktNAME);

bool FileExists (const std::string& rktNAME);
std::string FileExtension (const std::string& rktNAME);

Word GetWord (std::istream& rsSTREAM, int iBIG_ENDIAN = FX_LITTLE_ENDIAN);
DWord GetDWord (std::istream& rsSTREAM, int iBIG_ENDIAN = FX_LITTLE_ENDIAN);
float GetFloat (std::istream& rsSTREAM, int iBIG_ENDIAN = FX_LITTLE_ENDIAN);
std::string GetString (std::istream& rsSTREAM);

#endif  /* _FILE__ */

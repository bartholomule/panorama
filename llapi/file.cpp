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

#include "llapi/file.h"

bool FileExists (const string& rktNAME)
{

  ifstream   sFile (rktNAME.c_str(), ios::nocreate);

  if ( !sFile )
  {
    return false;
  }

  sFile.close();
  
  return true;

}  /* FileExists() */


string FileExtension (const string& rktNAME)
{

  char*   pcExtension;
  char*   pcAux;
  char    acFileName [256];

  strcpy (acFileName, rktNAME.c_str());
  
  pcExtension = strtok (acFileName, ".");
  while ( (pcAux = strtok (NULL, ".")) != NULL )
  {
    pcExtension = pcAux;
  }

  return pcExtension;
  
}  /* FileExtension() */


Word GetWord (istream& rsSTREAM, int iBIG_ENDIAN)
{

  if ( iBIG_ENDIAN != FX_BIG_ENDIAN_SYSTEM )
  {
    return ((Word (rsSTREAM.get()) << 8) + Word (rsSTREAM.get()));
  }
  
  return (Word (rsSTREAM.get()) + (Word (rsSTREAM.get()) << 8));

}  /* GetWord() */


DWord GetDWord (istream& rsSTREAM, int iBIG_ENDIAN)
{

  if ( iBIG_ENDIAN != FX_BIG_ENDIAN_SYSTEM )
  {
    return ((DWord (GetWord (rsSTREAM, iBIG_ENDIAN)) << 16) + DWord (GetWord (rsSTREAM, iBIG_ENDIAN)));
  }
  
  return (DWord (GetWord (rsSTREAM, iBIG_ENDIAN)) + (DWord (GetWord (rsSTREAM, iBIG_ENDIAN)) << 16));

}  /* GetWord() */


string GetString (istream& rsSTREAM)
{

  string   tString;
  char     cChar;

  while ( ( (cChar = rsSTREAM.get()) != 0 ) && !rsSTREAM.eof() )
  {
    tString += cChar;
  }

  return tString;
  
}  /* GetString() */


float GetFloat (istream& rsSTREAM, int iBIG_ENDIAN)
{

  //
  // [_TODO_] Fix this function so that it works with architectures in which float is not in
  //          IEEE single precision format.
  //

  float   fValue;
  DWord   dwAux = GetDWord (rsSTREAM, iBIG_ENDIAN);

  memcpy (&fValue, &dwAux, 4);
  
  return fValue;

}  /* GetFloat() */

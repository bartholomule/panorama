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

#ifndef _CHUNKS__
#define _CHUNKS__

#include <vector>
#include <string>
#include <iostream.h>
#include "llapi/color.h"
#include "llapi/llapi_defs.h"
#include "hlapi/mesh_object.h"

void GetLWIdTag (istream& rsSTREAM, char acTAG[4]);
void GetLWColor (istream& rsSTREAM, TColor& rtCOLOR);
void GetLWVector (istream& rsSTREAM, TVector& rtVECTOR);
size_t GetLWString (istream& rsSTREAM, string& rtSTRING);

void ReadPNTSChunk (istream& rsSTREAM, size_t zSIZE, vector<TVector>& rtVERTEX_LIST);
void ReadSRFSChunk (istream& rsSTREAM, size_t zSIZE, vector<string>& rtSURF_LIST);
void ReadPOLSChunk (istream& rsSTREAM, size_t zSIZE, TMeshObject* ptMESH);
  
#endif  /* _CHUNKS__ */

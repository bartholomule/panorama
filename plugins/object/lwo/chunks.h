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
#include "llapi/color.h"
#include "llapi/llapi_defs.h"
#include "hlapi/mesh_object.h"

void GetLWIdTag (std::istream& rsSTREAM, char acTAG[4]);
void GetLWColor (std::istream& rsSTREAM, TColor& rtCOLOR);
void GetLWVector (std::istream& rsSTREAM, TVector& rtVECTOR);
size_t GetLWString (std::istream& rsSTREAM, std::string& rtSTRING);

void ReadPNTSChunk (std::istream& rsSTREAM, size_t zSIZE, std::vector<TVector>& rtVERTEX_LIST);
void ReadSRFSChunk (std::istream& rsSTREAM, size_t zSIZE, std::vector<std::string>& rtSURF_LIST);
void ReadPOLSChunk (std::istream& rsSTREAM, size_t zSIZE, TMeshObject* ptMESH);
  
#endif  /* _CHUNKS__ */

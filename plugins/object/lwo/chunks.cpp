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

#include "llapi/warning_eliminator.h"
#include "chunks.h"
#include "llapi/file.h"

void GetLWIdTag (istream& rsSTREAM, char acTAG[4])
{

  acTAG[0] = rsSTREAM.get();
  acTAG[1] = rsSTREAM.get();
  acTAG[2] = rsSTREAM.get();
  acTAG[3] = rsSTREAM.get();

}  /* GetLWIdTag() */


void GetLWColor (istream& rsSTREAM, TColor& rtCOLOR)
{

  rtCOLOR.setRed (rsSTREAM.get());
  rtCOLOR.setGreen (rsSTREAM.get());
  rtCOLOR.setBlue (rsSTREAM.get());

  rtCOLOR = rtCOLOR.convertFrom24Bits();
  
}  /* GetLWColor() */


void GetLWVector (istream& rsSTREAM, TVector& rtVECTOR)
{

  // Z coordinate is changed from a left-handed system to a right-handed system
  
  rtVECTOR.set (GetFloat (rsSTREAM, FX_BIG_ENDIAN),
                GetFloat (rsSTREAM, FX_BIG_ENDIAN),
                -GetFloat (rsSTREAM, FX_BIG_ENDIAN));

}  /* GetLWVector() */


size_t GetLWString (istream& rsSTREAM, string& rtSTRING)
{

  char     cChar;
  size_t   zChars = 0;

  while ( ( (cChar = rsSTREAM.get()) != 0 ) && !rsSTREAM.eof() )
  {
    rtSTRING += cChar;
    zChars++;
  }

  if ( (zChars & 1) == 0 )
  {
    // Odd number of bytes read, get padding character.
    rsSTREAM.get();
    zChars++;
  }

  return zChars + 1;
  
}  /* GetLWString() */


void ReadPNTSChunk (istream& rsSTREAM, size_t zSIZE, vector<TVector>& rtVERTEX_LIST)
{

  TVector   tVertex;
  
  while ( zSIZE && !rsSTREAM.eof() )
  {
    GetLWVector (rsSTREAM, tVertex);

    rtVERTEX_LIST.push_back (tVertex);

    zSIZE -= 12;
  }

}  /* ReadPNTSChunk() */


void ReadSRFSChunk (istream& rsSTREAM, size_t zSIZE, vector<string>& rtSURF_LIST)
{

  string   tName;
  
  while ( zSIZE && !rsSTREAM.eof() )
  {
    zSIZE -= GetLWString (rsSTREAM, tName);

    rtSURF_LIST.push_back (tName);

    tName = "";
  }

}  /* ReadSRFSChunk() */


void ReadPOLSChunk (istream& rsSTREAM, size_t zSIZE, TMeshObject* ptMESH)
{

  TMesh::TFace     tFace;
  Word             wVertices;
  Word             wVertex;
  int              iSurface;
  vector<size_t>   tVertexList;
  size_t           zFaces = 0;

  while ( zSIZE && !rsSTREAM.eof() )
  {
    zFaces++;

    if ( (zFaces % 1000) == 0 )
    {
      cout << "Faces : " << zFaces << endl;
    }
    
    wVertices = GetWord (rsSTREAM, FX_BIG_ENDIAN);
    zSIZE    -= 2;

    tVertexList.clear();
    for (Word J = 0; ( J < wVertices ) ;J++)
    {
      wVertex = GetWord (rsSTREAM, FX_BIG_ENDIAN);
      
      tVertexList.push_back (wVertex);
    }

    zSIZE -= 2 * wVertices;

    iSurface = GetWord (rsSTREAM, FX_BIG_ENDIAN);
    zSIZE   -= 2;

    if ( iSurface < 0 )
    {
      cout << "MODEL HAS DETAIL POLYGONS!!!!!!!!!!!" << endl;
    }

    if ( wVertices == 3 )
    {
      tFace.azVertex[0] = tVertexList[2];
      tFace.azVertex[1] = tVertexList[1];
      tFace.azVertex[2] = tVertexList[0];
      tFace.pktObject   = ptMESH;
      
      ptMESH->faceList().push_back (tFace);
    }
    else
    {
      cout << "NON TRIANGLE VERTEX!!!, vertices = " << wVertices << endl;
    }
  }

}  /* ReadPOLSChunk() */

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

#include "lwo.h"
#include "chunks.h"
#include "llapi/file.h"
#include "llapi/material.h"

DEFINE_PLUGIN ("ObjectLW", FX_OBJECT_CLASS, TLightWaveObject);

int TLightWaveObject::parseObject (void)
{

  ifstream         sFile;
  size_t           zBytesLeft;
  size_t           zTagSize;
  vector<string>   tSurfaceNameList;
  char             acTag [5]   = "    ";
  bool             gPointsRead = false;

  sFile.open (tFileName.c_str(), ios::in | ios::binary);

  if ( !sFile )
  {
    return -1;
  }
  
  GetLWIdTag (sFile, acTag);
  if ( strcmp (acTag, "FORM") )
  {
    cerr << "File not in IFF format" << endl;

    sFile.close();

    return -1;
  }

  zBytesLeft = GetDWord (sFile, FX_BIG_ENDIAN);

  GetLWIdTag (sFile, acTag);
  if ( strcmp (acTag, "LWOB") )
  {
    cerr << "File is not a LightWave object" << endl;

    sFile.close();

    return -1;
  }

  zBytesLeft -= 4;

  while ( zBytesLeft > 0 )
  {
    GetLWIdTag (sFile, acTag);

    zTagSize = GetDWord (sFile, FX_BIG_ENDIAN);

    if ( !strcmp (acTag, "PNTS") )
    {
      ReadPNTSChunk (sFile, zTagSize, tVertexList);
      gPointsRead = true;

      cout << "Vertices : " << tVertexList.size() << endl;
    }
    else if ( !strcmp (acTag, "SRFS") )
    {
      ReadSRFSChunk (sFile, zTagSize, tSurfaceNameList);

      for (size_t J = 0; ( J < tSurfaceNameList.size() ) ;J++)
      {
        cout << "Surface (" << J << ") : " << tSurfaceNameList [J] << endl;
      }
    }
    else if ( !strcmp (acTag, "POLS") )
    {
      ReadPOLSChunk (sFile, zTagSize, this);

      cout << "Faces : " << tFaceList.size() << endl;
    }
    else
    {
      cout << "Unknown tag : " << acTag << endl;

      sFile.seekg (zTagSize, ios::cur);
    }

    zBytesLeft -= (zTagSize + 8);
  }
  
  sFile.close();

  return 0;
  
}  /* parseObject() */


int TLightWaveObject::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "file" )
  {
    if ( eTYPE == FX_STRING )
    {
      tFileName = (char*) nVALUE.pvValue;

      if ( parseObject() )
      {
        TProcedural::_tUserErrorMessage = string ("could not open object file ") + tFileName;
        return FX_ATTRIB_USER_ERROR;
      }
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TMeshObject::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TLightWaveObject::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "file" )
  {
    rnVALUE.pvValue = (char*) tFileName.c_str();
  }
  else
  {
    return TMeshObject::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TLightWaveObject::getAttributeList (TAttributeList& rtLIST) const
{

  TMeshObject::getAttributeList (rtLIST);

  rtLIST ["file"]  = FX_STRING;

}  /* getAttributeList() */

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
#include "lwo.h"
#include "chunks.h"
#include "llapi/file.h"
#include "llapi/material.h"
#include "llapi/attribute.h"

DEFINE_PLUGIN ("ObjectLW", FX_OBJECT_CLASS, TLightWaveObject);

int TLightWaveObject::parseObject (void)
{

  std::ifstream    sFile;
  size_t           zBytesLeft;
  size_t           zTagSize;
  std::vector<std::string>   tSurfaceNameList;
  char             acTag [5]   = "    ";
  bool             gPointsRead = false;

  sFile.open (tFileName.c_str(), std::ios::in | std::ios::binary);

  if ( !sFile )
  {
    return -1;
  }
  
  GetLWIdTag (sFile, acTag);
  if ( strcmp (acTag, "FORM") )
  {
    GOM.error() << "File not in IFF format" << std::endl;

    sFile.close();

    return -1;
  }

  zBytesLeft = GetDWord (sFile, FX_BIG_ENDIAN);

  GetLWIdTag (sFile, acTag);
  if ( strcmp (acTag, "LWOB") )
  {
    GOM.error() << "File is not a LightWave object" << std::endl;

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

      GOM.debug() << "Vertices : " << tVertexList.size() << std::endl;
    }
    else if ( !strcmp (acTag, "SRFS") )
    {
      ReadSRFSChunk (sFile, zTagSize, tSurfaceNameList);

      for (size_t J = 0; ( J < tSurfaceNameList.size() ) ;J++)
      {
        GOM.debug() << "Surface (" << J << ") : " << tSurfaceNameList [J] << std::endl;
      }
    }
    else if ( !strcmp (acTag, "POLS") )
    {
      ReadPOLSChunk (sFile, zTagSize, this);

      GOM.debug() << "Faces : " << tFaceList.size() << std::endl;
    }
    else
    {
      GOM.debug() << "Unknown tag : " << acTag << std::endl;

      sFile.seekg (zTagSize, std::ios::cur);
    }

    zBytesLeft -= (zTagSize + 8);
  }
  
  sFile.close();

  return 0;
  
}  /* parseObject() */


int TLightWaveObject::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "file" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_STRING )
    {
      tFileName = (char*) nVALUE.pvValue;

      if ( parseObject() )
      {
        TProcedural::_tUserErrorMessage = std::string ("could not open object file ") + tFileName;
        return FX_ATTRIB_USER_ERROR;
      }
    }
#else
    magic_pointer<TAttribString> str = get_string(nVALUE);
    if( !!str )
    {
      tFileName = str->tValue;

      if ( parseObject() )
      {
        TProcedural::_tUserErrorMessage = std::string ("could not open object file ") + tFileName;
        return FX_ATTRIB_USER_ERROR;
      }      
    }
#endif
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


int TLightWaveObject::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "file" )
  {
#if !defined(NEW_ATTRIBUTES)
    rnVALUE.pvValue = (char*) tFileName.c_str();
#else
    rnVALUE = (user_arg_type)new TAttribString (tFileName);
#endif
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

/*
*  Copyright (C) 1998 Matt Kimball
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
#include <string>
#include <stdio.h>
#include "subdiv.h"
#include "subdivvert.h"
#include "subdivedge.h"
#include "subdivface.h"

DEFINE_PLUGIN ("SubdivisionSurface", FX_OBJECT_CLASS, TSubdiv);

TSubdiv::TSubdiv (void)
{

}  /* TSubdiv() */


TSubdiv::~TSubdiv (void)
{

}  /* ~TSubdiv() */


bool TSubdiv::findAllIntersections (const TRay& rktRAY, 
                                    TSpanList& rtLIST) const
{
  bool      gFoundIntersection;
  TRay      tTransformRay;
  TScalar   tScale;

  tTransformRay = rktRAY;
  tScale = tTransformRay.applyTransform (ptInverseMatrix);

  gFoundIntersection = false;
  for (vector<TSubdivFace*>::const_iterator tIter = tFaces.begin(); ( tIter != tFaces.end() ) ;tIter++)
  {
    if ( (*tIter)->findAllIntersections (*this, rktRAY, tScale,
                                         tTransformRay, rtLIST) )
    {
      gFoundIntersection = true;
    }
  }

  return gFoundIntersection;

}  /* findAllIntersections() */


int TSubdiv::setAttribute (const string& rktNAME, NAttribute nVALUE, 
                           EAttribType eTYPE)
{
  string   tVal;

  if ( rktNAME == "method" )
  {
    if ( eTYPE != FX_STRING )
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
 
    tVal = (char *)nVALUE.pvValue;
    if ( tVal == "Catmull-Clark" )
    {
      //  This is the default method, so do nothing.
    }
    else
    {
      _tUserErrorMessage = "Unknown subdivision method";
      return FX_ATTRIB_USER_ERROR;
    }

    return FX_ATTRIB_OK;
  }
  
  if ( rktNAME == "vert" )
  {
    if ( eTYPE != FX_STRING )
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
 
    if ( addVertex ((char *)nVALUE.pvValue) )
    {
      _tUserErrorMessage = "Error in vertex specification";
      return FX_ATTRIB_USER_ERROR;
    }

    return FX_ATTRIB_OK;
  }
  
  if ( rktNAME == "face" )
  { 
    if ( eTYPE != FX_STRING )
    {
      return FX_ATTRIB_WRONG_TYPE;
    }

    if ( addFace ((char *)nVALUE.pvValue) )
    {
      _tUserErrorMessage = "Error in face specification";
      return FX_ATTRIB_USER_ERROR;
    }

    return FX_ATTRIB_OK;
  }

  return TObject::setAttribute (rktNAME, nVALUE, eTYPE);

}  /* setAttribute() */

//
//  Attempt to process the specification for a vector.  
//  If there is an error, return true.
//
bool TSubdiv::addVertex (const string& rktVALUE)
{
  Byte    bMatched;
  char    acName[256];
  float   fX, fY, fZ;

  bMatched = sscanf (rktVALUE.c_str(), " %255s < %f , %f , %f > ", 
                     acName, &fX, &fY, &fZ); 
  if ( bMatched != 4 )
    return true;

  tPoints[acName] = new TSubdivVert (rktVALUE, TVector (fX, fY, fZ));

  return false;

}  /* addVertex() */


//
//  Attempt to process the specification for a face on the subdivision
//  surface.  
//  If there is an error, return true.
//
bool TSubdiv::addFace (const string& rktVALUE)
{
  vector<string>         tPointNames;
  vector<TSubdivVert*>   tFacePoints;
  char                   acName[256];
  char*                  pcStr;
  Byte                   bMatched;
  int                    dwConsumed;

  pcStr = (char *)rktVALUE.c_str();
  while ( true )
  {
    bMatched = sscanf (pcStr, " %255s %n", acName, &dwConsumed);
    pcStr += dwConsumed;

    if ( bMatched != 1 && bMatched != 2 ) 
    {
      break;
    }

    tPointNames.push_back (acName);
  }

  if ( tPointNames.size() < 3 )
  {
    return true;
  }

  for (vector<string>::const_iterator tIter = tPointNames.begin(); ( tIter != tPointNames.end() ) ;tIter++)
  {
    if ( tPoints.find (*tIter) == tPoints.end() )
    {
      return true;
    }

    tFacePoints.push_back (tPoints[*tIter]);
  }  

  tFaces.push_back (new TSubdivFace (tFacePoints));

  return false;

}  /* addVertex() */

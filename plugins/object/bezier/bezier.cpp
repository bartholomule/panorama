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

#include "llapi/llapi_defs.h"
#include "bezier.h"
#include "beziersub.h"

DEFINE_PLUGIN ("BezierSurface", FX_OBJECT_CLASS, TBezierSurface);

TBezierSurface::TBezierSurface (void)
{

  ptCurrentSurface = NULL;

}  /* TBezierSurface() */


TBezierSurface::~TBezierSurface (void)
{

  delete ptCurrentSurface;

  for (vector<TBezierSubsurface*>::iterator tIter = tSurfaceList.begin(); ( tIter != tSurfaceList.end() ) ;tIter++)
  {
    delete (*tIter);
  }

}  /* ~TBezierSurface() */


bool TBezierSurface::findAllIntersections (const TRay& rktRAY, 
					   TSpanList& rtLIST) const
{

  TScalar   tFactor;
  TRay      tTransformRay      = rktRAY;
  bool      gFoundIntersection = false;
  
  tFactor = tTransformRay.applyTransform (ptInverseMatrix);

  for (vector<TBezierSubsurface*>::const_iterator tIter = tSurfaceList.begin(); ( tIter != tSurfaceList.end() ) ;tIter++)
  {
    bool gFoundMoreIntersections = (*tIter)->findAllIntersections (tTransformRay, tFactor, rktRAY, rtLIST);

    gFoundIntersection = gFoundIntersection || gFoundMoreIntersections;
  }

  return gFoundIntersection;

}  /* findAllIntersections() */


int TBezierSurface::setAttribute (const string& rktNAME, NAttribute nVALUE, 
				  EAttribType eTYPE)
{

  if ( rktNAME == "control" )
  {
    if ( eTYPE != FX_VECTOR )
    {
      return FX_ATTRIB_WRONG_TYPE;
    }

    TVector* v = (TVector*) nVALUE.pvValue;

    if ( ptCurrentSurface == NULL )
    {
      ptCurrentSurface = new TBezierSubsurface (this);
     
      iBuildU = 0;
      iBuildV = 0;
    }

    ptCurrentSurface->setPoint (iBuildU, iBuildV, *v);
    iBuildU++;

    if ( iBuildU >= 4 )
    {
      iBuildU = 0;
      iBuildV++;
    }

    if ( iBuildV >= 4 )
    {
      ptCurrentSurface->calculateSubdivisionDepth();

      tSurfaceList.push_back (ptCurrentSurface);
      ptCurrentSurface = NULL;
    }

    return FX_ATTRIB_OK;
  }

  return TTransformObject::setAttribute (rktNAME, nVALUE, eTYPE);

}  /* setAttribute() */

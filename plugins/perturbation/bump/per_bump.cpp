/*
*  Copyright (C) 2000 Jon Frydensbjerg
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
*
*  Algorithm based on public domain code by Jim McElhiney,
*  CompuServe 71201,1326, aka mcelhiney@acm.org
*/

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "per_bump.h"

DEFINE_PLUGIN ("PerturbationBump", FX_PERTURBATION_CLASS, TPerturbationBump);

TPerturbationBump::TPerturbationBump (void) :
      TPerturbation(),
      ptPattern (NULL),
      tBumpFactor (1),
      tSamples (2, 2)
{

  calcTotalNoSamples();

}  /* TPerturbationBump() */

TVector TPerturbationBump::perturbNormal (const TSurfaceData& rktDATA) const
{

  TVector   tNewNormal = rktDATA.normal();

  if ( fabs(tBumpFactor) > FX_EPSILON )
  {
    TSurfaceData   tData;
    TColor         tColor;
    TVector        tGradientU;
    TVector        tGradientV;
    TVector        r, s, t;
    TVector        tTemp;
    TScalar        tHeight;
    TScalar        tHeightDiff;
    TScalar        dx, dy;
    TScalar        x, y;
    TScalar        tRDamping;
    TScalar        tTDamping;
    TScalar        tRTotal;
    TScalar        tTTotal;

    if ( !ptPattern )
    {
      cout << ("Error: pattern must be set") << endl;
      exit (1);
    }

    s = rktDATA.normal();

    r = crossProduct (s, TVector(0.0, 1.0, 0.0));

    if ( r.norm() < FX_EPSILON )
    {
      r = TVector(1.0, 0.0, 0.0);

      if ( fabs (s.y() - 1.0) < FX_EPSILON )
      {
	s = TVector(0.0, 1.0, 0.0);
      }
      else
      {
	s = TVector(0.0, -1.0, 0.0);
      }
    }

    s.normalize();
    t = crossProduct (s, r);
    t.normalize();

    tGradientU = r * tGradientDisplacement.x();
    tGradientV = t * tGradientDisplacement.y();

    tData = rktDATA;

    tColor = ptPattern->color (rktDATA);
    tHeight = tColor.average();

    dx = ( tSamples.x() > 1 ) ? (2.0 / (tSamples.x() - 1.0)) : 0;
    dy = ( tSamples.y() > 1 ) ? (2.0 / (tSamples.y() - 1.0)) : 0;    

    tRTotal = 0;
    tTTotal = 0;

    y = -1.0;

    for (size_t iy = 0; ( iy < (size_t) tSamples.y() ); iy++)
    {  
      x = -1.0;

      tTDamping = ( y == 0 ) ? 0 : (1.0 - (y * y) * 0.5);

      if ( y < 0 )
      {
        tTDamping = -tTDamping;  
      }

      for (size_t ix = 0; ( ix < (size_t) tSamples.x() ); ix++)
      {
	tTemp = rktDATA.point() + (tGradientU * x) + (tGradientV * y);
	tData.setPoint (tTemp);
	tColor = ptPattern->color (tData);

	tHeightDiff = tColor.average() - tHeight;
	
	tRDamping = ( x == 0 ) ? 0 : (1.0 - (x * x) * 0.5);	

	if ( x < 0 )
	{
	  tRDamping = -tRDamping;  
	}
	
	tRTotal += tHeightDiff * tRDamping;
	tTTotal += tHeightDiff * tTDamping;

	x += dx;
      }

      y += dy;
    }

    r *= tRTotal;
    t *= tTTotal;

    tNewNormal = rktDATA.normal() + (r + t) * tBumpFactor * tTotalNoSamples;
    tNewNormal.normalize();
  }
  
  return tNewNormal;
  
}  /* perturbNormal() */


int TPerturbationBump::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "source" )
  {
    if ( eTYPE == FX_PATTERN )
    {
      setPattern ((TPattern*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "grad_disp" )
  {
    if ( eTYPE == FX_VECTOR2 )
    {
      tGradientDisplacement = (*((TVector2*) nVALUE.pvValue));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "bump" )
  {
    if ( eTYPE == FX_REAL )
    {
      tBumpFactor = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "samples" )
  {
    if ( eTYPE == FX_VECTOR2 )
    {
      tSamples = (*((TVector2*) nVALUE.pvValue));

      calcTotalNoSamples();
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TPerturbation::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TPerturbationBump::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "source" )
  {
    rnVALUE.pvValue = ptPattern;
  }
  else if ( rktNAME == "grad_disp" )
  {
    rnVALUE.pvValue = &tGradientDisplacement;
  }
  else if ( rktNAME == "bump" )
  {
    rnVALUE.dValue = tBumpFactor;
  }
  else if ( rktNAME == "samples" )
  {
    rnVALUE.pvValue = &tSamples;
  }
  else
  {
    return TPerturbation::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPerturbationBump::getAttributeList (TAttributeList& rtLIST) const
{

  TPerturbation::getAttributeList (rtLIST);

  rtLIST ["source"]    = FX_PATTERN;
  rtLIST ["grad_disp"] = FX_VECTOR2;
  rtLIST ["bump"]      = FX_REAL;
  rtLIST ["samples"]   = FX_VECTOR2;

}  /* getAttributeList() */


/*
*  Copyright (C) 2001 Kevin Harris
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
#include <stdlib.h>
#include <iostream>
#include "per_wave.h"
#include <llapi/math_tools.h>

DEFINE_PLUGIN ("PerturbationWave", FX_PERTURBATION_CLASS, TPerturbationWave);

TPerturbationWave::TPerturbationWave (void):
  TPerturbation(),
  all_wave_sources(3),
  tMin_freq(0.7),
  tMax_freq(10),
  tMin_coord(-100),
  tMax_coord(100)
{
}

TVector TPerturbationWave::perturbNormal (const TSurfaceData& rktDATA) const
{
  TVector normal = rktDATA.unperturbedNormal();
  TVector normal_pert(0,0,0);
  // Apply the contribution from all of the wave sources.
  
  for(vector<TWaveSource>::const_iterator i = all_wave_sources.begin();
      i != all_wave_sources.end();
      ++i)
  {
    TVector contrib = wave_contribution(rktDATA.point(), *i);
    normal_pert += contrib;
  }
  TVector new_normal = normal + normal_pert;
  new_normal.normalize();
  
  return new_normal;
}  /* perturbNormal() */


int TPerturbationWave::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
#if defined(__FUNCTION__)
  cout << __FUNCTION__ << "(" << rktNAME << ") called." << endl;
#elif defined(__FUNCTION)
  cout << __FUNCTION << "(" << rktNAME << ") called." << endl;
#endif

  if ( rktNAME == "sources" )
  {
    if ( eTYPE == FX_REAL )
    {
      int new_num_sources = int(nVALUE.dValue);
      if ( new_num_sources < 0 )
      {
	all_wave_sources.resize(0);
	return FX_ATTRIB_WRONG_VALUE;
      }
      all_wave_sources.resize(new_num_sources);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }    
  }
  else if ( rktNAME == "min_freq" )
  {
    if ( eTYPE == FX_REAL )
    {
      tMin_freq = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }    
  }
  else if ( rktNAME == "max_freq" )
  {
    if ( eTYPE == FX_REAL )
    {
      tMax_freq = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }    
  }
  else if ( rktNAME == "min_coord" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      tMin_coord = (*((TVector*) nVALUE.pvValue));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }    
  }
  else if ( rktNAME == "max_coord" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      tMax_coord = (*((TVector*) nVALUE.pvValue));
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


int TPerturbationWave::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{
#if defined(__FUNCTION__)
  cout << __FUNCTION__ << "(" << rktNAME << ") called." << endl;
#elif defined(__FUNCTION)
  cout << __FUNCTION << "(" << rktNAME << ") called." << endl;
#endif
  if ( rktNAME == "sources" )
  {
    rnVALUE.dValue = int(all_wave_sources.size());
  }
  else if ( rktNAME == "min_freq" )
  {
    rnVALUE.dValue = tMin_freq;
  }
  else if ( rktNAME == "max_freq" )
  {
    rnVALUE.dValue = tMax_freq;
  }
  else if ( rktNAME == "min_coord" )
  {
    rnVALUE.pvValue = (void*)&tMin_coord;
  }
  else if ( rktNAME == "max_coord" )
  {
    rnVALUE.pvValue = (void*)&tMax_coord;
  }
  else
  {
    return TPerturbation::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPerturbationWave::getAttributeList (TAttributeList& rtLIST) const
{
#if defined(__FUNCTION__)
  cout << __FUNCTION__ << " called." << endl;
#elif defined(__FUNCTION)
  cout << __FUNCTION << " called." << endl;
#endif
  
  TPerturbation::getAttributeList (rtLIST);

  rtLIST ["sources"]   = FX_REAL;
  rtLIST ["min_freq"]  = FX_REAL;
  rtLIST ["max_freq"]  = FX_REAL;
  rtLIST ["min_coord"]  = FX_VECTOR;
  rtLIST ["max_coord"]  = FX_VECTOR;
  
}  /* getAttributeList() */


TVector TPerturbationWave::wave_contribution(const TVector& location, const TWaveSource& ws)
{
  TVector v = location - ws.center;
  TScalar norm = v.norm();

  TScalar cycle = ws.amplitude * sin(ws.frequency * norm);

  return v * (cycle / norm);
}

TVector TPerturbationWave::wave_contribution(const TVector& location, const TWaveSource& ws, TScalar time)
{
  TVector v = location - ws.center;
  TScalar norm = v.norm();


  // Note that I am setting the propogation speed of the wave to be the square
  // root of the frequency (as stated in Ken Perlin's paper "An Image
  // Synthesizer")...  It was suggested that this makes the waves appear to
  // move in a realistic manor.
  TScalar cycle =  ws.amplitude * (sin(ws.frequency * norm +
				       time * sqrt(ws.frequency) ) );

  return v * (cycle / norm);  
}

bool TPerturbationWave::initialize(void)
{
  bool val = true;
#if defined(__FUNCTION__)
  cout << __FUNCTION__ << " called." << endl;  
#elif defined(__FUNCTION)
  cout << __FUNCTION << " called." << endl;  
#endif

  // Create a random group of wave sources...

  // frand()...
  
  // If they have the min and max backwards, swap them.
  if(tMin_freq > tMax_freq)
  {
    TScalar temp = tMin_freq;
    tMin_freq = tMax_freq;
    tMax_freq = temp;
  }

  TVector diff = tMax_coord - tMin_coord;
  TScalar freq_diff = tMax_freq - tMin_freq;

  // 
  if( ( freq_diff < FX_EPSILON ) && ( fabs(tMin_freq) < FX_EPSILON ) )
  {
    // Both the difference and the minimum are effectively 0, no wave
    // contribution.  There is, therefore, no reason to have ANY sources, as
    // they will NEVER have any effect.
    all_wave_sources.resize(0);
  }
  
  for(vector<TWaveSource>::iterator i = all_wave_sources.begin();
      i != all_wave_sources.end();
      ++i)
  {
    // Generate a random center for the wave source (within the constraints).
    TVector location(frand(), frand(), frand());
    location *= diff;
    location += tMin_coord;
    i->center = location;

    // Generate a random frequency for the wave source (within the
    // constraints). Note that this loop is guaranteed to eventually terminate,
    // as the test above (before the loop over all sources), guarantees that we
    // will never execute this loop if there could only be a frequency of 0 for
    // all wave sources.  We do not want 0-frequency sources, because they have
    // no effect on anything (not moving).
    do
    {
      i->frequency = frand() * freq_diff + tMin_freq;
    }
    while( fabs(i->frequency) < FX_EPSILON );

    // Create an amplitude for the wave source.  According to Ken Perlin's
    // paper "An Image Synthesizer", this should be 1/frequency,
    i->amplitude = 1.0 / i->frequency;
  }
  return val && TPerturbation::initialize();
}

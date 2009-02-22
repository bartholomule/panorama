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
*
*/

#ifndef _PERTURBATION_WAVE__
#define _PERTURBATION_WAVE__

#include "llapi/perturbation.h"
#include "llapi/pattern.h"
#include "llapi/gradient.h"
#include "hlapi/plugin_manager.h"

struct TWaveSource
{
  TVector center;
  TScalar amplitude;
  TScalar frequency;
}; /* TWaveSource */

class TPerturbationWave : public TPerturbation
{

protected:
  std::vector<TWaveSource> all_wave_sources;
  TScalar tMin_freq;
  TScalar tMax_freq;
  TVector tMin_coord;
  TVector tMax_coord;
  bool    tNormal_shifted_positive;
  
public:

  static TBaseClass* _create (const TBaseClass* pktPARENT);

  TPerturbationWave (void);

  virtual bool initialize (void);

  virtual TVector perturbNormal (const TSurfaceData& rktDATA) const;

  virtual int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  virtual int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
  virtual void getAttributeList (TAttributeList& rtLIST) const;

  virtual std::string className (void) const { return "PerturbationWave"; }
  virtual TPerturbationWave* clone_new() const { return new TPerturbationWave(*this); }  

  static TVector wave_contribution(const TVector& location, const TWaveSource& ws);
  static TVector wave_contribution(const TVector& location, const TWaveSource& ws, TScalar time);
  void create_random_sources();
};  /* class TPerturbationWave */

#endif  /* _PERTURBATION_WAVE__ */

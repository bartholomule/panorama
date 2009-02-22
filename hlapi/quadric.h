/*
*  Copyright (C) 2003 Kevin Harris
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

#if       !defined(_QUADRIC__)
#define            _QUADRIC__

#include "llapi/object.h"
#include <vector>

/*
  A generic quadric shape.
  This quadric is in the form:
  A*x^2 + B*y^2 + C*z^2 + D*x*y + E*x*z + F*y*z + G*x + H*y + I*z + J = 0

  As such, a sphere of radius 1 (centered at the origin) could be defined as:
  1x^2 + 1y^2 + 1z^2 - 1 = 0
  That is, A = B = C = 1, J = -1
  
  All coefficients are zeroed by default, so unless copying from another
  modified quadric, it should be possible to modify only those values which
  need to be set.

  Squareds = A,B,C     ie, x^2
  Combos   = D,E,F     ie, x*z
  Singles  = G,H,I     ie, y, 
  Constant = J
 */

class TQuadric : public TObject
{
public:
  TQuadric();
  TQuadric(const TQuadric& oq);
  virtual ~TQuadric();
  TQuadric& operator=(const TQuadric& oq);

  bool initialize(void);

  int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
  void getAttributeList (TAttributeList& rtLIST) const;

  TUserFunctionMap getUserFunctions();

  bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
  bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;


  /* I do not know how to do this uniformly, or in any kind of fast manor. */
  //TVector RandomPointOnSurface() const;

  void printDebug (const std::string& indent) const;
  std::string className (void) const { return "Quadric"; }

  
  TScalar operator[](size_t index) const;
  TScalar get_coef(size_t index) const { return (*this)[index]; }
  void set_coef(size_t index, TScalar val);
  // Set 3 coefficients starting at the given index.  This will be careful
  // about writing too many.
  // This may be useful to do somthing like setting the values of all the
  // squared components -- set_coefs(0, <A,B,C>)
  
  void set_coefs(unsigned index, const TVector& values);
  // Set all 10, even if the thing isn't the proper size.
  void set_coefs(const std::vector<TScalar>& values);

  std::vector<TScalar> get_coefs() const { return coefs; }

protected:
  TVector localNormal (const TVector& rktPOINT) const;
  
private:

  std::vector<TScalar> coefs;  // TScalar coefs[10];
  enum coef_num { CQ_A = 0, CQ_B, CQ_C, CQ_D, CQ_E, CQ_F, CQ_G, CQ_H, CQ_I, CQ_J, CQ_NUM_COEFS };
};

#endif /* !defined(_QUADRIC__) */


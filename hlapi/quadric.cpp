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

#include "llapi/warning_eliminator.h"
#include <cmath>
#include "hlapi/quadric.h"
#include "llapi/root_solver.h"

#define QA coefs[CQ_A]
#define QB coefs[CQ_B]
#define QC coefs[CQ_C]
#define QD coefs[CQ_D]
#define QE coefs[CQ_E]
#define QF coefs[CQ_F]
#define QG coefs[CQ_G]
#define QH coefs[CQ_H]
#define QI coefs[CQ_I]
#define QJ coefs[CQ_J]
#define VX v.x()
#define VY v.y()
#define VZ v.z()
#define OX o.x()
#define OY o.y()
#define OZ o.z()

TQuadric::TQuadric():
  TObject(),
  coefs(std::vector<TScalar>(CQ_NUM_COEFS, 0.0))
{
}

TQuadric::TQuadric(const TQuadric& oq):
  TObject(oq),
  coefs(oq.coefs)
{
}

TQuadric::~TQuadric()
{
  // Nothing for now.
}

TQuadric& TQuadric::operator=(const TQuadric& oq)
{
  if( &oq != this )
  {
    coefs = oq.coefs;

    TObject::operator=(oq);
  }
  return *this;
}

bool TQuadric::initialize (void)
{
  bool val = true;
  
  // Temp... See below.
  sCapabilities.gInfinite = true;

  // Sanity check...
  if( coefs.size() != size_t(CQ_NUM_COEFS) )
  {
    val = false;
  }
  else
  {
    // [FIXME!] Check for infinite sized objects (ie. one of A,B,C==0, negative
    // combinations, etc. -- DO THE MATH!)
    // [FIXME!] Find the proper bounding box size
  }
  return val && TObject::initialize();
}

int TQuadric::setAttribute (const string& rktNAME, NAttribute nVALUE,
			    EAttribType eTYPE)
{
  if( rktNAME == "coefficients" || rktNAME == "coefs" )
  {
    magic_pointer<TAttribArray> a = get_array(nVALUE);
    if( !!a )
    {
      set_coefs(a->tValue);
    }    
  }
  else
  {
    return TObject::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;  
}

int TQuadric::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{
  if( rktNAME == "coefficients" || rktNAME == "coefs" )
  {
    rnVALUE = (user_arg_type)new TAttribArray(coefs);
    return FX_ATTRIB_OK;
  }
  else
  {
    return TObject::getAttribute (rktNAME, rnVALUE);
  }
  return FX_ATTRIB_OK;
}

void TQuadric::getAttributeList (TAttributeList& rtLIST) const
{
  TObject::getAttributeList (rtLIST);

  rtLIST ["coefs"] = FX_ARRAY;  
}

TUserFunctionMap TQuadric::getUserFunctions()
{
  TUserFunctionMap retmap = TObject::getUserFunctions();

  retmap["getCoef"]=create_user_function(this,&TQuadric::get_coef);
  retmap["getCoefs"]=create_user_function(this,&TQuadric::get_coefs);  
  retmap["setCoef"]=create_user_function(this,&TQuadric::set_coef);
  void (TQuadric::*fn)(const std::vector<TScalar>&) = &TQuadric::set_coefs;  
  retmap["setCoefs"]=create_user_function(this,fn);
  
  void (TQuadric::*fn2)(unsigned,const TVector&) = &TQuadric::set_coefs;  
  retmap["setCoefsV"]=create_user_function(this,fn2);

  return retmap;
}

bool TQuadric::findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA)
  const
{
  // This method was derived by me (Kevin Harris), after a little while of
  // twiddling with the general equation for a quartic.  There may be a much
  // faster way (TODO: check POV, graphics gems, etc. ), but I want to see how
  // rusty my math actually is.
  
  TRay tRayIT = rktRAY;
  TScalar tFactor = tRayIT.applyTransform (ptInverseMatrix);
  tRayIT.applyRangeFactor( 1.0 / tFactor );
  
  const TVector v = tRayIT.direction();
  const TVector o = tRayIT.location();  

  TScalar A = ( VX * (VX * QA + VY * QD + VZ * QE) +
		VY * (          VY * QB + VZ * QF) +
		VZ * (                    VZ * QC) );
  TScalar B = ( VX * (2 * OX * QA + OY * QD + OZ * QE + QG) +
		VY * (2 * OY * QB + OX * QD + OZ * QF + QH) +
		VZ * (2 * OZ * QC + OX * QE + OY * QF + QI) );
  TScalar C = ( OX * (OX * QA + OY * QD + OZ * QE + QG) +
		OY * (          OY * QB + OZ * QF + QH) +
		OZ * (                    OZ * QC + QI) +
		QJ );

  TScalar t1, t2;
    
  if( fabs(A) > FX_EPSILON )
  {
    TScalar discriminant = B * B - 4 * A * C;  
    
    // if it did not hit the quadric, bail
    if( discriminant <= 0 )
    {
      return false;
    }
    
    rtDATA.setup (this, rktRAY);
    
    TScalar sqrtd = sqrt(discriminant);
    

    TVector tpoint;
  
    // T2 will always be more than t1...    
    t1 = (-B - sqrtd) / (2 * A);
    
    if( rktRAY.range().inside(t1 * tFactor) )
    {
      //      cout << "origin " << o << " direction " << v << " factor " << tFactor <<" range " << rktRAY.range() << endl;
      //      cout << identifier() << ": t1=" << tFactor * t1 << endl;
      rtDATA.setPoint (tFactor * t1);
      return true;
    }
    t2 = (-B + sqrtd) / (2 * A);
    if( rktRAY.range().inside(t2 * tFactor) )
    {
      //      cout << "origin " << o << " direction " << v << " factor " << tFactor << " range " << rktRAY.range() << endl;
      //      cout << identifier() << ": t2=" << tFactor * t2 << endl;    
      rtDATA.setPoint (tFactor * t2);
      return true;    
    }
  }
  else if( fabs(B) > FX_EPSILON )
  {
    // This is not actually a quadric... It is, instead, a linear equation.

    // 0t^2 + B*t + C = 0 --> t = (-C)/B
    t1 = (-C)/B;
    if( rktRAY.range().inside( t1 * tFactor ) )
    {
      rtDATA.setPoint (tFactor * t2);
      return true;      
    }
  }
  else
  {
    // Constant equation....
    // 0t^2 + 0t + C = 0 --> No hit.
  }
  return false;
}

bool TQuadric::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST)
  const
{
  bool gIntersection = false;
  TSurfaceData   rtDATA;  
  TRay tRayIT = rktRAY;
  TScalar tFactor = tRayIT.applyTransform (ptInverseMatrix);
  tRayIT.applyRangeFactor( 1.0 / tFactor );
  
  const TVector v = tRayIT.direction();
  const TVector o = tRayIT.location();


  TScalar A = ( VX * (VX * QA + VY * QD + VZ * QE) +
		VY * (          VY * QB + VZ * QF) +
		VZ * (                    VZ * QC) );
  TScalar B = ( VX * (2 * OX * QA + OY * QD + OZ * QE + QG) +
		VY * (2 * OY * QB + OX * QD + OZ * QF + QH) +
		VZ * (2 * OZ * QC + OX * QE + OY * QF + QI) );
  TScalar C = ( OX * (OX * QA + OY * QD + OZ * QE + QG) +
		OY * (          OY * QB + OZ * QF + QH) +
		OZ * (                    OZ * QC + QI) +
		QJ );  

  // The simple method of solving it...
  double cs[3];
  double ts[2];
  cs[0] = A;
  cs[1] = B;
  cs[2] = C;

  int num_solutions = SafeSolveQuadric(cs, ts);
  if( num_solutions > 0 )
  {
    rtDATA.setup (this, rktRAY);    
    for(int solution = 0; solution < num_solutions; ++solution)
    {
      if( tRayIT.range().inside(ts[solution]) )
      {
	rtDATA.setPoint( tFactor * ts[solution] );
	rtLIST.add( rtDATA );
	gIntersection = true;
      }
    }
  }

  /*
  // The more complex, but maybe faster method.
  TScalar discriminant = B * B - 4 * A * C;

  // if it did not hit the sphere, bail
  if( discriminant < 0 )
  {
    rtDATA.setup (this, rktRAY);
    
    TScalar sqrtd = sqrt(discriminant);
    
    TScalar t1, t2;
    
    // T2 will always be more than t1...    
    t1 = (-B - sqrtd) / (2 * A);
    
    if( tRayIT.range().inside(t1) )
    {
      rtDATA.setPoint (tFactor * t1);
      rtLIST.add( rtDATA );
      gIntersection = true;
    }
    t2 = (-B + sqrtd) / (2 * A);
    if( tRayIT.range().inside(t2) )
    {
      rtDATA.setPoint (tFactor * t2);
      rtLIST.add( rtDATA );
      gIntersection = true;
    }
  }
  */
  return gIntersection;
}
void TQuadric::printDebug (const string& indent) const
{
  TObject::printDebug(indent);
  cerr << TDebug::Indent(indent)
       << "Function : "
       << QA << "X^2 + "
       << QB << "Y^2 + "
       << QC << "Z^2 + "
       << QD << "X*Y + "
       << QE << "X*Z + "
       << QF << "Y*Z + "
       << QG << "X + "
       << QH << "Y + "
       << QI << "Z + "
       << QJ
       << endl;
}

TScalar TQuadric::operator[](size_t index) const
{
  if(index < CQ_NUM_COEFS)
  {
    return coefs[index];
  }
  return TScalar(0);
}
void TQuadric::set_coef(size_t index, TScalar val)
{
  if(index < CQ_NUM_COEFS)
  {
    coefs[index] = val;
  }
}
void TQuadric::set_coefs(unsigned index, const TVector& values)
{
  for(unsigned i = index; (i < (index + 3)) && (i < CQ_NUM_COEFS); ++i)
  {
    coefs[i] = values[i - index];
  }
}

void TQuadric::set_coefs(const std::vector<TScalar>& values)
{
  //  cout << "set_coefs was given " << values.size() << " coefficients, but wanted " << CQ_NUM_COEFS << endl;
  
  for(unsigned i = 0; i < CQ_NUM_COEFS; ++i)
  {
    if( i < values.size() )
    {
      coefs[i] = values[i];
    }
    else
    {
      coefs[i] = TScalar(0);
    }
  }
}

TVector TQuadric::localNormal (const TVector& rktPOINT) const
{

  // This method is using the gradient of the generic quadric function as a
  // normal. 
  TVector retval;

  retval[0] = 2 * coefs[CQ_A] * rktPOINT.x() +
                  coefs[CQ_D] * rktPOINT.y() +
                  coefs[CQ_E] * rktPOINT.z() +
                  coefs[CQ_G];

  retval[1] =     coefs[CQ_D] * rktPOINT.x() +
              2 * coefs[CQ_B] * rktPOINT.y() +
                  coefs[CQ_F] * rktPOINT.z() +
                  coefs[CQ_H];

  retval[2] =     coefs[CQ_E] * rktPOINT.x() +
                  coefs[CQ_F] * rktPOINT.y() +
              2 * coefs[CQ_C] * rktPOINT.z() +
                  coefs[CQ_I];

  TScalar norm = retval.norm();
  if( norm < FX_EPSILON  )
  {
    // According to the comments in pov's quadrics.cpp, the normal is not
    // defined at this point, so they arbitrarily chose this vector:
    retval = TVector(1,0,0);
  }
  else
  {
    retval.normalize();
  }
  return retval;
}

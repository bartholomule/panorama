/*
*  Copyright (C) 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _CSG__
#define _CSG__

#include "hlapi/aggregate.h"

enum ECsgOp { FX_CSG_INTERSECTION, FX_CSG_UNION, FX_CSG_DIFFERENCE };

class TCsg : public TAggregate
{

  protected:

    ECsgOp   eOperation;

    void mergeUnion (TSpanList& rtLIST1, const TSpanList& rktLIST2, const TVector& rktRAY_DIR) const;
    void mergeIntersection (TSpanList& rtLIST1, const TSpanList& rktLIST2, const TVector& rktRAY_DIR) const;
    void mergeDifference (TSpanList& rtLIST1, const TSpanList& rktLIST2, const TVector& rktRAY_DIR) const;

    static map<ECsgOp,string> csg_type_strings;
    static vector<string> csg_type_choices;  
    static void generate_strings();
  
  public:

    TCsg();
    virtual ~TCsg();
  
    virtual void setOperation (ECsgOp eOP)
    {
      eOperation = eOP;
    }
  
    bool initialize (void);

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;  

    bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    string className (void) const { return "Csg"; }
    void printDebug (const string& indent) const;  

};  /* class TCsg */

#endif  /* _CSG__ */

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

#ifndef _ABVH__
#define _ABVH__

#include <list>
#include "hlapi/aggregate.h"
#include "hlapi/plugin_manager.h"

class TABVH : public TAggregate
{

  protected:

    struct TNode;

    mutable TNode*   ptTree;

    float costByMethod1 (TNode* ptTREE, TObject* ptOBJ);
    float costByMethod2 (TNode* ptTREE, TObject* ptOBJ);
    TNode* applyMethod1 (TNode* ptTREE, TObject* ptOBJ);
    TNode* applyMethod2 (TNode* ptTREE, TObject* ptOBJ);
    TNode* applyMethod3 (TNode* ptTREE, TObject* ptOBJ, float fINHERITANCE_COST, float fPARENT_BEST_COST);
    void insertObject (TObject* ptOBJ);
                       
  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    void initialize (void);

    bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    string className (void) const { return "ABVH"; }

};  /* class TABVH */


struct TABVH::TNode
{
  
  TVolume*       ptVolume;
  list<TNode*>   tChildList;
  float          fCost;

  TNode (TVolume* ptVOL, float fCOST)
  {
    ptVolume = ptVOL;
    fCost    = fCOST;
  }

  TBoundingBox boundingBox (void) const
  {
    if ( ptVolume->classType() == FX_OBJECT_CLASS )
    {
      return ((TObject*) ptVolume)->boundingBox();
    }

    return *((TBoundingBox*) ptVolume);
  }

  float cost (void) const
  {
    return fCost;
  }
  
  void addChild (TNode* ptNODE)
  {
    tChildList.push_back (ptNODE);
  }
  
  void addChild (TObject* ptOBJ)
  {
    tChildList.push_back (new TNode (ptOBJ, ptOBJ->boundingBox().cost()));
  }
  
};  // struct TNode

#endif  /* _ABVH__ */

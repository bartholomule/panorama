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
    typedef magic_pointer<TNode> node_ptr;

    mutable node_ptr   ptTree;

    float costByMethod1 (node_ptr ptTREE, magic_pointer<TObject> ptOBJ);
    float costByMethod2 (node_ptr ptTREE, magic_pointer<TObject> ptOBJ);
    node_ptr applyMethod1 (node_ptr ptTREE, magic_pointer<TObject> ptOBJ);
    node_ptr applyMethod2 (node_ptr ptTREE, magic_pointer<TObject> ptOBJ);
    node_ptr applyMethod3 (node_ptr ptTREE, magic_pointer<TObject> ptOBJ, float fINHERITANCE_COST, float fPARENT_BEST_COST);
    void insertObject (magic_pointer<TObject> ptOBJ);
                       
  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    bool initialize (void);

    bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    string className (void) const { return "ABVH"; }

};  /* class TABVH */


struct TABVH::TNode
{
  
  magic_pointer<TVolume> ptVolume;
  list<node_ptr >   tChildList;
  float          fCost;

  TNode (magic_pointer<TVolume> ptVOL, float fCOST)
  {
    ptVolume = ptVOL;
    fCost    = fCOST;
  }

  TBoundingBox boundingBox (void) const
  {
    if ( ptVolume->classType() == FX_OBJECT_CLASS )
    {
      return ((TObject*) ptVolume.get_pointer())->boundingBox();
    }

    return *rcp_static_cast<TBoundingBox>(ptVolume);
  }

  float cost (void) const
  {
    return fCost;
  }
  
  void addChild (node_ptr ptNODE)
  {
    tChildList.push_back (ptNODE);
  }
  
  void addChild (magic_pointer<TObject> ptOBJ)
  {
    tChildList.push_back ((node_ptr)new TNode (rcp_static_cast<TVolume>(ptOBJ), ptOBJ->boundingBox().cost()));
  }
  
};  // struct TNode

#endif  /* _ABVH__ */

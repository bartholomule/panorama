/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _AGGREGATE__
#define _AGGREGATE__

#include <vector>
#include "hlapi/class_manager.h"
#include "llapi/object.h"

typedef vector<TObject*>   TObjectList;

class TAggregate : public TObject
{

  protected:

    TObjectList   tObjectList;

  public:

    TAggregate (void) :
      TObject()
    {
      sCapabilities.gInfinite = false;
    }
      
    TAggregate (const TAggregate& rktAGGREGATE) :
      TObject (rktAGGREGATE)
    {
      copy (rktAGGREGATE.tObjectList);
      sCapabilities.gInfinite = rktAGGREGATE.capabilities().gInfinite;
    }

    TAggregate& operator = (const TAggregate& rktAGGREGATE)
    {
      if ( &rktAGGREGATE != this )
      {
        eraseList();
        copy (rktAGGREGATE.tObjectList);

        sCapabilities.gInfinite = rktAGGREGATE.capabilities().gInfinite;

        TObject::operator= (rktAGGREGATE);
      }

      return *this;
    }

    virtual void copy (const TObjectList& rktLIST)
    {
      for (TObjectList::const_iterator iter = rktLIST.begin(); ( iter != rktLIST.end() ); iter++)
      {
        tObjectList.push_back ((TObject*) TClassManager::_newObject ((*iter)->className(), (TObject*) (*iter)));
      }
    }
      
    virtual void eraseList (void)
    {
      for (TObjectList::iterator iter = tObjectList.begin(); ( iter != tObjectList.end() ); iter++)
      {
        //
        // Free the object to prevent a memory leak.
        // NOTE: I (KH) did NOT add a call to delete here, as I am not sure if
        //       it is safe to call it on the objects or not (do plugin manage
        //       returned objects have proper virtual destructors, and are they
        //       allocated with new?).  If someone knows the proper
        //       deallocation process, please fix this. (KH 16May2000)
        //
        // Angel has determined this to be safe (if people wrote their code
        // correctly), so I am going to make the change and avoid a memory
        // leak. (KH 04Aug2000)
        //
        delete *iter; 
      }

      //
      // Remove existing objects from the list to prevent nasty side effects.
      //
      tObjectList.erase (tObjectList.begin(), tObjectList.end());
    }

    virtual void add (TObject* ptOBJ)
    {
      if ( ptOBJ->capabilities().gInfinite == true )
      {
        sCapabilities.gInfinite = true;
      }
      tObjectList.push_back (ptOBJ);
    }

    void setMaterial (TMaterial* ptMATERIAL);
    void setObjectCode (size_t zCODE);
    void addFilter (const TObjectFilter* pktFILTER);

    void initialize (void);
    void finalize (void);

    bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    TVector normal (const TSurfaceData& rktDATA) const
    {
      return rktDATA.object()->normal (rktDATA);
    }

    TObjectList* objectList (void)
    {
      return &tObjectList;
    }

    void getMesh (list<TMesh*>& rtMESH_LIST) const
    {
      for (TObjectList::const_iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
      {
        (*tIter)->getMesh (rtMESH_LIST);
      }
    }
    
    void printDebug (void) const;

    EClass classType (void) const { return FX_AGGREGATE_CLASS; }
    string className (void) const { return "Aggregate"; }

};  /* class TAggregate */

#endif  /* _AGGREGATE__ */

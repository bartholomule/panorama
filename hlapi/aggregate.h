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

#ifndef PANORAMA_AGGREGATE_H_INCLUDED
#define PANORAMA_AGGREGATE_H_INCLUDED

#include <vector>
#include "hlapi/class_manager.h"
#include "llapi/object.h"
#include "generic/rc_pointer.hpp"

namespace panorama
{
  typedef std::vector<rc_pointer<TObject> > TObjectList;

  class TAggregate : public TObject
  {

  protected:

    TObjectList tObjectList;

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
        tObjectList.push_back(rc_pointer<Cloneable>((*iter)->clone_new()));
        // FIXME! If the above works, delete this commented line.
        //        tObjectList.push_back (rc_pointer<TObject>((TObject*)(TClassManager::_newObject ((*iter)->className(), (TObject*) &*(*iter)))));
      }
    }

    virtual void eraseList (void)
    {
      tObjectList.erase (tObjectList.begin(), tObjectList.end());
    }

    virtual void add (rc_pointer<TObject> ptOBJ)
    {
      if ( ptOBJ->capabilities().gInfinite == true )
      {
        sCapabilities.gInfinite = true;
      }
      tObjectList.push_back (ptOBJ);
    }

    void setMaterial (rc_pointer<TMaterial> ptMATERIAL);
    void setObjectCode (size_t zCODE);
    void addFilter (const rc_pointer<TObjectFilter> pktFILTER);

    bool initialize (void);
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

    bool containsObjects() const { return !tObjectList.empty(); }

    bool containsObject (const rc_pointer<TObject> pktObject);

    void getMesh (std::list<TMesh*>& rtMESH_LIST) const
    {
      for (TObjectList::const_iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
      {
        (*tIter)->getMesh (rtMESH_LIST);
      }
    }

    // Attribute management
    virtual AttributeErrorCode setAttribute (const std::string& rktNAME, Attribute nVALUE);
    virtual AttributeErrorCode getAttribute (const std::string& rktNAME, Attribute& rnVALUE);
    virtual void getAttributeList (TAttributeList& rtLIST) const;

    EClass classType (void) const { return FX_AGGREGATE_CLASS; }
    std::string name (void) const { return "Aggregate"; }
    virtual std::string internalMembers(const Indentation& indent, StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE ) const;
    virtual TUserFunctionMap getUserFunctions();

  };  /* class TAggregate */
}

#endif  /* PANORAMA_AGGREGATE_H_INCLUDED */

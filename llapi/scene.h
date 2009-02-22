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

#ifndef _SCENE__
#define _SCENE__

#include <string>
#include <list>
#include <vector>
#include <map>
#include "llapi/image.h"
#include "llapi/camera.h"
#include "llapi/light.h"
#include "llapi/renderer.h"
#include "llapi/image_filter.h"
#include "llapi/atmosphere.h"
#include "llapi/pattern.h"
#include "llapi/surface_data.h"
#include "llapi/image_io.h"
#include "generic/rc_pointer.hpp"

namespace panorama
{

  struct SBuffers
  {

    TImage*     ptImage;
    TZBuffer*   ptZBuffer;
    TNBuffer*   ptNBuffer;

    SBuffers (void) :
      ptImage (NULL),
      ptZBuffer (NULL),
      ptNBuffer (NULL) {}

  };  /* struct SBuffers */


  typedef std::vector<rc_pointer<TObject> > TObjectArray;

  class TScene : public TProcedural
  {

  private:

    rc_pointer<TObject> ptWorld;
    rc_pointer<TCamera> ptCamera;
    rc_pointer<TRenderer> ptRenderer;
    rc_pointer<TMaterial> ptDefaultMaterial;
    TAtmosphere tAtmosphere;
    bool gParticipatingMedia;
    Word wNeededBuffers;
    size_t zWidth;
    size_t zHeight;
    SBuffers sBuffers;
    rc_pointer<TPattern> ptBackgroundColor;
    std::vector<rc_pointer<TLight> > tLightList;
    TObjectArray tAreaLightList;
    std::list<rc_pointer<TImageFilter> > tFilterList;
    rc_pointer<TImageIO> ptImageIO;
    TProgram tGlobalData;

    bool recursiveLocateLights(rc_pointer<TObject> obj, TObjectArray& light_manip_list, bool addlights = true);

  public:

    TScene (void);

    TColor backgroundColor (const TSurfaceData& rktDATA) const { return ptBackgroundColor->color (rktDATA); }
    rc_pointer<TCamera> camera (void) const { return ptCamera; }
    rc_pointer<TObject> world (void) const { return ptWorld; }
    std::vector<rc_pointer<TLight> >& lightList (void) { return tLightList; }
    std::vector<rc_pointer<TObject> >& areaLightList (void) { return tAreaLightList; }
    SBuffers* buffers (void) { return &sBuffers; }
    Word neededBuffers (void) const { return wNeededBuffers; }
    bool participatingMedia (void) const { return gParticipatingMedia; }
    rc_pointer<TRenderer> renderer (void) { return ptRenderer; }
    TAtmosphere* atmosphere (void) { return &tAtmosphere; }
    rc_pointer<TImageIO> imageIO (void) { return ptImageIO; }
    TProgram* globalData (void) { return &tGlobalData; }

    AttributeErrorCode setAttribute (const std::string& rktNAME, Attribute nVALUE);
    AttributeErrorCode getAttribute (const std::string& rktNAME, Attribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setBackgroundColor (rc_pointer<TPattern> ptPATTERN) { ptBackgroundColor = ptPATTERN; }
    void setWorld (rc_pointer<TObject> ptWORLD) { ptWorld = ptWORLD; }
    void setCamera (rc_pointer<TCamera> ptCAMERA) { ptCamera = ptCAMERA; }
    void addObject(rc_pointer<TObject> ptOBJECT);
    void addLight (rc_pointer<TLight> ptLIGHT);
    void addAreaLight (rc_pointer<TObject> ptLIGHT);
    void setRenderer (rc_pointer<TRenderer> ptRENDERER) { ptRenderer = ptRENDERER; }
    void setImageOutput (rc_pointer<TImageIO> ptIMAGE_IO) { ptImageIO = ptIMAGE_IO; }
    void setParticipatingMedia (bool gACTIVE) { gParticipatingMedia = gACTIVE; }
    void addImageFilter (rc_pointer<TImageFilter> ptFILTER);
    void setOutputFileName (const std::string& rktNAME);

    void setWidth (size_t zWIDTH)
    {
      if( zWidth != zWIDTH )
      {
        destroy_buffers();

        zWidth = zWIDTH;

        if( (zWidth > 0) && (zHeight > 0) )
        {
          create_buffers();
        }
      }
    }

    void setHeight (size_t zHEIGHT)
    {
      if( zHeight != zHEIGHT )
      {
        destroy_buffers();

        zHeight = zHEIGHT;

        if( (zWidth > 0) && (zHeight > 0) )
        {
          create_buffers();
        }
      }
    }

    void addBuffer (Word wBUFFER)
    {
      wNeededBuffers |= wBUFFER;
    }

    bool create_buffers(void);
    bool destroy_buffers (void);
    bool initialize (void);
    bool finalize (void);
    bool render (TUserFunction* pfUSER = NULL, void* pvDATA = NULL);
    bool postprocess (void);
    bool saveImage (void);

    EClass classType (void) const { return FX_SCENE_CLASS; }
    virtual std::string name (void) const { return "Scene"; }
    virtual std::string internalMembers(const Indentation& indent, StringDumpable::PrefixType prefix) const;
    virtual TUserFunctionMap getUserFunctions();
  };  /* class TScene */
} // end namespace panorama


#endif  /* _RT_SCENE__ */

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
#include "generic/magic_pointer.h"

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


typedef vector<TObject*> TObjectVector;



class TScene : public TProcedural
{

  protected:

    magic_pointer<TObject>   ptWorld;
    magic_pointer<TCamera>   ptCamera;
    magic_pointer<TRenderer> ptRenderer;
    magic_pointer<TMaterial> ptDefaultMaterial;
    TAtmosphere           tAtmosphere;
    bool                  gParticipatingMedia;
    Word                  wNeededBuffers;
    size_t                zWidth;
    size_t                zHeight;
    SBuffers              sBuffers;
    magic_pointer<TPattern> ptBackgroundColor;
    vector<TLight*>       tLightList;
    vector<TObject*>      tAreaLightList;    
    list<TImageFilter*>   tFilterList;
    magic_pointer<TImageIO>  ptImageIO;
    TProgram              tGlobalData;

    bool recursiveLocateLights(TObject* obj, TObjectVector& light_manip_list, bool addlights = true);
  
  public:

    TScene (void);

    TColor backgroundColor (const TSurfaceData& rktDATA) const { return ptBackgroundColor->color (rktDATA); }
    magic_pointer<TCamera> camera (void) const { return ptCamera; }
    magic_pointer<TObject> world (void) const { return ptWorld; }
    vector<TLight*>& lightList (void) { return tLightList; }
    vector<TObject*>& areaLightList (void) { return tAreaLightList; }  
    SBuffers* buffers (void) { return &sBuffers; }
    Word neededBuffers (void) const { return wNeededBuffers; }
    bool participatingMedia (void) const { return gParticipatingMedia; }
    magic_pointer<TRenderer> renderer (void) { return ptRenderer; }
    TAtmosphere* atmosphere (void) { return &tAtmosphere; }
    magic_pointer<TImageIO> imageIO (void) { return ptImageIO; }
    TProgram* globalData (void) { return &tGlobalData; }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setBackgroundColor (magic_pointer<TPattern> ptPATTERN) { ptBackgroundColor = ptPATTERN; }
    void setWorld (magic_pointer<TObject> ptWORLD) { ptWorld = ptWORLD; }
    void setCamera (magic_pointer<TCamera> ptCAMERA) { ptCamera = ptCAMERA; }
    void addObject(magic_pointer<TObject> ptOBJECT);
    void addLight (TLight* ptLIGHT);
    void addAreaLight (TObject* ptLIGHT);
    void setRenderer (magic_pointer<TRenderer> ptRENDERER) { ptRenderer = ptRENDERER; }
    void setImageOutput (magic_pointer<TImageIO> ptIMAGE_IO) { ptImageIO = ptIMAGE_IO; }
    void setParticipatingMedia (bool gACTIVE) { gParticipatingMedia = gACTIVE; }
    void addImageFilter (TImageFilter* ptFILTER);
    void setOutputFileName (const string& rktNAME);

    void setWidth (size_t zWIDTH)
    {
      zWidth = zWIDTH;

      if ( !sBuffers.ptImage )
      {
	create_buffers();
      }
    }
    
    void setHeight (size_t zHEIGHT)
    {
      zHeight = zHEIGHT;
      
      if ( !sBuffers.ptImage )
      {
	create_buffers();
      }
    }

    void addBuffer (Word wBUFFER)
    {
      wNeededBuffers |= wBUFFER;
    }

    bool create_buffers(void);
    bool initialize (void);
    bool finalize (void);
    bool render (TUserFunction* pfUSER = NULL, void* pvDATA = NULL);
    bool postprocess (void);
    bool saveImage (void);

    void printDebug (const string& indent) const;

    EClass classType (void) const { return FX_SCENE_CLASS; }
    string className (void) const { return "Scene"; }
    virtual TUserFunctionMap getUserFunctions();  

};  /* class TScene */


#endif  /* _RT_SCENE__ */

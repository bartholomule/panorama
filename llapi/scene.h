/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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
#include "llapi/image_io.h"

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


class TScene : public TBaseClass
{

  protected:

    TObject*              ptWorld;
    TCamera*              ptCamera;
    TRenderer*            ptRenderer;
    TAtmosphere           tAtmosphere;
    bool                  gParticipatingMedia;
    Word                  wNeededBuffers;
    size_t                zWidth;
    size_t                zHeight;
    SBuffers              sBuffers;
    TColor                tBackgroundColor;
    vector<TLight*>       tLightList;
    list<TImageFilter*>   tFilterList;
    TImageIO*             ptImageIO;

  public:

    static string   _tIncludePath;

    TScene (void);

    TColor backgroundColor (void) const { return tBackgroundColor; }
    TCamera* camera (void) const { return ptCamera; }
    TObject* world (void) const { return ptWorld; }
    vector<TLight*>& lightList (void) { return tLightList; }
    SBuffers* buffers (void) { return &sBuffers; }
    Word neededBuffers (void) const { return wNeededBuffers; }
    bool participatingMedia (void) const { return gParticipatingMedia; }
    TRenderer* renderer (void) { return ptRenderer; }
    TAtmosphere* atmosphere (void) { return &tAtmosphere; }
    TImageIO* imageIO (void) { return ptImageIO; }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setBackgroundColor (const TColor& rktCOLOR) { tBackgroundColor = rktCOLOR; }
    void setWorld (TObject* ptWORLD) { ptWorld = ptWORLD; }
    void setCamera (TCamera* ptCAMERA) { ptCamera = ptCAMERA; }
    void addLight (TLight* ptLIGHT) { tLightList.push_back (ptLIGHT); }
    void setRenderer (TRenderer* ptRENDERER) { ptRenderer = ptRENDERER; }
    void setImageOutput (TImageIO* ptIMAGE_IO) { ptImageIO = ptIMAGE_IO; }
    void setParticipatingMedia (bool gACTIVE) { gParticipatingMedia = gACTIVE; }
    void addImageFilter (TImageFilter* ptFILTER);
    void setOutputFileName (const string& rktNAME);

    void setWidth (size_t zWIDTH)
    {
      if ( !sBuffers.ptImage )
      {
        zWidth = zWIDTH;
      }
    }
    
    void setHeight (size_t zHEIGHT)
    {
      if ( !sBuffers.ptImage )
      {
        zHeight = zHEIGHT;
      }
    }

    void addBuffer (Word wBUFFER)
    {
      wNeededBuffers |= wBUFFER;
    }
                    
    bool initialize (void);
    bool finalize (void);
    bool render (TUserFunction* pfUSER = NULL, void* pvDATA = NULL);
    bool postprocess (void);
    bool saveImage (void);

    void printDebug (void) const;

    EClass classType (void) const { return FX_SCENE_CLASS; }
    string className (void) const { return "Scene"; }

};  /* class TScene */

#endif  /* _RT_SCENE__ */

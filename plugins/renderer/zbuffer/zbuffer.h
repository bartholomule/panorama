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

#ifndef _ZBUFFER__
#define _ZBUFFER__

#include "llapi/renderer.h"
#include "hlapi/plugin_manager.h"
#include "plugins/renderer/raytracer/raytracer.h"

enum EShading
{

  FX_CONSTANT,
  FX_GOURAUD,
  FX_PHONG

};  /* enum EShading */

struct TVertexData
{

  TVector    tPoint;
  TVector2   tCoord;
  TVector    tNormal;
  TColor     tColor;
  TScalar    tDepth;

};  /* struct TVertexData */


class TZBufferRenderer : public TRaytracer
{

  protected:

    bool       gBackfaceCulling;
    EShading   eShading;

    void initBuffers (SBuffers& rsBUFFERS) const;
    void renderHalfTriangle (SBuffers& rsBUFFERS,
                             TMesh::TFace* ptFACE,
                             TVertexData& rtVERTEX1,
                             TVertexData& rtVERTEX2,
                             TVertexData& rtVERTEX3,
                             TVertexData& rtVERTEX4) const;
    void sortVertices (TVertexData atVERTEX [3]) const;
    TColor getRadiance (TSurfaceData& rtDATA, Word wDEPTH) const;
    void calculateIllumination (list<TMesh*>& rtMESH_LIST) const;
    
  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TZBufferRenderer (void) :
      TRaytracer(),
      gBackfaceCulling (true),
      eShading (FX_PHONG) {}

    void initialize (TScene& rtSCENE);
    void finalize (void);

    void render (SBuffers& rsBUFFERS);

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    TColor directLight (const TSurfaceData& rktDATA) const;
    TColor directLight (const TSurfaceData& rktDATA, const TLight* pktLIGHT) const;
    TColor specularReflectedLight (const TSurfaceData& rktDATA, Word wDEPTH, size_t* pzOBJ_CODE = NULL) const;
    TColor specularTransmittedLight (const TSurfaceData& rktDATA, Word wDEPTH, size_t* pzOBJ_CODE = NULL) const;

    Word neededBuffers (void) const { return FX_ZBUFFER; }
    
    string className (void) const { return "ZBufferRenderer"; }

    void printDebug (void) const;
    
};  /* class TZBufferRenderer */

#endif  /* _ZBUFFER__ */

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

#include "llapi/mesh.h"
#include "llapi/camera.h"
#include "llapi/material.h"
#include "zbuffer.h"

DEFINE_PLUGIN ("ZBufferRenderer", FX_RENDERER_CLASS, TZBufferRenderer);

bool TZBufferRenderer::initialize (TScene& rtSCENE)
{

  bool result = TRaytracer::initialize (rtSCENE);

  // >>>>>>>>>>>>>> Front to back ordering

  return result;
  
}  /* initialize() */


void TZBufferRenderer::finalize (void)
{

}  /* finalize() */


int TZBufferRenderer::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "backface" )
  {
    if ( eTYPE == FX_BOOL )
    {
      gBackfaceCulling = nVALUE.gValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "shading" )
  {
    if ( eTYPE == FX_STRING )
    {
      string   tName = (char*) nVALUE.pvValue;
      if ( tName == "constant" )
      {
        eShading = FX_CONSTANT;
      }
      else if ( tName == "gouraud" )
      {
        eShading = FX_GOURAUD;
      }
      else if ( tName == "phong" )
      {
        eShading = FX_PHONG;
      }
      else
      {
        TProcedural::_tUserErrorMessage = "unknown shading method : " + tName;

        return FX_ATTRIB_USER_ERROR;
      }
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TRaytracer::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TZBufferRenderer::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "backface" )
  {
    rnVALUE.gValue = gBackfaceCulling;
  }
  else
  {
    return TRaytracer::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TZBufferRenderer::getAttributeList (TAttributeList& rtLIST) const
{

  TRaytracer::getAttributeList (rtLIST);

  rtLIST ["backface"] = FX_BOOL;
  rtLIST ["shading"]  = FX_STRING;  

}  /* getAttributeList() */


void TZBufferRenderer::initBuffers (SBuffers& rsBUFFERS) const
{
  TRay          tRay;
  TSurfaceData  tData;
  TVector       tDirection;
  TVector       tNormal;

  for (size_t J = 0; ( J < rsBUFFERS.ptImage->height() ) ;J++)
  {
    for (size_t I = 0; ( I < rsBUFFERS.ptImage->width() ) ;I++)
    {
      ptScene->camera()->getRay(I, J, tRay);

      tDirection = tRay.direction();

      tData.setPoint (tDirection);

      tNormal = -tDirection;
      tNormal.normalize();

      tData.setNormal (tNormal);

      rsBUFFERS.ptImage->setPixel (I, J, ptScene->backgroundColor(tData));
      rsBUFFERS.ptZBuffer->setPixel (I, J, SCALAR_MAX);
    }
  }
  
}  /* initBuffers() */


void TZBufferRenderer::renderHalfTriangle (SBuffers& rsBUFFERS,
                                           TMesh::TFace* ptFACE,
                                           TVertexData& rtVERTEX1,
                                           TVertexData& rtVERTEX2,
                                           TVertexData& rtVERTEX3,
                                           TVertexData& rtVERTEX4) const
{

  TSurfaceData   tSurfaceData;
  TColor         tColor;
  TScalar        tSignX;
  TScalar        X1, X2;
  TScalar        tDeltaX;
  TScalar        D1, D2;
  TScalar        tDeltaD;
  TVector        P1, P2;
  TVector        tDeltaP;
  TVector        N1, N2;
  TVector        tDeltaN;
  TColor         C1, C2;
  TColor         tDeltaC;
  TScalar        t1, t2;
  bool           gPoint     = ( ( eShading == FX_CONSTANT ) || ( eShading == FX_PHONG ) );
  bool           gNormal    = ( ( eShading == FX_PHONG ) || rsBUFFERS.ptNBuffer );
  bool           gColor     = ( eShading == FX_GOURAUD );
  TScalar        tDelta1    = 1.0 / (rtVERTEX2.tCoord.y() - rtVERTEX1.tCoord.y());
  TScalar        tDelta2    = 1.0 / (rtVERTEX4.tCoord.y() - rtVERTEX3.tCoord.y());
  TScalar        tScanStart = ceil (rtVERTEX1.tCoord.y());
  TScalar        tScanEnd   = (( rtVERTEX2.tCoord.y() == floor (rtVERTEX2.tCoord.y()) ) ?
                               rtVERTEX2.tCoord.y() - 1 :
                               floor (rtVERTEX2.tCoord.y()));

  tSurfaceData.setup (ptFACE->pktObject, TRay());

  t1 = (tScanStart - rtVERTEX1.tCoord.y()) * tDelta1;
  t2 = (tScanStart - rtVERTEX3.tCoord.y()) * tDelta2;
  
  for (TScalar tScanline = tScanStart; ( tScanline <= tScanEnd ) ;tScanline++)
  {
    X1 = lerp (rtVERTEX1.tCoord.x(), rtVERTEX2.tCoord.x(), t1);
    X2 = lerp (rtVERTEX3.tCoord.x(), rtVERTEX4.tCoord.x(), t2);

    if ( X1 <= X2 )
    {
      X1 = ceil (X1);
      if ( X2 == floor (X2) )
      {
        X2--;
      }
      else
      {
        X2 = floor (X2);
      }
      if ( X1 > X2 )
      {
        t1 += tDelta1;
        t2 += tDelta2;
        continue;
      }
    }
    else
    {
      X2 = ceil (X2);
      if ( X1 == floor (X1) )
      {
        X1--;
      }
      else
      {
        X1 = floor (X1);
      }
      if ( X2 > X1 )
      {
        t1 += tDelta1;
        t2 += tDelta2;
        continue;
      }
    }
    
    tSignX  = sign (X2 - X1);
    tDeltaX = fabs (X2 - X1);

    D1      = lerp (rtVERTEX1.tDepth, rtVERTEX2.tDepth, t1);
    D2      = lerp (rtVERTEX3.tDepth, rtVERTEX4.tDepth, t2);
    tDeltaD = (D2 - D1) / tDeltaX;

    if ( gPoint )
    {
      P1      = lerp (rtVERTEX1.tPoint, rtVERTEX2.tPoint, t1);
      P2      = lerp (rtVERTEX3.tPoint, rtVERTEX4.tPoint, t2);
      tDeltaP = (P2 - P1) / tDeltaX;
    }

    if ( gColor )
    {
      C1      = lerp (rtVERTEX1.tColor, rtVERTEX2.tColor, t1);
      C2      = lerp (rtVERTEX3.tColor, rtVERTEX4.tColor, t2);
      tDeltaC = (C2 - C1) / tDeltaX;
    }

    if ( gNormal )
    {
      N1      = lerp (rtVERTEX1.tNormal, rtVERTEX2.tNormal, t1);
      N2      = lerp (rtVERTEX3.tNormal, rtVERTEX4.tNormal, t2);
      tDeltaN = (N2 - N1) / tDeltaX;
    }

    for (TScalar I = X1; ( fabs (I - X1) <= fabs (X2 - X1) ) ;I += tSignX)
    {
      if ( D1 < rsBUFFERS.ptZBuffer->getPixel (I, tScanline) )
      {
        if ( eShading == FX_CONSTANT )
        {
          tSurfaceData.setPoint (P1);
          tSurfaceData.setNormal (ptFACE->tNormal);

          tColor = getRadiance (tSurfaceData, 0);
        }
        else if ( eShading == FX_GOURAUD )
        {
          tColor = C1;
        }
        else if ( eShading == FX_PHONG )
        {
          N1.normalize();

          tSurfaceData.setPoint (P1);
          tSurfaceData.setNormal (N1);

          tColor = getRadiance (tSurfaceData, 0);
        }

        rsBUFFERS.ptImage->setPixel (I, tScanline, tColor);
        rsBUFFERS.ptZBuffer->setPixel (I, tScanline, D1);

        if ( rsBUFFERS.ptNBuffer )
        {
          rsBUFFERS.ptNBuffer->setPixel (I, tScanline, N1);
        }
      }

      // Span line covers only one pixel
      if ( tSignX == 0 )
      {
        break;
      }
      
      D1 += tDeltaD;

      if ( gPoint )
      {
        P1 += tDeltaP;
      }
      if ( gColor )
      {
        C1 += tDeltaC;
      }
      if ( gNormal )
      {
        N1 += tDeltaN;
      }
    }
    
    t1 += tDelta1;
    t2 += tDelta2;
  }

}  /* renderHalfTriangle() */


void TZBufferRenderer::sortVertices (TVertexData atVERTEX [3]) const
{

  TVertexData   tTmpVertex;

  if ( atVERTEX[1].tCoord.y() < atVERTEX[0].tCoord.y() )
  {
    tTmpVertex   = atVERTEX [0];
    atVERTEX [0] = atVERTEX [1];
    atVERTEX [1] = tTmpVertex;
  }

  if ( atVERTEX[2].tCoord.y() < atVERTEX[0].tCoord.y() )
  {
    tTmpVertex   = atVERTEX [0];
    atVERTEX [0] = atVERTEX [2];
    atVERTEX [2] = tTmpVertex;
  }

  if ( atVERTEX[2].tCoord.y() < atVERTEX[1].tCoord.y() )
  {
    tTmpVertex   = atVERTEX [1];
    atVERTEX [1] = atVERTEX [2];
    atVERTEX [2] = tTmpVertex;
  }

}  /* sortVertices() */


TColor TZBufferRenderer::getRadiance (TSurfaceData& rtDATA, Word wDEPTH) const
{

  TColor tRadiance;
  
  tRadiance = ambientLight (rtDATA, wDEPTH) + directLight (rtDATA);

  for (list<const TObjectFilter*>::const_iterator tIter = rtDATA.object()->filterList().begin(); ( tIter != rtDATA.object()->filterList().end() ) ;tIter++)
  {
    tRadiance = (*tIter)->filterRadiance (rtDATA, tRadiance);
  }

  return tRadiance;
  
}  /* getRadiance() */


void TZBufferRenderer::calculateIllumination (list<TMesh*>& rtMESH_LIST) const
{

  TSurfaceData      tSurfaceData;
  TMesh*            ptMesh;
  TMesh::TVertex*   ptVertex;

  for (list<TMesh*>::iterator tIterMesh = rtMESH_LIST.begin(); ( tIterMesh != rtMESH_LIST.end() ) ;tIterMesh++)
  {
    ptMesh = (*tIterMesh);

    for (vector<TMesh::TVertex>::iterator tIter = ptMesh->vertexList()->begin(); ( tIter != ptMesh->vertexList()->end() ) ;tIter++)
    {
      ptVertex = &(*tIter);

      tSurfaceData.setup (ptMesh->face (ptVertex->tFaceList.front()).pktObject, TRay());
      tSurfaceData.setPoint (ptVertex->tPoint);
      tSurfaceData.setNormal (ptVertex->tNormal);

      ptVertex->tColor = getRadiance (tSurfaceData, 0);
    }
  }
  
}  /* calculateIllumination() */


void TZBufferRenderer::render (SBuffers& rsBUFFERS)
{

  TMesh*           ptMesh;
  list<TMesh*>     tMeshList;
  TMesh::TFace*    ptFace;
  TMesh::TVertex   atVertex [3];
  TVertexData      atVertexData [3];

  initBuffers (rsBUFFERS);
  
  ptScene->world()->getMesh (tMeshList);

  cout << "Meshes : " << tMeshList.size() << endl;

  // For every mesh, set the normal of each vertex to the mean of adjacent triangle normals.
  for (list<TMesh*>::iterator tIter = tMeshList.begin(); ( tIter != tMeshList.end() ) ;tIter++)
  {
    (*tIter)->calculateVertexNormals();
  }

  if ( eShading == FX_GOURAUD )
  {
    calculateIllumination (tMeshList);
  }
  
  for (list<TMesh*>::iterator tIterMesh = tMeshList.begin(); ( tIterMesh != tMeshList.end() ) ;tIterMesh++)
  {
    ptMesh = (*tIterMesh);

    for (vector<TMesh::TFace>::iterator tIter = ptMesh->faceList()->begin(); ( tIter != ptMesh->faceList()->end() ) ;tIter++)
    {
      ptFace = &(*tIter);
  
      atVertex [0] = ptMesh->vertex (ptFace->azVertex[0]);
      atVertex [1] = ptMesh->vertex (ptFace->azVertex[1]);
      atVertex [2] = ptMesh->vertex (ptFace->azVertex[2]);
  
      // Back-face culling
      if ( gBackfaceCulling )
      {
        if ( dotProduct (ptFace->tNormal, ptScene->camera()->location()) < -ptFace->D )
        {
          continue;
        }
      }
  
      // Fill vertex data array
      atVertexData[0].tPoint = atVertex[0].tPoint;
      atVertexData[1].tPoint = atVertex[1].tPoint;
      atVertexData[2].tPoint = atVertex[2].tPoint;
      
      ptScene->camera()->getPlaneProjection (atVertex[0].tPoint, atVertexData[0].tCoord);
      ptScene->camera()->getPlaneProjection (atVertex[1].tPoint, atVertexData[1].tCoord);
      ptScene->camera()->getPlaneProjection (atVertex[2].tPoint, atVertexData[2].tCoord);
  
      /*
      atVertexData[0].tDepth = Distance (ptScene->camera()->location(), atVertex[0].tPoint);
      atVertexData[1].tDepth = Distance (ptScene->camera()->location(), atVertex[1].tPoint);
      atVertexData[2].tDepth = Distance (ptScene->camera()->location(), atVertex[2].tPoint);
      */

      atVertexData[0].tDepth = ptScene->camera()->getZ (atVertex[0].tPoint);
      atVertexData[1].tDepth = ptScene->camera()->getZ (atVertex[1].tPoint);
      atVertexData[2].tDepth = ptScene->camera()->getZ (atVertex[2].tPoint);
      
      if ( eShading == FX_GOURAUD )
      {
        atVertexData[0].tColor = atVertex[0].tColor;
        atVertexData[1].tColor = atVertex[1].tColor;
        atVertexData[2].tColor = atVertex[2].tColor;
      }
      else if ( eShading == FX_PHONG )
      {
        atVertexData[0].tNormal = atVertex[0].tNormal;
        atVertexData[1].tNormal = atVertex[1].tNormal;
        atVertexData[2].tNormal = atVertex[2].tNormal;
      }

      sortVertices (atVertexData);

      if ( fabs (atVertexData[0].tCoord.y() - atVertexData[1].tCoord.y()) > FX_EPSILON )
      {
        renderHalfTriangle (rsBUFFERS, ptFace, atVertexData[0], atVertexData[1], atVertexData[0], atVertexData[2]);
      }

      if ( fabs (atVertexData[1].tCoord.y() - atVertexData[2].tCoord.y()) > FX_EPSILON )
      {
        renderHalfTriangle (rsBUFFERS, ptFace, atVertexData[1], atVertexData[2], atVertexData[0], atVertexData[2]);
      }
    }
  }

  for (list<TMesh*>::iterator tIter2 = tMeshList.begin(); ( tIter2 != tMeshList.end() ) ;tIter2++)
  {
    delete (*tIter2);
  }
  
}  /* render() */


TColor TZBufferRenderer::directLight (const TSurfaceData& rktDATA) const
{

  const TLight* ptLight;
  TColor        tTotalRadiance;
    
  for (vector<TLight*>::const_iterator tIter = ptScene->lightList().begin(); ( tIter != ptScene->lightList().end() ) ;tIter++)
  {
    ptLight         = *tIter;
    tTotalRadiance += directLight (rktDATA, ptLight);
  }

  for (vector<TObject*>::const_iterator tIter = ptScene->areaLightList().begin(); ( tIter != ptScene->areaLightList().end() ) ;tIter++)
  {
    TObject* ptObject = *tIter;
    tTotalRadiance += directLight (rktDATA, ptObject);
  }  

  return tTotalRadiance;

}  /* directLight() */


TColor TZBufferRenderer::directLight (const TSurfaceData& rktDATA, const TLight* pktLIGHT) const
{

  TScalar   tCosNL;
  TColor    rho;
  TColor    tTotalRadiance;
  TColor    tRadiance;
  TVector   tDirection;
  
  if ( pktLIGHT->shadow() && pktLIGHT->raytraced() )
  {
    return TRaytracer::directLight (rktDATA, pktLIGHT);
  }
  
  tDirection = pktLIGHT->location() - rktDATA.point();

  tDirection.normalize();

  if ( rktDATA.object() )
  {
    tCosNL = dotProduct (rktDATA.normal(), tDirection);
  
    if ( tCosNL > 0 )
    {
      tRadiance      = pktLIGHT->color (rktDATA.point());
      rho            = rktDATA.object()->material()->bsdf()->evaluateReflection (rktDATA, tDirection, tCosNL, tRadiance);
      tTotalRadiance = tRadiance * rho;
    }
  }
  else
  {
    tTotalRadiance = pktLIGHT->color (rktDATA.point());
  }

  return tTotalRadiance;
  
}  /* directLight() */

TColor TZBufferRenderer::directLight (const TSurfaceData& rktDATA, const TObject* pktALIGHT) const
{

  // [_FIXME_]
  // This should be fixed sometime to do some calculation instead of passing it
  // on. 
  return TRaytracer::directLight (rktDATA, pktALIGHT);

}  /* directLight() */



TColor TZBufferRenderer::specularReflectedLight (const TSurfaceData& rktDATA, Word wDEPTH, size_t* pzOBJ_CODE) const
{

  return TColor::_null();

}  /* specularReflectedLight() */


TColor TZBufferRenderer::specularTransmittedLight (const TSurfaceData& rktDATA, Word wDEPTH, size_t* pzOBJ_CODE) const
{

  return TColor::_null();

}  /* specularTransmittedLight() */


void TZBufferRenderer::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_ZBufferRenderer_]" << endl;

  TDebug::_push();

  cerr << TDebug::_indent() << "Ambient light : "; tAmbientLight.printDebug();

  TDebug::_pop();
  
}  /* printDebug() */

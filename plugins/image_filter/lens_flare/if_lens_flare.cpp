/*
*  Copyright (C) 1999 Jon Frydensbjerg
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

#include "llapi/scene.h"
#include "llapi/gradient.h"
#include "if_lens_flare.h"
#include "flare.h"
#include "flare_std.h"
#include "flare_hard.h"
#include "flare_decreasing.h"
#include "flare_ring.h"
#include "flare_halo.h"
#include "flare_streaks.h"

DEFINE_PLUGIN ("IF_Lens_Flare", FX_IMAGE_FILTER_CLASS, TIF_Lens_Flare);

TIF_Lens_Flare::TIF_Lens_Flare (void) :
  TImageFilter(),
  eType (FX_NORMAL),
  eForm (FX_CIRCLE),
  fScale (0.65),
  fThreshold (0.8),
  fIntensity (1.6),
  fInfluence (2.2),
  gArtefacts (true)
{

}  /* TIF_Cartoon() */


void TIF_Lens_Flare::generateNearFlares (void)
{

  float  fPosition;

  //
  // Equals a 105 mm lens flare
  // 

  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Std  (TColor(1.00f, 1.00f, 1.00f), eForm, fScale * 0.058f, -1.000f, ptCurrentImage);
  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Std  (TColor(0.92f, 0.92f, 0.84f), eForm, fScale * 0.088f, -1.000f, ptCurrentImage);
  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Std  (TColor(0.52f, 0.50f, 1.00f), eForm, fScale * 0.180f, -1.000f, ptCurrentImage);
  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Std  (TColor(0.45f, 0.47f, 0.46f), eForm, fScale * 0.500f, -1.000f, ptCurrentImage);
  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Halo (TColor(0.14f, 0.04f, 0.04f), eForm, fScale * 0.092f, -1.000f, 0.02f, ptCurrentImage);

  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Hard       (TColor(0.059f, 0.314f, 0.157f), eForm, fScale * 0.010f, -2.200f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Std        (TColor(0.549f, 0.451f, 0.000f), eForm, fScale * 0.009f, -2.230f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Hard       (TColor(0.020f, 0.196f, 0.196f), eForm, fScale * 0.004f, -2.260f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.043f, 0.024f, 0.024f), eForm, fScale * 0.370f, -1.580f, 0.045f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.004f, 0.039f, 0.039f), eForm, fScale * 0.085f, -1.370f, 0.045f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Ring       (TColor(0.004f, 0.063f, 0.051f), eForm, fScale * 0.030f, -0.750f, 0.120f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Hard       (TColor(0.239f, 0.235f, 0.039f), eForm, fScale * 0.007f, -0.370f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.000f, 0.020f, 0.020f), eForm, fScale * 0.040f, -0.230f, 0.045f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.000f, 0.063f, 0.094f), eForm, fScale * 0.008f, -0.100f, 0.045f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.000f, 0.122f, 0.118f), eForm, fScale * 0.003f, -0.080f, 0.045f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.047f, 0.039f, 0.023f), eForm, fScale * 0.210f,  0.450f, 0.045f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.031f, 0.031f, 0.000f), eForm, fScale * 0.105f,  0.450f, 0.045f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.000f, 0.023f, 0.000f), eForm, fScale * 0.020f,  0.450f, 0.045f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Std        (TColor(0.510f, 0.510f, 0.137f), eForm, fScale * 0.009f,  0.510f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Ring       (TColor(0.008f, 0.031f, 0.000f), eForm, fScale * 0.020f,  0.535f, 0.120f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.431f, 0.353f, 0.196f), eForm, fScale * 0.015f,  1.050f, 0.045f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Hard       (TColor(0.471f, 0.471f, 0.667f), eForm, fScale * 0.010f,  1.080f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.027f, 0.027f, 0.000f), eForm, fScale * 0.043f,  1.095f, 0.045f, ptCurrentImage);

  fPosition = 1.24;

  for (size_t I = 0; ( I < 3 ) ;I++)
  {
    aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Hard       (TColor(0.067f, 0.173f, 0.215f), eForm, fScale * 0.012f, fPosition, ptCurrentImage);

    fPosition += 0.034;
  }

  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Hard       (TColor(0.008f, 0.000f, 0.275f), eForm, fScale * 0.026f,  1.276f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Hard       (TColor(0.549f, 0.431f, 0.275f), eForm, fScale * 0.005f,  1.276f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.027f, 0.047f, 0.016f), eForm, fScale * 0.075f,  1.720f, 0.045f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.075f, 0.047f, 0.047f), eForm, fScale * 0.056f,  1.735f, 0.045f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Ring       (TColor(0.024f, 0.039f, 0.039f), eForm, fScale * 0.040f,  1.820f, 0.120f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Streaks    (TColor(0.180f, 0.184f, 0.190f), fScale * 0.350f, -1.000f, 24, 0.040f, 0.03f, 0.6f, 0.55f, ptCurrentImage);

}  /* generateNearFlare() */


void TIF_Lens_Flare::generateNormalFlares (void)
{

  //
  // Equals a 50-300 mm lens flare
  // 

  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Std  (TColor(0.93f, 0.93f, 0.93f), eForm, fScale * 0.038f, -1.000f, ptCurrentImage);
  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Std  (TColor(0.96f, 0.96f, 0.96f), eForm, fScale * 0.078f, -1.000f, ptCurrentImage);
  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Std  (TColor(1.00f, 0.15f, 0.17f), eForm, fScale * 0.230f, -1.000f, ptCurrentImage);
  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Hard (TColor(0.26f, 0.24f, 0.24f), eForm, fScale * 0.386f, -1.000f, ptCurrentImage);
  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Halo (TColor(0.31f, 0.06f, 0.02f), eForm, fScale * 0.084f, -1.000f, 0.07f, ptCurrentImage);

  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Std        (TColor(0.00f, 0.05f, 0.44f), eForm, fScale * 0.027f,  0.670f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Std        (TColor(0.35f, 0.71f, 0.56f), eForm, fScale * 0.010f,  0.270f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Std        (TColor(0.22f, 0.55f, 0.42f), eForm, fScale * 0.005f, -0.011f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.04f, 0.11f, 0.07f), eForm, fScale * 0.031f,  0.649f, 0.15f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.09f, 0.05f, 0.00f), eForm, fScale * 0.015f,  0.470f, 0.15f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.09f, 0.05f, 0.00f), eForm, fScale * 0.037f,  0.409f, 0.15f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.16f, 0.07f, 0.00f), eForm, fScale * 0.022f, -0.200f, 0.15f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.07f, 0.04f, 0.00f), eForm, fScale * 0.025f, -0.410f, 0.15f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.04f, 0.02f, 0.00f), eForm, fScale * 0.058f, -0.450f, 0.15f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.02f, 0.02f, 0.05f), eForm, fScale * 0.017f, -0.511f, 0.15f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.04f, 0.02f, 0.00f), eForm, fScale * 0.200f, -1.496f, 0.15f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.04f, 0.02f, 0.00f), eForm, fScale * 0.500f, -1.496f, 0.15f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Ring       (TColor(0.13f, 0.07f, 0.00f), eForm, fScale * 0.075f,  0.449f, 0.12f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Ring       (TColor(0.05f, 0.10f, 0.00f), eForm, fScale * 0.100f,  1.000f, 0.12f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Ring       (TColor(0.04f, 0.10f, 0.05f), eForm, fScale * 0.039f, -1.301f, 0.12f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Halo       (TColor(0.02f, 0.00f, 0.07f), eForm, fScale * 0.190f,  1.309f, 0.04f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Halo       (TColor(0.01f, 0.06f, 0.01f), eForm, fScale * 0.195f,  1.309f, 0.04f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Halo       (TColor(0.07f, 0.02f, 0.00f), eForm, fScale * 0.200f,  1.309f, 0.04f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Halo       (TColor(0.07f, 0.02f, 0.00f), eForm, fScale * 0.038f, -1.301f, 0.04f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Halo       (TColor(0.08f, 0.06f, 0.02f), eForm, fScale * 0.096f,  1.000f, 0.04f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Streaks    (TColor(0.18f, 0.18f, 0.18f), fScale * 0.260f, -1.000f, 50, 0.010f, 0.005f, 0.9f, 0.2f, ptCurrentImage);

}  /* generateNormalFlare() */


void TIF_Lens_Flare::generateFarFlares (void)
{

  float    fPosition;
  size_t   I;

  //
  // Equals a 35 mm lens flare
  // 

  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Std  (TColor(1.00f, 1.00f, 1.00f), eForm, fScale * 0.058f, -1.000f, ptCurrentImage);
  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Std  (TColor(1.00f, 1.00f, 0.76f), eForm, fScale * 0.088f, -1.000f, ptCurrentImage);
  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Std  (TColor(1.00f, 0.15f, 0.17f), eForm, fScale * 0.180f, -1.000f, ptCurrentImage);
  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Std  (TColor(0.27f, 0.23f, 0.25f), eForm, fScale * 0.606f, -1.000f, ptCurrentImage);
  aptHotspotTable  [ iNoHotspots++ ]  = new TFlare_Halo (TColor(0.31f, 0.06f, 0.02f), eForm, fScale * 0.084f, -1.000f, 0.07f, ptCurrentImage);

  fPosition = -1.65;

  for (I = 0; ( I < 6 ) ;I++)
  {
    aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.000f, 0.025f, 0.029f), eForm, fScale * 0.034f, fPosition, 0.07f, ptCurrentImage);

    fPosition -= 0.022;
  }

  fPosition = -1.42;

  for (I = 0; ( I < 4 ) ;I++)
  {
    aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Hard       (TColor(0.000f, 0.125f, 0.121f), eForm, fScale * 0.020f, fPosition, ptCurrentImage);

    fPosition -= 0.024;
  }

  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.035f, 0.031f, 0.082f), eForm, fScale * 0.031f, -0.45f, 0.070f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.019f, 0.012f, 0.067f), eForm, fScale * 0.047f, -0.42f, 0.070f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Hard       (TColor(0.235f, 0.471f, 0.412f), eForm, fScale * 0.005f,  0.45f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Std        (TColor(0.196f, 0.314f, 0.216f), eForm, fScale * 0.013f,  0.45f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Std        (TColor(0.216f, 0.118f, 0.137f), eForm, fScale * 0.019f,  0.55f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Decreasing (TColor(0.031f, 0.102f, 0.075f), eForm, fScale * 0.190f,  0.69f, 0.200f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Halo       (TColor(0.039f, 0.008f, 0.004f), eForm, fScale * 0.150f,  0.69f, 0.075f, ptCurrentImage);
  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Hard       (TColor(0.039f, 0.024f, 0.000f), eForm, fScale * 0.125f,  0.69f, ptCurrentImage);

  fPosition = 0.69;

  for (I = 0; ( I < 5 ) ;I++)
  {
    aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Std        (TColor(0.035f, 0.020f, 0.000f), eForm, fScale * 0.075f, fPosition, ptCurrentImage);

    fPosition += 0.025;
  }

  aptArtefactTable [ iNoArtefacts++ ] = new TFlare_Streaks    (TColor(0.210f, 0.210f, 0.210f), fScale * 0.350f, -1.000f, 40, 0.030f, 0.02f, 0.6f, 0.55f, ptCurrentImage);

}  /* generateFarFlare() */


void TIF_Lens_Flare::renderFlares (float fATTENUATION, float fXOFFSET, float fYOFFSET)
{

  for (size_t I = 0; ( I < iNoHotspots ) ;I++)
  {
    aptHotspotTable[I]->render (fIntensity * fATTENUATION, fXOFFSET, fYOFFSET);
  }

  if ( gArtefacts )
  {
    for (size_t I = 0; ( I < iNoArtefacts ) ;I++)
    {
      aptArtefactTable[I]->render (fIntensity * fATTENUATION, fXOFFSET, fYOFFSET);
    }
  }

}  /* renderFlares() */


bool TIF_Lens_Flare::checkPixel (int X, int Y)
{

  float fPixelIntensity;

  if ( ( X < 0 ) || 
       ( Y < 0 ) || 
       ( X >= (int) ptCurrentImage->width()  ) ||
       ( Y >= (int) ptCurrentImage->height() ) )
  {
    return false;
  }

  if ( getMapPixel (X, Y) )
  {
    return false;
  }

  fPixelIntensity = ptImageCopy->getPixel (X, Y).intensity();

  if ( fPixelIntensity > fThreshold  )
  {
    if ( fMaxIntensity < fPixelIntensity )
    {
      fMaxIntensity = fPixelIntensity;
          
      iMaxXpos = X;
      iMaxYpos = Y;
    }

    return true;
  }
  
  return false;

}  /* checkPixel() */


void TIF_Lens_Flare::markArea (int X, int Y)
{

  if ( checkPixel (X-1, Y-1) )
  {
    setMapPixel (X-1, Y-1, true);
    markArea    (X-1, Y-1);
  }
  if ( checkPixel (X, Y-1) )
  {
    setMapPixel (X, Y-1, true);
    markArea    (X, Y-1);
  }
  if ( checkPixel (X+1, Y-1) )
  {
    setMapPixel (X+1, Y-1, true);
    markArea    (X+1, Y-1);
  }
  if ( checkPixel (X-1, Y) )
  {
    setMapPixel (X-1, Y, true);
    markArea    (X-1, Y);
  }
  if ( checkPixel (X+1, Y) )
  {
    setMapPixel (X+1, Y, true);
    markArea    (X+1, Y);
  }
  if ( checkPixel (X-1, Y+1) )
  {
    setMapPixel (X-1, Y+1, true);
    markArea    (X-1, Y+1);
  }
  if ( checkPixel (X, Y+1) )
  {
    setMapPixel (X, Y+1, true);
    markArea    (X, Y+1);
  }
  if ( checkPixel (X+1, Y+1) )
  {
    setMapPixel (X+1, Y+1, true);
    markArea    (X+1, Y+1);
  }

}  /* markArea() */


void TIF_Lens_Flare::flaresByReflections (void)
{

  float    fXScrOffset;
  float    fYScrOffset;
  float    fMaxImageIntensity;
  bool     gExceeded;
  size_t   I;

  fMaxImageIntensity = ptCurrentImage->maxIntensity();

  if ( fMaxImageIntensity == 0.0f )
  {
    return;
  }

  apgMarkedMap = (bool *) malloc (ptCurrentImage->width() * ptCurrentImage->height() * sizeof (bool));

  ptImageCopy  = new TImage (ptCurrentImage->width(), ptCurrentImage->height());

  for (I = 0; ( I < ptCurrentImage->width() ) ;I++)
  {
    for (size_t J = 0; ( J < ptCurrentImage->height() ) ;J++)
    {
      setMapPixel (I, J, false);

      ptImageCopy->setPixel (I, J, ptCurrentImage->getPixel (I, J));
    } 
  }

  for (I = 0; ( I < ptCurrentImage->width() ) ;I++)
  {
    for (size_t J = 0; ( J < ptCurrentImage->height() ) ;J++)
    {
      if ( getMapPixel (I, J) == false)
      {
        gExceeded = checkPixel (I, J);

        if ( gExceeded ) 
        {
          fMaxIntensity = 0.0f;

          markArea (I, J);

          fXScrOffset = (float) iMaxXpos / (float) (ptCurrentImage->width()  - 1);
          fYScrOffset = (float) iMaxYpos / (float) (ptCurrentImage->height() - 1);
          
          renderFlares(fMaxIntensity / fMaxImageIntensity, fXScrOffset, fYScrOffset);
        }

        setMapPixel (I, J, true);
      }
    }
  }
  
  delete ptImageCopy;

  free (apgMarkedMap);

}  /* flaresByReflections() */


void TIF_Lens_Flare::flaresByLightsources (void)
{

  TCamera*       ptSceneCamera;
  const TLight*  ptLight;
  TVector2       tScreenPosition;
  TVector        tPosition;
  TRay           tRay;
  TSurfaceData   tSurf;
  TScalar        tDistToIntersection;
  TScalar        tDistToLight;
  TScalar        tDotLightCamera;
  bool           gOnImagePlane;
  bool           gOkToRenderFlare;
  bool           gObjectHit;
  float          fXScrOffset;
  float          fYScrOffset;
  float          fAttenuation;

  ptSceneCamera = ptScene->camera();

  for (vector<TLight*>::const_iterator tIter = ptScene->lightList().begin(); ( tIter != ptScene->lightList().end() ) ;tIter++)
  {
    ptLight = *tIter;

    if ( ptLight->className() == "PointLight" )
    {
      tPosition = ptLight->location();      

      gOnImagePlane = ptSceneCamera->getPlaneProjection(tPosition, tScreenPosition);

      tDotLightCamera = dotProduct((ptSceneCamera->getLookAt() - ptSceneCamera->location()), (tPosition - ptSceneCamera->location()));

      if ( gOnImagePlane && ( tDotLightCamera > 0 ) )
      {
        gOkToRenderFlare = false;     

        ptSceneCamera->getRay (tScreenPosition.x(), tScreenPosition.y(), tRay);

        gObjectHit = ptScene->world()->findFirstIntersection (tRay, tSurf);

        gOkToRenderFlare = ( !gObjectHit );

        if ( gObjectHit ) 
        {
          tDistToIntersection = tSurf.distance();
          tDistToLight = Distance (tPosition, ptSceneCamera->location());

          if ( tDistToIntersection > tDistToLight )
          {
            gOkToRenderFlare = true;
          }
        }

        if ( gOkToRenderFlare )
        {
          fXScrOffset = tScreenPosition.x() / (float) (ptCurrentImage->width()  - 1);
          fYScrOffset = tScreenPosition.y() / (float) (ptCurrentImage->height() - 1);

          fAttenuation = ptLight->color(ptSceneCamera->location()).intensity() * fInfluence;

          renderFlares(fAttenuation, fXScrOffset, fYScrOffset);
        }                           
      } 
    }
  }  

}  /* flaresByLightsources() */

void TIF_Lens_Flare::filter (SBuffers& rsBUFFERS)
{

  ptCurrentImage = rsBUFFERS.ptImage;

  iNoHotspots  = 0;
  iNoArtefacts = 0;

  switch (eType) 
  {
    case (FX_NEAR) :
      generateNearFlares();
      break;

    case (FX_FAR) :
      generateFarFlares();
      break;

    default:
      generateNormalFlares();
  }

  //
  // Render reflection lens flares
  //

  flaresByReflections();

  //
  // Render lens flares generated by light sources
  //

  flaresByLightsources();

  for (size_t I = 0; ( I < iNoHotspots ) ;I++)
  {
    delete aptHotspotTable[I];
  }

  if ( gArtefacts )
  {
    for (size_t I = 0; ( I < iNoArtefacts ) ;I++)
    {
      delete aptArtefactTable[I];
    }
  }

}  /* filter() */


int TIF_Lens_Flare::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "lf_type" )
  {
    if ( eTYPE == FX_STRING )
    {
      string tType ((char *) nVALUE.pvValue);

      if ( tType == "near" )
      {
        eType = FX_NEAR;
      }
      else if ( tType == "normal" )
      {
        eType = FX_NORMAL;
      }
      else if ( tType == "far" )
      {
        eType = FX_FAR;
      }
      else
      {
        return FX_ATTRIB_WRONG_VALUE;
      } 
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "lf_form" )
  {
    if ( eTYPE == FX_STRING )
    {
      string tForm ((char *) nVALUE.pvValue);

      if ( tForm == "pentagons" )
      {
        eForm = FX_PENTAGON;
      }
      else if ( tForm == "hexagons" )
      {
        eForm = FX_HEXAGON;
      }
      else if ( tForm == "circles" )
      {
        eForm = FX_CIRCLE;
      }
      else
      {
        return FX_ATTRIB_WRONG_VALUE;
      } 
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "lf_scale" )
  {
    if ( eTYPE == FX_REAL )
    {
      fScale = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "threshold" )
  {
    if ( eTYPE == FX_REAL )
    {
      fThreshold = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "intensity" )
  {
    if ( eTYPE == FX_REAL )
    {
      fIntensity = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "influence" )
  {
    if ( eTYPE == FX_REAL )
    {
      fInfluence = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "artefacts" )
  {
    if ( eTYPE == FX_BOOL )
    {
      gArtefacts = nVALUE.gValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TImageFilter::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TIF_Lens_Flare::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "lf_type" )
  {
    switch (eType) 
    {
      case (FX_NEAR) :
        rnVALUE.pvValue = (void *) "near";
        break; 

      case (FX_FAR) :
        rnVALUE.pvValue = (void *) "far";
        break;
 
      default:
        rnVALUE.pvValue = (void *) "normal";
    }
  }
  else if ( rktNAME == "lf_form" )
  {
    switch (eForm) 
    {
      case (FX_PENTAGON) :
        rnVALUE.pvValue = (void *) "pentagons";
        break;

      case (FX_HEXAGON) :
        rnVALUE.pvValue = (void *) "hexagons";
        break; 
 
      default:
        rnVALUE.pvValue = (void *) "circles";
    }
  }
  else if ( rktNAME == "lf_scale" )
  {
    rnVALUE.dValue = fScale;
  }
  else if ( rktNAME == "threshold" )
  {
    rnVALUE.dValue = fThreshold;
  }
  else if ( rktNAME == "intensity" )
  {
    rnVALUE.dValue = fIntensity;
  }
  else if ( rktNAME == "influence" )
  {
    rnVALUE.dValue = fInfluence;
  }
  else if ( rktNAME == "artefacts" )
  {
    rnVALUE.gValue = gArtefacts;
  }
  else
  {
    return TImageFilter::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TIF_Lens_Flare::getAttributeList (TAttributeList& rtLIST) const
{

  TImageFilter::getAttributeList (rtLIST);

  rtLIST ["lf_type"]   = FX_STRING;
  rtLIST ["lf_form"]   = FX_STRING;
  rtLIST ["lf_scale"]  = FX_REAL;
  rtLIST ["threshold"] = FX_REAL;
  rtLIST ["intensity"] = FX_REAL;
  rtLIST ["influence"] = FX_REAL;
  rtLIST ["artefacts"] = FX_BOOL;

}  /* getAttributeList() */




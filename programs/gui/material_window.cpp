/*
*  Copyright (C) 1998 Angel Jimenez Jimenez
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

#include "llapi/material.h"
#include "hlapi/plugin_manager.h"
#include "hlapi/sphere.h"
#include "material_window.h"

void TMaterialWindow::setupScene (void)
{

  TBsdf*       ptBsdf;
  TSphere*     ptSphere;
  TCamera*     ptCamera;
  TLight*      ptLight;
  TRenderer*   ptRenderer;
  NAttribute   nAttrib;

  ptScene = new TScene;

  ptCamera = (TCamera*) tPluginManager.newObject ("PinholeCamera");
  ptCamera->translate (TVector (0, 0, 4));
  ptCamera->setLookAt (TVector (0, 0, 0));

  ptRenderer = (TRenderer*) tPluginManager.newObject ("Raytracer");
  
  ptLight = (TLight*) tPluginManager.newObject ("PointLight");
  ptLight->translate (TVector (5, 5, 5));
  ptLight->setColor (TColor::_white());
  
  ptBsdf = (TBsdf*) tPluginManager.newObject ("BsdfPhong");

  nAttrib.dValue = 20;
  ptBsdf->setAttribute ("exponent", nAttrib, FX_REAL);
                        
  ptMaterial = new TMaterial;
  ptMaterial->setColor (new TPattern(TColor (1, 0, 0)));
  ptMaterial->setAmbientReflection (new TPattern(0.2));
  ptMaterial->setDiffuseReflection (new TPattern(0.6));
  ptMaterial->setSpecularReflection (new TPattern(0.2));
  ptMaterial->setBsdf (ptBsdf);
  
  ptSphere = new TSphere();
  ptSphere->translate (TVector (0, 0, 0));
  ptSphere->setRadius (1);
  ptSphere->setMaterial (ptMaterial);

  ptScene->setBackgroundColor (new TPattern(TColor::_white()));
  ptScene->setCamera (ptCamera);
  ptScene->setRenderer (ptRenderer);
  ptScene->addLight (ptLight);
  ptScene->setWorld (ptSphere);
  ptScene->setWidth (FX_PREVIEW_WIDTH);
  ptScene->setHeight (FX_PREVIEW_HEIGHT);

  ptScene->initialize();
  
}  /* setupScene() */


void TMaterialWindow::previewButtonCB (Gtk::Button* ptBUTTON)
{

  drawPreview();

}  /* previewButtonCB() */


TMaterialWindow::TMaterialWindow (void)
{

  Gtk::Table*            ptTable;
  Gtk::ScrolledWindow*   ptScrolledWnd;
  Gtk::Frame*            ptFrame;
  Gtk::Button*           ptButton;

  ptMaterial = new TMaterial;
  
  setupScene();

  ptTable = new Gtk::Table (3, 3, 0);
  ptTable->show();

  add (*ptTable);

  ptScrolledWnd = new Gtk::ScrolledWindow;
  ptScrolledWnd->set_policy (GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  ptScrolledWnd->show();

  ptTable->attach (*ptScrolledWnd, 0, 2, 0, 3, GTK_SHRINK | GTK_FILL | GTK_EXPAND, GTK_SHRINK | GTK_FILL | GTK_EXPAND);

  ptGraph = new TMaterialGraph;
  ptGraph->show();

  ptScrolledWnd->add_with_viewport (*ptGraph);

  ptFrame = new Gtk::Frame;
  ptFrame->set_border_width (3);
  ptFrame->show();

  ptTable->attach (*ptFrame, 2, 3, 0, 1, 0, 0);

  ptPreview = new Gtk::Preview (GTK_PREVIEW_COLOR);
  ptPreview->size (FX_PREVIEW_WIDTH, FX_PREVIEW_HEIGHT);
  ptPreview->show();

  ptFrame->add (*ptPreview);
  
  ptButton = new Gtk::Button ("Preview");
  ptButton->set_border_width (3);
  ptButton->show();

  ptButton->clicked.connect(bind(slot(this, &TMaterialWindow::previewButtonCB), ptButton));
                     
  ptTable->attach (*ptButton, 2, 3, 1, 2, 0, 0);
  
  ptNotebook = new Gtk::Notebook;
  ptNotebook->set_border_width (3);
  ptNotebook->show();

  ptTable->attach (*ptNotebook, 2, 3, 2, 3, 0, GTK_SHRINK | GTK_FILL | GTK_EXPAND);

  set_usize (600, 500);
  set_title ("Material -");
  
}  /* TMaterialWindow() */


TMaterialWindow::~TMaterialWindow (void)
{

  ptScene->finalize();
  delete ptScene;

}  /* ~TMaterialWindow() */


void TMaterialWindow::drawPreview (void)
{

  Byte*    pbBuffer;
  TColor   tColor;
  size_t   zWidth  = ptScene->buffers()->ptImage->width();
  size_t   zHeight = ptScene->buffers()->ptImage->height();

  pbBuffer = new Byte [zWidth * 3];
  
  ptScene->render();

  for (size_t J = 0; ( J < zHeight ) ;J++)
  {
    for (size_t I = 0; ( I < zWidth ) ;I++)
    {
      tColor = ptScene->buffers()->ptImage->getPixel (I, J);
      tColor.clamp();
      tColor = tColor.convertTo24Bits();
      
      pbBuffer [I * 3 + 0] = (Byte) tColor.red();
      pbBuffer [I * 3 + 1] = (Byte) tColor.green();
      pbBuffer [I * 3 + 2] = (Byte) tColor.blue();
    }
    ptPreview->draw_row (pbBuffer, 0, J, zWidth);
  }

  delete pbBuffer;

  gtk_widget_draw (GTK_WIDGET (ptPreview->gtkobj()), NULL);
  
}  /* drawPreview() */

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

#include <iostream.h>
#include "image_window.h"
#include "scene_window.h"
#include "plugin_window.h"
#include "material_window.h"
#include "message_dialog.h"
#include "render_dialog.h"
#include "scene_callbacks.h"
#include <gtk--/fileselection.h>

void sceneQuitCB ()
{

  Gtk::Main::quit();

}  /* sceneQuitCB() */


void sceneMenuCB (const char* s)
{
  
  MessageDialog ("Scene window menu", string("This option is not implemented yet: " + string(s)).c_str());
  
}  /* sceneMenuCB() */


void sceneCloseCB (TSceneWindow* ptSW)
{

  ptSW->setSceneFile();
  
}  /* sceneCloseCB() */


void sceneReplaceCB (TSceneWindow* ptWnd)
{

  if ( !ptWnd->ptFileSelection )
  {
    ptWnd->ptFileSelection = new Gtk::FileSelection ("Select scene file...");

    ptWnd->ptFileSelection->get_ok_button()->clicked.connect(slot(ptWnd,&TSceneWindow::setSceneFile));      

    ptWnd->ptFileSelection->get_cancel_button()->clicked.connect(bind(slot(sceneCancelCB),ptWnd));    
    
    ptWnd->ptFileSelection->show();
  }
  
}  /* sceneReplaceCB() */


void sceneNewCB (TSceneWindow* ptWnd)
{

  if ( !ptWnd->ptFileSelection )
  {
    ptWnd->ptFileSelection = new Gtk::FileSelection ("Select scene file...");

    ptWnd->ptFileSelection->get_ok_button()->clicked.connect
      (slot(ptWnd, &TSceneWindow::openNewSceneWindow));
    ptWnd->ptFileSelection->get_cancel_button()->clicked.connect
      (bind(slot(sceneCancelCB), ptWnd));

    ptWnd->ptFileSelection->show();
  }
    
}  /* sceneNewCB() */


void sceneRenderCB (TSceneWindow* ptWnd)
{

  TScene*          ptScene;
  TRenderDialog*   ptRenderDlg;
  
  ptScene = ptWnd->scene();
  if ( ptScene )
  {
    ptRenderDlg = new TRenderDialog (ptScene);
    ptRenderDlg->show();
  }
  
}  /* sceneRenderCB() */


void scenePluginWindowCB ()
{

  TPluginWindow*   ptPluginWnd;

  ptPluginWnd = new TPluginWindow;
  ptPluginWnd->show();
  
}  /* scenePluginWindowCB() */


void sceneMaterialWindowCB ()
{

  TMaterialWindow*   ptMaterialWnd;

  ptMaterialWnd = new TMaterialWindow;
  ptMaterialWnd->show();
  
}  /* sceneMaterialWindowCB() */


void sceneCancelCB (TSceneWindow* ptWND)
{

  ptWND->ptFileSelection->hide();
  delete ptWND->ptFileSelection;
  ptWND->ptFileSelection = NULL;

}  /* sceneCancelCB() */

void sceneCameraCB (TSceneWindow* ptWND, string plugin_name)
{
  sceneMenuCB(string("set camera :" + plugin_name).c_str());
}

void sceneLightCB (TSceneWindow* ptWND, string plugin_name)
{
  sceneMenuCB(string("add light :" + plugin_name).c_str());  
}

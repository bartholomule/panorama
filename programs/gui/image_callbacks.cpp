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
#include "image_callbacks.h"
#include "message_dialog.h"
#include "hlapi/plugin_manager.h"

void imageMenuCB (const char* s)
{
  
  MessageDialog ("Image window menu",
		 string("This option is not implemented yet:" + string(s)).c_str());
  
}  /* imageMenuCB() */


void imageCloseCB (TImageWindow* ptWnd)
{

  ptWnd->hide();
  delete ptWnd;
  
}  /* imageCloseCB() */


void imageSaveCB (TImageWindow* ptWnd)
{

  if ( ptWnd->gRenderingDone )
  {
    ptWnd->ptScene->saveImage();
  }
  
}  /* imageSaveCB() */


void imageSaveAsCB (TImageWindow* ptWnd)
{

  if ( ptWnd->gRenderingDone && !ptWnd->ptFileSelection )
  {
    ptWnd->ptFileSelection = new Gtk::FileSelection ("Select image file...");

    ptWnd->ptFileSelection->get_ok_button()->clicked.connect(slot(ptWnd, &TImageWindow::saveImage));
    ptWnd->ptFileSelection->get_cancel_button()->clicked.connect(bind(slot(imageCancelCB), ptWnd));

    ptWnd->ptFileSelection->show();
  }
  
}  /* imageSaveAsCB() */


void imageFilterCB2(TImageWindow* ptWND, TImageFilter* ptFilter)
{
  //  delete ptWND->dialog;
  ptWND->filterImage(ptFilter);     
}

void imageFilterCB (TImageWindow* ptWND, const char* filter_name)
{

  cout << "Need to apply filter \"" << filter_name << "\"" << endl;

  TImageFilter* ptFilter = (TImageFilter*)tPluginManager.newObject(filter_name);
  cout << "Pointer=" << ptFilter << endl;

  TObjectPropertiesDialog* dialog = new TObjectPropertiesDialog(ptFilter);
  dialog->getOk().clicked.connect(bind(slot(imageFilterCB2),ptWND,ptFilter));
  dialog->show();

}  /* imageFilterCB() */


void imageCancelCB (TImageWindow* ptWND)
{

  delete ptWND->ptFileSelection;
  ptWND->ptFileSelection = NULL;

}  /* imageCancelCB() */

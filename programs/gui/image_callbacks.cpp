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
#include "llapi/attribute.h"

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
  // Since each window now contains its own buffers (instead of being shared
  // with the scene), we have to let the window save its image.
    NAttribute nat;
    if( ptWnd->ptScene->imageIO()->getAttribute("name",nat) == FX_ATTRIB_OK )
    {
#if !defined(NEW_ATTRIBUTES)
      ptWnd->saveImage((char*)nat.pvValue);
#else
      magic_pointer<TAttribString> str = get_string(nat);
      if( !!str )
      {
	ptWnd->saveImage(str->tValue);
      }
#endif
    }
  }
  
}  /* imageSaveCB() */


void imageSaveAsCB (TImageWindow* ptWnd)
{

  if ( ptWnd->gRenderingDone && !ptWnd->ptFileSelection )
  {
    ptWnd->ptFileSelection = new Gtk::FileSelection ("Select image file...");

    ptWnd->ptFileSelection->get_ok_button()->clicked.connect(bind(slot(ptWnd, &TImageWindow::saveImage),string("")));
    ptWnd->ptFileSelection->get_cancel_button()->clicked.connect(bind(slot(imageCancelCB), ptWnd));

    ptWnd->ptFileSelection->show();
  }
  
}  /* imageSaveAsCB() */

#include <pair.h>
using std::pair;
typedef pair<TImageWindow*,TObjectPropertiesDialog*> cb2_item;

void imageFilterCB2(cb2_item cb_data, TImageFilter* ptFilter)
{
  TImageWindow* ptWnd = cb_data.first;  
  TObjectPropertiesDialog* dialog = cb_data.second;
  dialog->accept_changes();
  dialog->hide();
  delete dialog;
  ptWnd->filterImage(ptFilter);     
}

void imageFilterCB (TImageWindow* ptWND, string filter_name)
{

  TImageFilter* ptFilter = (TImageFilter*)tPluginManager.newObject(filter_name);

  TObjectPropertiesDialog* dialog = new TObjectPropertiesDialog(ptFilter);
  dialog->getOk().clicked.connect(bind(slot(imageFilterCB2),cb2_item(ptWND,dialog),ptFilter));
  dialog->show();

}  /* imageFilterCB() */


void imageCancelCB (TImageWindow* ptWND)
{

  delete ptWND->ptFileSelection;
  ptWND->ptFileSelection = NULL;

}  /* imageCancelCB() */

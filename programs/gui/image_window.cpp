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

#include "llapi/file.h"
#include "hlapi/plugin_manager.h"
#include "image_callbacks.h"
#include "image_window.h"

using SigC::slot;
using SigC::bind;

Gtk::Menu* TImageWindow::createFilterMenu (void)
{
  using namespace Gtk::Menu_Helpers;
  MenuList* menu_list;
  Gtk::Menu* filter_menu = new Gtk::Menu();
  menu_list = &filter_menu->items();
  
  string                        tMenuOption;
  const TPluginList*            ptPluginList;
  TPluginList::const_iterator   tIter;
  TImageFilterCallbackData*     ptData;
  size_t                        J             = 0;
  GtkMenuEntry*                 ptMenuEntries = NULL;

  ptPluginList = tPluginManager.pluginList();
  assert ( ptPluginList );

  tIter = ptPluginList->find (FX_IMAGE_FILTER_CLASS);
  if ( tIter != ptPluginList->end() )
  {
    cout << "Image filter plugin type located" << endl;
    if ( !tIter->second.empty() )
    {
      cout << "List not empty" << endl;
      ptMenuEntries = new GtkMenuEntry [tIter->second.size()];
        
      for (list<string>::const_iterator tIter2 = tIter->second.begin();
	   tIter2 != tIter->second.end();
	   ++tIter2)
      {
	cout << "Menu Option=" << *tIter2 << endl;	
	menu_list->push_back(MenuElem(*tIter2,
				      bind(slot(imageFilterCB),this,tIter2->c_str())));
#if garbage	
        tMenuOption = string ("<Main>/Filter/") + *tIter2;

        ptMenuEntries[J].path = new char [tMenuOption.length() + 1];
        
        strcpy (ptMenuEntries[J].path, tMenuOption.c_str());
        
        ptMenuEntries[J].callback = &imageFilterCB;

        ptData = new TImageFilterCallbackData;

        ptData->tName    = *tIter2;
        ptData->ptWindow = this;

        ptMenuEntries[J].callback_data = ptData;
        
        J++;
#endif /* garbage		 */
      }

#if FIXME
      ptMenuFactory->add_entries (ptMenuEntries, J);
#endif
      
      delete ptMenuEntries;
    }
    else
    {
      cout << "Plugin list is empty" << endl;
    }
  }
  else
  {
    cout << "No image filters found" << endl;
  }

  return filter_menu;
}  /* setFilterMenu() */


TImageWindow::TImageWindow (TScene* ptSCENE)
{

  string             tTitle;
#if FIXME
  Gtk_MenuFactory*   ptSubfactory;
#endif
  NAttribute         nAttrib;
  
  gRenderingDone = false;
  ptScene        = ptSCENE;
  //  dialog         = NULL;
  ptImage        = ptScene->buffers()->ptImage;

  ptVBox = new Gtk::VBox;
  ptVBox->show();
  
  add (*ptVBox);

#if FIXME
  ptMenuFactory = new Gtk_MenuFactory (GTK_MENU_FACTORY_MENU_BAR);
  ptSubfactory  = new Gtk_MenuFactory (GTK_MENU_FACTORY_MENU_BAR);
  
  for (size_t J = 0; ( J < _zMenuItems ) ;J++)
  {
    _atMenuItems[J].callback_data = (gpointer) this;
  }
  
  ptMenuFactory->add_subfactory (ptSubfactory, "<Main>");
  ptMenuFactory->add_entries (_atMenuItems, _zMenuItems);

  ptMenuBar = ptSubfactory->get_menubar_widget();
#else
  ptMenuBar = manage(new Gtk::MenuBar());
  using namespace Gtk::Menu_Helpers;
  MenuList* menu_list;
  Gtk::Menu* image_menu = manage(new Gtk::Menu());
  //  Gtk::Menu* filter_menu = manage(new Gtk::Menu());
  Gtk::Menu* help_menu = manage(new Gtk::Menu());

  menu_list = &image_menu->items();
  menu_list->push_back(MenuElem("_Save",ALT|'s',bind(slot(imageSaveCB),this)));
  menu_list->push_back(MenuElem("Save _As",ALT|'a',bind(slot(imageSaveAsCB),this)));
  menu_list->push_back(SeparatorElem());
  menu_list->push_back(MenuElem("_Close",ALT|'c',bind(slot(imageCloseCB),this)));

  menu_list = &help_menu->items();
  menu_list->push_back(MenuElem("_About",bind(slot(imageMenuCB),"about")));  

  // Add them to the bar...
  menu_list = &ptMenuBar->items();
  menu_list->push_back(MenuElem("_Image",*image_menu));
  //  menu_list->push_back(MenuElem("_Filter",*filter_menu));
  menu_list->push_back(MenuElem("_Filter",*manage(createFilterMenu())));
  menu_list->push_back(MenuElem("_Help",*help_menu));      
#endif
//  ptMenuBar = new Gtk_MenuBar (GTK_MENU_BAR (ptSubfactory->gtkobj()->widget));
  ptMenuBar->show_all();

//  ptMenuFactory->factory_find ("<Main>/Help")->widget->right_justify();

  //  setFilterMenu();
  
  ptVBox->pack_start (*ptMenuBar, 0, 1, 0);

  ptPreview = new Gtk::Preview (GTK_PREVIEW_COLOR);
  ptPreview->size (ptImage->width(), ptImage->height());
  ptPreview->show();

  ptVBox->add (*ptPreview);

  ptScene->imageIO()->getAttribute ("name", nAttrib);
  
  tTitle = string ("Image - ") + (char*) nAttrib.pvValue;
  set_title (tTitle.c_str());
  
}  /* TImageWindow() */


void TImageWindow::saveImage (void)
{

  string   tName;
  
  if ( ptFileSelection )
  {
    tName = ptFileSelection->get_filename();

    ptScene->setOutputFileName (tName);
    ptScene->saveImage();

    ptFileSelection->hide();
    delete ptFileSelection;
    ptFileSelection = NULL;
  }
  
}  /* saveImage() */


void TImageWindow::drawRow (size_t zROW)
{

  guchar*        ptRow;
  TColor         tPixel;
  GdkRectangle   tRectangle;

  ptRow = new guchar [3 * ptImage->width()];

  for (size_t J = 0; ( J < ptImage->width() ) ;J++)
  {
    tPixel = ptImage->getPixel (J, zROW);

    tPixel.clamp();
    tPixel = tPixel.convertTo24Bits();

    ptRow [J * 3 + 0] = (Byte) tPixel.red();
    ptRow [J * 3 + 1] = (Byte) tPixel.green();
    ptRow [J * 3 + 2] = (Byte) tPixel.blue();
  }

  ptPreview->draw_row (ptRow, 0, zROW, ptImage->width());

  delete ptRow;

  tRectangle.x      = 0;
  tRectangle.y      = zROW;
  tRectangle.width  = ptImage->width();
  tRectangle.height = 1;
  
  gtk_widget_draw (GTK_WIDGET (ptPreview->gtkobj()), &tRectangle);
  
}  /* drawRow() */


void TImageWindow::drawImage (void)
{

  for (size_t J = 0; ( J < ptImage->height() ) ;J++)
  {
    drawRow (J);
  }
  
}  /* drawImage() */


void FinishedRenderLine (size_t zROW, void* pvDATA)
{

  TImageWindow*   ptWnd = (TImageWindow*) pvDATA;

  while ( gtk_events_pending() )
  {
    gtk_main_iteration();
  }

  ptWnd->drawRow (zROW);

}  /* FinishedRenderLine() */


void TImageWindow::filterImage(TImageFilter* ptFilter)
{
  SBuffers* rendered_buffers = ptScene->buffers();
  Word existing_buffers = 0;
  if(rendered_buffers->ptZBuffer != NULL)
  {
    existing_buffers |= FX_ZBUFFER;
  }
  if(rendered_buffers->ptNBuffer != NULL)
  {
    existing_buffers |= FX_NBUFFER;    
  }
  Word required_buffers = ptFilter->neededBuffers();
  Word missing_buffers = required_buffers & ~existing_buffers;

  if(missing_buffers)
  {
    static const char* zb = "ZBuffer (Distance)";
    static const char* nb = "NBuffer (Normal)";    
    string missing = "";
    string missing2 = " not generated";
    if(missing_buffers & FX_ZBUFFER)
    {
      if(missing_buffers & FX_NBUFFER)
      {
	missing = zb + string(" and ") + nb + string(" buffers were") + missing2;
      }
      else
      {
	missing = zb + string(" buffer was") + missing2;
      }
    }
    else if(missing_buffers & FX_NBUFFER)
    {
      missing = nb + string(" buffer was") + missing2;      
    }
    else
    {
      missing = string("[Unknown buffer type] was") + missing2;            
    }

    MessageDialog("Cannot apply filter", missing);
    
    return;
  }

  ptFilter->setScene(ptScene);
  ptFilter->filter(*rendered_buffers);
  cout << "Done with filter..." << endl;
  // Refresh the screen here...
  drawImage();
}

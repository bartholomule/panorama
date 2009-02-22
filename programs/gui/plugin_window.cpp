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

#include "hlapi/plugin_manager.h"
#include "plugin_window.h"
#include <gtk--/scrolledwindow.h>
#include <gtk--/tree.h>

TPluginWindow::TPluginWindow (void)
{

  Gtk::ScrolledWindow*   ptScrolledWnd;
  Gtk::Tree*             ptTree;
  Gtk::Tree*             ptSubtree;
  Gtk::TreeItem*         ptItem;
  TPluginList*          ptClassList;
  list<string>*         ptPluginList;

  ptScrolledWnd = new Gtk::ScrolledWindow;
  ptScrolledWnd->set_policy (GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  ptScrolledWnd->show();

  add (*ptScrolledWnd);
  
  ptTree = new Gtk::Tree;

  ptScrolledWnd->add_with_viewport (*ptTree);
  
  ptClassList = tPluginManager.pluginList();

  TPluginList::iterator   tClassIter = ptClassList->begin();

  while ( tClassIter != ptClassList->end() )
  {
    ptSubtree = new Gtk::Tree;
    ptSubtree->show();
    
    ptPluginList = &tClassIter->second;
    for (std::list<string>::const_iterator tPluginIter = ptPluginList->begin(); ( tPluginIter != ptPluginList->end() ) ;tPluginIter++)
    {
      ptItem = new Gtk::TreeItem (tPluginIter->c_str());
      ptItem->show();

      ptSubtree->append (*ptItem);
    }
    
    ptItem = new Gtk::TreeItem (TBaseClass::classTypeString (tClassIter->first).c_str());
    ptItem->show();
    
    ptTree->append (*ptItem);

    ptItem->set_subtree (*ptSubtree);

    tClassIter++;
  }
  
  ptTree->show();

  set_usize (300, 300);
  set_title ("Registered plugins");
  
}  /* TPluginWindow() */

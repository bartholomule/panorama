#if       !defined(KH_COMMON_H)
#define            KH_COMMON_H

/*
*  Copyright (C) 2001 Kevin Harris
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

#include <gtk--/menu.h>
#include "hlapi/plugin_manager.h"
#include <string>

// Create a menu for all plugins of the given type.
template <class callback_data_type>
Gtk::Menu* createPluginMenu (EClass tPLUGINCLASS,
			     void (*callback_function)(callback_data_type data,
						       string plugin_name),
			     callback_data_type data)
{
  using namespace Gtk::Menu_Helpers;
  MenuList* menu_list;
  Gtk::Menu* filter_menu = new Gtk::Menu();
  menu_list = &filter_menu->items();
  
  string                        tMenuOption;
  const TPluginList*            ptPluginList;
  TPluginList::const_iterator   tIter;

  ptPluginList = tPluginManager.pluginList();
  assert ( ptPluginList );

  tIter = ptPluginList->find (tPLUGINCLASS);
  if ( tIter != ptPluginList->end() )
  {
    if ( !tIter->second.empty() )
    {
        
      for (list<string>::const_iterator tIter2 = tIter->second.begin();
	   tIter2 != tIter->second.end();
	   ++tIter2)
      {
	menu_list->push_back(MenuElem(*tIter2,
				      SigC::bind(SigC::slot(callback_function),
						 data,*tIter2)));
      }

    }
    else
    {
      cout << "Plugin list is empty" << endl;
    }
  }
  else
  {
    cout << "No plugins of requested type found" << endl;
  }

  return filter_menu;
}  /* createPluginMenu() */

#endif /* !defined(KH_COMMON_H) */

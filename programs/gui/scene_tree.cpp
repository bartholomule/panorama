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

#include "hlapi/aggregate.h"
#include "object_properties_dialog.h"
#include "scene_tree.h"

static void accept_properties(TObjectPropertiesDialog* tOPD)
{
  tOPD->accept_changes();
  tOPD->hide();
  delete tOPD;
}

bool TSceneTree::setCamera (Gtk::Tree* ptTREE)
{
  
  Gtk::TreeItem*   ptItem;
  Gtk::Tree*       ptSubtree;
  TCamera*        ptCamera;
  
  ptCamera = ptScene->camera();
  if ( ptCamera )
  {
    ptSubtree = new Gtk::Tree;

    string entry_name;
    if(!ptCamera->identifier().empty())
    {
      entry_name = ptCamera->identifier() + " [" + ptCamera->className() + ']';
    }
    else
    {
      entry_name = ptCamera->className();
    }
    
    ptItem = new Gtk::TreeItem (entry_name);
    ptItem->show();
    ptSubtree->append (*ptItem);

    ptItem->button_press_event.connect(bind(slot(this,&TSceneTree::manageButtonPress), (TProcedural*) ptCamera));

    ptItem = new Gtk::TreeItem ("Camera");
    ptItem->show();

    ptTREE->append (*ptItem);
    ptItem->set_subtree (*ptSubtree);

    return true;
  }
  
  return false;

}  /* setCamera() */


bool TSceneTree::setLights (Gtk::Tree* ptTREE)
{
  
  Gtk::TreeItem*      ptItem;
  Gtk::Tree*          ptSubtree;
  TLight*            ptLight;
  vector<TLight*>&   tLightList = ptScene->lightList();

  if ( !tLightList.empty() )
  {
    ptSubtree = new Gtk::Tree;

    for (vector<TLight*>::const_iterator tIter = tLightList.begin(); ( tIter != tLightList.end() ) ;tIter++)
    {
      ptLight = *tIter;

      string entry_name = ptLight->className();
      if(!ptLight->identifier().empty())
      {
	entry_name = ptLight->identifier() + " [" + entry_name + ']';
      }      
      
      ptItem = new Gtk::TreeItem (entry_name);
      ptItem->show();
      ptSubtree->append (*ptItem);

      ptItem->button_press_event.connect(bind(slot(this, &TSceneTree::manageButtonPress), (TProcedural*) ptLight));

    }

    ptItem = new Gtk::TreeItem ("Lights");
    ptItem->show();
    
    ptTREE->append (*ptItem);
    ptItem->set_subtree (*ptSubtree);

    return true;
  }

  return false;

}  /* setLights() */


bool TSceneTree::recSetObjects (Gtk::Tree* ptTREE, TObject* ptOBJ)
{
  
  Gtk::TreeItem*       ptItem;
  Gtk::Tree*           ptSubtree;
  vector<TObject*>*   ptObjectList;
  bool                gSubtree = false;

  if ( ptOBJ->classType() == FX_AGGREGATE_CLASS )
  {
    ptSubtree = new Gtk::Tree;

    ptObjectList = ((TAggregate*) ptOBJ)->objectList();

    for (vector<TObject*>::iterator tIter = ptObjectList->begin(); ( tIter != ptObjectList->end() ) ;tIter++)
    {
      gSubtree |= recSetObjects (ptSubtree, *tIter);
    }

    string entry_name = ptOBJ->className();
    if(!ptOBJ->identifier().empty())
    {
      entry_name = ptOBJ->identifier() + " [" + entry_name + ']';
    }
    
    ptItem = new Gtk::TreeItem (entry_name);
    ptItem->show();
    ptTREE->append (*ptItem);

    ptItem->button_press_event.connect(bind(slot(this, &TSceneTree::manageButtonPress), (TProcedural*) ptOBJ));

    
    if ( gSubtree )
    {
      ptSubtree->show();
      ptItem->set_subtree (*ptSubtree);
    }
    else
    {
      delete ptSubtree;
    }
  }
  else
  {
    string entry_name = ptOBJ->className();
    if(!ptOBJ->identifier().empty())
    {
      entry_name = ptOBJ->identifier() + " [" + entry_name + ']';
    }
    
    ptItem = new Gtk::TreeItem (entry_name);
    ptItem->show();
    ptTREE->append (*ptItem);

    ptItem->button_press_event.connect(bind(slot(this, &TSceneTree::manageButtonPress), (TProcedural*) ptOBJ));

  }

  return true;
  
}  /* recSetObjects() */


bool TSceneTree::setObjects (Gtk::Tree* ptTREE)
{
  
  Gtk::TreeItem*   ptItem;
  Gtk::Tree*       ptSubtree;
  bool            gSubtree = false;
  TObject*        ptWorld  = ptScene->world();

  if ( ptWorld )
  {
    ptSubtree = new Gtk::Tree;

    gSubtree = recSetObjects (ptSubtree, ptWorld);
    
    ptItem = new Gtk::TreeItem ("Objects");
    ptItem->show();
    ptTREE->append (*ptItem);

    if ( gSubtree )
    {
      ptSubtree->show();
      ptItem->set_subtree (*ptSubtree);
    }
    else
    {
      delete ptSubtree;
    }
    
    return true;
  }

  return false;
  
}  /* setObjects() */


TSceneTree::TSceneTree (TScene* ptSCENE)
{

  Gtk::Tree*       ptSubtree;
  Gtk::TreeItem*   ptItem;
  bool            gSubtree = false;

  ptScene = ptSCENE;
  
  if ( ptScene )
  {
    ptSubtree = new Gtk::Tree;

    gSubtree |= setCamera (ptSubtree);
    gSubtree |= setLights (ptSubtree);
    gSubtree |= setObjects (ptSubtree);

    ptItem = new Gtk::TreeItem ("Scene");
    ptItem->show();

    ptItem->button_press_event.connect(bind(slot(this, &TSceneTree::manageButtonPress), (TProcedural*) ptScene));

    append (*ptItem);
    
    if ( gSubtree )
    {
      ptSubtree->show();
      ptItem->set_subtree (*ptSubtree);
    }
    else
    {
      delete ptSubtree;
    }
  }
  
}  /* TSceneTree() */


gint TSceneTree::manageButtonPress (GdkEventButton* ptEVENT, TProcedural* ptOBJECT)
{

  TObjectPropertiesDialog*   ptDlg;
  
  if ( ( ptEVENT->type == GDK_2BUTTON_PRESS ) && ( ptEVENT->button == 1 ) )
  {
    ptDlg = new TObjectPropertiesDialog (ptOBJECT);
    ptDlg->getOk().clicked.connect(bind(slot(&accept_properties), ptDlg));
    ptDlg->show();
  }

  return 1;

}  /* manageButtonPress() */

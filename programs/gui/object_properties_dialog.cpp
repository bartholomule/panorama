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

#include "llapi/attribs.h"
#include "llapi/llapi_defs.h"
#include "hlapi/class_manager.h"
#include "object_properties_dialog.h"
#include "color_preview.h"
#include "message_dialog.h"
#include <gtk--/frame.h>
#include <gtk--/togglebutton.h>
#include <gtk--/spinbutton.h>
#include <gtk--/entry.h>
#include <gtk--/adjustment.h>
#include <gtk--/label.h>
#include <gtk--/box.h>
#include <gtk--/table.h>
#include <gtk--/notebook.h>
#include <gtk--/combo.h>
#include "llapi/attribute.h"


using SigC::slot;
using SigC::bind;

static void _cancelCB (TObjectPropertiesDialog* ptDIALOG)
{

  ptDIALOG->hide();
  delete ptDIALOG;
  
}  /* _cancelCB() */

static void attribute_copy(TProcedural* source, TProcedural* dest);

struct property_callback_data
{
  TObjectPropertiesDialog* ptDlg;  
  string attributeName;
  EAttribType eType;
  void* dataContainer;
  TProcedural* destObject;
  int extraData; // Used to contain info such as the index into the vector...

  property_callback_data(TObjectPropertiesDialog* dlg,
			 const string& aName,
			 EAttribType   eTYPE,
			 void*         data,
			 TProcedural*  dest,
			 int           extra = 0):
    attributeName(aName), eType(eTYPE), dataContainer(data), destObject(dest),
    extraData(extra)
  {
  }
};

static void property_change_callback(property_callback_data tPCD);
                 
Gtk::Widget*
TObjectPropertiesDialog::createValueWidget (const string& name,
					    EAttribType eTYPE,
					    NAttribute nVALUE)
{
  TVector             tVector;
  TVector2            tVector2;
  Gtk::Adjustment*    ptAdjustment = NULL;
  Gtk::HBox*          ptHBox = NULL;
  Gtk::Frame*         ptFrame = NULL;  
  Gtk::ToggleButton*  ptToggleButton = NULL;
  TColorPreview*      ptPreview = NULL;
  Gtk::Widget*        ptWidget = NULL;
  Gtk::SpinButton*    ptSB = NULL;

  if(ptObjectCopy == NULL)
  {
    cout << "Null object... Not creating widget." << endl;
    return new Gtk::Label("BROKEN!");
  }
  
  switch ( eTYPE )
  {
  case FX_NONE:
    {
      ptWidget = new Gtk::Label;
      
      ((Gtk::Entry*) ptWidget)->set_text ("NONE -- DON'T EDIT");      
    }
    break;
    
  case FX_STRING:
    {
      Gtk::Entry* entry = new Gtk::Entry;
      ptWidget = entry;
#if !defined(NEW_ATTRIBUTES)
      entry->set_text ((char*) nVALUE.pvValue);
#else
      entry->set_text (rcp_static_cast<TAttribString>(nVALUE)->tValue);
#endif
      entry->changed.connect(bind(slot(&property_change_callback),
				  property_callback_data(this,
							 name,
							 eTYPE,
							 (void*)entry,
							 ptObjectCopy)));
							 
    }
    break;
#if defined(NEW_ATTRIBUTES)
  case FX_STRING_LIST:
    {
      Gtk::Combo* selection = new Gtk::Combo;
      magic_pointer<TAttribStringList> strlist = rcp_static_cast<TAttribStringList>(nVALUE);
      selection->set_popdown_strings (strlist->choices);
      selection->set_value_in_list (true, false);
      selection->set_use_arrows (true);
      selection->set_case_sensitive (true);
      Gtk::Entry* entry = selection->get_entry();
      entry->set_text(strlist->tValue);
      entry->changed.connect(bind(slot(&property_change_callback),
				  property_callback_data(this,
							 name,
							 FX_STRING,
							 (void*)entry,
							 ptObjectCopy)));
      ptWidget = selection;
    }
    break;
  case FX_INTEGER:
    {
      magic_pointer<TAttribInt> i = get_int(nVALUE);
      ptAdjustment = new Gtk::Adjustment (i->tValue, INT_MIN, INT_MAX, 1, 10, 10);
      ptWidget = ptSB = new Gtk::SpinButton (*ptAdjustment, 0.0, 0);

      ptSB->set_update_policy (GTK_UPDATE_ALWAYS);
      
      ptSB->changed.connect(bind(slot(&property_change_callback),
				 property_callback_data(this,
							name,
							eTYPE,
							(void*)ptSB,
							ptObjectCopy)));
    }
    break;
#endif

  case FX_REAL:
    {
#if !defined(NEW_ATTRIBUTES)
      ptAdjustment = new Gtk::Adjustment (nVALUE.dValue, -FLT_MAX, FLT_MAX, 1, 10, 10);
#else
      magic_pointer<TAttribReal> r = get_real(nVALUE);
      ptAdjustment = new Gtk::Adjustment (r->tValue, -FLT_MAX, FLT_MAX, 1, 10, 10);      
#endif
      ptWidget = ptSB = new Gtk::SpinButton (*ptAdjustment, 0.0, 3);

      ptSB->set_update_policy (GTK_UPDATE_ALWAYS);

      ptSB->changed.connect(bind(slot(&property_change_callback),
				 property_callback_data(this,
							name,
							eTYPE,
							(void*)ptSB,
							ptObjectCopy)));      
    }
    break;

  case FX_COLOR:
    {
      ptFrame = new Gtk::Frame;
      ptFrame->show();
      
#if !defined(NEW_ATTRIBUTES)
      ptPreview = new TColorPreview (*((TColor*) nVALUE.pvValue));
#else
      magic_pointer<TAttribColor> col = get_color(nVALUE);
      ptPreview = new TColorPreview (col->tValue);
#endif
      ptPreview->set_expand (true);
      ptPreview->show();
      
      ptFrame->add(*ptPreview);

      ptWidget = ptFrame;

      ptPreview->color_changed.connect(bind(slot(&property_change_callback),
					    property_callback_data(this,
								   name,
								   eTYPE,
								   (void*)ptPreview,
								   ptObjectCopy)));
    }
    break;

  case FX_BOOL:
    {
      //      ptToggleButton = new Gtk::ToggleButton ("On");
      ptToggleButton = new Gtk::ToggleButton (name);      
#if !defined(NEW_ATTRIBUTES)
      ptToggleButton->set_state ((GtkStateType&)nVALUE.gValue);
#else
      magic_pointer<TAttribBool> b = get_bool(nVALUE);
      ptToggleButton->set_state ((GtkStateType&)b->tValue);
#endif
      
      ptWidget = ptToggleButton;

      ptToggleButton->toggled.connect(bind(slot(&property_change_callback),
					   property_callback_data(this,
								  name,
    								  eTYPE,
								  (void*)ptToggleButton,
								  ptObjectCopy)));
    }
    break;

  case FX_CAMERA:
    {
      ptWidget = NULL;
    }
    break;

  case FX_RENDERER:
    {
      ptWidget = NULL;
    }
    break;

  case FX_BSDF:
    {
      ptWidget = new Gtk::Label("Cannot Change Now");
    }
    break;

  case FX_OBJECT_FILTER:
    {
      ptWidget = NULL;
    }
    break;

  case FX_MATERIAL:
    {
      ptWidget = new Gtk::Label("Cannot Change Now");
    }
    break;

  case FX_IMAGE:
    {
      ptWidget = new Gtk::Label("Cannot Change Now");
    }
    break;

  case FX_VECTOR:
    {
#if !defined(NEW_ATTRIBUTES)      
      tVector = *((TVector*) nVALUE.pvValue);
#else
      magic_pointer<TAttribVector> vec = get_vector(nVALUE);
      tVector = vec->tValue;
#endif
      
      ptHBox = new Gtk::HBox;

      ptAdjustment = new Gtk::Adjustment (tVector.x(), -FLT_MAX, FLT_MAX, 1, 10, 10);
      ptWidget = ptSB = new Gtk::SpinButton (*ptAdjustment, (gfloat)0.0, 3);
      ptSB->changed.connect(bind(slot(&property_change_callback),
				 property_callback_data(this,
							name,
							eTYPE,
							(void*)ptSB,
							ptObjectCopy,
							0)));      
      ptWidget->show();

      ptSB->set_update_policy (GTK_UPDATE_ALWAYS);

      ptHBox->pack_start (*ptWidget);
      
      ptAdjustment = new Gtk::Adjustment (tVector.y(), -FLT_MAX, FLT_MAX, 1, 10, 10);
      ptWidget = ptSB = new Gtk::SpinButton (*ptAdjustment, (gfloat)0.0, 3);
      ptSB->changed.connect(bind(slot(&property_change_callback),
				 property_callback_data(this,
							name,
							eTYPE,
							(void*)ptSB,
							ptObjectCopy,
							1)));            
      ptWidget->show();

      ptSB->set_update_policy (GTK_UPDATE_ALWAYS);
      
      ptHBox->add (*ptWidget);
      
      ptAdjustment = new Gtk::Adjustment (tVector.z(), -FLT_MAX, FLT_MAX, 1, 10, 10);
      ptWidget = ptSB = new Gtk::SpinButton (*ptAdjustment, (gfloat)0.0, 3);
      ptSB->changed.connect(bind(slot(&property_change_callback),
				 property_callback_data(this,
							name,
							eTYPE,
							(void*)ptSB,
							ptObjectCopy,
							2)));            
      ptWidget->show();

      ptSB->set_update_policy (GTK_UPDATE_ALWAYS);

      ptHBox->add (*ptWidget);

      ptWidget = ptHBox;
    }
    break;

  case FX_VECTOR2:
    {
#if !defined(NEW_ATTRIBUTES)
      tVector2 = *((TVector2*) nVALUE.pvValue);
#else
      magic_pointer<TAttribVector2> vec2 = get_vector2(nVALUE);
      tVector2 = vec2->tValue;
#endif
      
      ptHBox = new Gtk::HBox;

      ptAdjustment = new Gtk::Adjustment (tVector2.x(), -FLT_MAX, FLT_MAX, 1, 10, 10);
      ptWidget = ptSB = new Gtk::SpinButton (*ptAdjustment, (float)0.0, 3);
      ptSB->changed.connect(bind(slot(&property_change_callback),
				 property_callback_data(this,
							name,
							eTYPE,
							(void*)ptSB,
							ptObjectCopy,
							0)));            
      ptWidget->show();

      ptSB->set_update_policy (GTK_UPDATE_ALWAYS);

      ptHBox->pack_start (*ptWidget);
      
      ptAdjustment = new Gtk::Adjustment (tVector2.y(), -FLT_MAX, FLT_MAX, 1, 10, 10);
      ptWidget = ptSB = new Gtk::SpinButton (*ptAdjustment, (gfloat)0.0, 3);
      ptSB->changed.connect(bind(slot(&property_change_callback),
				 property_callback_data(this,
							name,
							eTYPE,
							(void*)ptSB,
							ptObjectCopy,
							1)));
      ptWidget->show();

      ptSB->set_update_policy (GTK_UPDATE_ALWAYS);
      
      ptHBox->add (*ptWidget);
      
      ptWidget = ptHBox;
    }
    break;
  default:
    {
      ptWidget = new Gtk::Label;

      ((Gtk::Entry*) ptWidget)->set_text ("UNKNOWN -- DON'T EDIT");      
    }
    break;    
  }

  return ptWidget;

}  /* createValueWidget() */


Gtk::Widget* TObjectPropertiesDialog::createInfoWidget (void)
{

  Gtk::Table*   ptTable;
  Gtk::Label*   ptLabel;

  ptTable = new Gtk::Table (2, 2, 0);
  ptTable->set_border_width (5);

  ptLabel = new Gtk::Label ("Class name :");
  ptLabel->set_alignment (0, 0.5);
  ptLabel->show();

  ptTable->attach (*ptLabel, 0, 1, 0, 1, GTK_EXPAND | GTK_FILL, GTK_FILL, 5, 5);

  ptLabel = new Gtk::Label (ptObject->className().c_str());
  ptLabel->set_alignment (0, 0.5);
  ptLabel->show();

  ptTable->attach (*ptLabel, 1, 2, 0, 1, GTK_EXPAND | GTK_FILL, GTK_FILL, 5, 5);

  ptLabel = new Gtk::Label ("Class type :");
  ptLabel->set_alignment (0, 0.5);
  ptLabel->show();

  ptTable->attach (*ptLabel, 0, 1, 1, 2, GTK_EXPAND | GTK_FILL, GTK_FILL, 5, 5);

  ptLabel = new Gtk::Label (TBaseClass::classTypeString (ptObject->classType()).c_str());
  ptLabel->set_alignment (0, 0.5);
  ptLabel->show();

  ptTable->attach (*ptLabel, 1, 2, 1, 2, GTK_EXPAND | GTK_FILL, GTK_FILL, 5, 5);

  return ptTable;
  
}  /* createInfoWidget() */


Gtk::Widget* TObjectPropertiesDialog::createPropertiesWidget (void)
{

  //  Gtk_ScrolledWindow*   ptScrolledWnd;
  Gtk::Table*            ptTable;
  Gtk::Label*            ptLabel;
  Gtk::Widget*           ptWidget;
  TAttributeList        tList;
  NAttribute            nValue;
  size_t                zRow = 0;

  
  ptObject->getAttributeList (tList);

  /*
    ptScrolledWnd = new Gtk_ScrolledWindow;
    ptScrolledWnd->set_policy (GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    ptScrolledWnd->show();
  */
  
  ptTable = new Gtk::Table (tList.size(), 2, 0);
  ptTable->set_border_width (5);

  //  ptScrolledWnd->add (ptTable);

  ptTable->show();
  
  for (TAttributeList::const_iterator tIter = tList.begin(); ( tIter != tList.end() ) ;tIter++)
  {
    ptLabel = new Gtk::Label (tIter->first.c_str());
    assert ( ptLabel );
    ptLabel->set_alignment (0, 0.5);
    ptLabel->show();

    ptTable->attach (*ptLabel, 0, 1, zRow, zRow + 1, GTK_FILL, GTK_FILL, 2, 5);

    ptObject->getAttribute (tIter->first, nValue);
    ptWidget = createValueWidget (tIter->first, tIter->second, nValue);

    if ( ptWidget )
    {
      ptWidget->show();

      // Cleanup for a boolean value.
      if( tIter->second == FX_BOOL )
      {
	ptLabel->set_text("");
      }
      
      ptTable->attach (*ptWidget, 1, 2, zRow, zRow + 1, GTK_EXPAND | GTK_FILL | GTK_SHRINK, GTK_FILL);
      
    }
    
    zRow++;
  }

  return ptTable;
  
}  /* createPropertiesWidget() */


Gtk::Widget* TObjectPropertiesDialog::createStatusWidget (void)
{

  Gtk::Table*   ptTable;

  ptTable = new Gtk::Table (2, 2, 0);
  ptTable->set_border_width (5);

  return ptTable;
  
}  /* createStatusWidget() */


TObjectPropertiesDialog::TObjectPropertiesDialog (TProcedural* ptOBJECT)
{
  string          tTitle;
  Gtk::Notebook*   ptNotebook;
  Gtk::Label*      ptLabel;
  Gtk::Widget*     ptWidget;
  Gtk::Button*     ptButton;

  assert ( ptOBJECT );
  
  ptObject = ptOBJECT;

  // Make a copy of the object so that it can be changed, and the values will
  // not be updated in the original until 'ok' is pressed...
  ptObjectCopy = (TProcedural*)TClassManager::_newObject(ptOBJECT->className(),
							 ptOBJECT);
  // Copy the attributes from the original to the working copy.
  attribute_copy(ptOBJECT, ptObjectCopy);  

  ptNotebook = new Gtk::Notebook;
  ptNotebook->set_tab_border (5);
  ptNotebook->set_border_width (5);
  ptNotebook->set_scrollable (1);
  ptNotebook->show();

  get_vbox()->add (*ptNotebook);

  ptLabel = new Gtk::Label ("Info");
  ptLabel->show();

  ptWidget = createInfoWidget();
  ptWidget->show();
  ptNotebook->append_page (*ptWidget, *ptLabel);
  
  ptLabel = new Gtk::Label ("Properties");
  ptLabel->show();

  ptWidget = createPropertiesWidget();
  ptWidget->show();
  ptNotebook->append_page (*ptWidget, *ptLabel);

  ptLabel = new Gtk::Label ("Status");
  ptLabel->show();
  
  ptWidget = createStatusWidget();
  ptWidget->show();
  ptNotebook->append_page (*ptWidget, *ptLabel);

  ptOkButton = new Gtk::Button ("Ok");
  ptOkButton->show();
  get_action_area()->pack_start (*ptOkButton);

  ptButton = new Gtk::Button ("Cancel");
  ptButton->show();
  ptButton->clicked.connect(bind(slot(&_cancelCB), this));
  get_action_area()->pack_start (*ptButton);

  
  tTitle = string ("Properties - ") + ptOBJECT->className();
  set_title (tTitle.c_str());

  set_usize (250, -1);



  
}  /* TObjectPropertiesDialog() */

TObjectPropertiesDialog::~TObjectPropertiesDialog()
{
  delete ptObjectCopy;
  delete ptOkButton;
}

void TObjectPropertiesDialog::accept_changes()
{
  // Copy the attributes from the copy back over to the original.
  attribute_copy(ptObjectCopy, ptObject);
  /*
  NAttribute attrib;
  TAttributeList tal;

  ptObject->getAttributeList (tal);
  
  for(vector<string>::iterator i = modified_attributes.begin();
      i != modified_attributes.end();
      ++i)
  {
    cout << "Copying attribute " << *i << endl;
    EAttribType type = tal[*i];
    if( ( ptObjectCopy->getAttribute(*i, attrib) != FX_ATTRIB_OK ) || 
	( ptObject->setAttribute(*i, attrib, type) != FX_ATTRIB_OK ) )
    {
      cerr << "Error: accept_changes: could not copy attribute "
	   << "\"" << *i << "\""
	   << endl;      
    }
  }
  */
}


static void attribute_copy(TProcedural* source, TProcedural* dest)
{
  if(source == NULL)
  {
    cout << "Null source for attribute copy." << endl;
    return;
  }
  if(dest == NULL)
  {
    cout << "Null dest for attribute copy." << endl;
    return;
  }  
  
  TAttributeList aList;
  NAttribute     nValue;
  source->getAttributeList(aList);

  for(TAttributeList::iterator attribute = aList.begin();
      attribute != aList.end();
      ++attribute)
  {
    if(source->getAttribute(attribute->first, nValue) == FX_ATTRIB_OK)
    {
      if(dest->setAttribute(attribute->first, nValue, attribute->second) !=
	 FX_ATTRIB_OK)
      {
	cerr << "Error: attribute_copy: could not copy attribute \""
	     << attribute->first << "\""
	     << endl;
      }
    }
  }
}

static void property_change_callback(property_callback_data tPCD)
{
  cout << __FUNCTION__ << endl;
  NAttribute nValue;
  TProcedural* dest_object = tPCD.destObject;
  bool changed = false;
  static const char* unsup_title = "Not yet supported";
  static const char* unsup_text  = "Changes to this type of data are not currently supported";  
  
  
  switch(tPCD.eType)
  {
  case FX_NONE:
    {
      MessageDialog(unsup_title, unsup_text);
    }
    break;

  case FX_STRING_LIST:    
  case FX_STRING:
    {
      cout << "string" << endl;
#if !defined(NEW_ATTRIBUTES)
      nValue.pvValue = (void*)((Gtk::Entry*)tPCD.dataContainer)->get_text().c_str();
#else
      nValue = new TAttribString (((Gtk::Entry*)tPCD.dataContainer)->get_text());
#endif
      dest_object->setAttribute(tPCD.attributeName, nValue, tPCD.eType);
      changed = true;
    }
    break;

  case FX_REAL:
    {
      cout << "real" << endl;      
#if !defined(NEW_ATTRIBUTES)
      nValue.dValue = ((Gtk::SpinButton*)tPCD.dataContainer)->get_value_as_float();
#else
      nValue = new TAttribReal (((Gtk::SpinButton*)tPCD.dataContainer)->get_value_as_float());      
#endif
      cout << "Have value... Setting (" << tPCD.attributeName << ") ." << endl;
      dest_object->setAttribute(tPCD.attributeName, nValue, tPCD.eType);
      changed = true;      
    }
    break;
#if defined(NEW_ATTRIBUTES)
  case FX_INTEGER:
    {
      cout << "int" << endl;      
      nValue = new TAttribInt (((Gtk::SpinButton*)tPCD.dataContainer)->get_value_as_int());
      dest_object->setAttribute(tPCD.attributeName, nValue, tPCD.eType);
      changed = true;      
    }
    break;
#endif

  case FX_COLOR:
    {
      cout << "color" << endl;      
#if !defined(NEW_ATTRIBUTES)	
      MessageDialog(unsup_title, unsup_text);
#else
      nValue = new TAttribColor (((TColorPreview*)tPCD.dataContainer)->color());
      dest_object->setAttribute(tPCD.attributeName, nValue, tPCD.eType);
      changed = true;      
#endif      
    }
    break;

  case FX_BOOL:
    {
      cout << "bool" << endl;      
#if !defined(NEW_ATTRIBUTES)
      nValue.gValue = ((Gtk::ToggleButton*)tPCD.dataContainer)->get_active();
#else
      nValue = new TAttribBool (((Gtk::ToggleButton*)tPCD.dataContainer)->get_active());
#endif
      dest_object->setAttribute(tPCD.attributeName, nValue, tPCD.eType);
      changed = true;      
    }
    break;

  case FX_CAMERA:
    {
      MessageDialog(unsup_title, unsup_text);      
    }
    break;

  case FX_RENDERER:
    {
      MessageDialog(unsup_title, unsup_text);      
    }
    break;

  case FX_BSDF:
    {
      MessageDialog(unsup_title, unsup_text);      
    }
    break;

  case FX_OBJECT_FILTER:
    {
      MessageDialog(unsup_title, unsup_text);      
    }
    break;

  case FX_MATERIAL:
    {
      MessageDialog(unsup_title, unsup_text);      
    }
    break;

  case FX_IMAGE:
    {
      MessageDialog(unsup_title, unsup_text);      
    }
    break;

  case FX_VECTOR:
    {
      cout << "vector" << endl;      
      dest_object->getAttribute(tPCD.attributeName, nValue);
#if !defined(NEW_ATTRIBUTES)
      TVector tmp_vector(*(TVector*)nValue.pvValue);
#else
      magic_pointer<TAttribVector> vec = get_vector(nValue);
      TVector tmp_vector(vec->tValue);
#endif
      tmp_vector[tPCD.extraData] = ((Gtk::SpinButton*)tPCD.dataContainer)->get_value_as_float();
#if !defined(NEW_ATTRIBUTES)      
      nValue.pvValue = (void*)&tmp_vector;
#else
      nValue = new TAttribVector(tmp_vector);
#endif
      dest_object->setAttribute(tPCD.attributeName, nValue, tPCD.eType);
      changed = true;      
    }
    break;

  case FX_VECTOR2:
    {
      cout << "vector2" << endl;      
      dest_object->getAttribute(tPCD.attributeName, nValue);
#if !defined(NEW_ATTRIBUTES)
      TVector2 tmp_vector(*(TVector2*)nValue.pvValue);
#else
      magic_pointer<TAttribVector2> vec = get_vector2(nValue);
      TVector2 tmp_vector(vec->tValue);
#endif
      tmp_vector[tPCD.extraData] = ((Gtk::SpinButton*)tPCD.dataContainer)->get_value_as_float();
#if !defined(NEW_ATTRIBUTES)
      nValue.pvValue = (void*)&tmp_vector;
#else
      nValue = new TAttribVector2 (tmp_vector);
#endif
      dest_object->setAttribute(tPCD.attributeName, nValue, tPCD.eType);
      changed = true;      
    }
    break;
  default:
    {
      MessageDialog(unsup_title, unsup_text);      
    }
    break;        
  }
  /*
  if( changed )
  {
    cout << "Changed!" << endl;
    string name = tPCD.attributeName;
    vector<string>& vec = tPCD.ptDlg->modified_attributes;

    vec.push_back(name);
  }
  */
}



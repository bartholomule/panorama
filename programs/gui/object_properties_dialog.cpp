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
  string attributeName;
  EAttribType eType;
  void* dataContainer;
  TProcedural* destObject;
  int extraData; // Used to contain info such as the index into the vector...

  property_callback_data(const string& aName,
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
  Gtk::Adjustment*    ptAdjustment;
  Gtk::HBox*          ptHBox;
  Gtk::Frame*         ptFrame;
  Gtk::ToggleButton*  ptToggleButton;
  TColorPreview*      ptPreview;
  Gtk::Widget*        ptWidget = NULL;
  Gtk::SpinButton*    ptSB;

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
      
      entry->set_text ((char*) nVALUE.pvValue);
      entry->changed.connect(bind(slot(&property_change_callback),
				  property_callback_data(name,
							 eTYPE,
							 (void*)entry,
							 ptObjectCopy)));
							 
    }
    break;

  case FX_REAL:
    {
      ptAdjustment = new Gtk::Adjustment (nVALUE.dValue, -FLT_MAX, FLT_MAX, 1, 10, 10);
      ptWidget = ptSB = new Gtk::SpinButton (*ptAdjustment, 0.0, 3);

      ptSB->set_update_policy (GTK_UPDATE_ALWAYS);

      ptSB->changed.connect(bind(slot(&property_change_callback),
				 property_callback_data(name,
							eTYPE,
							(void*)ptSB,
							ptObjectCopy)));      
    }
    break;

  case FX_COLOR:
    {
      ptPreview = new TColorPreview (*((TColor*) nVALUE.pvValue));
      cout << "Showing" << endl;
      ptPreview->show();

      ptFrame = new Gtk::Frame;
      ptFrame->show();

      cout << "Adding" << endl;
      //      ptFrame->add (*ptPreview);
      //      ptFrame->show();

      cout << "a2" << endl;
      Gtk::Window* tmp_wnd = manage(new Gtk::Window());
      Gtk::VBox* tmp_box = manage(new Gtk::VBox());
      Gtk::Label* tmp_label = manage(new Gtk::Label("BARF"));
      Gtk::Frame* tmp_frame = manage(new Gtk::Frame);
      tmp_frame->add(*ptPreview);
      tmp_box->pack_start(*tmp_frame); //add(*ptPreview);
      tmp_box->pack_start(*tmp_label);
      tmp_wnd->add(*tmp_box);
      tmp_label->show();
      tmp_frame->show();
      tmp_box->show();
      tmp_wnd->show();

      cout << "Returning" << endl;
      
      ptWidget = ptFrame;
    }
    break;

  case FX_BOOL:
    {
      ptToggleButton = new Gtk::ToggleButton ("On");
      ptToggleButton->set_state ((GtkStateType&)nVALUE.gValue);
      
      ptWidget = ptToggleButton;

      ptToggleButton->toggled.connect(bind(slot(&property_change_callback),
					   property_callback_data(name,
    								  eTYPE,
								  (void*)ptToggleButton,
								  ptObjectCopy)));
    }
    break;

  case FX_CAMERA:
    {
      ptWidget = new Gtk::Combo;
    }
    break;

  case FX_RENDERER:
    {
      ptWidget = new Gtk::Combo;
    }
    break;

  case FX_BSDF:
    {
      ptWidget = new Gtk::Combo;
    }
    break;

  case FX_OBJECT_FILTER:
    {
      ptWidget = new Gtk::Combo;
    }
    break;

  case FX_MATERIAL:
    {
      ptWidget = new Gtk::Combo;
    }
    break;

  case FX_IMAGE:
    {
      ptWidget = new Gtk::Combo;
    }
    break;

  case FX_VECTOR:
    {
      tVector = *((TVector*) nVALUE.pvValue);
      
      ptHBox = new Gtk::HBox;

      ptAdjustment = new Gtk::Adjustment (tVector.x(), -FLT_MAX, FLT_MAX, 1, 10, 10);
      ptWidget = ptSB = new Gtk::SpinButton (*ptAdjustment, (gfloat)0.0, 3);
      ptSB->changed.connect(bind(slot(&property_change_callback),
				 property_callback_data(name,
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
				 property_callback_data(name,
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
				 property_callback_data(name,
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
      tVector2 = *((TVector2*) nVALUE.pvValue);
      
      ptHBox = new Gtk::HBox;

      ptAdjustment = new Gtk::Adjustment (tVector2.x(), -FLT_MAX, FLT_MAX, 1, 10, 10);
      ptWidget = ptSB = new Gtk::SpinButton (*ptAdjustment, (float)0.0, 3);
      ptSB->changed.connect(bind(slot(&property_change_callback),
				 property_callback_data(name,
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
				 property_callback_data(name,
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
  cout << "Making a copy of a " << ptOBJECT->className() << endl;
  ptObjectCopy = (TProcedural*)TClassManager::_newObject(ptOBJECT->className(),NULL);
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
  cout << "Copying Attributes from " << source->className()
       << " to " << dest->className() << endl;
  
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
  static const char* unsup_title = "Not yet supported";
  static const char* unsup_text  = "Changes to this type of data are not currently supported";  
  
  
  switch(tPCD.eType)
  {
  case FX_NONE:
    {
      MessageDialog(unsup_title, unsup_text);
    }
    break;
    
  case FX_STRING:
    {
      nValue.pvValue = (void*)((Gtk::Entry*)tPCD.dataContainer)->get_text().c_str();
      cout << "Setting string value to " << (char*)nValue.pvValue << endl;
      dest_object->setAttribute(tPCD.attributeName, nValue, tPCD.eType);
    }
    break;

  case FX_REAL:
    {
      nValue.dValue = ((Gtk::SpinButton*)tPCD.dataContainer)->get_value_as_float();
      cout << "Setting float value to " << nValue.dValue << endl;
      dest_object->setAttribute(tPCD.attributeName, nValue, tPCD.eType);      
    }
    break;

  case FX_COLOR:
    {
      MessageDialog(unsup_title, unsup_text);      
    }
    break;

  case FX_BOOL:
    {
      nValue.gValue = ((Gtk::ToggleButton*)tPCD.dataContainer)->get_active();
      cout << "Setting bool value to " << nValue.gValue << endl;
      dest_object->setAttribute(tPCD.attributeName, nValue, tPCD.eType);
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
      dest_object->getAttribute(tPCD.attributeName, nValue);
      TVector tmp_vector(*(TVector*)nValue.pvValue);
      tmp_vector[tPCD.extraData] = ((Gtk::SpinButton*)tPCD.dataContainer)->get_value_as_float();
      nValue.pvValue = (void*)&tmp_vector;
      cerr << "Setting vector value to ";
      ((TVector*)nValue.pvValue)->printDebug();
      dest_object->setAttribute(tPCD.attributeName, nValue, tPCD.eType);      
    }
    break;

  case FX_VECTOR2:
    {
      dest_object->getAttribute(tPCD.attributeName, nValue);
      TVector2 tmp_vector(*(TVector2*)nValue.pvValue);
      tmp_vector[tPCD.extraData] = ((Gtk::SpinButton*)tPCD.dataContainer)->get_value_as_float();
      nValue.pvValue = (void*)&tmp_vector;
      cerr << "Setting vector value to ";
      ((TVector2*)nValue.pvValue)->printDebug();      
      dest_object->setAttribute(tPCD.attributeName, nValue, tPCD.eType);            
    }
    break;
  default:
    {
      MessageDialog(unsup_title, unsup_text);      
    }
    break;        
  }
}

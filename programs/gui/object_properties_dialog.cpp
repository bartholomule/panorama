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
#include "object_properties_dialog.h"
#include "color_preview.h"

static void _cancelCB (TObjectPropertiesDialog* ptDIALOG)
{

  ptDIALOG->hide();
  delete ptDIALOG;
  
}  /* _cancelCB() */

                 
Gtk::Widget* TObjectPropertiesDialog::createValueWidget (EAttribType eTYPE, NAttribute nVALUE)
{

  TVector             tVector;
  TVector2            tVector2;
  Gtk::Adjustment*    ptAdjustment;
  Gtk::HBox*          ptHBox;
  Gtk::Frame*         ptFrame;
  Gtk::ToggleButton*  ptToggleButton;
  TColorPreview*      ptPreview;
  Gtk::Widget*        ptWidget = NULL;

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
      ptWidget = new Gtk::Entry;
      
      ((Gtk::Entry*) ptWidget)->set_text ((char*) nVALUE.pvValue);
    }
    break;

    case FX_REAL:
    {
      ptAdjustment = new Gtk::Adjustment (nVALUE.dValue, -FLT_MAX, FLT_MAX, 1, 10, 10);

      ptWidget = new Gtk::SpinButton (*ptAdjustment, 0.0, 3);

      ((Gtk::SpinButton*) ptWidget)->set_update_policy (GTK_UPDATE_ALWAYS);
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

      ptWidget = new Gtk::SpinButton (*ptAdjustment, (gfloat)0.0, 3);
      ptWidget->show();

      ((Gtk::SpinButton*) ptWidget)->set_update_policy (GTK_UPDATE_ALWAYS);

      ptHBox->pack_start (*ptWidget);
      
      ptAdjustment = new Gtk::Adjustment (tVector.y(), -FLT_MAX, FLT_MAX, 1, 10, 10);

      ptWidget = new Gtk::SpinButton (*ptAdjustment, (gfloat)0.0, 3);
      ptWidget->show();

      ((Gtk::SpinButton*) ptWidget)->set_update_policy (GTK_UPDATE_ALWAYS);
      
      ptHBox->add (*ptWidget);
      
      ptAdjustment = new Gtk::Adjustment (tVector.z(), -FLT_MAX, FLT_MAX, 1, 10, 10);

      ptWidget = new Gtk::SpinButton (*ptAdjustment, (gfloat)0.0, 3);
      ptWidget->show();

      ((Gtk::SpinButton*) ptWidget)->set_update_policy (GTK_UPDATE_ALWAYS);

      ptHBox->add (*ptWidget);

      ptWidget = ptHBox;
    }
    break;

    case FX_VECTOR2:
    {
      tVector2 = *((TVector2*) nVALUE.pvValue);
      
      ptHBox = new Gtk::HBox;

      ptAdjustment = new Gtk::Adjustment (tVector2.x(), -FLT_MAX, FLT_MAX, 1, 10, 10);

      ptWidget = new Gtk::SpinButton (*ptAdjustment, (float)0.0, 3);
      ptWidget->show();

      ((Gtk::SpinButton*) ptWidget)->set_update_policy (GTK_UPDATE_ALWAYS);

      ptHBox->pack_start (*ptWidget);
      
      ptAdjustment = new Gtk::Adjustment (tVector2.y(), -FLT_MAX, FLT_MAX, 1, 10, 10);

      ptWidget = new Gtk::SpinButton (*ptAdjustment, (gfloat)0.0, 3);
      ptWidget->show();

      ((Gtk::SpinButton*) ptWidget)->set_update_policy (GTK_UPDATE_ALWAYS);
      
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
    ptWidget = createValueWidget (tIter->second, nValue);

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

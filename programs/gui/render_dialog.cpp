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

#include "image_window.h"
#include "render_dialog.h"

void TRenderDialog::toggleZBuffer (Gtk::CheckButton* ptBUTTON)
{

  if ( ptBUTTON->get_active() )
  {
    wNeededBuffers |= FX_ZBUFFER;
  }
  else
  {
    wNeededBuffers &= ~FX_ZBUFFER;
  }
  
}  /* toggleZBuffer() */


void TRenderDialog::toggleNBuffer (Gtk::CheckButton* ptBUTTON)
{
  
  if ( ptBUTTON->get_active() )
  {
    wNeededBuffers |= FX_NBUFFER;
  }
  else
  {
    wNeededBuffers &= ~FX_NBUFFER;
  }
  
}  /* toggleNBuffer() */


TRenderDialog::TRenderDialog (TScene* ptSCENE)
{

  Gtk::Frame*         ptFrame;
  Gtk::VBox*          ptVBox;
  Gtk::Table*         ptTable;
  Gtk::Button*        ptButton;
  Gtk::CheckButton*   ptCButton;
  Gtk::RadioButton*   ptRButton;
  Gtk::RadioButton::Group Group;
  Gtk::Label*         ptLabel;

  wNeededBuffers = 0;
  ptScene        = ptSCENE;
  
  get_vbox()->set_border_width (10);
  get_action_area()->set_border_width (10);


  ptFrame = new Gtk::Frame;
  ptFrame->show();

  ptTable = new Gtk::Table (1, 2, 1);
  ptTable->show();

  ptFrame->add (*ptTable);

  ptVBox = new Gtk::VBox;
  ptVBox->show();

  ptTable->attach (*ptVBox, 0, 1, 0, 1, 0, 0, 5, 5);
    
  ptRButton = new Gtk::RadioButton ("Preview");
  ptRButton->show();

  ptVBox->pack_start (*ptRButton, 1, 1, 0);
  
  Group   = ptRButton->group();
  ptRButton = new Gtk::RadioButton (Group, "Render");
  ptRButton->show();

  ptVBox->pack_start(*ptRButton);

  ptVBox = new Gtk::VBox;
  ptVBox->show();

  ptTable->attach (*ptVBox, 1, 2, 0, 1, 0, 0, 5, 5);
    
  ptLabel = new Gtk::Label ("Buffers to generate:");
  ptLabel->show();

  ptVBox->pack_start(*ptLabel);

  ptCButton = new Gtk::CheckButton ("Normal");
  ptCButton->set_active(true);
  ptCButton->show();

  ptCButton->toggled.connect(bind(slot(this, &TRenderDialog::toggleNBuffer), ptCButton));

  
  ptVBox->add (*ptCButton);
  
  ptCButton = new Gtk::CheckButton ("Distance");
  ptCButton->set_active(true);  
  ptCButton->show();

  ptCButton->toggled.connect(bind(slot(this, &TRenderDialog::toggleZBuffer), ptCButton));


  ptVBox->add (*ptCButton);
  
  get_vbox()->pack_start (*ptFrame);

  ptButton = new Gtk::Button ("Render");
  ptButton->show();

  ptButton->clicked.connect(slot(this, &TRenderDialog::render));
  
  get_action_area()->pack_start (*ptButton, 1, 1, 0);
  
  ptButton = new Gtk::Button ("Cancel");
  ptButton->show();

  ptButton->clicked.connect(slot(this, &TRenderDialog::cancel));
  
  get_action_area()->pack_start (*ptButton);

}  /* TRenderDialog() */


void TRenderDialog::render (void)
{

  TImageWindow*   ptImageWnd;
  
  hide();
  
  if ( ptScene )
  {
    ptScene->addBuffer (wNeededBuffers);
    
    ptScene->initialize();
    
    ptImageWnd = new TImageWindow (ptScene);

    ptImageWnd->show();

    ptImageWnd->gRenderingDone = false;

    ptScene->render (&FinishedRenderLine, ptImageWnd);
      
    ptImageWnd->gRenderingDone = true;
  }

  delete this;
  
}  /* render() */


void TRenderDialog::cancel (void)
{

  hide();
  delete this;
  
}  /* cancel() */

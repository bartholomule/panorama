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
#include "common.h"
#include <gtk--/main.h>
#include "llapi/attribute.h"

using SigC::slot;
using SigC::bind;

TImageWindow::~TImageWindow ()
{
  delete sBuffers.ptImage;
  delete sBuffers.ptZBuffer;
  delete sBuffers.ptNBuffer;
  delete ptPreview;
  delete ptVBox;
  delete ptProgress;
}

TImageWindow::TImageWindow (TScene* ptSCENE):
  ptProgress(NULL)
{
  string             tTitle;
  NAttribute         nAttrib;
  
  gRenderingDone     = false;
  ptScene            = ptSCENE;
  sBuffers.ptImage   = new TImage(*ptScene->buffers()->ptImage);
  if(ptScene->buffers()->ptZBuffer)
  {
    sBuffers.ptZBuffer = new TZBuffer(*ptScene->buffers()->ptZBuffer);
  }
  if(ptScene->buffers()->ptNBuffer)
  {
    sBuffers.ptNBuffer = new TNBuffer(*ptScene->buffers()->ptNBuffer);
  }

  ptVBox = new Gtk::VBox;
  ptVBox->show();
  
  add (*ptVBox);

  ptMenuBar = manage(new Gtk::MenuBar());
  using namespace Gtk::Menu_Helpers;
  MenuList* menu_list;
  Gtk::Menu* image_menu = manage(new Gtk::Menu());
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
  menu_list->push_back(MenuElem("_Filter",
				*manage(createPluginMenu(FX_IMAGE_FILTER_CLASS,
							 imageFilterCB,
							 this))));
  menu_list->push_back(MenuElem("_Help",*help_menu));      

  ptMenuBar->show_all();

  ptVBox->pack_start (*ptMenuBar, 0, 1, 0);

  ptPreview = new Gtk::Preview (GTK_PREVIEW_COLOR);
  ptPreview->size (sBuffers.ptImage->width(), sBuffers.ptImage->height());
  ptPreview->show();

  ptVBox->add (*ptPreview);

  ptScene->imageIO()->getAttribute ("name", nAttrib);

#if !defined(NEW_ATTRIBUTES)
  tTitle = string ("Image - ") + (char*) nAttrib.pvValue;
#else
  magic_pointer<TAttribString> str = get_string(nAttrib);
  if( !!str )
  {
    tTitle = string ("Image - ") + str->tValue;
  }
  else
  {
    tTitle = string ("Image - NO NAME");
  }
#endif
  set_title (tTitle.c_str());
  
}  /* TImageWindow() */


void TImageWindow::saveImage (const string& name)
{

  string   tName = name;

  if( name.empty() )
  {
    if ( ptFileSelection )
    {
      tName = ptFileSelection->get_filename();
      
      ptScene->setOutputFileName (tName);
      
      SBuffers* scene_buffers = ptScene->buffers();
      SBuffers old_buffers = *scene_buffers;
      *scene_buffers = sBuffers;
      
      ptScene->saveImage();
      
      *scene_buffers = old_buffers;
      
      ptFileSelection->hide();
      delete ptFileSelection;
      ptFileSelection = NULL;
    }
  }
  else
  {
    ptScene->setOutputFileName (tName);
    SBuffers* scene_buffers = ptScene->buffers();
    SBuffers old_buffers = *scene_buffers;
    *scene_buffers = sBuffers;
    
    ptScene->saveImage();

    *scene_buffers = old_buffers;
  }
  
}  /* saveImage() */


void TImageWindow::drawRow (size_t zROW)
{

  guchar*        ptRow;
  TColor         tPixel;
  GdkRectangle   tRectangle;

  ptRow = new guchar [3 * sBuffers.ptImage->width() * numPixelCopies];

  for (size_t I = 0; I < numPixelCopies; ++I)
  {
    for (size_t J = 0; ( J < sBuffers.ptImage->width() ) ;J++)
    {
      tPixel = sBuffers.ptImage->getPixel (J, zROW);
      
      tPixel.clamp();
      tPixel = tPixel.convertTo24Bits();

      for( size_t K = 0; K < numPixelCopies; ++K )
      {
	ptRow [(J * numPixelCopies + K) * 3 + 0] = (Byte) tPixel.red();
	ptRow [(J * numPixelCopies + K) * 3 + 1] = (Byte) tPixel.green();
	ptRow [(J * numPixelCopies + K) * 3 + 2] = (Byte) tPixel.blue();
      }
    }
    ptPreview->draw_row (ptRow, 0,
			 zROW * numPixelCopies + I,
			 sBuffers.ptImage->width() * numPixelCopies);
  }
  delete ptRow;

  tRectangle.x      = 0;
  tRectangle.y      = zROW * numPixelCopies;
  tRectangle.width  = sBuffers.ptImage->width() * numPixelCopies;
  tRectangle.height = numPixelCopies;
  
  gtk_widget_draw (GTK_WIDGET (ptPreview->gtkobj()), &tRectangle);
  
}  /* drawRow() */


void TImageWindow::drawImage (void)
{

  for (size_t J = 0; ( J < sBuffers.ptImage->height()) ;J++)
  {
    drawRow (J);
  }
  
}  /* drawImage() */

void TImageWindow::set_progress (size_t line_number)
{
  // Height=sBuffers.ptImage->height();
  gfloat percentage = line_number / gfloat(sBuffers.ptImage->height() - 1);

  if(percentage < 1)
  {
    if(ptProgress == NULL)
    {
      ptProgress = new Gtk::ProgressBar();
      ptProgress->show();
      ptVBox->add (*ptProgress);
    }
    ptProgress->set_percentage(percentage);
  }
  else
  {
    ptProgress->set_percentage(1.0);    
    /*
    ptVBox->remove(*ptProgress);
    ptProgress->hide();
    delete ptProgress;
    */
  }  
}

bool FinishedRenderLine (size_t zROW, void* pvDATA)
{

  TImageWindow*   ptWnd = (TImageWindow*) pvDATA;

  while ( Gtk::Main::events_pending() )
  {
    Gtk::Main::iteration();
  }

  ptWnd->drawRow (zROW);

  // Update progress bar.
  ptWnd->set_progress(zROW);

  return ptWnd->is_visible();
}  /* FinishedRenderLine() */

void FinishedRendering (void* pvDATA)
{
  TImageWindow*   ptWnd = (TImageWindow*) pvDATA;

  while ( Gtk::Main::events_pending() )
  {
    Gtk::Main::iteration();
  }
  for( size_t row = 0; row < ptWnd->image_height(); ++row)
  {
    ptWnd->drawRow (row);  
  }
  while ( Gtk::Main::events_pending() )
  {
    Gtk::Main::iteration();
  }  
}

bool FilterUserUpdate (double percentage, void* pvDATA)
{

  TImageWindow*   ptWnd = (TImageWindow*) pvDATA;

  while ( Gtk::Main::events_pending() )
  {
    Gtk::Main::iteration();
  }

  //  ptWnd->drawRow (zROW);

  // Update progress bar.
  ptWnd->set_progress(int(percentage * ptWnd->image_height()));

  return true;
  
}  /* FilterUserUpdate() */



void TImageWindow::filterImage(TImageFilter* ptFilter)
{
  Word existing_buffers = 0;
  if(sBuffers.ptZBuffer != NULL)
  {
    existing_buffers |= FX_ZBUFFER;
  }
  if(sBuffers.ptNBuffer != NULL)
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

  ptFilter->setUserFunction (&FilterUserUpdate, (void*)this);
  ptFilter->setScene(ptScene);
  ptFilter->filter(sBuffers);
#if DEBUG_IT
  GOM.debug() << "Done with filter..." << endl;
#endif
  // Refresh the screen here...
  drawImage();
} /* filterImage() */

void TImageWindow::render(bool preview)
{
  SBuffers orig_buffers;
  if( !preview )
  {
    numPixelCopies = 1;
  }
  else
  {
    orig_buffers = sBuffers;

    // Find something that will allow an even number of pixel divisions (no
    // remainder).
    numPixelCopies = 4;
    while( (sBuffers.ptImage->width()  % numPixelCopies != 0) ||
	   (sBuffers.ptImage->height() % numPixelCopies != 0) )
    {
      --numPixelCopies;
    }

    ptScene->setWidth  (orig_buffers.ptImage->width()  / numPixelCopies);
    ptScene->setHeight (orig_buffers.ptImage->height() / numPixelCopies);
    ptScene->camera()->setImageResolution((orig_buffers.ptImage->width()  /
					   numPixelCopies),
					  (orig_buffers.ptImage->height()  /
					   numPixelCopies));
    ptScene->camera()->initialize();
				     
    
    sBuffers.ptImage = new TImage(orig_buffers.ptImage->width()  / numPixelCopies,
				  orig_buffers.ptImage->height() / numPixelCopies);
    if(orig_buffers.ptZBuffer)
    {
      sBuffers.ptZBuffer = new TZBuffer(orig_buffers.ptImage->width(),
					orig_buffers.ptImage->height());
    }
    if(orig_buffers.ptNBuffer)
    {
      sBuffers.ptNBuffer = new TNBuffer(orig_buffers.ptImage->width(),
					orig_buffers.ptImage->height());
    }    
  }
  
  gRenderingDone = false;
  TRenderer* rend = ptScene->renderer()->clone_new();
  
  rend->setUserFunction(&FinishedRenderLine,
			&FinishedRendering,
			(void*)this);
  rend->render (sBuffers);

  gRenderingDone = true;

  if( preview )
  {
    SBuffers temp = sBuffers;
    sBuffers = orig_buffers;

    ptScene->setWidth  (sBuffers.ptImage->width());
    ptScene->setHeight (sBuffers.ptImage->height());
    ptScene->camera()->setImageResolution(sBuffers.ptImage->width(),
					  sBuffers.ptImage->height());
    ptScene->camera()->initialize();
    
    for( size_t y = 0; y < sBuffers.ptImage->height(); ++y )
    {
      size_t y1 = y / numPixelCopies;	
      for( size_t x = 0; x < sBuffers.ptImage->width(); ++x )
      {
	// BARF
	size_t x1 = x / numPixelCopies;
	sBuffers.ptImage->setPixel(x, y, temp.ptImage->getPixel(x1,y1));
	
	if( sBuffers.ptZBuffer )
	{
	  sBuffers.ptZBuffer->setPixel(x, y,
				       temp.ptZBuffer->getPixel(x1,y1));
				       
	}
	if( sBuffers.ptNBuffer )
	{
	  sBuffers.ptNBuffer->setPixel(x, y,
				       temp.ptNBuffer->getPixel(x1,y1));
				       
	}	
      } // x
    } // y

    delete temp.ptImage;
    delete temp.ptZBuffer;
    delete temp.ptNBuffer;

    // Redraw what I have just copied into the buffer...
    numPixelCopies = 1;
    drawImage();    
  } // image copied (preview)
  
  delete rend;
} /* render() */

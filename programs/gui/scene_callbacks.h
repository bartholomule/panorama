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

#ifndef _SCENE_CALLBACKS__
#define _SCENE_CALLBACKS__

class TSceneWindow;

void sceneMenuCB (const char* s);
void sceneQuitCB ();
void sceneCloseCB (TSceneWindow* ptWnd);
void sceneNewCB (TSceneWindow* ptWnd);
void sceneReplaceCB (TSceneWindow* ptWnd);
void sceneRenderCB (TSceneWindow* ptWnd);
void scenePluginWindowCB ();
void sceneMaterialWindowCB ();

void sceneCancelCB (TSceneWindow* ptWND);
void sceneCameraCB (TSceneWindow* ptWND, string plugin_name);
void sceneLightCB  (TSceneWindow* ptWND, string plugin_name);
    
#endif  /* _SCENE_CALLBACKS__ */

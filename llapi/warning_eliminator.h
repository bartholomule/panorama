/*
*  Copyright (C) 2002 Kevin Harris
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

#if       !defined(KH_WARNING_ELIMINATOR_H)
#define            KH_WARNING_ELIMINATOR_H

#if defined(_MSC_VER)
// ---------------------------------------------------------------------------
// Get rid of messages for using maps, vectors, lists, etc.
// MSVC++ has problems with template names expanding too large.  To disable
// some nasty warnings, the following pragmas can be used:
// ---------------------------------------------------------------------------
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#endif /* defined(_MSC_VER) */

#endif /* !defined(KH_WARNING_ELIMINATOR_H) */

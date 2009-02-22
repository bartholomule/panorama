/*
 * $Id: BaseClass.hpp,v 1.1.2.1 2009/02/22 10:09:56 kpharris Exp $
 *
 * Part of GNU Panorama -- A framework for graphics production.
 * Copyright (C) 2009 Kevin Harris
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#if       !defined(PANORAMA_BASECLASS_HPP)
#define            PANORAMA_BASECLASS_HPP

/*
 * @author Kevin Harris
 */

#include "panorama/common/StringDumpable.hpp"
#include "panorama/common/Cloneable.hpp"

namespace panorama
{
	/**
	 * The root (base class) of most panorama structures.  This contains no
	 * useful interface or data in itself, but forces multiple pure virtual
	 * classes as ancestors.
	 *
	 * @author Kevin Harris <kpharris@users.sourceforge.net>
	 * @version $Revision: 1.1.2.1 $
	 *
	 */
	class BaseClass : public StringDumpable, public Cloneable
	{
	public:
		BaseClass();
		virtual ~BaseClass();
		BaseClass(const BaseClass& old);
		BaseClass& operator= (const BaseClass& old);
	}; // class BaseClass

	typedef blocxx::IntrusiveReference<BaseClass> BaseClassRef;

} // namespace panorama

#endif /* !defined(PANORAMA_BASECLASS_HPP) */


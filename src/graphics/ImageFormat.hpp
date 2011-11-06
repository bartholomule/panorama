/*
 * $Id: ImageFormat.hpp,v 1.1.2.1 2011/11/06 03:30:51 kpharris Exp $
 *
 * Part of GNU Panorama
 *
 * Copyright (C) 2011 Kevin Harris
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

#if       !defined(PANORAMA_IMAGE_FORMAT_HPP)
#define            PANORAMA_IMAGE_FORMAT_HPP

#include "panorama/common/Capabilities.hpp"
#include "blocxx/Array.hpp"

namespace panorama
{
	// Image formats have two capabilities: Color and Image.
	// They also have specific file extensions and a tag for use by an image writer.
	class ImageFormat
	{
	public:
		// This tag allows use in the StringDumpable.hpp toString functions
		// without requiring the overridden virtual functions.
		typedef bool CanBeStringDumpedTag;
		typedef unsigned long TagType;
	private:
		ImageCapabilities m_imageCapabilities;
		ColorCapabilities m_colorCapabilities;
		blocxx::StringArray m_fileExtensions;
		blocxx::String m_preferredExtension;
		blocxx::String m_formatName;
		TagType m_formatTag;
	public:
		ImageFormat(const ImageCapabilities& imageCaps, const ColorCapabilities& colorCaps,
			const blocxx::StringArray& extensions, const blocxx::String& preferredExtension,
			const blocxx::String& givenFormatName, TagType tag);

		ImageCapabilities imageCapabilities() const;
		ColorCapabilities colorCapabilities() const;
		blocxx::StringArray defaultFileExtensions() const;
		blocxx::String preferredFileExtension() const;
		blocxx::String formatName() const;
		TagType formatTag() const;

		// For string dumping.
		void collectInternalMembers(MemberStringDumpCollector& collector) const;
		blocxx::String toString(const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE ) const;
		blocxx::String name() const { return "ImageFormat"; }
	};
} // namespace panorama

#endif /* !defined(PANORAMA_IMAGE_FORMAT_HPP) */

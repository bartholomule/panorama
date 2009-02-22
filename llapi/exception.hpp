/*
 *  Copyright (C) 2008 Kevin Harris
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
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

#if !defined(PANORAMA_EXCEPTION_HPP_INCLUDED)
#define PANORAMA_EXCEPTION_HPP_INCLUDED

#include <iosfwd>
#include <exception>

namespace panorama
{
  /**
   * The base class for a more complete std::exception.  This includes
   * file ane line information.
   */
  class Exception : public std::exception
  {
  public:
    Exception(const char* file, int line, const char* text);

    const char* getFilename() const throw();
    int getLineNumber() const throw();
    const char* getText() const throw();

    virtual const char* what() const throw();
    virtual const char* name() const throw();

  private:
    const char* m_filename;
    int m_lineNumber;
    const char* m_exceptionText;
  };

  std::ostream& operator<<(std::ostream& o, const Exception& e);

#define THROW(type, message) throw type(__FILE__, __LINE__, (message))

#define DECLARE_EXCEPTION_BASE(type, base) \
  class type : public base \
  { \
  public: \
    type(const char* file, int line, const char* text); \
    const char* name() const throw(); \
  };

#define DECLARE_EXCEPTION(type) DECLARE_EXCEPTION_BASE(type, ::panorama::Exception)

#define DEFINE_EXCEPTION_BASE(type, base) \
  type::type(const char* file, int line, const char* text): base(file, line, text) { } \
  const char* type::name() const throw() { return #type; }

#define DEFINE_EXCEPTION(type) DEFINE_EXCEPTION_BASE(type, ::panorama::Exception)

} // end namespace panorama
#endif /* !defined(PANORAMA_EXCEPTION_HPP_INCLUDED) */

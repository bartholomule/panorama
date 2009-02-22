#include "exception.hpp"

#include <iostream>

namespace panorama
{
  Exception::Exception(const char* file, int line, const char* text)
    : m_filename(file)
    , m_lineNumber(line)
    , m_exceptionText(text)
  {
  }

  const char* Exception::getFilename() const throw()
  {
    return m_filename;
  }

  int Exception::getLineNumber() const throw()
  {
    return m_lineNumber;
  }

  const char* Exception::getText() const throw()
  {
    return m_exceptionText;
  }

  const char* Exception::what() const throw()
  {
    return m_exceptionText;
  }

  const char* Exception::name() const throw()
  {
    return "Exception";
  }

  std::ostream& operator<<(std::ostream& o, const Exception& e)
  {
    return o << e.getFilename() << ":"
             << e.getLineNumber() << ":"
             << e.name() << ": "
             << e.getText();
  }

} // end namespace panorama

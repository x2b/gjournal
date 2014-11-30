#ifndef READERROR_HH
#define READERROR_HH

#include <sstream>

#include <glibmm/ustring.h>

class ReadError : public std::exception
{
public:
  ReadError()
  {}

  virtual void raise() const = 0;

  virtual ~ReadError()
  {}
};

class IOError : public ReadError
{
public:
  IOError(const Glib::ustring& filename_)
    : filename(filename_)
  {
  }

  void raise() const override
  {
    throw *this;
  }

  const char* what() const throw() override
  {
    return Glib::ustring::compose("Could not open \"%1\"",
				  filename).c_str();
  }

private:
  Glib::ustring filename;
};

class ParseError : public ReadError
{
public:
  ParseError(const Glib::ustring& value_)
    : value(value_)
  {
  }

  void raise() const override
  {
    throw *this;
  }

  const char* what() const throw() override
  {
    return Glib::ustring::compose("Could not parse \"%1\"",
				  value).c_str();
  }

private:
  Glib::ustring value;
};


#endif /* READERROR_HH */

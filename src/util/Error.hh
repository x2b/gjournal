#ifndef ERROR_HH
#define ERROR_HH

#include <string>
#include <stdexcept>
#include <sstream>

#include "cfg.hh"

class Error : public std::logic_error
{
public:
  Error(const std::string &what_arg) : std::logic_error(what_arg) {}

  virtual void raise() const
  {
    throw *this;
  }
};


class FailedAssertion : public Error
{
public:
  FailedAssertion(const std::string &what_arg) : Error(what_arg) {}

  virtual void raise() const
  {
    throw *this;
  }
};

class AssertionFail
{
public:

  AssertionFail(const char *expr,
                const char *func,
                uint line,
                const char *file,
                const char *expl = NULL)
  {
    str << "Error: failed assertion" << std::endl
        << "Expr: " << expr << std::endl
        << "Func: " << func << std::endl
        << "File: " << file << std::endl
        << "Line: " << line << std::endl;

    if(expl)
    {
      str << "Explanation: " << expl << std::endl;
    }
  }

  void raise() const
  {
    FailedAssertion(str.str()).raise();
  }

private:
  std::ostringstream str;
};

#if GJOURNAL_DEBUG == 1

#define gj_assert(x)                                                   \
  do                                                                   \
  {                                                                                    \
    if(!(x))                                                                           \
    {                                                                                  \
      AssertionFail(#x, __PRETTY_FUNCTION__, __LINE__, __FILE__).raise();              \
    }                                                                                  \
  }                                                                                    \
  while(false)

#else

#define gj_assert(x)

#endif

#endif

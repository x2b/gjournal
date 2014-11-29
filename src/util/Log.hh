#ifndef LOG_HH
#define LOG_HH

#include <sstream>
#include <iostream>

using std::endl;

#include "cfg.hh"

enum LogLevel {ERROR, WARNING, INFO, DEBUG};

class Log
{
public:
  Log();
  virtual ~Log();
  std::ostringstream& get(LogLevel level = INFO);

  static LogLevel reporting_level();

protected:
  std::ostringstream os;

private:
  Log(const Log&);
  Log& operator =(const Log&);
  std::string to_string(LogLevel level);
private:
  LogLevel message_level;
};

#define LOG(level)                              \
  if (level > Log::reporting_level()) ;         \
  else Log().get(level)

#if GJOURNAL_DEBUG
#define TRACE					\
  Log().get(DEBUG) << __PRETTY_FUNCTION__
#else
#define TRACE do{} while(false)
#endif

#endif

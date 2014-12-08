#include "Log.hh"

#include <cstdio>

#include "cfg.hh"

Log::Log()
{
  message_level = DEBUG;
}

std::ostringstream& Log::get(LogLevel level)
{
  os << " " << to_string(level) << ": ";

  /*
  os << "- " << NowTime();
  os << std::string(level > logDEBUG ? 0 : level - logDEBUG, '\t');
  */
  message_level = level;
  return os;
}

std::string Log::to_string(LogLevel level)
{
  switch(level)
  {
    case ERROR:
      return "Error";
    case WARNING:
      return "Warning";
    case INFO:
      return "Info";
    case DEBUG:
      return "Debug";
  }



  return "";
}

LogLevel Log::reporting_level()
{
#if GJOURNAL_DEBUG
  return DEBUG;
#else
  return WARNING;
#endif
}

Log::~Log()
{
  os << std::endl;
  fprintf(stderr, "%s", os.str().c_str());
  fflush(stderr);
}

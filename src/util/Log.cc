#include "Log.hh"

#include "../cfg.hh"

Log::Log()
{
  message_level = DEBUG;
}

std::ostringstream& Log::get(LogLevel level)
{
  /*
  os << "- " << NowTime();
  os << " " << ToString(level) << ": ";
  os << std::string(level > logDEBUG ? 0 : level - logDEBUG, '\t');
  */
  message_level = level;
  return os;
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

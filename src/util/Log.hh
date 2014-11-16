#ifndef LOG_HH
#define LOG_HH

#include <sstream>
#include <iostream>

using std::endl;

enum LogLevel {ERROR, WARNING, INFO, DEBUG};

class Log
{
public:
   Log();
   virtual ~Log();
   std::ostringstream& get(LogLevel level = INFO);
public:
   static LogLevel reporting_level();
protected:
   std::ostringstream os;
private:
   Log(const Log&);
   Log& operator =(const Log&);
private:
   LogLevel message_level;
};

#define LOG(level) \
if (level > Log::reporting_level()) ; \
else Log().get(level)

#endif

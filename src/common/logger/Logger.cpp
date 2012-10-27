#include "Logger.hpp"
#include <mutex>

static unsigned globalCount = 0;

static unsigned nextColor()
{
  return 31 + globalCount++ % 7;
}

Logger::Logger(const std::string& title,
               const std::string& filename, bool verbose)
: file(filename.c_str(), std::ios::app), title(title),
color(nextColor()), verbose(verbose), enabled(true)
{
}

Logger::Logger(const std::string& title)
: title(title), color(nextColor()), verbose(true), enabled(true)
{
}

Logger::~Logger()
{
  if (file.is_open())
  {
    file.close();
  }
}

void Logger::set(bool active)
{
  enabled = active;
}

void Logger::writeHead(std::ostream& stream, bool colored, bool dated)
{
  if (dated)
  {
    time_t logTime = std::time(nullptr);
    std::string reprTime(std::asctime(std::localtime(&logTime)));
    stream << reprTime;
  }
  if (colored)
  {
    stream << "\x1b[4m\x1b[" << color << "m" << title << ":" << "\x1b[0m ";
  }
  else
  {
    stream << title << ": ";
  }
}

#ifndef LOG_MESSAGE_HPP
#define LOG_MESSAGE_HPP

#include "level.hpp"
#include <string>

namespace domeeno
{

struct LogMessage
{
  Level       lvl;
  std::string message;
};

} // namespace domeeno

#endif // !LOG_MESSAGE_HPP

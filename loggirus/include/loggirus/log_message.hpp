#ifndef LOG_MESSAGE_HPP
#define LOG_MESSAGE_HPP

#include <loggirus/level.hpp>
#include <string>

namespace domeeno
{

struct LogMessage
{
  const Level       lvl;
  const std::string message;
};

} // namespace domeeno

#endif // !LOG_MESSAGE_HPP

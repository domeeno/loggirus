#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string_view>
#include <utility>

namespace domeeno
{
enum class Level
{
  DEBUG,
  INFO,
  WARN,
  ERROR,
};

constexpr std::string_view to_string(Level level)
{
  switch (level)
  {
  case Level::DEBUG:
    return "DEBUG";
  case Level::INFO:
    return "INFO";
  case Level::WARN:
    return "WARN";
  case Level::ERROR:
    return "ERROR";
  }
  std::unreachable();
}

constexpr std::string_view to_emoji(Level level)
{
  switch (level)
  {
  case Level::DEBUG:
    return "🛠️";
  case Level::INFO:
    return "ℹ️";
  case Level::WARN:
    return "💢";
  case Level::ERROR:
    return "⚠️";
  }
  std::unreachable();
}

} // namespace domeeno

#endif // LEVEL_HPP

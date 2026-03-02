#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include "level.hpp"
#include "rand_well.hpp"
#include <chrono>
#include <format>
#include <string>

namespace domeeno
{

#if defined(_WIN64)
constexpr std::string_view OS_NAME = "64 ";
#elif defined(_WIN32)
constexpr std::string_view OS_NAME = "32 ";
#elif defined(__APPLE__) && defined(__MACH__)
constexpr std::string_view OS_NAME = "A  ";
#elif defined(__linux__)
constexpr std::string_view OS_NAME = "   ";
#elif defined(__FreeBSD__)
constexpr std::string_view OS_NAME = "   ";
#else
constexpr std::string_view OS_NAME = "    ";
#endif

class Formatter
{
public:
  template <class... Args>
  std::string format(Level level, std::format_string<Args...> fmt, Args &&...args)
  {

    std::string message = std::format(fmt, std::forward<Args>(args)...);

    std::string append = m_well.get_append(level);

    return std::format(                       //
      "{}: {} [{:%Y/%m/%d %H:%M}] [{}] {} {}", // format
      OS_NAME,                                // OS
      to_emoji(level),                        // emoji
      std::chrono::system_clock::now(),       // time
      to_string(level),                       // level
      message,                                // message
      append                                  // append
    );
  }

private:
  RandWell m_well{};
};
} // namespace domeeno
#endif // FORMATTER_HPP

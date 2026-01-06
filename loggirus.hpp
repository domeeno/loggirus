#ifndef LOGGIRUS_H
#define LOGGIRUS_H

#include "concurrent_queue.hpp"
#include <format>
#include <iostream>
#include <vector>

namespace domeeno
{

enum level
{
  DEBUG,
  INFO,
  WARN,
  ERROR,
};

class Log
{
public:
  Log() : m_log_level(level::DEBUG) {};
  Log(level l) : m_log_level(l) {};

  // to be
  template <class... Args>
  void debug(std::format_string<Args...> fmt, Args &&...args)
  {
    log<level::DEBUG>(fmt, std::forward<Args>(args)...);
  }

  template <class... Args>
  void info(std::format_string<Args...> fmt, Args &&...args)
  {
    log<level::INFO>(fmt, std::forward<Args>(args)...);
  }

  template <class... Args>
  void warn(std::format_string<Args...> fmt, Args &&...args)
  {
    log<level::WARN>(fmt, std::forward<Args>(args)...);
  }

  template <class... Args>
  void error(std::format_string<Args...> fmt, Args &&...args)
  {
    log<level::ERROR>(fmt, std::forward<Args>(args)...);
  }

  void test() {
    std::cout << m_log_queue.pop() << std::endl;
  }

private:
  template <level L, class... Args>
  void log(std::format_string<Args...> fmt, Args &&...args)
  {
    if (m_log_level > L)
      return;

    std::string message = std::format(fmt, std::forward<Args>(args)...);
    m_log_queue.push(message);
  };

  level                        m_log_level;
  ConcurrentQueue<std::string> m_log_queue {};

  // prepending
  std::vector<std::string> m_info_prepend{
    "ℹ️: [INF]",
    "🤔: [INF]",
  };
  std::vector<std::string> m_debug_prepend{
    "🔧: [DEB]",
    "🤖: [DEB]",
    "🛠️: [DEB]",
    "🤓: [DEB]",
  };
  std::vector<std::string> m_error_prepend{
    "💢: [ERR]",
    "🧑‍🚒: [ERR]",
    "🤦: [ERR]",
  };
  std::vector<std::string> m_warn_prepend{
    "⚠️: [WRN]",
  };

  // appending
  std::vector<std::string> m_info_append{
    " - so far so good.",
    " - I hope this helps.",
    " - as it should.",
  };
  std::vector<std::string> m_debug_append{
    " - mathematical, don't you agree?.",
    " - algebraic, CS degree.",
    " - bleep-blop.",
  };
  std::vector<std::string> m_error_append{
    " - buns. As in butts.",
    " - oh nooo.",
    " - maybe ask AI? There is no shame in that.",
    " - be level headed.",
    " - the answer is within you... or online.",
  };
  std::vector<std::string> m_warn_append{
    " - who uses warn level anyway? Nerd.",
    " - something's off I can feel it.",
    " - should we worry about this?",
    " - hmm a warning? probably nothing.",
  };
};

} // namespace domeeno

#endif

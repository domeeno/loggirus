#ifndef LOGGIRUS_H
#define LOGGIRUS_H

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

class log
{
public:
  log() : m_log_level(level::DEBUG) {};
  log(level l) : m_log_level(l) {};

  template <class... Args> void info(std::format_string<Args...> fmt, Args &&...args)
  {
    if (m_log_level > level::INFO)
      return;

    std::string message = std::format(fmt, std::forward<Args>(args)...);
  }

private:
  level m_log_level;

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

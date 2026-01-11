#ifndef LOGGIRUS_H
#define LOGGIRUS_H

#include "level.hpp"
#include "worker_thread.hpp"
#include <format>
#include <map>
#include <vector>

namespace domeeno
{

class Log
{
public:
  Log() : m_log_level(Level::DEBUG)
  {
    m_worker_thread.start();
  };

  Log(Level l) : m_log_level(l)
  {
    m_worker_thread.start();
  };

  ~Log()
  {
  }

  template <class... Args>
  void debug(std::format_string<Args...> fmt, Args &&...args)
  {
    log<Level::DEBUG>(std::move(fmt), std::forward<Args>(args)...);
  }

  template <class... Args>
  void info(std::format_string<Args...> fmt, Args &&...args)
  {
    log<Level::INFO>(std::move(fmt), std::forward<Args>(args)...);
  }

  template <class... Args>
  void warn(std::format_string<Args...> fmt, Args &&...args)
  {
    log<Level::WARN>(std::move(fmt), std::forward<Args>(args)...);
  }

  template <class... Args>
  void error(std::format_string<Args...> fmt, Args &&...args)
  {
    log<Level::ERROR>(std::move(fmt), std::forward<Args>(args)...);
  }

private:
  template <Level L, class... Args>
  void log(std::format_string<Args...> fmt, Args &&...args)
  {
    if (m_log_level > L)
      return;

    std::string log_text = std::format(fmt, std::forward<Args>(args)...);

    m_worker_thread.publish({L, log_text});
  };

  Level        m_log_level;
  WorkerThread m_worker_thread{};

  // prepending
  const std::map<Level, std::vector<std::string>> m_log_prepends = {
    {Level::INFO,
     {
       "ℹ️",
       "🤔",
     }},
    {Level::DEBUG,
     {
       "🔧",
       "🤖",
       "🛠️",
       "🤓",
     }},
    {Level::ERROR,
     {
       "💢",
       "🧑‍🚒",
       "🤦",
     }},
    {Level::WARN,
     {
       "⚠️",
     }},
  };

  // appending
  const std::map<Level, std::vector<std::string>> m_log_appends{
    {Level::INFO,
     {
       " - so far so good.",
       " - I hope this helps.",
       " - as it should.",
     }},
    {Level::DEBUG,
     {
       " - mathematical, don't you agree?.",
       " - algebraic, CS degree.",
       " - bleep-blop.",
     }},
    {Level::ERROR,
     {
       " - buns. As in butts.",
       " - oh nooo.",
       " - maybe ask AI? There is no shame in that.",
       " - would you like to play some Baldur's Gate?",
       " - be level headed.",
       " - the answer is within you... or online.",
     }},
    {Level::WARN,
     {
       " - who uses warn level anyway? Nerd.",
       " - something's off I can feel it.",
       " - should we worry about this?",
       " - hmm a warning? probably nothing.",
     }},
  };
};

} // namespace domeeno

#endif

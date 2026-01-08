#ifndef LOGGIRUS_H
#define LOGGIRUS_H

#include "concurrent_queue.hpp"
#include <format>
#include <iostream>
#include <map>
#include <thread>
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

struct logMessage
{
  level       l;
  std::string message;
};

class Log
{ public:
  Log() : m_log_level(level::DEBUG)
  {
    std::cout << "attempting to start thread." << std::endl;
    m_process_thread = std::thread(&Log::process, this);
  };

  Log(level l) : m_log_level(l)
  {
    std::cout << "attempting to start thread." << std::endl;
    m_process_thread = std::thread(&Log::process, this);
  };

  ~Log()
  {
    m_running = false;
    m_process_thread.join();
  }

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

private:
  template <level L, class... Args>
  void log(std::format_string<Args...> fmt, Args &&...args)
  {
    if (m_log_level > L)
      return;

    std::string message = std::format(fmt, std::forward<Args>(args)...);
    std::cout << "pushing message: " << message << std::endl;
    m_log_queue.push({L, message});
  };

  void process()
  {
    std::cout << "started processing thread." << std::endl;
    while (m_running)
    {
      if (!m_log_queue.empty())
      {
        logMessage log_msg = m_log_queue.pop();

        std::string prepend =
          m_log_prepends[log_msg.l][static_cast<unsigned long>(rand()) % m_log_prepends[log_msg.l].size()];
        std::string append =
          m_log_appends[log_msg.l][static_cast<unsigned long>(rand()) % m_log_appends[log_msg.l].size()];

        std::cout << prepend << log_msg.message << append << std::endl;
      }
    }
  }

  level                       m_log_level;
  ConcurrentQueue<logMessage> m_log_queue{};
  std::thread                 m_process_thread{};
  bool                        m_running{true};

  // prepending
  std::map<level, std::vector<std::string>> m_log_prepends = {
    {level::INFO,
     {
       "ℹ️: [INF] :",
       "🤔: [INF] :",
     }},
    {level::DEBUG,
     {
       "🔧: [DEB] :",
       "🤖: [DEB] :",
       "🛠️: [DEB] :",
       "🤓: [DEB] :",
     }},
    {level::ERROR,
     {
       "💢: [ERR] :",
       "🧑‍🚒: [ERR] :",
       "🤦: [ERR] :",
     }},
    {level::WARN,
     {
       "⚠️: [WRN] :",
     }},
  };

  // appending
  std::map<level, std::vector<std::string>> m_log_appends{
    {level::INFO,
     {
       " - so far so good.",
       " - I hope this helps.",
       " - as it should.",
     }},
    {level::DEBUG,
     {
       " - mathematical, don't you agree?.",
       " - algebraic, CS degree.",
       " - bleep-blop.",
     }},
    {level::ERROR,
     {
       " - buns. As in butts.",
       " - oh nooo.",
       " - maybe ask AI? There is no shame in that.",
       " - would you like to play some Baldur's Gate?",
       " - be level headed.",
       " - the answer is within you... or online.",
     }},
    {level::WARN,
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

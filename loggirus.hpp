#ifndef LOGGIRUS_H
#define LOGGIRUS_H

#include "concurrent_queue.hpp"
#include <format>
#include <iostream>
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
{
public:
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

        std::string prepend{};
        std::string append{};

        if (log_msg.l == level::DEBUG)
        {
          prepend = m_debug_prepend[rand() % m_debug_prepend.size()];
          append  = m_debug_append[rand() % m_debug_append.size()];
        }
        else if (log_msg.l == level::INFO)
        {
          prepend = m_info_prepend[rand() % m_info_prepend.size()];
          append  = m_info_append[rand() % m_info_append.size()];
        }
        else if (log_msg.l == level::WARN)
        {
          prepend = m_warn_prepend[rand() % m_warn_prepend.size()];
          append  = m_warn_append[rand() % m_warn_append.size()];
        }
        else if (log_msg.l == level::ERROR)
        {
          prepend = m_error_prepend[rand() % m_error_prepend.size()];
          append  = m_error_append[rand() % m_error_append.size()];
        }

        std::cout << prepend << log_msg.message << append << std::endl;
      }
    }
  }

  level                       m_log_level;
  ConcurrentQueue<logMessage> m_log_queue{};
  std::thread                 m_process_thread;
  bool                        m_running{true};

  // prepending
  std::vector<std::string> m_info_prepend{
    "ℹ️: [INF] ",
    "🤔: [INF] ",
  };
  std::vector<std::string> m_debug_prepend{
    "🔧: [DEB] ",
    "🤖: [DEB] ",
    "🛠️: [DEB] ",
    "🤓: [DEB] ",
  };
  std::vector<std::string> m_error_prepend{
    "💢: [ERR] ",
    "🧑‍🚒: [ERR] ",
    "🤦: [ERR] ",
  };
  std::vector<std::string> m_warn_prepend{
    "⚠️: [WRN] ",
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

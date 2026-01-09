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

enum class Level
{
  DEBUG,
  INFO,
  WARN,
  ERROR,
};

struct LogMessage
{
  Level       lvl;
  std::string message;
};

class Log
{
public:
  Log() : m_log_level(Level::DEBUG)
  {
    m_process_thread = std::thread(&Log::process, this);
  };

  Log(Level l) : m_log_level(l)
  {
    m_process_thread = std::thread(&Log::process, this);
  };

  ~Log()
  {
    m_running = false;
    m_process_thread.join();

    while (!m_log_queue.empty())
    {
      stdout(m_log_queue.pop());
    }
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

    std::string message = std::format(fmt, std::forward<Args>(args)...);
    m_log_queue.push({L, std::move(message)});
    m_cond.notify_one();
  };

  void process()
  {
    while (m_running)
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_cond.wait(lock, [this]() { return !m_log_queue.empty(); });
      stdout(m_log_queue.pop());
    }
  }

  void stdout(LogMessage log_msg)
  {
    std::string prepend =
      m_log_prepends[log_msg.lvl][static_cast<unsigned long>(rand()) % m_log_prepends[log_msg.lvl].size()];
    std::string append =
      m_log_appends[log_msg.lvl][static_cast<unsigned long>(rand()) % m_log_appends[log_msg.lvl].size()];

    std::cout << prepend << log_msg.message << append << std::endl;
  }

  Level                       m_log_level;
  ConcurrentQueue<LogMessage> m_log_queue{};
  std::mutex                  m_mutex{};
  std::thread                 m_process_thread{};
  std::condition_variable     m_cond{};
  bool                        m_running{true};

  // prepending
  std::map<Level, std::vector<std::string>> m_log_prepends = {
    {Level::INFO,
     {
       "ℹ️: [INF] :",
       "🤔: [INF] :",
     }},
    {Level::DEBUG,
     {
       "🔧: [DEB] :",
       "🤖: [DEB] :",
       "🛠️: [DEB] :",
       "🤓: [DEB] :",
     }},
    {Level::ERROR,
     {
       "💢: [ERR] :",
       "🧑‍🚒: [ERR] :",
       "🤦: [ERR] :",
     }},
    {Level::WARN,
     {
       "⚠️: [WRN] :",
     }},
  };

  // appending
  std::map<Level, std::vector<std::string>> m_log_appends{
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

#ifndef LOGGIRUS_HPP
#define LOGGIRUS_HPP

#include "formatter.hpp"
#include "level.hpp"
#include "worker_thread.hpp"
#include <format>

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

    std::string log = m_formatter.format(L, std::move(fmt), std::forward<Args>(args)...);

    m_worker_thread.publish(log);
  };

  Level        m_log_level;
  WorkerThread m_worker_thread{};
  Formatter    m_formatter{};
};

} // namespace domeeno

#endif // LOGGIRUS_HPP

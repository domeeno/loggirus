#ifndef LOGGIRUS_HPP
#define LOGGIRUS_HPP

#include <loggirus/formatter.hpp>
#include <loggirus/level.hpp>
#include <loggirus/worker_thread.hpp>

namespace domeeno
{

class Logger
{
public:
  Logger() : m_log_level(Level::DEBUG)
  {
    m_worker_thread.start();
  };

  Logger(Level l) : m_log_level(l)
  {
    m_worker_thread.start();
  };

  ~Logger()
  {
  }

  template <class... Args>
  void debug(std::format_string<Args...> fmt, Args &&...args)
  {
    log(Level::DEBUG, std::move(fmt), std::forward<Args>(args)...);
  }

  template <class... Args>
  void info(std::format_string<Args...> fmt, Args &&...args)
  {
    log(Level::INFO, std::move(fmt), std::forward<Args>(args)...);
  }

  template <class... Args>
  void warn(std::format_string<Args...> fmt, Args &&...args)
  {
    log(Level::WARN, std::move(fmt), std::forward<Args>(args)...);
  }

  template <class... Args>
  void error(std::format_string<Args...> fmt, Args &&...args)
  {
    log(Level::ERROR, std::move(fmt), std::forward<Args>(args)...);
  }

private:
  template <class... Args>
  void log(Level l, std::format_string<Args...> fmt, Args &&...args)
  {
    if (m_log_level > l)
      return;

    const std::string log = m_formatter.format(l, std::move(fmt), std::forward<Args>(args)...);

    m_worker_thread.publish(log);
  };

  Level        m_log_level;
  WorkerThread m_worker_thread{};
  Formatter    m_formatter{};
};

} // namespace domeeno

#endif // LOGGIRUS_HPP

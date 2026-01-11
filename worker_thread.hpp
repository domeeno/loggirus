#ifndef WORKER_THREAD
#define WORKER_THREAD

#include "concurrent_queue.hpp"
#include <condition_variable>
#include <iostream>
#include <thread>

namespace domeeno
{
class WorkerThread
{
public:
  WorkerThread() {};

  void start()
  {
    m_process_thread = std::thread(&WorkerThread::process, this);
  }

  void publish(std::string &log)
  {
    m_log_queue.push(log);
    m_cond.notify_one();
  }

  ~WorkerThread()
  {
    m_running = false;
    m_process_thread.join();

    while (!m_log_queue.empty())
    {
      std::cout << m_log_queue.pop() << std::endl;
    }
  }

private:
  ConcurrentQueue<std::string> m_log_queue{};
  std::thread                  m_process_thread{};
  std::mutex                   m_mutex{};
  bool                         m_running{true};
  std::condition_variable      m_cond{};

  void process()
  {
    while (m_running)
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_cond.wait(lock, [this]() { return !m_log_queue.empty(); });

      std::cout << m_log_queue.pop() << std::endl;
    }
  };
};
} // namespace domeeno

#endif // !WORKER_THREAD

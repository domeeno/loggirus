#ifndef CONCURRENT_QUEUE_HPP
#define CONCURRENT_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class ConcurrentQueue
{
public:
  void push(T item)
  {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_queue.push(std::move(item));
    m_cond.notify_one();
  }

  T pop()
  {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cond.wait(lock, [this]() { return !m_queue.empty(); });

    T item = std::move(m_queue.front());
    m_queue.pop();

    return item;
  }

  bool empty()
  {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.empty();
  }

private:
  std::queue<T>           m_queue{};
  std::mutex              m_mutex{};
  std::condition_variable m_cond{};
};

#endif // CONCURRENT_QUEUE_HPP

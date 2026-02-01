#ifndef RAND_WELL_HPP
#define RAND_WELL_HPP

#include "level.hpp"
#include <array>
#include <random>
#include <string>
#include <vector>

namespace domeeno
{
class RandWell
{
public:
  RandWell() : m_gen(std::random_device{}())
  {
  }

  std::string get_append(Level level)
  {
    const auto &pool = m_log_appends[to_index(level)];
    if (pool.empty())
    {
      return {};
    }

    std::uniform_int_distribution<std::size_t> dist(0, pool.size() - 1);
    return pool[dist(m_gen)];
  }

private:
  static constexpr std::size_t to_index(Level level) noexcept
  {
    return static_cast<std::size_t>(level);
  }

private:
  std::mt19937 m_gen;

  std::array<std::vector<std::string>, 4> m_log_appends{{
    /* DEBUG */
    {
      " - mathematical, don't you agree?",
      " - algebraic, CS degree.",
      " - bleep-blop.",
    },
    /* INFO */
    {
      " - so far so good.",
      " - I hope this helps.",
      " - as it should.",
      " - maybe it is time to sleep.",
    },
    /* WARN */
    {
      " - who uses warn level anyway? Nerd.",
      " - something's off I can feel it.",
      " - should we worry about this?",
      " - hmm a warning? probably nothing.",
    },
    /* ERROR */
    {
      " - buns. As in butts.",
      " - oh nooo.",
      " - maybe ask AI? There is no shame in that.",
      " - would you like to play some Baldur's Gate?",
      " - be level headed.",
      " - the answer is within you... or online.",
    },
  }};
};
} // namespace domeeno
#endif // !WELL

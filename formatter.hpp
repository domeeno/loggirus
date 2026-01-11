#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include "level.hpp"
#include <chrono>
#include <format>
#include <map>
#include <string>
#include <vector>

namespace domeeno
{

class Formatter
{

public:
  template <class... Args>
  std::string format(Level level, std::format_string<Args...> fmt, Args &&...args)
  {

    std::string message = std::format(fmt, std::forward<Args>(args)...);
    auto const &vec     = m_log_appends.at(level);
    std::string append  = vec[static_cast<std::size_t>(rand()) % vec.size()];

    return std::format(                    //
      "{} [{:%Y/%m/%d %H:%M}] [{}] {} {}", // format
      to_emoji(level),                     // emoji
      std::chrono::system_clock::now(),    // time
      to_string(level),                    // level
      message,                             // message
      append                               // append
    );
  }

private:
  // appending
  const std::map<Level, std::vector<std::string>> m_log_appends{
    {Level::INFO,
     {
       " - so far so good.",
       " - I hope this helps.",
       " - as it should.",
       " - maybe it is time to sleep.",
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

#endif // FORMATTER_HPP

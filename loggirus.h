#ifndef LOGGIRUS_H
#define LOGGIRUS_H

#include <format>
#include <iostream>
#include <string>

namespace domeeno
{
class log
{
public:
  template <class... Args> void info(std::format_string<Args...> fmt, Args &&...args)
  {
    std::cout << std::format(fmt, std::forward<Args>(args)...) << '\n';
  }
};
} // namespace domeeno

#endif

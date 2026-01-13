#include "loggirus.hpp"
#include <iostream>

std::string getOsName()
{
#ifdef _WIN32
  return "Windows 32-bit";
#elif _WIN64
  return "Windows 64-bit";
#elif __APPLE__ || __MACH__
  return "Mac OSX";
#elif __linux__
  return "Linux";
#elif __FreeBSD__
  return "FreeBSD";
#elif __unix || __unix__
  return "Unix";
#else
  return "Other";
#endif
}

int main()
{

  std::cout << "Example output:\n";
  {

    domeeno::Log logger(domeeno::Level::DEBUG);

    logger.info("output of logging, [{}] [{}]!", "Hello", "World");
    logger.debug("operating system: {}", getOsName());
    logger.error("{} feature is not working ", "random phrases");
    logger.warn("test number {}", 42);
  }

  return 0;
}

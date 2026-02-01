#include "loggirus.hpp"

int main()
{

  {

    domeeno::Log logger(domeeno::Level::DEBUG);

    logger.info("output of logging, [{}] [{}]!", "Hello", "World");
    logger.debug("operating system: {}", "name");
    logger.error("{} feature is not working ", "random phrases");
    logger.warn("test number {}", 42);
  }

  return 0;
}

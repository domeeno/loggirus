#include <loggirus/loggirus.hpp>

int main()
{

  {
    domeeno::Logger logger(domeeno::Level::DEBUG);

    logger.info("output of logging, [{}] [{}]!", "Hello", "World");
    logger.debug("operating system: {}", "name");
    logger.error("{} feature is not working ", "random phrases");
    logger.warn("test number {}", 42);
  }

  return 0;
}

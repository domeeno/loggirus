#include "loggirus.hpp"

int main()
{
  domeeno::Log logger(domeeno::level::DEBUG);

  logger.info("Hello, {} {}!", "World", 3);
  // should not be enqueued, because log level is info
  logger.debug("Debug, {} {}!", "World", 3);
  logger.error("Error, {} {}!", "World", 3);

  return 0;
}

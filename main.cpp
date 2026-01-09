#include "loggirus.hpp"

int main()
{
  domeeno::Log logger(domeeno::Level::DEBUG);

  logger.info("Hello, {} {}!", "World", 3);
  logger.debug("Debug, {} {}!", "World", 3);
  logger.error("Error, {} {}!", "World", 3);
  logger.warn("Warning, {} {}!", "World", 3);

  return 0;
}

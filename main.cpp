#include "loggirus.hpp"

int main()
{
  domeeno::Log logger(domeeno::Level::DEBUG);

  logger.info("Hello, {} {}!", "World", 3);

  return 0;
}

#include "loggirus.hpp"

int main()
{
  domeeno::log logger(domeeno::level::INFO);

  logger.info("Hello, {} {}!", "World", 3);

  return 0;
}

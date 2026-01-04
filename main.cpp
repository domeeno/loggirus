#include "loggirus.h"

int main()
{
  domeeno::log logger;

  logger.info("Hello, {} {}!", "World", 3);

  return 0;
}

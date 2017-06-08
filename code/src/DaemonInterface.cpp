#include "../include/DaemonInterface.hpp"

void DaemonInterface::connect( boost::function<void (int)> slot ) {
   signal_.connect(slot);
}

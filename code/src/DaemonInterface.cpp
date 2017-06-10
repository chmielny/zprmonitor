#include "../include/DaemonInterface.hpp"

void DaemonInterface::connect( DaemonObserver* slot ) {
   signal_.connect(boost::ref(*slot));
}

void DaemonInterface::disconnect( DaemonObserver* slot ) {
   signal_.disconnect(boost::ref(*slot));
}

int DaemonInterface::getActValue() {
    return actValue_;
}

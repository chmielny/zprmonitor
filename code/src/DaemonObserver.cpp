#include "../include/DaemonObserver.hpp"

DaemonObserver::DaemonObserver( std::function<void(void)> funcPtr ): userFunctionPtr_(funcPtr) {
}

DaemonObserver::~DaemonObserver() {
}

bool DaemonObserver::operator ==( const DaemonObserver &obs) const {
    return this == &obs; 
}

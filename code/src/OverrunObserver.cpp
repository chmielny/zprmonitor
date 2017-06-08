#include "../include/OverrunObserver.hpp"

OverrunObserver::OverrunObserver(std::function<void (void)> usrFunc ,int usrLimit ) : DaemonObserver( usrFunc ), maxLimit_(usrLimit) {
}

void OverrunObserver::update(int value) {
    if( value > maxLimit_)
        userFunctionPtr_();
}

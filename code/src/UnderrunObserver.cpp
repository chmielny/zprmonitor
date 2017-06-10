#include "../include/UnderrunObserver.hpp"

UnderrunObserver::UnderrunObserver(std::function<void (void)> usrFunc ,int usrLimit ) : DaemonObserver( usrFunc ), minLimit_(usrLimit) {
}

void UnderrunObserver::update(int value) {
    if( value < minLimit_)
        userFunctionPtr_();
}

void UnderrunObserver::operator()(int value) {
    update(value);
}

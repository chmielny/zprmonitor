#include "../include/InRangeObserver.hpp"

InRangeObserver::InRangeObserver(std::function<void (void)> usrFunc ,int usrMinLimit, int usrMaxLimit ) 
    : DaemonObserver( usrFunc ), minLimit_(usrMinLimit) ,maxLimit_(usrMaxLimit) {
}

void InRangeObserver::update(int value) {
    if( (value > maxLimit_) || (value < minLimit_) )
        userFunctionPtr_();
}

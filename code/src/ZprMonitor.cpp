#include"../include/ZprMonitor.hpp"

extern "C" ZprMonitor* create_object() {
    return new ZprMonitor;
}

extern "C" void destroy_object( ZprMonitor* object ) {
    delete object;
}

ZprMonitor::ZprMonitor()
{
    // konstruktor bezparametrowy
}


ZprMonitor::errorCode_ ZprMonitor::registerCallback(daemonType_ daemon, observerType_ obs, std::function< void(void) > callbackFunc, int maxValue, int minValue, int periodTime, std::string diskPath ) {
    return OK;
}    

#include"../include/ZprMonitor.hpp"
#include"../include/RamDaemon.hpp"

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

ZprMonitor::~ZprMonitor()
{
    // destruktor 
}

ZprMonitor::errorCode_ ZprMonitor::registerCallback(daemonType_ daemon, observerType_ obs, std::function< void(void) > callbackFunc, int maxValue, int minValue, int periodTime, std::string diskPath ) {
    return OK;
}    


int ZprMonitor::getActValue() {
    int value;
    RamDaemon tmp;
    value = tmp.getActValue();
    return value;
}    

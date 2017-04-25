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



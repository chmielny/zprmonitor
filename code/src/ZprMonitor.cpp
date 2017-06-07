#include"../include/ZprMonitor.hpp"
#include"../include/RamDaemon.hpp"

#ifdef _ZPRBUILD
    # define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
    # define DLLIMPORT __declspec (dllimport)
#endif


extern "C" 
{
    #ifdef _WINDOWS 
    DLLIMPORT 
    #endif 
    ZprMonitor* create_object() {
        return new ZprMonitor;
    }

    #ifdef _WINDOWS 
    DLLIMPORT 
    #endif 
    void destroy_object( ZprMonitor* object ) {
        delete object;
    }
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

#include"../include/ZprMonitor.hpp"

#ifdef _ZPRBUILD
    #include"../include/RamDaemon.hpp"
    #include"../include/CpuDaemon.hpp"
    #include"../include/DiskPathDaemon.hpp"
    # define DLLIMPORT __declspec (dllexport)
#else /* Not BUILD */
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
    callbackFunc();
    return OK;
}    


int ZprMonitor::getActValue( daemonType_ daemon ) {
    int value;
    DaemonInterface* tmp;
    tmp = getDaemon_(daemon);
    value = tmp->getActValue();
    return value;
}

DaemonInterface* ZprMonitor::getDaemon_(daemonType_ daemon) {
    DaemonInterface* tmpDaemon;
    if(daemon == RAM)
        tmpDaemon = new RamDaemon();
    else if (daemon == CPU)
        tmpDaemon = new CpuDaemon();
    else if (daemon == DISKPATH)
        tmpDaemon = new DiskPathDaemon();
    return tmpDaemon;
}

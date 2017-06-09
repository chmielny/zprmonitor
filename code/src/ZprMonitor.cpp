#include"../include/ZprMonitor.hpp"

#ifdef _ZPRBUILD
    #include"../include/RamDaemon.hpp"
    #include"../include/CpuDaemon.hpp"
    #include"../include/DiskPathDaemon.hpp"
    #include"../include/OverrunObserver.hpp"
    #include"../include/UnderrunObserver.hpp"
    #include"../include/InRangeObserver.hpp"
    #include"../include/AverageOverrunObserver.hpp"
    #include"../include/AverageUnderrunObserver.hpp"
    #include<boost/bind.hpp>
    #include<iostream>
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

    daemonInterfaceCollection_.push_back(getDaemon_(RAM));
    daemonInterfaceCollection_.push_back(getDaemon_(CPU));
    daemonInterfaceCollection_.push_back(getDaemon_(DISKPATH));

    threadFunctor_ = new MeasureTimerThread(std::ref(daemonInterfaceCollection_));
    timerThread_ = new std::thread( std::ref(*threadFunctor_) );
}

ZprMonitor::~ZprMonitor()
{
    // destruktor 
    timerThread_->join();
}

ZprMonitor::errorCode_ ZprMonitor::registerCallback(daemonType_ daemon, observerType_ observer, 
        std::function< void(void) > callbackFunc, int minValue, int maxValue, int periodTime, std::string diskPath ) {
    DaemonObserver* tmpObserver;
    DaemonInterface* tmpDaemon;

    if(daemon == RAM)
       tmpDaemon = daemonInterfaceCollection_[0];         
    else if (daemon == CPU)
       tmpDaemon = daemonInterfaceCollection_[1];         
    else if (daemon == DISKPATH)
       tmpDaemon = daemonInterfaceCollection_[2];         

    if(observer == OVERRUN)
        tmpObserver = new OverrunObserver( callbackFunc, maxValue );
    else if(observer == UNDERRUN)
        tmpObserver = new UnderrunObserver( callbackFunc, minValue );
    else if(observer == INRANGE)
        tmpObserver = new InRangeObserver( callbackFunc, minValue, maxValue );
    else if(observer == AVERAGEOVERRUN)
        tmpObserver = new AverageOverrunObserver( callbackFunc, maxValue, periodTime );
    else if(observer == AVERAGEUNDERRUN)
        tmpObserver = new AverageUnderrunObserver( callbackFunc, minValue, periodTime );
    
    tmpDaemon->connect(boost::bind(&DaemonObserver::update, tmpObserver, _1 ));
    
    return OK;
}    

int ZprMonitor::getActValue( daemonType_ daemon ) {
    int value;
    if(daemon == RAM)
       value = daemonInterfaceCollection_[0]->getActValue();         
    else if (daemon == CPU)
       value = daemonInterfaceCollection_[1]->getActValue();         
    else if (daemon == DISKPATH)
       value = daemonInterfaceCollection_[2]->getActValue();         
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


int main() {
}

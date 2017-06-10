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
    #include<utility>
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
    daemonInterfaceCollection_.push_back(getDaemon_(RAM));
    daemonInterfaceCollection_.push_back(getDaemon_(CPU));

    observerId_ = 1000;

    threadFunctor_ = new MeasureTimerThread(daemonInterfaceCollection_);
    timerThread_ = new std::thread( std::ref(*threadFunctor_) );
}

ZprMonitor::~ZprMonitor()
{   
    std::vector< DaemonInterface* > tmpDmnIntColl(daemonInterfaceCollection_);
    daemonInterfaceCollection_.clear();

    timerThread_->join();

    std::for_each(tmpDmnIntColl.begin(), tmpDmnIntColl.end(), [](DaemonInterface* tmp){ delete tmp;});
    delete timerThread_;
    delete threadFunctor_;

    std::for_each(observerCollection_.begin(), observerCollection_.end(), [](std::pair<unsigned long, DaemonObserver*> tmp){ delete tmp.second; });
}

unsigned long ZprMonitor::registerCallback(daemonType_ daemon, observerType_ observer, 
        std::function< void(void) > callbackFunc, int minValue, int maxValue, int periodTime, std::string diskPath ) {
    DaemonObserver* tmpObserver;
    DaemonInterface* tmpDaemon;

    if(daemon == RAM)
       tmpDaemon = daemonInterfaceCollection_[0];         
    else if (daemon == CPU)
       tmpDaemon = daemonInterfaceCollection_[1];         
    else if (daemon == DISKPATH) {
        tmpDaemon = getDaemon_(DISKPATH, diskPath);         
        daemonInterfaceCollection_.push_back(tmpDaemon);
    }

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
    
    ++observerId_; 
    observerCollection_.insert(std::make_pair( observerId_ , tmpObserver));
 
    tmpDaemon->connect(observerCollection_[observerId_]);
    
    return observerId_;
}    

ZprMonitor::errorCode_ ZprMonitor::unregisterCallback(unsigned long observer) {
    errorCode_ retTmp;
    DaemonObserver* tmpObs;
    try {
        tmpObs = observerCollection_.at(observer);
        retTmp = OK;
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Nie ma takiego obserwatora " << oor.what() << std::endl;
        retTmp = ERROR;
    }
    
    std::for_each(daemonInterfaceCollection_.begin(), daemonInterfaceCollection_.end(), [&](DaemonInterface* tmp ) {tmp->disconnect(tmpObs);} );
    
    delete tmpObs;
    observerCollection_.erase(observer);
    return retTmp;
}


int ZprMonitor::getActValue( daemonType_ daemon ) {
    int value;
    DaemonInterface* tmpDaemon;
    if(daemon == RAM){
        daemonInterfaceCollection_[0]->doMeasure();
        value = daemonInterfaceCollection_[0]->getActValue();         
    } else if (daemon == CPU) {
        daemonInterfaceCollection_[1]->doMeasure();
        value = daemonInterfaceCollection_[1]->getActValue();         
    } else if (daemon == DISKPATH) {
        tmpDaemon = getDaemon_(DISKPATH);
        tmpDaemon->doMeasure();
        value = tmpDaemon->getActValue();
        delete tmpDaemon;         
    }
    return value;
}

int ZprMonitor::getActValue( std::string usrPath ) {
    int value;
    DaemonInterface* tmpDaemon;
    tmpDaemon = getDaemon_(DISKPATH, usrPath);
    tmpDaemon->doMeasure();
    value = tmpDaemon->getActValue();
    delete tmpDaemon;         
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

DaemonInterface* ZprMonitor::getDaemon_(daemonType_ daemon, std::string usrPath) {
    DaemonInterface* tmpDaemon;
    if (daemon == DISKPATH)
        tmpDaemon = new DiskPathDaemon(usrPath);
    return tmpDaemon;
}

int main() {
}

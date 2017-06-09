#ifndef __ZPRMONITOR_H__
#define __ZPRMONITOR_H__

#include<functional>
#include<vector>

#ifdef _ZPRBUILD
    #include"DaemonObserver.hpp"
    #include"DaemonInterface.hpp"
    #include"MeasureTimerThread.hpp"
    #include <memory>
    #include <thread>
    # define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
    # define DLLIMPORT __declspec (dllimport)
#endif


#ifdef _WINDOWS
class DLLIMPORT  ZprMonitor {
#else
class ZprMonitor {
#endif
public:
    enum daemonType_ {
        RAM,
        CPU,
        TASK,
        DISKPATH,
        DATA,
        USER
    };
    enum observerType_ {
        OVERRUN,
        UNDERRUN,
        INRANGE,
        AVERAGEOVERRUN,
        AVERAGEUNDERRUN
    };
    enum errorCode_ {
        OK = 0,
        ERROR = -1
    };
    ZprMonitor();
    virtual ~ZprMonitor();
    virtual errorCode_ registerCallback(daemonType_, observerType_, std::function< void(void) >, int, int, int, std::string);    
    virtual int getActValue(daemonType_);

#ifdef _ZPRBUILD
private:
    std::thread *timerThread_;
    MeasureTimerThread *threadFunctor_;
    DaemonInterface* getDaemon_(daemonType_);
//    std::vector< std::unique_ptr<DaemonObserver> > observerCollection_;
//    std::vector< std::unique_ptr<DaemonInterface> > daemonInterfaceCollection_;
    std::vector< DaemonInterface* > daemonInterfaceCollection_;
#endif
};

#endif

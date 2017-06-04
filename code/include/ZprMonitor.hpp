#ifndef __ZPRMONITOR_H__
#define __ZPRMONITOR_H__

#include<functional>
#include<vector>
#include"DaemonObserver.hpp"
#include"DaemonInterface.hpp"


class ZprMonitor {
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
    errorCode_ registerCallback(daemonType_, observerType_, std::function< void(void) >, int, int, int, std::string);    
    virtual int getActValue();
private:
    std::vector<DaemonObserver> daemonCollection_;
    std::vector<DaemonInterface> daemonInterfaceCollection_;

};

#endif

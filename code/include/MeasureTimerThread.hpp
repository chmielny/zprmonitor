#ifndef MEASURETIMERTHREAD_HPP_
#define MEASURETIMERTHREAD_HPP_
#include "DaemonInterface.hpp"

class MeasureTimerThread {
public:
    void operator()( void );
    MeasureTimerThread(std::vector< DaemonInterface* > &);
private:    
    std::vector< DaemonInterface* > daemons_;
};

#endif //MEASURETIMERTHREAD_HPP_

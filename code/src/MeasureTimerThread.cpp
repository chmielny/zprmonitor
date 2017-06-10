#include "../include/MeasureTimerThread.hpp"
#include<iostream>
#include<thread>
#include<thread>

MeasureTimerThread::MeasureTimerThread( std::vector< DaemonInterface* > &daemonVec ): daemons_(daemonVec) {
}

void MeasureTimerThread::operator()( void ) {
    while(!daemons_.empty()) {
        std::for_each( daemons_.begin(), daemons_.end(), [](DaemonInterface* ep){ ep->doMeasure(); } ); 
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}


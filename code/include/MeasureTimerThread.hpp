/**
 * @file
 *
 * \class MeasureTimerThread
 * Klasa MeasureTimerThread jest funktorem dla jedynego watku tworzonego przez ZprMonitor.
 * Operator () wywoluje co 250ms metode doMeasure() z daemonow zgromadzonych w kolekcji.
 * Metoda doMeasure() wysyla sygnal z daemona do podlaczonych obserwatorow.
 */

#ifndef MEASURETIMERTHREAD_HPP_
#define MEASURETIMERTHREAD_HPP_
#include "DaemonInterface.hpp"

class MeasureTimerThread {
public:
    void operator()( void );
    MeasureTimerThread(std::vector< DaemonInterface* > &);
private:    
    std::vector< DaemonInterface* > &daemons_;
};

#endif //MEASURETIMERTHREAD_HPP_

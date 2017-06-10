/**
 * @file
 *
 * \class DaemonInterface
 * Klasa bazowa dla wszystkich daemonow - obiektow badajacych konretne parametry systemu. Metody connect() i 
 * i disconnect() sluza do podlaczania i odlaczania slotow (boost::signals2) bedacych obserwatorami.
 * Metoda getActValue() odczytuje aktualna wartosc parametru z pola klasy actValue_. Metoda doMeasure()
 * wymusza pomiar parametru i wysyla sygnal do slotow. Jest ona wywolywana z osobnego watku z zegarem co 250ms.
 */

#ifndef DAEMONINTERFACE_HPP_
#define DAEMONINTERFACE_HPP_
#include<boost/signals2.hpp>
#include<boost/function.hpp>
#include "../include/DaemonObserver.hpp"

class DaemonInterface {
protected:
    typedef boost::signals2::signal<void (int)> Signal;
	Signal signal_;
	int actValue_;
public:
	void connect( DaemonObserver* );
	void disconnect( DaemonObserver* );
	virtual int getActValue();
	virtual void doMeasure() = 0;
	DaemonInterface(){};
	virtual ~DaemonInterface(){};
};


#endif //DAEMONINTERFACE_HPP_

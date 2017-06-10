/**
 * @file
 *
 * \class CpuDaemon
 * Klasa ktorej obiekty - daemony sprawdzaja przez metode doMeasure() zuzycie procesora w %.
 * Zawiera kod dla Windows / Linux. Metoda doMeasure() wysyla takze sygnal do zarejestrowanych slotow - obserwatorow.
 */

#ifndef CPUDAEMON_HPP_
#define CPUDAEMON_HPP_
#include "DaemonInterface.hpp"

class CpuDaemon : public DaemonInterface {
public:
	void getDaemonInstance();
	void doMeasure();
};


#endif //CPUDAEMON_HPP_

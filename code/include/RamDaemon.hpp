/**
 * @file
 *
 * \class RamDaemon
 * Klasa ktorej obiekty - daemony sprawdzaja przez metode doMeasure() zuzycie pamieci RAM w %.
 * Zawiera kod dla Windows / Linux. Metoda doMeasure() wysyla takze sygnal do zarejestrowanych slotow - obserwatorow.
 */

#ifndef RAMDAEMON_HPP_
#define RAMDAEMON_HPP_

#ifndef _WINDOWS
#include "sys/types.h"
#include "sys/sysinfo.h"
#endif

#include "DaemonInterface.hpp"

class RamDaemon : public DaemonInterface {
public:
	void getDaemonInstance();
	void doMeasure();

#ifndef _WINDOWS
private:
    struct sysinfo memInfo_;
#endif

};


#endif //RAMDAEMON_HPP_

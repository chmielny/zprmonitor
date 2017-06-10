/**
 * @file
 *
 * \class DiskPathDaemon
 * Klasa ktorej obiekty - daemony sprawdzaja przez metode doMeasure() ilosc wolnego miejsca na partycji okreslonej przez sciezke diskPath_..
 * Zawiera kod dla Windows / Linux. Metoda doMeasure() wysyla takze sygnal do zarejestrowanych slotow - obserwatorow.
 */

#ifndef DISKPATHDAEMON_HPP_
#define DISKPATHDAEMON_HPP_
#include<string>
#include"DaemonInterface.hpp"
#ifdef _LINUX
    #include <sys/statvfs.h>
#endif

class DiskPathDaemon : public DaemonInterface {
private:
	std::string diskPath_;
#ifdef _LINUX
    struct statvfs actStat_; 
#endif
public:
	void getInstance(std::string);
	DiskPathDaemon(std::string);
	DiskPathDaemon();
	void doMeasure();
	std::string getPath();
};


#endif //DISKPATHDAEMON_HPP_

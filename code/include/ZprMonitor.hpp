/**
 * @file
 *
 * \class ZprMonitor
 * Glowna klasa biblioteki. Definiuje metody i typy wyliczeniowe potrzebne do komunikacji z programem uzytkownika.
 *
 *
 * Metoda registerCallback( daemonType_ daemon, observerType_ observer, std::function< void(void) > callbackFunc, int minValue, 
 * int maxValue, int periodTime, std::string diskPath) pozwala na zarejestrowanie wskaźnika (trzeci argument std::function< void(void) >) na funkcję ze 
 * swojego programu. Pierwszy argument funkcji mówi o tym jaki parametr chcemy badać i jest typu enum ZprMonitor::daemonType_ ={RAM, CPU, DISKPATH} 
 * co odpowiada kolejno badaniu zużycia CPU w %, zajętości RAM-u w % oraz wolnego miejsca na dysku w GB. Drugi argument 
 * mówi o typie obserwatora tego parametru i także jest typem wyliczeniowym { OVERRUN, UNDERRUN, INRANGE, AVERAGEOVERRUN, 
 * AVERAGEUNDERRUN}. Obserwatorzy odpowiadają kolejno za wywołanie funkcji użytkownika gdy: przekroczono zadany maksymalny 
 * próg parametru (piąty argument int Max), przekroczono minimalny zadany próg parametru (czwarty argument wywołania int Min), 
 * parametr wyjdzie poza zakres (Min,Max), średnia krocząca parametru z okresu określonego przez szósty argument int Time 
 * (w sekundach) przekroczy wartość Max, średnia krocząca parametru z wcześniej wspomnianego okresu spadnie poniżej wartości Min. 
 * Ostatni argument typu string określa badaną ścieżkę w przypadku badania parametru DISKPATH. Funkcja zwraca unikalny identyfikator, 
 * niezbędny podczas wyrejestrowywania wskaźnika na funkcję.
 *
 *
 * Metoda unregisterCallback() pozwala wyrejestrować wskaźnik na funkcję, jako argument powinniśmy podać wartość zwróconą przez 
 * funckję registerCallback() podczas rejestracji wskaźnika. Zwraca wartość ZprMonitor::OK jeżeli operacja się powiodła lub 
 * ZprMonitor::ERROR w przeciwnym wypadku.
 *
 *
 * Metoda getActValue(daemonType_) pozwala na odczytanie aktualnej wartości zużycia CPU w % (argument wywołania ZprMonitor::CPU), 
 * zużycia pamięci RAM w %  (argument wywołania ZprMonitor::RAM) oraz ilości wolnego miejsca dla ścieżki aktualnego katalogu “. - kropka” 
 * w GB  (argument wywołania ZprMonitor::DISKPATH).
 *
 *
 * Metoda getActValue(string) pozwala na odczytanie ilości wolnego miejsca dla ścieżki podanej w argumencie.
 *
 */

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
//        TASK,
        DISKPATH,
//        DATA,
//        USER
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
    virtual unsigned long registerCallback(daemonType_, observerType_, std::function< void(void) >, int, int, int, std::string);    
    virtual errorCode_ unregisterCallback(unsigned long);    
    virtual int getActValue(daemonType_);
    virtual int getActValue(std::string);   //get free diskspace in GB by path

#ifdef _ZPRBUILD
private:
    unsigned long observerId_;
    std::thread *timerThread_;
    MeasureTimerThread *threadFunctor_;
    DaemonInterface* getDaemon_(daemonType_);
    DaemonInterface* getDaemon_(daemonType_, std::string);
    std::map< unsigned long, DaemonObserver* > observerCollection_;
    std::vector< DaemonInterface* > daemonInterfaceCollection_;
#endif
};

#endif

/**
 * @file
 *
 * \class AverageUnderrunObserver
 * Observetor sprawdzajacy w metodze update() wywolywanej przez operator() warunek przekroczenia przez srednia kroczaca
 * parametru z okresu time_ (w sekundach) wartosci minLimit_
 * i uruchamiajacy w razie czego funkcje zarejestrowana przez uzytkownika.
 * Do liczenia sredniej kroczacej wykorzystany bufor cykliczny z boost.
 */

#ifndef AVERAGEUNDERRUNOBSERVER_HPP_
#define AVERAGEUNDERRUNOBSERVER_HPP_
#include <functional>
#include "DaemonObserver.hpp"
#include <boost/circular_buffer.hpp>

class AverageUnderrunObserver : public DaemonObserver {
private:
	int minLimit_;
	int time_;      //czas w sekundach
    boost::circular_buffer<int>* buff_;
public:
	AverageUnderrunObserver(std::function<void(void)> ,int, int );
	~AverageUnderrunObserver();
	void update(int);
	void operator()(int);
};


#endif //AVERAGEUNDERRUNOBSERVER_HPP_

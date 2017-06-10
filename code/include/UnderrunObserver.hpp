/**
 * @file
 *
 * \class UnderrunObserver
 * Observetor sprawdzajacy w metodze update() wywolywanej przez operator() warunek przekroczenia przez parametr wartosci minLimit_
 * i uruchamiajacy w razie czego funkcje zarejestrowana przez uzytkownika.
 */

#ifndef UNDERRUNOBSERVER_HPP_
#define UNDERRUNOBSERVER_HPP_
#include "DaemonObserver.hpp"

class UnderrunObserver : public DaemonObserver {
private:
	int minLimit_;
public:
	UnderrunObserver(std::function<void(void)> ,int );
	void update(int);
	void operator()(int);
};


#endif //UNDERRUNOBSERVER_HPP_

/**
 * @file
 *
 * \class OverrunObserver
 * Observetor sprawdzajacy w metodze update() wywolywanej przez operator() warunek przekroczenia przez parametr wartosci maxLimit_
 * i uruchamiajacy w razie czego funkcje zarejestrowana przez uzytkownika.
 */

#ifndef OVERRUNOBSERVER_HPP_
#define OVERRUNOBSERVER_HPP_
#include <functional>
#include "DaemonObserver.hpp"

class OverrunObserver : public DaemonObserver {
private:
	int maxLimit_;
public:
	OverrunObserver(std::function<void(void)> ,int );
	void update(int);
	void operator()(int);
};


#endif //OVERRUNOBSERVER_HPP_

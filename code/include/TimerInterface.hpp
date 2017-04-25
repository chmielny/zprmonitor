#ifndef TIMERINTERFACE_HPP_
#define TIMERINTERFACE_HPP_
#include <vector>
#include "TimeObserver.hpp"

class TimerInterface {
private:
	std::vector<TimeObserver> timeObserverCollection_;
public:
	void notifyObservers();
	void unregisterObserver();
	void registerObserver();
};
#endif //TIMERINTERFACE_HPP_
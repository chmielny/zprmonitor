#ifndef TIMER_HPP_
#define TIMER_HPP_
#include <boost/signal.hpp>

typedef signal<void (int)> SignalTime;
typedef boost::function<void (int)> SlotTime

class Timer {
public:
	void notifyObservers();
	void connect(SlotTime);
};
#endif //TIMER_HPP_

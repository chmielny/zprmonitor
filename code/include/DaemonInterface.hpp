#ifndef DAEMONINTERFACE_HPP_
#define DAEMONINTERFACE_HPP_
#include<boost/signal.hpp>

typedef boost::signal<void (int)> Signal;
typedef boost::function<void (int)> Slot;
class DaemonInterface {
private:
	Signal signal_;
	int value;
public:
	void connect();//Slot);
	int getActValue();
	int notifyObservers();
};


#endif //DAEMONINTERFACE_HPP_

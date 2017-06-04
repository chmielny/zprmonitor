#ifndef DAEMONINTERFACE_HPP_
#define DAEMONINTERFACE_HPP_
#include<boost/signals2.hpp>

class DaemonInterface {
private:
    typedef boost::signals2::signal<void (int temp)> Signal;
    typedef Signal::slot_type Slot;
	Signal signal_;
	int value;
public:
	void connect();//Slot);
	virtual int getActValue() = 0;
	int notifyObservers();
};


#endif //DAEMONINTERFACE_HPP_

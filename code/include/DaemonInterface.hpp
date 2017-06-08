#ifndef DAEMONINTERFACE_HPP_
#define DAEMONINTERFACE_HPP_
#include<boost/signals2.hpp>
#include<boost/function.hpp>

class DaemonInterface {
private:
    typedef boost::signals2::signal<void (int)> Signal;
	Signal signal_;
	int value;
public:
	void connect( boost::function<void (int)> );
	virtual int getActValue() = 0;
	int notifyObservers();
	DaemonInterface(){};
	~DaemonInterface(){};
};


#endif //DAEMONINTERFACE_HPP_

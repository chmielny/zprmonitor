#ifndef DAEMONINTERFACE_HPP_
#define DAEMONINTERFACE_HPP_
#include<boost/signals2.hpp>
#include<boost/function.hpp>

class DaemonInterface {
protected:
    typedef boost::signals2::signal<void (int)> Signal;
	Signal signal_;
	int actValue_;
public:
	void connect( boost::function<void (int)> );
	virtual int getActValue();
	virtual void doMeasure() = 0;
	DaemonInterface(){};
	~DaemonInterface(){};
};


#endif //DAEMONINTERFACE_HPP_

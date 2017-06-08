#ifndef DAEMONOBSERVER_HPP_
#define DAEMONOBSERVER_HPP_
#include <functional>

class DaemonObserver {
protected:
	std::function<void(void)> userFunctionPtr_;
public:
	DaemonObserver( std::function<void(void)> );
	virtual void update(int) {} ;
};


#endif //DAEMONOBSERVER_HPP_

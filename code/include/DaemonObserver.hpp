#ifndef DAEMONOBSERVER_HPP_
#define DAEMONOBSERVER_HPP_
#include <functional>

class DaemonObserver {
private:
	std::function<void(void)> userFunctionPtr_;
public:
	DaemonObserver();
	void udpate(int);
};


#endif //DAEMONOBSERVER_HPP_

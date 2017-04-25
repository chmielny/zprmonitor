#ifndef DAEMONOBSERVER_HPP_
#define DAEMONOBSERVER_HPP_
#include <functional>

class DaemonObserver {
private:
	std::function<void(void)> userFunctionPtr_;
public:
	void notify(&DaemonInterface);
};


#endif //DAEMONOBSERVER_HPP_
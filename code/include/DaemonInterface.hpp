#ifndef DAEMONINTERFACE_HPP_
#define DAEMONINTERFACE_HPP_
#include <vector>
#include "DaemonObserver.hpp"

class DaemonInterface {
private:
//	std::vector<DaemonObserver> daemonObserverCollection_;
    std::vector<DaemonObserver> daemonCollection_;
public:
	int getActValue();
	int registerObserver();
	int unregisterObserver();
	int notifyObservers();
};


#endif //DAEMONINTERFACE_HPP_

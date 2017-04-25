#ifndef DAEMONINTERFACE_HPP_
#define DAEMONINTERFACE_HPP_
#include <vector>

class DaemonInterface {
private:
	std::vector <DaemonObserver> daemonObserverCollection_;
public:
	int getActValue();
	int registerObserver();
	int unregisterObserver();
	int notifyObservers();
};


#endif //DAEMONINTERFACE_HPP_
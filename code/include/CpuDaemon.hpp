#ifndef CPUDAEMON_HPP_
#define CPUDAEMON_HPP_
#include "DaemonInterface.hpp"

class CpuDaemon : public DaemonInterface {
public:
	void getDaemonInstance();
	int getActValue();
	void doMeasure();
};


#endif //CPUDAEMON_HPP_

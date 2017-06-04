#ifndef RAMDAEMON_HPP_
#define RAMDAEMON_HPP_
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "DaemonInterface.hpp"

class RamDaemon : public DaemonInterface {
public:
	int getActValue();
	void getDaemonInstance();

#ifndef _WINDOWS
private:
    struct sysinfo memInfo_;
#endif

};


#endif //RAMDAEMON_HPP_

#ifndef RAMDAEMON_HPP_
#define RAMDAEMON_HPP_

#ifndef _WINDOWS
#include "sys/types.h"
#include "sys/sysinfo.h"
#endif

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

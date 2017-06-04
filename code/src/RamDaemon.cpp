#include "../include/RamDaemon.hpp"
#include <iostream>

#ifndef _WINDOWS
int RamDaemon::getActValue() {
    if(sysinfo(&memInfo_) == 0) {
        long long totalPhysMem = memInfo_.totalram * memInfo_.mem_unit;
        long long physMemUsed = (memInfo_.totalram - memInfo_.freeram) * memInfo_.mem_unit;
        return physMemUsed * 100 / totalPhysMem;
    } else {
        std::cerr << "Get meminfo failed" << std::endl;
        return -1;
    } 
}
#endif

#ifndef _LINUX
#include "windows.h"
int RamDaemon::getActValue() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (memInfo.dwLength != 0) {
        GlobalMemoryStatusEx(&memInfo);
        DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
        DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
        DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
        return physMemUsed * 100 / totalPhysMem;
    }
    else {
        std::cerr << "memInfo failed" << std::endl;
        return -1
    }
}
#endif

#include "../include/RamDaemon.hpp"
#include <iostream>


#ifndef _WINDOWS
void RamDaemon::doMeasure() {
    if(sysinfo(&memInfo_) == 0) {
        long long totalPhysMem = memInfo_.totalram * memInfo_.mem_unit;
        long long physMemUsed = (memInfo_.totalram - memInfo_.freeram) * memInfo_.mem_unit;
        actValue_ = physMemUsed * 100 / totalPhysMem;
        signal_(actValue_); 
    } else {
        std::cerr << "Get meminfo failed" << std::endl;
        actValue_ = -1;
    } 
}
#endif

#ifndef _LINUX
#include "windows.h"
void RamDaemon::doMeasure() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (memInfo.dwLength != 0) {
        GlobalMemoryStatusEx(&memInfo);
        DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
        DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
        DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
        actValue_ = physMemUsed * 100 / totalPhysMem;
        signal_(actValue_); 
    }
    else {
        std::cerr << "memInfo failed" << std::endl;
        actValue_ = -1;
    }
}
#endif

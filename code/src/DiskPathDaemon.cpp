#include "../include/DiskPathDaemon.hpp"
#include <iostream>

void DiskPathDaemon::doMeasure() {

}

#ifdef _LINUX
int DiskPathDaemon::getActValue() {
    statvfs("/home/", &actStat_);
    return actStat_.f_bfree * actStat_.f_bsize / 1024 / 1024 / 1024; 
}

#elif _WINDOWS
#include<Windows.h>
int DiskPathDaemon::getActValue() {
    typedef ULARGE_INTEGER PULARGE_INTEGER;
    PULARGE_INTEGER dataQuery;

    if (GetDiskFreeSpaceEx(NULL, &dataQuery, NULL, NULL)) {
        return dataQuery.QuadPart / 1024 / 1024 / 1024;
    }
    else {
        std::cerr << "getting disc free space failed" << std::endl;
        return -1;
    }
}
#endif

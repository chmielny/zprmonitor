#include "../include/DiskPathDaemon.hpp"
#include <iostream>


#ifdef _LINUX
void DiskPathDaemon::doMeasure() {
    statvfs("/home/", &actStat_);
    actValue_ = actStat_.f_bfree * actStat_.f_bsize / 1024 / 1024 / 1024; 
}

#elif _WINDOWS
#include<Windows.h>
void DiskPathDaemon::doMeasure() {
    typedef ULARGE_INTEGER PULARGE_INTEGER;
    PULARGE_INTEGER dataQuery;

    if (GetDiskFreeSpaceEx(NULL, &dataQuery, NULL, NULL)) {
        actValue_ = dataQuery.QuadPart / 1024 / 1024 / 1024;
        signal_(actValue_); 
    }
    else {
        std::cerr << "getting disc free space failed" << std::endl;
        actValue_ = -1;
    }
}
#endif

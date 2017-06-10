#include "../include/DiskPathDaemon.hpp"
#include <iostream>


#ifdef _LINUX
void DiskPathDaemon::doMeasure() {
    if(statvfs(diskPath_.c_str(), &actStat_) == 0) {
        actValue_ = actStat_.f_bfree * actStat_.f_bsize / 1024 / 1024 / 1024; 
        signal_(actValue_); 
    } else {
        std::cerr << "getting disc free space failed" << std::endl;
        actValue_ = -1;
    }
}

#elif _WINDOWS
#include<Windows.h>
void DiskPathDaemon::doMeasure() {
//    typedef ULARGE_INTEGER PULARGE_INTEGER;
    ULARGE_INTEGER dataQuery;

    if (GetDiskFreeSpaceEx(diskPath_.c_str(), &dataQuery, NULL, NULL)) {
        actValue_ = static_cast<int>(dataQuery.QuadPart / 1024 / 1024 / 1024);
        signal_(actValue_); 
    }
    else {
        std::cerr << "getting disc free space failed" << std::endl;
        actValue_ = -1;
    }
}
#endif

DiskPathDaemon::DiskPathDaemon() {
    diskPath_ = ".";
}

DiskPathDaemon::DiskPathDaemon(std::string userPath) : diskPath_(userPath) {
}

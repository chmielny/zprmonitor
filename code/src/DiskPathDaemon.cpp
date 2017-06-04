#include "../include/DiskPathDaemon.hpp"


int DiskPathDaemon::getActValue() {
    statvfs("/home/", &actStat_);
    return actStat_.f_bfree * actStat_.f_bsize / 1024 / 1024 / 1024; 
}

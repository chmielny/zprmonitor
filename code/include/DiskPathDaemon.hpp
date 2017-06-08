#ifndef DISKPATHDAEMON_HPP_
#define DISKPATHDAEMON_HPP_
#include<string>
#include"DaemonInterface.hpp"
#ifdef _LINUX
    #include <sys/statvfs.h>
#endif

class DiskPathDaemon : public DaemonInterface {
private:
	std::string diskPath_;
#ifdef _LINUX
    struct statvfs actStat_; 
#endif
public:
	int getActValue();
	void doMeasure();
	void getInstance(std::string);
	std::string getPath();
};


#endif //DISKPATHDAEMON_HPP_

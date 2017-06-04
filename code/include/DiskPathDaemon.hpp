#ifndef DISKPATHDAEMON_HPP_
#define DISKPATHDAEMON_HPP_
#include<string>
#include"DaemonInterface.hpp"
#include <sys/statvfs.h>

class DiskPathDaemon : public DaemonInterface {
private:
	std::string diskPath_;
    struct statvfs actStat_; 

public:
	int getActValue();
	void getInstance(std::string);
	std::string getPath();
};


#endif //DISKPATHDAEMON_HPP_

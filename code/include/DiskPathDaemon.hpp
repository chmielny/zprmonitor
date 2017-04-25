#ifndef DISKPATHDAEMON_HPP_
#define DISKPATHDAEMON_HPP_
#include<string>

class DiskPathDaemon : public DaemonInterface {
private:
	std::string diskPath_;

public:
	void getInstance(std::string)();
	std::string getPath();
};


#endif //DISKPATHDAEMON_HPP_
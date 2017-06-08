#ifndef OVERRUNOBSERVER_HPP_
#define OVERRUNOBSERVER_HPP_
#include <functional>
#include "DaemonObserver.hpp"

class OverrunObserver : public DaemonObserver {
private:
	int maxLimit_;
public:
	OverrunObserver(std::function<void(void)> ,int );
	void update(int);
};


#endif //OVERRUNOBSERVER_HPP_

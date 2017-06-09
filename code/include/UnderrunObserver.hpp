#ifndef UNDERRUNOBSERVER_HPP_
#define UNDERRUNOBSERVER_HPP_
#include "DaemonObserver.hpp"

class UnderrunObserver : public DaemonObserver {
private:
	int minLimit_;
public:
	UnderrunObserver(std::function<void(void)> ,int );
	void update(int);
};


#endif //UNDERRUNOBSERVER_HPP_

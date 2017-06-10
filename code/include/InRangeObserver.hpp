#ifndef INRANGEOBSERVER_HPP_
#define INRANGEOBSERVER_HPP_
#include <functional>
#include "DaemonObserver.hpp"

class InRangeObserver : public DaemonObserver {
private:
	int minLimit_;
	int maxLimit_;
public:
	InRangeObserver(std::function<void(void)> ,int, int );
	void update(int);
	void operator()(int);
};


#endif //INRANGEOBSERVER_HPP_

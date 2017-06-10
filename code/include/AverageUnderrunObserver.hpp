#ifndef AVERAGEUNDERRUNOBSERVER_HPP_
#define AVERAGEUNDERRUNOBSERVER_HPP_
#include <functional>
#include "DaemonObserver.hpp"
#include <boost/circular_buffer.hpp>

class AverageUnderrunObserver : public DaemonObserver {
private:
	int minLimit_;
	int time_;      //czas w sekundach
    boost::circular_buffer<int>* buff_;
public:
	AverageUnderrunObserver(std::function<void(void)> ,int, int );
	~AverageUnderrunObserver();
	void update(int);
	void operator()(int);
};


#endif //AVERAGEUNDERRUNOBSERVER_HPP_

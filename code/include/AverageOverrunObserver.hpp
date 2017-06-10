#ifndef AVERAGEOVERRUNOBSERVER_HPP_
#define AVERAGEOVERRUNOBSERVER_HPP_
#include <functional>
#include "DaemonObserver.hpp"
#include <boost/circular_buffer.hpp>

class AverageOverrunObserver : public DaemonObserver {
private:
	int maxLimit_;
	int time_;      //czas w sekundach
    boost::circular_buffer<int>* buff_;
public:
	AverageOverrunObserver(std::function<void(void)> ,int, int );
	~AverageOverrunObserver();
	void update(int);
	void operator()(int);
};


#endif //AVERAGEOVERRUNOBSERVER_HPP_

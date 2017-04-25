#ifndef AVERAGEOVERRUNOBSERVER_HPP_
#define AVERAGEOVERRUNOBSERVER_HPP_

class AverageOverrunObserver : public TimeObserver {
private:
	int maxLimit_;
public:
	AverageOverrunObserver(int, int);
};


#endif //AVERAGEOVERRUNOBSERVER_HPP_
#ifndef AVERAGEUNDERRUNOBSERVER_HPP_
#define AVERAGEUNDERRUNOBSERVER_HPP_

class AverageUnderrunObserver : public TimeObserver {
private:
	int minLimit_;
public:
	AverageUnderrunObserver(int, int);
};


#endif //AVERAGEUNDERRUNOBSERVER_HPP_
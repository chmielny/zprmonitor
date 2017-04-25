#ifndef TIMEOBSERVER_HPP_
#define TIMEOBSERVER_HPP_

class TimeObserver : public DaemonObserver {
private:
	int timePeriod_;
public:
	void fromTimerNotify();
};


#endif //TIMEOBSERVER_HPP_
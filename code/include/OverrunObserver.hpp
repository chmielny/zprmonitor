#ifndef OVERRUNOBSERVER_HPP_
#define OVERRUNOBSERVER_HPP_

class OverrunObserver : public DaemonObserver {
private:
	int maxLimit_;
public:
	OverrunObserver(int);
};


#endif //OVERRUNOBSERVER_HPP_
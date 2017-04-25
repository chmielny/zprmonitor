#ifndef UNDERRUNOBSERVER_HPP_
#define UNDERRUNOBSERVER_HPP_

class UnderrunObserver : public DaemonObserver {
private:
	int minLimit_;
public:
	UnderrunObserver(int);
};


#endif //UNDERRUNOBSERVER_HPP_
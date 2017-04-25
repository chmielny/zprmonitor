#ifndef INRANGEOBSERVER_HPP_
#define INRANGEOBSERVER_HPP_

class InRangeObserver : public TimeObserver {
private:
	int minLimit_;
	int maxLimit_;
public:
	InRangeObserver(int, int);
};


#endif //INRANGEOBSERVER_HPP_
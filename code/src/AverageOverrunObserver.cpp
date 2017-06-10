#include "../include/AverageOverrunObserver.hpp"
#include <numeric>

AverageOverrunObserver::AverageOverrunObserver(std::function<void (void)> usrFunc ,int usrLimit, int usrTime ) 
: DaemonObserver( usrFunc ), maxLimit_(usrLimit), time_(usrTime) {
    buff_ = new boost::circular_buffer<int>( time_ * 4  );
}

AverageOverrunObserver::~AverageOverrunObserver( ) {
    delete buff_;
}

void AverageOverrunObserver::update(int value) {
    buff_->push_back(value);
    if(buff_->full())
        //porownanie do sredniej kroczacej
        if( (std::accumulate(buff_->begin(), buff_->end(), 0) / static_cast<int>(buff_->size()) ) > maxLimit_)
            userFunctionPtr_();
}

void AverageOverrunObserver::operator()(int value) {
    update(value);
}

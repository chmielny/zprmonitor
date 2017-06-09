#include "../include/AverageUnderrunObserver.hpp"
#include <numeric>

AverageUnderrunObserver::AverageUnderrunObserver(std::function<void (void)> usrFunc ,int usrLimit, int usrTime ) 
: DaemonObserver( usrFunc ), minLimit_(usrLimit), time_(usrTime) {
    buff_ = new boost::circular_buffer<int>( time_ * 4  );
}

AverageUnderrunObserver::~AverageUnderrunObserver( ) {
    delete buff_;
}

void AverageUnderrunObserver::update(int value) {
    buff_->push_back(value);
    if(buff_->full())
        //porownanie do sredniej kroczacej
        if( (std::accumulate(buff_->begin(), buff_->end(), 0) / static_cast<int>(buff_->size()) ) < minLimit_)
            userFunctionPtr_();
}

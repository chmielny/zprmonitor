#ifndef DAEMONOBSERVER_HPP_
#define DAEMONOBSERVER_HPP_
#include <functional>

class DaemonObserver {
protected:
	std::function<void(void)> userFunctionPtr_;
public:
	DaemonObserver( std::function<void(void)> );
	virtual ~DaemonObserver( );
	virtual void update(int) {} ;
	virtual void operator()(int) {} ;
    bool operator ==( const DaemonObserver& ) const;
};


#endif //DAEMONOBSERVER_HPP_

#include "../include/DaemonObserver.hpp"

DaemonObserver::DaemonObserver( std::function<void(void)> funcPtr ): userFunctionPtr_(funcPtr) {
}

#include "../../code/include/ZprMonitor.hpp"
#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#ifdef _LINUX
    #include <dlfcn.h>
#elif _WINDOWS
    #include <windows.h>
#endif

void myFun( void ) {
    std::cout << "Przekroczono zadany parametr!" << std::endl;
}



int main() {
#ifdef _LINUX	
    void* handle = dlopen("../code/libZprMonitor.so", RTLD_LAZY);
#elif _WINDOWS
    HMODULE handle = LoadLibrary("../code/ZprMonitor.dll");
#endif
    if(handle == NULL) {
        std::cout << "Biblioteka zprmonitor nie otwiera sie:" << std::endl;
#ifdef _LINUX     
	std::cout << dlerror();
#endif
	std::cout << std::endl;
    } else {
        ZprMonitor* (*create)();
        void (*destroy)(ZprMonitor*);

#ifdef _LINUX     
        create = (ZprMonitor* (*)())dlsym(handle, "create_object");
        destroy = (void (*)(ZprMonitor*))dlsym(handle, "destroy_object");		
#elif _WINDOWS
        create = (ZprMonitor* (*)())GetProcAddress(handle, "create_object");
        destroy = (void (*)(ZprMonitor*))GetProcAddress(handle, "destroy_object");
#endif


        ZprMonitor* myClass = (ZprMonitor*)create();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        std::cout << "RAM: "  << myClass->getActValue(ZprMonitor::RAM) << std::endl;
        std::cout << "CPU: "  <<myClass->getActValue(ZprMonitor::CPU) << std::endl;
        std::cout << "DISK: " << myClass->getActValue(ZprMonitor::DISKPATH) << std::endl;

        std::function < void( void ) > myFunAddr;
        myFunAddr = &myFun;
        myClass->registerCallback(ZprMonitor::CPU, ZprMonitor::OVERRUN, myFunAddr, 60, 0, 0, "0");    
        while(1);
        destroy( myClass );
    }
}

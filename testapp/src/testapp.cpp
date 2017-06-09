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

void myCpuMax( void ) {
    std::cout << "Przekroczono CPU 60 %" << std::endl;
}

void myCpuMin( void ) {
    std::cout << "CPU ponizej 20 %" << std::endl;
}

void myCpuRange( void ) {
    std::cout << "CPU poza zakresem 20% - 70%" << std::endl;
}

void myCpuAverMax( void ) {
    std::cout << "CPU - srednia kroczaca z 5s powyzej 50%" << std::endl;
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

        std::function < void( void ) > myCpuMaxAddr, myCpuMinAddr, myCpuRangeAddr, myCpuAverMaxAddr;

        myCpuMaxAddr = &myCpuMax;
        myCpuMinAddr = &myCpuMin;
        myCpuRangeAddr = &myCpuRange;
        myCpuAverMaxAddr = &myCpuAverMax;

        myClass->registerCallback(ZprMonitor::CPU, ZprMonitor::OVERRUN, myCpuMaxAddr, 0, 60, 0, "0");   
        myClass->registerCallback(ZprMonitor::CPU, ZprMonitor::UNDERRUN, myCpuMinAddr, 20, 0, 0, "0");    
        myClass->registerCallback(ZprMonitor::CPU, ZprMonitor::INRANGE, myCpuRangeAddr, 20, 70, 0, "0");    
        myClass->registerCallback(ZprMonitor::CPU, ZprMonitor::AVERAGEOVERRUN, myCpuAverMaxAddr, 0, 50, 5, "0");    


        while(1)
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        destroy( myClass );
    }
}

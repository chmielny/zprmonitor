#include "../../code/include/ZprMonitor.hpp"
#include <iostream>
#ifdef _LINUX
    #include <dlfcn.h>
#elif _WINDOWS
    #include <windows.h>
#endif

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
        std::cout << myClass->getActValue() << std::endl;
        destroy( myClass );
    }
}

#include "include/ZprMonitor.hpp"
#include <dlfcn.h>
#include <iostream>


int main() {
    void* handle = dlopen("./libZprMonitor.so", RTLD_LAZY);
    if(handle == NULL) {
        std::cout << "nie otwiera sie" << std::endl;
        std::cout << dlerror();
        std::cout << std::endl;
    } else {
        ZprMonitor* (*create)();
        void (*destroy)(ZprMonitor*);

        create = (ZprMonitor* (*)())dlsym(handle, "create_object");
        destroy = (void (*)(ZprMonitor*))dlsym(handle, "destroy_object");

        ZprMonitor* myClass = (ZprMonitor*)create();
        std::cout << myClass->getActValue();
        destroy( myClass );
    }
}

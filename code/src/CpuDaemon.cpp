#include "../include/CpuDaemon.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>


#ifdef _LINUX
void CpuDaemon::doMeasure() {
    double percent;
    unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;
    std::ifstream ifs;
    std::string tmp;

    ifs.open("/proc/stat");
    ifs >> tmp >> lastTotalUser >> lastTotalUserLow >> lastTotalSys >> lastTotalIdle ;
    ifs.close();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    ifs.open("/proc/stat");
    ifs >> tmp >> totalUser >> totalUserLow >> totalSys >> totalIdle ;
    ifs.close();

    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
        totalSys < lastTotalSys || totalIdle < lastTotalIdle){
        std::cerr << "getting cpu usage failed" << std::endl;
        percent = -1.0;
    }
    else{
        total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
            (totalSys - lastTotalSys);
        percent = total;
        total += (totalIdle - lastTotalIdle);
        percent /= total;
        percent *= 100;
    }
    actValue_ = (int)percent;
    signal_(actValue_); 
}

#elif _WINDOWS
#include "TCHAR.h"
#include "pdh.h"
#include <Windows.h>
static PDH_HQUERY cpuQuery;
static PDH_HCOUNTER cpuTotal;

void init() {
    PdhOpenQuery(NULL, NULL, &cpuQuery);
    PdhAddEnglishCounter(cpuQuery, _T("\\Processor(_Total)\\% Processor Time"), NULL, &cpuTotal);
    PdhCollectQueryData(cpuQuery);
}

double getCurrentValue() {
    PDH_FMT_COUNTERVALUE counterVal;
    PdhCollectQueryData(cpuQuery);
    PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
    return counterVal.doubleValue;
}

void CpuDaemon::doMeasure() {
    init();
    if (cpuQuery != 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        actValue_ = getCurrentValue();
        signal_(actValue_); 
    }
    else {
        std::cerr << "getting cpu usage failed" << std::endl;
        actValue_ = -1;
    }
}

#endif

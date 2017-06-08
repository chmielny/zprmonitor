#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "../include/CpuDaemon.hpp"
#include <iostream>

#ifdef _LINUX
static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
int CpuDaemon::getActValue() {
    double percent;
    FILE* file;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

    file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
        &totalSys, &totalIdle);
    fclose(file);

    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
        totalSys < lastTotalSys || totalIdle < lastTotalIdle){
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

    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    return (int)percent;
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

int CpuDaemon::getActValue() {
    init();
    if (cpuQuery != 0) {
        Sleep(100);
        return getCurrentValue();
    }
    else {
        std::cerr << "getting cpu usage failed" << std::endl;
        return -1;
    }
}

#endif

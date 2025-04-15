#pragma once

#include "NetworkBase.h"
#include "DataProcessorUtils.h"
#include <string>


class DataProcessor {
private:
    NetworkBase _processorServer;
    NetworkBase _displayConnector;
    DataProcessorUtils _utils;

public:
    DataProcessor(const char* displayIp, int processorPort, int displayPort);
    void run();
    const DataProcessorUtils& getUtils() const;
};

#pragma once

#include "SocketManager.h"
#include "DataProcessorUtils.h"
#include <string>


class DataProcessor {
private:
    SocketManager _processorServer;
    SocketManager _displayConnector;
    DataProcessorUtils _utils;

public:
    DataProcessor(const char* displayIp, int processorPort, int displayPort);
    void run();
    const DataProcessorUtils& getUtils() const;
};

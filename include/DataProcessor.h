#pragma once

#include "NetworkBase.h"
#include <string>

class DataProcessor {
private:
    NetworkBase _clientServer;
    NetworkBase _displayClient;

    std::string processData(const std::string& data);

public:
    DataProcessor(const char* displayIp, int processorPort, int displayPort);
    void run();
};

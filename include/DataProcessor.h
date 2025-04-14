#pragma once

#include "NetworkBase.h"
#include <string>

class DataProcessor {
private:
    NetworkBase _clientServer;
    NetworkBase _displayClient;

    std::string processData(const std::string& data);

public:
    DataProcessor(int processorPort, const char* displayIp, int displayPort);
    void run();
};

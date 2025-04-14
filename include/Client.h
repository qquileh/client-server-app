#pragma once

#include "NetworkBase.h"
#include <string>

class Client {
private:
    NetworkBase _network;

public:
    Client(const char* ip, int port);
    void sendData(const std::string& data);
    void run();

};

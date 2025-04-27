#pragma once

#include "SocketManager.h"
#include <string>

class Client {
private:
    SocketManager _network;

public:
    Client(const char* ip, int port);
    void sendData(const std::string& data);
    void run();
};

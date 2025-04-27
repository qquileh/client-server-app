#pragma once

#include "SocketManager.h"

class DisplayServer {
private:
    SocketManager _network;

public:
    DisplayServer(int port);
    void run();
};

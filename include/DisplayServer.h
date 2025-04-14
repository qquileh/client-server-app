#pragma once

#include "NetworkBase.h"

class DisplayServer {
private:
    NetworkBase _network;

public:
    DisplayServer(int port);
    void run();
};

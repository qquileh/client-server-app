#pragma once

#include <ws2tcpip.h>
#include <string>
#include <stdexcept>

class NetworkBase {
private:
    SOCKET socketHandle;
    sockaddr_in address;

public:
    NetworkBase();
    ~NetworkBase();

    void initWinsock();
    void createSocket(int type = SOCK_STREAM);
    void setupAddress(int port, const char* ip = nullptr);

    SOCKET getSocket() const;
    sockaddr_in* getAddress();
};

#pragma once

#include <ws2tcpip.h>
#include <string>
#include <stdexcept>

class SocketManager {
private:
    SOCKET socketHandle;
    sockaddr_in address;

public:
    SocketManager();
    ~SocketManager();

    void createSocket(int type = SOCK_STREAM);
    void setupAddress(int port, const char* ip = nullptr);

    SOCKET getSocket() const;
    sockaddr_in* getAddress();
};

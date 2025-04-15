#include "../include/NetworkBase.h"
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


NetworkBase::NetworkBase() : socketHandle(INVALID_SOCKET), address{} {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("WSAStartup failed");
    }
}

void NetworkBase::createSocket(int type) {
    socketHandle = socket(AF_INET, type, 0);
    if (socketHandle == INVALID_SOCKET) {
        throw std::runtime_error("Socket creation error");
    }
}

void NetworkBase::setupAddress(int port, const char* ip) {
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (ip) {
        inet_pton(AF_INET, ip, &address.sin_addr);
    } else {
        address.sin_addr.s_addr = INADDR_ANY;
    }
}

NetworkBase::~NetworkBase() {
    if (socketHandle != INVALID_SOCKET) {
        closesocket(socketHandle);
    }
    WSACleanup();
}

SOCKET NetworkBase::getSocket() const {
    return socketHandle;
}

sockaddr_in* NetworkBase::getAddress() {
    return &address;
}

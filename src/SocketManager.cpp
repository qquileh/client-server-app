#include "../include/SocketManager.h"
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


SocketManager::SocketManager() : socketHandle(INVALID_SOCKET), address{} {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("WSAStartup failed");
    }
}

void SocketManager::createSocket(int type) {
    socketHandle = socket(AF_INET, type, 0);
    if (socketHandle == INVALID_SOCKET) {
        throw std::runtime_error("Socket creation error");
    }
}

void SocketManager::setupAddress(int port, const char* ip) {
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (ip) {
        inet_pton(AF_INET, ip, &address.sin_addr);
    } else {
        address.sin_addr.s_addr = INADDR_ANY;
    }
}

SocketManager::~SocketManager() {
    if (socketHandle != INVALID_SOCKET) {
        closesocket(socketHandle);
    }
    WSACleanup();
}

SOCKET SocketManager::getSocket() const {
    return socketHandle;
}

sockaddr_in* SocketManager::getAddress() {
    return &address;
}

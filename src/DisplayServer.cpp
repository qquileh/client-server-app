#include "../include/DisplayServer.h"
#include <stdexcept>
#include <iostream>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


DisplayServer::DisplayServer(int port) : _network() {
    _network.initWinsock();
    _network.createSocket();
    _network.setupAddress(port);

    if (bind(_network.getSocket(), (sockaddr*)_network.getAddress(), sizeof(sockaddr_in)) == SOCKET_ERROR) {
        throw std::runtime_error("Bind failed");
    }

    listen(_network.getSocket(), 5);
}

void DisplayServer::run() {
    std::cout << "Display Server started. Waiting for data..." << std::endl;
    while (true) {
        SOCKET clientSocket = accept(_network.getSocket(), nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) continue;

        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "Result: " << buffer << std::endl;
        }
        closesocket(clientSocket);
    }
}

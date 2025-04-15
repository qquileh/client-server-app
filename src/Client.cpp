#include "../include/Client.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


Client::Client(const char* ip, int port) : _network() {
    _network.createSocket();
    _network.setupAddress(port, ip);

    if (connect(_network.getSocket(), (sockaddr*)_network.getAddress(), sizeof(sockaddr_in)) == SOCKET_ERROR) {
        throw std::runtime_error("Connection failed");
    }
}

void Client::sendData(const std::string& data) {
    SOCKET socket = _network.getSocket();
    if (send(socket, data.c_str(), (int) data.size(), 0) == SOCKET_ERROR) {
        throw std::runtime_error("Send failed");
    }

    char buffer[1024];
    int bytesReceived = recv(socket, buffer, sizeof(buffer), 0);
    if (bytesReceived <= 0) {
        throw std::runtime_error("Server disconnected");
    }
    buffer[bytesReceived] = '\0';
}

void Client::run() {
    std::cout << "Client started." << std::endl;
    std::string input;
    while (std::getline(std::cin, input)) {
        if (input.empty()) {
            continue;
        }
        sendData(input);
    }
}
#include "../include/DataProcessor.h"
#include <iostream>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


const DataProcessorUtils& DataProcessor::getUtils() const {
    return _utils;
}

DataProcessor::DataProcessor(const char* displayIp, int processorPort, int displayPort)
    : _processorServer(), _displayConnector() {

    _processorServer.createSocket();
    _processorServer.setupAddress(processorPort);

    if (bind(_processorServer.getSocket(), (sockaddr*)_processorServer.getAddress(), sizeof(sockaddr_in)) == SOCKET_ERROR) {
        throw std::runtime_error("Bind failed");
    }
    listen(_processorServer.getSocket(), 5);


    _displayConnector.createSocket();
    _displayConnector.setupAddress(displayPort, displayIp);

    if (connect(_displayConnector.getSocket(), (sockaddr*)_displayConnector.getAddress(), sizeof(sockaddr_in)) == SOCKET_ERROR) {
        throw std::runtime_error("Connection to display server failed");
    }
}

void DataProcessor::run() {
    std::cout << "Data Processor started." << std::endl;
    while (true) {
        SOCKET clientSocket = accept(_processorServer.getSocket(), nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            continue;
        }

        char buffer[1024];
        int bytesReceived;
        do {
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                std::string result = _utils.processData(buffer);
                send(clientSocket, "OK", 2, 0);
                send(_displayConnector.getSocket(), result.c_str(), (int) result.size(), 0);
            }
        } while (bytesReceived > 0);

        closesocket(clientSocket);
    }
}

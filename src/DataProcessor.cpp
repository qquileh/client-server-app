#include "../include/DataProcessor.h"
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


DataProcessor::DataProcessor(int processorPort, const char* displayIp, int displayPort)
    : _clientServer(), _displayClient() {

    _clientServer.initWinsock();
    _clientServer.createSocket();
    _clientServer.setupAddress(processorPort);

    if (bind(_clientServer.getSocket(), (sockaddr*)_clientServer.getAddress(), sizeof(sockaddr_in)) == SOCKET_ERROR) {
        throw std::runtime_error("Bind failed");
    }
    listen(_clientServer.getSocket(), 5);


    _displayClient.initWinsock();
    _displayClient.createSocket();
    _displayClient.setupAddress(displayPort, displayIp);

    if (connect(_displayClient.getSocket(), (sockaddr*)_displayClient.getAddress(), sizeof(sockaddr_in)) == SOCKET_ERROR) {
        throw std::runtime_error("Connection to display server failed");
    }
}

std::string DataProcessor::processData(const std::string& data) {
    std::istringstream iss(data);
    std::unordered_set<std::string> uniqueWords;
    std::string word;
    while (iss >> word) {
        uniqueWords.insert(word);
    }

    std::ostringstream oss;
    for (const auto& w : uniqueWords) {
        oss << w << " ";
    }
    std::string result = oss.str();
    if (!result.empty()) result.pop_back();
    return result;
}

void DataProcessor::run() {
    std::cout << "Data Processor started. Waiting for clients..." << std::endl;
    while (true) {
        SOCKET clientSocket = accept(_clientServer.getSocket(), nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) continue;

        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::string result = processData(buffer);

            // Отправка подтверждения клиенту
            send(clientSocket, "OK", 2, 0);

            // Отправка результата на сервер отображения
            send(_displayClient.getSocket(), result.c_str(), result.size(), 0);
        }
        closesocket(clientSocket);
    }
}

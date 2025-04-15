#include "../include/DataProcessor.h"
#include <iostream>
#include <unordered_set>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


DataProcessor::DataProcessor(const char* displayIp, int processorPort, int displayPort)
    : _clientServer(), _displayClient() {

    _clientServer.createSocket();
    _clientServer.setupAddress(processorPort);

    if (bind(_clientServer.getSocket(), (sockaddr*)_clientServer.getAddress(), sizeof(sockaddr_in)) == SOCKET_ERROR) {
        throw std::runtime_error("Bind failed");
    }
    listen(_clientServer.getSocket(), 5);


    _displayClient.createSocket();
    _displayClient.setupAddress(displayPort, displayIp);

    if (connect(_displayClient.getSocket(), (sockaddr*)_displayClient.getAddress(), sizeof(sockaddr_in)) == SOCKET_ERROR) {
        throw std::runtime_error("Connection to display server failed");
    }
}

std::string DataProcessor::processData(const std::string& data) {
    std::unordered_set<std::string> uniqueWords;
    std::vector<std::string> tokens;
    std::string currentToken;
    bool isCurrentWord = false;

    for (char c : data) {
        bool isWordChar = (std::isalpha(c) || c == '-' || c == '\'');

        if (isWordChar) {
            if (!isCurrentWord && !currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            isCurrentWord = true;
            currentToken += c;
        } else {
            if (isCurrentWord && !currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            isCurrentWord = false;
            currentToken += c;
        }
    }

    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    std::string result;
    for (const auto& token : tokens) {
        bool isWord = true;
        for (char c : token) {
            if (!std::isalpha(c) && c != '-' && c != '\'') {
                isWord = false;
                break;
            }
        }

        if (isWord && !token.empty()) {
            if (uniqueWords.insert(token).second) {
                result += token;
            }
        } else {
            result += token;
        }
    }

    return result;
}

void DataProcessor::run() {
    std::cout << "Data Processor started. Waiting for clients..." << std::endl;
    while (true) {
        SOCKET clientSocket = accept(_clientServer.getSocket(), nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            continue;
        }

        char buffer[1024];
        int bytesReceived;
        do {
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                std::string result = processData(buffer);
                send(clientSocket, "OK", 2, 0);
                send(_displayClient.getSocket(), result.c_str(), (int) result.size(), 0);
            }
        } while (bytesReceived > 0);

        closesocket(clientSocket);
    }
}

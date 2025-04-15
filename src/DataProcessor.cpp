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
    std::string result;
    std::string currentWord;
    bool isInvalid = false;
    bool lastSymbolWasNonAlpha = false;
    bool hasValidWords = false;

    for (size_t i = 0; i < data.size(); ++i) {
        char c = data[i];

        if (std::isalpha(static_cast<unsigned char>(c))) {
            currentWord += c;
            lastSymbolWasNonAlpha = false;
            hasValidWords = true;
        } else {
            if (!currentWord.empty()) {
                if (uniqueWords.insert(currentWord).second) {
                    if (!result.empty()) {
                        result += " ";
                    }
                    result += currentWord;
                }
                currentWord.clear();
            }

            if (c != ' ' && c != ',' && c != '.' && c != '!' && c != '?') {
                isInvalid = true;
            }

            if (c != ' ' && lastSymbolWasNonAlpha && data[i - 1] != ' ') {
                isInvalid = true;
            }

            lastSymbolWasNonAlpha = (c != ' ');
        }
    }

    if (!currentWord.empty()) {
        if (uniqueWords.insert(currentWord).second) {
            if (!result.empty()) {
                result += " ";
            }
            result += currentWord;
        }
        hasValidWords = true;
    }

    if (isInvalid || !hasValidWords) {
        return "Invalid input: non-alphabetic characters or invalid format";
    }

    return result.empty() ? "Invalid input: no valid words" : result;
}

void DataProcessor::run() {
    std::cout << "Data Processor started." << std::endl;
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

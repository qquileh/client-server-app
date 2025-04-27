#include "../include/DataProcessorUtils.h"
#include <string>
#include <unordered_set>


std::string DataProcessorUtils::processData(const std::string& data) {
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

#include "TokenParser.h"

void TokenParser::parse(const std::string& sourceString) {
    if (sourceString.length() == 0)
        return;
    if (startCallback != nullptr)
        startCallback();
    std::string token;
    for (size_t i = 0; i < sourceString.length(); i++) {
        // если встретились эти символы, то токен заканчился
        if (sourceString[i] == ' ' || sourceString[i] == '\t' || 
            sourceString[i] == '\n') {
                if (token.length() == 0)
                    continue;
                bool isDigit = true;
                // проверка что токен является числом
                for (size_t j = 0; j < token.length(); j++) {
                    if (!std::isdigit(token[j]))
                        isDigit = false;
                }
                // проверка что число помещается в uint64_t
                std::string uint64MaxValue = std::to_string(UINT64_MAX);
                if (token.length() > uint64MaxValue.length())
                    isDigit = false;
                if (token.length() == uint64MaxValue.length() && token > uint64MaxValue)
                    isDigit = false;
                if (isDigit) {
                    if (digitTokenCallback != nullptr) {
                        digitTokenCallback(std::stoull(token));
                    }
                    token = "";
                    continue;
                }
                if (stringTokenCallback != nullptr)
                    stringTokenCallback(token);
                token = "";
            } else {
                token.push_back(sourceString[i]);
            }
    }
    // обработка последнего токена
    if (token.length() != 0) {
        bool isDigit = true;
        // проверка что токен является числом
        for (size_t j = 0; j < token.length(); j++) {
            if (!std::isdigit(token[j])) {
                isDigit = false;
            }
        }
        // проверка что число помещается в uint64_t
        std::string uint64MaxValue = std::to_string(UINT64_MAX);
        if (token.length() > uint64MaxValue.length())
            isDigit = false;
        if (token.length() == uint64MaxValue.length() && token > uint64MaxValue)
            isDigit = false;
        if (isDigit) {
            if (digitTokenCallback != nullptr)
                digitTokenCallback(std::stoull(token));
        } else {
        if (stringTokenCallback != nullptr)
            stringTokenCallback(token);
        }
    }
    if (endCallback != nullptr)
        endCallback();
}

void TokenParser::setDigitTokenCallback(std::function<void(uint64_t)> callbackFunction) {
    digitTokenCallback = callbackFunction;
}

void TokenParser::setStringTokenCallback(std::function<void(std::string)> callbackFunction) {
    stringTokenCallback = callbackFunction;
}

void TokenParser::setStartCallback(std::function<void()> callbackFunction) {
    startCallback = callbackFunction;
}

void TokenParser::setEndCallback(std::function<void()> callbackFunction) {
    endCallback = callbackFunction;
}

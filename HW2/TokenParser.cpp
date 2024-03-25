#include "TokenParser.h"

#include <sstream>

void TokenParser::parse(const std::string& sourceString) {
    if (sourceString.length() == 0)
        return;
    if (startCallback != nullptr)
        startCallback();

    std::stringstream stream(sourceString);
    std::string token;
    while (stream >> token) {
        bool isDigit = true;
        // проверка что токен является числом
        for (size_t j = 0; j < token.length(); j++) {
            if (!std::isdigit(token[j]))
                isDigit = false;
        }

        if (isDigit) {
            try {
                uint64_t temp = std::stoull(token);
                if (digitTokenCallback != nullptr)
                    digitTokenCallback(temp);
            } catch(std::out_of_range& error) {
                isDigit = false;
            }
        }
        if (!isDigit && stringTokenCallback != nullptr)
            stringTokenCallback(token);
        token = "";
    }
    if (endCallback != nullptr)
            endCallback();
}

void TokenParser::setDigitTokenCallback(std::function<void(uint64_t)> callbackFunction) {
    digitTokenCallback = callbackFunction;
}

void TokenParser::setStringTokenCallback(std::function<void(const std::string&)> callbackFunction) {
    stringTokenCallback = callbackFunction;
}

void TokenParser::setStartCallback(std::function<void()> callbackFunction) {
    startCallback = callbackFunction;
}

void TokenParser::setEndCallback(std::function<void()> callbackFunction) {
    endCallback = callbackFunction;
}

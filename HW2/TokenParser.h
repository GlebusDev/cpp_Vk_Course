#pragma once

#include <string>

#include <functional>

class TokenParser {
public:
    TokenParser() = default;

    // Устанавливаем callback-функцию перед стартом парсинга.
    void setStartCallback(std::function<void()> callbackFunction);

    // Устанавливаем callback-функцию после окончания парсинга.
    void setEndCallback(std::function<void()> callbackFunction);

    // Устанавливаем callback-функцию для обработки чисел.
    void setDigitTokenCallback(std::function<void(uint64_t)> callbackFunction);

    void setStringTokenCallback(std::function<void(const std::string&)> callbackFunction);

    void parse(const std::string &);
private:
    std::function<void()> startCallback;
    std::function<void()> endCallback;
    std::function<void(uint64_t)> digitTokenCallback;
    std::function<void(const std::string&)> stringTokenCallback;
};

#include <gtest/gtest.h>

#include <iostream>

#include <string>

#include "TokenParser.h"

// тест проверяет работу setStartCallback
TEST(TOKEN_PARSER_TESTS, startCallbackTest) {
    static int callbackCounter = 0;
    std::function<void()> callback = [](){
        callbackCounter++;
    };
    TokenParser parser;
    parser.setStartCallback(callback);
    std::string s1 = "357743 fdfdfe 3242";
    std::string s2 ="2355fds";
    parser.parse(s1);
    parser.parse(s2);
    ASSERT_EQ(callbackCounter, 2);
}

// тест проверяет работу setEndCallback
TEST(TOKEN_PARSER_TESTS, endCallbackTest) {
    static int callbackCounter = 0;
    std::function<void()> callback = [](){
        callbackCounter++;
    };
    TokenParser parser;
    parser.setEndCallback(callback);
    std::string s1 = "357743 fdfdfe 3242";
    std::string s2 ="2355fds";
    parser.parse(s1);
    parser.parse(s2);
    ASSERT_EQ(callbackCounter, 2);
}

// тест проверяет распознавание числовых токенов setDigitTokenCallback
TEST(TOKEN_PARSER_TESTS, digitTokenTest) {
    static int callbackCounter = 0;
    std::function<void(uint64_t)> callback = [](uint64_t){
        callbackCounter++;
    };
    TokenParser parser;
    parser.setDigitTokenCallback(callback);
    std::string s1 = "357743 fdfdfe 3242";
    std::string s2 ="2355fds";
    // токен слишком большой
    std::string s3 ="1111111111111111111111111111111111111111111111111111";
    parser.parse(s1);
    parser.parse(s2);
    parser.parse(s3);
    ASSERT_EQ(callbackCounter, 2);
}

// тест проверяет передачу токена в digitTokenCallback
TEST(TOKEN_PARSER_TESTS, digitValueTest) {
    static uint64_t token = 0;
    std::function<void(uint64_t)> callback = [](uint64_t digitToken){
        token = digitToken;
    };
    TokenParser parser;
    parser.setDigitTokenCallback(callback);
    std::string s1 = "357743 fdfdfe";
    parser.parse(s1);
    ASSERT_EQ(token, 357743);
}

// тест проверяет передачу токена в stringTokenCallback
TEST(TOKEN_PARSER_TESTS, stringValueTest) {
    static std::string token;
    std::function<void(const std::string&)> stringCallback = [](const std::string& s){
        token = s;
    };
    TokenParser parser;
    parser.setStringTokenCallback(stringCallback);
    std::string s1 = "357743 abcde34-";
    parser.parse(s1);
    ASSERT_EQ(token, "abcde34-");
}

// тест проверяет работу парсера без назначенных callback функций
TEST(TOKEN_PARSER_TESTS, withoutCallbackTest) {
    TokenParser parser;
    std::string s1 = "357743 fdfdfe 3242";
    parser.parse(s1);
}

// тест проверяет распознавание различных разделителей
TEST(TOKEN_PARSER_TESTS, separatorTest) {
    static int digitCallbackCounter = 0;
    static int stringCallbackCounter = 0;
    std::function<void(uint64_t)> digitCallback = [](uint64_t){
        digitCallbackCounter++;
    };
    std::function<void(const std::string&)> stringCallback = [](const std::string&){
        stringCallbackCounter++;
    };
    TokenParser parser;
    parser.setDigitTokenCallback(digitCallback);
    parser.setStringTokenCallback(stringCallback);
    std::string s1 = " 357743 fdfdfe   3242\t2390\n\nstringggg\t\t";
    parser.parse(s1);
    ASSERT_EQ(digitCallbackCounter, 3);
    ASSERT_EQ(stringCallbackCounter, 2);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

#include <gtest/gtest.h>

#include "Format.h"

struct A {
        A(int a) {
            this->a = a;
        }
        int a;
};

std::ostream& operator<<(std::ostream& stream, const A& a) {
            stream << a.a;
            return stream;
}

// тест из github
TEST(FORMAT_TESTS, work_test) {
    std::string text = format("{1}+{1} = {0}", 2, "one");
    ASSERT_EQ(text, "one+one = 2");
}

// тест проверяет, что функция поддерживает любые типы данных, которые можно вывести в поток
TEST(FORMAT_TESTS, concept_test) {

    std::string text = format("{1} + {1} = {0}", A(6), 3);
    ASSERT_EQ(text, "3 + 3 = 6");
}

// тест проверяет выброс исключения при неверном синтаксисе
TEST(FORMAT_TESTS, syntax_exception_test) {
    ASSERT_THROW(format("{1}}}+{1} = {0}", 2, "one"), Error::SyntaxError);
}

// тест проверяет выброс исключения при неверном количестве аргументов
TEST(FORMAT_TESTS, argumentCount_exception_test) {
    ASSERT_THROW(format("{1}+{1} = {0}", 2), Error::ArgumentCountError);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

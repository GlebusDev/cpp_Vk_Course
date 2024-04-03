#include <gtest/gtest.h>

#include "BigInt.h"

// тест проверяет работу конструктора
TEST(BIGINT_TESTS, constructorTest) {
    BigInt num ("1234567");
    BigInt num2;
    ASSERT_EQ(num.getString(), "1234567");
    ASSERT_EQ(num2.getString(), "0");
}

// тест проверяет работу конструктора копирования
TEST(BIGINT_TESTS, constructorCopyTest) {
    BigInt num ("1234567");
    BigInt num2(num);
    ASSERT_EQ(num, num2);
}

// тест проверяет работу конструктора перемещения
TEST(BIGINT_TESTS, constructorMoveTest) {
    BigInt num ("1234567");
    BigInt num2 = std::move(num);
    ASSERT_EQ(num2.getString(), "1234567");
}

// тест проверяет работу оператора копирования
TEST(BIGINT_TESTS, opearatorCopyTest) {
    BigInt num ("1234567");
    BigInt num2("993");
    num2 = num;
    ASSERT_EQ(num2, num);
}

// тест проверяет работу оператора перемещения
TEST(BIGINT_TESTS, opearatorMoveTest) {
    BigInt num ("1234567");
    BigInt num2("993");
    num2 = std::move(num);
    ASSERT_EQ(num2.getString(), "1234567");
}

// тест проверяет работу оператора больше
TEST(BIGINT_TESTS, compareBiggerTest) {
    BigInt num ("1234567");
    BigInt num2("993");
    ASSERT_EQ(num2 > num, false);
    ASSERT_EQ(num > num2, true);
}

// тест проверяет работу оператора меньше
TEST(BIGINT_TESTS, compareLowerTest) {
    BigInt num ("1234567");
    BigInt num2("993");
    ASSERT_EQ(num2 < num, true);
    ASSERT_EQ(num < num2, false);
}

// тест проверяет работу оператора равенства
TEST(BIGINT_TESTS, equalityTest) {
    BigInt num ("1234567");
    BigInt num2("993");
    BigInt num3("993");
    ASSERT_EQ(num2 == num, false);
    ASSERT_EQ(num3 == num2, true);
}

// тест проверяет работу оператора не равно
TEST(BIGINT_TESTS, compareNETest) {
    BigInt num ("1234567");
    BigInt num2("993");
    BigInt num3("993");
    ASSERT_EQ(num != num2, true);
    ASSERT_EQ(num2 != num3, false);
}

// тест проверяет работу оператора больше или равно
TEST(BIGINT_TESTS, compareBEQTest) {
    BigInt num ("1234567");
    BigInt num2("993");
    BigInt num3("993");
    ASSERT_EQ(num >= num2, true);
    ASSERT_EQ(num2 >= num3, true);
    ASSERT_EQ(num3 >= num2, true);
    ASSERT_EQ(num2 >= num, false);
}

// тест проверяет работу оператора меньше или равно
TEST(BIGINT_TESTS, compareLEQTest) {
    BigInt num ("1234567");
    BigInt num2("993");
    BigInt num3("993");
    ASSERT_EQ(num <= num2, false);
    ASSERT_EQ(num2 <= num3, true);
    ASSERT_EQ(num3 <= num2, true);
    ASSERT_EQ(num2 <= num, true);
}

// тест проверяет работу оператора сложения двух BigInt
TEST(BIGINT_TESTS, addBITest) {
    BigInt num ("123456789345");
    BigInt num2("993");
    BigInt num3(std::to_string(123456789345 + 993));
    ASSERT_EQ(num + num2, num3);
}

// тест проверяет работу оператора сложения BigInt и int32_t
TEST(BIGINT_TESTS, addI32Test) {
    BigInt num ("123456789345");
    int32_t num2 = 993;
    BigInt num3(std::to_string(123456789345 + 993));
    ASSERT_EQ(num + num2, num3);
}

// тест проверяет работу оператора вычитания двух BigInt
TEST(BIGINT_TESTS, subBITest) {

    BigInt num ("123456789345");
    BigInt num2("993");
    BigInt num3(std::to_string(123456789345 - 993));
    ASSERT_EQ(num - num2, num3);
}

// тест проверяет работу оператора вычитания int32_t из BigInt
TEST(BIGINT_TESTS, subI32Test) {

    BigInt num ("123456789345");
    int32_t num2  = 993;
    BigInt num3(std::to_string(123456789345 - 993));
    ASSERT_EQ(num - num2, num3);
}

// тест проверяет работу оператора умножения двух BigInt
TEST(BIGINT_TESTS, multBITest) {
    BigInt num ("123456789345");
    BigInt num2("993");
    BigInt num3(std::to_string(123456789345ll * 993));
    ASSERT_EQ(num * num2, num3);
}

// тест проверяет работу оператора умножения int32_t и BigInt
TEST(BIGINT_TESTS, multI32Test) {
    BigInt num ("123456789345");
    int32_t num2 = 993;
    BigInt num3(std::to_string(123456789345ll * 993));
    ASSERT_EQ(num * num2, num3);
}

// тест проверяет работу оператора унарного минуса
TEST(BIGINT_TESTS, minusTest) {
    BigInt num ("123456789345");
    BigInt num2 ("-123456789345");
    ASSERT_EQ(-num, num2);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

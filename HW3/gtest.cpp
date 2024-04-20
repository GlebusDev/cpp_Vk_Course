#include <gtest/gtest.h>

#include "Matrix.h"

#include <sstream>

// тест проверяет работу конструктора и геттеров
TEST(MATRIX_TESTS, constructorTest) {
    Matrix m(5,3);
    ASSERT_EQ(m.getColNum(), 5);
    ASSERT_EQ(m.getRowNum(), 3);
}

// тест проверяет возможность доступа к элементу матрицы
TEST(MATRIX_TESTS, accessTest) {
    Matrix m(5, 3);
    m[0][2] = 99;
    ASSERT_EQ(m[0][2], 99); 
}

// тест проверяет, что при выходе за границы матрицы, выбрасывается исключение
TEST(MATRIX_TESTS, accessExceptionTest) {
    Matrix m(5, 3);
    try {
        m[0][3] = 99;
    } catch (const std::out_of_range& e) {}
}

// тест проверяет умножение матрицы на число
TEST(MATRIX_TESTS, multTest) {
    Matrix m(5, 3);
    m[1][2] = 3;
    m *= 7;
    ASSERT_EQ(m[1][2], 21);
}

// тест проверяет работу оператора сравнения
TEST(MATRIX_TESTS, equalTest) {
    Matrix m1(5, 3);
    Matrix m2(5, 3);
    ASSERT_EQ(m1, m2);
}

// тест проверяет работу оператора сложения
TEST(MATRIX_TESTS, addTest) {
    Matrix m1(5, 3);
    Matrix m2(5, 3);
    m1[3][2] = 3;
    m2[3][2] = 5;
    auto m3 = m1 + m2;
    Matrix m4(5, 3);
    m4[3][2] = 8;
    ASSERT_EQ(m4, m3);
}

// тест проверяет возможность вывода матрицы в поток
TEST(MATRIX_TESTS, ostreamTest) {
    Matrix m1 (2, 3);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[0][2] = 3;
    m1[1][0] = 4;
    m1[1][1] = 5;
    m1[1][2] = 6;
    
    std::stringstream s;
    s << m1;
    std::string out = "1 2 3 \n4 5 6 \n";
    ASSERT_EQ(s.str(),out);
}

// тест проверяет работу оператора присваивания
TEST(MATRIX_TESTS, assignTest) {
    Matrix m1 (2, 5);
    Matrix m2 (2, 3);
    m1[0][1] = 5;
    m2[0][1] = 9;
    m1 = m2;
    ASSERT_EQ(m1[0][1], 9);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

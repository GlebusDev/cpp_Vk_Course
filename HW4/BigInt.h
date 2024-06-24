#pragma once

#include <cstdint>

#include <cstddef>

#include <string>

#include <iostream>

class BigInt {
public:
    BigInt();
    explicit BigInt(const std::string& s);
    BigInt(const BigInt& num2);
    BigInt(BigInt&& num2);
    BigInt& operator=(const BigInt& num2);
    BigInt& operator=(BigInt&& num2);
    ~BigInt();
    
    BigInt operator+(const BigInt& num2) const;
    BigInt operator+(int32_t num2) const;
    BigInt operator-(const BigInt& num2) const;
    BigInt operator-(int32_t num2) const;
    BigInt operator*(BigInt num2) const;
    BigInt operator*(int32_t num2) const;
    BigInt operator-() const;

    bool operator>(const BigInt& num2) const;
    bool operator<(const BigInt& num2) const;
    bool operator==(const BigInt& num2) const;
    bool operator>=(const BigInt& num2) const;
    bool operator<=(const BigInt& num2) const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& num);
    std::string getString() const;
private:
// знак числа: 
// false - положительное
// true - отрицательное
bool sign;
// массив из чисел размером до 999999999
uint32_t *data;
// размер массива data
size_t length;
};


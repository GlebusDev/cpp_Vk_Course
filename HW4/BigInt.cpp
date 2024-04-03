#include "BigInt.h"

#include <cmath>

#include <algorithm>

BigInt::BigInt() {
    sign = false;
    length = 1;
    data = new uint32_t[1];
    data[0] = 0;
}

BigInt::BigInt(const std::string& s) {
    size_t slen = s.length();
    if (s[0] == '-') {
        sign = true;    
        slen--;
    } else {
        sign = false;
    }

    if (slen % 9 == 0)
        length = slen / 9;
    else
        length = slen / 9 + 1;

    data = new uint32_t[length];

    int64_t index = s.length() - 1;
    for (size_t i = 0; i < length; i++) {
        data[i] = 0;
        int left = -1;
        if (sign)
            left = 0;
        for (size_t j = 0; j < 9 && index != left; j++, index--) {
            data[i] += std::pow(10, j) * static_cast<uint32_t>(s[index]-'0');
        }
    }
}

BigInt::~BigInt() {
    delete[] data;
}

BigInt::BigInt(const BigInt& num) {
    length = num.length;
    sign = num.sign;
    data = new uint32_t[length];
    for (size_t i = 0; i < length; i++) {
        data[i] = num.data[i];
    }
}

BigInt& BigInt::operator=(const BigInt& num) {
    if (this == &num)
        return *this;
    length = num.length;
    sign = num.sign;
    delete[] data;
    data = new uint32_t[length];
    for (size_t i = 0; i < length; i++) {
        data[i] = num.data[i];
    }
    return *this;
}

BigInt::BigInt(BigInt&& num) {
    length = num.length;
    sign = num.sign;
    data = num.data;
    num.data = nullptr;
    num.length = 0;
    num.sign = false;
}

BigInt& BigInt::operator=(BigInt&& num2) {
    length = num2.length;
    sign = num2.sign;
    delete[] data;
    data = num2.data;
    num2.data = nullptr;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const BigInt& num) {
    if (num.sign)
        os << "-";
    for (int64_t i = num.length - 1; i >= 0; i--) {
        os << num.data[i];
    }
    os << std::endl;
    return os;
}

bool BigInt::operator==(const BigInt& num2) const {
    if (sign != num2.sign)
        return false;
    if (length != num2.length)
        return false;
    for (size_t i = 0; i < length; i++) {
        if (data[i] != num2.data[i])
            return false;
    }
    return true;
}

bool BigInt::operator>(const BigInt& num2) const {
    if (sign != num2.sign)
        return !sign;
    if (length != num2.length) {
        if (length > num2.length)
            return true;
        return false;
    }
    for (int64_t i = length - 1; i >= 0; i--) {
        if (data[i] != num2.data[i]) {
            if (data[i] > num2.data[i])
                return true;
            return false;
        } 
    }
    return false;
}

bool BigInt::operator<(const BigInt& num2) const {
    return (num2 > *this && num2 != *this);
}

bool BigInt::operator>=(const BigInt& num2) const {
    return (*this > num2 || *this == num2);
}

bool BigInt::operator<=(const BigInt& num2) const {
    return (*this < num2 || *this == num2);
}

BigInt BigInt::operator-() const {
    BigInt num = *this;
    num.sign = !sign;
    return num;
}

BigInt BigInt::operator+(const BigInt& num2) const {
    BigInt num3;
    if (sign == num2.sign) {
        num3.sign = sign;
        num3.length = std::max(length, num2.length) + 1;
        delete[] num3.data;
        num3.data = new uint32_t[num3.length];
        bool wasOverflow = false;
        for (size_t i = 0; i < num3.length - 1 && i < std::min(length, num2.length); i++) {
            uint32_t temp = data[i] + num2.data[i];
            if (wasOverflow) {
                temp++;
                wasOverflow = false;
            }
            if (temp > 999999999) {
                temp -= 1000000000;
                wasOverflow = true;
            }
            num3.data[i] = temp;
        }
        if (std::min(length, num2.length) != num3.length - 1) {
            if (length >= num2.length) {
                for (size_t i = num2.length; i < length; i++) {
                    num3.data[i] = data[i];
                }
                if (wasOverflow)
                    num3.data[num2.length]++;
            } else {
                for (size_t i = length; i < num2.length; i++) {
                    num3.data[i] = num2.data[i];
                }
                if (wasOverflow)
                    num3.data[length]++;
            }
        } else {
            if (wasOverflow)
                num3.data[num3.length - 1] = 1;
            else
                num3.length--;
        }
        while (num3.data[num3.length - 1] == 0 && num3.length != 0)
            num3.length--;
          
    } else {
        BigInt abs1, abs2;
        
        if (sign) 
            abs1 = -(*this);
        else
            abs1 = *this;
        
        if (num2.sign) 
            abs2 = -num2;
        else
            abs2 = num2;

        BigInt* max,* min;
        if (abs1 > abs2) {
            max = &abs1;
            max->sign = sign;
            min = &abs2;
        }   
        else {
            max = &abs2;
            max->sign = num2.sign;
            min = &abs1;
        }
        
        BigInt temp = *max;
        
        for (size_t i = 0; i < min->length; i++) {
            if (temp.data[i] < min->data[i]) {
                size_t j = i + 1;
                while (temp.data[j] == 0) {
                    temp.data[j] = 999999999;
                    j++;
                }
                temp.data[j]--;
                temp.data[i] = 1000000000 + temp.data[i] - min->data[i];
            } else {
                temp.data[i] -= min->data[i];
            }
        }
        while (temp.data[temp.length - 1] == 0 && temp.length != 0)
            temp.length--;
        if (temp.length == 0)
            return BigInt();
        num3 = temp;
        
    }
    return BigInt(num3);
}

BigInt BigInt::operator-(const BigInt& num2) const {
    return *this + (-num2);
}

BigInt BigInt::operator+(int32_t num2) const {
    return *this + BigInt(std::to_string(num2));
}

BigInt BigInt::operator-(int32_t num2) const {
    return *this + BigInt(std::to_string(-num2));
}

BigInt BigInt::operator*(BigInt num2) const {
    BigInt mult("0");
    bool s = num2.sign;
    if (s)
        num2.sign = false;
    while (num2 > BigInt("0")) {
        mult = mult + *this;
        num2  = num2 - 1;
    }
    if (s)
        mult.sign = true;
    return mult;
}

BigInt BigInt::operator*(int32_t num2) const {
    return (*this) * BigInt(std::to_string(num2));
}

std::string BigInt::getString() const {
    std::string s = "";
    if (sign)
        s.append("-");
    for (int64_t i = length - 1; i >= 0; i--)
        s.append(std::to_string(data[i]));
    return s;
}

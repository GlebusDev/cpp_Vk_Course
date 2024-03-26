#pragma once

#include <cstddef>

#include <cstdint>

#include <iostream>

class Matrix {
private:

    struct Row {
        size_t length;
        int32_t * data;
        Row() = default;
        int32_t& operator[](size_t n) const;
        ~Row() {delete[] data;} 
    };

    Row* rows;
    size_t colNum, rowNum;

public:
    Matrix() = delete;
    Matrix(size_t col, size_t row);
    ~Matrix();
    Matrix(const Matrix& m2);
    Matrix& operator=(const Matrix& m2);
    size_t getColNum() const {return colNum;}
    size_t getRowNum() const {return rowNum;}
    Row& operator[](size_t index) const;
    Matrix& operator*=(int32_t mult);
    Matrix operator+(const Matrix& m2);
    bool operator==(const Matrix& m2) const;
};

std::ostream& operator<<(std::ostream& os, const Matrix& m);

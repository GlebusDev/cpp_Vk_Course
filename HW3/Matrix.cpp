#include <stdexcept>

#include "Matrix.h"

Matrix::Matrix(size_t col, size_t row) {
    colNum = col;
    rowNum = row;
    rows = new Row[col];
    for(size_t i = 0; i < col; i++) {
        rows[i].data = new int32_t[row];
        rows[i].length = row;
        for(size_t j = 0; j < row; j++)
            rows[i][j] = 0;
    }
}

Matrix::~Matrix() {
    delete[] rows;
}

int32_t& Matrix::Row::operator[] (size_t n) const {
    if (n>=length)
        throw std::out_of_range("");
    return data[n];
}

Matrix::Row& Matrix::operator[] (size_t index) const {
    if (index >= colNum)
        throw std::out_of_range("");
    return rows[index];
}

Matrix& Matrix::operator*= (int32_t mult) {
    for (size_t i = 0; i < colNum; i++) {
        for (size_t j = 0; j < rowNum; j++)
            (*this)[i][j] *= mult;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (size_t i = 0; i < m.getColNum(); i++) {
        for (size_t j = 0; j < m.getRowNum(); j++) 
            os << m[i][j] << " ";
        os << std::endl;
    }
    return os;
}

Matrix Matrix::operator+(const Matrix& m2) {
    if (m2.getColNum() != colNum && m2.getRowNum() != rowNum)
        throw std::invalid_argument("Matrix dimensions do not match for addition");
    Matrix m3(m2.getColNum(), m2.getRowNum());
    for (size_t i = 0; i < colNum; i++) {
        for (size_t j =0; j < rowNum; j++) {
            m3[i][j] = (*this)[i][j] + m2[i][j];
        }
    }
    return m3;
}

bool Matrix::operator==(const Matrix& m2) const {
    if (m2.getColNum() != colNum && m2.getRowNum() != rowNum)
        throw std::invalid_argument("Matrix dimensions do not match for comparison");
    for (size_t i = 0; i < colNum; i++) {
        for (size_t j =0; j < rowNum; j++) {
            if ((*this)[i][j] != m2[i][j])
                return false;
        }
    }
    return true;
}

Matrix::Matrix(const Matrix& m2) {
    colNum = m2.getColNum();
    rowNum = m2.getRowNum();
    rows = new Row[colNum];
    for(size_t i = 0; i < colNum; i++) {
        rows[i].data = new int32_t[rowNum];
        rows[i].length = rowNum;
        for(size_t j = 0; j < rowNum; j++)
            rows[i][j] = m2[i][j];
    }
}

Matrix& Matrix::operator=(const Matrix& m2) {
    if (this == &m2)
        return *this;
    delete[] rows;
    colNum = m2.getColNum();
    rowNum = m2.getRowNum();
    rows = new Row[colNum];
    for(size_t i = 0; i < colNum; i++) {
        rows[i].data = new int32_t[rowNum];
        rows[i].length = rowNum;
        for(size_t j = 0; j < rowNum; j++)
            rows[i][j] = m2[i][j];
    }
    return *this;
}

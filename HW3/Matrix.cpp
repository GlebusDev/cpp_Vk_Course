#include "Matrix.h"

Matrix::Matrix(size_t col, size_t row) {
    rows = new Row*[col];
    for(size_t i = 0; i < col; i++) {
        rows[i] = new Row(row);
    }
}

Matrix::~Matrix()
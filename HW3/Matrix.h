class Matrix {
public:
    Matrix() = delete;
    Matrix(size_t col, size_t row);
    ~Matrix();
private:
    class Row {
    private:
        int32_t* data;
    public:
        Row() = delete;
        Row(size_t len) {data = new int32_t[len]};
        int32_t operator[](size_t n) const;
        ~Row() {delete[] data}; 
    };
    Row** rows;
};
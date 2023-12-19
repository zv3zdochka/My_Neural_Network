#pragma once

#include <vector>

class Matrix {
private:
    std::vector<std::vector<float>> data;
    size_t rows;
    size_t cols;

public:

    Matrix();

    Matrix(size_t rows, size_t cols);

    explicit Matrix(const std::vector<std::vector<float>> &values);


    ~Matrix();


    [[nodiscard]] size_t getRows() const;

    [[nodiscard]] size_t getCols() const;

    void resize(size_t rows, size_t gor);

    std::vector<float> &operator[](size_t index);

    const std::vector<float> &operator[](size_t index) const;


    [[nodiscard]] Matrix transpose() const;


    Matrix operator+(const Matrix &other) const;

    Matrix operator-(const Matrix &other) const;

    Matrix operator*(const Matrix &other) const;

    bool operator==(const Matrix &other) const;

    bool operator!=(const Matrix &other) const;

    std::vector<std::vector<float>> getData();

    void showMatrix();
};


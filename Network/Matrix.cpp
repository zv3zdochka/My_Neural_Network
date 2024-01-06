#include "Matrix.h"
#include <iomanip>

Matrix::Matrix() : rows(0), cols(0) {}

Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    data.resize(rows, std::vector<float>(cols, 0.0f));
}

Matrix::Matrix(const std::vector<std::vector<float>> &values) {
    rows = values.size();
    cols = values[0].size();
    data = values;
}

Matrix::~Matrix() = default;

size_t Matrix::getRows() const {
    return rows;
}

size_t Matrix::getCols() const {
    return cols;
}

void Matrix::resize(size_t vert, size_t gor) {
    this->rows = vert;
    this->cols = gor;
    data.resize(vert, std::vector<float>(gor, 0.0f));
}

std::vector<float> &Matrix::operator[](size_t index) {
    return data[index];
}

const std::vector<float> &Matrix::operator[](size_t index) const {
    return data[index];
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[j][i] = data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const {
    if (cols != other.getRows()) {
        throw std::invalid_argument("Matrix multiplication not possible due to incompatible sizes.");
    }
    Matrix result(rows, other.getCols());
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < other.getCols(); ++j) {
            float sum = 0.0f;
            for (size_t k = 0; k < cols; ++k) {
                sum += data[i][k] * other[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix &other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix addition not possible due to incompatible sizes.");

    }

    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = data[i][j] + other[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix subtraction not possible due to incompatible sizes.");

    }

    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = data[i][j] - other[i][j];
        }
    }
    return result;
}

bool Matrix::operator==(const Matrix &other) const {
    if (rows != other.rows || cols != other.cols) {
        return false;
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &other) const {
    return !(*this == other);
}

std::vector<std::vector<float>> Matrix::getData() {
    return data;
}

void Matrix::showMatrix(const std::string &name) {
    std::cout << "Result Matrix " << name << ": " << std::endl;
    std::cout << "-----------------------" << std::endl;
    for (auto &i: data) {
        for (float j: i) {
            std::cout << j << std::setprecision(10) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
}

Matrix Matrix::calculate_errors() {
    std::vector<float> summa = {};

    std::vector<std::vector<float>> matr = this->getData();
    for (int i = 0; i < data.size(); i++) {
        float mi_s = 0.0f;
        for (int j = 0; j < data[i].size(); j++)
            mi_s += matr[i][j];
        summa.push_back(mi_s);
    }
    Matrix transposed = this->transpose();

    std::vector<std::vector<float>> error_matrix = {};

    for (int i = 0; i < data.size(); i++) {
        std::vector<float> semi_data = {};
        for (int j = 0; j < data[i].size(); j++) {
            semi_data.push_back(data[i][j] / summa[i]);
        }
        error_matrix.push_back(semi_data);
    }
    return Matrix(error_matrix).transpose();
}



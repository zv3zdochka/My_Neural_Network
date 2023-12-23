#include "Matrix.h"

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
    if (cols == other.getRows()) {
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

    std::cout << "Unable to perform matrix multiplication due to incompatible sizes." << std::endl;

    return {};

}

Matrix Matrix::operator+(const Matrix &other) const {
    if (rows != other.rows || cols != other.cols) {
        std::cout << "Unable to perform matrix multiplication due to incompatible sizes." << std::endl;
        return {};
    }

    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = data[i][j] + other[i][j];
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

void Matrix::showMatrix(const std::string& name) {
    std::cout << "Result Matrix " << name << ": " << std::endl;
    std::cout << "-----------------------" << std::endl;
    for (auto & i : data){
        for (float j : i){
            std::cout << j << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------" << std::endl;

}








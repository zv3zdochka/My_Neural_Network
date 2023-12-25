#pragma once

/**
 * @file Matrix.h
 * @brief Header file containing the Matrix class for matrix operations.
 */

#include <vector>
#include <string>
#include <iostream>

/**
 * @class Matrix
 * @brief Represents a matrix and provides basic matrix operations.
 */
class Matrix {
private:
    std::vector<std::vector<float>> data; ///< Matrix data
    size_t rows; ///< Number of rows in the matrix
    size_t cols; ///< Number of columns in the matrix

public:
    /**
     * @brief Default constructor.
     */
    Matrix();

    /**
     * @brief Parameterized constructor.
     * @param rows Number of rows.
     * @param cols Number of columns.
     */
    Matrix(size_t rows, size_t cols);

    /**
     * @brief Parameterized constructor with initial values.
     * @param values Initial values for the matrix.
     */
    explicit Matrix(const std::vector<std::vector<float>> &values);

    /**
     * @brief Destructor.
     */
    ~Matrix();

    /**
     * @brief Get the number of rows in the matrix.
     * @return Number of rows.
     */
    [[nodiscard]] size_t getRows() const;

    /**
     * @brief Get the number of columns in the matrix.
     * @return Number of columns.
     */
    [[nodiscard]] size_t getCols() const;

    /**
     * @brief Resize the matrix to the specified dimensions.
     * @param rows New number of rows.
     * @param cols New number of columns.
     */
    void resize(size_t rows, size_t cols);

    /**
     * @brief Access a row of the matrix.
     * @param index Row index.
     * @return Reference to the row.
     */
    std::vector<float> &operator[](size_t index);

    /**
     * @brief Access a row of the matrix (const version).
     * @param index Row index.
     * @return Const reference to the row.
     */
    const std::vector<float> &operator[](size_t index) const;

    /**
     * @brief Transpose the matrix.
     * @return Transposed matrix.
     */
    [[nodiscard]] Matrix transpose() const;

    /**
     * @brief Perform matrix addition.
     * @param other Matrix to be added.
     * @return Resulting matrix.
     */
    Matrix operator+(const Matrix &other) const;

    /**
     * @brief Perform matrix subtraction.
     * @param other Matrix to be subtracted.
     * @return Resulting matrix.
     */
    Matrix operator-(const Matrix &other) const;

    /**
     * @brief Perform matrix multiplication.
     * @param other Matrix to be multiplied.
     * @return Resulting matrix.
     */
    Matrix operator*(const Matrix &other) const;

    /**
     * @brief Check if two matrices are equal.
     * @param other Matrix to compare.
     * @return True if equal, false otherwise.
     */
    bool operator==(const Matrix &other) const;

    /**
     * @brief Check if two matrices are not equal.
     * @param other Matrix to compare.
     * @return True if not equal, false otherwise.
     */
    bool operator!=(const Matrix &other) const;

    /**
     * @brief Get the raw data of the matrix.
     * @return Vector of vectors representing the matrix.
     */
    std::vector<std::vector<float>> getData();

    /**
     * @brief Display the matrix.
     * @param name Optional name to display.
     */
    void showMatrix(const std::string &name = "");
};

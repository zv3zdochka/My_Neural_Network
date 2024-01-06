#pragma once

#include <vector>
#include <string>
#include <iostream>

/**
 * @brief The Matrix class represents a mathematical matrix and supports basic matrix operations.
 */
class Matrix {
private:
    std::vector<std::vector<float>> data; ///< 2D vector to store matrix elements
    size_t rows; ///< Number of rows in the matrix
    size_t cols; ///< Number of columns in the matrix

public:
    /**
     * @brief Default constructor. Constructs an empty matrix.
     */
    Matrix();

    /**
     * @brief Parameterized constructor. Constructs a matrix of specified dimensions initialized with zeros.
     * @param rows Number of rows in the matrix
     * @param cols Number of columns in the matrix
     */
    Matrix(size_t rows, size_t cols);

    /**
     * @brief Constructor that initializes the matrix with the provided 2D vector of values.
     * @param values 2D vector representing the matrix elements
     */
    explicit Matrix(const std::vector<std::vector<float>> &values);

    /**
     * @brief Destructor to release memory occupied by the matrix.
     */
    ~Matrix();

    /**
     * @brief Get the number of rows in the matrix.
     * @return Number of rows
     */
    [[nodiscard]] size_t getRows() const;

    /**
     * @brief Get the number of columns in the matrix.
     * @return Number of columns
     */
    [[nodiscard]] size_t getCols() const;

    /**
     * @brief Resize the matrix to the specified dimensions and initializes with zeros.
     * @param rows New number of rows
     * @param cols New number of columns
     */
    void resize(size_t rows, size_t cols);

    /**
     * @brief Overloaded operator to access and modify matrix elements.
     * @param index Row index
     * @return Reference to the vector representing a row in the matrix
     */
    std::vector<float> &operator[](size_t index);

    /**
     * @brief Overloaded operator to access matrix elements (const version).
     * @param index Row index
     * @return Const reference to the vector representing a row in the matrix
     */
    const std::vector<float> &operator[](size_t index) const;

    /**
     * @brief Calculate and return the transpose of the matrix.
     * @return Transpose of the matrix
     */
    [[nodiscard]] Matrix transpose() const;

        /**
     * @brief Computes the error in a neural network layer based on the sum of elements in the weight matrix.
     *
     * This function accepts the weight matrix of a neural network layer and calculates the error in the layer
     * based on the sum of all elements in the matrix. It does not perform division by zero.
     *
     * @return Matrix A matrix containing the calculated error values based on the sum of elements.
     */
    Matrix calculate_errors();

    /**
     * @brief Overloaded operator to perform matrix multiplication.
     * @param other Another matrix to multiply with
     * @return Result of matrix multiplication
     * @throw std::invalid_argument if the matrices' dimensions are incompatible for multiplication
     */
    Matrix operator*(const Matrix &other) const;

    /**
     * @brief Overloaded operator to perform matrix addition.
     * @param other Another matrix to add
     * @return Result of matrix addition
     * @throw std::invalid_argument if the matrices' dimensions are incompatible for addition
     */
    Matrix operator+(const Matrix &other) const;

    /**
     * @brief Overloaded operator to perform matrix subtraction.
     * @param other Another matrix to subtract
     * @return Result of matrix subtraction
     * @throw std::invalid_argument if the matrices' dimensions are incompatible for subtraction
     */
    Matrix operator-(const Matrix &other) const;

    /**
     * @brief Overloaded operator to check equality between two matrices.
     * @param other Another matrix for comparison
     * @return True if matrices are equal, False otherwise
     */
    bool operator==(const Matrix &other) const;

    /**
     * @brief Overloaded operator to check inequality between two matrices.
     * @param other Another matrix for comparison
     * @return True if matrices are not equal, False otherwise
     */
    bool operator!=(const Matrix &other) const;

    /**
     * @brief Get the matrix elements as a 2D vector.
     * @return 2D vector containing the matrix elements
     */
    std::vector<std::vector<float>> getData();

    /**
     * @brief Display the matrix elements in the console.
     * @param name Name to identify the matrix (optional)
     */
    void showMatrix(const std::string &name = "");



};


#pragma once

#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <numeric>
#include <iostream>
#include <random>
#include <sstream>
#include <iterator>
/**
 * @file DerivativeFunctions.h
 * @brief Header file containing functions to compute derivatives.
 */

namespace Derivatives {

    /**
     * @brief Computes the derivative of the sigmoid function.
     * @param x The value of the argument.
     * @return The value of the derivative at point x.
     */
    float sigmoid_derivative(float x);

    /**
     * @brief Computes the fast derivative of the sigmoid function.
     * @param x The value of the argument.
     * @return The value of the derivative at point x.
     */
    float fast_sigmoid_derivative(float x);

    /**
     * @brief Computes the derivative of the Silu (Sigmoid Linear Unit) function.
     * @param x The value of the argument.
     * @return The value of the derivative at point x.
     */
    float silu_derivative(float x);

    /**
     * @brief Computes the derivative of the hyperbolic tangent function.
     * @param x The value of the argument.
     * @return The value of the derivative at point x.
     */
    float tanh_derivative(float x);

}


class Data_Worker {
public:
    /**
     * @brief Read a dataset from a file.
     * @param filename Path to the dataset file.
     * @param input_data Vector to store input data.
     * @param output_data Vector to store output data.
     */
    static void readDataset(const std::string &filename, std::vector<std::vector<std::vector<float>>> &input_data,
                            std::vector<std::vector<float>> &output_data);

    /**
     * @brief Normalize a dataset.
     * @param input_data Input data to be normalized.
     * @param output_data Output data to be normalized.
     */
    static void normalize_dataset(std::vector<std::vector<std::vector<float>>> &input_data,
                                  std::vector<std::vector<float>> &output_data);

    /**
     * @brief Shuffle a dataset randomly.
     * @param input_data Input data to be shuffled.
     * @param output_data Output data to be shuffled.
     */
    static void shuffle_dataset(std::vector<std::vector<std::vector<float>>> &input_data,
                                std::vector<std::vector<float>> &output_data);

};
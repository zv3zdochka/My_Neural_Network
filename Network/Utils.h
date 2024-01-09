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
#include "Neurons.h"

/**
 * @file DerivativeFunctions.h
 * @brief Header file containing functions to compute derivatives and data normalization.
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

/**
 * @brief Enum representing the types of data normalization techniques available.
 */
enum class Normalisation {
    min_max_normalisation,       ///< Min-max normalization technique
    z_normalisation,             ///< Z-score normalization technique
    quantile_normalisation,      ///< Quantile normalization technique
    max_abs_normalisation,       ///< Max-abs normalization technique
    without_normalisation        ///< No normalization applied
};

/**
 * @brief Class containing methods for data processing and normalization.
 */
class Data_Worker {
public:

    /**
     * @brief Shuffles the input and output data randomly.
     *
     * @param input_d The input data to be shuffled.
     * @param out_d The output data to be shuffled.
     * @return A vector containing shuffled input and output data.
     */
    static std::vector<std::vector<std::vector<float>>>
    shuffle_data(std::vector<std::vector<float>> input_d, std::vector<std::vector<float>> out_d);

    /**
     * @brief Performs min-max normalization on the given data.
     *
     * @param data The data to be normalized using min-max normalization.
     * @return The normalized data.
     */
    static std::vector<std::vector<float>> min_max_normalisation(std::vector<std::vector<float>> data);

    /**
     * @brief Performs z-score normalization on the given data.
     *
     * @param data The data to be normalized using z-score normalization.
     * @return The normalized data.
     */
    static std::vector<std::vector<float>> zScoreNormalization(std::vector<std::vector<float>> data);

    /**
     * @brief Performs max-abs normalization on the given data.
     *
     * @param data The data to be normalized using max-abs normalization.
     * @return The normalized data.
     */
    static std::vector<std::vector<float>> maxAbsNormalization(std::vector<std::vector<float>> data);

    /**
     * @brief Performs quantile normalization on the given data.
     *
     * @param data The data to be normalized using quantile normalization.
     * @return The normalized data.
     */
    static std::vector<std::vector<float>> quantileNormalization(std::vector<std::vector<float>> data);

    /**
     * @brief Checks the consistency of the provided input and output data with the neural network architecture.
     *
     * @param input_data The input data.
     * @param output_data The output data.
     * @param net The neural network architecture.
     */
    static void check_data(std::vector<std::vector<float>> input_data,
                           std::vector<std::vector<float>> output_data,
                           std::vector<std::vector<Neuron>> net);

    /**
     * @brief Performs the specified normalization technique on input and output data.
     *
     * @param type The type of normalization technique to apply.
     * @param inp The input data to be normalized.
     * @param out The output data to be normalized.
     * @return The normalized input and output data.
     */
    static std::vector<std::vector<std::vector<float>>>
    call(Normalisation type, const std::vector<std::vector<float>> &inp, const std::vector<std::vector<float>> &out);

    /**
     * @brief Splits input and output data into training and testing sets based on the given coefficient.
     *
     * @param input_d The input data to be split.
     * @param out_d The output data to be split.
     * @param coe The coefficient determining the split ratio between training and testing data.
     * @return The split input and output data.
     */
    static std::vector<std::vector<std::vector<float>>>
    split_data(std::vector<std::vector<float>> input_d, std::vector<std::vector<float>> out_d, float coe);
};


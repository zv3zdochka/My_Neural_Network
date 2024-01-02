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
enum class Normalisation {
    min_max_normalisation,
    z_normalisation,
    quantile_normalisation,
    max_abs_normalisation,
    without_normalisation
};


class Data_Worker {
public:

    static std::vector<std::vector<float>> min_max_normalisation(std::vector<std::vector<float>> data);

    static std::vector<std::vector<float>> zScoreNormalization(std::vector<std::vector<float>> data);

    static std::vector<std::vector<float>> maxAbsNormalization(std::vector<std::vector<float>> data);

    static std::vector<std::vector<float>> quantileNormalization(std::vector<std::vector<float>> data);

    static void check_data(std::vector<std::vector<float>> input_data,
                           std::vector<std::vector<float>> output_data,
                           std::vector<std::vector<Neuron>> net);

    static std::vector<std::vector<std::vector<float>>>
    call(Normalisation type, const std::vector<std::vector<float>>& inp, const std::vector<std::vector<float>>& out);
    };

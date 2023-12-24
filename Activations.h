#pragma once

#include <string_view>

enum class FunctionType {
    sigmoid,
    fast_sigmoid,
    silu,
    tanh
};


float call(FunctionType type, float arg);

const char *function_type_to_string(FunctionType type);

FunctionType function_type_from_string(std::string_view name);

namespace activation {
    /**
     * @brief Sigmoid function.
     *
     * This function computes the sigmoid (logistic) function for the given number.
     *
     * @param x Your number.
     * @return Function value.
     */
    float sigmoid(float x);

    /**
     * @brief Fast sigmoid approximation.
     *
     * This function computes an approximation of the sigmoid function for the given number.
     * It sacrifices accuracy for speed.
     *
     * @param x Your number.
     * @return Approximated function value.
     */
    float fast_sigmoid(float x);

    /**
     * @brief Rectified Linear Unit (ReLU) function.
     *
     * This function computes the ReLU function for the given number.
     * Returns 0 if input is less than 0, otherwise returns the input itself.
     *
     * @param x Your number.
     * @return Function value.
     */

    float silu(float x);

    /**
     * @brief Hyperbolic Tangent (Tanh) function.
     *
     * This function computes the hyperbolic tangent for the given number.
     *
     * @param x Your number.
     * @return Function value.
     */
    float tanh(float x);
}
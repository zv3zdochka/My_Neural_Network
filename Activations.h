#pragma once

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
    float relu(float x);

    /**
     * @brief Leaky Rectified Linear Unit (Leaky ReLU) function.
     *
     * This function computes the Leaky ReLU function for the given number.
     * Returns 'x' if input is greater than or equal to 0, otherwise returns 'a * x', where 'a' is a small constant.
     *
     * @param x Your number.
     * @param a The slope of the function for x < 0 (typically a small positive value).
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
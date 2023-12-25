#pragma once

/**
 * @file Activ_derivatives.h
 * @brief Header file containing derivative functions for various activation functions.
 */

namespace Derivatives {

    /**
     * @brief Compute the derivative of the sigmoid activation function.
     * @param x Input value.
     * @return Derivative of the sigmoid function.
     */
    float sigmoid_derivative(float x);

    /**
     * @brief Compute the derivative of the fast sigmoid activation function.
     * @param x Input value.
     * @return Derivative of the fast sigmoid function.
     */
    float fast_sigmoid_derivative(float x);

    /**
     * @brief Compute the derivative of the silu (Sigmoid Linear Unit) activation function.
     * @param x Input value.
     * @return Derivative of the silu function.
     */
    float silu_derivative(float x);

    /**
     * @brief Compute the derivative of the hyperbolic tangent (tanh) activation function.
     * @param x Input value.
     * @return Derivative of the tanh function.
     */
    float tanh_derivative(float x);

}

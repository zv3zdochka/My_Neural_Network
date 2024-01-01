#pragma oncet

#include <string_view>

enum class FunctionType {
    sigmoid,
    fast_sigmoid,
    silu,
    tanh
};


/**
 * @brief Call a specific activation function based on the FunctionType.
 *
 * This function executes the specified activation function based on the FunctionType enum.
 *
 * @param type The type of activation function to be called.
 * @param arg The argument to the activation function.
 * @return The result of the specified activation function.
 */
float call(FunctionType type, float arg);

/**
 * @brief Convert FunctionType enum to its string representation.
 *
 * This function converts a FunctionType enum value to its corresponding string representation.
 *
 * @param type The FunctionType value.
 * @return The string representation of the FunctionType.
 */
const char *function_type_to_string(FunctionType type);

/**
 * @brief Convert string representation to FunctionType enum.
 *
 * This function converts a string representation of a FunctionType to its corresponding enum value.
 *
 * @param name The string representation of the FunctionType.
 * @return The FunctionType enum value.
 * @throw std::runtime_error if the provided name is invalid.
 */
FunctionType function_type_from_string(std::string_view name);

namespace activation {
    /**
     * @brief Sigmoid function.
     *
     * This function computes the sigmoid (logistic) function for the given number.
     *
     * @param x The input value.
     * @return The computed sigmoid function value.
     */
    float sigmoid(float x);

    /**
     * @brief Fast sigmoid approximation.
     *
     * This function computes an approximation of the sigmoid function for the given number.
     * It sacrifices accuracy for speed.
     *
     * @param x The input value.
     * @return The approximated sigmoid function value.
     */
    float fast_sigmoid(float x);

    /**
     * @brief Sigmoid-weighted linear unit (SiLU) function.
     *
     * This function computes the SiLU (Sigmoid-weighted linear unit) function for the given number.
     * Returns x multiplied by the sigmoid of x.
     *
     * @param x The input value.
     * @return The computed SiLU function value.
     */
    float silu(float x);

    /**
     * @brief Hyperbolic Tangent (Tanh) function.
     *
     * The hyperbolic tangent function calculates the hyperbolic tangent for the given number.
     * It returns the value (exp(x) - exp(-x)) / (exp(x) + exp(-x)), where x is the input.
     *
     * @param x The input value.
     * @return The computed hyperbolic tangent of the input value.
     * @note The output of this function ranges between -1 and 1.
     *       For large positive or negative input values, the output approaches -1 or 1 respectively.
     */
    float tanh(float x);
}

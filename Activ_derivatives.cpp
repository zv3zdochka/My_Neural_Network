#include <iostream>
#include <numbers>
#include <cmath>

namespace Derivatives {

    float sigmoid_derivative(float x) {
        float exp_x = std::exp(x);
        return exp_x / std::pow(exp_x + 1, 2);
    }

    float fast_sigmoid_derivative(float x) {
        return 1 / (pow(1 + abs(x), 2));
    }


    float silu_derivative(float x) {
        float exp_x = std::exp(x);
        return (std::exp(2 * x) + exp_x + x * exp_x) / std::pow(exp_x + 1, 2);
    }

    float tanh_derivative(float x) {
        float exp_2x = std::exp(2 * x);
        return (4 * exp_2x) / std::pow(exp_2x, 2);
    }

}
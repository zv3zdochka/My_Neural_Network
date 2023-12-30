#include <cmath>

namespace Derivatives {

    float sigmoid_derivative(float x) {
        float exp_x = std::exp(x);
        return static_cast<float>(exp_x / std::pow(exp_x + 1.0f, 2));
    }

    float fast_sigmoid_derivative(float x) {
        return static_cast<float>(1.0f / (std::pow(1.0f + std::abs(x), 2)));
    }


    float silu_derivative(float x) {
        float exp_x = std::exp(x);
        return static_cast<float>((std::exp(2 * x) + exp_x + x * exp_x) / std::pow(exp_x + 1.0f, 2));
    }

    float tanh_derivative(float x) {
        float exp_2x = std::exp(2 * x);
        return static_cast<float>((4 * exp_2x) / std::pow(exp_2x, 2));
    }

}

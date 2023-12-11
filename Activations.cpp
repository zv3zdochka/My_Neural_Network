#include "Activations.h"
#include <cmath>
#include <numbers>

float activation::sigmoid(float x) {
    return 1 / (1 + std::pow(std::numbers::e_v<float>, -x));
}

float activation::fast_sigmoid(float x) {
    return x / (1 + std::abs(x));
}

float activation::relu(float x) {
    if (x > 0) {
        return x;
    } else {
        return 0;
    }
}


float activation::silu(float x) {
    return x * (1 / (1 + std::pow(std::numbers::e_v<float>, -x)));
}

float activation::tanh(float x) {
    using std::pow;
    using std::numbers::e_v;
    return (pow(e_v<float>, x) - pow(e_v<float>, -x))
           / (pow(e_v<float>, x) + pow(e_v<float>, -x));
}


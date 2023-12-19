#include "Activations.h"
#include <cmath>

float activation::sigmoid(float x) {
    return 1 / (1 + std::exp(-x));
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
    return x * (1 / (1 + std::exp(-x)));
}

float activation::tanh(float x) {
    return std::tanh(x);
}

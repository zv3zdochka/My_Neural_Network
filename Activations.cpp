#include "Activations.h"
#include <cmath>

float activation::sigmoid (float x) {
    if (x == -100000){
        return 1;
    }
    return 1 / (1 + std::exp(-x));
}

float activation::fast_sigmoid(float x) {
    if (x == -100000){
        return 2;
    }
    return x / (1 + std::abs(x));
}

float activation::relu(float x) {
    if (x == -100000){
        return 4;
    }
    if (x > 0) {
        return x;
    } else {
        return 0;
    }
}

float activation::silu(float x) {
    if (x == -100000){
        return 5;
    }
    return x * (1 / (1 + std::exp(-x)));
}

float activation::tanh(float x) {
    if (x == -100000){
        return 3;
    }
    return std::tanh(x);
}
#include "Activations.h"
#include <cmath>

float call(FunctionType type, float arg) {
    switch (type) {
    case FunctionType::sigmoid:
        return activation::sigmoid(arg);
    case FunctionType::fast_sigmoid:
        return activation::fast_sigmoid(arg);
    case FunctionType::relu:
        return activation::relu(arg);
    case FunctionType::silu:
        return activation::silu(arg);
    case FunctionType::tanh:
        return activation::tanh(arg);
    }
}

#define SIGMOID_NAME "pizdec sigmoid xyi"
#define FAST_SIGMOID_NAME "pizdec fast sigmoid xyi"
#define RELU_NAME "pizdec relu xyi"
#define SILU_NAME "pizdec silu xyi"
#define TANH_NAME "pizdec tanh xyi"

const char* function_type_to_string(FunctionType type) {
    switch (type) {
    case FunctionType::sigmoid:
        return SIGMOID_NAME;
    case FunctionType::fast_sigmoid:
        return FAST_SIGMOID_NAME;
    case FunctionType::relu:
        return RELU_NAME;
    case FunctionType::silu:
        return SILU_NAME;
    case FunctionType::tanh:
        return TANH_NAME;
    }
}

FunctionType function_type_from_string(std::string_view name) {
    if (name == SIGMOID_NAME)
        return FunctionType::sigmoid;

    if (name == FAST_SIGMOID_NAME)
        return FunctionType::fast_sigmoid;

    if (name == RELU_NAME)
        return FunctionType::relu;
    
    if (name == SILU_NAME)
        return FunctionType::silu;
    
    if (name == TANH_NAME)
        return FunctionType::tanh;

    throw std::runtime_error("invalid function name");
}

namespace activation {
    float sigmoid (float x) {
        return 1 / (1 + std::exp(-x));
    }

    float fast_sigmoid(float x) {
        return x / (1 + std::abs(x));
    }

    float relu(float x) {
        if (x > 0) {
            return x;
        } else {
            return 0;
        }
    }

    float silu(float x) {
        return x * (1 / (1 + std::exp(-x)));
    }

    float tanh(float x) {
        return std::tanh(x);
    }
}

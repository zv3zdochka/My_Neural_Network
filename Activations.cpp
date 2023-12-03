#include "Activations.h"
#include <cmath>

float Activation::sigmoid(float x) {
    const float e = 2.7182818284;
    return 1 / (1 + pow(e, -x));
}

float Activation::fast_sigmoid(float x) {
    return x / (1 + abs(x));
}

float Activation::relu(float x) {
    if (x > 0) {
        return x;
    } else {
        return 0;
    }
}

float Activation::leaky_relu(float x, float a) {
    if (a * x > x) {
        return a * x;
    } else {
        return x;
    }
}

float Activation::elu(float x, float a) {
    const float e = 2.7182818284;
    if (x > 0) {
        return x;
    } else {
        return (a * ((pow(e, x)) - 1));
    }
}

float Activation::silu(float x) {
    const float e = 2.7182818284;
    return x * (1 / (1 + pow(e, -x)));
}

float Activation::tanh(float x) {
    const float e = 2.7182818284;
    return (pow(e, x) - pow(e, -x)) / (pow(e, x) + pow(e, -x));
}

//float Activation::softmax(float x) {
//    return x;
//}

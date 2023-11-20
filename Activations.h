#pragma once

class Activation {
public:
    /**
     * @brief Sigmoid function.
     *
     * This function computes the sigmoid (logistic) function for the given number.
     *
     * @param x Your number.
     * @return Function value.
     */
    static float sigmoid(float x);
    static float fast_sigmoid(float x);
    static float relu(float x);
    static float leaky_relu(float x, float a);
    static float elu(float x, float a);
    static float silu(float x);
    static float tanh(float x);
    static float softmax(float x);


};

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

};

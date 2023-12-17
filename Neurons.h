#pragma once
#include <functional>
#include <utility>

class Neuron {
public:
    Neuron(int layer_number, float weight, std::function<float(float)> activationFunc);

    float computeActivation(float input);

    const int layer_num;
    float weight;
    const std::function<float(float)> activationFunction;

};

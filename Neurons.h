#pragma once
#include <functional>
#include <utility>

class Neuron {
public:
    Neuron(int layer_number, float weight, std::function<float(float)> activationFunc);

    float computeActivation(float input);

    int layer_num;
    float weight;
    std::function<float(float)> activationFunction;

    Neuron& operator=(const Neuron& other) {
        if (this != &other) {
            layer_num = other.layer_num;
            weight = other.weight;
            activationFunction = other.activationFunction;  // Copy the function
        }
        return *this;
    }

};
#pragma once
#include <functional>

class Neurons {
public:
    class Input_Neuron {
    public:
        Input_Neuron(float weight, std::function<float(float)> activationFunc);

        float computeActivation(float input);

        float weight;
        int layer_number = 0;
        std::function<float(float)> activationFunction;
    };

    class Hidden_Neuron {
    public:
        Hidden_Neuron(int layer_num, float weight, std::function<float(float)> activationFunc);

        float computeActivation(float input);

        float weight;
        int layer_number;
        std::function<float(float)> activationFunction;
    };

    class Output_Neuron {
    public:
        Output_Neuron(int layer_num, float weight, std::function<float(float)> activationFunc);

        float computeActivation(float input);

        float weight;
        int layer_number;
        std::function<float(float)> activationFunction;
    };
};



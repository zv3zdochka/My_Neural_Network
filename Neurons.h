#pragma once
#include <functional>
#include <utility>
#include "Activations.h"

class Neuron {
public:
    Neuron(int layer_number, float weight, FunctionType type);

    float computeActivation(float input);

    int layer_num;
    float weight;
    FunctionType fn_type;
};

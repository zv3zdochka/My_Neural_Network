#include "Neurons.h"

Neuron::Neuron(int layer_number, float weight, FunctionType type)
        : layer_num(layer_number), weight(weight), fn_type(type) {}

float Neuron::computeActivation(float input) {
    return call(fn_type, input);
}

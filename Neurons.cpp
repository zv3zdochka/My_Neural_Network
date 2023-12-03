#include "neurons.h"

Neuron::Neuron(int layer_number, float weight, std::function<float(float)> activationFunc)
        : layer_num(layer_number), weight(weight), activationFunction(std::move(activationFunc)) {}

float Neuron::computeActivation(float input) {
    return activationFunction(input);
}

float Neuron::getWeight() {
    return weight;
}

int Neuron::getLayer() {
    return layer_num;
}

#pragma once
#include <vector>
#include "Neurons.h"

class Network {
public:

    int layers = 0;
    std::vector<std::vector<Neuron>> network ;


    void add_input_layer(int number_of_neurons, const std::function<float(float)>& activation_func, float b);
    void add_hidden_layer(int number_of_neurons, const std::function<float(float)>& activation_func, float b);
    void add_output_layer(int number_of_neurons, const std::function<float(float)>& activation_func, float b);
    void show_network();
};

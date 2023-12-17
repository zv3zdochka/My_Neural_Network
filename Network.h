#pragma once

#include <vector>
#include "Neurons.h"

class Network {
public:

    int layers = 0;
    std::vector<std::vector<Neuron>> network;
    std::vector<std::vector<float>> synapse;

    void add_input_layer(int number_of_neurons, const std::function<float(float)> &activation_func, float b);

    void add_hidden_layer(int number_of_neurons, const std::function<float(float)> &activation_func, float b);

    void add_output_layer(int number_of_neurons, const std::function<float(float)> &activation_func, float b);

    void build();

    void show_network();


    void through(std::vector<std::vector<float>> weights, std::vector<float> inp);
    void train(std::vector<std::vector<float>> parameters, std::vector<std::vector<float>> answer, int epochs, float test_data);

private:
    void create_synapse();
    void show_weights();
    void show_synapse();
};


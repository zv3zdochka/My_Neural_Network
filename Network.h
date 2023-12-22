#pragma once

#include "Neurons.h"
#include "Matrix.h"
#include "Activations.h"
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <iomanip>
#include <fstream>

enum class LayerType {
    input,
    hidden,
    output
};

class Network {
public:

    explicit Network(const char *filename);
    Network();

    int layers = 0;
    std::vector<std::vector<Neuron>> network;
    std::vector<std::vector<std::vector<float>>> synapse;

    void add_layer(LayerType type, int number_of_neurons, const std::function<float(float)> &activation_func, float b);
    void build();
    void show_network();
    void save(const char *filename) const;


    static Matrix through_layer(const Matrix& weights, const std::vector<std::vector<float>>& input, const std::function<float(float)>& activationFunc);
    void train(std::vector<std::vector<std::vector<float>>> data, const std::vector<std::vector<float>>& answer, int epochs, float test_data_per);


private:
    void create_synapse();
    void show_weights();
    void show_synapse();
    void clear_weights();
};


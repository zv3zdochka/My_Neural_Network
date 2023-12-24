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
    std::vector<std::vector<float>> neu_out;

    void add_layer(LayerType type, int number_of_neurons, FunctionType af, float b);

    void build();

    void show_network();

    void save(const char *filename) const;


    Matrix through_layer(const Matrix &weights, const std::vector<std::vector<float>> &input, FunctionType af);

    void
    train(std::vector<std::vector<std::vector<float>>> data, const std::vector<std::vector<float>> &answer, int epochs,
          float test_data_per, float train_speed);
    static Matrix multiply(const Matrix &weights, const Matrix &input);

private:
    void create_synapse();

    void show_weights();

    void show_synapse();

    void clear_weights();

    Matrix convert(std::vector<float> inp);
};


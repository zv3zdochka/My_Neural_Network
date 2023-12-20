#pragma once

#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <string_view>

#include "Neurons.h"
#include "Matrix.h"

enum class LayerType {
    input,
    hidden,
    output
};

class Network {
public:
    Network(std::string_view filename);

    Network() = default;
    ~Network() = default;

public:
    void build();
    void show_network();

    void add_layer(LayerType type, int number_of_neurons, const std::function<float(float)> &activation_func, float b = 0.0f);

    using vec3 = std::vector<std::vector<std::vector<float>>>;
    using vec2 = std::vector<std::vector<float>>;
    Matrix through_layer(const Matrix& weights, const vec2& input) ;

    void train(const vec3& data, const vec2& answer, int epochs, float test_data_per);

    void save(std::string_view filename) const;

private:
    void create_synapse();
    void show_weights();
    void show_synapse();

    int layers;
    std::vector<std::vector<Neuron>> network;
    std::vector<std::vector<std::vector<float>>> synapse;
};

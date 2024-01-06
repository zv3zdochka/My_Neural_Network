#pragma once

#include "Neurons.h"
#include "Matrix.h"
#include "Activations.h"
#include "Utils.h"
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

    std::vector<std::vector<float>> input_train;
    std::vector<std::vector<float>> output_train;
    std::vector<std::vector<float>> input_test;
    std::vector<std::vector<float>> output_test;

    void add_layer(LayerType type, int number_of_neurons, FunctionType af, float b);

    void build();

    void show_network();

    void save(const char *filename) const;


    Matrix through_layer(const Matrix &weights, const std::vector<std::vector<float>> &input, FunctionType af);

    void
    train(const std::vector<std::vector<float>>& inputData, const std::vector<std::vector<float>> &outputData, Normalisation normalisation, int epochs,
          float test_data_per, float train_speed);


private:
    void process_data(std::vector<std::vector<float>> input_train,
                      std::vector<std::vector<float>> output_train, Normalisation norm, float spliting);

    static Matrix multiply(const Matrix &weights, const Matrix &input);

    void create_synapse();

    void show_weights();

    void show_synapse();

    void clear_weights();

    static Matrix convert(const std::vector<float> &inp);

    Matrix collect_with_derivatives(int cur_lay, Matrix input, std::vector<std::vector<float>> errors, float speed);

};


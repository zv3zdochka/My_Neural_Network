#pragma once

/**
 * @file Network.h
 * @brief Header file containing the Network class for building and training neural networks.
 */

#include "Neurons.h"
#include "Matrix.h"
#include "Activations.h"
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <iomanip>
#include <fstream>

/**
 * @enum LayerType
 * @brief Enumeration representing the types of layers in the neural network.
 */
enum class LayerType {
    input, ///< Input layer
    hidden, ///< Hidden layer
    output ///< Output layer
};

/**
 * @class Network
 * @brief Represents a neural network and provides methods for building, training, and using the network.
 */
class Network {
public:
    /**
     * @brief Parameterized constructor to initialize the network from a file.
     * @param filename Name of the file containing network configuration.
     */
    explicit Network(const char *filename);

    /**
     * @brief Default constructor.
     */
    Network();

    int layers = 0; ///< Number of layers in the network
    std::vector<std::vector<Neuron>> network; ///< Vector of neuron vectors representing the network structure
    std::vector<std::vector<std::vector<float>>> synapse; ///< Vector of weight matrices connecting neurons
    std::vector<std::vector<float>> neu_out; ///< Vector of neuron outputs

    /**
     * @brief Add a layer to the network.
     * @param type Type of the layer (input, hidden, output).
     * @param number_of_neurons Number of neurons in the layer.
     * @param af Activation function for the layer.
     * @param b Bias for the neurons in the layer.
     */
    void add_layer(LayerType type, int number_of_neurons, FunctionType af, float b);

    /**
     * @brief Build the neural network by connecting neurons and initializing weights.
     */
    void build();

    /**
     * @brief Display information about the network structure.
     */
    void show_network();

    /**
     * @brief Save the network configuration to a file.
     * @param filename Name of the file to save the configuration.
     */
    void save(const char *filename) const;

    /**
     * @brief Pass input through a layer with specified weights and activation function.
     * @param weights Weight matrix for the layer.
     * @param input Input data to the layer.
     * @param af Activation function for the layer.
     * @return Matrix representing the output of the layer.
     */
    Matrix through_layer(const Matrix &weights, const std::vector<std::vector<float>> &input, FunctionType af);

    /**
     * @brief Train the network using backpropagation.
     * @param data Input data for training.
     * @param answer Target output for training.
     * @param epochs Number of training epochs.
     * @param test_data_per Percentage of data to use for testing.
     * @param train_speed Learning rate for training.
     */
    void train(std::vector<std::vector<std::vector<float>>> data, const std::vector<std::vector<float>> &answer,
               int epochs, float test_data_per, float train_speed);

    /**
     * @brief Perform matrix multiplication.
     * @param weights Weight matrix.
     * @param input Input matrix.
     * @return Resulting matrix.
     */
    static Matrix multiply(const Matrix &weights, const Matrix &input);

private:
    /**
     * @brief Create synapses between layers and initialize weights.
     */
    void create_synapse();

    /**
     * @brief Display information about the weights in the network.
     */
    void show_weights();

    /**
     * @brief Display information about the synapses in the network.
     */
    void show_synapse();

    /**
     * @brief Clear the weights in the network.
     */
    void clear_weights();

    /**
     * @brief Convert a vector to a matrix for compatibility.
     * @param inp Input vector.
     * @return Matrix representing the vector.
     */
    static Matrix convert(const std::vector<float>& inp);

    /**
     * @brief Collect gradients and update weights using backpropagation.
     * @param cur_lay Current layer index.
     * @param input Input data to the layer.
     * @param errors Errors in the output.
     * @param speed Learning rate for weight updates.
     * @return Matrix representing the collected gradients.
     */
    Matrix collect_with_derivatives(int cur_lay, Matrix input, std::vector<std::vector<float>> errors, float speed);
};


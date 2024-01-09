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

/**
 * @brief Enum defining the type of layers in a neural network.
 */
enum class LayerType {
    input,   // Input layer
    hidden,  // Hidden layer
    output   // Output layer
};

/**
 * @brief Class representing a neural network.
 */
class Network {
public:
    /**
     * @brief Constructor that loads the network configuration from a file.
     *
     * @param filename The name of the file containing the network configuration.
     */
    explicit Network(const char *filename);

    /**
     * @brief Default constructor for the Network class.
     */
    Network();

    /**
 * @brief Represents the number of layers in the neural network.
 */
    int layers = 0;

    /**
     * @brief Represents the network architecture as a vector of vectors of neurons.
     */
    std::vector<std::vector<Neuron>> network;

    /**
     * @brief Represents the synapse weights between layers in the network.
     */
    std::vector<std::vector<std::vector<float>>> synapse;

    /**
     * @brief Stores the output of neurons for each layer during the network's operations.
     */
    std::vector<std::vector<std::vector<float>>> neu_out;

    /**
     * @brief Contains the input training data for the neural network.
     */
    std::vector<std::vector<float>> input_train;

    /**
     * @brief Contains the output training data for the neural network.
     */
    std::vector<std::vector<float>> output_train;

    /**
     * @brief Contains the input test data for the neural network.
     */
    std::vector<std::vector<float>> input_test;

    /**
     * @brief Contains the output test data for the neural network.
     */
    std::vector<std::vector<float>> output_test;


    /**
     * @brief Adds a layer to the neural network.
     *
     * @param type The type of layer (input, hidden, or output).
     * @param number_of_neurons The number of neurons in the layer.
     * @param af The activation function used in the layer.
     */
    void add_layer(LayerType type, int number_of_neurons, FunctionType af);

    /**
     * @brief Builds the neural network.
     */
    void build();

    /**
     * @brief Displays the network architecture.
     */
    void show_network();

    /**
     * @brief Saves the network configuration to a file.
     *
     * @param filename The name of the file to save the configuration to.
     */
    void save(const char *filename) const;

    //... (other member functions)

    /**
     * @brief Performs forward pass through a layer with given weights and input data using a specified activation function.
     *
     * @param weights The weights of the layer.
     * @param input The input data to the layer.
     * @param af The activation function used in the layer.
     * @return Matrix containing the output after passing through the layer.
     */
    Matrix through_layer(const Matrix &weights, const std::vector<std::vector<float>> &input, FunctionType af);

    /**
     * @brief Trains the neural network using the provided input and output data.
     *
     * @param inputData The input data for training.
     * @param outputData The corresponding output data for training.
     * @param normalisation The type of normalization to be applied.
     * @param epochs The number of training epochs.
     * @param test_data_per The percentage of data to use as test data.
     * @param train_speed The learning rate for training.
     */
    void train(const std::vector<std::vector<float>> &inputData, const std::vector<std::vector<float>> &outputData,
               Normalisation normalisation, int epochs,
               float test_data_per, float train_speed);

    /**
     * @brief Performs inference using the trained network on input data.
     *
     * @param input The input data for inference.
     */
    void work(std::vector<std::vector<float>> input);

private:
    //... (other private member variables and functions)

    /**
     * @brief Processes the training data, normalizing, shuffling, and splitting it.
     *
     * @param input_train The input training data.
     * @param output_train The output training data.
     * @param norm The normalization method to be applied.
     * @param coe The coefficient for splitting the data.
     */
    void process_data(const std::vector<std::vector<float>> &input_train,
                      const std::vector<std::vector<float>> &output_train, Normalisation norm, float coe);

    /**
     * @brief Multiplies two matrices.
     *
     * @param weights The first matrix to be multiplied.
     * @param input The second matrix to be multiplied.
     * @return The result of the matrix multiplication.
     */
    static Matrix multiply(const Matrix &weights, const Matrix &input);

    //... (other private member functions)

    /**
     * @brief Creates synapses for the neural network with random weights.
     */
    void create_synapse();

    /**
     * @brief Displays the weights of neurons in the network.
     */
    void show_weights();

    /**
     * @brief Displays the synapse weights between layers in the network.
     */
    void show_synapse();

    /**
     * @brief Resets all weights in the network to zero.
     */
    void clear_weights();

    /**
     * @brief Collects derivatives of errors for weight update in backpropagation.
     *
     * @param cur_lay The current layer index.
     * @param input The input matrix.
     * @param errors The errors matrix.
     * @param speed The learning rate.
     * @return Matrix containing the derivatives.
     */
    Matrix collect_with_derivatives(int cur_lay, Matrix input, std::vector<std::vector<float>> errors, float speed);
};

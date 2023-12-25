#pragma once

/**
 * @file Neurons.h
 * @brief Header file containing the Neuron class for representing individual neurons.
 */

#include <functional>
#include <utility>
#include "Activations.h"

/**
 * @class Neuron
 * @brief Represents an individual neuron in a neural network.
 */
class Neuron {
public:
    /**
     * @brief Parameterized constructor to initialize a neuron.
     * @param layer_number Layer index to which the neuron belongs.
     * @param weight Weight assigned to the neuron.
     * @param type Activation function type for the neuron.
     */
    Neuron(int layer_number, float weight, FunctionType type);

    /**
     * @brief Compute the activation of the neuron for a given input.
     * @param input Input value to the neuron.
     * @return Activation value.
     */
    float computeActivation(float input);

    int layer_num; ///< Layer index to which the neuron belongs
    float weight; ///< Weight assigned to the neuron
    FunctionType fn_type; ///< Activation function type for the neuron
};

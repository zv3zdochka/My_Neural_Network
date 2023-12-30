#pragma once
#include <functional>
#include <utility>
#include "Activations.h"

/**
 * @brief Class representing a Neuron in a neural network.
 */
class Neuron {
public:
    /**
     * @brief Constructor for Neuron class.
     * @param layer_number The layer number to which the neuron belongs.
     * @param weight The weight of the neuron.
     * @param type The activation function type for the neuron.
     */
    Neuron(int layer_number, float weight, FunctionType type);

    /**
     * @brief Computes the activation of the neuron based on the input.
     * @param input The input value for computing the activation.
     * @return The computed activation value.
     */
    [[maybe_unused]] [[nodiscard]] float computeActivation(float input) const;

    int layer_num; /**< The layer number of the neuron. */
    float weight; /**< The weight of the neuron. */
    FunctionType fn_type; /**< The activation function type of the neuron. */
};

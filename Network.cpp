#include <random>
#include <iostream>
#include "Network.h"
#include "Neurons.h"

std::random_device weight;
std::mt19937 gen1(weight());


std::random_device sepsis;
std::default_random_engine gen2(sepsis());


std::uniform_real_distribution<float> dis1(1.0f, 5.0f);
std::uniform_real_distribution<float> dis2(0.1f, 10.0f);


void Network::add_input_layer(int number_of_neurons, const std::function<float(float)> &activation_func, float b) {
    network.emplace_back();
    for (int neuron = 0; neuron < number_of_neurons; neuron++) {
        network[0].emplace_back(1, dis1(gen1), activation_func);
    }
    layers += 1;


}


void Network::add_hidden_layer(int number_of_neurons, const std::function<float(float)> &activation_func, float b) {
    network.emplace_back();
    for (int neuron = 0; neuron < number_of_neurons; neuron++) {
        network[layers].emplace_back(layers + 1, dis1(gen1), activation_func);
    }
    layers += 1;
}


void Network::add_output_layer(int number_of_neurons, const std::function<float(float)> &activation_func, float b) {
    network.emplace_back();

    for (int neuron = 0; neuron < number_of_neurons; neuron++) {
        network[network.size() - 1].emplace_back(layers + 1, dis1(gen1), activation_func);
    }

    layers += 1;
}

void Network::create_synapse() {


    for (size_t i = 0; i < network.size() - 1; ++i) {
        synapse.emplace_back();
        for (size_t j = 0; j < network[i].size(); ++j) {
            for (size_t k = 0; k < network[i + 1].size(); ++k) {
                float weight = dis2(gen2);
                synapse[i].push_back(weight);
            }
        }
    }
}


void Network::build() {
    create_synapse();
}

void Network::show_network() {
    show_weights();
    show_synapse();
}

void Network::show_synapse() {
    for (size_t i = 0; i < synapse.size(); ++i) {
        std::cout << "Layer " << i + 1 << " to Layer " << i + 2 << " synapse weights:\n";
        for (size_t j = 0; j < synapse[i].size(); ++j) {
            std::cout << "Synapse weight " << j + 1 << ": " << synapse[i][j] << std::endl;
        }
        std::cout << std::endl;
    }
}

void Network::show_weights() {
    for (int i = 0; i < layers; i++) {
        std::cout << "Layer " << i + 1 << ":\n";
        for (int j = 0; j < network[i].size(); j++) {
            Neuron current_neuron = network[i][j];
            std::cout << "Neuron " << j + 1 << " in Layer " << i + 1 << ":\n";
            std::cout << "Weight: " << current_neuron.getWeight() << "\n";
            std::cout << "----------------\n";
        }
        std::cout << "\n";
    }
}
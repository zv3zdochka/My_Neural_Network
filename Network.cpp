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



void Network::add_input_layer(int number_of_neurons, const std::function<float(float)>& activation_func, float b) {
    network.emplace_back();
    for (int neuron = 0; neuron < number_of_neurons; neuron++){
        network[0].emplace_back(1, dis1(gen1), activation_func);
    }
    layers += 1;


}



void Network::add_hidden_layer(int number_of_neurons, const std::function<float(float)>& activation_func, float b) {
    network.emplace_back();
    for (int neuron = 0; neuron < number_of_neurons; neuron++) {
        network[layers].emplace_back(layers + 1, dis1(gen1), activation_func);
    }
    layers += 1;
}


void Network::add_output_layer(int number_of_neurons, const std::function<float(float)>& activation_func, float b) {
    network.emplace_back();

    for (int neuron = 0; neuron < number_of_neurons; neuron++) {
        network[network.size()-1].emplace_back(layers + 1, dis1(gen1), activation_func);
    }

    layers += 1;
}


void Network::show_network() {
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


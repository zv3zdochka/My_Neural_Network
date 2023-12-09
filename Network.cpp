#include <random>
#include "Network.h"
#include "Neurons.h"

std::random_device weight;
std::mt19937 gen1(weight());


std::random_device sepsis;
std::default_random_engine gen2(sepsis());


std::uniform_real_distribution<float> dis1(1.0f, 5.0f);
std::uniform_real_distribution<float> dis2(0.1f, 10.0f);



void Network::add_input_layer(int number_of_neurons, std::function<float(float)> activation_func, float b) {

    for (int neuron = 0; neuron < number_of_neurons; neuron++){
        network[0].push_back(Neuron(1, dis1(gen1), activation_func));
    }
    layers += 1;


}



void Network::add_hidden_layer(int number_of_neurons, std::function<float(float)> activation_func, float b) {
    for (int neuron = 0; neuron < number_of_neurons; neuron++) {
        network[layers].push_back(Neuron(layers + 1, dis1(gen1), activation_func));
    }
    layers += 1;
}


void Network::add_output_layer(int number_of_neurons, std::function<float(float)> activation_func, float b) {
    for (int neuron = 0; neuron < number_of_neurons; neuron++) {
        network[-1].push_back(Neuron(layers + 1, dis1(gen1), activation_func));
    }


}

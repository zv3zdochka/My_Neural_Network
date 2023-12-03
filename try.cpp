#include "Neurons.h"
#include <vector>
#include "Activations.h"
#include <iostream>

int main() {
    Activation act;
    int layer_num = 3;
    int neurons_num = 2;

    std::vector<std::vector<Neuron>> network(layer_num);
    std::vector<std::vector<float>> weights(layer_num - 1);

    for (int i = 0; i < layer_num; i++) {
        for (int j = 0; j < neurons_num; j++) {
            network[i].push_back(Neuron(i + 1, 2.66, act.sigmoid));

        }
    }
    // print
    for (int i = 0; i < layer_num; i++) {
        std::cout << "Layer " << i + 1 << ":\n";
        for (int j = 0; j < neurons_num; j++) {
            Neuron current_neuron = network[i][j];
            std::cout << "Neuron " << j + 1 << " in Layer " << i + 1 << ":\n";
            std::cout << "Weight: " << current_neuron.getWeight() << "\n"   ;

            // std::cout << "Activation Function: " << current_neuron.getActivationFunction() << "\n";
            std::cout << "----------------\n";
        }
        std::cout << "\n";
    }

};
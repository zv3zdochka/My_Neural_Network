#include "Neurons.h"
#include <vector>
#include "Activations.h"
#include <iostream>

int main() {
    Activation act;
    int layer_num = 5;
    int neurons_num = 10;

    std::vector<std::vector<Neuron>> network(layer_num);

    for (int i = 0; i < layer_num; i++) {
        for (int j = 0; j < neurons_num; j++) {
            network[i].push_back(Neuron(5, 2.66, act.sigmoid));

        }
    }


};
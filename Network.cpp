#include "Network.h"
#include "Neurons.h"

void Network::add_hidden_layer() {}
void Network::add_input_layer(int number_of_neurons, std::function<float(float)> activation_func, float b) {
    for (int i = 0; i < layer_num; i++) {
        for (int j = 0; j < neurons_num; j++) {
            network[i].push_back(Neuron(i + 1, dis1(gen1), Activation::sigmoid));

        }
    }
}
void Network::add_output_layer() {}




#include "Network.h"
#include "Activations.h"
#include <iostream>
#include <vector>

int main() {
    Network net;
    net.add_input_layer(2, activation::sigmoid, 0.0f);
    net.add_hidden_layer(3, activation::tanh, 0.0f);
    net.add_output_layer(1, activation::tanh, 0.0f);
    net.build();
    net.show_network();


    // (->)
    std::vector<std::vector<float>> input_data = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    std::vector<std::vector<float>> output_data = {{1.0}, {1.0}, {0.0}, {1.0}};


    const int epochs = 100;


    net.train(input_data, output_data, epochs, 0.1);


    return 0;
}

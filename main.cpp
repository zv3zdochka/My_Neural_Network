#include "Network.h"
#include "Activations.h"


int main() {
    Network net;
    net.add_input_layer(2, activation::sigmoid, 0.0f);
    net.add_hidden_layer(4, activation::tanh, 0.0f);
    net.add_hidden_layer(6, activation::fast_sigmoid, 0.0f);
    net.add_output_layer(3, activation::tanh, 0.0f);
    net.build();
    net.show_network();


    return 0;
}
#include <iostream>
#include <cmath>
#include "Network.h"
#include "Activations.h"


int main() {
    Network net;
    net.add_input_layer(2, Activation::sigmoid, 0.0f);
    net.add_hidden_layer(4, Activation::sigmoid, 0.0f);

    return 0;
}
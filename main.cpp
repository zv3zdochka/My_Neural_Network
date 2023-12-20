#include "Network.h"
#include "Activations.h"
#include <iostream>
#include <vector>
#include <fstream>

#include <filesystem>

int main() {
    std::filesystem::current_path("..");

    Network net;
    net.add_layer(LayerType::input, 2, activation::sigmoid, 0.0f);
    net.add_layer(LayerType::hidden, 3, activation::sigmoid, 0.0f);
    net.add_layer(LayerType::output, 1, activation::sigmoid, 0.0f);
    net.build();
    net.show_network();

    net.save("base.json");


    Network loadedNetwork("base.json");

    // Display the loaded network
    loadedNetwork.show_network();


    //// (->)
    //std::vector<std::vector<std::vector<float>>> input_data = {{{7.6f}, {9.4f}}, {{7.8f}, {9.8f}}, {{1.0f}, {0.0f}}, {{1.0f}, {1.0f}}};
    //std::vector<std::vector<float>> output_data = {{1.0f}, {1.0f}, {0.0f}, {1.0f}};
//
//
    //const int epochs = 1;
//
//
    //net.train(input_data, output_data, epochs, 1);


    return 0;

}

#include "Network.h"
#include "Activations.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

int main() {
    std::filesystem::current_path("..");

    Network net;
    net.add_layer(LayerType::input, 2, FunctionType::silu, 0.0f);
    net.add_layer(LayerType::hidden, 5, FunctionType::sigmoid, 0.0f);
    net.add_layer(LayerType::hidden, 5, FunctionType::sigmoid, 0.0f);
    net.add_layer(LayerType::output, 2, FunctionType::tanh, 0.0f);


    net.build();
    net.show_network();
    net.save("base.json");
    std::vector<std::vector<std::vector<float>>> input_data = {{{0.1f}, {0.2f}}, {{0.7f}, {0.8f}}};
    std::vector<std::vector<float>> output_data = {{0.2f, 0.3f}, {0.8f, 0.9f}};

    const int epochs = 10;


    net.train(input_data, output_data, epochs, 0.5, 0.000001);



    //std::cout << "--------------------------------" << std::endl;


//    Network loadedNetwork("base.json");
//
//    // Display the loaded network
//    loadedNetwork.show_network();
//    std::vector<std::vector<std::vector<float>>> input_data = {{{1.0f}, {2.0f}}, {{3.0f}, {4.0f}}};
//    std::vector<std::vector<float>> output_data = {{3.0f, 4.09f}, {7.0f, 8.07f}};
//
//    const int epochs = 1;
//
//
//    loadedNetwork.train(input_data, output_data, epochs, 1, 0.02);
    
    // (->)
//    std::vector<std::vector<std::vector<float>>> input_data = {{{0.0f}, {0.0f}}, {{0.0f}, {1.0f}}, {{1.0f}, {0.0f}}, {{1.0f}, {1.0f}}};
//    std::vector<std::vector<float>> output_data = {{1.0f}, {1.0f}, {0.0f}, {1.0f}};



    return 0;
}

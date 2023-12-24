#include "Network.h"
#include "Activations.h"
#include "DataUtils.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

int main() {
    std::filesystem::current_path("..");

    Network net;
    net.add_layer(LayerType::input, 2, FunctionType::silu, 0.0f);
    net.add_layer(LayerType::hidden, 2, FunctionType::sigmoid, 0.0f);
    net.add_layer(LayerType::output, 2, FunctionType::tanh, 0.0f);

    net.build();
    net.show_network();
    net.save("base.json");
//    std::vector<std::vector<std::vector<float>>> input_data = {{{1.0f}, {2.0f}}, {{3.0f}, {4.0f}}};
//    std::vector<std::vector<float>> output_data = {{3.0f, 4.09f}, {7.0f, 8.07f}};
//
    const int epochs = 2;
//

    std::vector<std::vector<std::vector<float>>> input_data;
    std::vector<std::vector<float>> output_data;

    DataUtils::readDataset("fruits_dataset.txt", input_data, output_data);
    DataUtils::normalizeData(input_data);

    net.train(input_data, output_data, 2, 0.9, 0.02);



    //std::cout << "--------------------------------" << std::endl;


//    Network loadedNetwork("base.json");
//
//    Display the loaded network
//    loadedNetwork.show_network();
    
    // (->)
//    std::vector<std::vector<std::vector<float>>> input_data = {{{0.0f}, {0.0f}}, {{0.0f}, {1.0f}}, {{1.0f}, {0.0f}}, {{1.0f}, {1.0f}}};
//    std::vector<std::vector<float>> output_data = {{1.0f}, {1.0f}, {0.0f}, {1.0f}};



    return 0;
}

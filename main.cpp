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
    net.add_layer(LayerType::input, 2, FunctionType::relu, 0.0f);
    net.add_layer(LayerType::hidden, 3, FunctionType::sigmoid, 0.0f);
    net.add_layer(LayerType::output, 2, FunctionType::tanh, 0.0f);

    net.build();
    net.show_network();

    std::fstream input_file("input_data.txt");
    std::vector<std::vector<std::vector<float>>> input_data;
    std::vector<std::vector<float>> output_data;

    float value;
    while (input_file >> value) {
        std::vector<std::vector<float>> input_vector;
        input_vector.emplace_back(1, value);
        input_file >> value;
        input_vector.emplace_back(1, value);

        input_data.push_back(input_vector);

        std::vector<float> output_vector;
        input_file >> value;
        output_vector.push_back(value);
        input_file >> value;
        output_vector.push_back(value);

        output_data.push_back(output_vector);

    }
    normalize_input(input_data);
    normalize_output(output_data);

    display_data(input_data, output_data);


    const int epochs = 1;


    net.train(input_data, output_data, epochs, 1, 0.1);

    //net.save("base.json");

    std::cout << "--------------------------------" << std::endl;


    Network loadedNetwork("base.json");

    // Display the loaded network
    loadedNetwork.show_network();
    
    // (->)
//    std::vector<std::vector<std::vector<float>>> input_data = {{{0.0f}, {0.0f}}, {{0.0f}, {1.0f}}, {{1.0f}, {0.0f}}, {{1.0f}, {1.0f}}};
//    std::vector<std::vector<float>> output_data = {{1.0f}, {1.0f}, {0.0f}, {1.0f}};



    return 0;
}

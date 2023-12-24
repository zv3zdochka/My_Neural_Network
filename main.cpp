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

    //std::fstream data_file("fruits_dataset.txt");
    //std::vector<std::vector<float>> input_data;
    //std::vector<float> output_data;
//
    //float input1, input2, output;
    //char separator;
    //while (data_file >> input1 >> separator >> input2 >> separator >> output){
    //    input_data.push_back({input1, input2});
    //    output_data.push_back(output);
    //}

    std::vector<std::vector<float>> input_data = {{1.0f, 2.0f}, {3.0f, 4.0f}};
    std::vector<float> output_data = {3.0f, 4.09f, 7.0f, 8.07f};

    std::vector<std::vector<std::vector<float>>> normalized_input_data = normalize_input(input_data);
    std::vector<std::vector<float>> normalized_output_data = normalize_output(output_data);

    display_data(normalized_input_data, normalized_output_data);


    const int epochs = 1;


    net.train(normalized_input_data, normalized_output_data, epochs, 1, 0.1);

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


#include "Core.h"


int main() {
    std::filesystem::current_path("..");

//    Network net;
//    net.add_layer(LayerType::input, 3, FunctionType::sigmoid, 0.0f);
//    net.add_layer(LayerType::hidden, 3, FunctionType::sigmoid, 0.0f);
//    net.add_layer(LayerType::output, 3, FunctionType::sigmoid, 0.0f);
//
//    net.build();
    Network net("base.json");
    net.show_network();
    net.save("base.json");


    std::vector<std::vector<float>> input_data = {{0.9, 0.1f, 0.8f}};
    std::vector<std::vector<float>> output_data = {{3.4f, 5.7f, 6.0f}};

    const int epochs = 1;

    net.train(input_data, output_data, Normalisation::min_max_normalisation, epochs, 1, 0.02);




//    std::cout << "--------------------------------" << std::endl;
//
//
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

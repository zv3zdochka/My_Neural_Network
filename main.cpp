
#include "Core.h"


int main() {
    std::filesystem::current_path("..");

    Network net;
    net.add_layer(LayerType::input, 2, FunctionType::sigmoid, 0.0f);
    net.add_layer(LayerType::hidden, 4, FunctionType::silu, 0.0f);
    net.add_layer(LayerType::output, 2, FunctionType::sigmoid, 0.0f);

    net.build();
    net.show_network();
    //net.save("base.json");


    std::vector<std::vector<float>> input_data = {{1.0f, 2.0f}, {3.0f, 4.0f}, {5.0f, 6.0f}, {7.0f, 8.0f}, {9.0f, 10.0f}};
    std::vector<std::vector<float>> output_data = {{3.4f, 5.7f}, {10.0f, 8.4f}, {35.0f, 43.0f},{1.0f, 4.0f},{23.0f, 14.0f}};

    const int epochs = 1;

    net.train(input_data, output_data, Normalisation::min_max_normalisation, epochs, 0.2, 0.02);




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

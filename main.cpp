
#include "Core.h"


int main() {
    std::filesystem::current_path("..");

    Network net;
    net.add_layer(LayerType::input, 2, FunctionType::sigmoid, 0.0f);
    net.add_layer(LayerType::hidden, 2, FunctionType::sigmoid, 0.0f);
    net.add_layer(LayerType::hidden, 2, FunctionType::sigmoid, 0.0f);
    net.add_layer(LayerType::hidden, 2, FunctionType::sigmoid, 0.0f);
    net.add_layer(LayerType::hidden, 2, FunctionType::sigmoid, 0.0f);

    net.add_layer(LayerType::output, 2, FunctionType::sigmoid, 0.0f);
    net.build();
    net.show_network();
    //net.save("base3.json");

//    Network net("base2.json");
//    net.show_network();
    //net.save("base.json");

//
//    std::vector<std::vector<float>> input_data = {{0.9, 0.1f, 0.8f}};
//    std::vector<std::vector<float>> output_data = {{3.4f, 5.7f, 6.0f}};
    std::vector<std::vector<float>> input_data = {
            {0.6f, 0.2f},
//            {0.4f, 0.8f},
//            {0.3f, 0.7f},
//            {0.9f, 0.1f},
//            {0.5f, 0.5f}
    };

    std::vector<std::vector<float>> output_data = {
            {1.0f, 0.3f},
//            {0.5f, 0.9f},
//            {0.4f, 0.8f},
//            {1.0f, 0.0f},
//            {0.6f, 0.6f}
    };
//    std::vector<std::vector<float>> input_data = {
//            {0.6f},
//            {0.4f},
//            {0.3f},
//            {0.9f},
//            {0.5f}
//    };
//
//    std::vector<std::vector<float>> output_data = {
//            {0.9f},
//            {0.5f},
//            {0.4f},
//            {1.0f},
//            {0.6f}
//    };

    const int epochs = 900;

    net.train(input_data, output_data, Normalisation::without_normalisation, epochs, 1, 0.02);
    net.work(input_data);

    return 0;
}

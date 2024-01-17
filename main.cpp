#include "Core.h"


int main() {
    std::filesystem::current_path("..");

    Network net;
    net.add_layer(LayerType::input, 2, FunctionType::sigmoid);
    net.add_layer(LayerType::hidden, 3, FunctionType::sigmoid);
    net.add_layer(LayerType::hidden, 5, FunctionType::sigmoid);
    net.add_layer(LayerType::output, 1, FunctionType::sigmoid);
    net.build();
    net.show_network();
    net.save("base.json");

    std::vector<std::vector<float>> input_data = {
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 0.0f},
    };


    std::vector<std::vector<float>> output_data = {
            {0.0f},
            {1.0f},
            {1.0f},
            {1.0f},
    };

    const int epochs = 100;


    net.train(input_data, output_data, Normalisation::without_normalisation, epochs, 1, 0.5);

    net.work({{1.0f, 0.0f}});


    return 0;
}

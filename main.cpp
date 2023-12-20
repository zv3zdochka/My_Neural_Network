#include "Network.h"
#include "Activations.h"
#include <iostream>
#include <vector>
#include <fstream>

#include <filesystem>

int main() {
    std::filesystem::current_path("..");

    Network net;
    net.add_layer(LayerType::input, 2, activation::sigmoid);
    net.add_hidden_layer(3, activation::tanh, 0.0f);
    net.add_output_layer(1, activation::tanh, 0.0f);
    net.build();
    net.show_network();

    net.save("D:\\Code\\Network\\test.txt");

    // ������� ���� ��ꥪ� ��
    Network loadedNetwork;
    auto loadedData = loadedNetwork.read("D:\\Code\\Network\\test.txt");
    int loadedLayers;
    std::vector<std::vector<Neuron>> loadedNetworkData;
    std::vector<std::vector<std::vector<float>>> loadedSynapseData;

    std::tie(loadedLayers, loadedNetworkData, loadedSynapseData) = loadedData;

    // Create a new network and assign the loaded data
    Network newNetwork;
    newNetwork.layers = loadedLayers;
    newNetwork.network = loadedNetworkData;
    newNetwork.synapse = loadedSynapseData;

    // Display the loaded network
    newNetwork.show_network();


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

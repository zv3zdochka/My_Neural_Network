#include <fstream>
#include "Network.h"
#include "Neurons.h"
#include "Matrix.h"
#include "json.h"

//     std::string line;
//     std::getline(file, line);
//     size_t pos = line.find("num of layers ");
//     if (pos != std::string::npos) {
//         layers = std::stoi(line.substr(pos + 14));
//     }

//     // �ய����� ࠧ����⥫�
//     std::getline(file, line);

//     // �⥭�� ���ଠ樨 � ������ ᫮� � ���� ᨭ��ᮢ
//     for (int i = 0; i < layers; ++i) {
//         std::getline(file, line);  // �ய����� "layer num: neurons n; activation func"
//         std::getline(file, line);  // �ய����� "-----------------"

//         for (size_t j = 0; j < synapse[i].size(); ++j) {
//             std::getline(file, line);  // �ய����� "weights: w11 w21 ..."
//             // ��ࠡ�⪠ ��ப� � ���������� synapse[i][j]
//         }

//         std::getline(file, line);  // �ய����� "-----------------"
//     }

//     // �ய����� "extra data" � ���� �������⥫�� ����� (�᫨ ����)
//     std::getline(file, line);
//     // ��ࠡ�⪠ �������⥫��� ������

//     file.close();
//     return std::make_tuple(layers, network, synapse);
// }

std::random_device sepsis;
std::default_random_engine gen2(sepsis());
std::uniform_real_distribution<float> dis2(0.1f, 10.0f);

#define NETWORK_NUM_NEURONS_NAME    "num of neurons"
#define NETWORK_ACTIVATION_FN_NAME  "activation function"
#define NETWORK_SYNAPSE_NAME        "synapse"


Network::Network() {
}

Network::Network(const char *filename) {
    nlohmann::json input;

    {
        std::ifstream file(filename, std::ios::in | std::ios::binary);

        if (!file.is_open())
            throw std::runtime_error("unable to open file");

        file >> input;
    }

    int i = 0;
    for (const auto& layer_data : input) {
        int num_neurons = layer_data.at(NETWORK_NUM_NEURONS_NAME);
        std::function<float(float)> activation_func = activation::sigmoid; // sam nastroi
        float b = 0.0f; // sam nastroi

        // Add input layer
        if (i == 0){
            add_layer(LayerType::input, num_neurons, activation_func, b);
        }

        // Add hidden layer
        add_layer(LayerType::hidden, num_neurons, activation_func, b);

        // dodelay wywod
        auto& synapse_data = layer_data.at(NETWORK_SYNAPSE_NAME);
        for (size_t j = 0; j < synapse_data.size(); ++j) {
            synapse[layers - 1][j] = synapse_data[j].get<std::vector<float>>();
        }
        i++;
    }

    add_layer(LayerType::output, 1, activation::sigmoid, 0.0f);

    build();

    

}

void Network::add_layer(LayerType type, int number_of_neurons, const std::function<float(float)> &activation_func, float b) {
    network.emplace_back();

    switch (type) {
    case LayerType::input:
        for (int neuron = 0; neuron < number_of_neurons; neuron++) {
            network[0].emplace_back(1, 0, activation_func);
        }
        break;
    case LayerType::hidden:
        for (int neuron = 0; neuron < number_of_neurons; neuron++) {
            network[layers].emplace_back(layers + 1, 0, activation_func);
        }
        break;
    case LayerType::output:
        for (int neuron = 0; neuron < number_of_neurons; neuron++) {
            network[network.size() - 1].emplace_back(layers + 1, 0, activation_func);
        }
        break;
    }

    layers += 1;
}

void Network::create_synapse() {
    static std::random_device sepsis;
    static std::default_random_engine gen2(sepsis());
    std::uniform_real_distribution<float> dis2(0.1f, 10.0f);

    for (size_t i = 0; i < network.size() - 1; ++i) {
        synapse.emplace_back();

        if (network[i + 1].size() != 1) {
            for (size_t j = 0; j < network[i + 1].size(); ++j) {
                std::vector<float> demi_synapse;

                for (size_t k = 0; k < network[i].size(); ++k) {
                    float c_weight = dis2(gen2);
                    demi_synapse.push_back(c_weight);
                }

                synapse[i].emplace_back(std::move(demi_synapse));
            }
        } else {
            for (size_t j = 0; j < network[i].size(); ++j) {
                std::vector<float> demi_synapse;

                for (size_t k = 0; k < network[i + 1].size(); ++k) {
                    float c_weight = dis2(gen2);
                    demi_synapse.push_back(c_weight);
                }

                synapse[i].emplace_back(std::move(demi_synapse));
            }
        }
    }
}


void Network::build() {
    create_synapse();
}

void Network::show_network() {
    show_weights();
    show_synapse();

}

void Network::show_synapse() {
    for (int i = 0; i < layers - 1; i++) {
        std::cout << "Synapse weights from Layer " << i + 1 << " to Layer " << i + 2 << ":\n";

        for (auto & j : synapse[i]) {

            for (float k : j) {
                std::cout << k << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

}


void Network::show_weights() {
    std::cout << "Neuron Weights" << std::endl;
    for (const auto& layer : network) {
        for (const auto& neuron : layer) {
            std::cout << std::fixed << std::setprecision(1) << neuron.weight << " ";
        }
        std::cout << std::endl;
    }
}


void Network::train(const std::vector<std::vector<std::vector<float>>>& data, const std::vector<std::vector<float>>& answer, int epochs, float test_data_per) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (int j = 0; j < data.size(); j++) {
            std::vector<std::vector<float>> demi_res;

            for (int lay = 0; lay < layers - 1; lay++) {
                for (int k = 0; k < network[lay].size(); k++){
                    if (lay == 0){
                        network[lay][k].weight = data[j][k][0];
                    }
                    else{
                        network[lay][k].weight = demi_res[k][0];
                    }
                }

                show_weights();
                std::cout << '\n';
                demi_res = through_layer(Matrix(synapse[lay]), data[j]).get_data();
                for (int i = 0; i < demi_res.size(); i++){

                }
            }

        }

    }
}

Matrix Network::through_layer(const Matrix& weights, const std::vector<std::vector<float>>& input) {
    Matrix inp(input);
    Matrix res = weights * inp;
    return res;
}


void Network::save(const char *filename) const {
    nlohmann::json output;

    for (int i = 0; i < layers - 1; ++i) {
        nlohmann::json& layer_data = output.emplace_back();

        layer_data[NETWORK_NUM_NEURONS_NAME] = network[i].size();
        layer_data[NETWORK_ACTIVATION_FN_NAME] = "activation func";
        layer_data[NETWORK_SYNAPSE_NAME] = synapse[i];
    }

    std::ofstream file(filename, std::ios::out | std::ios::binary);
    file << output.dump(/* indent= */ 4) << std::endl;
}

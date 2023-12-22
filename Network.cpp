#include "Network.h"
#include "Matrix.h"
#include "json.h"

#define NETWORK_NUM_NEURONS_NAME    "num of neurons"
#define NETWORK_ACTIVATION_FN_NAME  "activation function"
#define NETWORK_SYNAPSE_NAME        "synapse"



Network::Network() = default;

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
        std::function<float(float)> activation_func = activation::sigmoid;
        float b = 0.0f;


        if (network.empty()) {
            add_layer(LayerType::input, num_neurons, activation_func, b);
        }


        else {
            add_layer(LayerType::hidden, num_neurons, activation_func, b);
        }


        auto& synapse_data = layer_data.at(NETWORK_SYNAPSE_NAME);
        synapse.push_back(synapse_data.get<std::vector<std::vector<float>>>());
        i++;
    }

    add_layer(LayerType::output, 1, activation::sigmoid, 0.0f);



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
    std::uniform_real_distribution<float> dis2(0.1f, 1.0f);

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
    std::cout << "><><><><><>><><><><><><><><><><><><><><" << std::endl;
    std::cout << "     NETWORK WAS BUILT SUCCESSFULLY" << std::endl;
    std::cout << "><><><><><>><><><><><><><><><><><><><><" << std::endl;
    create_synapse();
}

void Network::show_network() {
    show_weights();
    show_synapse();

}

void Network::show_synapse() {
    for (int i = 0; i < layers - 1; i++) {
        std::cout << "Synapse weights from Layer " << i + 1 << " to Layer " << i + 2 << ":\n";
        std::cout << "-----------------------" << std::endl;
        for (auto &j: synapse[i]) {
            for (float k: j) {
                std::cout << k << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "-----------------------" << std::endl;
    }
}
void Network::show_weights() {
    std::cout << "Neuron Weights" << std::endl;
    std::cout << "-----------------------" << std::endl;
    size_t max_neurons = 0;
    for (const auto &i: network) {
        max_neurons = std::max(max_neurons, i.size());
    }
    for (size_t i = 0; i < max_neurons; ++i) {
        for (auto &j: network) {
            if (i < j.size()) {
                std::cout << std::fixed << std::setprecision(1) << j[i].weight << " ";
            } else {
                std::cout << "    ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
}


void Network::train(std::vector<std::vector<std::vector<float>>> data, const std::vector<std::vector<float>>& answer, int epochs, float test_data_per) {

    std::cout << "-----------------------" << std::endl;
    std::cout << "    START TRAINING" << std::endl;
    std::cout << "-----------------------" << std::endl;

    for (int epoch = 0; epoch < epochs; ++epoch) {
        //std::cout << "-----------------------" << std::endl;
        //std::cout << "       NEW EPOCH" << std::endl;
        //std::cout << "-----------------------" << std::endl;
        for (auto & j : data) {
            clear_weights();
            std::vector<std::vector<float>> demi_res;

            for (int lay = 0; lay < layers-1; lay++) {

                for (int k = 0; k < network[lay].size(); k++) {
                    if (lay == 0) {
                        network[lay][k].weight = j[k][0];
                    } else {
                        network[lay][k].weight = demi_res[k][0];
                    }
                }

                show_weights();

                size_t k = network[lay + 1].size();
                std::vector<std::vector<float>> local_inp = {};
                for (auto & d : network[lay]) {
                    local_inp.push_back({d.weight});
                }
                if (k == 1) {
                    std::vector<std::vector<float>> semi = {{}};
                    for (auto & h : synapse[lay])
                        semi[0].push_back(h[0]);

                    demi_res = through_layer(Matrix(semi), local_inp, network[lay][0].activationFunction).getData();
                } else {
                    demi_res = through_layer(Matrix(synapse[lay]), local_inp,
                                             network[lay][0].activationFunction).getData();
                }



            for (int neu = 0; neu < network[lay+1].size(); neu++){
                network[lay+1][neu].weight = demi_res[neu][0];
            }


            show_weights();

            }

        }
        std::cout << "-----------------------" << std::endl;
        std::cout << "    FINISH TRAINING" << std::endl;
        std::cout << "-----------------------" << std::endl;

    }


    //for (int i = 0; i < input_data.size(); ++i) {
    // Прямое распространение (получение предсказания)
    // Реализуйте функцию, которая передает входные данные через сеть и получает предсказание

    // Обратное распространение (вычисление ошибки и обновление весов)
    // Реализуйте алгоритм обратного распространения для вычисления ошибки и обновления весов
    // Используйте функцию потерь (например, MSE для задачи регрессии)

    // Вычисление ошибки
    // Обновление весов (градиентный спуск)
    // Реализуйте обновление весов в соответствии с градиентным спуском и скоростью обучения
}



// Вывод ошибки на каждой итерации (опционально)
//std::cout << "Epoch: " << epoch + 1 << ", Error: " << total_error << std::endl;



Matrix Network::through_layer(const Matrix& weights, const std::vector<std::vector<float>>& input,
                              const std::function<float(float)>& activationFunc) {
    Matrix inp(input);
    //weights.showMatrix("WEIGHTS");
    //inp.showMatrix("INP_DATA");
    Matrix res = weights * inp;
    std::vector<std::vector<float>> out = res.getData();
    for (int i = 0; i < res.getData().size(); i++) {
        out[i][0] = activationFunc(res.getData()[i][0]);
    }
    //res.showMatrix("RES");
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

void Network::clear_weights() {
    for(auto & lay : network){
        for (auto & neu : lay){
            neu.weight = 0.0f;
        }
    }
}





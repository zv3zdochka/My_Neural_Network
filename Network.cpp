#include <random>
#include <iostream>
#include <iomanip>
#include "Network.h"
#include "Neurons.h"
#include "Matrix.h"


std::random_device sepsis;
std::default_random_engine gen2(sepsis());
std::uniform_real_distribution<float> dis2(0.0f, 1.0f);


void Network::add_input_layer(int number_of_neurons, const std::function<float(float)> &activation_func, float b) {
    network.emplace_back();
    for (int neuron = 0; neuron < number_of_neurons; neuron++) {
        network[0].emplace_back(1, 0, activation_func);
    }
    layers += 1;


}


void Network::add_hidden_layer(int number_of_neurons, const std::function<float(float)> &activation_func, float b) {
    network.emplace_back();
    for (int neuron = 0; neuron < number_of_neurons; neuron++) {
        network[layers].emplace_back(layers + 1, 0, activation_func);
    }
    layers += 1;
}


void Network::add_output_layer(int number_of_neurons, const std::function<float(float)> &activation_func, float b) {
    network.emplace_back();

    for (int neuron = 0; neuron < number_of_neurons; neuron++) {
        network[network.size() - 1].emplace_back(layers + 1, 0, activation_func);
    }

    layers += 1;
}

void Network::create_synapse() {


    for (size_t i = 0; i < network.size() - 1; ++i) {
        synapse.emplace_back();


        if (network[i + 1].size() != 1) {


            for (size_t j = 0; j < network[i + 1].size(); ++j) {
                std::vector<float> demi_synapse;


                for (size_t k = 0; k < network[i].size(); ++k) {
                    float c_weight = dis2(gen2);
                    demi_synapse.push_back(c_weight);
                }
                synapse[i].push_back(demi_synapse);
                demi_synapse.clear();
            }
        } else {
            for (size_t j = 0; j < network[i].size(); ++j) {
                std::vector<float> demi_synapse;

                for (size_t k = 0; k < network[i + 1].size(); ++k) {
                    float c_weight = dis2(gen2);
                    demi_synapse.push_back(c_weight);
                }
                synapse[i].push_back(demi_synapse);
                demi_synapse.clear();
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


void
Network::train(std::vector<std::vector<std::vector<float>>> data, std::vector<std::vector<float>> answer, int epochs,
               float test_data_per) {
    //training message
    for (int epoch = 0; epoch < epochs; ++epoch) {
        std::cout << "-----------------------" << std::endl;
        std::cout << "       NEW EPOCH" << std::endl;
        std::cout << "-----------------------" << std::endl;
        for (int j = 0; j < data.size(); j++) {
            std::cout << "-----------------------" << std::endl;
            std::cout << "     NEW KNOWLEDGE" << std::endl;
            std::cout << "-----------------------" << std::endl;
            std::vector<std::vector<float>> demi_res;

            for (int lay = 0; lay < layers - 1; lay++) {

                for (int k = 0; k < network[lay].size(); k++) {
                    if (lay == 0) {
                        network[lay][k].weight = data[j][k][0];
                    } else {
                        network[lay][k].weight = demi_res[k][0];
                    }
                }

                show_weights();

                int k = network[lay + 1].size();
                std::vector<std::vector<float>> local_inp = {};
                for (int d = 0; d < network[lay].size(); d++) {
                    local_inp.push_back({network[lay][d].weight});
                }
                if (k == 1) {
                    std::vector<std::vector<float>> semi = {{}};
                    for (int h = 0; h < synapse[lay].size(); h++)
                        semi[0].push_back(synapse[lay][h][0]);

                    demi_res = through_layer(Matrix(semi), local_inp, network[lay][0].activationFunction).getData();
                } else {
                    demi_res = through_layer(Matrix(synapse[lay]), local_inp,
                                             network[lay][0].activationFunction).getData();
                }

                Matrix(demi_res).showMatrix();
            for (int neu = 0; neu < network[lay].size(); neu++){
                for (int dat = 0; dat < demi_res.size()-1; dat++){
                    network[lay][neu].weight = demi_res[dat][0];
                }
            }

            show_weights();
            for (int i = 0; i < network[lay].size(); i++){
                std::cout << network[lay][i].weight << "//" << std::endl;
            }



            }

        }
        std::cout << "FINISH TRAINING";

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



Matrix Network::through_layer(Matrix weights, std::vector<std::vector<float>> input,
                              std::function<float(float)> activationFunc) {
    Matrix inp(input);
    weights.showMatrix("WEIGHTS");
    inp.showMatrix("INP_DATA");
    Matrix res = weights * inp;
    std::vector<std::vector<float>> out = res.getData();
    for (int i = 0; i < res.getData().size(); i++) {
        out[i][0] = activationFunc(res.getData()[i][0]);
    }
    res.showMatrix("RES");
    return res;
}

void Network::save() {

}

void Network::read() {

}





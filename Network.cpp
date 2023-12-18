#include <random>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Network.h"
#include "Neurons.h"
#include "Matrix.h"



std::random_device sepsis;
std::default_random_engine gen2(sepsis());
std::uniform_real_distribution<float> dis2(0.1f, 10.0f);


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


void Network::train(std::vector<std::vector<std::vector<float>>> data, std::vector<std::vector<float>> answer, int epochs, float test_data_per) {
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



Matrix Network::through_layer(Matrix weights, std::vector<std::vector<float>> input) {
    Matrix inp(input);
    Matrix res = weights * inp;
    return res;
}


void Network::save(const std::string& filename){
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << '\n';
        return;
    }

    // Запись числа слоев
    file << "num of layers " << layers << '\n';
    file << "-----------------\n";

    // Запись синапсов
    for (int i = 0; i < layers - 1; ++i) {
        file << "layer num: neurons " << network[i].size() << "; activation func\n";
        file << "-----------------\n";

        for (const auto & j : synapse[i]) {
            file << "weights: ";
            for (float k : j) {
                file << k << ' ';
            }
            file << '\n';
        }
        file << "-----------------\n";
    }


    file << "extra data\n";

    file.close();
}


std::tuple<int, std::vector<std::vector<Neuron>>, std::vector<std::vector<std::vector<float>>>> Network::read(const std::string& filename) {
    std::ifstream file;
    file.open(filename.c_str());

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << '\n';
        return std::make_tuple(0, std::vector<std::vector<Neuron>>(), std::vector<std::vector<std::vector<float>>>());
    }

    // Чтение общего числа слоев
    std::string line;
    std::getline(file, line);
    size_t pos = line.find("num of layers ");
    if (pos != std::string::npos) {
        layers = std::stoi(line.substr(pos + 14));
    }

    // Пропустить разделитель
    std::getline(file, line);

    // Чтение информации о каждом слое и весах синапсов
    for (int i = 0; i < layers; ++i) {
        std::getline(file, line);  // Пропустить "layer num: neurons n; activation func"
        std::getline(file, line);  // Пропустить "-----------------"

        for (size_t j = 0; j < synapse[i].size(); ++j) {
            std::getline(file, line);  // Пропустить "weights: w11 w21 ..."
            // Обработка строки и заполнение synapse[i][j]
        }

        std::getline(file, line);  // Пропустить "-----------------"
    }

    // Пропустить "extra data" и читать дополнительные данные (если есть)
    std::getline(file, line);
    // Обработка дополнительных данных

    file.close();
    return std::make_tuple(layers, network, synapse);
}






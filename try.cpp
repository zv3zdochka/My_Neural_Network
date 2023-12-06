#include "Neurons.h"
#include <vector>
#include "Activations.h"
#include <iostream>
#include <random>

int main() {
    int layer_num = 3;
    int neurons_num = 2;

    std::vector<std::vector<Neuron>> network(layer_num);
    std::vector<std::vector<float>> weights(layer_num - 1);

    std::random_device weight;
    std::mt19937 gen1(weight());


    std::random_device sepsis;
    std::default_random_engine gen2(sepsis());


    std::uniform_real_distribution<float> dis1(1.0f, 5.0f);
    std::uniform_real_distribution<float> dis2(0.1f, 10.0f);






    for (int i = 0; i < layer_num; i++) {
        for (int j = 0; j < neurons_num; j++) {
            network[i].push_back(Neuron(i + 1, dis1(gen1), Activation::sigmoid));

        }
    }

    for (int i = 0; i < layer_num - 1; i++){
        for (int j = 0; j < neurons_num; j++){
            weights[i].push_back(dis2(gen2));
        }
    }



    // print
    for (int i = 0; i < layer_num; i++) {
        std::cout << "Layer " << i + 1 << ":\n";
        for (int j = 0; j < neurons_num; j++) {
            Neuron current_neuron = network[i][j];
            std::cout << "Neuron " << j + 1 << " in Layer " << i + 1 << ":\n";
            std::cout << "Weight: " << current_neuron.getWeight() << "\n"   ;

            // std::cout << "Activation Function: " << current_neuron.getActivationFunction() << "\n";
            std::cout << "----------------\n";
        }
        std::cout << "\n";
    }


    for (int i = 0; i < layer_num - 1; i++) {
        std::cout << "Sepsis " << i + 1 << " и " << i + 2 << ":\n";
        for (int j = 0; j < neurons_num; j++) {
            std::cout << "Weight " << j + 1 << ": " << weights[i][j] << "\n";
        }
        std::cout << "----------------\n";
    }








    return 0;
};



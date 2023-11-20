#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

class Neurons {
public:
    class Input_Neuron {
    public:
        Input_Neuron(const int layer_num, float weight, std::function<float(float)> activationFunc)
                : layer_number(layer_num), weight(weight), activationFunction(activationFunc) {

        }

        float computeActivation(float input) {
            return activationFunction(input);
        }

        float weight;
        int layer_number;
        std::function<float(float)> activationFunction;
    };

    class Hidden_Neuron {
    public:
        Hidden_Neuron(const int layer_num, float weight, std::function<float(float)> activationFunc)
                : layer_number(layer_num), weight(weight), activationFunction(activationFunc) {

        }

        float computeActivation(float input) {
            return activationFunction(input);
        }

        float weight;
        int layer_number;
        std::function<float(float)> activationFunction;
    };

    class Output_Neuron {
    public:
        Output_Neuron(const int layer_num, float weight, std::function<float(float)> activationFunc)
                : layer_number(layer_num), weight(weight), activationFunction(activationFunc) {

        }

        float computeActivation(float input) {
            return activationFunction(input);
        }

        float weight;
        int layer_number;
        std::function<float(float)> activationFunction;
    };

    class NeuralNetwork {
    private:
        std::vector<std::vector<Input_Neuron>> layers; // Слои нейронов

    public:
        // Метод добавления входного слоя
        void addInputLayer(int num_neurons) {
            std::vector<Input_Neuron> input_layer;
            // Создание входных нейронов и добавление их в слой
            for (int i = 0; i < num_neurons; ++i) {
                Input_Neuron neuron(0, 0.0, /* ваша функция активации */);
                input_layer.push_back(neuron);
            }
            layers.push_back(input_layer);
        }

        // Метод добавления скрытого слоя
        void addHiddenLayer(int num_neurons) {
            std::vector<Input_Neuron> hidden_layer;
            // Создание скрытых нейронов и добавление их в слой
            for (int i = 0; i < num_neurons; ++i) {
                Input_Neuron neuron(0, 0.0, /* ваша функция активации */);
                hidden_layer.push_back(neuron);
            }
            layers.push_back(hidden_layer);
        }

        // Метод добавления выходного слоя
        void addOutputLayer(int num_neurons) {
            std::vector<Input_Neuron> output_layer;
            // Создание выходных нейронов и добавление их в слой
            for (int i = 0; i < num_neurons; ++i) {
                Input_Neuron neuron(0, 0.0, /* ваша функция активации */);
                output_layer.push_back(neuron);
            }
            layers.push_back(output_layer);
        }

        // Другие методы для обучения, прогнозирования и т.д.
        // Например, метод обратного распространения ошибки, метод обновления весов и т.д.
    };
};

int main() {
    // Пример использования:
    Neurons::NeuralNetwork neuralNetwork;

    // Добавление слоев: входной, скрытый, выходной
    neuralNetwork.addInputLayer(3);
    neuralNetwork.addHiddenLayer(4);
    neuralNetwork.addOutputLayer(2);

    // Теперь у вас есть основа для нейросети с различными слоями и нейронами.
    // Вы можете добавить методы обучения, прямого и обратного распространения и другие функции
    // для реализации обучения нейросети.

    return 0;
}

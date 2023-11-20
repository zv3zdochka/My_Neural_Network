#include <functional>
#include <utility>

class Neurons {
public:
    class Input_Neuron {
    public:
        Input_Neuron(float weight, std::function<float(float)> activationFunc)
                : weight(weight), activationFunction(std::move(activationFunc)) {

        }

        float computeActivation(float input) {
            return activationFunction(input);
        }

        float weight;
        int layer_number = 0;
        std::function<float(float)> activationFunction;
    };

    class Hidden_Neuron {
    public:
        Hidden_Neuron(int layer_num, float weight, std::function<float(float)> activationFunc)
                : layer_number(layer_num), weight(weight), activationFunction(std::move(activationFunc)) {

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
        Output_Neuron(int layer_num, float weight, std::function<float(float)> activationFunc)
                : layer_number(layer_num), weight(weight), activationFunction(std::move(activationFunc)) {

        }

        float computeActivation(float input) {
            return activationFunction(input);
        }

        float weight;
        int layer_number;
        std::function<float(float)> activationFunction;
    };
};

#include <cmath>
#include "Utils.h"
#include "Neurons.h"

namespace Derivatives {

    float sigmoid_derivative(float x) {
        float exp_x = std::exp(x);
        return static_cast<float>(exp_x / std::pow(exp_x + 1.0f, 2));
    }

    float fast_sigmoid_derivative(float x) {
        return static_cast<float>(1.0f / (std::pow(1.0f + std::abs(x), 2)));
    }


    float silu_derivative(float x) {
        float exp_x = std::exp(x);
        return static_cast<float>((std::exp(2 * x) + exp_x + x * exp_x) / std::pow(exp_x + 1.0f, 2));
    }

    float tanh_derivative(float x) {
        float exp_2x = std::exp(2 * x);
        return static_cast<float>((4 * exp_2x) / std::pow(exp_2x, 2));
    }

}
void print_data(const std::vector<std::vector<float>>& data) {
    for (const auto& row : data) {
        for (const auto& val : row) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void Data_Worker::shuffle_dataset(std::vector<std::vector<std::vector<float>>> &input_data,
                                  std::vector<std::vector<float>> &output_data) {
    std::vector<std::pair<std::vector<std::vector<float>>, std::vector<float>>> combined_data;
    for (size_t i = 0; i < input_data.size(); ++i) {
        combined_data.push_back({input_data[i], output_data[i]});
    }

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(combined_data), std::end(combined_data), rng);


    std::cout << "Shuffled input data:" << std::endl;
    for (const auto &combined : combined_data) {
        for (const auto &input_row : combined.first) {
            for (const auto &input : input_row) {
                std::cout << input;

                std::cout << "| ";
            }
            std::cout << "    ";
        }
        std::cout << std::endl;
    }

    std::cout << "Shuffled output data:" << std::endl;
    for (const auto &combined : combined_data) {
        for (float val : combined.second) {
            std::cout << val << " ";
        }
        std::cout << "    ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < combined_data.size(); ++i) {
        input_data[i] = combined_data[i].first;
        output_data[i] = combined_data[i].second;
    }
}

void Data_Worker::check_data(std::vector<std::vector<float>> input_data,
                             std::vector<std::vector<float>> output_data,
                             std::vector<std::vector<Neuron>> net) {
    for (int i = 0; i < input_data.size(); i++) {
        if (input_data[i].size() != net[0].size()) {
            throw std::invalid_argument("The number of neurons should match the number of elements in the input data.");
        } else if (output_data[i].size() != net[net.size()-1].size()) {
            throw std::invalid_argument(
                    "The number of neurons in the output layer should match the number of elements in the output data.");
        }
    }
}

std::vector<std::vector<float>> Data_Worker::min_max_normalisation(
        std::vector<std::vector<float>> data) {

    std::vector<float> all_input_values;
    std::vector<float> all_output_values;

    for (const auto &input_row : data) {
        for (const auto &input : input_row) {
            all_input_values.push_back(input);
        }
    }

    float min_val = *std::min_element(all_input_values.begin(), all_input_values.end());
    float max_val = *std::max_element(all_input_values.begin(), all_input_values.end());
    min_val /= 1.01;
    max_val *= 1.01;
    for (auto &input_row : data) {
        for (auto &input : input_row) {
            input = (input - min_val) / (max_val - min_val);
        }
    }

    return data;
}
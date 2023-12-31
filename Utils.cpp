#include <cmath>
#include "Utils.h"


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




void Data_Worker::readDataset(const std::string &filename, std::vector<std::vector<std::vector<float>>> &input_data,
                             std::vector<std::vector<float>> &output_data) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open dataset file");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::vector<float>> input_row;
        float value;

        while (iss >> value) {
            input_row.push_back({value});
        }

        if (!input_row.empty()) {
            float output_value = input_row.back().front();
            input_row.pop_back();
            std::vector<float> output_vector = {output_value};
            output_data.push_back(output_vector);
        }

        input_data.push_back(input_row);
    }
}

void Data_Worker::normalize_dataset(std::vector<std::vector<std::vector<float>>> &input_data,
                                   std::vector<std::vector<float>> &output_data) {

    std::vector<float> all_input_values;
    std::vector<float> all_output_values;

    for (const auto &input_row: input_data) {
        for (const auto &input: input_row) {
            all_input_values.insert(all_input_values.end(), input.begin(), input.end());
        }
    }

    float min_val = *std::min_element(all_input_values.begin(), all_input_values.end());
    float max_val = *std::max_element(all_input_values.begin(), all_input_values.end());

    for (auto &input_row: input_data) {
        for (auto &input: input_row) {
            for (float &val: input) {
                val = (val - min_val) / (max_val - min_val);
            }
        }
    }

    for (const auto &input_row: input_data) {
        for (const auto &input: input_row) {
            all_output_values.insert(all_output_values.end(), input.begin(), input.end());
        }
    }

    float min_va = *std::min_element(all_output_values.begin(), all_output_values.end());
    float max_va = *std::max_element(all_output_values.begin(), all_output_values.end());

    for (auto &output_row: output_data) {
        for (float &val: output_row) {
            val = (val - min_va) / (max_va - min_va);
        }
    }


//    std::cout << "Normalized input data:" << std::endl;
//    for (const auto &input_row : input_data) {
//        for (const auto &input : input_row) {
//            for (float val : input) {
//                std::cout << val << " ";
//            }
//            std::cout << "| ";
//        }
//        std::cout << std::endl;
//    }
//
//    std::cout << "Normalized output data:" << std::endl;
//    for (const auto &output_row : output_data) {
//        for (float val : output_row) {
//            std::cout << val << " ";
//        }
//        std::cout << std::endl;
//    }
}

void Data_Worker::shuffle_dataset(std::vector<std::vector<std::vector<float>>> &input_data,
                                 std::vector<std::vector<float>> &output_data) {
    std::vector<std::pair<std::vector<std::vector<float>>, std::vector<float>>> combined_data;
    for (size_t i = 0; i < input_data.size(); ++i) {
        combined_data.push_back({input_data[i], output_data[i]});
    }

    std::shuffle(combined_data.begin(), combined_data.end(), std::default_random_engine());


//    std::cout << "Shuffled input data:" << std::endl;
//    for (const auto &combined : combined_data) {
//        for (const auto &input_row : combined.first) {
//            for (const auto &input : input_row) {
//                std::cout << input;
//
//                std::cout << "| ";
//            }
//            std::cout << "    ";
//        }
//        std::cout << std::endl;
//    }
//
//    std::cout << "Shuffled output data:" << std::endl;
//    for (const auto &combined : combined_data) {
//        for (float val : combined.second) {
//            std::cout << val << " ";
//        }
//        std::cout << "    ";
//    }
//    std::cout << std::endl;
//
//    for (size_t i = 0; i < combined_data.size(); ++i) {
//        input_data[i] = combined_data[i].first;
//        output_data[i] = combined_data[i].second;
//    }
}


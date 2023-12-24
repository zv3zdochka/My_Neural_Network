#include <iostream>
#include <vector>
#include <iomanip>

#include "DataUtils.h"

void normalize_input(std::vector<std::vector<std::vector<float>>>& vec) {
    for (size_t i = 0; i < vec[0][0].size(); ++i) {

        float min_val = vec[0][0][i];
        float max_val = vec[0][0][i];
        for (auto & j : vec) {
            for (auto & k : j) {
                min_val = std::min(min_val, k[i]);
                max_val = std::max(max_val, k[i]);
            }
        }


        for (auto & j : vec) {
            for (auto & k : j) {
                k[i] = ((k[i] - min_val) / (max_val - min_val));
            }
        }
    }
}

void normalize_output(std::vector<std::vector<float>>& vec) {
    for (size_t i = 0; i < vec[0].size(); ++i) {
        // Find min and max values for the current dimension
        float min_val = vec[0][i];
        float max_val = vec[0][i];
        for (size_t j = 0; j < vec.size(); ++j) {
            min_val = std::min(min_val, vec[j][i]);
            max_val = std::max(max_val, vec[j][i]);
        }

        // Apply normalization formula to each element in the current dimension
        for (size_t j = 0; j < vec.size(); ++j) {
            vec[j][i] = ((vec[j][i] - min_val) / (max_val - min_val)) * (1.0f - 0.0f) + 0.0f;
        }
    }
}

void display_data(const std::vector<std::vector<std::vector<float>>>& input_data, const std::vector<std::vector<float>>& output_data) {
    std::cout << "Input Data:\n";
    for (const auto& input_vector : input_data) {
        for (const auto& inner_vector : input_vector) {
            for (float val : inner_vector) {
                std::cout <<std::fixed << std::setprecision(5) << val << ' ';
            }
        }
        std::cout << '\n';
    }

    std::cout << "\nOutput Data:\n";
    for (const auto& output_vector : output_data) {
        for (float val : output_vector) {
            std::cout << std::fixed <<std::setprecision(5)<< val << ' ';
        }
        std::cout << '\n';
    }
}

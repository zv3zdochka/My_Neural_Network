#include <iostream>
#include <vector>
#include <iomanip>

#include "DataUtils.h"

std::vector<std::vector<std::vector<float>>> normalize_input(std::vector<std::vector<float>>& vec) {
    std::vector<std::vector<std::vector<float>>> normalized_data;

    for (size_t i = 0; i < vec[0].size(); ++i) {
        float min_val = vec[0][i];
        float max_val = vec[0][i];

        for (const auto & j : vec) {
            min_val = std::min(min_val, j[i]);
            max_val = std::max(max_val, j[i]);
        }

        std::vector<std::vector<float>> normalized_column;
        for (const auto & j : vec) {
            float normalized_value = (j[i] - min_val) / (max_val - min_val);
            normalized_column.push_back({normalized_value});
        }

        normalized_data.push_back(normalized_column);
    }

    return normalized_data;
}

std::vector<std::vector<float>> normalize_output(std::vector<float>& vec) {
    float min_val = vec[0];
    float max_val = vec[0];

    for (float i : vec) {
        min_val = std::min(min_val, i);
        max_val = std::max(max_val, i);
    }

    std::vector<std::vector<float>> normalized_data;
    for (float i : vec) {
        float normalized_value = (i - min_val) / (max_val - min_val);
        normalized_data.push_back({normalized_value});
    }

    return normalized_data;
}

void display_data(const std::vector<std::vector<std::vector<float>>>& input_data, const std::vector<std::vector<float>>& output_data) {
    std::cout << "Input Data:\n";
    for (const auto& input_column : input_data) {
        for (const auto& input_vector : input_column) {
            std::cout << std::fixed << std::setprecision(5) << input_vector[0] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "\nOutput Data:\n";
    for (const auto& output_vector : output_data) {
        for (float val : output_vector) {
            std::cout << std::fixed << std::setprecision(5) << val << ' ';
        }
        std::cout << '\n';
    }
}

#include "DataUtils.h"

#include <random>

void DataUtils::readDataset(const std::string& filename, std::vector<std::vector<std::vector<float>>>& input_data,
                            std::vector<std::vector<float>>& output_data) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open dataset file");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::vector<float>> input_row;
        float value;

        // Read input values
        while (iss >> value) {
            input_row.push_back({value});
        }

        // Read output value
        if (!input_row.empty()) {
            float output_value = input_row.back().front();
            input_row.pop_back(); // Remove the output value from input_row
            output_data.push_back({output_value});
        }

        input_data.push_back(input_row);
    }
}


void DataUtils::normalizeData(std::vector<std::vector<std::vector<float>>>& data) {
    for (size_t i = 0; i < data[0].size(); ++i) {
        float min_val = data[0][i][0];
        float max_val = data[0][i][0];

        // Find min and max values
        for (size_t j = 1; j < data.size(); ++j) {
            min_val = std::min(min_val, data[j][i][0]);
            max_val = std::max(max_val, data[j][i][0]);
        }

        // Normalize data
        for (size_t j = 0; j < data.size(); ++j) {
            data[j][i][0] = (data[j][i][0] - min_val) / (max_val - min_val);
        }
    }
}

void DataUtils::shuffleData(std::vector<std::vector<std::vector<float>>>& input_data,
                            std::vector<std::vector<float>>& output_data) {
    // Generate random indices
    std::vector<int> indices(input_data.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), std::mt19937(std::random_device()()));

    // Shuffle input_data and output_data using the same random indices
    std::vector<std::vector<std::vector<float>>> shuffled_input_data(input_data.size());
    std::vector<std::vector<float>> shuffled_output_data(output_data.size());

    for (size_t i = 0; i < indices.size(); ++i) {
        shuffled_input_data[i] = input_data[indices[i]];
        shuffled_output_data[i] = output_data[indices[i]];
    }

    // Update input_data and output_data
    input_data = shuffled_input_data;
    output_data = shuffled_output_data;

}

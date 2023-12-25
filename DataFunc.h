#pragma once

#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <numeric>
#include <iostream>
#include <random>
#include <sstream>
#include <iterator>


class DataLoader {
public:
    static void readDataset(const std::string& filename, std::vector<std::vector<std::vector<float>>>& input_data,
                               std::vector<std::vector<float>>& output_data);

    static void normalize_dataset(std::vector<std::vector<std::vector<float>>> &input_data,
                                  std::vector<std::vector<float>> &output_data);

    static void shuffle_dataset(std::vector<std::vector<std::vector<float>>> &input_data,
                                std::vector<std::vector<float>> &output_data);

};
#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <random>

class DataUtils {
public:
    static void readDataset(const std::string& filename, std::vector<std::vector<std::vector<float>>>& input_data,
                            std::vector<std::vector<float>>& output_data);

    static void normalizeData(std::vector<std::vector<std::vector<float>>>& data);

    static void shuffleData(std::vector<std::vector<std::vector<float>>>& input_data,
                            std::vector<std::vector<float>>& output_data);
};
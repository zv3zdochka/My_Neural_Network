#pragma once

/**
 * @file DataFunc.h
 * @brief Header file containing a data loading utility class for handling datasets.
 */

#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <numeric>
#include <iostream>
#include <random>
#include <sstream>
#include <iterator>

/**
 * @class DataLoader
 * @brief Utility class for reading, normalizing, and shuffling datasets.
 */
class DataLoader {
public:
    /**
     * @brief Read a dataset from a file.
     * @param filename Path to the dataset file.
     * @param input_data Vector to store input data.
     * @param output_data Vector to store output data.
     */
    static void readDataset(const std::string& filename, std::vector<std::vector<std::vector<float>>>& input_data,
                            std::vector<std::vector<float>>& output_data);

    /**
     * @brief Normalize a dataset.
     * @param input_data Input data to be normalized.
     * @param output_data Output data to be normalized.
     */
    static void normalize_dataset(std::vector<std::vector<std::vector<float>>> &input_data,
                                  std::vector<std::vector<float>> &output_data);

    /**
     * @brief Shuffle a dataset randomly.
     * @param input_data Input data to be shuffled.
     * @param output_data Output data to be shuffled.
     */
    static void shuffle_dataset(std::vector<std::vector<std::vector<float>>> &input_data,
                                std::vector<std::vector<float>> &output_data);

};


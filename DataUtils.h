#pragma once


#include <vector>

void normalize_input(std::vector<std::vector<std::vector<float>>>& vec);

void normalize_output(std::vector<std::vector<float>>& vec);

void display_data(const std::vector<std::vector<std::vector<float>>>& input_data, const std::vector<std::vector<float>>& output_data);

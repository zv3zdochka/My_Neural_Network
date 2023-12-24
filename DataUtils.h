#pragma once


#include <vector>

std::vector<std::vector<std::vector<float>>> normalize_input(std::vector<std::vector<float>>& vec);
std::vector<std::vector<float>> normalize_output(std::vector<float>& vec);

void display_data(const std::vector<std::vector<std::vector<float>>>& input_data, const std::vector<std::vector<float>>& output_data);

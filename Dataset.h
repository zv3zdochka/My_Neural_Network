#pragma once
#include <vector>

class Dataset {
public:
    std::vector<std::vector<float>> input_data;
    std::vector<std::vector<float>> output_data;
    Dataset(std::vector<std::vector<float>>, std::vector<std::vector<float>>);
};




#include <iostream>
#include <vector>
#include <cmath>

std::vector<double> softmax(const std::vector<double> &input) {
    std::vector<double> result;
    double sum = 0.0;
    double maxInput = *std::max_element(input.begin(), input.end());

    for (size_t i = 0; i < input.size(); ++i) {
        double exponent = std::exp(input[i] - maxInput);
        result.push_back(exponent);
        sum += exponent;
    }

    for (size_t i = 0; i < result.size(); ++i) {
        result[i] /= sum;
    }

    return result;
}

int main() {
    std::vector<double> input = {2.0, 3.0, 1.0};
    std::vector<double> output = softmax(input);

    std::cout << "Softmax result: ";
    for (size_t i = 0; i < output.size(); ++i) {
        std::cout << output[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
//
// Created by batsi on 20.11.2023.
//

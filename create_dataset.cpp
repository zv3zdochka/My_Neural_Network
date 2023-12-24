#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    std::string file_path = R"(C:\Users\batsi\OneDrive\Documents\CLionProjects\My_own_Neural_Network\fruits_dataset.txt)";

    std::ofstream dataset(file_path);
    if (!dataset.is_open()) {
        std::cout << "Unable to create dataset file!" << std::endl;
        return 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> apple_diameter_dist(7.0f, 15.0f);
    std::uniform_real_distribution<float> apple_weight_dist(100.0f, 300.0f);

    std::uniform_real_distribution<float> orange_diameter_dist(14.0f, 20.0f);
    std::uniform_real_distribution<float> orange_weight_dist(250.0f, 500.0f);

    const int total_samples = 500;

    std::vector<std::string> data_lines;

    for (int i = 0; i < total_samples / 2; ++i) {
        float apple_diameter = apple_diameter_dist(gen);
        float apple_weight = apple_weight_dist(gen);
        data_lines.push_back(std::to_string(apple_diameter) + " " + std::to_string(apple_weight) + " 0.0");

        float orange_diameter = orange_diameter_dist(gen);
        float orange_weight = orange_weight_dist(gen);
        data_lines.push_back(std::to_string(orange_diameter) + " " + std::to_string(orange_weight) + " 1.0");
    }

    std::shuffle(data_lines.begin(), data_lines.end(), gen);

    for (const std::string &line: data_lines) {
        dataset << line << "\n";
    }

    dataset.close();
    std::cout << "Dataset created successfully!" << std::endl;
    return 0;
}

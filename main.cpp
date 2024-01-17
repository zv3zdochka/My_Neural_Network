#include "Core.h"


int main() {
    std::ifstream file(R"(C:\Users\batsi\OneDrive\Documents\CLionProjects\My_own_Neural_Network\Iris.csv)");

    if (!file.is_open()) {
        std::cerr << "Unable to open the file.\n";
        return 1;
    }

    std::vector<std::vector<float>> input;
    std::vector<std::vector<float>> output;

    std::string line;

    // Read the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        std::vector<float> row_input;
        std::vector<float> row_output(3, 0.0);

        // Read Id and Species
        std::getline(iss, token, ','); // Id
        std::getline(iss, token, ','); // SepalLengthCm
        row_input.push_back(std::stof(token));
        std::getline(iss, token, ','); // SepalWidthCm
        row_input.push_back(std::stof(token));
        std::getline(iss, token, ','); // PetalLengthCm
        row_input.push_back(std::stof(token));
        std::getline(iss, token, ','); // PetalWidthCm
        row_input.push_back(std::stof(token));
        std::getline(iss, token, ','); // Species

        if (token == "Iris-setosa") {
            row_output[0] = 1.0;
        } else if (token == "Iris-versicolor") {
            row_output[1] = 1.0;
        } else if (token == "Iris-virginica") {
            row_output[2] = 1.0;
        }

        input.push_back(row_input);
        output.push_back(row_output);
    }
    std::filesystem::current_path("..");

    Network net;
    net.add_layer(LayerType::input, 4, FunctionType::sigmoid);
    net.add_layer(LayerType::hidden, 3, FunctionType::sigmoid);
    net.add_layer(LayerType::hidden, 5, FunctionType::sigmoid);
    net.add_layer(LayerType::output, 3, FunctionType::sigmoid);
    net.build();
    net.show_network();
    net.save("base.json");

//    std::vector<std::vector<float>> input_data = {
//            {1.0f, 0.0f},
//            {1.0f, 1.0f},
//            {0.0f, 1.0f},
//            {0.0f, 0.0f},
//    };
//
//
//    std::vector<std::vector<float>> output_data = {
//            {0.0f},
//            {1.0f},
//            {1.0f},
//            {1.0f},
//    };

    const int epochs = 3000;


    net.train(input, output, Normalisation::without_normalisation, epochs, 1, 0.1);

    net.work({{5.1, 3.5, 1.3, 0.2}});


    return 0;
}

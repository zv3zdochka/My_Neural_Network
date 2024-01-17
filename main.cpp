#include "Core.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

// ”ã­ªæ¨ï ¤«ï ¯à¥®¡à §®¢ ­¨ï â¥ªáâ®¢ëå ª« áá®¢ ¢ ç¨á«®¢ë¥ §­ ç¥­¨ï
int getClassNumber(const std::string &className) {
    static std::map<std::string, float> classMap = {
            {"Iris-setosa",     0.33},
            {"Iris-versicolor", 0.66},
            {"Iris-virginica",  0.99}
    };

    auto it = classMap.find(className);
    if (it != classMap.end()) {
        return it->second;
    } else {
        return -1; // ‚®§¢à é ¥¬ -1 ¢ á«ãç ¥ ­¥®¯à¥¤¥«¥­­®£® ª« áá 
    }
}

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
    std::ifstream file(
            R"(C:\Users\batsi\OneDrive\Documents\CLionProjects\My_own_Neural_Network\Iris.csv)"); // ‡ ¬¥­¨â¥ "example.csv" ­  ¨¬ï ¢ è¥£® CSV ä ©« 

    if (!file.is_open()) {
        std::cout << "¥ ã¤ «®áì ®âªàëâì ä ©«." << std::endl;
        return 1;
    }

    std::vector<std::vector<float>> input; // ‚¥ªâ®à ¤«ï åà ­¥­¨ï ç¨á«®¢ëå ¤ ­­ëå
    std::vector<float> output; // ‚¥ªâ®à ¤«ï åà ­¥­¨ï ç¨á«®¢ëå §­ ç¥­¨© ª« áá®¢

    std::string line;
    bool headerSkipped = false;
    while (std::getline(file, line)) {
        if (!headerSkipped) {
            headerSkipped = true;
            continue; // à®¯ãáâ¨âì ¯¥à¢ãî áâà®ªã á § £®«®¢ª ¬¨
        }

        std::vector<float> rowInput;
        std::stringstream ss(line);
        std::string cell;
        int classNumber = -1;

        int col = 0;
        while (std::getline(ss, cell, ',')) {
            if (col < 4) { // ¥à¢ë¥ ç¥âëà¥ áâ®«¡æ  á®¤¥à¦ â ç¨á«®¢ë¥ ¤ ­­ë¥
                rowInput.push_back(std::stod(cell));
            } else if (col == 4) { // ïâë© áâ®«¡¥æ á®¤¥à¦¨â â¥ªáâ®¢ë© ª« áá
                classNumber = getClassNumber(cell);
            }
            col++;
        }

        if (classNumber != -1) {
            input.push_back(rowInput);
            output.push_back(classNumber);
        }
    }

    file.close();

    // ‚ë¢®¤ §­ ç¥­¨© ¤«ï ¯à®¢¥àª¨
    std::cout << "Input:" << std::endl;
    for (const auto &row: input) {
        for (const auto &value: row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Output:" << std::endl;
    for (const auto &value: output) {
        std::cout << value << std::endl;
    }


    std::vector<std::vector<float>> out = {};
    for (int i = 0; i < output.size(); i++) {
        out.push_back({output[i]});
    }


    Network net;
    net.add_layer(LayerType::input, 4, FunctionType::sigmoid);

    net.build();
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



    return 0;
}

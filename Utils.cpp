#include <cmath>
#include "Utils.h"
#include "Neurons.h"

namespace Derivatives {

    float sigmoid_derivative(float x) {
        float exp_x = std::exp(x);
        return static_cast<float>(exp_x / std::pow(exp_x + 1.0f, 2));
    }

    float fast_sigmoid_derivative(float x) {
        return static_cast<float>(1.0f / (std::pow(1.0f + std::abs(x), 2)));
    }


    float silu_derivative(float x) {
        float exp_x = std::exp(x);
        return static_cast<float>((std::exp(2 * x) + exp_x + x * exp_x) / std::pow(exp_x + 1.0f, 2));
    }

    float tanh_derivative(float x) {
        float exp_2x = std::exp(2 * x);
        return static_cast<float>((4 * exp_2x) / std::pow(exp_2x, 2));
    }

}


void Data_Worker::shuffle_dataset(std::vector<std::vector<std::vector<float>>> &input_data,
                                  std::vector<std::vector<float>> &output_data) {
    std::vector<std::pair<std::vector<std::vector<float>>, std::vector<float>>> combined_data;
    for (size_t i = 0; i < input_data.size(); ++i) {
        combined_data.emplace_back(input_data[i], output_data[i]);
    }

    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(combined_data), std::end(combined_data), rng);

    for (size_t i = 0; i < combined_data.size(); ++i) {
        input_data[i] = combined_data[i].first;
        output_data[i] = combined_data[i].second;
    }
}


void Data_Worker::check_data(std::vector<std::vector<float>> input_data,
                             std::vector<std::vector<float>> output_data,
                             std::vector<std::vector<Neuron>> net) {
    for (int i = 0; i < input_data.size(); i++) {
        if (input_data[i].size() != net[0].size()) {
            throw std::invalid_argument("The number of neurons should match the number of elements in the input data.");
        } else if (output_data[i].size() != net[net.size() - 1].size()) {
            throw std::invalid_argument(
                    "The number of neurons in the output layer should match the number of elements in the output data.");
        }
    }
}

std::vector<std::vector<float>> Data_Worker::min_max_normalisation(
        std::vector<std::vector<float>> data) {

    std::vector<float> all_input_values;
    std::vector<float> all_output_values;

    for (const auto &input_row: data) {
        for (const auto &input: input_row) {
            all_input_values.push_back(input);
        }
    }

    float min_val = *std::min_element(all_input_values.begin(), all_input_values.end());
    float max_val = *std::max_element(all_input_values.begin(), all_input_values.end());
    min_val /= 1.01;
    max_val *= 1.01;
    for (auto &input_row: data) {
        for (auto &input: input_row) {
            input = (input - min_val) / (max_val - min_val);
        }
    }

    return data;
}

std::vector<std::vector<float>> Data_Worker::zScoreNormalization(std::vector<std::vector<float>> data) {

    int rows = data.size();
    int cols = data[0].size();
    std::vector<double> mean(cols, 0.0);
    std::vector<double> stdDev(cols, 0.0);

    for (int j = 0; j < cols; ++j) {
        double sum = 0.0;
        for (int i = 0; i < rows; ++i) {
            sum += data[i][j];
        }
        mean[j] = sum / rows;

        double squaredSum = 0.0;
        for (int i = 0; i < rows; ++i) {
            squaredSum += pow(data[i][j] - mean[j], 2);
        }
        stdDev[j] = sqrt(squaredSum / rows);
    }


    std::vector<std::vector<float>> normalizedData(rows, std::vector<float>(cols, 0.0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            normalizedData[i][j] = (data[i][j] - mean[j]) / stdDev[j];
        }
    }

    return normalizedData;
}

std::vector<std::vector<float>> Data_Worker::maxAbsNormalization(std::vector<std::vector<float>> data) {
    int rows = data.size();
    int cols = data[0].size();

    std::vector<float> maxAbsValues(cols, 0.0);

    for (int j = 0; j < cols; ++j) {
        double maxAbs = 0.0;
        for (int i = 0; i < rows; ++i) {
            double absVal = std::abs(data[i][j]);
            if (absVal > maxAbs) {
                maxAbs = absVal;
            }
        }
        maxAbsValues[j] = maxAbs;
    }
    std::vector<std::vector<float>> normalizedData(rows, std::vector<float>(cols, 0.0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            normalizedData[i][j] = data[i][j] / maxAbsValues[j];
        }
    }

    return normalizedData;
}

std::vector<std::vector<float>> Data_Worker::quantileNormalization(std::vector<std::vector<float>> data) {
    int rows = data.size();
    int cols = data[0].size();

    std::vector<std::vector<float>> normalizedData(rows, std::vector<float>(cols, 0.0));

    std::vector<std::vector<float>> tempData = data;

    for (int j = 0; j < cols; ++j) {
        std::sort(tempData.begin(), tempData.end(), [j](const std::vector<float> &a, const std::vector<float> &b) {
            return a[j] < b[j];
        });

        for (int i = 0; i < rows; ++i) {
            normalizedData[i][j] = (i + 1.0) / rows;
        }

        for (int i = 0; i < rows; ++i) {
            data[i][j] = normalizedData[i][j];
        }
    }

    return data;
}

std::vector<std::vector<std::vector<float>>>
Data_Worker::call(Normalisation type, const std::vector<std::vector<float>> &inp,
                  const std::vector<std::vector<float>> &out) {
    std::vector<std::vector<std::vector<float>>> ret = {};
    switch (type) {
        case Normalisation::min_max_normalisation: {
            ret.push_back(min_max_normalisation(inp));
            ret.push_back(min_max_normalisation(out));
            return ret;
        }
        case Normalisation::z_normalisation: {
            ret.push_back(zScoreNormalization(inp));
            ret.push_back(zScoreNormalization(out));
            return ret;
        }
        case Normalisation::quantile_normalisation: {
            ret.push_back(quantileNormalization(inp));
            ret.push_back(quantileNormalization(out));
            return ret;
        }
        case Normalisation::max_abs_normalisation: {
            ret.push_back(maxAbsNormalization(inp));
            ret.push_back(maxAbsNormalization(out));
            return ret;
        }
        case Normalisation::without_normalisation: {
            ret.push_back(inp);
            ret.push_back(out);
            return ret;
        }

    }
}

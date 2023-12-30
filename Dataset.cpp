
#include "Dataset.h"

#include <utility>

Dataset::Dataset(std::vector<std::vector<float>> inp, std::vector<std::vector<float>> out) : input_data(std::move(inp)),
                                                                                             output_data(
                                                                                                     std::move(out)) {

}

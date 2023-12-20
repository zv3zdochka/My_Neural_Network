#include "json.h"

#include <vector>
#include <iostream>

int main(void) {
    nlohmann::json output;

    std::vector<int> x { 1, 2, 3, 4 };

    output["key"] = x;

    std::cout << output.dump(2) << std::endl;

    std::vector<int> y;

    for (const auto& i : output["key"]) {
        for (const auto& j : i) {
        }
    }

    return 0;
}
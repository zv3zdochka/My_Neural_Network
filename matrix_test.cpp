#include <iostream>
#include "Matrix.h"

int main() {
    std::vector<std::vector<float>> data1 = {{0.9,
                                             0.2,
                                             0.1}};

    std::vector<std::vector<float>> data2 = {{0.9}, {0.1}, {0.8}};



    Matrix matrix1(data1);
    Matrix matrix2(data2);

    Matrix result = matrix1 * matrix2;

    result.show_matrix(result);

    return 0;
}

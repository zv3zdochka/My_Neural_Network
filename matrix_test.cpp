#include <iostream>
#include "Matrix.h"

int main() {
    std::vector<std::vector<float>> data1 = {{0.4,
                                             1.0,
                                             0.3}};

    std::vector<std::vector<float>> data2 = {{1.0}, {2.0}};



    Matrix matrix1(data1);
    Matrix matrix2(data2);

    Matrix result = matrix1 * matrix2;

    result.showMatrix();

    return 0;
}

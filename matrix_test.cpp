#include <iostream>
#include "Matrix.h"

int main() {
    std::vector<std::vector<float>> data1 = {{0.5, 0.6},
                                             {2.0, 0.3},
                                             {4.0, 0.4}};

    std::vector<std::vector<float>> data2 = {{0.5, 0.7, 0.8},
                                             {0.2, 0.1, 0.7}};


    Matrix matrix1(data1);
    Matrix matrix2(data2);


    matrix1.showMatrix();
    matrix2.showMatrix();
    matrix1.transpose().showMatrix();
    Matrix res = matrix1.transpose() * matrix2;

    return 0;
}

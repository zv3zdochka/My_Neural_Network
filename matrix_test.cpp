#include <iostream>
#include "matrix.h"

int main() {
    // Примеры матриц для перемножения
    std::vector<std::vector<float>> data1 = {{0.3, 0.7, 0.5},
                                             {0.6, 0.5, 0.2},
                                             {0.8, 0.1, 0.9}};
    std::vector<std::vector<float>> data2 = {{0.761}, {0.603}, {0.650}};

    Matrix matrix1(data1);
    Matrix matrix2(data2);

    // Вывод исходных матриц
    std::cout << "Matrix 1:" << std::endl;
    for (size_t i = 0; i < matrix1.getRows(); ++i) {
        for (size_t j = 0; j < matrix1.getCols(); ++j) {
            std::cout << matrix1[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix 2:" << std::endl;
    for (size_t i = 0; i < matrix2.getRows(); ++i) {
        for (size_t j = 0; j < matrix2.getCols(); ++j) {
            std::cout << matrix2[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Перемножение матриц
    Matrix result = matrix1 * matrix2;

    // Вывод результата перемножения
    std::cout << "Result Matrix:" << std::endl;
    for (size_t i = 0; i < result.getRows(); ++i) {
        for (size_t j = 0; j < result.getCols(); ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

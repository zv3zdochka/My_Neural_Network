#include <iostream>
#include "Matrix.h"

int main() {
    std::vector<std::vector<float>> data1 = {{3.0, 8.5},
                                             {9.4, 8.0},
                                             {4.0, 3.9}};

    std::vector<std::vector<float>> data2 = {{7.2}, {1.7}};

    Matrix matrix1(data1);
    Matrix matrix2(data2);

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

#include <iostream>
#include <vector>
#include <cmath>

// Функция для Z-score нормализации
std::vector<std::vector<double>> zScoreNormalization(const std::vector<std::vector<double>>& data) {
    // Нахождение среднего и стандартного отклонения для каждого столбца
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

    // Z-score нормализация
    std::vector<std::vector<double>> normalizedData(rows, std::vector<double>(cols, 0.0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            normalizedData[i][j] = (data[i][j] - mean[j]) / stdDev[j];
        }
    }

    return normalizedData;
}

int main() {
    // Пример данных (ваш набор данных)
    std::vector<std::vector<double>> data = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };

    // Нормализация данных Z-score
    std::vector<std::vector<double>> normalizedDataZScore = zScoreNormalization(data);

    // Вывод нормализованных данных Z-score
    std::cout << "Нормализованные данные Z-score:" << std::endl;
    for (const auto& row : normalizedDataZScore) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}



#include <iostream>
#include <vector>
#include <algorithm>

// Функция для нормализации квантилей
std::vector<std::vector<double>> quantileNormalization(const std::vector<std::vector<double>>& data) {
    int rows = data.size();
    int cols = data[0].size();

    std::vector<std::vector<double>> normalizedData(rows, std::vector<double>(cols, 0.0));

    // Создание временной копии данных для сортировки
    std::vector<std::vector<double>> tempData = data;

    for (int j = 0; j < cols; ++j) {
        std::sort(tempData.begin(), tempData.end(), [j](const std::vector<double>& a, const std::vector<double>& b) {
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

int main() {
    // Пример данных (ваш набор данных)
    std::vector<std::vector<double>> data = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };

    // Нормализация данных квантилей
    std::vector<std::vector<double>> normalizedDataQuantile = quantileNormalization(data);

    // Вывод нормализованных данных квантилей
    std::cout << "Нормализованные данные квантилей:" << std::endl;
    for (const auto& row : normalizedDataQuantile) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <cmath>

// Функция для нормализации по максимальному абсолютному значению
std::vector<std::vector<double>> maxAbsNormalization(const std::vector<std::vector<double>>& data) {
    int rows = data.size();
    int cols = data[0].size();

    std::vector<double> maxAbsValues(cols, 0.0);

    // Нахождение максимального абсолютного значения для каждого столбца
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

    // Нормализация по максимальному абсолютному значению
    std::vector<std::vector<double>> normalizedData(rows, std::vector<double>(cols, 0.0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            normalizedData[i][j] = data[i][j] / maxAbsValues[j];
        }
    }

    return normalizedData;
}

int main() {
    // Пример данных (ваш набор данных)
    std::vector<std::vector<double>> data = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };

    // Нормализация данных по максимальному абсолютному значению
    std::vector<std::vector<double>> normalizedDataMaxAbs = maxAbsNormalization(data);

    // Вывод нормализованных данных по максимальному абсолютному значению
    std::cout << "Нормализованные данные по максимальному абсолютному значению:" << std::endl;
    for (const auto& row : normalizedDataMaxAbs) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}




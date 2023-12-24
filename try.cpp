#include "CrazyMath.h"
#include <iostream>
#include <numbers>
using namespace CrazyMath;
using namespace std::numbers;
float fast_sigmoid(float x) {
    auto f_sigmoid_1 = Divide(Const(1), Pow(Add(Const(1), (X)), 2));
    auto f_sigmoid_2 = Divide(Const(1), Pow(Add(Const(1), Multiply(X, Const(-1))), 2));
    if (x >= 0) {
        Derivative<decltype(f_sigmoid_1)> sigmoid_derivative(f_sigmoid_1);
        double result = sigmoid_derivative(x);
        return (float) result;
    } else {

        Derivative<decltype(f_sigmoid_2)> sigmoid_derivative(f_sigmoid_2);
        double result = sigmoid_derivative(x);

        return (float) result;
    }
}

int main() {

    std::cout << fast_sigmoid(0.1);

}

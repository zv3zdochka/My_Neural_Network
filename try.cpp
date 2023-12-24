#include "CrazyMath.h"
#include <iostream>

int main() {
    using namespace CrazyMath;

    // Define the sigmoid function: f(x) = 1 / (1 + exp(-x))
    auto sigmoid = Divide(Const(1), Add(Const(1), Exp(2.71828, Multiply(Const(-1), X))));

    // Calculate the derivative of the sigmoid function
    Derivative<decltype(sigmoid)> sigmoid_derivative(sigmoid);

    // Calculate the derivative at x = 0.5
    double result = sigmoid_derivative(0.5);

    std::cout << "The derivative of the sigmoid function at x = 0.5 is: " << result << std::endl;

    return 0;
}


---


# NeuralNetwork++: Library for Perceptron Implementation in C++

This project is a C++ library designed for implementing a simple perceptron capable of solving classification and prediction tasks. The implementation focuses on creating and training straightforward perceptrons for these purposes.

## Description

NeuralNetwork++ consists of a set of header files organizing the functionality for working with perceptrons at the library level:
### Modules:

- **Neurons**: Describes neurons, their weights, and activation functions.
- **Matrix**: Provides matrix operations for managing weights and data.
- **Activations**: Contains implementations of popular activation functions (sigmoid, hyperbolic tangent, SiLU, and a fast sigmoid approximation).
- **Utils**: Utility functions for data handling and information output.
- **Network**: The main class providing an interface for creating, training, and utilizing neural networks.

### Functionality:

- Creating and configuring neural networks with different numbers of layers and neurons in each layer.
- Training neural networks using backpropagation and gradient descent.
- Using a trained network for predictions on new data.

## Project Structure

- **Network**: The main file that consolidates modules and provides the interface for working with neural networks.
- **json.h**: A library for working with JSON files.
- **Main.cpp**: A file with an example of usage and testing the library's functionality on simple data.

## Inspiration and Project Goals

This project was created for educational purposes to understand the principles of neural networks. It was inspired by the book "Make Your Own Neural Network" by Tariq Rashid, which thoroughly explains the basics of creating and training neural networks.

## Usage

To use the library, you need to include the respective header files in your project and utilize the `Network` class interface. An example of usage can be seen below:

### Example Usage:

#### Initializing a Network and Adding Layers with Different Activation Functions:

```cpp
#include "Core.h"

int main() {
    std::filesystem::current_path("..");

    Network net;
    net.add_layer(LayerType::input, 2, FunctionType::fast_sigmoid);
    net.add_layer(LayerType::hidden, 3, FunctionType::sigmoid);
    net.add_layer(LayerType::hidden, 5, FunctionType::silu);
    net.add_layer(LayerType::hidden, 7, FunctionType::sigmoid);
    net.add_layer(LayerType::hidden, 3, FunctionType::tanh);
    net.add_layer(LayerType::output, 2, FunctionType::sigmoid);
    net.build();
    net.save("base.json");

    return 0;
}
```

This snippet demonstrates initializing a neural network using the `Network` class and adding multiple layers with different activation functions.

#### Training and Using a Trained Network:

```cpp
#include "Core.h"

int main() {
    std::filesystem::current_path("..");

    Network net;
    // ... (code omitted for brevity) ...

    std::vector<std::vector<float>> input_data = {{0.6f, 0.2f}};
    std::vector<std::vector<float>> output_data = {{1.0f, 0.3f}};

    const int epochs = 10000;

    net.train(input_data, output_data, Normalisation::min_max_normalisation, epochs, 1, 0.1);
    net.work(input_data);

    return 0;
}
```

This example demonstrates the training process of the initialized network using input and output data. After training, it uses the trained network to perform calculations on new input data.

These code snippets showcase the usage of the `NeuralNetwork++` library for initializing, training, and utilizing a neural network. These fragments can be combined into a single file to create a complete program.

## Dependencies

The project uses the standard C++ library and some external libraries such as json.h for working with JSON format.

## License

This project is distributed under the MIT License. Details can be found in the `LICENSE` file.

---

# Neural Network Library

This is a simple neural network library implemented in C++. The library provides functionality for creating, training, and using feedforward neural networks. It includes support for different activation functions, customizable network architectures, and data loading utilities.

## Contents

1. [Activation Functions](#activation-functions)
2. [DataLoader](#dataloader)
3. [Matrix Operations](#matrix-operations)
4. [Neural Network](#neural-network)
5. [Usage](#usage)

## Activation Functions

The activation functions are implemented in the `Activations.h` file. Currently supported functions are:
- Sigmoid
- Fast Sigmoid
- Silu (Rectified Linear Unit)
- Hyperbolic Tangent (Tanh)

## DataLoader

The `DataFunc.h` file contains a `DataLoader` class for reading and preprocessing datasets. It includes functions for reading datasets from files, normalizing data, and shuffling data.

## Matrix Operations

Matrix operations are implemented in the `Matrix.h` file. The `Matrix` class provides basic matrix operations such as addition, subtraction, multiplication, and transpose. It is used for handling the weights and inputs in the neural network.

## Neural Network

The neural network is implemented in the `Network.h` file. It supports customizable network architectures, including input, hidden, and output layers. The network can be trained using the backpropagation algorithm. The weights and synapses are managed using the `Matrix` class.

## Neurons

The `Neurons.h` file contains the `Neuron` class, which represents an individual neuron in the network. It includes functionality for computing neuron activations using different activation functions.

## Usage

To use the library, follow these steps:

1. Include the necessary header files in your project.
2. Create an instance of the `Network` class and configure the network architecture.
3. Train the network using the `train` method, providing input data, target outputs, and training parameters.
4. Use the trained network for predictions.

Refer to the example code and documentation in the header files for more details on usage.

Feel free to explore the source code and modify it according to your needs. If you find any issues or have suggestions for improvements, please create an issue in the repository.

Enjoy using the neural network library!
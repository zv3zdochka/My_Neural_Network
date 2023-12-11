cmake_minimum_required(VERSION 3.26)
project(My_own_Neural_Network)

set(CMAKE_CXX_STANDARD 23)

add_executable(My_own_Neural_Network
        Neurons.cpp
        Neurons.h

        Activations.h
        Activations.cpp

        Network.h
        Network.cpp

        Matrix.h
        Matrix.cpp

        main.cpp

)

add_executable(matrix_test matrix_test.cpp)
add_executable(try try.cpp)
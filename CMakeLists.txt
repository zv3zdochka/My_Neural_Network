cmake_minimum_required(VERSION 3.26)
project(My_own_Neural_Network)

set(CMAKE_CXX_STANDARD 20)

add_executable(My_own_Neural_Network
        Neurons.cpp
        Neurons.h

        Activations.h
        Activations.cpp

        Network.h
        Network.cpp

        Matrix.h
        Matrix.cpp

        CrazyMath.h
        CrazyMath.cpp

        main.cpp
        json.h

)

add_executable(try try.cpp CrazyMath.cpp CrazyMath.h)
cmake_minimum_required(VERSION 3.26)
project(My_own_Neural_Network)

set(CMAKE_CXX_STANDARD 20)

add_executable(My_own_Neural_Network
        Network/Neurons.cpp
        Network/Neurons.h

        Network/Activations.h
        Network/Activations.cpp

        Network/Network.h
        Network/Network.cpp

        Network/Matrix.h
        Network/Matrix.cpp

        main.cpp
        Network/json.h

        Network/Utils.cpp
        Network/Utils.h
        Core.h

)

add_executable(try try.cpp)
add_executable(create_dataset create_dataset.cpp)
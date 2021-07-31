cmake_minimum_required(VERSION 3.19)
project(LowPowerNeuralNetwork)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(LowPowerNeuralNetwork main.cpp DeepNeuralNetwork.cpp DeepNeuralNetwork.h Test/DNNTest.cpp Test/DNNTest.h)
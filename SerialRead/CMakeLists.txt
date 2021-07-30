cmake_minimum_required(VERSION 3.19)
project(SerialRead)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(SerialRead main.cpp SerialPort.cpp SerialPort.h)
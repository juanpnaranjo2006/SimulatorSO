cmake_minimum_required(VERSION 4.1)
project(SimulatorSO)

set(CMAKE_CXX_STANDARD 14)

add_executable(SimulatorSO
        main.cpp
        cpu.cpp
        cpu.h)
